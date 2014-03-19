/*
    Copyright (c) 2007-2013 Contributors as noted in the AUTHORS file

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stream.hpp"
#include "pipe.hpp"
#include "wire.hpp"
#include "random.hpp"
#include "likely.hpp"
#include "err.hpp"

zmq::stream_t::stream_t (class ctx_t *parent_, uint32_t tid_, int sid_) :
    socket_base_t (parent_, tid_, sid_),
    prefetched (false),
    identity_sent (false),
    current_out (NULL),
    more_out (false),
    next_peer_id (generate_random ())
{
    options.type = ZMQ_STREAM;
    options.raw_sock = true;

    prefetched_id.init ();
    prefetched_msg.init ();
}

zmq::stream_t::~stream_t ()
{
    zmq_assert (outpipes.empty ());
    prefetched_id.close ();
    prefetched_msg.close ();
}

void zmq::stream_t::xattach_pipe (pipe_t *pipe_, bool subscribe_to_all_)
{
    // subscribe_to_all_ is unused
    (void)subscribe_to_all_;

    zmq_assert (pipe_);

    identify_peer (pipe_);
    fq.attach (pipe_);
}

void zmq::stream_t::xpipe_terminated (pipe_t *pipe_)
{
    outpipes_t::iterator it = outpipes.find (pipe_->get_identity ());
    zmq_assert (it != outpipes.end ());
    outpipes.erase (it);
    fq.pipe_terminated (pipe_);
    if (pipe_ == current_out)
        current_out = NULL;
}

void zmq::stream_t::xread_activated (pipe_t *pipe_)
{
    fq.activated (pipe_);
}

void zmq::stream_t::xwrite_activated (pipe_t *pipe_)
{
    outpipes_t::iterator it;
    for (it = outpipes.begin (); it != outpipes.end (); ++it)
        if (it->second.pipe == pipe_)
            break;

    zmq_assert (it != outpipes.end ());
    zmq_assert (!it->second.active);
    it->second.active = true;
}

int zmq::stream_t::xsend (msg_t *msg_)
{
    //  If this is the first part of the message it's the ID of the
    //  peer to send the message to.
    if (!more_out) {
        zmq_assert (!current_out);

        //  If we have malformed message (prefix with no subsequent message)
        //  then just silently ignore it.
        //  TODO: The connections should be killed instead.
        if (msg_->flags () & msg_t::more) {

            //  Find the pipe associated with the identity stored in the prefix.
            //  If there's no such pipe return an error
            blob_t identity ((unsigned char*) msg_->data (), msg_->size ());
            outpipes_t::iterator it = outpipes.find (identity);

            if (it != outpipes.end ()) {
                current_out = it->second.pipe;
                if (!current_out->check_write ()) {
                    it->second.active = false;
                    current_out = NULL;
                    errno = EAGAIN;
                    return -1;
                }
            }
            else {
                errno = EHOSTUNREACH;
                return -1;
            }
        }

        //  Expect one more message frame.
        more_out = true;

        int rc = msg_->close ();
        errno_assert (rc == 0);
        rc = msg_->init ();
        errno_assert (rc == 0);
        return 0;
    }

    //  Ignore the MORE flag
    msg_->reset_flags (msg_t::more);

    //  This is the last part of the message.
    more_out = false;

    //  Push the message into the pipe. If there's no out pipe, just drop it.
    if (current_out) {

        // Close the remote connection if user has asked to do so
        // by sending zero length message.
        // Pending messages in the pipe will be dropped (on receiving term- ack)
        if (msg_->size () == 0) {
            current_out->terminate (false);
            int rc = msg_->close ();
            errno_assert (rc == 0);
            current_out = NULL;
            return 0;
        }
        bool ok = current_out->write (msg_);
        if (likely (ok))
            current_out->flush ();
        current_out = NULL;
    }
    else {
        int rc = msg_->close ();
        errno_assert (rc == 0);
    }

    //  Detach the message from the data buffer.
    int rc = msg_->init ();
    errno_assert (rc == 0);

    return 0;
}

int zmq::stream_t::xrecv (msg_t *msg_)
{
    if (prefetched) {
        if (!identity_sent) {
            int rc = msg_->move (prefetched_id);
            errno_assert (rc == 0);
            identity_sent = true;
        }
        else {
            int rc = msg_->move (prefetched_msg);
            errno_assert (rc == 0);
            prefetched = false;
        }
        return 0;
    }

    pipe_t *pipe = NULL;
    int rc = fq.recvpipe (&prefetched_msg, &pipe);
    if (rc != 0)
        return -1;

    zmq_assert (pipe != NULL);
    zmq_assert ((prefetched_msg.flags () & msg_t::more) == 0);

    //  We have received a frame with TCP data.
    //  Rather than sendig this frame, we keep it in prefetched
    //  buffer and send a frame with peer's ID.
    blob_t identity = pipe->get_identity ();
    rc = msg_->init_size (identity.size ());
    errno_assert (rc == 0);
    memcpy (msg_->data (), identity.data (), identity.size ());
    msg_->set_flags (msg_t::more);

    prefetched = true;
    identity_sent = true;

    return 0;
}

bool zmq::stream_t::xhas_in ()
{
    //  We may already have a message pre-fetched.
    if (prefetched)
        return true;

    //  Try to read the next message.
    //  The message, if read, is kept in the pre-fetch buffer.
    pipe_t *pipe = NULL;
    int rc = fq.recvpipe (&prefetched_msg, &pipe);
    if (rc != 0)
        return false;

    zmq_assert (pipe != NULL);
    zmq_assert ((prefetched_msg.flags () & msg_t::more) == 0);

    blob_t identity = pipe->get_identity ();
    rc = prefetched_id.init_size (identity.size ());
    errno_assert (rc == 0);
    memcpy (prefetched_id.data (), identity.data (), identity.size ());
    prefetched_id.set_flags (msg_t::more);

    prefetched = true;
    identity_sent = false;

    return true;
}

bool zmq::stream_t::xhas_out ()
{
    //  In theory, STREAM socket is always ready for writing. Whether actual
    //  attempt to write succeeds depends on which pipe the message is going
    //  to be routed to.
    return true;
}

void zmq::stream_t::identify_peer (pipe_t *pipe_)
{
    //  Always assign identity for raw-socket
    unsigned char buffer [5];
    buffer [0] = 0;
    put_uint32 (buffer + 1, next_peer_id++);
    blob_t identity = blob_t (buffer, sizeof buffer);

    memcpy (options.identity, identity.data (), identity.size ());
    options.identity_size = identity.size ();

    pipe_->set_identity (identity);
    //  Add the record into output pipes lookup table
    outpipe_t outpipe = {pipe_, true};
    const bool ok = outpipes.insert (
        outpipes_t::value_type (identity, outpipe)).second;
    zmq_assert (ok);
}
