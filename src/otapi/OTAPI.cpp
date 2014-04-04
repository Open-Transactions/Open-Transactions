/************************************************************************************
*
* OTAPI.cpp   --	A C++ Low-Level API (wraps OT_API)
*
* This is a C++ class that contains many helper functions.
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

#include <stdafx.hpp>

// A C++ class, low-level interface to OT.
#include "OTAPI.hpp"

#include <OTAPI_Exec.hpp>
#include <OpenTransactions.hpp>

#ifndef IMPORT
#define IMPORT
#endif

#include <OTBasket.hpp>
#include <OTCheque.hpp>
#include <OTCredential.hpp>
#include <OTEnvelope.hpp>
#include <OTLedger.hpp>
#include <OTLog.hpp>
#include <OTMessage.hpp>
#include <OTMint.hpp>
#include <OTPassword.hpp>
#include <OTPaths.hpp>
#include <OTPayment.hpp>
#include <OTPaymentPlan.hpp>
#include <OTPurse.hpp>
#include <OTServerContract.hpp>
#include <OTSymmetricKey.hpp>
#include <OTWallet.hpp>

#include <OTAccount.hpp>  //included in OTSmartContract.hpp

//extern "C"
//{
//#ifndef _WIN32
//#include <inttypes.h>
//#else
//
//#ifndef PRId64
//#define PRId64 "I64d"
//#endif
//
//#ifndef PRId32
//#define PRId32 "I32d"
//#endif
//
//#endif
//}

// ---------------------------------------------------------------

#ifndef OT_BOOL
#define OT_BOOL int32_t
#endif

#ifndef OT_FALSE
const int32_t OT_FALSE = 0;
#endif

#ifndef OT_TRUE
const int32_t OT_TRUE = 1;
#endif


#ifndef OT_ERROR
const int32_t OT_ERROR = (-1);
#endif

// ---------------------------------------------------------------

// singleton object !!!
static OTAPI_Exec singleton;
static OTAPI_Exec * exec = &singleton;


OTAPI_Exec * OTAPI_Wrap::SetExecutor(OTAPI_Exec * execNew)
{
	OTAPI_Exec * execOld = exec;
	exec = execNew;
	return execOld;
}

OTAPI_Exec * OTAPI_Wrap::Exec()
{
	if (NULL == exec)
	{
		OTLog::sError("%s: Error: OTAPI_Exec wrapper not found!!\n", __FUNCTION__);
		OT_FAIL;
	}

	OT_API * pOTAPI = exec->OTAPI();
	if (NULL == pOTAPI || !pOTAPI->IsInitialized())
	{
		OTLog::sError("%s: Error: OT_API not Initialized!!\n", __FUNCTION__);
		OT_FAIL;
	}

	return exec;
}

bool OTAPI_Wrap::AppInit()
{
	if (NULL == exec)
	{
		OTLog::sError("%s: Error: OTAPI_Exec wrapper not found!!\n", __FUNCTION__);
		OT_FAIL;
	}

	return exec->AppInit();
}

bool OTAPI_Wrap::AppCleanup()
{
	if (NULL == exec)
	{
		OTLog::sError("%s: Error: OTAPI_Exec wrapper not found!!\n", __FUNCTION__);
		OT_FAIL;
	}

	return exec->AppCleanup();
}

// --------------------------------------------------------------------
// SetAppBinaryFolder
// OPTIONAL. Used in Android and Qt.
//
// Certain platforms use this to override the Prefix folder.
// Basically /usr/local is the prefix folder by default, meaning
// /usr/local/lib/opentxs will be the location of the scripts. But
// if you override AppBinary folder to, say, "res/raw"
// (Android does something like that) then even though the prefix remains
// as /usr/local, the scripts folder will be res/raw
//
//
void OTAPI_Wrap::SetAppBinaryFolder(const std::string & strFolder)
{
    Exec()->SetAppBinaryFolder(strFolder);
}

// --------------------------------------------------------------------
// SetHomeFolder
// OPTIONAL. Used in Android.
//
// The AppDataFolder, such as /Users/au/.ot, is constructed from the home
// folder, such as /Users/au.
//
// Normally the home folder is auto-detected, but certain platforms, such as
// Android, require us to explicitly set this folder from the Java code. Then
// the AppDataFolder is constructed from it. (It's the only way it can be done.)
//
// In Android, you would SetAppBinaryFolder to the path to "/data/app/packagename/res/raw",
// and you would SetHomeFolder to "/data/data/[app package]/files/"
//
void OTAPI_Wrap::SetHomeFolder(const std::string & strFolder)
{
    Exec()->SetHomeFolder(strFolder);
}


OT_API * OTAPI_Wrap::OTAPI()
{
	if (NULL == exec)
	{
		OTLog::sError("%s: Error: OTAPI_Exec wrapper not found!!\n", __FUNCTION__);
		OT_FAIL;
	}

	return exec->OTAPI();
}

int64_t OTAPI_Wrap::StringToLong(const std::string & strNumber)
{
    return Exec()->StringToLong(strNumber);
}

std::string OTAPI_Wrap::LongToString(const int64_t & lNumber)
{
    return Exec()->LongToString(lNumber);
}

uint64_t OTAPI_Wrap::StringToUlong(const std::string & strNumber)
{
    return Exec()->StringToUlong(strNumber);
}

std::string OTAPI_Wrap::UlongToString(const uint64_t & lNumber)
{
    return Exec()->UlongToString(lNumber);
}

void OTAPI_Wrap::Output(const int32_t & nLogLevel, const std::string & strOutput)
{
    return Exec()->Output(nLogLevel, strOutput);
}

bool OTAPI_Wrap::SetWallet(const std::string & strWalletFilename)
{
    return Exec()->SetWallet(strWalletFilename);
}

bool OTAPI_Wrap::WalletExists()
{
	return Exec()->WalletExists();
}

bool OTAPI_Wrap::LoadWallet()
{
	return Exec()->LoadWallet();
}

bool OTAPI_Wrap::SwitchWallet()
{
	return Exec()->LoadWallet();
}

int32_t OTAPI_Wrap::GetMemlogSize()
{
	return Exec()->GetMemlogSize();
}

std::string OTAPI_Wrap::GetMemlogAtIndex(const int32_t & nIndex)
{
	return Exec()->GetMemlogAtIndex(nIndex);
}

std::string OTAPI_Wrap::PeekMemlogFront()
{
	return Exec()->PeekMemlogFront();
}

std::string OTAPI_Wrap::PeekMemlogBack()
{
	return Exec()->PeekMemlogBack();
}

bool OTAPI_Wrap::PopMemlogFront()
{
	return Exec()->PopMemlogFront();
}

bool OTAPI_Wrap::PopMemlogBack()
{
	return Exec()->PopMemlogBack();
}

std::string OTAPI_Wrap::NumList_Add(const std::string & strNumList, const std::string & strNumbers)
{
    return Exec()->NumList_Add(strNumList, strNumbers);
}

std::string OTAPI_Wrap::NumList_Remove(const std::string & strNumList, const std::string & strNumbers)
{
    return Exec()->NumList_Remove(strNumList, strNumbers);
}

bool OTAPI_Wrap::NumList_VerifyQuery(const std::string & strNumList, const std::string & strNumbers)
{
    return Exec()->NumList_VerifyQuery(strNumList, strNumbers);
}

bool OTAPI_Wrap::NumList_VerifyAll(const std::string & strNumList, const std::string & strNumbers)
{
    return Exec()->NumList_VerifyAll(strNumList, strNumbers);
}

int32_t OTAPI_Wrap::NumList_Count(const std::string & strNumList)
{
    return Exec()->NumList_Count(strNumList);
}

std::string OTAPI_Wrap::CreateNym(const int32_t & nKeySize, const std::string & NYM_ID_SOURCE, const std::string & ALT_LOCATION)
{
    return Exec()->CreateNym(nKeySize, NYM_ID_SOURCE, ALT_LOCATION);
}

std::string OTAPI_Wrap::GetNym_ActiveCronItemIDs(const std::string & NYM_ID, const std::string & SERVER_ID)
{
    return Exec()->GetNym_ActiveCronItemIDs(NYM_ID, SERVER_ID);

}
std::string OTAPI_Wrap::GetActiveCronItem(const std::string & SERVER_ID, int64_t lTransNum)
{
    return Exec()->GetActiveCronItem(SERVER_ID, lTransNum);
}

std::string OTAPI_Wrap::GetNym_SourceForID(const std::string & NYM_ID)
{
    return Exec()->GetNym_SourceForID(NYM_ID);
}

std::string OTAPI_Wrap::GetNym_AltSourceLocation(const std::string & NYM_ID)
{
    return Exec()->GetNym_AltSourceLocation(NYM_ID);
}

int32_t OTAPI_Wrap::GetNym_CredentialCount(const std::string & NYM_ID)
{
    return Exec()->GetNym_CredentialCount(NYM_ID);
}

std::string OTAPI_Wrap::GetNym_CredentialID(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_CredentialID(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_CredentialContents(const std::string & NYM_ID, const std::string & CREDENTIAL_ID)
{
    return Exec()->GetNym_CredentialContents(NYM_ID, CREDENTIAL_ID);
}

int32_t OTAPI_Wrap::GetNym_RevokedCredCount(const std::string & NYM_ID)
{
    return Exec()->GetNym_RevokedCredCount(NYM_ID);
}

std::string OTAPI_Wrap::GetNym_RevokedCredID(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_RevokedCredID(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_RevokedCredContents(const std::string & NYM_ID, const std::string & CREDENTIAL_ID)
{
    return Exec()->GetNym_RevokedCredContents(NYM_ID, CREDENTIAL_ID);
}

int32_t OTAPI_Wrap::GetNym_SubcredentialCount(const std::string & NYM_ID, const std::string & MASTER_CRED_ID)
{
    return Exec()->GetNym_SubcredentialCount(NYM_ID, MASTER_CRED_ID);
}

std::string OTAPI_Wrap::GetNym_SubCredentialID(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_SubCredentialID(NYM_ID, MASTER_CRED_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_SubCredentialContents(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const std::string & SUB_CRED_ID)
{
    return Exec()->GetNym_SubCredentialContents(NYM_ID, MASTER_CRED_ID, SUB_CRED_ID);
}

std::string OTAPI_Wrap::AddSubcredential(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const int32_t & nKeySize)
{
    return Exec()->AddSubcredential(NYM_ID, MASTER_CRED_ID, nKeySize);
}

bool OTAPI_Wrap::RevokeSubcredential(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const std::string & SUB_CRED_ID)
{
    return Exec()->RevokeSubcredential(NYM_ID, MASTER_CRED_ID, SUB_CRED_ID);
}

std::string OTAPI_Wrap::CalculateAssetContractID(const std::string & str_Contract)
{
    return Exec()->CalculateAssetContractID(str_Contract);
}

std::string OTAPI_Wrap::CalculateServerContractID(const std::string & str_Contract)
{
    return Exec()->CalculateServerContractID(str_Contract);
}

std::string OTAPI_Wrap::CreateServerContract(const std::string & NYM_ID, const std::string & strXMLcontents)
{
    return Exec()->CreateServerContract(NYM_ID, strXMLcontents);
}

std::string OTAPI_Wrap::CreateAssetContract(const std::string & NYM_ID, const std::string & strXMLcontents)
{
    return Exec()->CreateAssetContract(NYM_ID, strXMLcontents);
}

std::string OTAPI_Wrap::GetServer_Contract(const std::string & SERVER_ID)
{
    return Exec()->GetServer_Contract(SERVER_ID);
}

int64_t OTAPI_Wrap::StringToAmount(const std::string & ASSET_TYPE_ID, const std::string & str_input)
{
    return Exec()->StringToAmount(ASSET_TYPE_ID, str_input);
}

std::string OTAPI_Wrap::FormatAmount(const std::string & ASSET_TYPE_ID, const int64_t & THE_AMOUNT)
{
    return Exec()->FormatAmount(ASSET_TYPE_ID, THE_AMOUNT);
}

std::string OTAPI_Wrap::GetAssetType_Contract(const std::string & ASSET_TYPE_ID)
{
    return Exec()->GetAssetType_Contract(ASSET_TYPE_ID);
}

int32_t OTAPI_Wrap::AddServerContract(const std::string & strContract)
{
    return Exec()->AddServerContract(strContract);
}

int32_t OTAPI_Wrap::AddAssetContract(const std::string & strContract)
{
    return Exec()->AddAssetContract(strContract);
}

int32_t OTAPI_Wrap::GetNymCount(void)
{
    return Exec()->GetNymCount();
}

int32_t OTAPI_Wrap::GetServerCount(void)
{
    return Exec()->GetServerCount();
}

int32_t OTAPI_Wrap::GetAssetTypeCount(void)
{
    return Exec()->GetAssetTypeCount();
}

int32_t OTAPI_Wrap::GetAccountCount(void)
{
    return Exec()->GetAccountCount();
}

bool OTAPI_Wrap::Wallet_CanRemoveServer(const std::string & SERVER_ID)
{
    return Exec()->Wallet_CanRemoveServer(SERVER_ID);
}

bool OTAPI_Wrap::Wallet_RemoveServer(const std::string & SERVER_ID)
{
    return Exec()->Wallet_RemoveServer(SERVER_ID);
}

bool	OTAPI_Wrap::Wallet_CanRemoveAssetType(const std::string & ASSET_ID)
{
    return Exec()->Wallet_CanRemoveAssetType(ASSET_ID);
}

bool	OTAPI_Wrap::Wallet_RemoveAssetType(const std::string & ASSET_ID)
{
    return Exec()->Wallet_RemoveAssetType(ASSET_ID);
}

bool OTAPI_Wrap::Wallet_CanRemoveNym(const std::string & NYM_ID)
{
    return Exec()->Wallet_CanRemoveNym(NYM_ID);
}

bool	OTAPI_Wrap::Wallet_RemoveNym(const std::string & NYM_ID)
{
    return Exec()->Wallet_RemoveNym(NYM_ID);
}

bool	OTAPI_Wrap::Wallet_CanRemoveAccount(const std::string & ACCOUNT_ID)
{
    return Exec()->Wallet_CanRemoveAccount(ACCOUNT_ID);
}

bool OTAPI_Wrap::DoesBoxReceiptExist(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const int32_t & nBoxType, const int64_t & TRANSACTION_NUMBER)
{
    return Exec()->DoesBoxReceiptExist(SERVER_ID, USER_ID, ACCOUNT_ID, 	nBoxType, TRANSACTION_NUMBER);
}

int32_t OTAPI_Wrap::getBoxReceipt(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const int32_t & nBoxType, const int64_t & TRANSACTION_NUMBER)
{
    return Exec()->getBoxReceipt(SERVER_ID, USER_ID, ACCOUNT_ID, nBoxType, TRANSACTION_NUMBER);
}



int32_t OTAPI_Wrap::deleteAssetAccount(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->deleteAssetAccount(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::Wallet_ExportNym(const std::string & NYM_ID)
{
    return Exec()->Wallet_ExportNym(NYM_ID);
}

std::string OTAPI_Wrap::Wallet_ExportCert(const std::string & NYM_ID)
{
    return Exec()->Wallet_ExportCert(NYM_ID);
}

std::string OTAPI_Wrap::Wallet_ImportNym(const std::string & FILE_CONTENTS)
{
    return Exec()->Wallet_ImportNym(FILE_CONTENTS);
}

std::string OTAPI_Wrap::Wallet_ImportCert(const std::string & DISPLAY_NAME, const std::string & FILE_CONTENTS)
{
    return Exec()->Wallet_ImportCert(DISPLAY_NAME, FILE_CONTENTS);
}

bool OTAPI_Wrap::Wallet_ChangePassphrase()
{
    return Exec()->Wallet_ChangePassphrase();
}

std::string OTAPI_Wrap::Wallet_GetNymIDFromPartial(const std::string & PARTIAL_ID)
{
    return Exec()->Wallet_GetNymIDFromPartial(PARTIAL_ID);
}

std::string OTAPI_Wrap::Wallet_GetServerIDFromPartial(const std::string & PARTIAL_ID)
{
    return Exec()->Wallet_GetServerIDFromPartial(PARTIAL_ID);
}

std::string OTAPI_Wrap::Wallet_GetAssetIDFromPartial(const std::string & PARTIAL_ID)
{
    return Exec()->Wallet_GetAssetIDFromPartial(PARTIAL_ID);
}

std::string OTAPI_Wrap::Wallet_GetAccountIDFromPartial(const std::string & PARTIAL_ID)
{
    return Exec()->Wallet_GetAccountIDFromPartial(PARTIAL_ID);
}

std::string OTAPI_Wrap::GetNym_ID(const int32_t & nIndex)
{
    return Exec()->GetNym_ID(nIndex);
}

std::string OTAPI_Wrap::GetNym_Name(const std::string & NYM_ID)
{
    return Exec()->GetNym_Name(NYM_ID);
}

bool OTAPI_Wrap::IsNym_RegisteredAtServer(const std::string & NYM_ID, const std::string & SERVER_ID)
{
    return Exec()->IsNym_RegisteredAtServer(NYM_ID, SERVER_ID);
}

std::string OTAPI_Wrap::GetNym_Stats(const std::string & NYM_ID)
{
    return Exec()->GetNym_Stats(NYM_ID);
}

std::string OTAPI_Wrap::GetNym_NymboxHash(const std::string & SERVER_ID, const std::string & NYM_ID)
{
    return Exec()->GetNym_NymboxHash(SERVER_ID, NYM_ID);
}

std::string OTAPI_Wrap::GetNym_RecentHash(const std::string & SERVER_ID, const std::string & NYM_ID)
{
    return Exec()->GetNym_RecentHash(SERVER_ID, NYM_ID);
}

std::string OTAPI_Wrap::GetNym_InboxHash(const std::string & ACCOUNT_ID, const std::string & NYM_ID)
{
    return Exec()->GetNym_InboxHash(ACCOUNT_ID, NYM_ID);
}

std::string OTAPI_Wrap::GetNym_OutboxHash(const std::string & ACCOUNT_ID, const std::string & NYM_ID)
{
    return Exec()->GetNym_OutboxHash(ACCOUNT_ID, NYM_ID);
}

int32_t	OTAPI_Wrap::GetNym_MailCount(const std::string & NYM_ID)
{
    return Exec()->GetNym_MailCount(NYM_ID);
}

std::string OTAPI_Wrap::GetNym_MailContentsByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_MailContentsByIndex(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_MailSenderIDByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_MailSenderIDByIndex(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_MailServerIDByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_MailServerIDByIndex(NYM_ID, nIndex);
}

bool OTAPI_Wrap::Nym_RemoveMailByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->Nym_RemoveMailByIndex(NYM_ID, nIndex);
}

bool OTAPI_Wrap::Nym_VerifyMailByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->Nym_VerifyMailByIndex(NYM_ID, nIndex);
}

int32_t	OTAPI_Wrap::GetNym_OutmailCount(const std::string & NYM_ID)
{
    return Exec()->GetNym_OutmailCount(NYM_ID);
}

std::string OTAPI_Wrap::GetNym_OutmailContentsByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_OutmailContentsByIndex(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_OutmailRecipientIDByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_OutmailRecipientIDByIndex(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_OutmailServerIDByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_OutmailServerIDByIndex(NYM_ID, nIndex);
}

bool OTAPI_Wrap::Nym_RemoveOutmailByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->Nym_RemoveOutmailByIndex(NYM_ID, nIndex);
}

bool OTAPI_Wrap::Nym_VerifyOutmailByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->Nym_VerifyOutmailByIndex(NYM_ID, nIndex);
}

int32_t	OTAPI_Wrap::GetNym_OutpaymentsCount(const std::string & NYM_ID)
{
    return Exec()->GetNym_OutpaymentsCount(NYM_ID);
}

std::string OTAPI_Wrap::GetNym_OutpaymentsContentsByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_OutpaymentsContentsByIndex(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_OutpaymentsRecipientIDByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_OutpaymentsRecipientIDByIndex(NYM_ID, nIndex);
}

std::string OTAPI_Wrap::GetNym_OutpaymentsServerIDByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->GetNym_OutpaymentsServerIDByIndex(NYM_ID, nIndex);
}

bool OTAPI_Wrap::Nym_RemoveOutpaymentsByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->Nym_RemoveOutpaymentsByIndex(NYM_ID, nIndex);
}

bool OTAPI_Wrap::Nym_VerifyOutpaymentsByIndex(const std::string & NYM_ID, const int32_t & nIndex)
{
    return Exec()->Nym_VerifyOutpaymentsByIndex(NYM_ID, nIndex);
}

int64_t OTAPI_Wrap::Instrmnt_GetAmount(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetAmount(THE_INSTRUMENT);
}

int64_t OTAPI_Wrap::Instrmnt_GetTransNum(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetTransNum(THE_INSTRUMENT);
}

time_t OTAPI_Wrap::Instrmnt_GetValidFrom(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetValidFrom(THE_INSTRUMENT);
}

time_t OTAPI_Wrap::Instrmnt_GetValidTo(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetValidTo(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetType(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetType(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetMemo(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetMemo(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetServerID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetServerID(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetAssetID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetAssetID(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetRemitterUserID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetRemitterUserID(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetRemitterAcctID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetRemitterAcctID(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetSenderUserID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetSenderUserID(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetSenderAcctID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetSenderAcctID(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetRecipientUserID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetRecipientUserID(THE_INSTRUMENT);
}

std::string OTAPI_Wrap::Instrmnt_GetRecipientAcctID(const std::string & THE_INSTRUMENT)
{
    return Exec()->Instrmnt_GetRecipientAcctID(THE_INSTRUMENT);
}

bool OTAPI_Wrap::SetNym_Name(const std::string & NYM_ID, const std::string & SIGNER_NYM_ID, const std::string & NYM_NEW_NAME)
{
    return Exec()->SetNym_Name(NYM_ID, SIGNER_NYM_ID, NYM_NEW_NAME);
}

bool OTAPI_Wrap::SetServer_Name(const std::string & SERVER_ID, const std::string & STR_NEW_NAME)
{
    return Exec()->SetServer_Name(SERVER_ID, STR_NEW_NAME);
}

bool OTAPI_Wrap::SetAssetType_Name(const std::string & ASSET_ID, const std::string & STR_NEW_NAME)
{
    return Exec()->SetAssetType_Name(ASSET_ID, STR_NEW_NAME);
}

int32_t OTAPI_Wrap::GetNym_TransactionNumCount(const std::string & SERVER_ID, const std::string & NYM_ID)
{
    return Exec()->GetNym_TransactionNumCount(SERVER_ID, NYM_ID);
}

std::string OTAPI_Wrap::GetServer_ID(const int32_t & nIndex)
{
    return Exec()->GetServer_ID(nIndex);
}

std::string OTAPI_Wrap::GetServer_Name(const std::string & THE_ID)
{
    return Exec()->GetServer_Name(THE_ID);
}

std::string OTAPI_Wrap::GetAssetType_ID(const int32_t & nIndex)
{
    return Exec()->GetAssetType_ID(nIndex);
}

std::string OTAPI_Wrap::GetAssetType_Name(const std::string & THE_ID)
{
    return Exec()->GetAssetType_Name(THE_ID);
}

std::string OTAPI_Wrap::GetAssetType_TLA(const std::string & THE_ID)
{
    return Exec()->GetAssetType_TLA(THE_ID);
}

std::string OTAPI_Wrap::GetAccountWallet_ID(const int32_t & nIndex)
{
    return Exec()->GetAccountWallet_ID(nIndex);
}

std::string OTAPI_Wrap::GetAccountWallet_Name(const std::string & THE_ID)
{
    return Exec()->GetAccountWallet_Name(THE_ID);
}

std::string OTAPI_Wrap::GetAccountWallet_InboxHash(const std::string & ACCOUNT_ID)
{
    return Exec()->GetAccountWallet_InboxHash(ACCOUNT_ID);
}

std::string OTAPI_Wrap::GetAccountWallet_OutboxHash(const std::string & ACCOUNT_ID)
{
    return Exec()->GetAccountWallet_OutboxHash(ACCOUNT_ID);
}

time_t OTAPI_Wrap::GetTime(void)
{
    return Exec()->GetTime();
}

std::string OTAPI_Wrap::Encode(const std::string & strPlaintext, const bool & bLineBreaks)
{
    return Exec()->Encode(strPlaintext, bLineBreaks);
}

std::string OTAPI_Wrap::Decode(const std::string & strEncoded, const bool & bLineBreaks)
{
    return Exec()->Decode(strEncoded, bLineBreaks);
}

std::string OTAPI_Wrap::Encrypt(const std::string & RECIPIENT_NYM_ID, const std::string & strPlaintext)
{
    return Exec()->Encrypt(RECIPIENT_NYM_ID, strPlaintext);
}

std::string OTAPI_Wrap::Decrypt(const std::string & RECIPIENT_NYM_ID, const std::string & strCiphertext)
{
    return Exec()->Decrypt(RECIPIENT_NYM_ID, strCiphertext);
}

std::string OTAPI_Wrap::CreateSymmetricKey()
{
    return Exec()->CreateSymmetricKey();
}

std::string OTAPI_Wrap::SymmetricEncrypt(const std::string & SYMMETRIC_KEY, const std::string & PLAINTEXT)
{
    return Exec()->SymmetricEncrypt(SYMMETRIC_KEY, PLAINTEXT);
}

std::string OTAPI_Wrap::SymmetricDecrypt(const std::string & SYMMETRIC_KEY, const std::string & CIPHERTEXT_ENVELOPE)
{
    return Exec()->SymmetricDecrypt(SYMMETRIC_KEY, CIPHERTEXT_ENVELOPE);
}

std::string OTAPI_Wrap::SignContract(const std::string & SIGNER_NYM_ID, const std::string & THE_CONTRACT)
{
    return Exec()->SignContract(SIGNER_NYM_ID, THE_CONTRACT);
}

std::string OTAPI_Wrap::FlatSign(const std::string & SIGNER_NYM_ID, const std::string & THE_INPUT, const std::string & CONTRACT_TYPE)
{
    return Exec()->FlatSign(SIGNER_NYM_ID, THE_INPUT, CONTRACT_TYPE);
}

std::string OTAPI_Wrap::AddSignature(const std::string & SIGNER_NYM_ID, const std::string & THE_CONTRACT)
{
    return Exec()->AddSignature(SIGNER_NYM_ID, THE_CONTRACT);
}

bool	OTAPI_Wrap::VerifySignature(const std::string & SIGNER_NYM_ID, const std::string & THE_CONTRACT)
{
    return Exec()->VerifySignature(SIGNER_NYM_ID, THE_CONTRACT);
}

std::string OTAPI_Wrap::VerifyAndRetrieveXMLContents(const std::string & THE_CONTRACT, const std::string & SIGNER_ID)
{
    return Exec()->VerifyAndRetrieveXMLContents(THE_CONTRACT, SIGNER_ID);
}

bool OTAPI_Wrap::VerifyAccountReceipt(const std::string & SERVER_ID, const std::string & NYM_ID, const std::string & ACCT_ID)
{
    return Exec()->VerifyAccountReceipt(SERVER_ID, NYM_ID, ACCT_ID);
}

bool OTAPI_Wrap::SetAccountWallet_Name(const std::string & ACCT_ID, const std::string & SIGNER_NYM_ID, const std::string & ACCT_NEW_NAME)
{
    return Exec()->SetAccountWallet_Name(ACCT_ID, SIGNER_NYM_ID, ACCT_NEW_NAME);
}

int64_t OTAPI_Wrap::GetAccountWallet_Balance(const std::string & THE_ID)
{
    return Exec()->GetAccountWallet_Balance(THE_ID);
}

std::string OTAPI_Wrap::GetAccountWallet_Type(const std::string & THE_ID)
{
    return Exec()->GetAccountWallet_Type(THE_ID);
}

std::string OTAPI_Wrap::GetAccountWallet_AssetTypeID(const std::string & THE_ID)
{
    return Exec()->GetAccountWallet_AssetTypeID(THE_ID);
}

std::string OTAPI_Wrap::GetAccountWallet_ServerID(const std::string & THE_ID)
{
    return Exec()->GetAccountWallet_ServerID(THE_ID);
}

std::string OTAPI_Wrap::GetAccountWallet_NymID(const std::string & THE_ID)
{
    return Exec()->GetAccountWallet_NymID(THE_ID);
}

std::string OTAPI_Wrap::WriteCheque(const std::string & SERVER_ID, const int64_t & CHEQUE_AMOUNT, const time_t & VALID_FROM, const time_t & VALID_TO, const std::string & SENDER_ACCT_ID, const std::string & SENDER_USER_ID, const std::string & CHEQUE_MEMO, const std::string & RECIPIENT_USER_ID)
{
    return Exec()->WriteCheque(SERVER_ID, CHEQUE_AMOUNT, VALID_FROM, VALID_TO, SENDER_ACCT_ID, SENDER_USER_ID, CHEQUE_MEMO, RECIPIENT_USER_ID);
}

bool OTAPI_Wrap::DiscardCheque(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & THE_CHEQUE)
{
    return Exec()->DiscardCheque(SERVER_ID, USER_ID, ACCT_ID, THE_CHEQUE);
}

std::string OTAPI_Wrap::ProposePaymentPlan(const std::string & SERVER_ID, const time_t & VALID_FROM, const time_t & VALID_TO, const std::string & SENDER_ACCT_ID, const std::string & SENDER_USER_ID, const std::string & PLAN_CONSIDERATION, const std::string & RECIPIENT_ACCT_ID, const std::string & RECIPIENT_USER_ID, const int64_t & INITIAL_PAYMENT_AMOUNT, const time_t & INITIAL_PAYMENT_DELAY, const int64_t & PAYMENT_PLAN_AMOUNT, const time_t & PAYMENT_PLAN_DELAY, const time_t & PAYMENT_PLAN_PERIOD, const time_t & PAYMENT_PLAN_LENGTH, const int32_t & PAYMENT_PLAN_MAX_PAYMENTS)
{
    return Exec()->ProposePaymentPlan(SERVER_ID, VALID_FROM, VALID_TO, SENDER_ACCT_ID, SENDER_USER_ID, PLAN_CONSIDERATION, RECIPIENT_ACCT_ID, RECIPIENT_USER_ID, INITIAL_PAYMENT_AMOUNT, INITIAL_PAYMENT_DELAY, PAYMENT_PLAN_AMOUNT, PAYMENT_PLAN_DELAY, PAYMENT_PLAN_PERIOD, PAYMENT_PLAN_LENGTH, PAYMENT_PLAN_MAX_PAYMENTS);
}

std::string OTAPI_Wrap::EasyProposePlan(const std::string & SERVER_ID, const std::string & DATE_RANGE, const std::string & SENDER_ACCT_ID, const std::string & SENDER_USER_ID, const std::string & PLAN_CONSIDERATION, const std::string & RECIPIENT_ACCT_ID, const std::string & RECIPIENT_USER_ID, const std::string & INITIAL_PAYMENT, const std::string & PAYMENT_PLAN, const std::string & PLAN_EXPIRY)
{
    return Exec()->EasyProposePlan(SERVER_ID, DATE_RANGE, SENDER_ACCT_ID, SENDER_USER_ID, PLAN_CONSIDERATION, RECIPIENT_ACCT_ID, RECIPIENT_USER_ID, INITIAL_PAYMENT, PAYMENT_PLAN, PLAN_EXPIRY);
}

std::string OTAPI_Wrap::ConfirmPaymentPlan(const std::string & SERVER_ID, const std::string & SENDER_USER_ID, const std::string & SENDER_ACCT_ID, const std::string & RECIPIENT_USER_ID, const std::string & PAYMENT_PLAN)
{
    return Exec()->ConfirmPaymentPlan(SERVER_ID, SENDER_USER_ID, SENDER_ACCT_ID, RECIPIENT_USER_ID, PAYMENT_PLAN);
}

std::string OTAPI_Wrap::Create_SmartContract(const std::string & SIGNER_NYM_ID, const time_t & VALID_FROM, const time_t & VALID_TO)
{
    return Exec()->Create_SmartContract(SIGNER_NYM_ID, VALID_FROM, VALID_TO);
}

std::string OTAPI_Wrap::SmartContract_AddBylaw(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME)
{
    return Exec()->SmartContract_AddBylaw(THE_CONTRACT, SIGNER_NYM_ID, BYLAW_NAME);
}

std::string OTAPI_Wrap::SmartContract_AddClause(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & CLAUSE_NAME, const std::string & SOURCE_CODE)
{
    return Exec()->SmartContract_AddClause(THE_CONTRACT, SIGNER_NYM_ID, BYLAW_NAME, CLAUSE_NAME, SOURCE_CODE);
}

std::string OTAPI_Wrap::SmartContract_AddVariable(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & VAR_NAME, const std::string & VAR_ACCESS, const std::string & VAR_TYPE, const std::string & VAR_VALUE)
{
    return Exec()->SmartContract_AddVariable(THE_CONTRACT, SIGNER_NYM_ID, BYLAW_NAME, VAR_NAME, VAR_ACCESS, VAR_TYPE, VAR_VALUE);
}

std::string OTAPI_Wrap::SmartContract_AddCallback(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & CALLBACK_NAME, const std::string & CLAUSE_NAME)
{
    return Exec()->SmartContract_AddCallback(THE_CONTRACT, SIGNER_NYM_ID, BYLAW_NAME, CALLBACK_NAME, CLAUSE_NAME);
}

std::string OTAPI_Wrap::SmartContract_AddHook(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & HOOK_NAME, const std::string & CLAUSE_NAME)
{
    return Exec()->SmartContract_AddHook(THE_CONTRACT, SIGNER_NYM_ID, BYLAW_NAME, HOOK_NAME, CLAUSE_NAME);
}

std::string OTAPI_Wrap::SmartContract_AddParty(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & PARTY_NAME, const std::string & AGENT_NAME)
{
    return Exec()->SmartContract_AddParty(THE_CONTRACT, SIGNER_NYM_ID, PARTY_NAME, AGENT_NAME);
}

std::string OTAPI_Wrap::SmartContract_AddAccount(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & PARTY_NAME, const std::string & ACCT_NAME, const std::string & ASSET_TYPE_ID)
{
    return Exec()->SmartContract_AddAccount(THE_CONTRACT, SIGNER_NYM_ID, PARTY_NAME, ACCT_NAME, ASSET_TYPE_ID);
}

int32_t OTAPI_Wrap::SmartContract_CountNumsNeeded(const std::string & THE_CONTRACT, const std::string & AGENT_NAME)
{
    return Exec()->SmartContract_CountNumsNeeded(THE_CONTRACT, AGENT_NAME);
}

std::string OTAPI_Wrap::SmartContract_ConfirmAccount(const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & PARTY_NAME, const std::string & ACCT_NAME, const std::string & AGENT_NAME, const std::string & ACCT_ID)
{
    return Exec()->SmartContract_ConfirmAccount(THE_CONTRACT, SIGNER_NYM_ID, PARTY_NAME, ACCT_NAME, AGENT_NAME, ACCT_ID);
}

std::string OTAPI_Wrap::SmartContract_ConfirmParty(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & NYM_ID)
{
    return Exec()->SmartContract_ConfirmParty(THE_CONTRACT, PARTY_NAME, NYM_ID);
}

bool OTAPI_Wrap::Smart_AreAllPartiesConfirmed(const std::string & THE_CONTRACT)
{
    return Exec()->Smart_AreAllPartiesConfirmed(THE_CONTRACT);
}

bool OTAPI_Wrap::Smart_IsPartyConfirmed(const std::string & THE_CONTRACT, const std::string & PARTY_NAME)
{
    return Exec()->Smart_IsPartyConfirmed(THE_CONTRACT, PARTY_NAME);
}

int32_t OTAPI_Wrap::Smart_GetPartyCount(const std::string & THE_CONTRACT)
{
    return Exec()->Smart_GetPartyCount(THE_CONTRACT);
}

int32_t OTAPI_Wrap::Smart_GetBylawCount(const std::string & THE_CONTRACT)
{
    return Exec()->Smart_GetBylawCount(THE_CONTRACT);
}

std::string OTAPI_Wrap::Smart_GetPartyByIndex(const std::string & THE_CONTRACT, const int32_t & nIndex)
{
    return Exec()->Smart_GetPartyByIndex(THE_CONTRACT, nIndex);
}

std::string OTAPI_Wrap::Smart_GetBylawByIndex(const std::string & THE_CONTRACT, const int32_t & nIndex)
{
    return Exec()->Smart_GetBylawByIndex(THE_CONTRACT, nIndex);
}

std::string OTAPI_Wrap::Bylaw_GetLanguage(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return Exec()->Bylaw_GetLanguage(THE_CONTRACT, BYLAW_NAME);
}

int32_t OTAPI_Wrap::Bylaw_GetClauseCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return Exec()->Bylaw_GetClauseCount(THE_CONTRACT, BYLAW_NAME);
}

int32_t OTAPI_Wrap::Bylaw_GetVariableCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return Exec()->Bylaw_GetVariableCount(THE_CONTRACT, BYLAW_NAME);
}

int32_t OTAPI_Wrap::Bylaw_GetHookCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return Exec()->Bylaw_GetHookCount(THE_CONTRACT, BYLAW_NAME);
}

int32_t OTAPI_Wrap::Bylaw_GetCallbackCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return Exec()->Bylaw_GetCallbackCount(THE_CONTRACT, BYLAW_NAME);
}

std::string OTAPI_Wrap::Clause_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex)
{
    return Exec()->Clause_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}

std::string OTAPI_Wrap::Clause_GetContents(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & CLAUSE_NAME)
{
    return Exec()->Clause_GetContents(THE_CONTRACT, BYLAW_NAME, CLAUSE_NAME);
}

std::string OTAPI_Wrap::Variable_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex)
{
    return Exec()->Variable_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}

std::string OTAPI_Wrap::Variable_GetType(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME)
{
    return Exec()->Variable_GetType(THE_CONTRACT, BYLAW_NAME, VARIABLE_NAME);
}

std::string OTAPI_Wrap::Variable_GetAccess(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME)
{
    return Exec()->Variable_GetAccess(THE_CONTRACT, BYLAW_NAME, VARIABLE_NAME);
}

std::string OTAPI_Wrap::Variable_GetContents(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME)
{
    return Exec()->Variable_GetContents(THE_CONTRACT, BYLAW_NAME, VARIABLE_NAME);
}

std::string OTAPI_Wrap::Hook_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex)
{
    return Exec()->Hook_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}

int32_t OTAPI_Wrap::Hook_GetClauseCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & HOOK_NAME)
{
    return Exec()->Hook_GetClauseCount(THE_CONTRACT, BYLAW_NAME, HOOK_NAME);
}

std::string OTAPI_Wrap::Hook_GetClauseAtIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & HOOK_NAME, const int32_t & nIndex)
{
    return Exec()->Hook_GetClauseAtIndex(THE_CONTRACT, BYLAW_NAME, HOOK_NAME, nIndex);
}

std::string OTAPI_Wrap::Callback_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex)
{
    return Exec()->Callback_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}

std::string OTAPI_Wrap::Callback_GetClause(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & CALLBACK_NAME)
{
    return Exec()->Callback_GetClause(THE_CONTRACT, BYLAW_NAME, CALLBACK_NAME);
}

int32_t OTAPI_Wrap::Party_GetAcctCount(const std::string & THE_CONTRACT, const std::string & PARTY_NAME)
{
    return Exec()->Party_GetAcctCount(THE_CONTRACT, PARTY_NAME);
}

int32_t OTAPI_Wrap::Party_GetAgentCount(const std::string & THE_CONTRACT, const std::string & PARTY_NAME)
{
    return Exec()->Party_GetAgentCount(THE_CONTRACT, PARTY_NAME);
}

std::string OTAPI_Wrap::Party_GetID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME)
{
    return Exec()->Party_GetID(THE_CONTRACT, PARTY_NAME);
}

std::string OTAPI_Wrap::Party_GetAcctNameByIndex(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const int32_t & nIndex)
{
    return Exec()->Party_GetAcctNameByIndex(THE_CONTRACT, PARTY_NAME, nIndex);
}

std::string OTAPI_Wrap::Party_GetAcctID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME)
{
    return Exec()->Party_GetAcctID(THE_CONTRACT, PARTY_NAME, ACCT_NAME);
}

std::string OTAPI_Wrap::Party_GetAcctAssetID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME)
{
    return Exec()->Party_GetAcctAssetID(THE_CONTRACT, PARTY_NAME, ACCT_NAME);
}

std::string OTAPI_Wrap::Party_GetAcctAgentName(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME)
{
    return Exec()->Party_GetAcctAgentName(THE_CONTRACT, PARTY_NAME, ACCT_NAME);
}

std::string OTAPI_Wrap::Party_GetAgentNameByIndex(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const int32_t & nIndex)
{
    return Exec()->Party_GetAgentNameByIndex(THE_CONTRACT, PARTY_NAME, nIndex);
}

std::string OTAPI_Wrap::Party_GetAgentID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & AGENT_NAME)
{
    return Exec()->Party_GetAgentID(THE_CONTRACT, PARTY_NAME, AGENT_NAME);
}

int32_t OTAPI_Wrap::activateSmartContract(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_SMART_CONTRACT)
{
    return Exec()->activateSmartContract(SERVER_ID, USER_ID, THE_SMART_CONTRACT);
}

int32_t OTAPI_Wrap::triggerClause(const std::string & SERVER_ID, const std::string & USER_ID, const int64_t & TRANSACTION_NUMBER, const std::string & CLAUSE_NAME, const std::string & STR_PARAM)
{
    return Exec()->triggerClause(SERVER_ID, USER_ID, TRANSACTION_NUMBER, CLAUSE_NAME, STR_PARAM);
}

bool OTAPI_Wrap::Msg_HarvestTransactionNumbers(const std::string & THE_MESSAGE, const std::string & USER_ID, const bool & bHarvestingForRetry, const bool & bReplyWasSuccess, const bool & bReplyWasFailure, const bool & bTransactionWasSuccess, const bool & bTransactionWasFailure)
{
    return Exec()->Msg_HarvestTransactionNumbers(THE_MESSAGE, USER_ID, bHarvestingForRetry, bReplyWasSuccess, bReplyWasFailure, bTransactionWasSuccess, bTransactionWasFailure);
}

std::string OTAPI_Wrap::LoadPubkey_Encryption(const std::string & USER_ID)
{
    return Exec()->LoadPubkey_Encryption(USER_ID);
}

std::string OTAPI_Wrap::LoadPubkey_Signing(const std::string & USER_ID)
{
    return Exec()->LoadPubkey_Signing(USER_ID);
}

std::string OTAPI_Wrap::LoadUserPubkey_Encryption(const std::string & USER_ID)
{
    return Exec()->LoadUserPubkey_Encryption(USER_ID);
}

std::string OTAPI_Wrap::LoadUserPubkey_Signing(const std::string & USER_ID)
{
    return Exec()->LoadUserPubkey_Signing(USER_ID);
}

bool OTAPI_Wrap::VerifyUserPrivateKey(const std::string & USER_ID)
{
    return Exec()->VerifyUserPrivateKey(USER_ID);
}

bool OTAPI_Wrap::Mint_IsStillGood(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID)
{
    return Exec()->Mint_IsStillGood(SERVER_ID, ASSET_TYPE_ID);
}

std::string OTAPI_Wrap::LoadMint(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID)
{
    return Exec()->LoadMint(SERVER_ID, ASSET_TYPE_ID);
}

std::string OTAPI_Wrap::LoadAssetContract(const std::string & ASSET_TYPE_ID)
{
    return Exec()->LoadAssetContract(ASSET_TYPE_ID);
}

std::string OTAPI_Wrap::LoadServerContract(const std::string & SERVER_ID)
{
    return Exec()->LoadServerContract(SERVER_ID);
}

std::string OTAPI_Wrap::LoadAssetAccount(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->LoadAssetAccount(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::Nymbox_GetReplyNotice(const std::string & SERVER_ID, const std::string & USER_ID, const int64_t & REQUEST_NUMBER)
{
    return Exec()->Nymbox_GetReplyNotice(SERVER_ID, USER_ID, REQUEST_NUMBER);
}

bool OTAPI_Wrap::HaveAlreadySeenReply(const std::string & SERVER_ID, const std::string & USER_ID, const int64_t & REQUEST_NUMBER)
{
    return Exec()->HaveAlreadySeenReply(SERVER_ID, USER_ID, REQUEST_NUMBER);
}

std::string OTAPI_Wrap::LoadNymbox(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->LoadNymbox(SERVER_ID, USER_ID);
}

std::string OTAPI_Wrap::LoadNymboxNoVerify(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->LoadNymboxNoVerify(SERVER_ID, USER_ID);
}

std::string OTAPI_Wrap::LoadInbox(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->LoadInbox(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::LoadInboxNoVerify(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->LoadInboxNoVerify(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::LoadOutbox(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->LoadOutbox(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::LoadOutboxNoVerify(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->LoadOutboxNoVerify(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::LoadPaymentInbox(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->LoadPaymentInbox(SERVER_ID, USER_ID);
}

std::string OTAPI_Wrap::LoadPaymentInboxNoVerify(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->LoadPaymentInboxNoVerify(SERVER_ID, USER_ID);
}

std::string OTAPI_Wrap::LoadRecordBox(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->LoadRecordBox(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::LoadRecordBoxNoVerify(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID)
{
    return Exec()->LoadRecordBoxNoVerify(SERVER_ID, USER_ID, ACCOUNT_ID);
}

std::string OTAPI_Wrap::LoadExpiredBox(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->LoadExpiredBox(SERVER_ID, USER_ID);
}

std::string OTAPI_Wrap::LoadExpiredBoxNoVerify(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->LoadExpiredBoxNoVerify(SERVER_ID, USER_ID);
}

bool OTAPI_Wrap::RecordPayment(const std::string & SERVER_ID, const std::string & USER_ID, const bool & bIsInbox, const int32_t & nIndex, const bool & bSaveCopy)
{
    return Exec()->RecordPayment(SERVER_ID, USER_ID, bIsInbox, nIndex, bSaveCopy);
}

bool OTAPI_Wrap::ClearRecord(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const int32_t & nIndex, const bool & bClearAll)
{
    return Exec()->ClearRecord(SERVER_ID, USER_ID, ACCOUNT_ID, nIndex, bClearAll);
}

bool OTAPI_Wrap::ClearExpired(const std::string & SERVER_ID, const std::string & USER_ID, const int32_t & nIndex, const bool & bClearAll)
{
    return Exec()->ClearExpired(SERVER_ID, USER_ID, nIndex, bClearAll);
}

int32_t OTAPI_Wrap::Ledger_GetCount(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER)
{
    return Exec()->Ledger_GetCount(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER);
}

std::string OTAPI_Wrap::Ledger_CreateResponse(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & ORIGINAL_LEDGER)
{
    return Exec()->Ledger_CreateResponse(SERVER_ID, USER_ID, ACCOUNT_ID, ORIGINAL_LEDGER);
}

std::string OTAPI_Wrap::Ledger_GetTransactionByIndex(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int32_t & nIndex)
{
    return Exec()->Ledger_GetTransactionByIndex(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, nIndex);
}

std::string OTAPI_Wrap::Ledger_GetTransactionByID(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int64_t & TRANSACTION_NUMBER)
{
    return Exec()->Ledger_GetTransactionByID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, TRANSACTION_NUMBER);
}

std::string OTAPI_Wrap::Ledger_GetInstrument(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int32_t & nIndex)
{
    return Exec()->Ledger_GetInstrument(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, nIndex);
}

int64_t OTAPI_Wrap::Ledger_GetTransactionIDByIndex(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int32_t & nIndex)
{
    return Exec()->Ledger_GetTransactionIDByIndex(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, nIndex);
}

std::string OTAPI_Wrap::Ledger_AddTransaction(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const std::string & THE_TRANSACTION)
{
    return Exec()->Ledger_AddTransaction(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, THE_TRANSACTION);
}

std::string OTAPI_Wrap::Transaction_CreateResponse(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const std::string & THE_TRANSACTION, const bool & BOOL_DO_I_ACCEPT)
{
    return Exec()->Transaction_CreateResponse(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, THE_TRANSACTION, BOOL_DO_I_ACCEPT);
}

std::string OTAPI_Wrap::Ledger_FinalizeResponse(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER)
{
    return Exec()->Ledger_FinalizeResponse(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER);
}

std::string OTAPI_Wrap::Transaction_GetVoucher(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetVoucher(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

std::string OTAPI_Wrap::Transaction_GetSenderUserID(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetSenderUserID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

std::string OTAPI_Wrap::Transaction_GetRecipientUserID(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetRecipientUserID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

std::string OTAPI_Wrap::Transaction_GetSenderAcctID(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetSenderAcctID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

std::string OTAPI_Wrap::Transaction_GetRecipientAcctID(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetRecipientAcctID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

std::string OTAPI_Wrap::Pending_GetNote(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Pending_GetNote(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

int64_t OTAPI_Wrap::Transaction_GetAmount(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetAmount(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

int64_t OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetDisplayReferenceToNum(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

std::string OTAPI_Wrap::Transaction_GetType(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetType(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

int64_t OTAPI_Wrap::ReplyNotice_GetRequestNum(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->ReplyNotice_GetRequestNum(SERVER_ID, USER_ID, THE_TRANSACTION);
}

time_t OTAPI_Wrap::Transaction_GetDateSigned(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetDateSigned(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

OT_BOOL OTAPI_Wrap::Transaction_GetSuccess(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetSuccess(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

OT_BOOL OTAPI_Wrap::Transaction_IsCanceled(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_IsCanceled(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

OT_BOOL OTAPI_Wrap::Transaction_GetBalanceAgreementSuccess(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION)
{
    return Exec()->Transaction_GetBalanceAgreementSuccess(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
}

OT_BOOL OTAPI_Wrap::Message_GetBalanceAgreementSuccess(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetBalanceAgreementSuccess(SERVER_ID, USER_ID, ACCOUNT_ID, THE_MESSAGE);
}

bool OTAPI_Wrap::SavePurse(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID, const std::string & THE_PURSE)
{
    return Exec()->SavePurse(SERVER_ID, ASSET_TYPE_ID, USER_ID, THE_PURSE);
}

std::string OTAPI_Wrap::LoadPurse(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID)
{
    return Exec()->LoadPurse(SERVER_ID, ASSET_TYPE_ID, USER_ID);
}

int64_t OTAPI_Wrap::Purse_GetTotalValue(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_PURSE)
{
    return Exec()->Purse_GetTotalValue(SERVER_ID, ASSET_TYPE_ID, THE_PURSE);
}

int32_t OTAPI_Wrap::Purse_Count(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_PURSE)
{
    return Exec()->Purse_Count(SERVER_ID, ASSET_TYPE_ID, THE_PURSE);
}

bool OTAPI_Wrap::Purse_HasPassword(const std::string & SERVER_ID, const std::string & THE_PURSE)
{
    return Exec()->Purse_HasPassword(SERVER_ID, THE_PURSE);
}

std::string OTAPI_Wrap::CreatePurse(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & OWNER_ID, const std::string & SIGNER_ID)
{
    return Exec()->CreatePurse(SERVER_ID, ASSET_TYPE_ID, OWNER_ID, SIGNER_ID);
}

std::string OTAPI_Wrap::CreatePurse_Passphrase(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & SIGNER_ID)
{
    return Exec()->CreatePurse_Passphrase(SERVER_ID, ASSET_TYPE_ID, SIGNER_ID);
}

std::string OTAPI_Wrap::Purse_Peek(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & OWNER_ID, const std::string & THE_PURSE)
{
    return Exec()->Purse_Peek(SERVER_ID, ASSET_TYPE_ID, OWNER_ID, THE_PURSE);
}

std::string OTAPI_Wrap::Purse_Pop(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & OWNER_OR_SIGNER_ID, const std::string & THE_PURSE)
{
    return Exec()->Purse_Pop(SERVER_ID, ASSET_TYPE_ID, OWNER_OR_SIGNER_ID, THE_PURSE);
}

std::string OTAPI_Wrap::Purse_Empty(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & SIGNER_ID, const std::string & THE_PURSE)
{
    return Exec()->Purse_Empty(SERVER_ID, ASSET_TYPE_ID, SIGNER_ID, THE_PURSE);
}

std::string OTAPI_Wrap::Purse_Push(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & SIGNER_ID, const std::string & OWNER_ID, const std::string & THE_PURSE, const std::string & THE_TOKEN)
{
    return Exec()->Purse_Push(SERVER_ID, ASSET_TYPE_ID, SIGNER_ID, OWNER_ID, THE_PURSE, THE_TOKEN);
}

bool OTAPI_Wrap::Wallet_ImportPurse(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID, const std::string & THE_PURSE)
{
    return Exec()->Wallet_ImportPurse(SERVER_ID, ASSET_TYPE_ID, USER_ID, THE_PURSE);
}

int32_t OTAPI_Wrap::exchangePurse(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID, const std::string & THE_PURSE)
{
    return Exec()->exchangePurse(SERVER_ID, ASSET_TYPE_ID, USER_ID, THE_PURSE);
}

std::string OTAPI_Wrap::Token_ChangeOwner(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN, const std::string & SIGNER_NYM_ID, const std::string & OLD_OWNER, const std::string & NEW_OWNER)
{
    return Exec()->Token_ChangeOwner(SERVER_ID, ASSET_TYPE_ID, THE_TOKEN, SIGNER_NYM_ID, OLD_OWNER, NEW_OWNER);
}

std::string OTAPI_Wrap::Token_GetID(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN)
{
    return Exec()->Token_GetID(SERVER_ID, ASSET_TYPE_ID, THE_TOKEN);
}

int64_t OTAPI_Wrap::Token_GetDenomination(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN)
{
    return Exec()->Token_GetDenomination(SERVER_ID, ASSET_TYPE_ID, THE_TOKEN);
}

int32_t OTAPI_Wrap::Token_GetSeries(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN)
{
    return Exec()->Token_GetSeries(SERVER_ID, ASSET_TYPE_ID, THE_TOKEN);
}

time_t OTAPI_Wrap::Token_GetValidFrom(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN)
{
    return Exec()->Token_GetValidFrom(SERVER_ID, ASSET_TYPE_ID, THE_TOKEN);
}

time_t OTAPI_Wrap::Token_GetValidTo(const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN)
{
    return Exec()->Token_GetValidTo(SERVER_ID, ASSET_TYPE_ID, THE_TOKEN);
}

std::string OTAPI_Wrap::Token_GetAssetID(const std::string & THE_TOKEN)
{
    return Exec()->Token_GetAssetID(THE_TOKEN);
}

std::string OTAPI_Wrap::Token_GetServerID(const std::string & THE_TOKEN)
{
    return Exec()->Token_GetServerID(THE_TOKEN);
}

bool OTAPI_Wrap::IsBasketCurrency(const std::string & ASSET_TYPE_ID)
{
    return Exec()->IsBasketCurrency(ASSET_TYPE_ID);
}

int32_t OTAPI_Wrap::Basket_GetMemberCount(const std::string & ASSET_TYPE_ID)
{
    return Exec()->Basket_GetMemberCount(ASSET_TYPE_ID);
}

std::string OTAPI_Wrap::Basket_GetMemberType(const std::string & BASKET_ASSET_TYPE_ID, const int32_t & nIndex)
{
    return Exec()->Basket_GetMemberType(BASKET_ASSET_TYPE_ID, nIndex);
}

int64_t OTAPI_Wrap::Basket_GetMinimumTransferAmount(const std::string & BASKET_ASSET_TYPE_ID)
{
    return Exec()->Basket_GetMinimumTransferAmount(BASKET_ASSET_TYPE_ID);
}

int64_t OTAPI_Wrap::Basket_GetMemberMinimumTransferAmount(const std::string & BASKET_ASSET_TYPE_ID, const int32_t & nIndex)
{
    return Exec()->Basket_GetMemberMinimumTransferAmount(BASKET_ASSET_TYPE_ID, nIndex);
}

int32_t OTAPI_Wrap::checkServerID(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->checkServerID(SERVER_ID, USER_ID);
}

int32_t OTAPI_Wrap::createUserAccount(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->createUserAccount(SERVER_ID, USER_ID);
}

int32_t OTAPI_Wrap::deleteUserAccount(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->deleteUserAccount(SERVER_ID, USER_ID);
}

int64_t OTAPI_Wrap::Message_GetUsageCredits(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetUsageCredits(THE_MESSAGE);
}

int32_t OTAPI_Wrap::usageCredits(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_CHECK, const int64_t & ADJUSTMENT)
{
    return Exec()->usageCredits(SERVER_ID, USER_ID, USER_ID_CHECK, ADJUSTMENT);
}

int32_t OTAPI_Wrap::checkUser(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_CHECK)
{
    return Exec()->checkUser(SERVER_ID, USER_ID, USER_ID_CHECK);
}

int32_t OTAPI_Wrap::sendUserMessage(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_RECIPIENT, const std::string & RECIPIENT_PUBKEY, const std::string & THE_MESSAGE)
{
    return Exec()->sendUserMessage(SERVER_ID, USER_ID, USER_ID_RECIPIENT, RECIPIENT_PUBKEY, THE_MESSAGE);
}

int32_t OTAPI_Wrap::sendUserInstrument(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_RECIPIENT, const std::string & RECIPIENT_PUBKEY, const std::string & THE_INSTRUMENT, const std::string & INSTRUMENT_FOR_SENDER)
{
    return Exec()->sendUserInstrument(SERVER_ID, USER_ID, USER_ID_RECIPIENT, RECIPIENT_PUBKEY, THE_INSTRUMENT, INSTRUMENT_FOR_SENDER);
}

int32_t OTAPI_Wrap::getRequest(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->getRequest(SERVER_ID, USER_ID);
}

int32_t OTAPI_Wrap::issueAssetType(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_CONTRACT)
{
    return Exec()->issueAssetType(SERVER_ID, USER_ID, THE_CONTRACT);
}

int32_t OTAPI_Wrap::getContract(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ID)
{
    return Exec()->getContract(SERVER_ID, USER_ID, ASSET_ID);
}

int32_t OTAPI_Wrap::getMint(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ID)
{
    return Exec()->getMint(SERVER_ID, USER_ID, ASSET_ID);
}

int32_t OTAPI_Wrap::createAssetAccount(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ID)
{
    return Exec()->createAssetAccount(SERVER_ID, USER_ID, ASSET_ID);
}

int32_t OTAPI_Wrap::getAccount(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID)
{
    return Exec()->getAccount(SERVER_ID, USER_ID, ACCT_ID);
}

int32_t OTAPI_Wrap::getAccountFiles(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID)
{
    return Exec()->getAccountFiles(SERVER_ID, USER_ID, ACCT_ID);
}

std::string OTAPI_Wrap::GenerateBasketCreation(const std::string & USER_ID, const int64_t & MINIMUM_TRANSFER)
{
    return Exec()->GenerateBasketCreation(USER_ID, MINIMUM_TRANSFER);
}

std::string OTAPI_Wrap::AddBasketCreationItem(const std::string & USER_ID, const std::string & THE_BASKET, const std::string & ASSET_TYPE_ID, const int64_t & MINIMUM_TRANSFER)
{
    return Exec()->AddBasketCreationItem(USER_ID, THE_BASKET, ASSET_TYPE_ID, MINIMUM_TRANSFER);
}

int32_t OTAPI_Wrap::issueBasket(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_BASKET)
{
    return Exec()->issueBasket(SERVER_ID, USER_ID, THE_BASKET);
}

std::string OTAPI_Wrap::GenerateBasketExchange(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & BASKET_ASSET_TYPE_ID, const std::string & BASKET_ASSET_ACCT_ID, const int32_t & TRANSFER_MULTIPLE)
{
    return Exec()->GenerateBasketExchange(SERVER_ID, USER_ID, BASKET_ASSET_TYPE_ID, BASKET_ASSET_ACCT_ID, TRANSFER_MULTIPLE);
}

std::string OTAPI_Wrap::AddBasketExchangeItem(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_BASKET, const std::string & ASSET_TYPE_ID, const std::string & ASSET_ACCT_ID)
{
    return Exec()->AddBasketExchangeItem(SERVER_ID, USER_ID, THE_BASKET, ASSET_TYPE_ID, ASSET_ACCT_ID);
}

int32_t OTAPI_Wrap::exchangeBasket(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & BASKET_ASSET_ID, const std::string & THE_BASKET, const bool & BOOL_EXCHANGE_IN_OR_OUT)
{
    return Exec()->exchangeBasket(SERVER_ID, USER_ID, BASKET_ASSET_ID, THE_BASKET, BOOL_EXCHANGE_IN_OR_OUT);
}

int32_t OTAPI_Wrap::getTransactionNumber(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->getTransactionNumber(SERVER_ID, USER_ID);
}

int32_t OTAPI_Wrap::notarizeWithdrawal(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const int64_t & AMOUNT)
{
    return Exec()->notarizeWithdrawal(SERVER_ID, USER_ID, ACCT_ID, AMOUNT);
}

int32_t OTAPI_Wrap::notarizeDeposit(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & THE_PURSE)
{
    return Exec()->notarizeDeposit(SERVER_ID, USER_ID, ACCT_ID, THE_PURSE);
}

int32_t OTAPI_Wrap::notarizeTransfer(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_FROM, const std::string & ACCT_TO, const int64_t & AMOUNT, const std::string & NOTE)
{
    return Exec()->notarizeTransfer(SERVER_ID, USER_ID, ACCT_FROM, ACCT_TO, AMOUNT, NOTE);
}

int32_t OTAPI_Wrap::getInbox(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID)
{
    return Exec()->getInbox(SERVER_ID, USER_ID, ACCT_ID);
}

int32_t OTAPI_Wrap::getNymbox(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->getNymbox(SERVER_ID, USER_ID);
}

int32_t OTAPI_Wrap::getOutbox(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID)
{
    return Exec()->getOutbox(SERVER_ID, USER_ID, ACCT_ID);
}

int32_t OTAPI_Wrap::processInbox(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & ACCT_LEDGER)
{
    return Exec()->processInbox(SERVER_ID, USER_ID, ACCT_ID, ACCT_LEDGER);
}

int32_t OTAPI_Wrap::processNymbox(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->processNymbox(SERVER_ID, USER_ID);
}

int32_t OTAPI_Wrap::withdrawVoucher(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & RECIPIENT_USER_ID, const std::string & CHEQUE_MEMO, const int64_t & AMOUNT)
{
    return Exec()->withdrawVoucher(SERVER_ID, USER_ID, ACCT_ID, RECIPIENT_USER_ID, CHEQUE_MEMO, AMOUNT);
}

int32_t OTAPI_Wrap::payDividend(const std::string & SERVER_ID, const std::string & ISSUER_USER_ID, const std::string & DIVIDEND_FROM_ACCT_ID, const std::string & SHARES_ASSET_TYPE_ID, const std::string & DIVIDEND_MEMO, const int64_t & AMOUNT_PER_SHARE)
{
    return Exec()->payDividend(SERVER_ID, ISSUER_USER_ID, DIVIDEND_FROM_ACCT_ID, SHARES_ASSET_TYPE_ID, DIVIDEND_MEMO, AMOUNT_PER_SHARE);
}

int32_t OTAPI_Wrap::depositCheque(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & THE_CHEQUE)
{
    return Exec()->depositCheque(SERVER_ID, USER_ID, ACCT_ID, THE_CHEQUE);
}

int32_t OTAPI_Wrap::depositPaymentPlan(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_PAYMENT_PLAN)
{
    return Exec()->depositPaymentPlan(SERVER_ID, USER_ID, THE_PAYMENT_PLAN);
}

int32_t OTAPI_Wrap::killMarketOffer(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ACCT_ID, const int64_t & TRANSACTION_NUMBER)
{
    return Exec()->killMarketOffer(SERVER_ID, USER_ID, ASSET_ACCT_ID, TRANSACTION_NUMBER);
}

int32_t OTAPI_Wrap::killPaymentPlan(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & FROM_ACCT_ID, const int64_t & TRANSACTION_NUMBER)
{
    return Exec()->killPaymentPlan(SERVER_ID, USER_ID, FROM_ACCT_ID, TRANSACTION_NUMBER);
}

int32_t OTAPI_Wrap::issueMarketOffer(const std::string & ASSET_ACCT_ID, const std::string & CURRENCY_ACCT_ID, const int64_t & MARKET_SCALE, const int64_t & MINIMUM_INCREMENT, const int64_t & TOTAL_ASSETS_ON_OFFER, const int64_t & PRICE_LIMIT, const bool & bBuyingOrSelling, const time_t & LIFESPAN_IN_SECONDS, const std::string & STOP_SIGN, const int64_t & ACTIVATION_PRICE)
{
    return Exec()->issueMarketOffer(ASSET_ACCT_ID, CURRENCY_ACCT_ID, MARKET_SCALE, MINIMUM_INCREMENT, TOTAL_ASSETS_ON_OFFER, PRICE_LIMIT, bBuyingOrSelling, LIFESPAN_IN_SECONDS, STOP_SIGN, ACTIVATION_PRICE);
}

int32_t OTAPI_Wrap::getMarketList(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->getMarketList(SERVER_ID, USER_ID);
}

int32_t OTAPI_Wrap::getMarketOffers(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & MARKET_ID, const int64_t & MAX_DEPTH)
{
    return Exec()->getMarketOffers(SERVER_ID, USER_ID, MARKET_ID, MAX_DEPTH);
}

int32_t OTAPI_Wrap::getMarketRecentTrades(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & MARKET_ID)
{
    return Exec()->getMarketRecentTrades(SERVER_ID, USER_ID, MARKET_ID);
}

int32_t OTAPI_Wrap::getNym_MarketOffers(const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->getNym_MarketOffers(SERVER_ID, USER_ID);
}

std::string OTAPI_Wrap::PopMessageBuffer(const int64_t & REQUEST_NUMBER, const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, USER_ID);
}

void OTAPI_Wrap::FlushMessageBuffer(void)
{
    return Exec()->FlushMessageBuffer();
}

std::string OTAPI_Wrap::GetSentMessage(const int64_t & REQUEST_NUMBER, const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->GetSentMessage(REQUEST_NUMBER, SERVER_ID, USER_ID);
}

bool OTAPI_Wrap::RemoveSentMessage(const int64_t & REQUEST_NUMBER, const std::string & SERVER_ID, const std::string & USER_ID)
{
    return Exec()->RemoveSentMessage(REQUEST_NUMBER, SERVER_ID, USER_ID);
}

void OTAPI_Wrap::FlushSentMessages(const bool & bHarvestingForRetry, const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_NYMBOX)
{
    return Exec()->FlushSentMessages(bHarvestingForRetry, SERVER_ID, USER_ID, THE_NYMBOX);
}

void OTAPI_Wrap::Sleep(const int64_t & MILLISECONDS)
{
    return Exec()->Sleep(MILLISECONDS);
}

bool OTAPI_Wrap::ResyncNymWithServer(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_MESSAGE)
{
    return Exec()->ResyncNymWithServer(SERVER_ID, USER_ID, THE_MESSAGE);
}

int32_t OTAPI_Wrap::queryAssetTypes(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ENCODED_MAP)
{
    return Exec()->queryAssetTypes(SERVER_ID, USER_ID, ENCODED_MAP);
}

std::string OTAPI_Wrap::Message_GetPayload(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetPayload(THE_MESSAGE);
}

std::string OTAPI_Wrap::Message_GetCommand(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetCommand(THE_MESSAGE);
}

std::string OTAPI_Wrap::Message_GetLedger(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetLedger(THE_MESSAGE);
}

std::string OTAPI_Wrap::Message_GetNewAssetTypeID(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetNewAssetTypeID(THE_MESSAGE);
}

std::string OTAPI_Wrap::Message_GetNewIssuerAcctID(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetNewIssuerAcctID(THE_MESSAGE);
}

std::string OTAPI_Wrap::Message_GetNewAcctID(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetNewAcctID(THE_MESSAGE);
}

std::string OTAPI_Wrap::Message_GetNymboxHash(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetNymboxHash(THE_MESSAGE);
}

OT_BOOL OTAPI_Wrap::Message_GetSuccess(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetSuccess(THE_MESSAGE);
}

int32_t OTAPI_Wrap::Message_GetDepth(const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetDepth(THE_MESSAGE);
}

OT_BOOL OTAPI_Wrap::Message_IsTransactionCanceled(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_MESSAGE)
{
    return Exec()->Message_IsTransactionCanceled(SERVER_ID, USER_ID, ACCOUNT_ID, THE_MESSAGE);
}

OT_BOOL OTAPI_Wrap::Message_GetTransactionSuccess(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_MESSAGE)
{
    return Exec()->Message_GetTransactionSuccess(SERVER_ID, USER_ID, ACCOUNT_ID, THE_MESSAGE);
}

bool OTAPI_Wrap::ConnectServer(const std::string & SERVER_ID, const std::string & USER_ID, const std::string & strCA_FILE, const std::string & strKEY_FILE, const std::string & strKEY_PASSWORD)
{
    return Exec()->ConnectServer(SERVER_ID, USER_ID, strCA_FILE, strKEY_FILE, strKEY_PASSWORD);
}

bool OTAPI_Wrap::ProcessSockets(void)
{
    return Exec()->ProcessSockets();
}
