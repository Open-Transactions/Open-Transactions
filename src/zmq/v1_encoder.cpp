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

#include "encoder.hpp"
#include "v1_encoder.hpp"
#include "likely.hpp"
#include "wire.hpp"

zmq::v1_encoder_t::v1_encoder_t (size_t bufsize_) :
    encoder_base_t <v1_encoder_t> (bufsize_)
{
    //  Write 0 bytes to the batch and go to message_ready state.
    next_step (NULL, 0, &v1_encoder_t::message_ready, true);
}

zmq::v1_encoder_t::~v1_encoder_t ()
{
}

void zmq::v1_encoder_t::size_ready ()
{
    //  Write message body into the buffer.
    next_step (in_progress->data (), in_progress->size (),
        &v1_encoder_t::message_ready, true);
}

void zmq::v1_encoder_t::message_ready ()
{
    //  Get the message size.
    size_t size = in_progress->size ();

    //  Account for the 'flags' byte.
    size++;

    //  For messages less than 255 bytes long, write one byte of message size.
    //  For longer messages write 0xff escape character followed by 8-byte
    //  message size. In both cases 'flags' field follows.
    if (size < 255) {
        tmpbuf [0] = (unsigned char) size;
        tmpbuf [1] = (in_progress->flags () & msg_t::more);
        next_step (tmpbuf, 2, &v1_encoder_t::size_ready, false);
    }
    else {
        tmpbuf [0] = 0xff;
        put_uint64 (tmpbuf + 1, size);
        tmpbuf [9] = (in_progress->flags () & msg_t::more);
        next_step (tmpbuf, 10, &v1_encoder_t::size_ready, false);
    }
}
