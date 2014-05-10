/*
    Copyright (c) 2007-2014 Contributors as noted in the AUTHORS file

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

#ifndef __ZMQ_GSSAPI_SERVER_HPP_INCLUDED__
#define __ZMQ_GSSAPI_SERVER_HPP_INCLUDED__

#ifdef HAVE_LIBGSSAPI_KRB5

#include "gssapi_mechanism_base.hpp"

namespace zmq
{

    class msg_t;
    class session_base_t;

    class gssapi_server_t :
        public gssapi_mechanism_base_t
    {
    public:

        gssapi_server_t (session_base_t *session_,
                            const std::string &peer_address,
                            const options_t &options_);
        virtual ~gssapi_server_t ();

        // mechanism implementation
        virtual int next_handshake_command (msg_t *msg_);
        virtual int process_handshake_command (msg_t *msg_);
        virtual int encode (msg_t *msg_);
        virtual int decode (msg_t *msg_);
        virtual int zap_msg_available ();
        virtual status_t status () const;

    private:

        enum state_t {
            send_next_token,
            recv_next_token,
            expect_zap_reply,
            send_ready,
            recv_ready,
            connected
        };

        session_base_t * const session;

        const std::string peer_address;

        //  Current FSM state
        state_t state;

        //  True iff server considers the client authenticated
        bool security_context_established;

        //  The underlying mechanism type (ignored)
        gss_OID doid;

        void accept_context ();
        int produce_next_token (msg_t *msg_);
        int process_next_token (msg_t *msg_);
	void send_zap_request ();
	int receive_and_process_zap_reply();
    };

}

#endif

#endif
