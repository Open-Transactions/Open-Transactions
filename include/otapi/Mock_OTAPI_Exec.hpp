/************************************************************************************
*
* Mock_OTAPI_Exec.h --
* This file is wrapped by ChaiScript (or any scripting engine...) for writing
* OT Script, whereas OTAPI_Basic.h is wrapped by SWIG (Python, Ruby, PHP, Java,
* etc.)
*
* da2ce7: chaiscript (since the last 2 weeks), makes use of the OTAPI.h,
*         where the types are bool, int32_t, int64_t, std::string


3:25:14 PM FellowTraveler: so chaiscript is using this file OTAPI.h, and the data types are
int32_t for "int" and int64_t for "long" -- right?
3:25:14 PM FellowTraveler: and strings are only for real strings.
3:25:15 PM FellowTraveler: right?
3:27:19 PM FellowTraveler: in other words, where I might pass int for  −1, or 0, or 1 or 2,
then chaiscript is using int32_t —— whereas where I might pass long for a transaction #,
then chaiscript is usingint64_t
3:27:31 PM FellowTraveler: Also, where I might pass a currency AMOUNT, chaiscript is using int64_t
3:27:32 PM FellowTraveler: right?
3:28:32 PM da2ce7: yep... -1, 0, 1, 2 are int > int32_t
3:28:41 PM da2ce7: but in siwg are long
3:29:02 PM da2ce7: and AMOUNT long > int64_t
3:29:08 PM da2ce7: and in swig will be std::string
3:30:32 PM FellowTraveler: why no int64_t in swig?
3:30:35 PM FellowTraveler: doesn't work ?
3:31:20 PM da2ce7: FellowTraveler: yep it makes this messy SWIG_TYPE_INT64_T  and is just a mess

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


#ifndef __Mock_OTAPI_Exec_H__
#define __Mock_OTAPI_Exec_H__

#include "gmock/gmock.h"

#include "OTAPI_Exec.hpp"


class Mock_OTAPI_Exec : public OTAPI_Exec
{
private:
	OTAPI_Exec * execOld;

public:
	// have the constructor/destructor created elsewhere to limit comnpile time
	// building the mock ctor/dtor is extremely costly due to heavy templating!
	Mock_OTAPI_Exec();
	virtual ~Mock_OTAPI_Exec();

	// leave logging intact
	//MOCK_METHOD2(Output, void (const int32_t & nLogLevel, const std::string & strOutput));

	// this one gets called way too much and inconsistently to mock for now
	// MOCK_METHOD0(GetTime, time_t ());

	// seriously, Sleep(50) in every SendRequest? Ignore it here. It should be removed
	MOCK_METHOD1(Sleep, void(const int64_t & MILLISECONDS));

	MOCK_METHOD1(StringToLong, int64_t (const std::string & strNumber));
	MOCK_METHOD1(LongToString, std::string (const int64_t & lNumber));
	MOCK_METHOD0(AppInit, bool ());
	MOCK_METHOD0(AppCleanup, bool ());
	MOCK_METHOD1(SetWallet, bool (const std::string & strWalletFilename));
	MOCK_METHOD0(WalletExists, bool ());
	MOCK_METHOD0(LoadWallet, bool ());
	MOCK_METHOD0(SwitchWallet, bool ());
	MOCK_METHOD2(NumList_Add, std::string (const std::string & strNumList, const std::string & strNumbers));
	MOCK_METHOD2(NumList_Remove, std::string (const std::string & strNumList, const std::string & strNumbers));
	MOCK_METHOD2(NumList_VerifyQuery, bool (const std::string & strNumList, const std::string & strNumbers));
	MOCK_METHOD2(NumList_VerifyAll, bool (const std::string & strNumList, const std::string & strNumbers));
	MOCK_METHOD1(NumList_Count, int32_t (const std::string & strNumList));
	MOCK_METHOD2(Encode, std::string (const std::string & strPlaintext, const bool & bLineBreaks));
	MOCK_METHOD2(Decode, std::string (const std::string & strEncoded, const bool & bLineBreaks));
	MOCK_METHOD2(Encrypt, std::string (const std::string & RECIPIENT_NYM_ID, const std::string & strPlaintext));
	MOCK_METHOD2(Decrypt, std::string (const std::string & RECIPIENT_NYM_ID, const std::string & strCiphertext));
	MOCK_METHOD0(CreateSymmetricKey, std::string ());
	MOCK_METHOD2(SymmetricEncrypt, std::string (const std::string & SYMMETRIC_KEY, const std::string & PLAintEXT));
	MOCK_METHOD2(SymmetricDecrypt, std::string (const std::string & SYMMETRIC_KEY, const std::string & CIPHERTEXT_ENVELOPE));
	MOCK_METHOD2(SignContract, std::string (const std::string & SIGNER_NYM_ID, const std::string & THE_CONTRACT));
	MOCK_METHOD3(FlatSign, std::string (const std::string & SIGNER_NYM_ID, const std::string & THE_INPUT, const std::string & CONTRACT_TYPE));
	MOCK_METHOD2(AddSignature, std::string (const std::string & SIGNER_NYM_ID, const std::string & THE_CONTRACT));
	MOCK_METHOD2(VerifySignature, bool (const std::string & SIGNER_NYM_ID, const std::string & THE_CONTRACT));
	MOCK_METHOD2(VerifyAndRetrieveXMLContents, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_ID));
	MOCK_METHOD0(GetMemlogSize, int32_t ());
	MOCK_METHOD1(GetMemlogAtIndex, std::string (const int32_t & nIndex));
	MOCK_METHOD0(PeekMemlogFront, std::string ());
	MOCK_METHOD0(PeekMemlogBack, std::string ());
	MOCK_METHOD0(PopMemlogFront, bool ());
	MOCK_METHOD0(PopMemlogBack, bool ());
	MOCK_METHOD3(CreateNym, std::string (const int32_t & nKeySize, const std::string & NYM_ID_SOURCE, const std::string & ALT_LOCATION));
	MOCK_METHOD1(GetNym_SourceForID, std::string (const std::string & NYM_ID));
	MOCK_METHOD1(GetNym_AltSourceLocation, std::string (const std::string & NYM_ID));
	MOCK_METHOD1(GetNym_CredentialCount, int32_t (const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_CredentialID, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_CredentialContents, std::string (const std::string & NYM_ID, const std::string & CREDENTIAL_ID));
	MOCK_METHOD1(GetNym_RevokedCredCount, int32_t (const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_RevokedCredID, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_RevokedCredContents, std::string (const std::string & NYM_ID, const std::string & CREDENTIAL_ID));
	MOCK_METHOD2(GetNym_SubcredentialCount, int32_t (const std::string & NYM_ID, const std::string & MASTER_CRED_ID));
	MOCK_METHOD3(GetNym_SubCredentialID, std::string (const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const int32_t & nIndex));
	MOCK_METHOD3(GetNym_SubCredentialContents, std::string (const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const std::string & SUB_CRED_ID));
	MOCK_METHOD3(AddSubcredential, std::string (const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const int32_t & nKeySize));
	MOCK_METHOD3(RevokeSubcredential, bool (const std::string & NYM_ID, const std::string & MASTER_CRED_ID, const std::string & SUB_CRED_ID));
	MOCK_METHOD2(CreateServerContract, std::string (const std::string & NYM_ID, const std::string & strXMLcontents));
	MOCK_METHOD2(CreateAssetContract, std::string (const std::string & NYM_ID, const std::string & strXMLcontents));
	MOCK_METHOD1(CalculateAssetContractID, std::string (const std::string & str_Contract));
	MOCK_METHOD1(CalculateServerContractID, std::string (const std::string & str_Contract));
	MOCK_METHOD1(AddServerContract, int32_t (const std::string & strContract));
	MOCK_METHOD1(AddAssetContract, int32_t (const std::string & strContract));
	MOCK_METHOD0(GetServerCount, int32_t ());
	MOCK_METHOD0(GetAssetTypeCount, int32_t ());
	MOCK_METHOD0(GetAccountCount, int32_t ());
	MOCK_METHOD0(GetNymCount, int32_t ());
	MOCK_METHOD1(GetServer_ID, std::string (const int32_t & nIndex));
	MOCK_METHOD1(GetServer_Name, std::string (const std::string & SERVER_ID));
	MOCK_METHOD1(GetServer_Contract, std::string (const std::string & SERVER_ID));
	MOCK_METHOD2(FormatAmount, std::string (const std::string & ASSET_TYPE_ID, const int64_t & THE_AMOUNT));
	MOCK_METHOD2(StringToAmount, int64_t (const std::string & ASSET_TYPE_ID, const std::string & str_input));
	MOCK_METHOD1(GetAssetType_ID, std::string (const int32_t & nIndex));
	MOCK_METHOD1(GetAssetType_Name, std::string (const std::string & ASSET_TYPE_ID));
	MOCK_METHOD1(GetAssetType_Contract, std::string (const std::string & ASSET_TYPE_ID));
	MOCK_METHOD1(GetAccountWallet_ID, std::string (const int32_t & nIndex));
	MOCK_METHOD1(GetAccountWallet_Name, std::string (const std::string & ACCOUNT_ID));
	MOCK_METHOD1(GetAccountWallet_Balance, int64_t (const std::string & ACCOUNT_ID));
	MOCK_METHOD1(GetAccountWallet_Type, std::string (const std::string & ACCOUNT_ID));
	MOCK_METHOD1(GetAccountWallet_AssetTypeID, std::string (const std::string & ACCOUNT_ID));
	MOCK_METHOD1(GetAccountWallet_ServerID, std::string (const std::string & ACCOUNT_ID));
	MOCK_METHOD1(GetAccountWallet_NymID, std::string (const std::string & ACCOUNT_ID));
	MOCK_METHOD1(GetAccountWallet_InboxHash, std::string (const std::string & ACCOUNT_ID));
	MOCK_METHOD1(GetAccountWallet_OutboxHash, std::string (const std::string & ACCOUNT_ID));
	MOCK_METHOD3(VerifyAccountReceipt, bool (const std::string & SERVER_ID, const std::string & NYM_ID, const std::string & ACCT_ID));
	MOCK_METHOD2(GetNym_TransactionNumCount, int32_t (const std::string & SERVER_ID, const std::string & NYM_ID));
	MOCK_METHOD1(GetNym_ID, std::string (const int32_t & nIndex));
	MOCK_METHOD1(GetNym_Name, std::string (const std::string & NYM_ID));
	MOCK_METHOD1(GetNym_Stats, std::string (const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_NymboxHash, std::string (const std::string & SERVER_ID, const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_RecentHash, std::string (const std::string & SERVER_ID, const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_InboxHash, std::string (const std::string & ACCOUNT_ID, const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_OutboxHash, std::string (const std::string & ACCOUNT_ID, const std::string & NYM_ID));
	MOCK_METHOD2(IsNym_RegisteredAtServer, bool (const std::string & NYM_ID, const std::string & SERVER_ID));
	MOCK_METHOD1(GetNym_MailCount, int32_t (const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_MailContentsByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_MailSenderIDByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_MailServerIDByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(Nym_RemoveMailByIndex, bool (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(Nym_VerifyMailByIndex, bool (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD1(GetNym_OutmailCount, int32_t (const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_OutmailContentsByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_OutmailRecipientIDByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_OutmailServerIDByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(Nym_RemoveOutmailByIndex, bool (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(Nym_VerifyOutmailByIndex, bool (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD1(GetNym_OutpaymentsCount, int32_t (const std::string & NYM_ID));
	MOCK_METHOD2(GetNym_OutpaymentsContentsByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_OutpaymentsRecipientIDByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(GetNym_OutpaymentsServerIDByIndex, std::string (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(Nym_RemoveOutpaymentsByIndex, bool (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD2(Nym_VerifyOutpaymentsByIndex, bool (const std::string & NYM_ID, const int32_t & nIndex));
	MOCK_METHOD1(Wallet_CanRemoveServer, bool (const std::string & SERVER_ID));
	MOCK_METHOD1(Wallet_RemoveServer, bool (const std::string & SERVER_ID));
	MOCK_METHOD1(Wallet_CanRemoveAssetType, bool (const std::string & ASSET_ID));
	MOCK_METHOD1(Wallet_RemoveAssetType, bool (const std::string & ASSET_ID));
	MOCK_METHOD1(Wallet_CanRemoveNym, bool (const std::string & NYM_ID));
	MOCK_METHOD1(Wallet_RemoveNym, bool (const std::string & NYM_ID));
	MOCK_METHOD1(Wallet_CanRemoveAccount, bool (const std::string & ACCOUNT_ID));
	MOCK_METHOD0(Wallet_ChangePassphrase, bool ());
	MOCK_METHOD1(Wallet_ExportNym, std::string (const std::string & NYM_ID));
	MOCK_METHOD1(Wallet_ImportNym, std::string (const std::string & FILE_CONTENTS));
	MOCK_METHOD2(Wallet_ImportCert, std::string (const std::string & DISPLAY_NAME, const std::string & FILE_CONTENTS));
	MOCK_METHOD1(Wallet_ExportCert, std::string (const std::string & NYM_ID));
	MOCK_METHOD1(Wallet_GetNymIDFromPartial, std::string (const std::string & PARTIAL_ID));
	MOCK_METHOD1(Wallet_GetServerIDFromPartial, std::string (const std::string & PARTIAL_ID));
	MOCK_METHOD1(Wallet_GetAssetIDFromPartial, std::string (const std::string & PARTIAL_ID));
	MOCK_METHOD1(Wallet_GetAccountIDFromPartial, std::string (const std::string & PARTIAL_ID));
	MOCK_METHOD3(SetNym_Name, bool (const std::string & NYM_ID, const std::string & SIGNER_NYM_ID, const std::string & NYM_NEW_NAME));
	MOCK_METHOD3(SetAccountWallet_Name, bool (const std::string & ACCT_ID, const std::string & SIGNER_NYM_ID, const std::string & ACCT_NEW_NAME));
	MOCK_METHOD2(SetAssetType_Name, bool (const std::string & ASSET_ID, const std::string & STR_NEW_NAME));
	MOCK_METHOD2(SetServer_Name, bool (const std::string & SERVER_ID, const std::string & STR_NEW_NAME));
	MOCK_METHOD8(WriteCheque, std::string (const std::string & SERVER_ID, const int64_t & CHEQUE_AMOUNT, const time_t & VALID_FROM, const time_t & VALID_TO,
											const std::string & SENDER_ACCT_ID, const std::string & SENDER_USER_ID, const std::string & CHEQUE_MEMO, const std::string & RECIPIENT_USER_ID));
	MOCK_METHOD4(DiscardCheque, bool (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & THE_CHEQUE));

	// note: there is no MOCK_METHOD15, but ChaiScript cannot call this one anyway
	virtual std::string ProposePaymentPlan(const std::string & SERVER_ID,
											const time_t & VALID_FROM,	// Default (0 or NULL) == current time measured in seconds since Jan 1970.
											const time_t & VALID_TO,	// Default (0 or NULL) == no expiry / cancel anytime. Otherwise this is ADDED to VALID_FROM (it's a length.)
											const std::string & SENDER_ACCT_ID,	// Mandatory parameters.
											const std::string & SENDER_USER_ID,	// Both sender and recipient must sign before submitting.
											const std::string & PLAN_CONSIDERATION,	// Like a memo.
											const std::string & RECIPIENT_ACCT_ID,	// NOT optional.
											const std::string & RECIPIENT_USER_ID,	// Both sender and recipient must sign before submitting.
											const int64_t & INITIAL_PAYMENT_AMOUNT,	// zero or NULL == no initial payment.
											const time_t  & INITIAL_PAYMENT_DELAY,	// seconds from creation date. Default is zero or NULL.
											const int64_t & PAYMENT_PLAN_AMOUNT,	// Zero or NULL == no regular payments.
											const time_t  & PAYMENT_PLAN_DELAY,	    // No. of seconds from creation date. Default is zero or NULL. (Causing 30 days.)
											const time_t  & PAYMENT_PLAN_PERIOD,	// No. of seconds between payments. Default is zero or NULL. (Causing 30 days.)
											const time_t  & PAYMENT_PLAN_LENGTH,	// In seconds. Defaults to 0 or NULL (no maximum length.)
											const int32_t & PAYMENT_PLAN_MAX_PAYMENTS)	// integer. Defaults to 0 or NULL (no maximum payments.)
	{
		return "";
	}


	// note: there is no MOCK_METHOD10, so we only mock 9 of them. We're not interested in PLAN_CONSIDERATION at the moment
	virtual std::string EasyProposePlan(const std::string & SERVER_ID,
										const std::string & DATE_RANGE,         // "from,to"  Default 'from' (0 or "") == NOW, and default 'to' (0 or "") == no expiry / cancel anytime
										const std::string & SENDER_ACCT_ID,     // Mandatory parameters.
										const std::string & SENDER_USER_ID,     // Both sender and recipient must sign before submitting.
										const std::string & PLAN_CONSIDERATION,	// Like a memo.
										const std::string & RECIPIENT_ACCT_ID,	// NOT optional.
										const std::string & RECIPIENT_USER_ID,	// Both sender and recipient must sign before submitting.
										const std::string & INITIAL_PAYMENT,	// "amount,delay"  Default 'amount' (0 or "") == no initial payment. Default 'delay' (0 or NULL) is seconds from creation date.
										const std::string & PAYMENT_PLAN,       // "amount,delay,period" 'amount' is a recurring payment. 'delay' and 'period' cause 30 days if you pass 0 or "".
										const std::string & PLAN_EXPIRY)         // "length,number" 'length' is maximum lifetime in seconds. 'number' is maximum number of payments in seconds. 0 or "" is unlimited (for both.)
	{
		return EasyProposePlan(SERVER_ID, DATE_RANGE, SENDER_ACCT_ID, SENDER_USER_ID, RECIPIENT_ACCT_ID, RECIPIENT_USER_ID,	INITIAL_PAYMENT, PAYMENT_PLAN, PLAN_EXPIRY);
	}
	MOCK_METHOD9(EasyProposePlan, std::string (const std::string & SERVER_ID, const std::string & DATE_RANGE, const std::string & SENDER_ACCT_ID,
											   const std::string & SENDER_USER_ID, const std::string & RECIPIENT_ACCT_ID, const std::string & RECIPIENT_USER_ID,
											   const std::string & INITIAL_PAYMENT, const std::string & PAYMENT_PLAN, const std::string & PLAN_EXPIRY));

	MOCK_METHOD5(ConfirmPaymentPlan, std::string (const std::string & SERVER_ID, const std::string & SENDER_USER_ID, const std::string & SENDER_ACCT_ID, const std::string & RECIPIENT_USER_ID, const std::string & PAYMENT_PLAN));
	MOCK_METHOD3(Create_SmartContract, std::string (const std::string & SIGNER_NYM_ID, const time_t & VALID_FROM, const time_t & VALID_TO));
	MOCK_METHOD3(SmartContract_AddBylaw, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME));
	MOCK_METHOD5(SmartContract_AddClause, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & CLAUSE_NAME, const std::string & SOURCE_CODE));
	MOCK_METHOD7(SmartContract_AddVariable, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & VAR_NAME, const std::string & VAR_ACCESS, const std::string & VAR_TYPE, const std::string & VAR_VALUE));
	MOCK_METHOD5(SmartContract_AddCallback, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & CALLBACK_NAME, const std::string & CLAUSE_NAME));
	MOCK_METHOD5(SmartContract_AddHook, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & BYLAW_NAME, const std::string & HOOK_NAME, const std::string & CLAUSE_NAME));
	MOCK_METHOD4(SmartContract_AddParty, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & PARTY_NAME, const std::string & AGENT_NAME));
	MOCK_METHOD5(SmartContract_AddAccount, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & PARTY_NAME, const std::string & ACCT_NAME, const std::string & ASSET_TYPE_ID));
	MOCK_METHOD2(SmartContract_CountNumsNeeded, int32_t (const std::string & THE_CONTRACT, const std::string & AGENT_NAME));
	MOCK_METHOD6(SmartContract_ConfirmAccount, std::string (const std::string & THE_CONTRACT, const std::string & SIGNER_NYM_ID, const std::string & PARTY_NAME, const std::string & ACCT_NAME, const std::string & AGENT_NAME, const std::string & ACCT_ID));
	MOCK_METHOD3(SmartContract_ConfirmParty, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & NYM_ID));
	MOCK_METHOD1(Smart_AreAllPartiesConfirmed, bool (const std::string & THE_CONTRACT));
	MOCK_METHOD1(Smart_GetBylawCount, int32_t (const std::string & THE_CONTRACT));
	MOCK_METHOD2(Smart_GetBylawByIndex, std::string (const std::string & THE_CONTRACT, const int32_t & nIndex));
	MOCK_METHOD2(Bylaw_GetLanguage, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME));
	MOCK_METHOD2(Bylaw_GetClauseCount, int32_t (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME));
	MOCK_METHOD3(Clause_GetNameByIndex, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex));
	MOCK_METHOD3(Clause_GetContents, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & CLAUSE_NAME));
	MOCK_METHOD2(Bylaw_GetVariableCount, int32_t (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME));
	MOCK_METHOD3(Variable_GetNameByIndex, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex));
	MOCK_METHOD3(Variable_GetType, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME));
	MOCK_METHOD3(Variable_GetAccess, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME));
	MOCK_METHOD3(Variable_GetContents, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & VARIABLE_NAME));
	MOCK_METHOD2(Bylaw_GetHookCount, int32_t (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME));
	MOCK_METHOD3(Hook_GetNameByIndex, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex));
	MOCK_METHOD3(Hook_GetClauseCount, int32_t (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & HOOK_NAME));
	MOCK_METHOD4(Hook_GetClauseAtIndex, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & HOOK_NAME, const int32_t & nIndex));
	MOCK_METHOD2(Bylaw_GetCallbackCount, int32_t (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME));
	MOCK_METHOD3(Callback_GetNameByIndex, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const int32_t & nIndex));
	MOCK_METHOD3(Callback_GetClause, std::string (const std::string & THE_CONTRACT, const std::string & BYLAW_NAME, const std::string & CALLBACK_NAME));
	MOCK_METHOD1(Smart_GetPartyCount, int32_t (const std::string & THE_CONTRACT));
	MOCK_METHOD2(Smart_GetPartyByIndex, std::string (const std::string & THE_CONTRACT, const int32_t & nIndex));
	MOCK_METHOD2(Smart_IsPartyConfirmed, bool (const std::string & THE_CONTRACT, const std::string & PARTY_NAME));
	MOCK_METHOD2(Party_GetID, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME));
	MOCK_METHOD2(Party_GetAcctCount, int32_t (const std::string & THE_CONTRACT, const std::string & PARTY_NAME));
	MOCK_METHOD3(Party_GetAcctNameByIndex, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const int32_t & nIndex));
	MOCK_METHOD3(Party_GetAcctID, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME));
	MOCK_METHOD3(Party_GetAcctAssetID, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME));
	MOCK_METHOD3(Party_GetAcctAgentName, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & ACCT_NAME));
	MOCK_METHOD2(Party_GetAgentCount, int32_t (const std::string & THE_CONTRACT, const std::string & PARTY_NAME));
	MOCK_METHOD3(Party_GetAgentNameByIndex, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const int32_t & nIndex));
	MOCK_METHOD3(Party_GetAgentID, std::string (const std::string & THE_CONTRACT, const std::string & PARTY_NAME, const std::string & AGENT_NAME));
	MOCK_METHOD3(activateSmartContract, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_SMART_CONTRACT));
	MOCK_METHOD5(triggerClause, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const int64_t & TRANSACTION_NUMBER, const std::string & CLAUSE_NAME, const std::string & STR_PARAM));
	MOCK_METHOD7(Msg_HarvestTransactionNumbers, bool (const std::string & THE_MESSAGE, const std::string & USER_ID, const bool & bHarvestingForRetry, const bool & bReplyWasSuccess, const bool & bReplyWasFailure, const bool & bTransactionWasSuccess, const bool & bTransactionWasFailure));
	MOCK_METHOD1(LoadUserPubkey_Encryption, std::string (const std::string & USER_ID));
	MOCK_METHOD1(LoadUserPubkey_Signing, std::string (const std::string & USER_ID));
	MOCK_METHOD1(LoadPubkey_Encryption, std::string (const std::string & USER_ID));
	MOCK_METHOD1(LoadPubkey_Signing, std::string (const std::string & USER_ID));
	MOCK_METHOD1(VerifyUserPrivateKey, bool (const std::string & USER_ID));
	MOCK_METHOD3(LoadPurse, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID));
	MOCK_METHOD2(LoadMint, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID));
	MOCK_METHOD1(LoadAssetContract, std::string (const std::string & ASSET_TYPE_ID));
	MOCK_METHOD1(LoadServerContract, std::string (const std::string & SERVER_ID));
	MOCK_METHOD2(Mint_IsStillGood, bool (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID));
	MOCK_METHOD1(IsBasketCurrency, bool (const std::string & ASSET_TYPE_ID));
	MOCK_METHOD1(Basket_GetMemberCount, int32_t (const std::string & BASKET_ASSET_TYPE_ID));
	MOCK_METHOD2(Basket_GetMemberType, std::string (const std::string & BASKET_ASSET_TYPE_ID, const int32_t & nIndex));
	MOCK_METHOD1(Basket_GetMinimumTransferAmount, int64_t (const std::string & BASKET_ASSET_TYPE_ID));
	MOCK_METHOD2(Basket_GetMemberMinimumTransferAmount, int64_t (const std::string & BASKET_ASSET_TYPE_ID, const int32_t & nIndex));
	MOCK_METHOD3(LoadAssetAccount, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD3(LoadInbox, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD3(LoadOutbox, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD3(LoadInboxNoVerify, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD3(LoadOutboxNoVerify, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD2(LoadPaymentInbox, std::string (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD2(LoadPaymentInboxNoVerify, std::string (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD3(LoadRecordBox, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD3(LoadRecordBoxNoVerify, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD5(ClearRecord, bool (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const int32_t & nIndex, const bool & bClearAll));
	MOCK_METHOD2(LoadExpiredBox, std::string (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD2(LoadExpiredBoxNoVerify, std::string (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD4(ClearExpired, bool (const std::string & SERVER_ID, const std::string & USER_ID, const int32_t & nIndex, const bool & bClearAll));
	MOCK_METHOD4(Ledger_GetCount, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER));
	MOCK_METHOD4(Ledger_CreateResponse, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & ORIGINAL_LEDGER));
	MOCK_METHOD5(Ledger_GetTransactionByIndex, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int32_t & nIndex));
	MOCK_METHOD5(Ledger_GetTransactionByID, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int64_t & TRANSACTION_NUMBER));
	MOCK_METHOD5(Ledger_GetTransactionIDByIndex, int64_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int32_t & nIndex));
	MOCK_METHOD5(Ledger_AddTransaction, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const std::string & THE_TRANSACTION));
	MOCK_METHOD6(Transaction_CreateResponse, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & RESPONSE_LEDGER, const std::string & ORIGINAL_TRANSACTION, const bool & BOOL_DO_I_ACCEPT));
	MOCK_METHOD4(Ledger_FinalizeResponse, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER));
	MOCK_METHOD5(Ledger_GetInstrument, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_LEDGER, const int32_t & nIndex));
	MOCK_METHOD5(RecordPayment, bool (const std::string & SERVER_ID, const std::string & USER_ID, const bool & bIsInbox, const int32_t & nIndex, const bool & bSaveCopy));
	MOCK_METHOD4(Transaction_GetType, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD3(ReplyNotice_GetRequestNum, int64_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetVoucher, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetSuccess, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_IsCanceled, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetBalanceAgreementSuccess, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetDateSigned, time_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetAmount, int64_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Pending_GetNote, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetSenderUserID, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetSenderAcctID, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetRecipientUserID, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetRecipientAcctID, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(Transaction_GetDisplayReferenceToNum, int64_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_TRANSACTION));
	MOCK_METHOD4(SavePurse, bool (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID, const std::string & THE_PURSE));
	MOCK_METHOD4(CreatePurse, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & OWNER_ID, const std::string & SIGNER_ID));
	MOCK_METHOD3(CreatePurse_Passphrase, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & SIGNER_ID));
	MOCK_METHOD3(Purse_GetTotalValue, int64_t (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_PURSE));
	MOCK_METHOD3(Purse_Count, int32_t (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_PURSE));
	MOCK_METHOD2(Purse_HasPassword, bool (const std::string & SERVER_ID, const std::string & THE_PURSE));
	MOCK_METHOD4(Purse_Peek, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & OWNER_ID, const std::string & THE_PURSE));
	MOCK_METHOD4(Purse_Pop, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & OWNER_OR_SIGNER_ID, const std::string & THE_PURSE));
	MOCK_METHOD6(Purse_Push, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & SIGNER_ID, const std::string & OWNER_ID, const std::string & THE_PURSE, const std::string & THE_TOKEN));
	MOCK_METHOD4(Purse_Empty, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & SIGNER_ID, const std::string & THE_PURSE));
	MOCK_METHOD4(Wallet_ImportPurse, bool (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID, const std::string & THE_PURSE));
	MOCK_METHOD4(exchangePurse, int32_t (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & USER_ID, const std::string & THE_PURSE));
	MOCK_METHOD6(Token_ChangeOwner, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN, const std::string & SIGNER_NYM_ID, const std::string & OLD_OWNER, const std::string & NEW_OWNER));
	MOCK_METHOD3(Token_GetID, std::string (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN));
	MOCK_METHOD3(Token_GetDenomination, int64_t (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN));
	MOCK_METHOD3(Token_GetSeries, int32_t (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN));
	MOCK_METHOD3(Token_GetValidFrom, time_t (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN));
	MOCK_METHOD3(Token_GetValidTo, time_t (const std::string & SERVER_ID, const std::string & ASSET_TYPE_ID, const std::string & THE_TOKEN));
	MOCK_METHOD1(Token_GetAssetID, std::string (const std::string & THE_TOKEN));
	MOCK_METHOD1(Token_GetServerID, std::string (const std::string & THE_TOKEN));
	MOCK_METHOD1(Instrmnt_GetAmount, int64_t (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetTransNum, int64_t (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetValidFrom, time_t (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetValidTo, time_t (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetMemo, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetType, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetServerID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetAssetID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetSenderUserID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetSenderAcctID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetRemitterUserID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetRemitterAcctID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetRecipientUserID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD1(Instrmnt_GetRecipientAcctID, std::string (const std::string & THE_INSTRUMENT));
	MOCK_METHOD2(checkServerID, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD2(createUserAccount, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD2(deleteUserAccount, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD3(deleteAssetAccount, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID));
	MOCK_METHOD4(usageCredits, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_CHECK, const int64_t & ADJUSTMENT));
	MOCK_METHOD1(Message_GetUsageCredits, int64_t (const std::string & THE_MESSAGE));
	MOCK_METHOD3(checkUser, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_CHECK));
	MOCK_METHOD5(sendUserMessage, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_RECIPIENT, const std::string & RECIPIENT_PUBKEY, const std::string & THE_MESSAGE));
	MOCK_METHOD6(sendUserInstrument, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & USER_ID_RECIPIENT, const std::string & RECIPIENT_PUBKEY, const std::string & THE_INSTRUMENT, const std::string & INSTRUMENT_FOR_SENDER));
	MOCK_METHOD2(getRequest, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD2(getTransactionNumber, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD3(issueAssetType, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_CONTRACT));
	MOCK_METHOD3(getContract, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ID));
	MOCK_METHOD3(getMint, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ID));
	MOCK_METHOD3(createAssetAccount, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ID));
	MOCK_METHOD3(getAccount, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID));
	MOCK_METHOD3(getAccountFiles, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID));
	MOCK_METHOD2(GenerateBasketCreation, std::string (const std::string & USER_ID, const int64_t & MINIMUM_TRANSFER));
	MOCK_METHOD4(AddBasketCreationItem, std::string (const std::string & USER_ID, const std::string & THE_BASKET, const std::string & ASSET_TYPE_ID, const int64_t & MINIMUM_TRANSFER));
	MOCK_METHOD3(issueBasket, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_BASKET));
	MOCK_METHOD5(GenerateBasketExchange, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & BASKET_ASSET_TYPE_ID, const std::string & BASKET_ASSET_ACCT_ID, const int32_t & TRANSFER_MULTIPLE));
	MOCK_METHOD5(AddBasketExchangeItem, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_BASKET, const std::string & ASSET_TYPE_ID, const std::string & ASSET_ACCT_ID));
	MOCK_METHOD5(exchangeBasket, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & BASKET_ASSET_ID, const std::string & THE_BASKET, const bool & BOOL_EXCHANGE_IN_OR_OUT));
	MOCK_METHOD4(notarizeWithdrawal, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const int64_t & AMOUNT));
	MOCK_METHOD4(notarizeDeposit, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & THE_PURSE));
	MOCK_METHOD6(notarizeTransfer, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_FROM, const std::string & ACCT_TO, const int64_t & AMOUNT, const std::string & NOTE));
	MOCK_METHOD3(getInbox, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID));
	MOCK_METHOD3(getOutbox, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID));
	MOCK_METHOD2(getNymbox, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD2(LoadNymbox, std::string (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD2(LoadNymboxNoVerify, std::string (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD3(Nymbox_GetReplyNotice, std::string (const std::string & SERVER_ID, const std::string & USER_ID, const int64_t & REQUEST_NUMBER));
	MOCK_METHOD3(HaveAlreadySeenReply, bool (const std::string & SERVER_ID, const std::string & USER_ID, const int64_t & REQUEST_NUMBER));
	MOCK_METHOD5(getBoxReceipt, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const int32_t & nBoxType, const int64_t & TRANSACTION_NUMBER));
	MOCK_METHOD5(DoesBoxReceiptExist, bool (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const int32_t & nBoxType, const int64_t & TRANSACTION_NUMBER));
	MOCK_METHOD4(processInbox, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & ACCT_LEDGER));
	MOCK_METHOD2(processNymbox, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD6(withdrawVoucher, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & RECIPIENT_USER_ID, const std::string & CHEQUE_MEMO, const int64_t & AMOUNT));
	MOCK_METHOD6(payDividend, int32_t (const std::string & SERVER_ID, const std::string & ISSUER_USER_ID, const std::string & DIVIDEND_FROM_ACCT_ID, const std::string & SHARES_ASSET_TYPE_ID, const std::string & DIVIDEND_MEMO, const int64_t & AMOUNT_PER_SHARE));
	MOCK_METHOD4(depositCheque, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCT_ID, const std::string & THE_CHEQUE));
	MOCK_METHOD3(depositPaymentPlan, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_PAYMENT_PLAN));

	// note: there is no MOCK_METHOD10, so we only mock 9 of them. We're not interested in LIFESPAN_IN_SECONDS at the moment
	virtual int32_t issueMarketOffer(const std::string & ASSET_ACCT_ID,     // Perhaps this is the wheat market.
									const std::string & CURRENCY_ACCT_ID,  // Perhaps I'm buying the wheat with rubles.
									const int64_t     & MARKET_SCALE,        // Defaults to minimum of 1. Market granularity.
									const int64_t     & MINIMUM_INCREMENT,   // This will be multiplied by the Scale. Min 1.
									const int64_t     & TOTAL_ASSETS_ON_OFFER,   // Total assets available for sale or purchase. Will be multiplied by minimum increment.
									const int64_t     & PRICE_LIMIT,			// Per Minimum Increment...
									const bool        & bBuyingOrSelling,    // SELLING == true, BUYING == false.
									const time_t      & LIFESPAN_IN_SECONDS, // Pass 0 for the default behavior: 86400 seconds aka 1 day.
									const std::string & STOP_SIGN,         // Must be "" (for market/limit orders) or "<" or ">"  (for stop orders.)
									const int64_t     & ACTIVATION_PRICE) // Must be provided if STOP_SIGN is also set. Determines the price threshold for stop orders.
	{
		// pass the remaining arguments to the mock function
		return issueMarketOffer(ASSET_ACCT_ID, CURRENCY_ACCT_ID, MARKET_SCALE, MINIMUM_INCREMENT, TOTAL_ASSETS_ON_OFFER, PRICE_LIMIT, bBuyingOrSelling, STOP_SIGN, ACTIVATION_PRICE);
	}
	MOCK_METHOD9(issueMarketOffer, int32_t (const std::string & ASSET_ACCT_ID, const std::string & CURRENCY_ACCT_ID, const int64_t & MARKET_SCALE,
											const int64_t & MINIMUM_INCREMENT, const int64_t & TOTAL_ASSETS_ON_OFFER, const int64_t & PRICE_LIMIT,
											const bool & bBuyingOrSelling, const std::string & STOP_SIGN, const int64_t & ACTIVATION_PRICE));

	MOCK_METHOD2(getMarketList, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD4(getMarketOffers, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & MARKET_ID, const int64_t & MAX_DEPTH));
	MOCK_METHOD3(getMarketRecentTrades, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & MARKET_ID));
	MOCK_METHOD2(getNym_MarketOffers, int32_t (const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD4(killMarketOffer, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ASSET_ACCT_ID, const int64_t & TRANSACTION_NUMBER));
	MOCK_METHOD4(killPaymentPlan, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & FROM_ACCT_ID, const int64_t & TRANSACTION_NUMBER));
	MOCK_METHOD3(PopMessageBuffer, std::string (const int64_t & REQUEST_NUMBER, const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD0(FlushMessageBuffer, void ());
	MOCK_METHOD3(GetSentMessage, std::string (const int64_t & REQUEST_NUMBER, const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD3(RemoveSentMessage, bool (const int64_t & REQUEST_NUMBER, const std::string & SERVER_ID, const std::string & USER_ID));
	MOCK_METHOD4(FlushSentMessages, void (const bool & bHarvestingForRetry, const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_NYMBOX));
	MOCK_METHOD3(ResyncNymWithServer, bool (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetCommand, std::string (const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetSuccess, int32_t (const std::string & THE_MESSAGE));
	MOCK_METHOD3(queryAssetTypes, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ENCODED_MAP));
	MOCK_METHOD1(Message_GetPayload, std::string (const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetDepth, int32_t (const std::string & THE_MESSAGE));
	MOCK_METHOD4(Message_GetTransactionSuccess, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_MESSAGE));
	MOCK_METHOD4(Message_IsTransactionCanceled, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_MESSAGE));
	MOCK_METHOD4(Message_GetBalanceAgreementSuccess, int32_t (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & ACCOUNT_ID, const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetLedger, std::string (const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetNewAssetTypeID, std::string (const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetNewIssuerAcctID, std::string (const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetNewAcctID, std::string (const std::string & THE_MESSAGE));
	MOCK_METHOD1(Message_GetNymboxHash, std::string (const std::string & THE_MESSAGE));
	MOCK_METHOD5(ConnectServer, bool (const std::string & SERVER_ID, const std::string & USER_ID, const std::string & strCA_FILE, const std::string & strKEY_FILE, const std::string & strKEY_PASSWORD));
	MOCK_METHOD0(ProcessSockets, bool ());
};

#endif
