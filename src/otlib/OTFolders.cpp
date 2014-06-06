/************************************************************
*
*  OTFolders.cpp
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

#include "OTFolders.hpp"

#include "OTPaths.hpp"

//#include <vector>

//#include <sys/stat.h>


#ifdef _WIN32
#include <direct.h>
#include <shlobj.h>
#endif

#ifndef _WIN32
#include <libgen.h>
#include <unistd.h>
#endif

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#ifdef TARGET_OS_MAC
#include <mach-o/dyld.h>
#include <limits.h>
#endif

#ifndef S_ISDIR
#define S_ISDIR(mode)  (((mode) & S_IFMT) == S_IFDIR)
#endif

#ifndef S_ISREG
#define S_ISREG(mode)  (((mode) & S_IFMT) == S_IFREG)
#endif

#ifdef _WIN32
#define OT_APPDATA_DIR "OpenTransactions"
#elif TARGET_OS_IPHONE
#define OT_APPDATA_DIR "Documents"
#elif ANDROID
#define OT_APPDATA_DIR "ot"
#else
#define OT_APPDATA_DIR ".ot"
#endif

#ifndef OT_PREFIX_PATH
#ifdef _WIN32
#define OT_PREFIX_PATH OTPaths::AppDataFolder() // windows, set to OT AppData Folder.
#elif TARGET_OS_IPHONE
#define OT_PREFIX_PATH OTPaths::AppDataFolder() // iphone,  set to OT AppData Folder.
#elif ANDROID
#define OT_PREFIX_PATH "res/raw"                // android, set to res/raw folder for static files in android app sandbox.
#else
#define OT_PREFIX_PATH "/usr/local" //default prefix_path unix
#endif
#endif

#define OT_INIT_CONFIG_FILENAME "ot_init.cfg"
#define CONFIG_FILE_EXT ".cfg"
#define OT_HOME_DIR "."
#define OT_CONFIG_DIR "."
#define OT_USER_SCRIPTS_DIR "scripts"
#define DATA_FOLDER_EXT "_data"
#define OT_LIB_DIR "lib"
#define OT_CONFIG_ISRELATIVE "_is_relative"

#ifdef _WIN32
#define OT_SCRIPTS_DIR "scripts/ot"
#elif defined(ANDROID)
#define OT_SCRIPTS_DIR ""
#else
#define OT_SCRIPTS_DIR "lib/opentxs"
#endif


#define    DEFAULT_ACCOUNT         "accounts"
#define    DEFAULT_CERT            "certs"
#define    DEFAULT_CONTRACT        "contracts"
#define    DEFAULT_CREDENTIAL      "credentials"
#define    DEFAULT_CRON            "cron"
#define    DEFAULT_INBOX           "inbox"
#define    DEFAULT_MARKET          "markets"
#define    DEFAULT_MINT            "mints"
#define    DEFAULT_NYM             "nyms"
#define    DEFAULT_NYMBOX          "nymbox"
#define    DEFAULT_OUTBOX          "outbox"
#define    DEFAULT_PAYMENTINBOX    "paymentInbox"
#define    DEFAULT_PUBCRED         "pubcred"
#define    DEFAULT_PUBKEY          "pubkeys"
#define    DEFAULT_PURSE           "purse"
#define    DEFAULT_RECEIPT         "receipts"
#define    DEFAULT_RECORDBOX       "recordBox"
#define    DEFAULT_EXPIREDBOX      "expiredBox"
#define    DEFAULT_SCRIPT          "scripts"
#define    DEFAULT_SMARTCONTRACTS  "smartcontracts"
#define    DEFAULT_SPENT           "spent"
#define    DEFAULT_USERACCT        "useraccounts"


#define    KEY_ACCOUNT             "account"
#define    KEY_CERT                "cert"
#define    KEY_CONTRACT            "contract"
#define    KEY_CREDENTIAL          "credential"
#define    KEY_CRON                "cron"
#define    KEY_INBOX               "inbox"
#define    KEY_MARKET              "market"
#define    KEY_MINT                "mint"
#define    KEY_NYM                 "nym"
#define    KEY_NYMBOX              "nymbox"
#define    KEY_OUTBOX              "outbox"
#define    KEY_PAYMENTINBOX        "paymentinbox"
#define    KEY_PUBCRED             "pubcred"
#define    KEY_PUBKEY              "pubkey"
#define    KEY_PURSE               "purse"
#define    KEY_RECEIPT             "receipt"
#define    KEY_RECORDBOX           "recordbox"
#define    KEY_EXPIREDBOX          "expiredbox"
#define    KEY_SCRIPT              "script"
#define    KEY_SMARTCONTRACTS      "smartcontracts"
#define    KEY_SPENT               "spent"
#define    KEY_USERACCT            "useracct"


OTString OTFolders::s_strAccount("");
OTString OTFolders::s_strCert("");
OTString OTFolders::s_strContract("");
OTString OTFolders::s_strCredential("");
OTString OTFolders::s_strCron("");
OTString OTFolders::s_strInbox("");
OTString OTFolders::s_strMarket("");
OTString OTFolders::s_strMint("");
OTString OTFolders::s_strNym("");
OTString OTFolders::s_strNymbox("");
OTString OTFolders::s_strOutbox("");
OTString OTFolders::s_strPaymentInbox("");
OTString OTFolders::s_strPubcred("");
OTString OTFolders::s_strPubkey("");
OTString OTFolders::s_strPurse("");
OTString OTFolders::s_strReceipt("");
OTString OTFolders::s_strRecordBox("");
OTString OTFolders::s_strExpiredBox("");
OTString OTFolders::s_strScript("");
OTString OTFolders::s_strSmartContracts("");
OTString OTFolders::s_strSpent("");
OTString OTFolders::s_strUserAcct("");


bool OTFolders::GetSetAll()
{
    OTSettings config = OTSettings(OTPaths::GlobalConfigFile());

    config.Reset();

    if(!config.Load()) return false;

    if(!GetSetFolderName(config,KEY_ACCOUNT,         DEFAULT_ACCOUNT,         s_strAccount         )) return false;
    if(!GetSetFolderName(config,KEY_CERT,            DEFAULT_CERT,            s_strCert            )) return false;
    if(!GetSetFolderName(config,KEY_CONTRACT,        DEFAULT_CONTRACT,        s_strContract        )) return false;
    if(!GetSetFolderName(config,KEY_CREDENTIAL,      DEFAULT_CREDENTIAL,      s_strCredential      )) return false;
    if(!GetSetFolderName(config,KEY_CRON,            DEFAULT_CRON,            s_strCron            )) return false;
    if(!GetSetFolderName(config,KEY_INBOX,           DEFAULT_INBOX,           s_strInbox           )) return false;
    if(!GetSetFolderName(config,KEY_MARKET,          DEFAULT_MARKET,          s_strMarket          )) return false;
    if(!GetSetFolderName(config,KEY_MINT,            DEFAULT_MINT,            s_strMint            )) return false;
    if(!GetSetFolderName(config,KEY_NYM,             DEFAULT_NYM,             s_strNym             )) return false;
    if(!GetSetFolderName(config,KEY_NYMBOX,          DEFAULT_NYMBOX,          s_strNymbox          )) return false;
    if(!GetSetFolderName(config,KEY_OUTBOX,          DEFAULT_OUTBOX,          s_strOutbox          )) return false;
    if(!GetSetFolderName(config,KEY_PAYMENTINBOX,    DEFAULT_PAYMENTINBOX,    s_strPaymentInbox    )) return false;
    if(!GetSetFolderName(config,KEY_PUBCRED,         DEFAULT_PUBCRED,         s_strPubcred         )) return false;
    if(!GetSetFolderName(config,KEY_PUBKEY,          DEFAULT_PUBKEY,          s_strPubkey          )) return false;
    if(!GetSetFolderName(config,KEY_PURSE,           DEFAULT_PURSE,           s_strPurse           )) return false;
    if(!GetSetFolderName(config,KEY_RECEIPT,         DEFAULT_RECEIPT,         s_strReceipt         )) return false;
    if(!GetSetFolderName(config,KEY_RECORDBOX,       DEFAULT_RECORDBOX,       s_strRecordBox       )) return false;
    if(!GetSetFolderName(config,KEY_EXPIREDBOX,      DEFAULT_EXPIREDBOX,      s_strExpiredBox      )) return false;
    if(!GetSetFolderName(config,KEY_SCRIPT,          DEFAULT_SCRIPT,          s_strScript          )) return false;
    if(!GetSetFolderName(config,KEY_SMARTCONTRACTS,  DEFAULT_SMARTCONTRACTS,  s_strSmartContracts  )) return false;
    if(!GetSetFolderName(config,KEY_SPENT,           DEFAULT_SPENT,           s_strSpent           )) return false;
    if(!GetSetFolderName(config,KEY_USERACCT,        DEFAULT_USERACCT,        s_strUserAcct        )) return false;

    if(!config.Save()) return false;

    config.Reset();

    return true;
}


const OTString & OTFolders::Account()         { return GetFolder(s_strAccount         ); }
const OTString & OTFolders::Cert()            { return GetFolder(s_strCert            ); }
const OTString & OTFolders::Contract()        { return GetFolder(s_strContract        ); }
const OTString & OTFolders::Credential()      { return GetFolder(s_strCredential      ); }
const OTString & OTFolders::Cron()            { return GetFolder(s_strCron            ); }
const OTString & OTFolders::Inbox()           { return GetFolder(s_strInbox           ); }
const OTString & OTFolders::Market()          { return GetFolder(s_strMarket          ); }
const OTString & OTFolders::Mint()            { return GetFolder(s_strMint            ); }
const OTString & OTFolders::Nym()             { return GetFolder(s_strNym             ); }
const OTString & OTFolders::Nymbox()          { return GetFolder(s_strNymbox          ); }
const OTString & OTFolders::Outbox()          { return GetFolder(s_strOutbox          ); }
const OTString & OTFolders::PaymentInbox()    { return GetFolder(s_strPaymentInbox    ); }
const OTString & OTFolders::Pubcred()         { return GetFolder(s_strPubcred         ); }
const OTString & OTFolders::Pubkey()          { return GetFolder(s_strPubkey          ); }
const OTString & OTFolders::Purse()           { return GetFolder(s_strPurse           ); }
const OTString & OTFolders::Receipt()         { return GetFolder(s_strReceipt         ); }
const OTString & OTFolders::RecordBox()       { return GetFolder(s_strRecordBox       ); }
const OTString & OTFolders::ExpiredBox()      { return GetFolder(s_strExpiredBox      ); }
const OTString & OTFolders::Script()          { return GetFolder(s_strScript          ); }
const OTString & OTFolders::SmartContracts()  { return GetFolder(s_strSmartContracts  ); }
const OTString & OTFolders::Spent()           { return GetFolder(s_strSpent           ); }
const OTString & OTFolders::UserAcct()        { return GetFolder(s_strUserAcct        ); }
