/************************************************************
 *
 *  OTCaller.cpp
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

#include "OTCaller.hpp"

#include "OTCallback.hpp"
#include "OTLog.hpp"

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


OTCaller::~OTCaller()
{
	OTLog::vOutput(0, "OTCaller::~OTCaller: (This should only happen as the application is closing.)\n");

	delCallback();
}


// A display string is set here before the Java dialog is shown, so that the string can be displayed on that dialog.
//
const char * OTCaller::GetDisplay() const
{
	// I'm using the OTPassword class to store the display string, in addition to
	// storing the password itself. (For convenience.)
	//
	return reinterpret_cast<const char *>(m_Display.getPassword_uint8());
}


// A display string is set here before the Java dialog is shown, so that the string can be displayed on that dialog.
//
void OTCaller::SetDisplay(const char * szDisplay, int32_t nLength)
{
	// I'm using the OTPassword class to store the display string, in addition to
	// storing the password itself. (For convenience.)
	//
	m_Display.setPassword_uint8(reinterpret_cast<const uint8_t *>(szDisplay), nLength);
}


// The password will be stored here by the Java dialog, so that the C callback can retrieve it and pass it to OpenSSL
//
bool OTCaller::GetPassword(OTPassword & theOutput) const // Get the password....
{
	OTLog::Output(0, "OTCaller::GetPassword: FYI, returning password after invoking a (probably Java) password dialog.\n");

	theOutput.setPassword_uint8(m_Password.getPassword_uint8(), m_Password.getPasswordSize());

	return true;
}


void OTCaller::ZeroOutPassword()	// Then ZERO IT OUT so copies aren't floating around.
{
	if (m_Password.getPasswordSize() > 0)
		m_Password.zeroMemory();
}


void OTCaller::delCallback()
{
	//	if (NULL != _callback)  // TODO this may be a memory leak.
	//		delete _callback;	// But I know we're currently crashing from deleting same object twice.
	// And since the object comes from Java, who am I to delete it? Let Java clean it up.
	if (isCallbackSet())
		OTLog::Output(0, "OTCaller::delCallback: WARNING: setting existing callback object pointer to NULL. "
					  "(This message doesn't trigger if it was already NULL.)\n");
	//--------------------------------
	_callback = NULL;
}


void OTCaller::setCallback(OTCallback *cb)
{
	OTLog::Output(0, "OTCaller::setCallback: Attempting to set the password OTCallback pointer...\n");

	if (NULL == cb)
	{
		OTLog::Output(0, "OTCaller::setCallback: ERROR: NULL password OTCallback object passed in. (Returning.)\n");
		return;
	}

	delCallback(); // Sets _callback to NULL, but LOGS first, if it was already set.
	// -----------------------------

	_callback = cb;
	OTLog::Output(0, "OTCaller::setCallback: FYI, the password OTCallback pointer was set.\n");
}


bool OTCaller::isCallbackSet() const
{
	return (NULL == _callback) ? false : true;
}


void OTCaller::callOne()
{
	ZeroOutPassword(); // Make sure there isn't some old password still in here.

	if (isCallbackSet())
	{
		OTLog::Output(0, "OTCaller::callOne: FYI, Executing password callback (one)...\n");
		_callback->runOne(this->GetDisplay(), m_Password);
	}
	else
	{
		OTLog::Output(0, "OTCaller::callOne: WARNING: Failed attempt to trigger password callback (one), due to \"it hasn't been set yet.\"\n");
	}
}


void OTCaller::callTwo()
{
	ZeroOutPassword(); // Make sure there isn't some old password still in here.

	if (isCallbackSet())
	{
		OTLog::Output(0, "OTCaller::callTwo: FYI, Executing password callback (two)...\n");
		_callback->runTwo(this->GetDisplay(), m_Password);
	}
	else
	{
		OTLog::Output(0, "OTCaller::callTwo: WARNING: Failed attempt to trigger password callback (two), due to \"it hasn't been set yet.\"\n");
	}
}


/*
 WCHAR szPassword[MAX_PATH];

 // Retrieve the password
 if (GetPasswordFromUser(szPassword, MAX_PATH))

 UsePassword(szPassword); // <===========

 // WINDOWS MEMORY ZEROING CODE:
 SecureZeroMemory(szPassword, sizeof(szPassword));

 */


/*
 SOURCE: https://www.securecoding.cert.org
 TODO security: research all of these items and implement them in OT properly along with all other code scanning and security measures.

 https://www.securecoding.cert.org/confluence/display/cplusplus/MSC06-CPP.+Be+aware+of+compiler+optimization+when+dealing+with+sensitive+data


 Compliant Code Example (Windows)
 This compliant solution uses a SecureZeroMemory() function provided by many versions of the Microsoft Visual Studio compiler.
 The documentation for the SecureZeroMemory() function guarantees that the compiler does not optimize out this call when zeroing memory.

 void getPassword(void) {
  char pwd[64];
  if (retrievePassword(pwd, sizeof(pwd))) {
    // checking of password, secure operations, etc
  }
  SecureZeroMemory(pwd, sizeof(pwd));
}

Compliant Solution (Windows)
The #pragma directives in this compliant solution instruct the compiler to avoid optimizing the enclosed code.
 This #pragma directive is supported on some versions of Microsoft Visual Studio and may be supported on other compilers.
 Check compiler documentation to ensure its availability and its optimization guarantees.

void getPassword(void) {
	char pwd[64];
	if (retrievePassword(pwd, sizeof(pwd))) {
		// checking of password, secure operations, etc
	}
#pragma optimize("", off)
	memset(pwd, 0, sizeof(pwd));
#pragma optimize("", on)
}

Compliant Solution
This compliant solution uses the volatile type qualifier to inform the compiler that the memory should be overwritten
 and that the call to the memset_s() function should not be optimized out. Unfortunately, this compliant solution may
 not be as efficient as possible due to the nature of the volatile type qualifier preventing the compiler from optimizing
 the code at all. Typically, some compilers are smart enough to replace calls to memset() with equivalent assembly instructions
 that are much more efficient than the memset() implementation. Implementing a memset_s() function as shown in the example may
 prevent the compiler from using the optimal assembly instructions and may result in less efficient code. Check compiler
 documentation and the assembly output from the compiler.

// memset_s.c
void *memset_s(void *v, int32_t c, size_t n) {
	volatile uint8_t *p = v;
	while (n--)
		*p++ = c;

	return v;
}

// getPassword.c
extern void *memset_s(void *v, int32_t c, size_t n);

void getPassword(void) {
	char pwd[64];

	if (retrievePassword(pwd, sizeof(pwd))) {
		// checking of password, secure operations, etc
	}
	memset_s(pwd, 0, sizeof(pwd));
}
However, it should be noted that both calling functions and accessing volatile qualified objects can still be optimized out
 (while maintaining strict conformance to the standard), so the above may still not work.
 */
