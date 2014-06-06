/************************************************************
*
* OTFolders.hpp
* This Class Maintins where stuff should go;
* You must create one and only one contex for
* every instance of OT_API.
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

#ifndef __OT_FOLDERS_HPP__
#define __OT_FOLDERS_HPP__

#include "OTAssert.hpp"
#include "OTSettings.hpp"


// This class is for storing the names of the folders.  A instance of it must be made.
// This function will store the folder-names automaticaly in the config file.
//
class OTFolders
{
private:

    static bool GetSetAll();

    static inline bool GetSetFolderName(OTSettings & config, const std::string strKeyName,
                                              const std::string strDefaultName, OTString & ret_strName)
    {
        if (ret_strName.Exists()) return true;
        else
        {
            if (strKeyName.empty()    || strDefaultName.empty())    return false;
            if (3 > strKeyName.size() || 3 > strDefaultName.size()) return false;

            OTString strResult("");
            bool bIsNew(false);

            config.CheckSet_str("folders",strKeyName,strDefaultName,strResult,bIsNew);

            if (!bIsNew) ret_strName = strResult;
            else         ret_strName = strDefaultName.c_str();

            return true;
        }
    }

    static inline const OTString & GetFolder(const OTString & strFolder)
    {
        if (!strFolder.Exists()) {
            if (!GetSetAll()) { OT_FAIL; } }
        return strFolder;
    }


    static OTString s_strAccount;
    static OTString s_strCert;
    static OTString s_strContract;
    static OTString s_strCredential;
    static OTString s_strCron;
    static OTString s_strInbox;
    static OTString s_strMarket;
    static OTString s_strMint;
    static OTString s_strNym;
    static OTString s_strNymbox;
    static OTString s_strOutbox;
    static OTString s_strPaymentInbox;
    static OTString s_strPubcred;
    static OTString s_strPubkey;
    static OTString s_strPurse;
    static OTString s_strReceipt;
    static OTString s_strRecordBox;
    static OTString s_strExpiredBox;
    static OTString s_strScript;
    static OTString s_strSmartContracts;
    static OTString s_strSpent;
    static OTString s_strUserAcct;

public:

    EXPORT static const OTString & Account();
    EXPORT static const OTString & Cert();
    EXPORT static const OTString & Contract();
    EXPORT static const OTString & Credential();
    EXPORT static const OTString & Cron();
    EXPORT static const OTString & Inbox();
    EXPORT static const OTString & Market();
    EXPORT static const OTString & Mint();
    EXPORT static const OTString & Nym();
    EXPORT static const OTString & Nymbox();
    EXPORT static const OTString & Outbox();
    EXPORT static const OTString & PaymentInbox();
    EXPORT static const OTString & Pubcred();
    EXPORT static const OTString & Pubkey();
    EXPORT static const OTString & Purse();
    EXPORT static const OTString & Receipt();
    EXPORT static const OTString & RecordBox();
    EXPORT static const OTString & ExpiredBox();
    EXPORT static const OTString & Script();
    EXPORT static const OTString & SmartContracts();
    EXPORT static const OTString & Spent();
    EXPORT static const OTString & UserAcct();

}; // class OTFolders


#endif // __OT_FOLDERS_HPP__
