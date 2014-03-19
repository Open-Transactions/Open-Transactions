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

#include "router.hpp"
#include "pipe.hpp"
#include "wire.hpp"
#include "random.hpp"
#include "likely.hpp"
#include "err.hpp"

zmq::router_t::router_t (class ctx_t *parent_, uint32_t tid_, int sid_) :
    socket_base_t (parent_, tid_, sid_),
    prefetched (false),
    identity_sent (false),
    more_in (false),
    current_out (NULL),
    more_out (false),
    next_peer_id (generate_random ()),
    mandatory (false),
    //  raw_sock functionality in ROUTER is deprecated
    raw_sock (false),       
    probe_router (false)
{
    options.type = ZMQ_ROUTER;
    options.recv_identity = true;
    options.raw_sock = false;

    prefetched_id.init ();
    prefetched_msg.init ();
}

zmq::router_t::~router_t ()
{
    zmq_assert (anonymous_pipes.empty ());;
    zmq_assert (outpipes.empty ());
    prefetched_id.close ();
    prefetched_msg.close ();
}

void zmq::router_t::xattach_pipe (pipe_t *pipe_, bool subscribe_to_all_)
{
    // subscribe_to_all_ is unused
    (void)subscribe_to_all_;

    zmq_assert (pipe_);

    if (probe_router) {
        msg_t probe_msg_;
        int rc = probe_msg_.init ();
        errno_assert (rc == 0);

        rc = pipe_->write (&probe_msg_);
        // zmq_assert (rc) is not applicable here, since it is not a bug.
        pipe_->flush ();

        rc = probe_msg_.close ();
        errno_assert (rc == 0);
    }

    bool identity_ok = identify_peer (pipe_);
    if (identity_ok)
        fq.attach (pipe_);
    else
        anonymous_pipes.insert (pipe_);
}

int zmq::router_t::xsetsockopt (int option_, const void *optval_,
    size_t optvallen_)
{
    bool is_int = (optvallen_ == sizeof (int));
    int value = is_int? *((int *) optval_): 0;

    switch (option_) {
        case ZMQ_ROUTER_RAW:
            if (is_int && value >= 0) {
                raw_sock = (value != 0);
                if (raw_sock) {
                    options.recv_identity = false;
                    options.raw_sock = true;
                }
                return 0;
            }
            break;

        case ZMQ_ROUTER_MANDATORY:
            if (is_int && value >= 0) {
                mandatory = (value != 0);
                return 0;
            }
            break;

        case ZMQ_PROBE_ROUTER:
            if (is_int && value >= 0) {
                probe_router = (value != 0);
                return 0;
            }
            break;

        default:
            break;
    }
    errno = EINVAL;
    return -1;
}


void zmq::router_t::xpipe_terminated (pipe_t *pipe_)
{
    std::set <pipe_t*>::iterator it = anonymous_pipes.find (pipe_);
    if (it != anonymous_pipes.end ())
        anonymous_pipes.erase (it);
    else {
        outpipes_t::iterator it = outpipes.find (pipe_->get_identity ());
        zmq_assert (it != outpipes.end ());
        outpipes.erase (it);
        fq.pipe_terminated (pipe_);
        if (pipe_ == current_out)
            current_out = NULL;
    }
}

void zmq::router_t::xread_activated (pipe_t *pipe_)
{
    std::set <pipe_t*>::iterator it = anonymous_pipes.find (pipe_);
    if (it == anonymous_pipes.end ())
        fq.activated (pipe_);
    else {
        bool identity_ok = identify_peer (pipe_);
        if (identity_ok) {
            anonymous_pipes.erase (it);
            fq.attach (pipe_);
        }
    }
}

void zmq::router_t::xwrite_activated (pipe_t *pipe_)
{
    outpipes_t::iterator it;
    for (it = outpipes.begin (); it != outpipes.end (); ++it)
        if (it->second.pipe == pipe_)
            break;

    zmq_assert (it != outpipes.end ());
    zmq_assert (!it->second.active);
    it->second.active = true;
}

int zmq::router_t::xsend (msg_t *msg_)
{
    //  If this is the first part of the message it's the ID of the
    //  peer to send the message to.
    if (!more_out) {
        zmq_assert (!current_out);

        //  If we have malformed message (prefix with no subsequent message)
        //  then just silently ignore it.
        //  TODO: The connections should be killed instead.
        if (msg_->flags () & msg_t::more) {

            more_out = true;

            //  Find the pipe associated with the identity stored in the prefix.
            //  If there's no such pipe just silently ignore the message, unless
            //  router_mandatory is set.
            blob_t identity ((unsigned char*) msg_->data (), msg_->size ());
            outpipes_t::iterator it = outpipes.find (identity);

            if (it != outpipes.end ()) {
                current_out = it->second.pipe;
                if (!current_out->check_write ()) {
                    it->second.active = false;
                    current_out = NULL;
                    if (mandatory) {
                        more_out = false;
                        errno = EAGAIN;
                        return -1;
                    }
                }
            }
            else
            if (mandatory) {
                more_out = false;
                errno = EHOSTUNREACH;
                return -1;
            }
        }

        int rc = msg_->close ();
        errno_assert (rc == 0);
        rc = msg_->init ();
        errno_assert (rc == 0);
        return 0;
    }

    //  Ignore the MORE flag for raw-sock or assert?
    if (options.raw_sock)
        msg_->reset_flags (msg_t::more);

    //  Check whether this is the last part of the message.
    more_out = msg_->flags () & msg_t::more ? true : false;

    //  Push the message into the pipe. If there's no out pipe, just drop it.
    if (current_out) {

        // Close the remote connection if user has asked to do so
        // by sending zero length message.
        // Pending messages in the pipe will be dropped (on receiving term- ack)
        if (raw_sock && msg_->size() == 0) {
            current_out->terminate (false);
            int rc = msg_->close ();
            errno_assert (rc == 0);
            rc = msg_->init ();
            errno_assert (rc == 0);
            current_out = NULL;
            return 0;
        }

        bool ok = current_out->write (msg_);
        if (unlikely (!ok))
            current_out = NULL;
        else
        if (!more_out) {
            current_out->flush ();
            current_out = NULL;
        }
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

int zmq::router_t::xrecv (msg_t *msg_)
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
        more_in = msg_->flags () & msg_t::more ? true : false;
        return 0;
    }

    pipe_t *pipe = NULL;
    int rc = fq.recvpipe (msg_, &pipe);

    //  It's possible that we receive peer's identity. That happens
    //  after reconnection. The current implementation assumes that
    //  the peer always uses the same identity.
    while (rc == 0 && msg_->is_identity ())
        rc = fq.recvpipe (msg_, &pipe);

    if (rc != 0)
        return -1;

    zmq_assert (pipe != NULL);

    //  If we are in the middle of reading a message, just return the next part.
    if (more_in)
        more_in = msg_->flags () & msg_t::more ? true : false;
    else {
        //  We are at the beginning of a message.
        //  Keep the message part we have in the prefetch buffer
        //  and return the ID of the peer instead.
        rc = prefetched_msg.move (*msg_);
        errno_assert (rc == 0);
        prefetched = true;

        blob_t identity = pipe->get_identity ();
        rc = msg_->init_size (identity.size ());
        errno_assert (rc == 0);
        memcpy (msg_->data (), identity.data (), identity.size ());
        msg_->set_flags (msg_t::more);
        identity_sent = true;
    }

    return 0;
}

int zmq::router_t::rollback (void)
{
    if (current_out) {
        current_out->rollback ();
        current_out = NULL;
        more_out = false;
    }
    return 0;
}

bool zmq::router_t::xhas_in ()
{
    //  If we are in the middle of reading the messages, there are
    //  definitely more parts available.
    if (more_in)
        return true;

    //  We may already have a message pre-fetched.
    if (prefetched)
        return true;

    //  Try to read the next message.
    //  The message, if read, is kept in the pre-fetch buffer.
    pipe_t *pipe = NULL;
    int rc = fq.recvpipe (&prefetched_msg, &pipe);

    //  It's possible that we receive peer's identity. That happens
    //  after reconnection. The current implementation assumes that
    //  the peer always uses the same identity.
    //  TODO: handle the situation when the peer changes its identity.
    while (rc == 0 && prefetched_msg.is_identity ())
        rc = fq.recvpipe (&prefetched_msg, &pipe);

    if (rc != 0)
        return false;

    zmq_assert (pipe != NULL);

    blob_t identity = pipe->get_identity ();
    rc = prefetched_id.init_size (identity.size ());
    errno_assert (rc == 0);
    memcpy (prefetched_id.data (), identity.data (), identity.size ());
    prefetched_id.set_flags (msg_t::more);

    prefetched = true;
    identity_sent = false;

    return true;
}

bool zmq::router_t::xhas_out ()
{
    //  In theory, ROUTER socket is always ready for writing. Whether actual
    //  attempt to write succeeds depends on whitch pipe the message is going
    //  to be routed to.
    return true;
}

bool zmq::router_t::identify_peer (pipe_t *pipe_)
{
    msg_t msg;
    blob_t identity;
    bool ok;

    if (options.raw_sock) { //  Always assign identity for raw-socket
        unsigned char buf [5];
        buf [0] = 0;
        put_uint32 (buf + 1, next_peer_id++);
        identity = blob_t (buf, sizeof buf);
    }
    else {
        msg.init ();
        ok = pipe_->read (&msg);
        if (!ok)
            return false;

        if (msg.size () == 0) {
            //  Fall back on the auto-generation
            unsigned char buf [5];
            buf [0] = 0;
            put_uint32 (buf + 1, next_peer_id++);
            identity = blob_t (buf, sizeof buf);
            msg.close ();
        }
        else {
            identity = blob_t ((unsigned char*) msg.data (), msg.size ());
            outpipes_t::iterator it = outpipes.find (identity);
            msg.close ();

            //  Ignore peers with duplicate ID.
            if (it != outpipes.end ())
                return false;
        }
    }

    pipe_->set_identity (identity);
    //  Add the record into output pipes lookup table
    outpipe_t outpipe = {pipe_, true};
    ok = outpipes.insert (outpipes_t::value_type (identity, outpipe)).second;
    zmq_assert (ok);

    return true;
}
