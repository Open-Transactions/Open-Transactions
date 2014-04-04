/*************************************************************

OTAPI_Basic.cpp   --	A C++ wrapper class (named OTAPI_Basic)

This is a Direct sub-set of OTAPI_Wrap

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

#include <OTAPI_Basic.hpp>

#include <OTAPI.hpp>

#ifndef IMPORT
#define IMPORT
#endif

#include <OTAssert.hpp>
#include <OTLog.hpp>



OTAPI_Basic::OTAPI_Basic()
{

}

OTAPI_Basic::~OTAPI_Basic()
{

}


// **********************************************************************

bool OTAPI_Basic::AppStartup()
{
    static bool bInitialized = false;
    
    if (!bInitialized)
    {
        bInitialized = OTAPI_Wrap::AppInit(); // Call this once, when your App first starts up.
    }
    else
        OTLog::vError("OTAPI_Basic::AppStartup: FYI: You can only call this successfully *once* (and it's already been called.)\n");
    
	return bInitialized;
}
// -----------------------------------

bool OTAPI_Basic::AppShutdown()
{
    static bool bShutdown = false;
    
    if (!bShutdown)
    {
        bShutdown = OTAPI_Wrap::AppCleanup(); // Call this once, when your App is shutting down.
    }
    else
        OTLog::vError("OTAPI_Basic::AppShutdown: FYI: You can only call this successfully *once* (and it's already been called.)\n");
    
	return bShutdown;
}
// -----------------------------------

void OTAPI_Basic::SetAppBinaryFolder(const std::string & strFolder)
{
    OTAPI_Wrap::SetAppBinaryFolder(strFolder);
}
// -----------------------------------

void OTAPI_Basic::SetHomeFolder(const std::string & strFolder)
{
    OTAPI_Wrap::SetHomeFolder(strFolder);
}

// -----------------------------------

// NOTE: If you need to call SetAppBinaryFolder or SetHomeFolder, then you should probably
// take care of that before calling this function, since it will assume they are already set.
//
bool OTAPI_Basic::Init()
{
    // If this function fails, you can call it multiple times until it succeeds.
    //
    return (NULL != OTAPI_Wrap::OTAPI());    // Call this for each OTAPI context you use. (Currently a singleton.)
}
// -----------------------------------

bool OTAPI_Basic::SetWallet(const std::string & strWalletFilename)
{
	return OTAPI_Wrap::SetWallet(strWalletFilename);
}
// -----------------------------------

bool OTAPI_Basic::LoadWallet()
{
	return OTAPI_Wrap::LoadWallet();
}

// **********************************************************************


bool OTAPI_Basic::WalletExists()
{
	return OTAPI_Wrap::WalletExists();
}



bool OTAPI_Basic::SwitchWallet()
{
	return OTAPI_Wrap::SwitchWallet();
}

void OTAPI_Basic::Output(
	long nLogLevel,
	const std::string & strOutput
	)
{
	OTAPI_Wrap::Output(nLogLevel,strOutput);
}

std::string OTAPI_Basic::GetTime()
{
	//int64_t lTime = OTAPI_Wrap::StringToLong(OTAPI_Wrap::GetTime());
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::GetTime());
}

std::string OTAPI_Basic::NumList_Add(
	const std::string & strNumList,
	const std::string & strNumbers
	)
{
	if (strNumList.empty()) { OTLog::sError("%s: Null: %s passed in!\n", __FUNCTION__, "strNumList" ); OT_FAIL; }

	return OTAPI_Wrap::NumList_Add(strNumList,strNumbers);
}

std::string OTAPI_Basic::NumList_Remove(
	const std::string & strNumList,
	const std::string & strNumbers
	)
{
	if (strNumList.empty()) { OTLog::sError("%s: Null: %s passed in!\n", __FUNCTION__, "strNumList" ); OT_FAIL; }
	if (strNumbers.empty()) { OTLog::sError("%s: Null: %s passed in!\n", __FUNCTION__, "strNumbers" ); OT_FAIL; }

	return OTAPI_Wrap::NumList_Remove(strNumList,strNumbers);
}

bool OTAPI_Basic::NumList_VerifyQuery(
	const std::string & strNumList,
	const std::string & strNumbers
	)
{
	if (strNumList.empty()) { OTLog::sError("%s: Null: %s passed in!\n", __FUNCTION__, "strNumList" ); OT_FAIL; }
	if (strNumbers.empty()) { OTLog::sError("%s: Null: %s passed in!\n", __FUNCTION__, "strNumbers" ); OT_FAIL; }

	return OTAPI_Wrap::NumList_VerifyQuery(strNumList,strNumbers);
}

bool OTAPI_Basic::NumList_VerifyAll(
	const std::string & strNumList,
	const std::string & strNumbers
	)
{
	if (strNumList.empty()) { OTLog::sError("%s: Null: %s passed in!\n", __FUNCTION__, "strNumList" ); OT_FAIL; }
	if (strNumbers.empty()) { OTLog::sError("%s: Null: %s passed in!\n", __FUNCTION__, "strNumbers" ); OT_FAIL; }

	return OTAPI_Wrap::NumList_VerifyAll(strNumList,strNumbers);
}

long OTAPI_Basic::NumList_Count(
	const std::string & strNumList
	)
{
	return OTAPI_Wrap::NumList_Count(strNumList);
}

std::string OTAPI_Basic::Encode(
	const std::string & strPlaintext,
	const bool & bLineBreaks
	)
{
	return OTAPI_Wrap::Encode(strPlaintext,bLineBreaks);
}

std::string OTAPI_Basic::Decode(
	const std::string & strEncoded,
	const bool & bLineBreaks
	)
{
	return OTAPI_Wrap::Decode(
		strEncoded,
		bLineBreaks
		);
}

std::string OTAPI_Basic::Encrypt(
	const std::string & RECIPIENT_NYM_ID,
	const std::string & strPlainText
	)
{
	return OTAPI_Wrap::Encrypt(
		RECIPIENT_NYM_ID,
		strPlainText
		);
}

std::string OTAPI_Basic::Decrypt(
	const std::string & RECIPIENT_NYM_ID,
	const std::string & strCiphertext
	)
{
	return OTAPI_Wrap::Decrypt(
		RECIPIENT_NYM_ID,
		strCiphertext
		);
}

std::string OTAPI_Basic::CreateSymmetricKey()
{
	return OTAPI_Wrap::CreateSymmetricKey();
}

std::string OTAPI_Basic::SymmetricEncrypt(
	const std::string & SYMMETRIC_KEY,
	const std::string & PLAINTEXT
	)
{
	return OTAPI_Wrap::SymmetricEncrypt(
		SYMMETRIC_KEY,
		PLAINTEXT
		);
}

std::string OTAPI_Basic::SymmetricDecrypt(
	const std::string & SYMMETRIC_KEY,
	const std::string & CIPHERTEXT_ENVELOPE
	)
{
	return OTAPI_Wrap::SymmetricDecrypt(
		SYMMETRIC_KEY,
		CIPHERTEXT_ENVELOPE
		);
}

std::string OTAPI_Basic::SignContract(
	const std::string & SIGNER_NYM_ID,
	const std::string & THE_CONTRACT
	)
{	
	return OTAPI_Wrap::SymmetricDecrypt(
		SIGNER_NYM_ID,
		THE_CONTRACT
		);
}

std::string OTAPI_Basic::FlatSign(
	const std::string & SIGNER_NYM_ID,
	const std::string & THE_INPUT,
	const std::string & CONTRACT_TYPE
	)
{
		return OTAPI_Wrap::FlatSign(SIGNER_NYM_ID,THE_INPUT,CONTRACT_TYPE);
}

std::string OTAPI_Basic::AddSignature(
	const std::string & SIGNER_NYM_ID,
	const std::string & THE_CONTRACT
	)
{
	return OTAPI_Wrap::AddSignature(
		SIGNER_NYM_ID,
		THE_CONTRACT
		);
}

bool OTAPI_Basic::VerifySignature(
	const std::string & SIGNER_NYM_ID,
	const std::string & THE_CONTRACT
	)
{
	return OTAPI_Wrap::VerifySignature(
		SIGNER_NYM_ID,
		THE_CONTRACT
		);
}

std::string OTAPI_Basic::VerifyAndRetrieveXMLContents(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_ID
	)

{
	return OTAPI_Wrap::VerifyAndRetrieveXMLContents(
		THE_CONTRACT,
		SIGNER_ID
		);
}

long OTAPI_Basic::GetMemlogSize() { return OTAPI_Wrap::GetMemlogSize(); }

std::string OTAPI_Basic::GetMemlogAtIndex(const long & nIndex) { return OTAPI_Wrap::GetMemlogAtIndex(nIndex); }

std::string OTAPI_Basic::PeekMemlogFront() { return OTAPI_Wrap::PeekMemlogFront(); }
std::string OTAPI_Basic::PeekMemlogBack() { return OTAPI_Wrap::PeekMemlogBack(); }

bool OTAPI_Basic::PopMemlogFront() { return OTAPI_Wrap::PopMemlogFront(); }
bool OTAPI_Basic::PopMemlogBack() {return OTAPI_Wrap::PopMemlogBack(); }

std::string OTAPI_Basic::CreateNym(const long & nKeySize, // must be 1024, 2048, 4096, or 8192
                              const std::string & NYM_ID_SOURCE,
                              const std::string & ALT_LOCATION)
{
	return OTAPI_Wrap::CreateNym(
		nKeySize, NYM_ID_SOURCE, ALT_LOCATION);
}


std::string OTAPI_Basic::GetNym_ActiveCronItemIDs(const std::string & NYM_ID, const std::string & SERVER_ID)
{
    return OTAPI_Wrap::GetNym_ActiveCronItemIDs(
                                     NYM_ID,
                                     SERVER_ID
                                     );
}

std::string OTAPI_Basic::GetActiveCronItem(const std::string & SERVER_ID, const std::string & TRANSACTION_NUMBER)
{
    return OTAPI_Wrap::GetActiveCronItem(
                                         SERVER_ID,
                                         OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER)
                                         );
}

std::string OTAPI_Basic::GetNym_SourceForID(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_SourceForID(NYM_ID);
}


std::string OTAPI_Basic::GetNym_AltSourceLocation(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_AltSourceLocation(NYM_ID);    
}


long OTAPI_Basic::GetNym_CredentialCount(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_CredentialCount(NYM_ID);
}


std::string OTAPI_Basic::GetNym_CredentialID(const std::string & NYM_ID, const long & nIndex)
{
	return OTAPI_Wrap::GetNym_CredentialID(NYM_ID, nIndex);
}


std::string OTAPI_Basic::GetNym_CredentialContents(const std::string & NYM_ID, const std::string & CREDENTIAL_ID)
{
	return OTAPI_Wrap::GetNym_CredentialContents(NYM_ID, CREDENTIAL_ID);
}


long OTAPI_Basic::GetNym_RevokedCredCount(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_RevokedCredCount(NYM_ID);
}


std::string OTAPI_Basic::GetNym_RevokedCredID(const std::string & NYM_ID, const long & nIndex)
{
	return OTAPI_Wrap::GetNym_RevokedCredID(NYM_ID, nIndex);
}


std::string OTAPI_Basic::GetNym_RevokedCredContents(const std::string & NYM_ID, const std::string & CREDENTIAL_ID)
{
	return OTAPI_Wrap::GetNym_RevokedCredContents(NYM_ID, CREDENTIAL_ID);
}


long OTAPI_Basic::GetNym_SubcredentialCount(const std::string & NYM_ID, const std::string & MASTER_CRED_ID)
{
	return OTAPI_Wrap::GetNym_SubcredentialCount(NYM_ID, MASTER_CRED_ID);
}


std::string OTAPI_Basic::GetNym_SubCredentialID(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const long & nIndex)
{
	return OTAPI_Wrap::GetNym_SubCredentialID(NYM_ID, MASTER_CRED_ID, nIndex);
}


std::string OTAPI_Basic::GetNym_SubCredentialContents(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const std::string & SUB_CRED_ID)
{
	return OTAPI_Wrap::GetNym_SubCredentialContents(NYM_ID, MASTER_CRED_ID, SUB_CRED_ID);
}

std::string OTAPI_Basic::AddSubcredential(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const long & nKeySize)
{
    return OTAPI_Wrap::AddSubcredential(NYM_ID, MASTER_CRED_ID, nKeySize);
}

bool OTAPI_Basic::RevokeSubcredential(const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const std::string & SUB_CRED_ID)
{
    return OTAPI_Wrap::RevokeSubcredential(NYM_ID, MASTER_CRED_ID, SUB_CRED_ID);
}


std::string OTAPI_Basic::CreateServerContract(
	const std::string & NYM_ID,
	const std::string & strXMLcontents
	)
{
	return OTAPI_Wrap::CreateServerContract(
		NYM_ID,
		strXMLcontents
		);
}


std::string OTAPI_Basic::CreateAssetContract(
	const std::string & NYM_ID,
	const std::string & strXMLcontents
	)
{
	return OTAPI_Wrap::CreateAssetContract(
		NYM_ID,
		strXMLcontents
		);
}


std::string OTAPI_Basic::CalculateAssetContractID(const std::string & str_Contract)
{
	return OTAPI_Wrap::CalculateAssetContractID(str_Contract);
}

std::string OTAPI_Basic::CalculateServerContractID(const std::string & str_Contract)
{
	return OTAPI_Wrap::CalculateServerContractID(str_Contract);
}


long OTAPI_Basic::AddServerContract(const std::string & strContract)
{
	return OTAPI_Wrap::AddServerContract(
		strContract
		);
}

long OTAPI_Basic::AddAssetContract(const std::string & strContract)
{
	return OTAPI_Wrap::AddAssetContract(
		strContract
		);
}

long OTAPI_Basic::GetServerCount()    { return OTAPI_Wrap::GetServerCount(); }
long OTAPI_Basic::GetAssetTypeCount() { return OTAPI_Wrap::GetAssetTypeCount(); }
long OTAPI_Basic::GetAccountCount()   { return OTAPI_Wrap::GetAccountCount(); }
long OTAPI_Basic::GetNymCount()
{
	const long nNymCount = OTAPI_Wrap::GetNymCount();
	return nNymCount;
}

std::string OTAPI_Basic::GetServer_ID(const long & nIndex)
{
	return OTAPI_Wrap::GetServer_ID(
		nIndex
		);
}

std::string OTAPI_Basic::GetServer_Name(const std::string & SERVER_ID)
{
	return OTAPI_Wrap::GetServer_Name(
		SERVER_ID
		);
}

std::string OTAPI_Basic::GetServer_Contract(const std::string & SERVER_ID)
{
	return OTAPI_Wrap::GetServer_Contract(
		SERVER_ID
		);
}


std::string OTAPI_Basic::FormatAmount(const std::string & ASSET_TYPE_ID, const std::string & THE_AMOUNT)
{
	return OTAPI_Wrap::FormatAmount(ASSET_TYPE_ID, OTAPI_Wrap::StringToLong(THE_AMOUNT));
}

std::string OTAPI_Basic::StringToAmount(const std::string & ASSET_TYPE_ID, const std::string & str_input)
{
    return OTAPI_Wrap::LongToString(OTAPI_Wrap::StringToAmount(ASSET_TYPE_ID, str_input));
}


std::string OTAPI_Basic::GetAssetType_ID(const long & nIndex)
{
	return OTAPI_Wrap::GetAssetType_ID(
		nIndex
		);
}

std::string OTAPI_Basic::GetAssetType_Name(const std::string & ASSET_TYPE_ID)
{
	return OTAPI_Wrap::GetAssetType_Name(
		ASSET_TYPE_ID
		);
}

std::string OTAPI_Basic::GetAssetType_TLA(const std::string & ASSET_TYPE_ID)
{
	return OTAPI_Wrap::GetAssetType_TLA(
		ASSET_TYPE_ID
		);
}

std::string OTAPI_Basic::GetAssetType_Contract(const std::string & ASSET_TYPE_ID)
{
	return OTAPI_Wrap::GetAssetType_Contract(
		ASSET_TYPE_ID
		);
}

std::string OTAPI_Basic::GetAccountWallet_ID(const long & nIndex)
{
	return OTAPI_Wrap::GetAccountWallet_ID(
		nIndex
		);
}

std::string OTAPI_Basic::GetAccountWallet_Name(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::GetAccountWallet_Name(
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::GetAccountWallet_Balance(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::GetAccountWallet_Balance(ACCOUNT_ID));
}

std::string OTAPI_Basic::GetAccountWallet_Type(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::GetAccountWallet_Type(
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::GetAccountWallet_AssetTypeID(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::GetAccountWallet_AssetTypeID(
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::GetAccountWallet_ServerID(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::GetAccountWallet_ServerID(
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::GetAccountWallet_NymID(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::GetAccountWallet_NymID(
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::GetAccountWallet_InboxHash(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::GetAccountWallet_InboxHash(
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::GetAccountWallet_OutboxHash(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::GetAccountWallet_OutboxHash(
		ACCOUNT_ID
		);
}

bool OTAPI_Basic::VerifyAccountReceipt(
	const std::string & SERVER_ID,
	const std::string & NYM_ID,
	const std::string & ACCT_ID
	)
{
	return OTAPI_Wrap::VerifyAccountReceipt(
		SERVER_ID,
		NYM_ID,
		ACCT_ID
		);
}

long OTAPI_Basic::GetNym_TransactionNumCount(
	const std::string & SERVER_ID,
	const std::string & NYM_ID
	)
{
	return OTAPI_Wrap::GetNym_TransactionNumCount(
		SERVER_ID,
		NYM_ID
		);
}

std::string OTAPI_Basic::GetNym_ID(const long & nIndex)
{
	return OTAPI_Wrap::GetNym_ID(
		nIndex
		);
}

std::string OTAPI_Basic::GetNym_Name(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_Name(
		NYM_ID
		);
}

std::string OTAPI_Basic::GetNym_Stats(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_Stats(
		NYM_ID
		);
}

std::string OTAPI_Basic::GetNym_NymboxHash(
	const std::string & SERVER_ID,
	const std::string & NYM_ID 
	)
{
	return OTAPI_Wrap::GetNym_NymboxHash(
		SERVER_ID,
		NYM_ID
		);
}

std::string OTAPI_Basic::GetNym_RecentHash(
	const std::string & SERVER_ID,
	const std::string & NYM_ID
	)
{
	return OTAPI_Wrap::GetNym_RecentHash(
		SERVER_ID,
		NYM_ID
		);	
}

std::string OTAPI_Basic::GetNym_InboxHash(
	const std::string & ACCOUNT_ID,
	const std::string & NYM_ID
	)
{
	return OTAPI_Wrap::GetNym_InboxHash(
		ACCOUNT_ID,
		NYM_ID
		);		
}

std::string OTAPI_Basic::GetNym_OutboxHash(
	const std::string & ACCOUNT_ID,
	const std::string & NYM_ID
	)
{
	return OTAPI_Wrap::GetNym_OutboxHash(
		ACCOUNT_ID,
		NYM_ID
		);	
}

bool OTAPI_Basic::IsNym_RegisteredAtServer(const std::string & NYM_ID, const std::string & SERVER_ID)
{
	return OTAPI_Wrap::IsNym_RegisteredAtServer(
		NYM_ID,
		SERVER_ID
		);	
}

long OTAPI_Basic::GetNym_MailCount(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_MailCount(
		NYM_ID
		);
}

std::string OTAPI_Basic::GetNym_MailContentsByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_MailContentsByIndex(
		NYM_ID,
		nIndex
		);	
}

std::string OTAPI_Basic::GetNym_MailSenderIDByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_MailSenderIDByIndex(
		NYM_ID,
		nIndex
		);		
}

std::string OTAPI_Basic::GetNym_MailServerIDByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_MailServerIDByIndex(
		NYM_ID,
		nIndex
		);
}

bool OTAPI_Basic::Nym_RemoveMailByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Nym_RemoveMailByIndex(
		NYM_ID,
		nIndex
		);
}

bool OTAPI_Basic::Nym_VerifyMailByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Nym_VerifyMailByIndex(
		NYM_ID,
		nIndex
		);	
}

long OTAPI_Basic::GetNym_OutmailCount(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_OutmailCount(
		NYM_ID
		);
}

std::string OTAPI_Basic::GetNym_OutmailContentsByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_OutmailContentsByIndex(
		NYM_ID,
		nIndex
		);	
}

std::string OTAPI_Basic::GetNym_OutmailRecipientIDByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_OutmailRecipientIDByIndex(
		NYM_ID,
		nIndex
		);
}

std::string OTAPI_Basic::GetNym_OutmailServerIDByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_OutmailServerIDByIndex(
		NYM_ID,
		nIndex
		);
}

bool OTAPI_Basic::Nym_RemoveOutmailByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Nym_RemoveOutmailByIndex(
		NYM_ID,
		nIndex
		);
}

bool OTAPI_Basic::Nym_VerifyOutmailByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Nym_VerifyOutmailByIndex(
		NYM_ID,
		nIndex
		);	
}

long OTAPI_Basic::GetNym_OutpaymentsCount(const std::string & NYM_ID)
{
	return OTAPI_Wrap::GetNym_OutpaymentsCount(
		NYM_ID
		);
}

std::string OTAPI_Basic::GetNym_OutpaymentsContentsByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_OutpaymentsContentsByIndex(
		NYM_ID,
		nIndex
		);	
}

std::string OTAPI_Basic::GetNym_OutpaymentsRecipientIDByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_OutpaymentsRecipientIDByIndex(
		NYM_ID,
		nIndex
		);
}

std::string OTAPI_Basic::GetNym_OutpaymentsServerIDByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::GetNym_OutpaymentsServerIDByIndex(
		NYM_ID,
		nIndex
		);	
}

bool OTAPI_Basic::Nym_RemoveOutpaymentsByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Nym_RemoveOutpaymentsByIndex(
		NYM_ID,
		nIndex
		);
}

bool OTAPI_Basic::Nym_VerifyOutpaymentsByIndex(
	const std::string & NYM_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Nym_VerifyOutpaymentsByIndex(
		NYM_ID,
		nIndex
		);	
}


bool  OTAPI_Basic::Wallet_ChangePassphrase() { return OTAPI_Wrap::Wallet_ChangePassphrase(); }

bool OTAPI_Basic::Wallet_CanRemoveServer(const std::string & SERVER_ID)
{
	return OTAPI_Wrap::Wallet_CanRemoveServer(
		SERVER_ID
		);
}

bool OTAPI_Basic::Wallet_RemoveServer(const std::string & SERVER_ID)
{
	return OTAPI_Wrap::Wallet_RemoveServer(
		SERVER_ID
		);
}

bool OTAPI_Basic::Wallet_CanRemoveAssetType(const std::string & ASSET_ID)
{
	return OTAPI_Wrap::Wallet_CanRemoveAssetType(
		ASSET_ID
		);
}

bool OTAPI_Basic::Wallet_RemoveAssetType(const std::string & ASSET_ID)
{
	return OTAPI_Wrap::Wallet_RemoveAssetType(
		ASSET_ID
		);
}

bool OTAPI_Basic::Wallet_CanRemoveNym(const std::string & NYM_ID)
{
	return OTAPI_Wrap::Wallet_RemoveAssetType(
		NYM_ID
		);
}

bool OTAPI_Basic::Wallet_RemoveNym(const std::string & NYM_ID)
{
	return OTAPI_Wrap::Wallet_RemoveNym(
		NYM_ID
		);
}

bool OTAPI_Basic::Wallet_CanRemoveAccount(const std::string & ACCOUNT_ID)
{
	return OTAPI_Wrap::Wallet_CanRemoveAccount(
		ACCOUNT_ID
		);
}


std::string OTAPI_Basic::Wallet_ExportNym(const std::string & NYM_ID)
{
	return OTAPI_Wrap::Wallet_ExportNym(NYM_ID);
}
std::string OTAPI_Basic::Wallet_ImportNym(const std::string & FILE_CONTENTS)
{
	return OTAPI_Wrap::Wallet_ImportNym(FILE_CONTENTS);
}
std::string OTAPI_Basic::Wallet_ImportCert(const std::string & DISPLAY_NAME, const std::string & FILE_CONTENTS)
{
	return OTAPI_Wrap::Wallet_ImportCert(DISPLAY_NAME, FILE_CONTENTS);
}
std::string OTAPI_Basic::Wallet_ExportCert(const std::string & NYM_ID)
{
	return OTAPI_Wrap::Wallet_ExportCert(NYM_ID);
}



std::string OTAPI_Basic::Wallet_GetNymIDFromPartial(const std::string & PARTIAL_ID)
{
	return OTAPI_Wrap::Wallet_GetNymIDFromPartial(
		PARTIAL_ID
		);
}

std::string OTAPI_Basic::Wallet_GetServerIDFromPartial(const std::string & PARTIAL_ID)
{
	return OTAPI_Wrap::Wallet_GetServerIDFromPartial(
		PARTIAL_ID
		);
}

std::string OTAPI_Basic::Wallet_GetAssetIDFromPartial(const std::string & PARTIAL_ID)
{
	return OTAPI_Wrap::Wallet_GetAssetIDFromPartial(
		PARTIAL_ID
		);
}

std::string OTAPI_Basic::Wallet_GetAccountIDFromPartial(const std::string & PARTIAL_ID)
{
	return OTAPI_Wrap::Wallet_GetAccountIDFromPartial(
		PARTIAL_ID
		);
}

bool OTAPI_Basic::SetNym_Name(
	const std::string & NYM_ID, 
	const std::string & SIGNER_NYM_ID, 
	const std::string & NYM_NEW_NAME
	)
{
	return OTAPI_Wrap::SetNym_Name(
		NYM_ID,
		SIGNER_NYM_ID,
		NYM_NEW_NAME
		);
}

bool OTAPI_Basic::SetAccountWallet_Name(
	const std::string & ACCT_ID, 
	const std::string & SIGNER_NYM_ID, 
	const std::string & ACCT_NEW_NAME
	)
{
	return OTAPI_Wrap::SetAccountWallet_Name(
		ACCT_ID,
		SIGNER_NYM_ID,
		ACCT_NEW_NAME
		);
}

bool OTAPI_Basic::SetAssetType_Name(
	const std::string & ASSET_ID, 
	const std::string & STR_NEW_NAME
	)
{
	return OTAPI_Wrap::SetAssetType_Name(
		ASSET_ID,
		STR_NEW_NAME
		);
}

bool OTAPI_Basic::SetServer_Name(
	const std::string & SERVER_ID, 
	const std::string & STR_NEW_NAME
	)
{
	return OTAPI_Wrap::SetServer_Name(
		SERVER_ID,
		STR_NEW_NAME
		);
}

std::string OTAPI_Basic::WriteCheque(
	const std::string & SERVER_ID,
	const std::string & CHEQUE_AMOUNT, 
	const std::string & VALID_FROM, 
	const std::string & VALID_TO,
	const std::string & SENDER_ACCT_ID,
	const std::string & SENDER_USER_ID,
	const std::string & CHEQUE_MEMO, 
	const std::string & RECIPIENT_USER_ID
	)
{
	//const int64_t lCHEQUE_AMOUNT = OTAPI_Wrap::StringToLong(CHEQUE_AMOUNT);
	//const int64_t lVALID_FROM	 = OTAPI_Wrap::StringToLong(VALID_FROM);
	//const int64_t lVALID_TO		 = OTAPI_Wrap::StringToLong(VALID_TO);

	return OTAPI_Wrap::WriteCheque(
		SERVER_ID,
		OTAPI_Wrap::StringToLong(CHEQUE_AMOUNT),
		OTAPI_Wrap::StringToLong(VALID_FROM),
		OTAPI_Wrap::StringToLong(VALID_TO),
		SENDER_ACCT_ID,
		SENDER_USER_ID,
		CHEQUE_MEMO,
		RECIPIENT_USER_ID
		);
}

bool OTAPI_Basic::DiscardCheque(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID,
	const std::string & THE_CHEQUE
	)
{
	return OTAPI_Wrap::DiscardCheque(
		SERVER_ID,
		USER_ID,
		ACCT_ID,
		THE_CHEQUE
		);
}

std::string OTAPI_Basic::ProposePaymentPlan(
		const std::string & SERVER_ID,
		const std::string & VALID_FROM,
		const std::string & VALID_TO,
		const std::string & SENDER_ACCT_ID,
		const std::string & SENDER_USER_ID,
		const std::string & PLAN_CONSIDERATION,
		const std::string & RECIPIENT_ACCT_ID,
		const std::string & RECIPIENT_USER_ID,
		const std::string & INITIAL_PAYMENT_AMOUNT,
		const std::string & INITIAL_PAYMENT_DELAY,
		const std::string & PAYMENT_PLAN_AMOUNT,
		const std::string & PAYMENT_PLAN_DELAY,
		const std::string & PAYMENT_PLAN_PERIOD,
		const std::string & PAYMENT_PLAN_LENGTH,
		const long & PAYMENT_PLAN_MAX_PAYMENTS
		)
{
	//const int64_t lVALID_FROM				= OTAPI_Wrap::StringToLong(VALID_FROM);
	//const int64_t lVALID_TO					= OTAPI_Wrap::StringToLong(VALID_TO);
	//const int64_t lINITIAL_PAYMENT_AMOUNT	= OTAPI_Wrap::StringToLong(INITIAL_PAYMENT_AMOUNT);
	//const int64_t lINITIAL_PAYMENT_DELAY	= OTAPI_Wrap::StringToLong(INITIAL_PAYMENT_DELAY);
	//const int64_t LPAYMENT_PLAN_AMOUNT		= OTAPI_Wrap::StringToLong(PAYMENT_PLAN_AMOUNT);
	//const int64_t lPAYMENT_PLAN_DELAY		= OTAPI_Wrap::StringToLong(PAYMENT_PLAN_DELAY);
	//const int64_t lPAYMENT_PLAN_PERIOD		= OTAPI_Wrap::StringToLong(PAYMENT_PLAN_PERIOD);
	//const int64_t lPAYMENT_PLAN_LENGTH		= OTAPI_Wrap::StringToLong(PAYMENT_PLAN_LENGTH);

	return OTAPI_Wrap::ProposePaymentPlan(
		SERVER_ID,
		OTAPI_Wrap::StringToLong(VALID_FROM),
		OTAPI_Wrap::StringToLong(VALID_TO),
		SENDER_ACCT_ID,
		SENDER_USER_ID,
		PLAN_CONSIDERATION,
		RECIPIENT_ACCT_ID,
		RECIPIENT_USER_ID,
		OTAPI_Wrap::StringToLong(INITIAL_PAYMENT_AMOUNT),
		OTAPI_Wrap::StringToLong(INITIAL_PAYMENT_DELAY),
		OTAPI_Wrap::StringToLong(PAYMENT_PLAN_AMOUNT),
		OTAPI_Wrap::StringToLong(PAYMENT_PLAN_DELAY),
		OTAPI_Wrap::StringToLong(PAYMENT_PLAN_PERIOD),
		OTAPI_Wrap::StringToLong(PAYMENT_PLAN_LENGTH),
		PAYMENT_PLAN_MAX_PAYMENTS
		);
}


std::string OTAPI_Basic::EasyProposePlan(
    const std::string & SERVER_ID,
    // ----------------------------------------
    const std::string & DATE_RANGE,          // "from,to"  Default 'from' (0 or "") == NOW, and default 'to' (0 or "") == no expiry / cancel anytime
    // ----------------------------------------
    const std::string & SENDER_ACCT_ID,      // Mandatory parameters.
    const std::string & SENDER_USER_ID,      // Both sender and recipient must sign before submitting.
    // ----------------------------------------
    const std::string & PLAN_CONSIDERATION,	// Like a memo.
    // ----------------------------------------
    const std::string & RECIPIENT_ACCT_ID,	// NOT optional.
    const std::string & RECIPIENT_USER_ID,	// Both sender and recipient must sign before submitting.
    // -------------------------------
    const std::string & INITIAL_PAYMENT,     // "amount,delay"  Default 'amount' (0 or "") == no initial payment. Default 'delay' (0 or NULL) is seconds from creation date.
    // -------------------------------
    const std::string & PAYMENT_PLAN,        // "amount,delay,period" 'amount' is a recurring payment. 'delay' and 'period' cause 30 days if you pass 0 or "".
    // -------------------------------
    const std::string & PLAN_EXPIRY          // "length,number" 'length' is maximum lifetime in seconds. 'number' is maximum number of payments in seconds. 0 or "" is unlimited.
    )
{
	return OTAPI_Wrap::EasyProposePlan(
          SERVER_ID,
          DATE_RANGE,
          SENDER_ACCT_ID,
          SENDER_USER_ID,
          PLAN_CONSIDERATION,
          RECIPIENT_ACCT_ID,
          RECIPIENT_USER_ID,
          INITIAL_PAYMENT,
          PAYMENT_PLAN,
          PLAN_EXPIRY
          );
}


std::string OTAPI_Basic::ConfirmPaymentPlan(
	const std::string & SERVER_ID,
	const std::string & SENDER_USER_ID,
	const std::string & SENDER_ACCT_ID,
	const std::string & RECIPIENT_USER_ID,
	const std::string & PAYMENT_PLAN
	)
{
	return OTAPI_Wrap::ConfirmPaymentPlan(
		SERVER_ID,
		SENDER_USER_ID,
		SENDER_ACCT_ID,
		RECIPIENT_USER_ID,
		PAYMENT_PLAN
		);
}

std::string OTAPI_Basic::Create_SmartContract(
	const std::string & SIGNER_NYM_ID,
	const std::string & VALID_FROM,
	const std::string & VALID_TO
	)
{
//  const int64_t lVALID_FROM = OTAPI_Wrap::StringToLong(VALID_FROM);
//  const int64_t lVALID_TO   = OTAPI_Wrap::StringToLong(VALID_TO);

	return OTAPI_Wrap::Create_SmartContract(
		SIGNER_NYM_ID,
		OTAPI_Wrap::StringToLong(VALID_FROM),
		OTAPI_Wrap::StringToLong(VALID_TO)
		);	
}

std::string OTAPI_Basic::SmartContract_AddBylaw(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & BYLAW_NAME
	)
{
	return OTAPI_Wrap::SmartContract_AddBylaw(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		BYLAW_NAME
		);
}

std::string OTAPI_Basic::SmartContract_AddClause(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & BYLAW_NAME,
	const std::string & CLAUSE_NAME,
	const std::string & SOURCE_CODE
	)
{
	return OTAPI_Wrap::SmartContract_AddClause(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		BYLAW_NAME,
		CLAUSE_NAME,
		SOURCE_CODE
		);
}

std::string OTAPI_Basic::SmartContract_AddVariable(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & BYLAW_NAME,
	const std::string & VAR_NAME,
	const std::string & VAR_ACCESS,
	const std::string & VAR_TYPE,
	const std::string & VAR_VALUE
	)
{
	return OTAPI_Wrap::SmartContract_AddVariable(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		BYLAW_NAME,
		VAR_NAME,
		VAR_ACCESS,
		VAR_TYPE,
		VAR_VALUE
		);
}

std::string OTAPI_Basic::SmartContract_AddCallback(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & BYLAW_NAME,
	const std::string & CALLBACK_NAME,
	const std::string & CLAUSE_NAME
	)
{
	return OTAPI_Wrap::SmartContract_AddCallback(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		BYLAW_NAME,
		CALLBACK_NAME,
		CLAUSE_NAME
		);
}

std::string OTAPI_Basic::SmartContract_AddHook(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & BYLAW_NAME,
	const std::string & HOOK_NAME,
	const std::string & CLAUSE_NAME
	)
{
	return OTAPI_Wrap::SmartContract_AddHook(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		BYLAW_NAME,
		HOOK_NAME,
		CLAUSE_NAME
		);
}

std::string OTAPI_Basic::SmartContract_AddParty(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & PARTY_NAME,
	const std::string & AGENT_NAME
	)
{
	return OTAPI_Wrap::SmartContract_AddParty(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		PARTY_NAME,
		AGENT_NAME
		);
}

std::string OTAPI_Basic::SmartContract_AddAccount(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & PARTY_NAME,
	const std::string & ACCT_NAME,
	const std::string & ASSET_TYPE_ID
	)
{
	return OTAPI_Wrap::SmartContract_AddAccount(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		PARTY_NAME,
		ACCT_NAME,
		ASSET_TYPE_ID
		);
}	

long OTAPI_Basic::SmartContract_CountNumsNeeded(
	const std::string & THE_CONTRACT,
	const std::string & AGENT_NAME
	)
{
	return OTAPI_Wrap::SmartContract_CountNumsNeeded(
		THE_CONTRACT,
		AGENT_NAME
		);
}

std::string OTAPI_Basic::SmartContract_ConfirmAccount(
	const std::string & THE_CONTRACT,
	const std::string & SIGNER_NYM_ID,
	const std::string & PARTY_NAME,
	const std::string & ACCT_NAME,
	const std::string & AGENT_NAME,
	const std::string & ACCT_ID
	)
{
	return OTAPI_Wrap::SmartContract_ConfirmAccount(
		THE_CONTRACT,
		SIGNER_NYM_ID,
		PARTY_NAME,
		ACCT_NAME,
		AGENT_NAME,
		ACCT_ID
		);
}

std::string OTAPI_Basic::SmartContract_ConfirmParty(
	const std::string & THE_CONTRACT,
	const std::string & PARTY_NAME,
	const std::string & NYM_ID
	)
{
	return OTAPI_Wrap::SmartContract_ConfirmParty(
		THE_CONTRACT,
		PARTY_NAME,
		NYM_ID
		);
}


bool OTAPI_Basic::Smart_AreAllPartiesConfirmed(const std::string & THE_CONTRACT)  // true or false?
{
	return OTAPI_Wrap::Smart_AreAllPartiesConfirmed(THE_CONTRACT);
}


bool OTAPI_Basic::Smart_IsPartyConfirmed(const std::string & THE_CONTRACT, const std::string & PARTY_NAME)  // true or false?
{
	return OTAPI_Wrap::Smart_IsPartyConfirmed(THE_CONTRACT, PARTY_NAME);
}


// ----------------------------------------------------------
long OTAPI_Basic::Smart_GetBylawCount(const std::string & THE_CONTRACT)
{
	return OTAPI_Wrap::Smart_GetBylawCount(THE_CONTRACT);
}


std::string OTAPI_Basic::Smart_GetBylawByIndex(const std::string & THE_CONTRACT, const long & nIndex) // returns the name of the bylaw.
{
	return OTAPI_Wrap::Smart_GetBylawByIndex(THE_CONTRACT, nIndex);
}


// ----------------------------------------------------------
std::string OTAPI_Basic::Bylaw_GetLanguage(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
	return OTAPI_Wrap::Bylaw_GetLanguage(THE_CONTRACT, BYLAW_NAME);
}


// ----------------------------------------------------------

long OTAPI_Basic::Bylaw_GetClauseCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
	return OTAPI_Wrap::Bylaw_GetClauseCount(THE_CONTRACT, BYLAW_NAME);
}


std::string OTAPI_Basic::Clause_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const long & nIndex) // returns the name of the clause.
{
	return OTAPI_Wrap::Clause_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}


std::string OTAPI_Basic::Clause_GetContents(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & CLAUSE_NAME) // returns the contents of the clause.
{
  	return OTAPI_Wrap::Clause_GetContents(THE_CONTRACT, BYLAW_NAME, CLAUSE_NAME);
}


// ----------------------------------------------------------
long OTAPI_Basic::Bylaw_GetVariableCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return OTAPI_Wrap::Bylaw_GetVariableCount(THE_CONTRACT, BYLAW_NAME);
}


std::string OTAPI_Basic::Variable_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const long & nIndex) // returns the name of the variable.
{
	return OTAPI_Wrap::Variable_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}


std::string OTAPI_Basic::Variable_GetType(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME) // returns the type of the variable.
{
    return OTAPI_Wrap::Variable_GetType(THE_CONTRACT, BYLAW_NAME, VARIABLE_NAME);
}


std::string OTAPI_Basic::Variable_GetAccess(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME) // returns the access level of the variable.
{
    return OTAPI_Wrap::Variable_GetAccess(THE_CONTRACT, BYLAW_NAME, VARIABLE_NAME);
}


std::string OTAPI_Basic::Variable_GetContents(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME) // returns the contents of the variable.
{
    return OTAPI_Wrap::Variable_GetContents(THE_CONTRACT, BYLAW_NAME, VARIABLE_NAME);
}


// ----------------------------------------------------------
long OTAPI_Basic::Bylaw_GetHookCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return OTAPI_Wrap::Bylaw_GetHookCount(THE_CONTRACT, BYLAW_NAME);
}


std::string OTAPI_Basic::Hook_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const long & nIndex) // returns the name of the hook.
{
    return OTAPI_Wrap::Hook_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}


long OTAPI_Basic::Hook_GetClauseCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & HOOK_NAME) // for iterating clauses on a hook.
{
    return OTAPI_Wrap::Hook_GetClauseCount(THE_CONTRACT, BYLAW_NAME, HOOK_NAME);
}


std::string OTAPI_Basic::Hook_GetClauseAtIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & HOOK_NAME, const long & nIndex)
{
    return OTAPI_Wrap::Hook_GetClauseAtIndex(THE_CONTRACT, BYLAW_NAME, HOOK_NAME, nIndex);
}


// ----------------------------------------------------------
long OTAPI_Basic::Bylaw_GetCallbackCount(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME)
{
    return OTAPI_Wrap::Bylaw_GetCallbackCount(THE_CONTRACT, BYLAW_NAME);
}


std::string OTAPI_Basic::Callback_GetNameByIndex(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const long & nIndex) // returns the name of the callback.
{
    return OTAPI_Wrap::Callback_GetNameByIndex(THE_CONTRACT, BYLAW_NAME, nIndex);
}


std::string OTAPI_Basic::Callback_GetClause(const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & CALLBACK_NAME) // returns name of clause attached to callback.
{
    return OTAPI_Wrap::Callback_GetClause(THE_CONTRACT, BYLAW_NAME, CALLBACK_NAME);
}


// **********************************************************
long OTAPI_Basic::Smart_GetPartyCount(const std::string & THE_CONTRACT)
{
    return OTAPI_Wrap::Smart_GetPartyCount(THE_CONTRACT);
}


std::string OTAPI_Basic::Smart_GetPartyByIndex(const std::string & THE_CONTRACT, const long & nIndex) // returns the name of the party.
{
    return OTAPI_Wrap::Smart_GetPartyByIndex(THE_CONTRACT, nIndex);
}


std::string OTAPI_Basic::Party_GetID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME) // returns either NymID or Entity ID.
{
    return OTAPI_Wrap::Party_GetID(THE_CONTRACT, PARTY_NAME);
}


// ----------------------------------------------------------
long OTAPI_Basic::Party_GetAcctCount(const std::string & THE_CONTRACT, const std::string & PARTY_NAME)
{
    return OTAPI_Wrap::Party_GetAcctCount(THE_CONTRACT, PARTY_NAME);
}


std::string OTAPI_Basic::Party_GetAcctNameByIndex(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const long & nIndex) // returns the name of the clause.
{
 	return OTAPI_Wrap::Party_GetAcctNameByIndex(THE_CONTRACT, PARTY_NAME, nIndex);
}


std::string OTAPI_Basic::Party_GetAcctID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME) // returns account ID for a given acct name.
{
    return OTAPI_Wrap::Party_GetAcctID(THE_CONTRACT, PARTY_NAME, ACCT_NAME);
}


std::string OTAPI_Basic::Party_GetAcctAssetID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME) // returns asset type ID for a given acct name.
{
    return OTAPI_Wrap::Party_GetAcctAssetID(THE_CONTRACT, PARTY_NAME, ACCT_NAME);
}


std::string OTAPI_Basic::Party_GetAcctAgentName(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME) // returns agent name authorized to administer a given named acct. (If it's set...)
{
    return OTAPI_Wrap::Party_GetAcctAgentName(THE_CONTRACT, PARTY_NAME, ACCT_NAME);
}


// ----------------------------------------------------------
long OTAPI_Basic::Party_GetAgentCount(const std::string & THE_CONTRACT, const std::string & PARTY_NAME)
{
    return OTAPI_Wrap::Party_GetAgentCount(THE_CONTRACT, PARTY_NAME);
}


std::string OTAPI_Basic::Party_GetAgentNameByIndex(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const long & nIndex) // returns the name of the agent.
{
    return OTAPI_Wrap::Party_GetAgentNameByIndex(THE_CONTRACT, PARTY_NAME, nIndex);
}


std::string OTAPI_Basic::Party_GetAgentID(const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & AGENT_NAME) // returns ID of the agent. (If there is one...)
{
    return OTAPI_Wrap::Party_GetAgentID(THE_CONTRACT, PARTY_NAME, AGENT_NAME);
}


long OTAPI_Basic::activateSmartContract(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & THE_SMART_CONTRACT
	)
{
	return OTAPI_Wrap::activateSmartContract(
		SERVER_ID,
		USER_ID,
		THE_SMART_CONTRACT
		);
}

long OTAPI_Basic::triggerClause(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & TRANSACTION_NUMBER,
	const std::string & CLAUSE_NAME,
	const std::string & STR_PARAM
	)
{
	//const int64_t lTRANSACTION_NUMBER		= OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER);

	return OTAPI_Wrap::triggerClause(
		SERVER_ID,
		USER_ID,
		OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER),
		CLAUSE_NAME,
		STR_PARAM
		);
}

bool OTAPI_Basic::Msg_HarvestTransactionNumbers(
	const std::string & THE_MESSAGE,
	const std::string & USER_ID,
	const bool & bHarvestingForRetry,
	const bool & bReplyWasSuccess,
	const bool & bReplyWasFailure,
	const bool & bTransactionWasSuccess,
	const bool & bTransactionWasFailure
	)
{
	return OTAPI_Wrap::Msg_HarvestTransactionNumbers(
		THE_MESSAGE,
		USER_ID,
		bHarvestingForRetry,
		bReplyWasSuccess,
		bReplyWasFailure,
		bTransactionWasSuccess,
		bTransactionWasFailure
		);
}

std::string OTAPI_Basic::LoadUserPubkey_Encryption(const std::string & USER_ID)
{
	return OTAPI_Wrap::LoadUserPubkey_Encryption(
		USER_ID
		);
}

std::string OTAPI_Basic::LoadPubkey_Encryption(const std::string & USER_ID)
{
	return OTAPI_Wrap::LoadPubkey_Encryption(
		USER_ID
		);
}

std::string OTAPI_Basic::LoadUserPubkey_Signing(const std::string & USER_ID)
{
	return OTAPI_Wrap::LoadUserPubkey_Signing(
		USER_ID
		);
}

std::string OTAPI_Basic::LoadPubkey_Signing(const std::string & USER_ID)
{
	return OTAPI_Wrap::LoadPubkey_Signing(
		USER_ID
		);
}

bool OTAPI_Basic::VerifyUserPrivateKey(const std::string & USER_ID)
{
	return OTAPI_Wrap::VerifyUserPrivateKey(
		USER_ID
		);
}

std::string OTAPI_Basic::LoadPurse(
	const std::string & SERVER_ID,
	const std::string & ASSET_TYPE_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::LoadPurse(
		SERVER_ID,
		ASSET_TYPE_ID,
		USER_ID
		);
}

std::string OTAPI_Basic::LoadMint(
	const std::string & SERVER_ID,
	const std::string & ASSET_TYPE_ID)
{
	return OTAPI_Wrap::LoadMint(
		SERVER_ID,
		ASSET_TYPE_ID
		);
}

std::string OTAPI_Basic::LoadAssetContract(const std::string & ASSET_TYPE_ID)
{
	return OTAPI_Wrap::LoadAssetContract(
		ASSET_TYPE_ID
		);
}

std::string OTAPI_Basic::LoadServerContract(const std::string & SERVER_ID)
{
	return OTAPI_Wrap::LoadServerContract(
		SERVER_ID
		);			
}

bool OTAPI_Basic::Mint_IsStillGood(
	const std::string & SERVER_ID,
	const std::string & ASSET_TYPE_ID
	)
{
	return OTAPI_Wrap::Mint_IsStillGood(
		SERVER_ID,
		ASSET_TYPE_ID
		);
}

bool OTAPI_Basic::IsBasketCurrency(const std::string & ASSET_TYPE_ID)
{
	return OTAPI_Wrap::IsBasketCurrency(
		ASSET_TYPE_ID
		);
}

long OTAPI_Basic::Basket_GetMemberCount(const std::string & BASKET_ASSET_TYPE_ID)
{
	return OTAPI_Wrap::Basket_GetMemberCount(
		BASKET_ASSET_TYPE_ID
		);
}

std::string OTAPI_Basic::Basket_GetMemberType(
	const std::string & BASKET_ASSET_TYPE_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Basket_GetMemberType(
		BASKET_ASSET_TYPE_ID,
		nIndex
		);
}

std::string OTAPI_Basic::Basket_GetMinimumTransferAmount(const std::string & BASKET_ASSET_TYPE_ID)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::Basket_GetMinimumTransferAmount(BASKET_ASSET_TYPE_ID));
}

std::string OTAPI_Basic::Basket_GetMemberMinimumTransferAmount(
	const std::string & BASKET_ASSET_TYPE_ID,
	const long & nIndex
	)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::Basket_GetMemberMinimumTransferAmount(
		BASKET_ASSET_TYPE_ID,
		nIndex
		));
}

std::string OTAPI_Basic::LoadAssetAccount(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::LoadAssetAccount(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::LoadInbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::LoadInbox(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::LoadOutbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::LoadOutbox(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);				
}

std::string OTAPI_Basic::LoadInboxNoVerify(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::LoadInboxNoVerify(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);				
}

std::string OTAPI_Basic::LoadOutboxNoVerify(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::LoadOutboxNoVerify(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);					
}

std::string OTAPI_Basic::LoadPaymentInbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::LoadPaymentInbox(
		SERVER_ID,
		USER_ID
		);					
}

std::string OTAPI_Basic::LoadPaymentInboxNoVerify(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::LoadPaymentInboxNoVerify(
		SERVER_ID,
		USER_ID
		);				
}

std::string OTAPI_Basic::LoadRecordBox(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::LoadRecordBox(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::LoadRecordBoxNoVerify(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::LoadRecordBoxNoVerify(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);
}

std::string OTAPI_Basic::LoadExpiredBox(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::LoadExpiredBox(
		SERVER_ID,
		USER_ID
		);
}

std::string OTAPI_Basic::LoadExpiredBoxNoVerify(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::LoadExpiredBoxNoVerify(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::Ledger_GetCount(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_LEDGER
	)
{
	return OTAPI_Wrap::Ledger_GetCount(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_LEDGER
		);
}

std::string OTAPI_Basic::Ledger_CreateResponse(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & ORIGINAL_LEDGER
	)
{
	return OTAPI_Wrap::Ledger_CreateResponse(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		ORIGINAL_LEDGER
		);
}

std::string OTAPI_Basic::Ledger_GetTransactionByIndex(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_LEDGER,
	const long & nIndex
	)
{
	return OTAPI_Wrap::Ledger_GetTransactionByIndex(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_LEDGER,
		nIndex
		);
}

std::string OTAPI_Basic::Ledger_GetTransactionByID(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_LEDGER,
	const std::string & TRANSACTION_NUMBER
	)
{
	//const int64_t lTRANSACTION_NUMBER		= OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER);

	return OTAPI_Wrap::Ledger_GetTransactionByID(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_LEDGER,
		OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER)
		);
}

std::string OTAPI_Basic::Ledger_GetTransactionIDByIndex(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_LEDGER,
	const long & nIndex
	)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::Ledger_GetTransactionIDByIndex(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_LEDGER,
		nIndex
		));
}

std::string OTAPI_Basic::Ledger_AddTransaction(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_LEDGER,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Ledger_AddTransaction(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_LEDGER,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::Transaction_CreateResponse(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & RESPONSE_LEDGER,
	const std::string & ORIGINAL_TRANSACTION,
	const bool & BOOL_DO_I_ACCEPT
	)
{
	return OTAPI_Wrap::Transaction_CreateResponse(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		RESPONSE_LEDGER,
		ORIGINAL_TRANSACTION,
		BOOL_DO_I_ACCEPT
		);
}

std::string OTAPI_Basic::Ledger_FinalizeResponse(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_LEDGER
	)
{
	return OTAPI_Wrap::Ledger_FinalizeResponse(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_LEDGER
		);
}

std::string OTAPI_Basic::Ledger_GetInstrument(
                                         const std::string & SERVER_ID,
                                         const std::string & USER_ID,
                                         const std::string & ACCOUNT_ID,
                                         const std::string & THE_LEDGER,
                                         const long & nIndex
                                         )
{
	return OTAPI_Wrap::Ledger_GetInstrument(
                                            SERVER_ID,
                                            USER_ID,
                                            ACCOUNT_ID,
                                            THE_LEDGER,
                                            nIndex
                                            );
}



bool OTAPI_Basic::RecordPayment(
                                const std::string & SERVER_ID,
                                const std::string & USER_ID,
                                const bool   & bIsInbox,
                                const long   & nIndex,
                                const bool   & bSaveCopy)
{
	return OTAPI_Wrap::RecordPayment(
                                     SERVER_ID,
                                     USER_ID,
                                     bIsInbox,
                                     nIndex,
                                     bSaveCopy
                                     );
}



bool OTAPI_Basic::ClearRecord(
                              const std::string & SERVER_ID,
                              const std::string & USER_ID,
                              const std::string & ACCOUNT_ID, // USER_ID can be passed here as well.
                              const long   & nIndex,
                              const bool   & bClearAll) // if true, nIndex is ignored.
{
	return OTAPI_Wrap::ClearRecord(
                                   SERVER_ID,
                                   USER_ID,
                                   ACCOUNT_ID,
                                   nIndex,
                                   bClearAll
                                   );
}

bool OTAPI_Basic::ClearExpired(
                               const std::string & SERVER_ID,
                               const std::string & USER_ID,
                               const long   & nIndex,
                               const bool   & bClearAll) // if true, nIndex is ignored.
{
	return OTAPI_Wrap::ClearExpired(
                                    SERVER_ID,
                                    USER_ID,
                                    nIndex,
                                    bClearAll
                                    );
}



std::string OTAPI_Basic::Transaction_GetType(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetType(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::ReplyNotice_GetRequestNum(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::ReplyNotice_GetRequestNum(
		SERVER_ID,
		USER_ID,
		THE_TRANSACTION
		));
}

std::string OTAPI_Basic::Transaction_GetVoucher(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetVoucher(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

// OT_BOOL (long) contains -1, 0, or 1
long OTAPI_Basic::Transaction_GetSuccess(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetSuccess(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

long OTAPI_Basic::Transaction_IsCanceled(
    const std::string & SERVER_ID,
    const std::string & USER_ID,
    const std::string & ACCOUNT_ID,
    const std::string & THE_TRANSACTION
    )
{
	return OTAPI_Wrap::Transaction_IsCanceled(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

// OT_BOOL (long) contains -1, 0, or 1
long OTAPI_Basic::Transaction_GetBalanceAgreementSuccess(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetBalanceAgreementSuccess(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::Transaction_GetDateSigned(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::Transaction_GetDateSigned(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		));
}

std::string OTAPI_Basic::Transaction_GetAmount(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::Transaction_GetAmount(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		));
}

std::string OTAPI_Basic::Pending_GetNote(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Pending_GetNote(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::Transaction_GetSenderUserID(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetSenderUserID(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::Transaction_GetSenderAcctID(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetSenderAcctID(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::Transaction_GetRecipientUserID(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetRecipientUserID(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::Transaction_GetRecipientAcctID(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::Transaction_GetRecipientAcctID(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		);
}

std::string OTAPI_Basic::Transaction_GetDisplayReferenceToNum(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_TRANSACTION
	)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_TRANSACTION
		));
}

bool OTAPI_Basic::SavePurse(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & USER_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::SavePurse(SERVER_ID,ASSET_TYPE_ID,USER_ID,THE_PURSE);
	}

std::string OTAPI_Basic::CreatePurse(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & OWNER_ID,
		const std::string & SIGNER_ID
		)
	{
		return OTAPI_Wrap::CreatePurse(SERVER_ID,ASSET_TYPE_ID,OWNER_ID,SIGNER_ID);
	}


std::string OTAPI_Basic::CreatePurse_Passphrase(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & SIGNER_ID
		)
	{
		return OTAPI_Wrap::CreatePurse_Passphrase(SERVER_ID,ASSET_TYPE_ID,SIGNER_ID);
	}


std::string OTAPI_Basic::Purse_GetTotalValue(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::LongToString(OTAPI_Wrap::Purse_GetTotalValue(SERVER_ID,ASSET_TYPE_ID,THE_PURSE));
	}

long OTAPI_Basic::Purse_Count(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::Purse_Count(SERVER_ID,ASSET_TYPE_ID,THE_PURSE);
	}


bool OTAPI_Basic::Purse_HasPassword(
		const std::string & SERVER_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::Purse_HasPassword(SERVER_ID,THE_PURSE);
	}

std::string OTAPI_Basic::Purse_Peek(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & OWNER_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::Purse_Peek(SERVER_ID,ASSET_TYPE_ID,OWNER_ID,THE_PURSE);
	}

std::string OTAPI_Basic::Purse_Pop(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & OWNER_OR_SIGNER_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::Purse_Pop(SERVER_ID,ASSET_TYPE_ID,OWNER_OR_SIGNER_ID,THE_PURSE);
	}

std::string OTAPI_Basic::Purse_Push(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & SIGNER_ID,
		const std::string & OWNER_ID,
		const std::string & THE_PURSE,
		const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::Purse_Push(SERVER_ID,ASSET_TYPE_ID,SIGNER_ID,OWNER_ID,THE_PURSE,THE_TOKEN);
	}

std::string OTAPI_Basic::Purse_Empty(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & SIGNER_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::Purse_Empty(SERVER_ID,ASSET_TYPE_ID,SIGNER_ID,THE_PURSE);
	}


bool OTAPI_Basic::Wallet_ImportPurse(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & USER_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::Wallet_ImportPurse(SERVER_ID,ASSET_TYPE_ID,USER_ID,THE_PURSE);
	}

long OTAPI_Basic::exchangePurse(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & USER_ID,
		const std::string & THE_PURSE
		)
	{
		return OTAPI_Wrap::exchangePurse(SERVER_ID,ASSET_TYPE_ID,USER_ID,THE_PURSE);
	}


std::string OTAPI_Basic::Token_ChangeOwner(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_TOKEN,
		const std::string & SIGNER_NYM_ID,
		const std::string & OLD_OWNER,
		const std::string & NEW_OWNER
		)
	{
		return OTAPI_Wrap::Token_ChangeOwner(SERVER_ID,ASSET_TYPE_ID,THE_TOKEN,SIGNER_NYM_ID,OLD_OWNER,NEW_OWNER);
	}

std::string OTAPI_Basic::Token_GetID(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::Token_GetID(SERVER_ID,ASSET_TYPE_ID,THE_TOKEN);
	}

std::string OTAPI_Basic::Token_GetDenomination(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::LongToString(OTAPI_Wrap::Token_GetDenomination(SERVER_ID,ASSET_TYPE_ID,THE_TOKEN));
	}

long OTAPI_Basic::Token_GetSeries(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::Token_GetSeries(SERVER_ID,ASSET_TYPE_ID,THE_TOKEN);
	}


std::string OTAPI_Basic::Token_GetValidFrom(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::LongToString(OTAPI_Wrap::Token_GetValidFrom(SERVER_ID,ASSET_TYPE_ID,THE_TOKEN));
	}

std::string OTAPI_Basic::Token_GetValidTo(
		const std::string & SERVER_ID,
		const std::string & ASSET_TYPE_ID,
		const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::LongToString(OTAPI_Wrap::Token_GetValidTo(SERVER_ID,ASSET_TYPE_ID,THE_TOKEN));
	}

std::string OTAPI_Basic::Token_GetAssetID(
	const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::Token_GetAssetID(THE_TOKEN);
	}

std::string OTAPI_Basic::Token_GetServerID(
	const std::string & THE_TOKEN
		)
	{
		return OTAPI_Wrap::Token_GetServerID(THE_TOKEN);
	}

std::string OTAPI_Basic::Instrmnt_GetAmount (const std::string & THE_INSTRUMENT)          { return OTAPI_Wrap::LongToString(OTAPI_Wrap::Instrmnt_GetAmount(THE_INSTRUMENT)); }
std::string OTAPI_Basic::Instrmnt_GetTransNum (const std::string & THE_INSTRUMENT)        { return OTAPI_Wrap::LongToString(OTAPI_Wrap::Instrmnt_GetTransNum(THE_INSTRUMENT)); }
std::string OTAPI_Basic::Instrmnt_GetValidFrom (const std::string & THE_INSTRUMENT)       { return OTAPI_Wrap::LongToString(OTAPI_Wrap::Instrmnt_GetValidFrom(THE_INSTRUMENT)); }
std::string OTAPI_Basic::Instrmnt_GetValidTo (const std::string & THE_INSTRUMENT)         { return OTAPI_Wrap::LongToString(OTAPI_Wrap::Instrmnt_GetValidTo(THE_INSTRUMENT)); }
std::string OTAPI_Basic::Instrmnt_GetMemo (const std::string & THE_INSTRUMENT)            { return OTAPI_Wrap::Instrmnt_GetMemo(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetType (const std::string & THE_INSTRUMENT)            { return OTAPI_Wrap::Instrmnt_GetType(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetServerID (const std::string & THE_INSTRUMENT)        { return OTAPI_Wrap::Instrmnt_GetServerID(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetAssetID (const std::string & THE_INSTRUMENT)         { return OTAPI_Wrap::Instrmnt_GetAssetID(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetSenderUserID (const std::string & THE_INSTRUMENT)    { return OTAPI_Wrap::Instrmnt_GetSenderUserID(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetSenderAcctID (const std::string & THE_INSTRUMENT)    { return OTAPI_Wrap::Instrmnt_GetSenderAcctID(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetRemitterUserID(const std::string & THE_INSTRUMENT)   { return OTAPI_Wrap::Instrmnt_GetRemitterUserID(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetRemitterAcctID(const std::string & THE_INSTRUMENT)   { return OTAPI_Wrap::Instrmnt_GetRemitterAcctID(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetRecipientUserID(const std::string & THE_INSTRUMENT)  { return OTAPI_Wrap::Instrmnt_GetRecipientUserID(THE_INSTRUMENT); }
std::string OTAPI_Basic::Instrmnt_GetRecipientAcctID(const std::string & THE_INSTRUMENT)  { return OTAPI_Wrap::Instrmnt_GetRecipientAcctID(THE_INSTRUMENT); }

long OTAPI_Basic::checkServerID(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::checkServerID(
		SERVER_ID,
		USER_ID
		);
}


long OTAPI_Basic::createUserAccount(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::createUserAccount(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::deleteUserAccount(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::deleteUserAccount(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::deleteAssetAccount(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID
	)
{
	return OTAPI_Wrap::deleteAssetAccount(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID
		);
}

long OTAPI_Basic::usageCredits(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & USER_ID_CHECK,
	const std::string & ADJUSTMENT
	)
{
	return OTAPI_Wrap::usageCredits(
		SERVER_ID,
		USER_ID,
		USER_ID_CHECK,
		OTAPI_Wrap::StringToLong(ADJUSTMENT)
		);
}

std::string OTAPI_Basic::Message_GetUsageCredits(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::LongToString(OTAPI_Wrap::Message_GetUsageCredits(
		THE_MESSAGE
		));
}

long OTAPI_Basic::checkUser(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & USER_ID_CHECK
	)
{
	return OTAPI_Wrap::checkUser(
		SERVER_ID,
		USER_ID,
		USER_ID_CHECK
		);
}

long OTAPI_Basic::sendUserMessage(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & USER_ID_RECIPIENT,
	const std::string & RECIPIENT_PUBKEY,
	const std::string & THE_MESSAGE
	)
{
	return OTAPI_Wrap::sendUserMessage(
		SERVER_ID,
		USER_ID,
		USER_ID_RECIPIENT,
		RECIPIENT_PUBKEY,
		THE_MESSAGE
		);
}

long OTAPI_Basic::sendUserInstrument(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & USER_ID_RECIPIENT,
	const std::string & RECIPIENT_PUBKEY,
    const std::string & THE_INSTRUMENT,
    const std::string & INSTRUMENT_FOR_SENDER
	)
{
	return OTAPI_Wrap::sendUserInstrument(
		SERVER_ID,
		USER_ID,
		USER_ID_RECIPIENT,
		RECIPIENT_PUBKEY,
		THE_INSTRUMENT,
        INSTRUMENT_FOR_SENDER                                  
		);
}

long OTAPI_Basic::getRequest(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::getRequest(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::getTransactionNumber(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::getTransactionNumber(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::issueAssetType(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & THE_CONTRACT
	)
{
	return OTAPI_Wrap::issueAssetType(
		SERVER_ID,
		USER_ID,
		THE_CONTRACT
		);
}

long OTAPI_Basic::getContract(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ASSET_ID
	)
{
	return OTAPI_Wrap::getContract(
		SERVER_ID,
		USER_ID,
		ASSET_ID
		);
}

long OTAPI_Basic::getMint(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ASSET_ID
	)
{
	return OTAPI_Wrap::getMint(
		SERVER_ID,
		USER_ID,
		ASSET_ID
		);
}

long OTAPI_Basic::createAssetAccount(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ASSET_ID
	)
{
	return OTAPI_Wrap::createAssetAccount(
		SERVER_ID,
		USER_ID,
		ASSET_ID
		);
}


// NOTE: Deprecated. Replaced by getAccountFiles
long OTAPI_Basic::getAccount(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID
	)
{
	return OTAPI_Wrap::getAccount(
		SERVER_ID,
		USER_ID,
		ACCT_ID
		);
}

long OTAPI_Basic::getAccountFiles(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID
	)
{
	return OTAPI_Wrap::getAccountFiles(
		SERVER_ID,
		USER_ID,
		ACCT_ID
		);
}


std::string OTAPI_Basic::GenerateBasketCreation(
	const std::string & USER_ID,
	const std::string & MINIMUM_TRANSFER
	)
{
	//const int64_t lMINIMUM_TRANSFER = OTAPI_Wrap::StringToLong(MINIMUM_TRANSFER);

	return OTAPI_Wrap::GenerateBasketCreation(
		USER_ID,
		OTAPI_Wrap::StringToLong(MINIMUM_TRANSFER)
		);
}

std::string OTAPI_Basic::AddBasketCreationItem(
	const std::string & USER_ID,
	const std::string & THE_BASKET,
	const std::string & ASSET_TYPE_ID,
	const std::string & MINIMUM_TRANSFER
	)
{
	//const int64_t lMINIMUM_TRANSFER = OTAPI_Wrap::StringToLong(MINIMUM_TRANSFER);

	return OTAPI_Wrap::AddBasketCreationItem(
		USER_ID,
		THE_BASKET,
		ASSET_TYPE_ID,
		OTAPI_Wrap::StringToLong(MINIMUM_TRANSFER)
		);	
}

long OTAPI_Basic::issueBasket(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & THE_BASKET
	)
{
	return OTAPI_Wrap::issueBasket(
		SERVER_ID,
		USER_ID,
		THE_BASKET
		);
}

std::string OTAPI_Basic::GenerateBasketExchange(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & BASKET_ASSET_TYPE_ID,
	const std::string & BASKET_ASSET_ACCT_ID,
	// -------------------------------------
	const long & TRANSFER_MULTIPLE
	)
{
	return OTAPI_Wrap::GenerateBasketExchange(
		SERVER_ID,
		USER_ID,
		BASKET_ASSET_TYPE_ID,
		BASKET_ASSET_ACCT_ID,
		TRANSFER_MULTIPLE
		);
}

std::string OTAPI_Basic::AddBasketExchangeItem(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & THE_BASKET, 
	const std::string & ASSET_TYPE_ID,
	const std::string & ASSET_ACCT_ID
	)
{
	return OTAPI_Wrap::AddBasketExchangeItem(
		SERVER_ID,
		USER_ID,
		THE_BASKET,
		ASSET_TYPE_ID,
		ASSET_ACCT_ID
		);
}

long OTAPI_Basic::exchangeBasket(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & BASKET_ASSET_ID,
	const std::string & THE_BASKET,
	const bool & BOOL_EXCHANGE_IN_OR_OUT
	)
{
	return OTAPI_Wrap::exchangeBasket(
		SERVER_ID,
		USER_ID,
		BASKET_ASSET_ID,
		THE_BASKET,
		BOOL_EXCHANGE_IN_OR_OUT
		);
}

long OTAPI_Basic::notarizeWithdrawal(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID,
	const std::string & AMOUNT
	)
{
	return OTAPI_Wrap::notarizeWithdrawal(
		SERVER_ID,
		USER_ID,
		ACCT_ID,
		OTAPI_Wrap::StringToLong(AMOUNT)
		);
}

long OTAPI_Basic::notarizeDeposit(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID,
	const std::string & THE_PURSE
	)
{
	return OTAPI_Wrap::notarizeDeposit(
		SERVER_ID,
		USER_ID,
		ACCT_ID,
		THE_PURSE
		);
}

long OTAPI_Basic::notarizeTransfer(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_FROM,
	const std::string & ACCT_TO,
	const std::string & AMOUNT,
	const std::string & NOTE
	)
{
	//const int64_t lAMOUNT = OTAPI_Wrap::StringToLong(AMOUNT);

	return OTAPI_Wrap::notarizeTransfer(
		SERVER_ID,
		USER_ID,
		ACCT_FROM,
		ACCT_TO,
		OTAPI_Wrap::StringToLong(AMOUNT),
		NOTE
		);
}

// NOTE: Deprecated. Replaced by getAccountFiles
long OTAPI_Basic::getInbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID
	)
{
	return OTAPI_Wrap::getInbox(
		SERVER_ID,
		USER_ID,
		ACCT_ID
		);
}

// NOTE: Deprecated. Replaced by getAccountFiles
long OTAPI_Basic::getOutbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID
	)
{
	return OTAPI_Wrap::getOutbox(
		SERVER_ID,
		USER_ID,
		ACCT_ID
		);
}

long OTAPI_Basic::getNymbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::getNymbox(
		SERVER_ID,
		USER_ID
		);
}

std::string OTAPI_Basic::LoadNymbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::LoadNymbox(
		SERVER_ID,
		USER_ID
		);				
}

std::string OTAPI_Basic::LoadNymboxNoVerify(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::LoadNymboxNoVerify(
		SERVER_ID,
		USER_ID
		);	
}

std::string OTAPI_Basic::Nymbox_GetReplyNotice(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & REQUEST_NUMBER
	)
{
	//const int64_t lREQUEST_NUMBER = OTAPI_Wrap::StringToLong(REQUEST_NUMBER);

	return OTAPI_Wrap::Nymbox_GetReplyNotice(
		SERVER_ID,
		USER_ID,
		OTAPI_Wrap::StringToLong(REQUEST_NUMBER)
		);	
}

bool OTAPI_Basic::HaveAlreadySeenReply(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & REQUEST_NUMBER
	)
{
	//const int64_t lREQUEST_NUMBER = OTAPI_Wrap::StringToLong(REQUEST_NUMBER);

	return OTAPI_Wrap::HaveAlreadySeenReply(
		SERVER_ID,
		USER_ID,
		OTAPI_Wrap::StringToLong(REQUEST_NUMBER)
		);
}

long OTAPI_Basic::getBoxReceipt(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const long & nBoxType,
	const std::string & TRANSACTION_NUMBER
	)
{
	//const int64_t lTRANSACTION_NUMBER = OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER);

	return OTAPI_Wrap::getBoxReceipt(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		nBoxType,
		OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER)
		);
}

bool OTAPI_Basic::DoesBoxReceiptExist(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const long & nBoxType,
	const std::string & TRANSACTION_NUMBER
	)
{
	//const int64_t lTRANSACTION_NUMBER = OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER);

	return OTAPI_Wrap::DoesBoxReceiptExist(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		nBoxType,
		OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER)
		);
}
long OTAPI_Basic::processInbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID,
	const std::string & ACCT_LEDGER
	)
{
	return OTAPI_Wrap::processInbox(
		SERVER_ID,
		USER_ID,
		ACCT_ID,
		ACCT_LEDGER
		);
}

long OTAPI_Basic::processNymbox(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::processNymbox(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::withdrawVoucher(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID,
	const std::string & RECIPIENT_USER_ID,
	const std::string & CHEQUE_MEMO,
	const std::string & AMOUNT
	)
{
	//const int64_t lAMOUNT = OTAPI_Wrap::StringToLong(AMOUNT);

	return OTAPI_Wrap::withdrawVoucher(
		SERVER_ID,
		USER_ID,
		ACCT_ID,
		RECIPIENT_USER_ID,
		CHEQUE_MEMO,
		OTAPI_Wrap::StringToLong(AMOUNT)
		);
}

long OTAPI_Basic::payDividend(
	const std::string & SERVER_ID,
	const std::string & ISSUER_USER_ID,
	const std::string & DIVIDEND_FROM_ACCT_ID,
	const std::string & SHARES_ASSET_TYPE_ID,
	const std::string & DIVIDEND_MEMO,
	const std::string & AMOUNT_PER_SHARE
	)
{
	//const int64_t lAMOUNT_PER_SHARE = OTAPI_Wrap::StringToLong(AMOUNT_PER_SHARE);

	return OTAPI_Wrap::payDividend(
		SERVER_ID,
		ISSUER_USER_ID,
		DIVIDEND_FROM_ACCT_ID,
		SHARES_ASSET_TYPE_ID,
		DIVIDEND_MEMO,
		OTAPI_Wrap::StringToLong(AMOUNT_PER_SHARE)
		);
}

long OTAPI_Basic::depositCheque(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCT_ID,
	const std::string & THE_CHEQUE
	)
{
	return OTAPI_Wrap::depositCheque(
		SERVER_ID,
		USER_ID,
		ACCT_ID,
		THE_CHEQUE
		);
}

long OTAPI_Basic::depositPaymentPlan(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & THE_PAYMENT_PLAN
	)
{
	return OTAPI_Wrap::depositPaymentPlan(
		SERVER_ID,
		USER_ID,
		THE_PAYMENT_PLAN
		);
}

long OTAPI_Basic::issueMarketOffer(
	const std::string & ASSET_ACCT_ID,
	const std::string & CURRENCY_ACCT_ID,
	const std::string & MARKET_SCALE,
	const std::string & MINIMUM_INCREMENT,
	const std::string & TOTAL_ASSETS_ON_OFFER,
	const std::string & PRICE_LIMIT,
	const bool   & bBuyingOrSelling,
    const std::string & LIFESPAN_IN_SECONDS,
    const std::string & STOP_SIGN,
    const std::string & ACTIVATION_PRICE
	)
{

	return OTAPI_Wrap::issueMarketOffer(
		ASSET_ACCT_ID,
		CURRENCY_ACCT_ID,
		OTAPI_Wrap::StringToLong(MARKET_SCALE),
		OTAPI_Wrap::StringToLong(MINIMUM_INCREMENT),
		OTAPI_Wrap::StringToLong(TOTAL_ASSETS_ON_OFFER),
		OTAPI_Wrap::StringToLong(PRICE_LIMIT),
		bBuyingOrSelling,
        OTAPI_Wrap::StringToLong(LIFESPAN_IN_SECONDS),
        STOP_SIGN,
        OTAPI_Wrap::StringToLong(ACTIVATION_PRICE)
		);
}

long OTAPI_Basic::getMarketList(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::getMarketList(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::getMarketOffers(
	const std::string & SERVER_ID,
	const std::string & USER_ID, 
	const std::string & MARKET_ID,
	const std::string & MAX_DEPTH
	)
{
	//const int64_t lMAX_DEPTH = OTAPI_Wrap::StringToLong(MAX_DEPTH);

	return OTAPI_Wrap::getMarketOffers(
		SERVER_ID,
		USER_ID,
		MARKET_ID,
		OTAPI_Wrap::StringToLong(MAX_DEPTH)
		);
}

long OTAPI_Basic::getMarketRecentTrades(
	const std::string & SERVER_ID,
	const std::string & USER_ID, 
	const std::string & MARKET_ID
	)
{
	return OTAPI_Wrap::getMarketRecentTrades(
		SERVER_ID,
		USER_ID,
		MARKET_ID
		);
}

long OTAPI_Basic::getNym_MarketOffers(
	const std::string & SERVER_ID,
	const std::string & USER_ID
	)
{
	return OTAPI_Wrap::getNym_MarketOffers(
		SERVER_ID,
		USER_ID
		);
}

long OTAPI_Basic::killMarketOffer(
	const std::string & SERVER_ID, 
	const std::string & USER_ID, 
	const std::string & ASSET_ACCT_ID, 
	const std::string & TRANSACTION_NUMBER
	)
{
	//const int64_t lTRANSACTION_NUMBER = OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER);

	return OTAPI_Wrap::killMarketOffer(
		SERVER_ID,
		USER_ID,
		ASSET_ACCT_ID,
		OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER)
		);
}

long OTAPI_Basic::killPaymentPlan(
	const std::string & SERVER_ID, 
	const std::string & USER_ID, 
	const std::string & FROM_ACCT_ID, 
	const std::string & TRANSACTION_NUMBER
	)
{
	//const int64_t lTRANSACTION_NUMBER = OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER);

	return OTAPI_Wrap::killPaymentPlan(
		SERVER_ID,
		USER_ID,
		FROM_ACCT_ID,
		OTAPI_Wrap::StringToLong(TRANSACTION_NUMBER)
		);	
}

std::string OTAPI_Basic::PopMessageBuffer(
	const std::string & REQUEST_NUMBER,
	const std::string & SERVER_ID, 
	const std::string & USER_ID
	)
{
	//const int64_t lREQUEST_NUMBER = OTAPI_Wrap::StringToLong(REQUEST_NUMBER);

	return OTAPI_Wrap::PopMessageBuffer(
		OTAPI_Wrap::StringToLong(REQUEST_NUMBER),
		SERVER_ID,
		USER_ID
		);
}

void OTAPI_Basic::FlushMessageBuffer()
{
	return OTAPI_Wrap::FlushMessageBuffer();
}

std::string OTAPI_Basic::GetSentMessage(
	const std::string & REQUEST_NUMBER,
	const std::string & SERVER_ID, 
	const std::string & USER_ID
	)
{	
	//const int64_t lREQUEST_NUMBER = OTAPI_Wrap::StringToLong(REQUEST_NUMBER);

	return OTAPI_Wrap::GetSentMessage(
		OTAPI_Wrap::StringToLong(REQUEST_NUMBER),
		SERVER_ID,
		USER_ID
		);	
}

bool OTAPI_Basic::RemoveSentMessage(
	const std::string & REQUEST_NUMBER,
	const std::string & SERVER_ID, 
	const std::string & USER_ID
	)
{	
	//const int64_t lREQUEST_NUMBER = OTAPI_Wrap::StringToLong(REQUEST_NUMBER);

	return OTAPI_Wrap::RemoveSentMessage(
		OTAPI_Wrap::StringToLong(REQUEST_NUMBER),
		SERVER_ID,
		USER_ID
		);
}

void OTAPI_Basic::FlushSentMessages(
	const bool & bHarvestingForRetry,
	const std::string & SERVER_ID, 
	const std::string & USER_ID,
	const std::string & THE_NYMBOX
	)
{
	return OTAPI_Wrap::FlushSentMessages(
		bHarvestingForRetry,
		SERVER_ID,
		USER_ID,
		THE_NYMBOX
		);
}

void OTAPI_Basic::Sleep(const std::string & MILLISECONDS)
{
	//const int64_t lMILLISECONDS = OTAPI_Wrap::StringToLong(MILLISECONDS);

	return OTAPI_Wrap::Sleep(
		OTAPI_Wrap::StringToLong(MILLISECONDS)
		//MILLISECONDS
		);
}

bool OTAPI_Basic::ResyncNymWithServer(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & THE_MESSAGE
	)
{
	return OTAPI_Wrap::ResyncNymWithServer(
		SERVER_ID,
		USER_ID,
		THE_MESSAGE
		);
}

std::string OTAPI_Basic::Message_GetCommand(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetCommand(
		THE_MESSAGE
		);		
}

long OTAPI_Basic::Message_GetSuccess(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetSuccess(
		THE_MESSAGE
		);	
}

long OTAPI_Basic::queryAssetTypes(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ENCODED_MAP
	)
{
	return OTAPI_Wrap::queryAssetTypes(
		SERVER_ID,
		USER_ID,
		ENCODED_MAP
		);	
}

std::string OTAPI_Basic::Message_GetPayload(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetPayload(
		THE_MESSAGE
		);		
}

long OTAPI_Basic::Message_GetDepth(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetDepth(
		THE_MESSAGE
		);
}

long OTAPI_Basic::Message_GetTransactionSuccess(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_MESSAGE
	)
{
	return OTAPI_Wrap::Message_GetTransactionSuccess(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_MESSAGE
		);
}


long OTAPI_Basic::Message_IsTransactionCanceled(
    const std::string & SERVER_ID,
    const std::string & USER_ID,
    const std::string & ACCOUNT_ID,
    const std::string & THE_MESSAGE
    )
{
	return OTAPI_Wrap::Message_IsTransactionCanceled(
        SERVER_ID,
        USER_ID,
        ACCOUNT_ID,
        THE_MESSAGE
        );    
}

long OTAPI_Basic::Message_GetBalanceAgreementSuccess(
	const std::string & SERVER_ID,
	const std::string & USER_ID,
	const std::string & ACCOUNT_ID,
	const std::string & THE_MESSAGE
	)
{
	return OTAPI_Wrap::Message_GetBalanceAgreementSuccess(
		SERVER_ID,
		USER_ID,
		ACCOUNT_ID,
		THE_MESSAGE
		);
}

std::string OTAPI_Basic::Message_GetLedger(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetLedger(
		THE_MESSAGE
		);			
}

std::string OTAPI_Basic::Message_GetNewAssetTypeID(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetNewAssetTypeID(
		THE_MESSAGE
		);	
}

std::string OTAPI_Basic::Message_GetNewIssuerAcctID(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetNewIssuerAcctID(
		THE_MESSAGE
		);
}

std::string OTAPI_Basic::Message_GetNewAcctID(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetNewAcctID(
		THE_MESSAGE
		);
}

std::string OTAPI_Basic::Message_GetNymboxHash(const std::string & THE_MESSAGE)
{
	return OTAPI_Wrap::Message_GetNymboxHash(
		THE_MESSAGE
		);
}

bool OTAPI_Basic::ConnectServer(
	const std::string & SERVER_ID,
	const std::string & USER_ID, 
	const std::string & strCA_FILE,
	const std::string & strKEY_FILE, 
	const std::string & strKEY_PASSWORD
	)
{
	return OTAPI_Wrap::ConnectServer(
		SERVER_ID,
		USER_ID,
		strCA_FILE,
		strKEY_FILE,
		strKEY_PASSWORD
		);
}

bool OTAPI_Basic::ProcessSockets()
{
	return OTAPI_Wrap::ProcessSockets();
}


