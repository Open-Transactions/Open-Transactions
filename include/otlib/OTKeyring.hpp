/************************************************************
 *
 *  OTKeyring.hpp
 *
 *  Mac has Keychain, Windows has DPAPI, Linux has Gnome-
 *  Keyring, KWallet, etc. The purpose of this class is to
 *  provide a simple, unified, cross-platform interface to
 *  all of them.
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

#ifndef __OT_KEYRING_HPP__
#define __OT_KEYRING_HPP__

#include "OTCommon.hpp"

// It's better to turn-on one of these, by using the Makefile,
// instead of hardcoding it here, which is entirely unnecessary.
//
// Nevertheless, I have added this comment anyway, in case that's
// what you want to do (for testing or whatever.)
//
//#define OT_KEYRING_WINDOWS  1
//#define OT_KEYRING_MAC      1
//#define OT_KEYRING_GNOME    1
//#define OT_KEYRING_KWALLET  1
//#define OT_KEYRING_FLATFILE 1

class OTString;
class OTPassword;


class OTKeyring
{
public:

    // NOTE: Normally the "username" in our context is related to the
    // master key. OTCachedKey will call OTKeyring::RetrieveSecret, and
    // will pass in probably a hash of the encrypted master key as the
    // "username", and will retrieve the cleartext master key as the
    // "password" (which it then uses as the password for all private
    // keys in the wallet.)
    //
    // OT *already* caches its master key inside the OTCachedKey object
    // itself, for X minutes. So then, why have this additional step,
    // where we store it using whatever is the standard API for
    // "protected memory" on the user's computer? The answer is, so that
    // we can cache the password BETWEEN runs of the OT engine, and not
    // just DURING the CURRENT run. For example, only this sort of
    // caching makes it possible to set the user free from still having
    // to enter his password for every run of an OT script.
    //
    // I don't even know if I recommend using this OTKeyring, since I
    // don't necessarily trust the operating system's protected memory,
    // and since the password is vulnerable during the time it is cached
    // by the OS, since any other process ALSO running as the same user
    // is able to ask the OS what the cached value is.
    //
    // (So be careful what software you run on your computer...)
    // In fact, perhaps OT should ONLY run as a certain user, which is
    // not used for anything else. Have it be setuid. That way, even if
    // a hacker can trick you into running his trojan as your own user,
    // he will be unable to query the OS for your master key, since your
    // user is not what was used to cache the PW in the first place (a
    // special "OT user" being used instead.) And thus cannot be used to
    // retrieve it, either.
    //
    // INTERFACE:
    //
EXPORT    static bool StoreSecret(    const OTString      & strUser,
                                      const OTPassword    & thePassword,
                                      const std::string   & str_display);

EXPORT    static bool RetrieveSecret( const OTString      & strUser,
                                            OTPassword    & thePassword,
                                      const std::string   & str_display);

EXPORT    static bool DeleteSecret(   const OTString      & strUser,
                                      const std::string   & str_display);
private:
    // -------------------------------------------------------
#if defined(OT_KEYRING_WINDOWS) && defined(_WIN32)
EXPORT    static bool Windows_StoreSecret(    const OTString      & strUser,
                                              const OTPassword    & thePassword,
                                              const std::string   & str_display);

EXPORT    static bool Windows_RetrieveSecret( const OTString      & strUser,
                                                    OTPassword    & thePassword,
                                              const std::string   & str_display);

EXPORT    static bool Windows_DeleteSecret(   const OTString      & strUser,
                                              const std::string   & str_display);
//#endif
    // -------------------------------------------------------
#elif defined(OT_KEYRING_MAC) && defined(__APPLE__)
    static bool Mac_StoreSecret(    const OTString      & strUser,
                                    const OTPassword    & thePassword,
                                    const std::string   & str_display);

    static bool Mac_RetrieveSecret( const OTString      & strUser,
                                          OTPassword    & thePassword,
                                    const std::string   & str_display);

    static bool Mac_DeleteSecret(   const OTString      & strUser,
                                    const std::string   & str_display);
//#endif
    // -------------------------------------------------------
#elif defined(OT_KEYRING_IOS) && defined(__APPLE__)
    static bool IOS_StoreSecret(    const OTString      & strUser,
                                    const OTPassword    & thePassword,
                                    const std::string   & str_display);

    static bool IOS_RetrieveSecret( const OTString      & strUser,
                                          OTPassword    & thePassword,
                                    const std::string   & str_display);

    static bool IOS_DeleteSecret(   const OTString      & strUser,
                                    const std::string   & str_display);
//#endif
    // -------------------------------------------------------
#elif defined(OT_KEYRING_GNOME)
    static bool Gnome_StoreSecret(   const OTString     & strUser,
                                     const OTPassword   & thePassword,
                                     const std::string  & str_display);

    static bool Gnome_RetrieveSecret(const OTString     & strUser,
                                           OTPassword   & thePassword,
                                     const std::string  & str_display); // unused

    static bool Gnome_DeleteSecret(  const OTString     & strUser,
                                     const std::string  & str_display); // unused
//#endif
    // -------------------------------------------------------
#elif defined(OT_KEYRING_KWALLET)
    static KWallet::Wallet * s_pWallet;
    static KApplication    * s_pApp;
    // -------------------------------------
    static bool KWallet_StoreSecret(   const OTString     & strUser,
                                       const OTPassword   & thePassword,
                                       const std::string  & str_display);

    static bool KWallet_RetrieveSecret(const OTString     & strUser,
                                             OTPassword   & thePassword,
                                       const std::string  & str_display);

    static bool KWallet_DeleteSecret(  const OTString     & strUser,
                                       const std::string  & str_display);
    // -------------------------------------------------------
#elif defined(OT_KEYRING_FLATFILE)  // Do not use! Unsafe! For testing only!
    // -------------------------------------
    static bool FlatFile_StoreSecret(   const OTString     & strUser,
                                        const OTPassword   & thePassword,
                                        const std::string  & str_display);

    static bool FlatFile_RetrieveSecret(const OTString     & strUser,
                                              OTPassword   & thePassword,
                                        const std::string  & str_display);

    static bool FlatFile_DeleteSecret(  const OTString     & strUser,
                                        const std::string  & str_display);
public:
EXPORT static void FlatFile_SetPasswordFolder(const std::string folder);
EXPORT static const char * FlatFile_GetPasswordFolder();
private:
EXPORT static std::string s_str_passwd_folder; //NOTE: Do not ever use this. OT_KEYRING_FLATFILE should NEVER be defined! No! For testing only.
#endif

};


#endif // __OT_KEYRING_HPP__
