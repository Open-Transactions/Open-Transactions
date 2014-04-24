/************************************************************************************
 *
 *  OTServerSocket.cpp  (Open Transactions server socket based on ZMQ.)
 */

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA1

 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net
 *
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT (PGP Key in license file):
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- otlib.........A class library.......LICENSE:...LAGPLv3
 *   -- otapi.........A client API..........LICENSE:...LAGPLv3
 *   -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
 *   -- otserver......Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (bitcointrader4@gmail.com).
 *  The open-source community has since actively contributed.
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT API, then you
 *   don't have to open-source your code--only your changes to
 *   Open-Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open-Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open-Transactions terms remain respected, with regard to
 *   the Open-Transactions code itself.
 *
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   See Lucre on Github:  https://github.com/benlaurie/lucre
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.

 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.9 (Darwin)

 iQIcBAEBAgAGBQJRSsfJAAoJEAMIAO35UbuOQT8P/RJbka8etf7wbxdHQNAY+2cC
 vDf8J3X8VI+pwMqv6wgTVy17venMZJa4I4ikXD/MRyWV1XbTG0mBXk/7AZk7Rexk
 KTvL/U1kWiez6+8XXLye+k2JNM6v7eej8xMrqEcO0ZArh/DsLoIn1y8p8qjBI7+m
 aE7lhstDiD0z8mwRRLKFLN2IH5rAFaZZUvj5ERJaoYUKdn4c+RcQVei2YOl4T0FU
 LWND3YLoH8naqJXkaOKEN4UfJINCwxhe5Ke9wyfLWLUO7NamRkWD2T7CJ0xocnD1
 sjAzlVGNgaFDRflfIF4QhBx1Ddl6wwhJfw+d08bjqblSq8aXDkmFA7HeunSFKkdn
 oIEOEgyj+veuOMRJC5pnBJ9vV+7qRdDKQWaCKotynt4sWJDGQ9kWGWm74SsNaduN
 TPMyr9kNmGsfR69Q2Zq/FLcLX/j8ESxU+HYUB4vaARw2xEOu2xwDDv6jt0j3Vqsg
 x7rWv4S/Eh18FDNDkVRChiNoOIilLYLL6c38uMf1pnItBuxP3uhgY6COm59kVaRh
 nyGTYCDYD2TK+fI9o89F1297uDCwEJ62U0Q7iTDp5QuXCoxkPfv8/kX6lS6T3y9G
 M9mqIoLbIQ1EDntFv7/t6fUTS2+46uCrdZWbQ5RjYXdrzjij02nDmJAm2BngnZvd
 kamH0Y/n11lCvo1oQxM+
 =uSzz
 -----END PGP SIGNATURE-----
 **************************************************************/

#include "OTServerSocket.hpp"

#include <OTLog.hpp>

#define	DEFAULT_LATENCY_SEND_MS				5000
#define	DEFAULT_LATENCY_SEND_NO_TRIES		2
#define	DEFAULT_LATENCY_RECEIVE_MS			5000
#define	DEFAULT_LATENCY_RECEIVE_NO_TRIES	2
#define	DEFAULT_LATENCY_DELAY_AFTER     	50
#define	DEFAULT_IS_BLOCKING					false

#define	KEY_LATENCY_SEND_MS					"latency_send_ms"
#define	KEY_LATENCY_SEND_NO_TRIES			"latency_send_no_tries"
#define	KEY_LATENCY_RECEIVE_MS				"latency_receive_ms"
#define	KEY_LATENCY_RECEIVE_NO_TRIES		"latency_receive_no_tries"
#define	KEY_LATENCY_DELAY_AFTER     		"latency_delay_after"
#define	KEY_IS_BLOCKING						"is_blocking"


OTServerSocket::OTServerSocket()
  : m_pContext(NULL),
    m_pSocket(NULL),

    m_strBindingPath(""),

    m_bInitialized(false),
    m_HasContext(false),
    m_bIsListening(false),

    m_lLatencySendMs(DEFAULT_LATENCY_SEND_MS),
    m_nLatencySendNoTries(DEFAULT_LATENCY_SEND_NO_TRIES),
    m_lLatencyReceiveMs(DEFAULT_LATENCY_RECEIVE_MS),
    m_nLatencyReceiveNoTries(DEFAULT_LATENCY_RECEIVE_NO_TRIES),
    m_lLatencyDelayAfter(DEFAULT_LATENCY_DELAY_AFTER),
    m_bIsBlocking(DEFAULT_IS_BLOCKING),

    m_pMutex(new tthread::mutex)
{
}

OTServerSocket::~OTServerSocket()
{
    if (NULL != m_pSocket)	delete m_pSocket;	m_pSocket	= NULL;
    if (NULL != m_pContext)	delete m_pContext;	m_pContext	= NULL;
    if (NULL != m_pMutex)	delete m_pMutex;	m_pMutex	= NULL;
}

bool OTServerSocket::Init()
{
    if (m_bInitialized) return false;
    if (m_HasContext) return false;
    if (m_bIsListening) return false;

    m_bInitialized =  true;
    return true;
}

bool OTServerSocket::Init(
        const int64_t	   & lLatencySendMs,
        const int32_t	   & nLatencySendNoTries,
        const int64_t	   & lLatencyReceiveMs,
        const int32_t	   & nLatencyReceiveNoTries,
        const int64_t	   & lLatencyDelayAfter,
        const bool	   & bIsBlocking
        )
{
    if (m_bInitialized) return false;
    if (m_HasContext) return false;
    if (m_bIsListening) return false;

    m_lLatencySendMs		 = lLatencySendMs;
    m_nLatencySendNoTries	 = nLatencySendNoTries;
    m_lLatencyReceiveMs		 = lLatencyReceiveMs;
    m_nLatencyReceiveNoTries = nLatencyReceiveNoTries;
    m_lLatencyDelayAfter     = lLatencyDelayAfter;
    m_bIsBlocking			 = bIsBlocking;

    m_bInitialized =  true;
    return true;
}

bool OTServerSocket::Init(OTSettings * pSettings)
{
    if (m_bInitialized) return false;
    if (m_HasContext) return false;
    if (m_bIsListening) return false;

    if (NULL == pSettings) { OT_FAIL; };

    bool bIsNew;
    {
        if(!pSettings->CheckSet_long("latency", KEY_LATENCY_SEND_MS,		m_lLatencySendMs,		m_lLatencySendMs,		bIsNew)) { OT_FAIL; };
    }
    {
        int64_t lResult = 0;
        if(!pSettings->CheckSet_long("latency", KEY_LATENCY_SEND_NO_TRIES,	m_nLatencySendNoTries,	lResult,				bIsNew)) { OT_FAIL;  };
        m_nLatencySendNoTries = static_cast<int32_t>(lResult);
    }
    {
        if(!pSettings->CheckSet_long("latency", KEY_LATENCY_RECEIVE_MS,		m_lLatencyReceiveMs,	m_lLatencyReceiveMs,	bIsNew)) { OT_FAIL;  };
    }
    {
        int64_t lResult = 0;
        if(!pSettings->CheckSet_long("latency", KEY_LATENCY_RECEIVE_NO_TRIES, m_nLatencyReceiveNoTries, lResult,			bIsNew)) { OT_FAIL;  };
        m_nLatencyReceiveNoTries = static_cast<int32_t>(lResult);
    }
    {
        if(!pSettings->CheckSet_long("latency", KEY_LATENCY_DELAY_AFTER,	m_lLatencyDelayAfter,	m_lLatencyDelayAfter,	bIsNew)) { OT_FAIL;  };
    }
    {
        if(!pSettings->CheckSet_bool("latency", KEY_IS_BLOCKING,			m_bIsBlocking,			m_bIsBlocking,			bIsNew)) { OT_FAIL;  };
    }

    m_bInitialized = true;

    return true;
}



bool OTServerSocket::NewContext()
{
    if (!m_bInitialized) return false;

    m_HasContext = false;

    if (NULL != m_pSocket)	delete m_pSocket;	m_pSocket	= NULL;
    if (NULL != m_pContext)	delete m_pContext;	m_pContext	= NULL;

    m_pContext = new zmq::context_t(1);

    m_HasContext = true;
    return true;
}


bool OTServerSocket::Listen(const OTString &strBind)
{
    if (!m_bInitialized) return false;
    if (!m_HasContext) return false;
    m_bIsListening = false;

    if (strBind.Exists() && !strBind.Compare("") &&  3 < strBind.GetLength())
    {
        if (!m_strBindingPath.Exists() || !m_strBindingPath.Compare(strBind)) // check if it is not the same
        {
            m_strBindingPath = strBind; // update m_strBindingPath
        }
    }
    else  // lets use m_strBindingPath, if it exists and isn't too short.
    {
        if (!m_strBindingPath.Exists() || 3 > m_strBindingPath.GetLength()) { return false; };  // m_strBindingPath is bad also, fail.
    }

    if (NULL != m_pSocket) delete m_pSocket; m_pSocket = NULL;  // cleanup any old socket

//	m_pSocket = NULL;
    m_pSocket = new zmq::socket_t(*m_pContext, ZMQ_REP);  // RESPONSE socket (Request / Response.)
    OT_ASSERT_MSG(NULL != m_pSocket, "OTServerSocket::Listen: new zmq::socket(context, ZMQ_REP)");


    //  Configure socket to not wait at close time
    //
    const int32_t linger = 0; // close immediately
    m_pSocket->setsockopt (ZMQ_LINGER, &linger, sizeof (linger));
    /*
     int32_t zmq_setsockopt (void *socket, int32_t option_name, const void *option_value, size_t option_len);

     Caution: All options, with the exception of ZMQ_SUBSCRIBE, ZMQ_UNSUBSCRIBE and ZMQ_LINGER, only take effect for subsequent socket bind/connects.
     */


    m_pSocket->bind(m_strBindingPath.Get());  // since m_strBindingPath was checked and set above.

    m_bIsListening = true;
    return true;

}
// -----------------------------------
/*
 typedef struct
 {
 void *socket;
 int32_t fd;
 short events;
 short revents;
 } zmq_pollitem_t;
 */

// The bool means true == try again soon, false == don't try again.
//
bool OTServerSocket::HandlePollingError()
{
    bool bRetVal = false;

    switch (errno) {
            // At least one of the members of the items array refers to a socket whose associated ØMQ context was terminated.
        case ETERM:
            OTLog::Error("OTServerSocket::HandlePollingError: Failure: At least one of the members of the items array refers to a socket whose associated ØMQ context was terminated. (Deleting and re-creating the context.)\n");
            this->NewContext();
            this->Listen(m_strBindingPath);
            break;
            // The provided items was not valid (NULL).
        case EFAULT:
            OTLog::Error("OTServerSocket::HandlePollingError: Failed: The provided polling items were not valid (NULL).\n");
            break;
            // The operation was interrupted by delivery of a signal before any events were available.
        case EINTR:
            OTLog::Error("OTServerSocket::HandlePollingError: The operation was interrupted by delivery of a signal before any events were available. Re-trying...\n");
            bRetVal = true;
            break;
        default:
            OTLog::Error("OTServerSocket::HandlePollingError: Default case. Re-trying...\n");
            bRetVal = true;
            break;
    }
    return bRetVal;
}

// return value bool, true == try again, false == error, failed.
//
bool OTServerSocket::HandleSendingError()
{
    bool bRetVal = false;

    switch (errno) {
            // Non-blocking mode was requested and the message cannot be sent at the moment.
        case EAGAIN:
            OTLog::vOutput(0, "OTServerSocket::HandleSendingError: Non-blocking mode was requested and the message cannot be sent at the moment. Re-trying...\n");
            bRetVal = true;
            break;
            // The zmq_send() operation is not supported by this socket type.
        case ENOTSUP:
            OTLog::Error("OTServerSocket::HandleSendingError: failure: The zmq_send() operation is not supported by this socket type.\n");
            break;
            // The zmq_send() operation cannot be performed on this socket at the moment due to the socket not being in the appropriate state. This error may occur with socket types that switch between several states, such as ZMQ_REP. See the messaging patterns section of zmq_socket(3) for more information.
        case EFSM:
            OTLog::vOutput(0, "OTServerSocket::HandleSendingError: The zmq_send() operation cannot be performed on this socket at the moment due to the socket not being in the appropriate state. Deleting socket and listening again...\n");
        { OTString strTemp(m_strBindingPath); this->Listen(strTemp); }
            break;
            // The ØMQ context associated with the specified socket was terminated.
        case ETERM:
            OTLog::Error("OTServerSocket::HandleSendingError: The ØMQ context associated with the specified socket was terminated. (Deleting and re-creating the context and the socket, and listening again.)\n");
            this->NewContext();
        { OTString strTemp(m_strBindingPath); this->Listen(strTemp); }
            break;
            // The provided socket was invalid.
        case ENOTSOCK:
            OTLog::Error("OTServerSocket::HandleSendingError: The provided socket was invalid. (Deleting socket and listening again...)\n");
        { OTString strTemp(m_strBindingPath); this->Listen(strTemp); }
            break;
            // The operation was interrupted by delivery of a signal before the message was sent. Re-trying...
        case EINTR:
            OTLog::Error("OTServerSocket::HandleSendingError: The operation was interrupted by delivery of a signal before the message was sent. (Re-trying...)\n");
            bRetVal = true;
            break;
            // Invalid message.
        case EFAULT:
            OTLog::Error("OTServerSocket::HandleSendingError: Failure: The provided pollitems were not valid (NULL).\n");
            break;
        default:
            OTLog::Error("OTServerSocket::HandleSendingError: Default case. Re-trying...\n");
            bRetVal = true;
            break;
    }
    return bRetVal;
}


bool OTServerSocket::HandleReceivingError()
{
    bool bRetVal = false;

    switch (errno) {
            // Non-blocking mode was requested and no messages are available at the moment.
        case EAGAIN:
            OTLog::vOutput(0, "OTServerSocket::HandleReceivingError: Non-blocking mode was requested and no messages are available at the moment. Re-trying...\n");
            bRetVal = true;
            break;
            // The zmq_recv() operation is not supported by this socket type.
        case ENOTSUP:
            OTLog::Error("OTServerSocket::HandleReceivingError: Failure: The zmq_recv() operation is not supported by this socket type.\n");
            break;
            // The zmq_recv() operation cannot be performed on this socket at the moment due to the socket not being in the appropriate state. This error may occur with socket types that switch between several states, such as ZMQ_REP. See the messaging patterns section of zmq_socket(3) for more information.
        case EFSM:
            OTLog::vOutput(0, "OTServerSocket::HandleReceivingError: The zmq_recv() operation cannot be performed on this socket at the moment due to the socket not being in the appropriate state. (Deleting socket and listening again...)\n");
        { OTString strTemp(m_strBindingPath); this->Listen(strTemp); }
            break;
            // The ØMQ context associated with the specified socket was terminated.
        case ETERM:
            OTLog::Error("OTServerSocket::HandleReceivingError: The ØMQ context associated with the specified socket was terminated. (Re-creating the context, and listening again with a new socket...)\n");
            this->NewContext();
        { OTString strTemp(m_strBindingPath); this->Listen(strTemp); }
            break;
            // The provided socket was invalid.
        case ENOTSOCK:
            OTLog::Error("OTServerSocket::HandleReceivingError: The provided socket was invalid. (Deleting socket and listening again.)\n");
        { OTString strTemp(m_strBindingPath); this->Listen(strTemp); }
            break;
            // The operation was interrupted by delivery of a signal before a message was available.
        case EINTR:
            OTLog::Error("OTServerSocket::HandleSendingError: The operation was interrupted by delivery of a signal before the message was sent. (Re-trying...)\n");
            bRetVal = true;
            break;
            // The message passed to the function was invalid.
        case EFAULT:
            OTLog::Error("OTServerSocket::HandleReceivingError: Failure: The message passed to the function was invalid.\n");
            break;
        default:
            OTLog::Error("OTServerSocket::HandleReceivingError: Default case. Re-trying...\n");
            bRetVal = true;
            break;
    }
    return bRetVal;
}


bool OTServerSocket::Send(const std::string & str_Reply)
{
    OT_ASSERT_MSG(NULL != m_pSocket, "m_pSocket == NULL in OTServerSocket::Send()");
    OT_ASSERT_MSG(NULL != m_pContext, "m_pContext == NULL in OTServerSocket::Send()");
    OT_ASSERT_MSG(str_Reply.size() > 0, "str_Reply.size() > 0");

    if (!m_bInitialized) return false;
    if (!m_HasContext) return false;
    if (!m_bIsListening) return false;

    // -----------------------------------
    const int64_t lLatencySendMilliSec	= this->m_lLatencySendMs;
    const int64_t lLatencySendMicroSec	= lLatencySendMilliSec*1000; // Microsecond is 1000 times smaller than millisecond.

    // Convert the std::string (reply) into a ZMQ message
    zmq::message_t reply (str_Reply.length());
    memcpy((void *) reply.data(), str_Reply.c_str(), str_Reply.length());
    // -----------------------------------

    bool bSuccessSending	= false;

    if (this->m_bIsBlocking)
    {
        bSuccessSending = m_pSocket->send(reply); // Blocking.
    }
    else // not blocking
    {
        int32_t		nSendTries	= this->m_nLatencySendNoTries;
        int64_t	lDoubling	= lLatencySendMicroSec;
        bool	bKeepTrying = true;

        while (bKeepTrying && (nSendTries > 0))
        {
            zmq::pollitem_t items [] = {
                { (*m_pSocket), 0, ZMQ_POLLOUT,	0 }
            };

            const int32_t nPoll = zmq::poll(&items[0], 1, lDoubling);	// ZMQ_POLLOUT, 1 item, timeout (microseconds in ZMQ 2.1; changes to milliseconds in 3.0)
            lDoubling *= 2;

            if (items[0].revents & ZMQ_POLLOUT)
            {
                bSuccessSending = m_pSocket->send(reply, ZMQ_NOBLOCK); // <=========== SEND ===============
                OTLog::SleepMilliseconds( 1 );

                if (!bSuccessSending)
                {
                    if (false == HandleSendingError())
                        bKeepTrying = false;
                }
                else
                    break; // (Success -- we're done in this loop.)
            }
            else if ((-1) == nPoll) // error.
            {
                if (false == HandlePollingError())
                    bKeepTrying = false;
            }

            --nSendTries;
        }
    }
    /*
     Normally, we try to send...
     If the send fails, we wait X ms and then try again (Y times).

     BUT -- what if the failure was an errno==EAGAIN ?
     In that case, it's not a REAL failure, but rather, a "failure right now, try again in a sec."
     */
    // ***********************************

    if (bSuccessSending)
        OTLog::SleepMilliseconds( m_lLatencyDelayAfter > 0 ? m_lLatencyDelayAfter : 1 );

    return bSuccessSending;
}
// -----------------------------------

bool OTServerSocket::Receive(std::string & str_Message)
{
    OT_ASSERT_MSG(NULL != m_pContext, "m_pContext == NULL in OTServerSocket::Receive()");
    OT_ASSERT_MSG(NULL != m_pSocket, "m_pSocket == NULL in OTServerSocket::Receive()");


    if (!m_bInitialized) return false;
    if (!m_HasContext) return false;
    if (!m_bIsListening) return false;

    // -----------------------------------
    const int64_t lLatencyRecvMilliSec	= this->m_lLatencyReceiveMs;
    const int64_t lLatencyRecvMicroSec	= lLatencyRecvMilliSec*1000;

    // ***********************************
    //  Get the request.
    zmq::message_t request;

    bool bSuccessReceiving = false;

    // If failure receiving, re-tries 2 times, with 4000 ms max delay between each (Doubling every time.)
    //
    if (this->m_bIsBlocking)
    {
        bSuccessReceiving = m_pSocket->recv(&request); // Blocking.
    }
    else	// not blocking
    {
        int64_t	lDoubling = lLatencyRecvMicroSec;
        int32_t		nReceiveTries = this->m_nLatencyReceiveNoTries;
        bool	expect_request = true;
        while (expect_request)
        {
            //  Poll socket for a request, with timeout
            zmq::pollitem_t items[] = { { *m_pSocket, 0, ZMQ_POLLIN, 0 } };

            const int32_t nPoll = zmq::poll (&items[0], 1, lDoubling);
            lDoubling *= 2; // 100 ms, then 200 ms, then 400 ms == total of 700 ms per receive. (About 15 per 10 seconds.)

            //  If we got a request, process it
            if (items[0].revents & ZMQ_POLLIN)
            {
                bSuccessReceiving = m_pSocket->recv(&request, ZMQ_NOBLOCK); // <=========== RECEIVE ===============
                OTLog::SleepMilliseconds( 1 );

                if (!bSuccessReceiving)
                {
                    if (false == HandleReceivingError())
                        expect_request = false;
                }
                else
                    break; // (Success -- we're done in this loop.)
            }
            else if (nReceiveTries == 0)
            {
//				OTLog::Error("OTServerSocket::Receive: Tried to receive, based on polling data, but failed even after retries.\n");
                expect_request = false;
                break;
            }
            else if ((-1) == nPoll) // error.
            {
                if (false == HandlePollingError())
                    expect_request = false;
            }

            --nReceiveTries;
        }
    }
    // ***********************************

    if (bSuccessReceiving && (request.size() > 0))
    {
        str_Message.reserve(request.size());
        str_Message.append(static_cast<const char *>(request.data()), request.size());
    }

    return (bSuccessReceiving && (request.size() > 0));
}

