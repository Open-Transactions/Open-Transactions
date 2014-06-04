/************************************************************
 *
 *  OTCaller.hpp
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

#ifndef __OT_CALLER_HPP__
#define __OT_CALLER_HPP__

#include "OTPassword.hpp"

class OTPassword;
class OTCallback;


/*
 To use:

 OTPassword thePass;
 (Or...)
 OTPassword thePass(strPassword, strPassword.length());

 const char * szPassword	= thePass.getPassword();
 const int32_t    nPassLength	= thePass.getPasswordSize();

 If the instance of OTPassword is not going to be destroyed immediately
 after the password is used, then make sure to call zeroMemory() after
 using the password. (Otherwise the destructor will handle this anyway.)

 (The primary purpose of this class is that it zeros its memory out when
 it is destructed.)

 This class gives me a safe way to hand-off a password, and off-load the
 handling risk to the user.  This class will be included as part of the
 OT-API SWIG interface so that it's available inside other languages.

 */

#define OT_PW_DISPLAY  "Enter master passphrase for wallet."

#define OTPASSWORD_BLOCKSIZE    128		// (128 bytes max length for a password.)
#define OTPASSWORD_MEMSIZE		129		// +1 for null terminator.

// UPDATE: Increasing the size here, so we can accommodate private keys (in addition to passphrases.)
//
#define OT_LARGE_BLOCKSIZE	32767		// (32767 bytes max length for a password.)
#define OT_LARGE_MEMSIZE	32768		// +1 for null terminator.

// Default is the smaller size.
#define OT_DEFAULT_BLOCKSIZE  128
#define OT_DEFAULT_MEMSIZE    129

// https://github.com/lorf/keepassx/blob/master/src/lib/SecString.cpp

// Done:  Although we have good memory ZEROING code (for destruction)
// we don't have code yet that will keep the contents SECURE while they
// are in memory. For example, that will prevent them from being paged
// to the hard drive during swapping. Such code would make OTPassword much
// more appropriate for use cases such as storing passphrases and private
// keys, and would even allow timeout procedures...
//
// NOTE: For Windows, use VirtualLock instead of mlock.
//

/*
 #include <sys/mman.h>

 void *locking_alloc(size_t numbytes)
 {
    static short have_warned = 0;

    void *mem = malloc(numbytes);

    if (mlock(mem, numbytes) && !have_warned)
    {

        // We probably do not have permission.
        // Sometimes, it might not be possible to lock enough memory.

        fprintf(stderr, "Warning: Using insecure memory!\n");

        have_warned = 1;

    }

    return mem;
 }

The mlock() call generally locks more memory than you want. Locking is done on a per-page basis. All of the pages the memory spans will be locked in RAM, and will not be swapped out under any circumstances, until the process unlocks something in the same page by using mlock().

There are some potentially negative consequences here. First, If your process locks two buffers that happen to live on the same page, then unlocking either one will unlock the entire page, causing both buffers to unlock. Second, when locking lots of data, it is easy to lock more pages than necessary (the operating system doesn't move data around once it has been allocated), which can slow down machine performance significantly.

Unlocking a chunk of memory looks exactly the same as locking it, except that you call munlock():
        munlock(mem, numbytes);


 // TODO: Work in some usage of CryptProtectMemory and CryptUnprotectMemory (Windows only)
 // with sample code below.  Also should make some kind of UNIX version.


#ifndef _WINDOWS_
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif
#include <cstdio>
#include <Wincrypt.h>

#define SSN_STR_LEN 12  // includes null

void main()
{
    HRESULT hr = S_OK;
    LPWSTR pSensitiveText = NULL;
    DWORD cbSensitiveText = 0;
    DWORD cbPlainText = SSN_STR_LEN*sizeof(WCHAR);
    DWORD dwMod = 0;

    //  Memory to encrypt must be a multiple of CRYPTPROTECTMEMORY_BLOCK_SIZE.
    if (dwMod = cbPlainText % CRYPTPROTECTMEMORY_BLOCK_SIZE)
        cbSensitiveText = cbPlainText +
		(CRYPTPROTECTMEMORY_BLOCK_SIZE - dwMod);
    else
        cbSensitiveText = cbPlainText;

    pSensitiveText = (LPWSTR)LocalAlloc(LPTR, cbSensitiveText);
    if (NULL == pSensitiveText)
    {
        wprintf(L"Memory allocation failed.\n");
        return E_OUTOFMEMORY;
    }

    //  Place sensitive string to encrypt in pSensitiveText.

    if (!CryptProtectMemory(pSensitiveText, cbSensitiveText,
		CRYPTPROTECTMEMORY_SAME_PROCESS))
    {
        wprintf(L"CryptProtectMemory failed: %d\n", GetLastError());
        SecureZeroMemory(pSensitiveText, cbSensitiveText);
        LocalFree(pSensitiveText);
        pSensitiveText = NULL;
        return E_FAIL;
    }

    //  Call CryptUnprotectMemory to decrypt and use the memory.

    SecureZeroMemory(pSensitiveText, cbSensitiveText);
    LocalFree(pSensitiveText);
    pSensitiveText = NULL;

    return hr;
}




#ifndef _WINDOWS_
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif
#include <cstdio>
#include <Wincrypt.h>
#include <strsafe.h>
#pragma comment(lib, "crypt32.lib")

void main()
{
    LPWSTR pEncryptedText;  // contains the encrypted text
    DWORD cbEncryptedText;  // number of bytes to which
	                        // pEncryptedText points

    if (CryptUnprotectMemory(pEncryptedText, cbEncryptedText,
		CRYPTPROTECTMEMORY_SAME_PROCESS))
    {
        // Use the decrypted string.
    }
    else
    {
        wprintf(L"CryptUnprotectMemory failed: %d\n",
			GetLastError());
    }

    // Clear and free memory after using
    // the decrypted string or if an error occurs.
    SecureZeroMemory(pEncryptedText, cbEncryptedText);
    LocalFree(pEncryptedText);
    pEncryptedText = NULL;
}


 */

//#undef OTPASSWORD_BLOCKSIZE
//#undef OTPASSWORD_MEMSIZE
//
//#undef OT_LARGE_BLOCKSIZE
//#undef OT_LARGE_MEMSIZE
//
//#undef OT_DEFAULT_BLOCKSIZE
//#undef OT_DEFAULT_MEMSIZE


class OTCaller
{
protected:
	OTPassword	m_Password;	// The password will be stored here by the Java dialog, so that the C callback can retrieve it and pass it to OpenSSL
	OTPassword	m_Display;	// A display string is set here before the Java dialog is shown. (OTPassword used here only for convenience.)

	OTCallback * _callback;

public:
	OTCaller() : _callback(NULL) { }
EXPORT	~OTCaller();

EXPORT	bool	GetPassword(OTPassword & theOutput) const;	// Grab the password when it is needed.
EXPORT	void	ZeroOutPassword();	// Then ZERO IT OUT so copies aren't floating around...

EXPORT	const char * GetDisplay() const;
EXPORT	void SetDisplay(const char * szDisplay, int32_t nLength);

EXPORT	void delCallback();
EXPORT	void setCallback(OTCallback *cb);
EXPORT	bool isCallbackSet() const;

EXPORT	void callOne(); // Asks for password once. (For authentication when using the Nym's private key.)
EXPORT	void callTwo(); // Asks for password twice. (For confirmation during nym creation and password change.)
};


/*
 HOW TO PREVENT MEMORY FROM GOING INTO CORE DUMPS

#include <sys/time.h>

#include <sys/resource.h>

#include <unistd.h>



int32_t  main(int32_t argc, char **argv)

 {

  struct rlimit rlim;



  getrlimit(RLIMIT_CORE, &rlim);

  rlim.rlim_max = rlim.rlim_cur = 0;

  if(setrlimit(RLIMIT_CORE, &rlim)) {

    exit(-1);

  }

  ...

  return 0;

}



 http://www.drdobbs.com/cpp/184401646




 MORE CODE FOR MEMLOCK:

 namespace Botan
 {

    bool has_mlock();

    bool lock_mem(void* addr, size_t length);

    void unlock_mem(void* addr, size_t length);
 }


//
// Memory Locking Functions
// (C) 1999-2007 Jack Lloyd
//
// Distributed under the terms of the Botan license
//

#include <botan/internal/mlock.h>

#if defined(BOTAN_TARGET_OS_HAS_POSIX_MLOCK)
  #include <sys/types.h>
  #include <sys/mman.h>
#elif defined(BOTAN_TARGET_OS_HAS_WIN32_VIRTUAL_LOCK)
#ifndef _WINDOWS_
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif
#endif

namespace Botan {

bool has_mlock()
   {
   byte buf[4096];
   if(!lock_mem(&buf, sizeof(buf)))
      return false;
   unlock_mem(&buf, sizeof(buf));
   return true;
   }

//
// Lock an area of memory into RAM
//
bool lock_mem(void* ptr, size_t bytes)
   {
#if defined(BOTAN_TARGET_OS_HAS_POSIX_MLOCK)
   return (::mlock(static_cast<char*>(ptr), bytes) == 0);
#elif defined(BOTAN_TARGET_OS_HAS_WIN32_VIRTUAL_LOCK)
   return (::VirtualLock(ptr, bytes) != 0);
#else
   return false;
#endif
   }

//
// Unlock a previously locked region of memory
//
void unlock_mem(void* ptr, size_t bytes)
   {
#if defined(BOTAN_TARGET_OS_HAS_POSIX_MLOCK)
   ::munlock(static_cast<char*>(ptr), bytes);
#elif defined(BOTAN_TARGET_OS_HAS_WIN32_VIRTUAL_LOCK)
   ::VirtualUnlock(ptr, bytes);
#endif
   }

}

 */


#endif // __OT_CALLER_HPP__
