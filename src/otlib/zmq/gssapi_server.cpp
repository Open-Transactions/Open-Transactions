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

#include "platform.hpp"

#ifdef HAVE_LIBGSSAPI_KRB5

#ifdef ZMQ_HAVE_WINDOWS
#include "windows.hpp"
#endif

#include <string.h>
#include <string>

#include "msg.hpp"
#include "session_base.hpp"
#include "err.hpp"
#include "gssapi_server.hpp"
#include "wire.hpp"

#include <gssapi/gssapi.h>

zmq::gssapi_server_t::gssapi_server_t (session_base_t *session_,
                                       const std::string &peer_address_,
                                       const options_t &options_) :
    gssapi_mechanism_base_t (options_),
    session (session_),
    peer_address (peer_address_),
    state (recv_next_token),
    security_context_established (false)
{
    maj_stat = GSS_S_CONTINUE_NEEDED;
    if(!options_.gss_principal.empty())
    {
        const std::string::size_type principal_size = options_.gss_principal.size();
        principal_name = static_cast <char *>(malloc(principal_size+1));
        assert(principal_name);
        memcpy(principal_name, options_.gss_principal.c_str(), principal_size+1 );

        if (acquire_credentials (principal_name, &cred) != 0)
            maj_stat = GSS_S_FAILURE;
    }
}

zmq::gssapi_server_t::~gssapi_server_t ()
{
    if(cred)
        gss_release_cred(&min_stat, &cred);

    if(target_name)
        gss_release_name(&min_stat, &target_name);
}

int zmq::gssapi_server_t::next_handshake_command (msg_t *msg_)
{
    if (state == send_ready) {
        int rc = produce_ready(msg_);
        if (rc == 0)
            state = recv_ready;

        return rc;
    }

    if (state != send_next_token) {
        errno = EAGAIN;
        return -1;
    }

    if (produce_next_token (msg_) < 0)
        return -1;

    if (maj_stat != GSS_S_CONTINUE_NEEDED && maj_stat != GSS_S_COMPLETE)
        return -1;

    if (maj_stat == GSS_S_COMPLETE) {
        security_context_established = true;
    }

    state = recv_next_token;

    return 0;
}

int zmq::gssapi_server_t::process_handshake_command (msg_t *msg_)
{
    if (state == recv_ready) {
        int rc = process_ready(msg_);
        if (rc == 0)
            state = connected;

        return rc;
    }

    if (state != recv_next_token) {
        errno = EPROTO;
        return -1;
    }

    if (security_context_established) {
     	//  Use ZAP protocol (RFC 27) to authenticate the user.
        bool expecting_zap_reply = false;
        int rc = session->zap_connect ();
        if (rc == 0) {
            send_zap_request();
            rc = receive_and_process_zap_reply ();
            if (rc != 0) {
                if (errno != EAGAIN)
                    return -1;
                expecting_zap_reply = true;
            }
        }
        state = expecting_zap_reply? expect_zap_reply: send_ready;
        return 0;
    }

    if (process_next_token (msg_) < 0)
        return -1;

    accept_context ();
    state = send_next_token;

    errno_assert (msg_->close () == 0);
    errno_assert (msg_->init () == 0);

    return 0;
}

void zmq::gssapi_server_t::send_zap_request ()
{
    int rc;
    msg_t msg;

    //  Address delimiter frame
    rc = msg.init ();
    errno_assert (rc == 0);
    msg.set_flags (msg_t::more);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);

    //  Version frame
    rc = msg.init_size (3);
    errno_assert (rc == 0);
    memcpy (msg.data (), "1.0", 3);
    msg.set_flags (msg_t::more);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);

    //  Request ID frame
    rc = msg.init_size (1);
    errno_assert (rc == 0);
    memcpy (msg.data (), "1", 1);
    msg.set_flags (msg_t::more);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);

    //  Domain frame
    rc = msg.init_size (options.zap_domain.length ());
    errno_assert (rc == 0);
    memcpy (msg.data (), options.zap_domain.c_str (), options.zap_domain.length ());
    msg.set_flags (msg_t::more);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);

    //  Address frame
    rc = msg.init_size (peer_address.length ());
    errno_assert (rc == 0);
    memcpy (msg.data (), peer_address.c_str (), peer_address.length ());
    msg.set_flags (msg_t::more);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);

    //  Identity frame
    rc = msg.init_size (options.identity_size);
    errno_assert (rc == 0);
    memcpy (msg.data (), options.identity, options.identity_size);
    msg.set_flags (msg_t::more);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);

    //  Mechanism frame
    rc = msg.init_size (6);
    errno_assert (rc == 0);
    memcpy (msg.data (), "GSSAPI", 6);
    msg.set_flags (msg_t::more);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);

    //  Principal frame
    gss_buffer_desc principal;
    gss_display_name(&min_stat, target_name, &principal, NULL);

    rc = msg.init_size (principal.length);
    errno_assert (rc == 0);
    memcpy (msg.data (), principal.value, principal.length);
    rc = session->write_zap_msg (&msg);
    errno_assert (rc == 0);
    gss_release_buffer(&min_stat, &principal);
}

int zmq::gssapi_server_t::receive_and_process_zap_reply ()
{
    int rc = 0;
    msg_t msg [7];  //  ZAP reply consists of 7 frames

    //  Initialize all reply frames
    for (int i = 0; i < 7; i++) {
        rc = msg [i].init ();
        errno_assert (rc == 0);
    }

    for (int i = 0; i < 7; i++) {
        rc = session->read_zap_msg (&msg [i]);
        if (rc == -1)
            break;
        if ((msg [i].flags () & msg_t::more) == (i < 6? 0: msg_t::more)) {
            errno = EPROTO;
            rc = -1;
            break;
        }
    }

    if (rc != 0)
        goto error;

    //  Address delimiter frame
    if (msg [0].size () > 0) {
        rc = -1;
        errno = EPROTO;
        goto error;
    }

    //  Version frame
    if (msg [1].size () != 3 || memcmp (msg [1].data (), "1.0", 3)) {
        rc = -1;
        errno = EPROTO;
        goto error;
    }

    //  Request id frame
    if (msg [2].size () != 1 || memcmp (msg [2].data (), "1", 1)) {
        rc = -1;
        errno = EPROTO;
        goto error;
    }

    //  Status code frame
    if (msg [3].size () != 3 || memcmp (msg [3].data (), "200", 3)) {
        rc = -1;
        errno = EACCES;
        goto error;
    }

    //  Save user id
    set_user_id (msg [5].data (), msg [5].size ());

    //  Process metadata frame
    rc = parse_metadata (static_cast <const unsigned char*> (msg [6].data ()),
                         msg [6].size (), true);

error:
    for (int i = 0; i < 7; i++) {
        const int rc2 = msg [i].close ();
        errno_assert (rc2 == 0);
    }

    return rc;
}


int zmq::gssapi_server_t::encode (msg_t *msg_)
{
    zmq_assert (state == connected);

    if (do_encryption)
      return encode_message (msg_);

    return 0;
}

int zmq::gssapi_server_t::decode (msg_t *msg_)
{
    zmq_assert (state == connected);

    if (do_encryption)
      return decode_message (msg_);

    return 0;
}

int zmq::gssapi_server_t::zap_msg_available ()
{
    if (state != expect_zap_reply) {
        errno = EFSM;
        return -1;
    }
    const int rc = receive_and_process_zap_reply ();
    if (rc == 0)
        state = send_ready;
    return rc;
}

zmq::mechanism_t::status_t zmq::gssapi_server_t::status () const
{
    return state == connected? mechanism_t::ready: mechanism_t::handshaking;
}

int zmq::gssapi_server_t::produce_next_token (msg_t *msg_)
{
    if (send_tok.length != 0) { // Client expects another token
        if (produce_initiate(msg_, send_tok.value, send_tok.length) < 0)
            return -1;
        gss_release_buffer(&min_stat, &send_tok);
    }

    if (maj_stat != GSS_S_COMPLETE && maj_stat != GSS_S_CONTINUE_NEEDED) {
        gss_release_name(&min_stat, &target_name);
        if (context != GSS_C_NO_CONTEXT)
            gss_delete_sec_context(&min_stat, &context, GSS_C_NO_BUFFER);
        return -1;
    }

    return 0;
}

int zmq::gssapi_server_t::process_next_token (msg_t *msg_)
{
    if (maj_stat == GSS_S_CONTINUE_NEEDED) {
        if (process_initiate(msg_, &recv_tok.value, recv_tok.length) < 0) {
            if (target_name != GSS_C_NO_NAME)
                gss_release_name(&min_stat, &target_name);
            return -1;
        }
    }

    return 0;
}

void zmq::gssapi_server_t::accept_context ()
{
    maj_stat = gss_accept_sec_context(&init_sec_min_stat, &context, cred,
                                      &recv_tok, GSS_C_NO_CHANNEL_BINDINGS,
                                      &target_name, &doid, &send_tok,
                                      &ret_flags, NULL, NULL);

    if (recv_tok.value) {
        free (recv_tok.value);
        recv_tok.value = NULL;
    }
}

#endif
