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

#ifndef __ZMQ_MECHANISM_HPP_INCLUDED__
#define __ZMQ_MECHANISM_HPP_INCLUDED__

#include "stdint.hpp"
#include "options.hpp"
#include "blob.hpp"

namespace zmq
{

    //  Abstract class representing security mechanism.
    //  Different mechanism extedns this class.

    class msg_t;

    class mechanism_t
    {
    public:

        mechanism_t (const options_t &options_);

        virtual ~mechanism_t ();

        //  Prepare next handshake command that is to be sent to the peer.
        virtual int next_handshake_command (msg_t *msg_) = 0;

        //  Process the handshake command received from the peer.
        virtual int process_handshake_command (msg_t *msg_) = 0;

        virtual int encode (msg_t *msg_) { return 0; }

        virtual int decode (msg_t *msg_) { return 0; }

        //  Notifies mechanism about availability of ZAP message.
        virtual int zap_msg_available () { return 0; }

        //  True iff the handshake stage is complete?
        virtual bool is_handshake_complete () const = 0;

        void set_peer_identity (const void *id_ptr, size_t id_size);

        void peer_identity (msg_t *msg_);

    protected:

        //  Only used to identify the socket for the Socket-Type
        //  property in the wire protocol.
        const char *socket_type_string (int socket_type) const;

        size_t add_property (unsigned char *ptr, const char *name,
            const void *value, size_t value_len) const;

        //  Parses a metadata.
        //  Metadata consists of a list of properties consisting of
        //  name and value as size-specified strings.
        //  Returns 0 on success and -1 on error, in which case errno is set.
        int parse_metadata (const unsigned char *ptr_, size_t length);

        //  This is called by parse_property method whenever it
        //  parses a new property. The function should return 0
        //  on success and -1 on error, in which case it should
        //  set errno. Signaling error prevents parser from
        //  parsing remaining data.
        //  Derived classes are supposed to override this
        //  method to handle custom processing.
        virtual int property (const std::string name_,
                              const void *value_, size_t length_);

        options_t options;

    private:

        blob_t identity;

        //  Returns true iff socket associated with the mechanism
        //  is compatible with a given socket type 'type_'.
        bool check_socket_type (const std::string type_) const;
    };

}

#endif
