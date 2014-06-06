/************************************************************
*
*  OTNumList.hpp
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

#ifndef __OT_NUM_LIST_HPP__
#define __OT_NUM_LIST_HPP__

#include "OTCommon.hpp"

#include <set>

class OTAsymmetricKey;
class OTPasswordData;
class OTString;


// Useful for storing a std::set of longs,
// serializing to/from comma-separated string,
// And easily being able to add/remove/verify the
// individual transaction numbers that are there.
// (Used by OTTransaction::blank and
// OTTransaction::successNotice.)
// Also used in OTMessage, for storing lists of acknowledged
// request numbers.
//
class OTNumList
{
    std::set<int64_t>  m_setData;

    // private for security reasons, used internally only by a function that knows the string length already.
    bool Add(const char * szfNumbers);   // if false, means the numbers were already there. (At least one of them.)

public:
EXPORT    OTNumList(const std::set<int64_t> & theNumbers);
//        OTNumList(const char * szNumbers); // removed for security reasons.
EXPORT    OTNumList(const OTString    & strNumbers);
EXPORT    OTNumList(const std::string & strNumbers);
EXPORT    OTNumList(int64_t lInput);
EXPORT    OTNumList();
EXPORT    ~OTNumList();
    // -------------------
EXPORT    bool Add(const OTString    & strNumbers);  // if false, means the numbers were already there. (At least one of them.)
EXPORT    bool Add(const std::string & strNumbers);  // if false, means the numbers were already there. (At least one of them.)
    // -------------------
EXPORT    bool Add   (const int64_t & theValue);       // if false, means the value was already there.
EXPORT    bool Remove(const int64_t & theValue);       // if false, means the value was NOT already there.
EXPORT    bool Verify(const int64_t & theValue) const; // returns true/false (whether value is already there.)
    // -------------------
EXPORT    bool Add   (const OTNumList      & theNumList); // if false, means the numbers were already there. (At least one of them.)
EXPORT    bool Add   (const std::set<int64_t> & theNumbers); // if false, means the numbers were already there. (At least one of them.)
EXPORT    bool Remove(const std::set<int64_t> & theNumbers); // if false, means the numbers were NOT already there. (At least one of them.)
EXPORT    bool Verify(const std::set<int64_t> & theNumbers) const; // True/False, based on whether values are already there. (ALL theNumbers must be present.)
    // -------------------
EXPORT    bool Verify   (const OTNumList & rhs) const; // True/False, based on whether OTNumLists MATCH in COUNT and CONTENT (NOT ORDER.)
EXPORT    bool VerifyAny(const OTNumList & rhs) const; // True/False, based on whether ANY of rhs are found in *this.
EXPORT    bool VerifyAny(const std::set<int64_t> & setData) const; // Verify whether ANY of the numbers on *this are found in setData.
    // -------------------
EXPORT    int32_t  Count() const;
    // -------------------
EXPORT    bool Peek(int64_t & lPeek) const;
EXPORT    bool Pop();
    // -------------------
    // Outputs the numlist as set of numbers. (To iterate OTNumList, call this, then iterate the output.)
EXPORT    bool Output(std::set<int64_t> & theOutput) const; // returns false if the numlist was empty.

    // Outputs the numlist as a comma-separated string (for serialization, usually.)
EXPORT    bool Output(OTString & strOutput) const; // returns false if the numlist was empty.
    // -------------------
EXPORT    void Release();
};


#endif // __OT_NUM_LIST_HPP__
