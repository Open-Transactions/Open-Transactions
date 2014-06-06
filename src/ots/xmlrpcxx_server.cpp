/************************************************************************************
 *
 *  xmlrpcxx_server.cpp  (The web-services implementation of the Open Transactions server.)
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

#include <stdafx.hpp>

#include <main.hpp>

#include <OTServer.hpp>

#include <OTCachedKey.hpp>
#include <OTCrypto.hpp>
#include <OTDataFolder.hpp>
#include <OTEnvelope.hpp>
#include <OTLog.hpp>
#include <OTMessage.hpp>
#include <OTPaths.hpp>
#include <OTSocket.hpp>

#include <Timer.hpp>

#include <cassert>

// TODO: what about android for all the defaults here? Are there ini files in android? Revisit.
// so far, treating it like unix since it is.
//
// Paths
//
#define SERVER_PATH_DEFAULT	"server_data" //should get programmatically
#define SERVER_CONFIG_KEY	"server" //should get programmatically



#define	SERVER_DEFAULT_LATENCY_SEND_MS				5000
#define	SERVER_DEFAULT_LATENCY_SEND_NO_TRIES		2
#define	SERVER_DEFAULT_LATENCY_RECEIVE_MS			5000
#define	SERVER_DEFAULT_LATENCY_RECEIVE_NO_TRIES     2
#define	SERVER_DEFAULT_LATENCY_DELAY_AFTER			50
#define	SERVER_DEFAULT_IS_BLOCKING					false

bool ProcessMessage_ZMQ(OTServer & theServer, const std::string & str_Message, std::string & str_Reply);

// *********************************************************************************************************
//
//
//             *** SERVER MAIN ***
//
//
// The MAIN function for the server software, which starts up the ZMQ listener, as well
// as well as the Open Transactions library and the OT Server object.
//
// After initialization, this function becomes the "main loop" of OT server.
//
int32_t main(int32_t argc, char* argv[])
{
	if(!OTLog::Init(SERVER_CONFIG_KEY,0)) { assert(false); };  // setup the logger.

	OTLog::vOutput(0, "\n\nWelcome to Open Transactions... Test Server -- version %s\n"
				   "(transport build: OTMessage -> OTEnvelope -> ZMQ )\n\n", OTLog::Version());

	// WINSOCK WINDOWS
	// -----------------------------------------------------------------------
#ifdef OT_ZMQ_2_MODE
#ifdef _WIN32

	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	int32_t err = WSAStartup( wVersionRequested, &wsaData );

	/* Tell the user that we could not find a usable		*/
	/* Winsock DLL.											*/

	OT_ASSERT_MSG((err == 0), "WSAStartup failed!\n");


	/*	Confirm that the WinSock DLL supports 2.2.			*/
	/*	Note that if the DLL supports versions greater		*/
	/*	than 2.2 in addition to 2.2, it will still return	*/
	/*	2.2 in wVersion since that is the version we		*/
	/*	requested.											*/

	bool bWinsock = (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2);

	/* Tell the user that we could not find a usable */
	/* WinSock DLL.                                  */

	if (!bWinsock) WSACleanup();  // do cleanup.
	OT_ASSERT_MSG((!bWinsock), "Could not find a usable version of Winsock.dll\n");

	/* The Winsock DLL is acceptable. Proceed to use it. */
	/* Add network programming using Winsock here */
	/* then call WSACleanup when done using the Winsock dll */
	OTLog::vOutput(0,"The Winsock 2.2 dll was found okay\n");
#endif
#endif





	// ***********************************************************************
    // INITIALIZATION and CLEANUP (for the OT library, and for this server application.)
    //
    class __ot_server_
    {
        OTServer * m_pServer;
    public:
        OTServer * GetServer() { return m_pServer; }
        // -----------------------------------
        __ot_server_() : m_pServer(NULL) // INIT
        {
            // -----------------------------------------------------------------------

            // -----------------------------------------------------------------------
            // OTLog class exists on both client and server sides.
            // #define OT_NO_SIGNAL_HANDLING if you want to turn off OT's signal handling.
            //
#if defined(OT_SIGNAL_HANDLING)
            OTLog::SetupSignalHandler(); // This is optional! (I, of course, am using it in this test app...)
#endif
            // -----------------------------------------------------------------------
            // I instantiate this here (instead of globally) so that I am assured that any globals and other
            // setup is already done before we instantiate the server object itself.
            //
            OT_ASSERT_MSG(NULL == m_pServer, "server main(): ASSERT: NULL == m_pServer.");
            m_pServer = new OTServer;
            //
            // (This .cpp file you are currently reading is a wrapper for OTServer,
            // which adds the transport layer.)
            //
            OT_ASSERT_MSG(NULL != m_pServer, "server main(): ASSERT: Unable to instantiate OT server.\n");


			//
			// OT Server Path:
			//
			{
				bool bSetupPathsSuccess = false;
				if(!OTDataFolder::Init(SERVER_CONFIG_KEY)) { OT_FAIL; }
				else
					bSetupPathsSuccess = true;

				OT_ASSERT_MSG(bSetupPathsSuccess, "main(): Assert failed: Failed to set OT Path");
			}

            // -----------------------------------------------------------------------

            OTCrypto::It()->Init();  // <========== (OpenSSL gets initialized here.)

        }
        // ****************************************
        //
        ~__ot_server_()  // CLEANUP
        {
            OTLog::vOutput(0, "\n\n OT version %s, shutting down and cleaning up.\n",
                           OTLog::Version());

            // ------------------------------
            if (NULL != m_pServer)
                delete m_pServer;
            m_pServer = NULL;
            // ------------------------------
            OTCachedKey::Cleanup();
            // ------------------------------
            // We clean these up in reverse order from the Init function, which just seems
            // like the best default, in absence of any brighter ideas.
            //
            OTCrypto::It()->Cleanup();  // <======= (OpenSSL gets cleaned up here.)

            // -------------------------
            // (This is at the bottom, since we do the cleanup in the
            // reverse order from initialization.)
#ifdef _WIN32
            WSACleanup();
#endif
        }
    };
	// ***********************************************************************
    //
    // INSTANTIATE and INITIALIZE...
    //
    // (Cleanup happens automatically when this object goes out of scope.)
    //
    __ot_server_  the_server_obj;
    OTServer * pServer = the_server_obj.GetServer();
    OT_ASSERT(NULL != pServer);
    // -----------------------------------------------------------------------
//	OTString strCAFile, strDHFile, strKeyFile;  //, strSSLPassword;
//	strCAFile. Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), CA_FILE);
//	strDHFile. Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), DH_FILE);
//	strKeyFile.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), KEY_FILE);
	// -----------------------------------------------------------------------
    //
    // UPDATE: This was moved to OTLog::OT_Init(), which is called above, by the
    // nested cleanup class.
    //
	// Initialize SSL -- This MUST occur before any Private Keys are loaded!
//	SSL_library_init();
//	SSL_load_error_strings();

	// -----------------------------------------------------------------------
	// OTServer::Init loads up server's nym so it can decrypt messages sent in
    // envelopes. It also does various other initialization work.
	//
	// (Envelopes prove that ONLY someone who actually had the server contract,
	//  and had loaded it into his wallet, could ever connect to the server or
	//  communicate with it. And if that person is following the contract, there
	//  is only one server he can connect to, and one key he can use to talk to it.)
	//
	OTLog::vOutput(0,
				   "\nNow loading the server nym, which will also ask you for a password, to unlock\n"
				   "its private key.\n");

	pServer->Init(); // Keys, etc are loaded here. ===> Assumes main path is set! <===

	// -----------------------------------------------------------------------
	// We're going to listen on the same port that is listed in our server contract.
	//
	//
	OTString	strHostname;	// The hostname of this server, according to its own contract.
	int32_t			nPort=0;		// The port of this server, according to its own contract.

    const bool bConnectInfo = pServer->GetConnectInfo(strHostname, nPort);

	OT_ASSERT_MSG(bConnectInfo, "server main: Unable to find my own connect info (which SHOULD be in my server contract, BTW.) Perhaps you failed trying to open that contract? Have you tried the test password? (\"test\")\n");

	const int32_t   nServerPort = nPort;

	// -----------------------------------------------------------------------
    // OT CRON
    //
    // A heartbeat for recurring transactions, such as markets, payment plans,
    // and smart contracts.

	pServer->ActivateCron();

    // NOTE: Currently we trigger OT Cron's processing internally, but there's no reason why, in the
    // future, we can't make an actual cron job that triggers a script, that fires a message
    // to OT, causing OT to process its Cron (even if we were single-threaded we could do this...)
    //
    // Have to put some thought into it...
    //
    // Wouldn't require much security, since OT can still be smart enough not to process cron any
    // more often than X minutes, no matter HOW many times the ProcessCron script fires.
    // Thing is, though, that with this setup, we can't really guarantee that cron will EVER be
    // triggered -- whereas the way OT is now, at least we know it WILL fire every X seconds.
    //

	// --------------------------------------
    //
    // NETWORK
    //
	// Prepare our context and listening socket...

#ifdef OT_ZMQ_2_MODE
    OTSocket *  pSocket = new OTSocket_ZMQ_2();
#endif

#ifdef OT_ZMQ_4_MODE
    OTSocket *  pSocket = new OTSocket_ZMQ_4();
#endif


    if (!OTDataFolder::IsInitialized()) { OT_FAIL; };

    {
        OTString strConfigFolderPath = "";
        if (!OTDataFolder::GetConfigFilePath(strConfigFolderPath)) { OT_FAIL; };
        OTSettings * pSettings(new OTSettings(strConfigFolderPath));

        pSettings->Reset();
        if (!pSettings->Load()) { OT_FAIL; };
        {
            const OTSocket::Defaults socketDefaults(
                SERVER_DEFAULT_LATENCY_SEND_MS,
                SERVER_DEFAULT_LATENCY_SEND_NO_TRIES,
                SERVER_DEFAULT_LATENCY_RECEIVE_MS,
                SERVER_DEFAULT_LATENCY_RECEIVE_NO_TRIES,
                SERVER_DEFAULT_LATENCY_DELAY_AFTER,
                SERVER_DEFAULT_IS_BLOCKING
                );


            if (!pSocket->Init(socketDefaults, pSettings)) { OT_FAIL; };
        }

		if (!pSettings->Save()) { OT_FAIL; };
		pSettings->Reset();

		if (NULL != pSettings) delete pSettings; pSettings = NULL;
	}

    if (!pSocket->NewContext())		{ OT_FAIL; };

	{
		if(0 == nServerPort)  { OT_FAIL; };
		OTString strBindPath; strBindPath.Format("%s%d", "tcp://*:", nServerPort);

        if (!pSocket->Listen(strBindPath))  { OT_FAIL; };
	}

    // ******************************************************************************************
    //
    //      *** MAIN LOOP ***
    //
	for (;;)
	{
        // =-=-=- HEARTBEAT -=-=-=
		//
		// The Server now processes certain things on a regular basis.
		// ProcessCron is what gives it the opportunity to do that.
		// All of the Cron Items (including market trades, payment plans, smart contracts...)
		// they all have their hooks here...
		//
		pServer->ProcessCron();  // Internally this is smart enough to know how often to actually activate itself.
                                   // Most often it just returns doing nothing (waiting for its timer.)
		// -----------------------------------------------------------------------
		// Wait for client http requests (and process replies out to them.)
		// ----------------------------------------------------------------------
		// Number of requests to process per heartbeat: OTServer::GetHeartbeatNoRequests()
		//
		// Loop: process up to 10 client requests, then sleep for 1/10th second.
		// That's a total of 100 requests per second. Can the computers handle it?
		// Is it too much or too little? Todo: load testing.
		//
		// Then: check for shutdown flag.
		//
		// Then: go back to the top ("do") and repeat the loop.... process cron,
		// process 10 client requests, sleep, check for shutdown, etc.
		//
		//

		Timer t;	// start timer
		t.start();
		const double tick1 = t.getElapsedTimeInMilliSec();
		// -----------------------------------------------------
		//
        // PROCESS X NUMBER OF REQUESTS (THIS PULSE.)
        //
        // Theoretically the "number of requests" that we process EACH PULSE.
        // (The timing code here is still pretty new, need to do some load testing.)
        //
		for (int32_t i = 0; i < /*10*/OTServer::GetHeartbeatNoRequests(); i++)
		{
			OTString str_Message;
			
			// With 100ms heartbeat, receive will try 100 ms, then 200 ms, then 400 ms, total of 700.
			// That's about 15 Receive() calls every 10 seconds. Therefore if I want the ProcessCron()
			// to trigger every 10 seconds, I need to set the cron interval to roll over every 15 heartbeats.
			// Therefore I will be using a real Timer for Cron, instead of the damn intervals.
			//
            bool bReceived = pSocket->Receive(str_Message);
			
			if  (bReceived)
			{
                std::string str_Reply; // Output.
				
				if (str_Message.GetLength() <= 0)
				{
					OTLog::Error("server main: Received a message, but of 0 length or less. Weird. (Skipping it.)\n");
				}
				else // ------------------------------------
				{
                    // true  == YES, DISCONNECT m_pSocket, something must have gone wrong.
                    // false ==  NO, do NOT disconnect m_pSocket, everything went wonderfully!
                    //
                    const std::string strMsg(str_Message.Get());
                    const bool bShouldDisconnect = ProcessMessage_ZMQ(*pServer, strMsg, str_Reply); // <================== PROCESS the message!
					// --------------------------------------------------

					if ((str_Reply.length() <= 0) || bShouldDisconnect)
					{
						OTLog::vOutput(0, "server main: ERROR: Unfortunately, not every client request is "
                                       "legible or worthy of a server response. :-)  "
                                       "Msg:\n\n%s\n\n", strMsg.c_str());
                        
                        pSocket->Listen();
					}
					else
					{
                        bool bSuccessSending = pSocket->Send(str_Reply.c_str()); // <===== SEND THE REPLY
						
						if (false == bSuccessSending)
							OTLog::vError("server main: Socket ERROR: failed while trying to send reply "
                                          "back to client! \n\n MESSAGE:\n%s\n\nREPLY:\n%s\n\n", 
                                          strMsg.c_str(), str_Reply.c_str());
						// --------------------------------------------------
					}
				}
			}
		} //  for

		// -----------------------------------------------------------------------
		//
        // IF the time we had available wasn't all used up -- if some of it is still
        // available, then SLEEP until we reach the NEXT PULSE. (In practice, we will
        // probably use TOO MUCH time, not too little--but then again OT isn't ALWAYS
        // processing a message. There could be plenty of dead time in between...)
        //
		const	double tick2	= t.getElapsedTimeInMilliSec();
		const	int64_t elapsed	= static_cast<int64_t>(tick2 - tick1);
		int64_t	lSleepMS		= 0;

		if (elapsed < /*100*/OTServer::GetHeartbeatMsBetweenBeats())
		{
			lSleepMS = OTServer::GetHeartbeatMsBetweenBeats() - elapsed;

			// Now go to sleep.
			// (The main loop processes ten times per second, currently.)
			OTLog::SleepMilliseconds(lSleepMS); // 100 ms == (1 second / 10)
		}

		// -----------------------------------------------------------------------
		// ARTIFICIAL LIMIT:
		// 10 requests per heartbeat, 10 rounds per second == 100 requests per second.
		//
		// *** ONE HUNDRED CLIENT MESSAGES PER SECOND is the same as:
		//
		//     6000 PER MINUTE == 360,000 PER HOUR == 8,640,000 PER DAY***
		//
		// Speeding it up is just a matter of adjusting the above numbers, and LOAD TESTING,
        // to see if OT can handle it. (Not counting optimization of course.)
		//
		// -----------------------------------------------------------------------

		if (pServer->IsFlaggedForShutdown())
		{
			OTLog::Output(0, "main: OT Server is shutting down gracefully....\n");
			break;
		}

    }
    if (NULL != pSocket) delete pSocket;

	// ------------------------------------
	return 0;
}


// true  == YES, DISCONNECT m_pSocket, something must have gone wrong.
// false ==  NO, do NOT disconnect m_pSocket, everything went wonderfully!
//
bool ProcessMessage_ZMQ(OTServer & theServer, const std::string & str_Message, std::string & str_Reply)
{
	if (str_Message.size() < 1)
		return false;

	// --------------------

	// return value.
	std::string resultString = ""; // Whatever we put in this string is what will get returned.

	// First we grab the client's message
	OTASCIIArmor ascMessage;
	ascMessage.MemSet(str_Message.data(), static_cast<uint32_t> (str_Message.size()));


    bool bReturnVal = false; // "false" == no, do NOT disconnect. No errors. ("True" means YES, DISCONNECT!)

	OTMessage theMsg, theReply; // we'll need these in a sec...

//	OTEnvelope theEnvelope(ascMessage);
	OTEnvelope theEnvelope;

	if (false == theEnvelope.SetAsciiArmoredData(ascMessage))
    {
        OTLog::vError("%s: Error retrieving envelope.\n", __FUNCTION__);
        bReturnVal = true; // disconnect the socket!
    }
	else
	{	// Now the base64 is decoded and the envelope is in binary form again.
		OTLog::vOutput(2, "%s: Successfully retrieved envelope from ZMQ message...\n", __FUNCTION__);

		OTString strEnvelopeContents;

//		OTString strPubkeyPath("TESTPUBKEY.txt");
//		theServer.GetServerNym().SavePublicKey(strPubkeyPath);

		// Decrypt the Envelope.
		if (false == theEnvelope.Open(theServer.GetServerNym(), strEnvelopeContents)) // now strEnvelopeContents contains the decoded message.
        {
            OTLog::vError("%s: Unable to open envelope.\n", __FUNCTION__);
            bReturnVal = true; // disconnect the socket!
        }
		else
		{
			// All decrypted--now let's load the results into an OTMessage.
			// No need to call theMsg.ParseRawFile() after, since
			// LoadContractFromString handles it.
			//
			if (strEnvelopeContents.Exists() && theMsg.LoadContractFromString(strEnvelopeContents))
			{
				theReply.m_strCommand.Format("@%s", theMsg.m_strCommand.Get());
				theReply.m_strNymID		= theMsg.m_strNymID;	// UserID
				theReply.m_strServerID	= theMsg.m_strServerID;	// ServerID, a hash of the server contract.
				theReply.m_bSuccess		= false;				// The default reply. In fact this is probably superfluous.

				// In case you want to see all the incoming messages...
//				OTLog::vOutput(0, "%s\n\n", strEnvelopeContents.Get());

				// By constructing this without a socket, I put it in ZMQ mode, instead of tcp/ssl.
				OTClientConnection theClient(theServer);

                OTPseudonym theNym(theMsg.m_strNymID);

                const bool bProcessedUserCmd = theServer.ProcessUserCommand(theMsg, theReply, &theClient, &theNym);

				// By optionally passing in &theClient, the client Nym's public key will be
				// set on it whenever verification is complete. (So for the reply, I'll
				// have the key and thus I'll be able to encrypt reply to the recipient.)
				if (false == bProcessedUserCmd)
				{
                    const OTString s1(theMsg);

					OTLog::vOutput(0, "%s: Unable to process user command: %s\n ********** "
                        "REQUEST:\n\n%s\n\n", __FUNCTION__, theMsg.m_strCommand.Get(), s1.Get());


					// NOTE: normally you would even HAVE a true or false if we're in this block. ProcessUserCommand()
					// is what tries to process a command and then sets false if/when it fails. Until that point, you
					// wouldn't get any server reply.  I'm now changing this slightly, so you still get a reply (defaulted
					// to success==false.) That way if a client needs to re-sync his request number, he will get the false
					// and therefore know to resync the # as his next move, vs being stuck with no server reply (and thus
					// stuck with a bad socket.)
					// We sign the reply here, but not in the else block, since it's already signed in cases where
					// ProcessUserCommand() is a success, by the time that call returns.

					theReply.m_bSuccess = false; // Since the process call definitely failed, I'm making sure this here is definitely set to false (even though it probably was already.)
					theReply.SignContract(theServer.GetServerNym());
					theReply.SaveContract();

                    const OTString s2(theReply);

					OTLog::vOutput(0, " ********** RESPONSE:\n\n%s\n\n", s2.Get());

				}
				else	// At this point the reply is ready to go, and theClient has the public key of the recipient...
                    OTLog::vOutput(1, "%s: Successfully processed user command: %s.\n", __FUNCTION__, theMsg.m_strCommand.Get());

                // -------------------------------------------------------------------------------------

                // IF ProcessUserCommand returned true, THEN we process the message for the recipient.
                // ELSE IF ProcessUserCommand returned false, YET the PubKey DOES exist, THEN in this case also, we process the message for the recipient.
                //
                if (bProcessedUserCmd || theNym.Server_PubKeyExists()) // if success + Nym's pub key exists here on server.
                {
                    // The transaction is now processed (or not), and the server's reply message is in theReply.
                    // Let's seal it up to the recipient's nym (in an envelope) and send back to the user...
                    //
                    OTEnvelope theRecipientEnvelope;

                    const bool bSealed = theClient.SealMessageForRecipient(theReply, theRecipientEnvelope);

                    if (false == bSealed)
                    {
                        OTLog::vOutput(0, "%s: Unable to seal envelope. (No reply will be sent.)\n", __FUNCTION__);
                        bReturnVal = true; // disconnect the socket!
                    }
                    else
                    {
//                      OTPayload theReplyPayload;
//                      theReplyPayload.SetEnvelope(theRecipientEnvelope);
//                      resultString = ascReply.Get();
//                      resultString.assign(theReplyPayload.GetPayloadPointer(), theReplyPayload.GetPayloadSize());

                        OTASCIIArmor ascReply;
                        if (theRecipientEnvelope.GetAsciiArmoredData(ascReply))
                        {
                            // -----------------------------------------
                            OTString strOutput;
                            const bool bSuccess = ascReply.Exists() &&
                                                    ascReply.WriteArmoredString(strOutput,
                                                                                "ENVELOPE"); // There's no default, to force you to enter the right string.
                            // -----------------------------------------
                            if (bSuccess && strOutput.Exists())
                                resultString.assign(strOutput.Get(), strOutput.GetLength()); // <============== REPLY ENVELOPE...
                            else
                            {
                                OTLog::vOutput(0, "%s: Unable to WriteArmoredString from OTASCIIArmor object into "
                                    "OTString object. (No reply envelope will be sent.)\n", __FUNCTION__);
                                bReturnVal = true; // disconnect the socket!
                            }
                        }
                        else
                        {
                            OTLog::vOutput(0, "%s: Unable to GetAsciiArmoredData from sealed envelope into "
                                "OTASCIIArmor object. (No reply envelope will be sent.)\n", __FUNCTION__);
                            bReturnVal = true; // disconnect the socket!
                        }
                    }
                }
                // -------------------------------------------------------------------------------------
                // ELSE we send the message in the CLEAR. (As an armored message, instead of as an armored envelope.)
                else
                {
                    const OTString  strReply(theReply);

                    if (strReply.Exists())
                    {
                        OTASCIIArmor ascReply(strReply);
                        // ------------------------------------
                        OTString strOutput;
                        const bool bSuccess = ascReply.Exists() &&
                                                ascReply.WriteArmoredString(strOutput,
                                                                            "MESSAGE"); // There's no default, to force you to enter the right string.
                        // -----------------------------------------
                        if (bSuccess && strOutput.Exists())
                            resultString.assign(strOutput.Get(), strOutput.GetLength()); // <============== REPLY MESSAGE...
                        else
                        {
                            OTLog::vOutput(0, "%s: Unable to WriteArmoredString from OTASCIIArmor object into "
                                "OTString object. (No reply message will be sent.)\n", __FUNCTION__);
                            bReturnVal = true; // disconnect the socket!
                        }
                    }
                    else
                    {
                        OTLog::vOutput(0, "%s: Failed trying to grab theReply in OTString form. "
                            "(No reply message will be sent.)\n", __FUNCTION__);
                        bReturnVal = true; // disconnect the socket!
                    }
                }
                // -------------------------------------------------------------------------------------
			}
			else
            {
				OTLog::vError("%s: Error loading message from envelope contents:\n\n%s\n\n",
                    __FUNCTION__, strEnvelopeContents.Get());
                bReturnVal = true; // disconnect the socket!
            }
		}
	}
	// ----------------------------------------------------------------------

	str_Reply = resultString;

    return bReturnVal;

} // ProcessMessage_ZMQ















































