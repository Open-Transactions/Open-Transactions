/************************************************************
 *
 *  OTPasswordData.cpp
 *
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

#include "stdafx.hpp"

#include "OTPasswordData.hpp"

#include "OTAssert.hpp"
#include "OTString.hpp"


// For SecureZeroMemory
#ifdef _WIN32
#else // not _WIN32

// for mlock and munlock
#include <sys/types.h>
#include <sys/mman.h>
#include <limits.h>

#ifndef PAGESIZE
    #include <unistd.h>
    #define PAGESIZE sysconf(_SC_PAGESIZE)
#endif

// FT: Credit to the Bitcoin team for the mlock / munlock defines.

#define mlock(a,b) \
  mlock(((void *)(((size_t)(a)) & (~((PAGESIZE)-1)))),\
  (((((size_t)(a)) + (b) - 1) | ((PAGESIZE) - 1)) + 1) - (((size_t)(a)) & (~((PAGESIZE) - 1))))
#define munlock(a,b) \
  munlock(((void *)(((size_t)(a)) & (~((PAGESIZE)-1)))),\
  (((((size_t)(a)) + (b) - 1) | ((PAGESIZE) - 1)) + 1) - (((size_t)(a)) & (~((PAGESIZE) - 1))))
#endif


// Instantiate one of these whenever you do an action that may
// require a passphrase. When you call the OpenSSL private key
// using function, just pass in the address to this instance along
// as one of the parameters. That way when the actual password
// callback is activated, you'll get that pointer as the userdata
// parameter to the callback.
// This enables you to easily pass data to the callback about
// which Nym is doing the action, or what string should be displayed
// on the screen, etc. You'll also be able to use the same mechanism
// for determining whether it's a wallet-Nym doing the action, or
// a real Nym. (Thus making it possible to skip any "password caching"
// code that normally happens for real nyms, when it's the wallet nym.)
//
/*

class OTPasswordData
{
private:
    OTPassword *       m_pMasterPW; // Used only when isForCachedKey is true.
    const std::string  m_strDisplay;

public:
    // --------------------------------
    bool            isForCachedKey()   const;
    const char *    GetDisplayString() const;
    // --------------------------------
    OTPasswordData(const char        *   szDisplay, OTPassword * pMasterPW=NULL);
    OTPasswordData(const std::string & str_Display, OTPassword * pMasterPW=NULL);
    OTPasswordData(const OTString    &  strDisplay, OTPassword * pMasterPW=NULL);
    ~OTPasswordData();
};
 */

bool OTPasswordData::isUsingOldSystem() const
{
    return m_bUsingOldSystem;
}


void OTPasswordData::setUsingOldSystem(bool bUsing/*=true*/)
{
    m_bUsingOldSystem = bUsing;
}


bool OTPasswordData::isForNormalNym() const
{
    return (NULL == m_pMasterPW);
}


bool OTPasswordData::isForCachedKey() const
{
    return (NULL != m_pMasterPW);
}


const char * OTPasswordData::GetDisplayString() const
{
    return m_strDisplay.c_str();
}


OTPasswordData::OTPasswordData(const char * szDisplay, OTPassword * pMasterPW/*=NULL*/, _SharedPtr<OTCachedKey> pCachedKey/*=_SharedPtr<OTCachedKey>()*/)
: m_pMasterPW(pMasterPW),
  m_strDisplay(NULL == szDisplay ? "(Sorry, no user data provided.)" : szDisplay),
  m_bUsingOldSystem(false),
  m_pCachedKey(pCachedKey)
{
    // They can both be NULL, or they can both be not NULL.
    // But you can't have one NULL, and the other not.
    OT_ASSERT(     ( (NULL == pMasterPW) && (!pCachedKey) ) || ( (NULL != pMasterPW) && (pCachedKey) )    );
}


OTPasswordData::OTPasswordData(const std::string & str_Display, OTPassword * pMasterPW/*=NULL*/, _SharedPtr<OTCachedKey> pCachedKey/*=_SharedPtr<OTCachedKey>()*/)
: m_pMasterPW(pMasterPW),
  m_strDisplay(str_Display),
  m_bUsingOldSystem(false),
  m_pCachedKey(pCachedKey)
{
    // They can both be NULL, or they can both be not NULL.
    // But you can't have one NULL, and the other not.
    OT_ASSERT(     ( (NULL == pMasterPW) && (!pCachedKey) ) || ( (NULL != pMasterPW) && (pCachedKey) )    );
}


OTPasswordData::OTPasswordData(const OTString & strDisplay, OTPassword * pMasterPW/*=NULL*/, _SharedPtr<OTCachedKey> pCachedKey/*=_SharedPtr<OTCachedKey>()*/)
: m_pMasterPW(pMasterPW),
  m_strDisplay(strDisplay.Get()),
  m_bUsingOldSystem(false),
  m_pCachedKey(pCachedKey)
{
    // They can both be NULL, or they can both be  not NULL.
    // But you can't have one NULL, and the other not.
    OT_ASSERT(     ( (NULL == pMasterPW) && (!pCachedKey) ) || ( (NULL != pMasterPW) && (pCachedKey) )    );
}


OTPasswordData::~OTPasswordData()
{
	m_pMasterPW  = NULL; // not owned
//    m_pCachedKey = NULL; // not owned
}
