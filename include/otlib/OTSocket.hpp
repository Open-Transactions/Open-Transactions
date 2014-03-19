/*************************************************************
 *
 * OTSocket.hpp
 *
 */

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA1

 * OPEN TRANSACTIONS
 *
 * Financial Cryptography and Digital Cash
 * Library, Protocol, API, Server, CLI, GUI
 *
 * -- Anonymous Numbered Accounts.
 * -- Untraceable Digital Cash.
 * -- Triple-Signed Receipts.
 * -- Cheques, Vouchers, Transfers, Inboxes.
 * -- Basket Currencies, Markets, Payment Plans.
 * -- Signed, XML, Ricardian-style Contracts.
 * -- Scripted smart contracts.
 *
 * Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
 *
 * EMAIL:
 * FellowTraveler@rayservers.net
 *
 * BITCOIN: 1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 * KEY FINGERPRINT (PGP Key in license file):
 * 9DD5 90EB 9292 4B48 0484 7910 0308 00ED F951 BB8E
 *
 * OFFICIAL PROJECT WIKI(s):
 * https://github.com/FellowTraveler/Moneychanger
 * https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 * WEBSITE:
 * http://www.OpenTransactions.org/
 *
 * Components and licensing:
 * -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 * -- otlib.........A class library.......LICENSE:...LAGPLv3
 * -- otapi.........A client API..........LICENSE:...LAGPLv3
 * -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
 * -- otserver......Server Application....LICENSE:....AGPLv3
 * Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 * All of the above OT components were designed and written by
 * Fellow Traveler, with the exception of Moneychanger, which
 * was contracted out to Vicky C (bitcointrader4@gmail.com).
 * The open-source community has since actively contributed.
 *
 * -----------------------------------------------------
 *
 * LICENSE:
 * This program is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Affero
 * General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 * section 7: (This paragraph applies only to the LAGPLv3
 * components listed above.) If you modify this Program, or
 * any covered work, by linking or combining it with other
 * code, such other code is not for that reason alone subject
 * to any of the requirements of the GNU Affero GPL version 3.
 * (==> This means if you are only using the OT API, then you
 * don't have to open-source your code--only your changes to
 * Open-Transactions itself must be open source. Similar to
 * LGPLv3, except it applies to software-as-a-service, not
 * just to distributing binaries.)
 *
 * Extra WAIVER for OpenSSL, Lucre, and all other libraries
 * used by Open Transactions: This program is released under
 * the AGPL with the additional exemption that compiling,
 * linking, and/or using OpenSSL is allowed. The same is true
 * for any other open source libraries included in this
 * project: complete waiver from the AGPL is hereby granted to
 * compile, link, and/or use them with Open-Transactions,
 * according to their own terms, as long as the rest of the
 * Open-Transactions terms remain respected, with regard to
 * the Open-Transactions code itself.
 *
 * Lucre License:
 * This code is also "dual-license", meaning that Ben Lau-
 * rie's license must also be included and respected, since
 * the code for Lucre is also included with Open Transactions.
 * See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
 * The Laurie requirements are light, but if there is any
 * problem with his license, simply remove the Lucre code.
 * Although there are no other blind token algorithms in Open
 * Transactions (yet. credlib is coming), the other functions
 * will continue to operate.
 * See Lucre on Github: https://github.com/benlaurie/lucre
 * -----------------------------------------------------
 * You should have received a copy of the GNU Affero General
 * Public License along with this program. If not, see:
 * http://www.gnu.org/licenses/
 *
 * If you would like to use this software outside of the free
 * software license, please contact FellowTraveler.
 * (Unfortunately many will run anonymously and untraceably,
 * so who could really stop them?)
 *
 * DISCLAIMER:
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Affero General Public License for
 * more details.

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

#ifndef __OTSOCKET_HPP__
#define __OTSOCKET_HPP__

#include "ExportWrapper.h"
#include "WinsockWrapper.h"
#include "TR1_Wrapper.hpp"

#include "OTString.hpp"
#include "OTASCIIArmor.hpp"
#include "OTSettings.hpp"

#include "tinythread.hpp"


#if defined(OPENTXS_HAVE_ZMQ_HPP) || defined(_WIN32)
#ifndef OT_ZMQ_2_MODE
#define OT_ZMQ_2_MODE
#endif
#endif





// --------------------------------------------------------------------
// Server and Client Side.
//
class OTSocket
{
public:
    class Defaults
    {
    public:
        EXPORT Defaults(
        long lLatencySendMs,
        int nLatencySendNoTries,
        long lLatencyReceiveMs,
        int nLatencyReceiveNoTries,
        long lLatencyDelayAfter,
        bool bIsBlocking);

        const long m_lLatencySendMs;
        const int  m_nLatencySendNoTries;
        const long m_lLatencyReceiveMs;
        const int  m_nLatencyReceiveNoTries;
        const long m_lLatencyDelayAfter;
        const bool m_bIsBlocking;
    };

private:
    class Mutex
    {
    private:
        tthread::mutex * m_pMutex;

    public:
        EXPORT Mutex();
        EXPORT ~Mutex();

        EXPORT tthread::mutex * Get();
    };

    Mutex m_Mutex;

protected:
    OTSocket();

    long m_lLatencySendMs;
    int  m_nLatencySendNoTries;
    long m_lLatencyReceiveMs;
    int  m_nLatencyReceiveNoTries;
    long m_lLatencyDelayAfter;
    bool m_bIsBlocking;

    bool m_bInitialized;
    bool m_HasContext;
    bool m_bConnected;
    bool m_bListening;

    OTString m_strConnectPath;
    OTString m_strBindingPath;

    OTASCIIArmor m_ascLastMsgSent;

    virtual bool HandlePollingError() = 0;
    virtual bool HandleSendingError() = 0;
    virtual bool HandleReceivingError() = 0;

public:
    EXPORT tthread::mutex * GetMutex();

    EXPORT bool Init(const Defaults & defaults);
    EXPORT bool Init(const Defaults & defaults, OTSettings * pSettings);

    EXPORT bool IsInitialized() const;
    EXPORT bool HasContext() const;
    EXPORT bool IsConnected() const;
    EXPORT bool IsListening() const;

    EXPORT const OTString & GetConnectPath() const;
    EXPORT const OTString & GetBindingPath() const;

    EXPORT virtual bool NewContext() = 0;
    EXPORT virtual bool RemakeSocket(const bool bNewContext = false) = 0;

    EXPORT virtual bool Connect() = 0;
    EXPORT virtual bool Listen() = 0;

    EXPORT virtual bool Connect(const OTString & strConnectPath) = 0;
    EXPORT virtual bool Listen(const OTString & strBindingPath) = 0;

    EXPORT virtual bool Send(const OTASCIIArmor & ascEnvelope) = 0;
    EXPORT virtual bool Send(const OTASCIIArmor & ascEnvelope, const OTString & strConnectPath) = 0;
    EXPORT virtual bool Receive(OTString & strServerReply) = 0;
};


#ifdef OT_ZMQ_2_MODE

class OTSocket_ZMQ_2 : public OTSocket
{
private:
    class ZMQ2; // defined in C++ file.
    ZMQ2 * const m_pzmq;

public:
    EXPORT OTSocket_ZMQ_2();
    EXPORT ~OTSocket_ZMQ_2();

private:
    bool CloseSocket(const bool bNewContext = false);
    bool NewSocket(const bool bIsRequest);

public:
    EXPORT bool NewContext();
    EXPORT bool RemakeSocket(const bool bNewContext = false);

    EXPORT bool Connect();
    EXPORT bool Listen();

    EXPORT bool Connect(const OTString & strConnectPath);
    EXPORT bool Listen(const OTString & strBindingPath);

    EXPORT bool Send(const OTASCIIArmor & ascEnvelope);
    EXPORT bool Send(const OTASCIIArmor & ascEnvelope, const OTString & strConnectPath);
    EXPORT bool Receive(OTString & strServerReply);

private:
    bool HandlePollingError();
    bool HandleSendingError();
    bool HandleReceivingError();

};

#endif // OT_ZMQ_2_MODE





#endif // __OTSOCKET_HPP__ 






















