/************************************************************
 *
 *  OTAccount.cpp
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

#include "OTAccount.hpp"

#include "OTDataFolder.hpp"
#include "OTFolders.hpp"
#include "OTLedger.hpp"
#include "OTLog.hpp"
#include "OTMessage.hpp"
#include "OTPaths.hpp"
#include "OTPayload.hpp"
#include "OTPseudonym.hpp"

#include "irrxml/irrXML.hpp"

#include <fstream>

#ifndef _WIN32
#include <unistd.h>
#include <sys/time.h>
#endif

using namespace irr;
using namespace io;


char const * const __TypeStrings[] =
{
	"simple",	// used by users
	"issuer",	// used by issuers	(these can only go negative.)
	"basket",	// issuer acct used by basket currencies (these can only go negative)
	"basketsub",// used by the server (to store backing reserves for basket sub-accounts)
	"mint",		// used by mints (to store backing reserves for cash)
	"voucher",	// used by the server (to store backing reserves for vouchers)
	"stash",	// used by the server (to store backing reserves for stashes, for smart contracts.)
	"err_acct"
};


char const * OTAccount::_GetTypeString(AccountType theType) {
	int32_t nType = static_cast<int32_t> (theType);
	return __TypeStrings[nType];
}


// Caller responsible to delete.
OTLedger * OTAccount::LoadInbox(OTPseudonym & theNym)
{
	OTLedger * pBox = new OTLedger(GetUserID(), GetRealAccountID(), GetRealServerID());
	OT_ASSERT(NULL != pBox);

	if (pBox->LoadInbox() && pBox->VerifyAccount(theNym))
	{
		return pBox;
	}
	else
	{
		OTString strUserID(GetUserID()), strAcctID(GetRealAccountID());

		OTLog::vOutput(2, "Unable to load or verify inbox:\n%s\n For user:\n%s\n",
					   strAcctID.Get(), strUserID.Get());
	}

	return NULL;
}


// Caller responsible to delete.
OTLedger * OTAccount::LoadOutbox(OTPseudonym & theNym)
{
	OTLedger * pBox = new OTLedger(GetUserID(), GetRealAccountID(), GetRealServerID());
	OT_ASSERT(NULL != pBox);

	if (pBox->LoadOutbox() && pBox->VerifyAccount(theNym))
	{
		return pBox;
	}
	else
	{
		OTString strUserID(GetUserID()), strAcctID(GetRealAccountID());

		OTLog::vOutput(2, "Unable to load or verify outbox:\n%s\n For user:\n%s\n",
					   strAcctID.Get(), strUserID.Get());
	}

	return NULL;
}


// pHash is optional, the account will update its internal copy of the hash anyway.
//
bool OTAccount::SaveInbox (OTLedger &theBox, OTIdentifier * pHash/*=NULL*/)
{
    if (!IsSameAccount(theBox))
    {
        const OTString  strAcctID(GetRealAccountID()),              strServerID(GetRealServerID()),
                        strBoxAcctID(theBox.GetRealAccountID()),    strBoxSvrID(theBox.GetRealServerID());
        OTLog::vError("OTAccount::SaveInbox: ERROR: The ledger passed in, isn't even for this account!\n"
                      "   Acct ID: %s\n  Other ID: %s\n Server ID: %s\n Other ID: %s\n",
                      strAcctID.Get(), strBoxAcctID.Get(), strServerID.Get(), strBoxSvrID.Get());
        return false;
    }

    OTIdentifier theHash; // Use pHash.
    if (NULL == pHash)
        pHash = &theHash;
    // ------------------------------------------
    bool bSuccess = theBox.SaveInbox(pHash);

    if (bSuccess)
        this->SetInboxHash(*pHash);

    return bSuccess;
}


// pHash is optional, the account will update its internal copy of the hash anyway.
//
bool OTAccount::SaveOutbox(OTLedger &theBox, OTIdentifier * pHash/*=NULL*/)  // If you pass the identifier in, the hash is recorded there
{
    if (!IsSameAccount(theBox))
    {
        const OTString  strAcctID(GetRealAccountID()),              strServerID(GetRealServerID()),
                        strBoxAcctID(theBox.GetRealAccountID()),    strBoxSvrID(theBox.GetRealServerID());
        OTLog::vError("OTAccount::SaveOutbox: ERROR: The ledger passed in, isn't even for this account!\n"
                      "   Acct ID: %s\n  Other ID: %s\n Server ID: %s\n Other ID: %s\n",
                      strAcctID.Get(), strBoxAcctID.Get(), strServerID.Get(), strBoxSvrID.Get());
        return false;
    }

    OTIdentifier theHash; // Use pHash.
    if (NULL == pHash)
        pHash = &theHash;
    // ------------------------------------------
    bool bSuccess = theBox.SaveOutbox(pHash);

    if (bSuccess)
        this->SetOutboxHash(*pHash);

    return bSuccess;
}


void  OTAccount::SetInboxHash(const OTIdentifier & theInput)
{
    m_InboxHash = theInput;
}


bool  OTAccount::GetInboxHash(OTIdentifier & theOutput)
{
    theOutput.Release();

    if (!m_InboxHash.IsEmpty())
    {
        theOutput = m_InboxHash;
        return true;
    }

    else if(!GetUserID().IsEmpty() &&
            !GetRealAccountID().IsEmpty() &&
            !GetRealServerID().IsEmpty()
            )
    {
        OTLedger theInbox(GetUserID(), GetRealAccountID(), GetRealServerID());

        if (theInbox.LoadInbox() && theInbox.CalculateInboxHash(theOutput))
        {
            SetInboxHash(theOutput);
            return true;
        }
    }

    return false;
}


void  OTAccount::SetOutboxHash(const OTIdentifier & theInput)
{
    m_OutboxHash = theInput;
}


bool  OTAccount::GetOutboxHash(OTIdentifier & theOutput)
{
    theOutput.Release();

    if (!m_OutboxHash.IsEmpty())
    {
        theOutput = m_OutboxHash;
        return true;
    }
    else if (!GetUserID().IsEmpty() &&
             !GetRealAccountID().IsEmpty() &&
             !GetRealServerID().IsEmpty()
             )
    {
        OTLedger theOutbox(GetUserID(), GetRealAccountID(), GetRealServerID());

        if (theOutbox.LoadOutbox() && theOutbox.CalculateOutboxHash(theOutput))
        {
            SetOutboxHash(theOutput);
            return true;
        }
    }

    return false;
}


// TODO:  add an override so that OTAccount, when it loads up, it performs the check to
// see the ServerID, look at the Server Contract and make sure the server hashes match.
//

// Todo override "Verify".  Have some way to verify a specific Nym to a specific account.

 // overriding this so I can set the filename automatically inside based on ID.
bool OTAccount::LoadContract()
{
	OTString strID;
	GetIdentifier(strID);

	return OTContract::LoadContract(OTFolders::Account().Get(), strID.Get());
}


bool OTAccount::SaveAccount()
{
	OTString strID;
	GetIdentifier(strID);

	return SaveContract(OTFolders::Account().Get(), strID.Get());
}


// Debit a certain amount from the account (presumably the same amount is being credited somewhere else)
bool OTAccount::Debit(const int64_t & lAmount)
{
	/* // TODO: Decide whether or not to allow negative Debits and negative Credits.
	  // (Currrently allowed -- a negative cheque is the same thing as an invoice.)
	if (lAmount < 0)
		return false;
	 */

	int64_t lOldBalance = atol(m_BalanceAmount.Get());

	int64_t lNewBalance = lOldBalance - lAmount;	// The MINUS here is the big difference between Debit and Credit

	// This is where issuer accounts get a pass. They just go negative.
	if ((lNewBalance < 0)				&&	// IF the new balance is less than zero...
		! IsAllowedToGoNegative()		&&	// AND it's a normal account... (not an issuer)
		(lNewBalance < lOldBalance))		// AND the new balance is even less than the old balance...
		return false;						// THEN FAIL. The "new less than old" requirement is recent,
	else									// and it means that we now allow <0 debits on normal accounts,
	{										// AS LONG AS the result is a HIGHER BALANCE  :-)
		m_BalanceAmount.Format("%lld", lNewBalance);

		const time64_t tDate = OTTimeGetCurrentTime(); // Today, now.
		m_BalanceDate.Format("%d", tDate);

		return true;
	}
}


// Credit a certain amount to the account (presumably the same amount is being debited somewhere else)
bool OTAccount::Credit(const int64_t & lAmount)
{
	/* // TODO: Decide whether or not to allow negative Debits and negative Credits. (Currrently allowed.)
	 if (lAmount < 0)
	 return false;
	 */

	int64_t lOldBalance = atol(m_BalanceAmount.Get());

	int64_t lNewBalance = lOldBalance + lAmount;  // The PLUS here is the big difference between Debit and Credit.

	// If the balance gets too big, it may flip to negative due to us using int64_t int32_t.
	// We'll maybe explicitly check that it's not negative in order to prevent that. TODO.
//	if (lNewBalance > 0 || (OTAccount::simple != m_AcctType))
//	{
//		m_BalanceAmount.Format("%lld", lNewBalance);
//		return true;
//	}

	// This is where issuer accounts get a pass. They just go negative.
	if ((lNewBalance < 0)				&&	// IF the new balance is less than zero...
		! IsAllowedToGoNegative()		&&	// AND it's a normal account... (not an issuer)
		(lNewBalance < lOldBalance))		// AND the new balance is even less than the old balance...
		return false;						// THEN FAIL. The "new less than old" requirement is recent,
	else									// and it means that we now allow <0 credits on normal accounts,
	{										// AS LONG AS the result is a HIGHER BALANCE  :-)
		m_BalanceAmount.Format("%lld", lNewBalance);

		const time64_t tDate = OTTimeGetCurrentTime(); // Today, now.
		m_BalanceDate.Format("%d", tDate);

		return true;
	}
}


const OTIdentifier & OTAccount::GetAssetTypeID() const
{
	return m_AcctAssetTypeID;
}


// Used for generating accounts, thus no accountID needed.
OTAccount::OTAccount(const OTIdentifier & theUserID, const OTIdentifier & theServerID)
: ot_super(), m_lStashTransNum(0), m_bMarkForDeletion(false)
{
	InitAccount();

	SetUserID(theUserID);
	SetRealServerID(theServerID);
	SetPurportedServerID(theServerID);
}


void OTAccount::InitAccount()
{
	m_strContractType	= "ACCOUNT";

	m_AcctType			= OTAccount::simple;
}


// this is private for now. hopefully keep that way.
OTAccount::OTAccount() : ot_super(), m_lStashTransNum(0), m_bMarkForDeletion(false)
{
	InitAccount();
}


OTAccount::OTAccount(const OTIdentifier & theUserID, const OTIdentifier & theAccountID,
                     const OTIdentifier & theServerID, const OTString & name)
: ot_super (theUserID, theAccountID, theServerID), m_lStashTransNum(0), m_bMarkForDeletion(false)
{
	InitAccount();

	m_strName = name;
}

OTAccount::OTAccount(const OTIdentifier & theUserID, const OTIdentifier & theAccountID, const OTIdentifier & theServerID)
: ot_super (theUserID, theAccountID, theServerID), m_lStashTransNum(0), m_bMarkForDeletion(false)
{
	InitAccount();
}


// Verify Contract ID first, THEN Verify Owner.
// Because we use the ID in this function, so make sure that it is verified before calling this.
//
bool OTAccount::VerifyOwner(const OTPseudonym & theCandidate) const
{
	OTIdentifier ID_CANDIDATE;
	theCandidate.GetIdentifier(ID_CANDIDATE); // ID_CANDIDATE now contains the ID of the Nym we're testing.

	if (m_AcctUserID == ID_CANDIDATE)
	{
		return true;
	}
	return false;
}


// Todo: when entities and roles are added, probably more will go here.
//
bool OTAccount::VerifyOwnerByID(const OTIdentifier & theNymID) const
{
	return (theNymID == m_AcctUserID);
}


// Let's say you don't have or know the UserID, and you just want to load the damn thing up.
// Then call this function. It will set userID and server ID for you.

OTAccount * OTAccount::LoadExistingAccount(const OTIdentifier & theAccountID, const OTIdentifier & theServerID)
{
	bool bFolderAlreadyExist=false, bFolderIsNew=false;

	OTString strDataFolder = "", strAccountPath = "";
	if (!OTDataFolder::Get(strDataFolder)) { OT_FAIL; };
	if (!OTPaths::AppendFolder(strAccountPath,strDataFolder,OTFolders::Account())) { OT_FAIL; };

	if (!OTPaths::ConfirmCreateFolder(strAccountPath,bFolderAlreadyExist,bFolderIsNew))
	{
		OTLog::vError("Unable to find or create accounts folder: %s\n", OTFolders::Account().Get());
		return NULL;
	}

	OTAccount * pAccount = new OTAccount();

	OT_ASSERT(NULL != pAccount);

	pAccount->SetRealAccountID(theAccountID);
	pAccount->SetRealServerID(theServerID);

	OTString strAcctID(theAccountID);

	pAccount->m_strFoldername	= OTFolders::Account().Get();
	pAccount->m_strFilename		= strAcctID.Get();

	// --------------------------------------------------------------------

	if (false == OTDB::Exists(pAccount->m_strFoldername.Get(), pAccount->m_strFilename.Get()))
	{
		OTLog::vOutput(2, "OTAccount::LoadExistingAccount: File does not exist: %s%s%s\n",
					   pAccount->m_strFoldername.Get(), OTLog::PathSeparator(), pAccount->m_strFilename.Get());
		return NULL;
	}

	// --------------------------------------------------------------------

	if (pAccount->LoadContract() && pAccount->VerifyContractID())
		return pAccount;
	else
	{
		delete pAccount;
		pAccount = NULL;
	}

	return NULL;
}


// static method (call it without an instance, using notation: OTAccount::GenerateNewAccount)
OTAccount * OTAccount::GenerateNewAccount(const OTIdentifier & theUserID,	const OTIdentifier & theServerID,
										  const OTPseudonym & theServerNym,	const OTMessage & theMessage,
										  const OTAccount::AccountType eAcctType/*=OTAccount::simple*/,
										  int64_t lStashTransNum/*=0*/)
{
	OTAccount * pAccount = new OTAccount(theUserID, theServerID);

	if (pAccount)
	{
		if (pAccount->GenerateNewAccount(theServerNym, theMessage, eAcctType,
										 lStashTransNum)) // This is only for stash accounts.
			return pAccount;
		else
		{
			delete pAccount;
			pAccount = NULL;
		}
	}

	return NULL;
}


/*

 Just make sure theMessage has these members populated:
theMessage.m_strNymID;
theMessage.m_strAssetID;
theMessage.m_strServerID;
 */
// The above method uses this one internally...
bool OTAccount::GenerateNewAccount(const OTPseudonym & theServer, const OTMessage & theMessage,
								   const OTAccount::AccountType eAcctType/*=OTAccount::simple*/,
								   int64_t lStashTransNum/*=0*/)
{
    const char *szFunc = "OTAccount::GenerateNewAccount";
    // -----------------------------------------------
	// First we generate a secure random number into a binary object...
    //
    OTPayload thePayload;

    if (false == thePayload.Randomize(100)) // todo hardcoding. Plus: is 100 bytes of random a little much here?
    {
		OTLog::vError("%s: Failed trying to acquire random numbers.\n", szFunc);
		return false;
    }
	// --------------------------------------------------
    //
	// Next we calculate that binary object into a message digest (an OTIdentifier).
    //
	OTIdentifier newID;
	if (!newID.CalculateDigest(thePayload))
	{
		OTLog::vError("%s: Error generating new account ID.\n", szFunc);
		return false;
	}
    // --------------------------------------------------
    //
	// Next we get that digest (which is a binary hash number)
	// and extract a human-readable standard string format of that hash,
	// into an OTString.
    //
	OTString strID(newID);

	SetRealAccountID(newID);		// Set the account number based on what we just generated.
	SetPurportedAccountID(newID);	// Might as well set them both. (Safe here to do so, for once.)

	m_strName.Set(strID); // So it's not blank. The user can always change it.

	// Next we create the full path filename for the account using the ID.
    //
	m_strFoldername = OTFolders::Account().Get();
	m_strFilename = strID.Get();

	// Then we try to load it, in order to make sure that it doesn't already exist.
	// --------------------------------------------------------------------

	if (OTDB::Exists(m_strFoldername.Get(), m_strFilename.Get()))
	{
		OTLog::vError("%s: Account already exists: %s\n", szFunc,
					  m_strFilename.Get());
		return false;
	}

	// --------------------------------------------------------------------

	// Set up the various important starting values of the account.
	m_AcctType = eAcctType; // account type defaults to OTAccount::simple. But there are also issuer accts...

	// --------------------------------------------------------------------

	if (IsInternalServerAcct())  // basket, basketsub, mint, voucher, and stash accounts are all "owned" by the server.
	{
		theServer.GetIdentifier(m_AcctUserID);
	}
	else
	{
		m_AcctUserID.SetString(theMessage.m_strNymID);
	}

	// --------------------------------------------------------------------
	m_AcctAssetTypeID.SetString(theMessage.m_strAssetID);

	OTLog::vOutput(3, "%s: Creating new account, type:\n%s\n", szFunc,
				   theMessage.m_strAssetID.Get());

	OTIdentifier SERVER_ID(theMessage.m_strServerID);
	SetRealServerID(SERVER_ID);			// todo this assumes the serverID on the message is correct. It's vetted, but still...
	SetPurportedServerID(SERVER_ID);

	const time64_t tDate = OTTimeGetCurrentTime(); // Today, now.
	m_BalanceDate.Format("%d", tDate);

	m_BalanceAmount.Set("0");

	// --------------------------------------------------------------------

	if (IsStashAcct())
	{
		OT_ASSERT_MSG(lStashTransNum > 0,
					  "You created a stash account, but with a zero-or-negative transaction number for its cron item.");
		m_lStashTransNum	= lStashTransNum;
	}

	// --------------------------------------------------------------------

	// Sign the Account (so we know that we did)... Otherwise someone could put a fake
	// account file on the server if the code wasn't designed to verify the signature on the
	// account.
	SignContract(theServer);
	SaveContract();

	// Save the Account to storage (based on its ID.)
	SaveAccount();

	// Don't know why I had this here. Putting SaveAccount() instead.
//	OTString strFilename(m_strFilename);
//	SaveContract(strFilename.Get()); // Saves the account to a specific filename

	// No need to create the inbox and outbox ledgers...they will be created automatically
	// if they do not exist when they are needed.

	return true;
}


int64_t OTAccount::GetBalance() const
{
	if (m_BalanceAmount.Exists())
		return atol(m_BalanceAmount.Get());

	return 0;
}


OTAccount::AccountType TranslateAccountTypeStringToEnum(const OTString & strAcctType)
{
	OTAccount::AccountType theReturnVal = OTAccount::err_acct;

	if (strAcctType.Compare("simple"))
		theReturnVal = OTAccount::simple;
	else if (strAcctType.Compare("issuer"))
		theReturnVal = OTAccount::issuer;
	else if (strAcctType.Compare("basket"))
		theReturnVal = OTAccount::basket;
	else if (strAcctType.Compare("basketsub"))
		theReturnVal = OTAccount::basketsub;
	else if (strAcctType.Compare("mint"))
		theReturnVal = OTAccount::mint;
	else if (strAcctType.Compare("voucher"))
		theReturnVal = OTAccount::voucher;
	else if (strAcctType.Compare("stash"))
		theReturnVal = OTAccount::stash;
	else
		OTLog::vError("Error: Unknown account type: %s \n", strAcctType.Get());

	return theReturnVal;
}


void TranslateAccountTypeToString(OTAccount::AccountType theType, OTString & strAcctType)
{
	switch (theType)
	{
		case OTAccount::simple:
			strAcctType.Set("simple");
			break;
		case OTAccount::issuer:
			strAcctType.Set("issuer");
			break;
		case OTAccount::basket:
			strAcctType.Set("basket");
			break;
		case OTAccount::basketsub:
			strAcctType.Set("basketsub");
			break;
		case OTAccount::mint:
			strAcctType.Set("mint");
			break;
		case OTAccount::voucher:
			strAcctType.Set("voucher");
			break;
		case OTAccount::stash:
			strAcctType.Set("stash");
			break;
		default:
			strAcctType.Set("err_acct");
			break;
	}
}


bool OTAccount::DisplayStatistics(OTString & strContents) const
{
	const OTString	strAccountID(GetPurportedAccountID()), strServerID(GetPurportedServerID()),
					strUserID(GetUserID()), strAssetTypeID(m_AcctAssetTypeID);

	OTString strAcctType;
	TranslateAccountTypeToString(m_AcctType, strAcctType);

	strContents.Concatenate(
							" Asset Account (%s) Name: %s\n"
							" Last retrieved Balance: %s  on date: %s\n"
							" accountID: %s\n"
							" userID: %s\n"
							" serverID: %s\n"
							" assetTypeID: %s\n"
							"\n",
							strAcctType.Get(),
							m_strName.Get(),
							m_BalanceAmount.Get(),
							m_BalanceDate.Get(),
							strAccountID.Get(),
							strUserID.Get(),
							strServerID.Get(),
							strAssetTypeID.Get());

	return true;
}


bool OTAccount::SaveContractWallet(OTString & strContents) const
{
	const OTString	strAccountID(GetPurportedAccountID()),
					strServerID(GetPurportedServerID()),
					strUserID(GetUserID()),
					strAssetTypeID(m_AcctAssetTypeID);

	OTString strAcctType;
	TranslateAccountTypeToString(m_AcctType, strAcctType);

	OTASCIIArmor ascName;

	if (m_strName.Exists()) // name is in the clear in memory, and base64 in storage.
	{
		ascName.SetString(m_strName, false); // linebreaks == false
	}

	strContents.Concatenate("<!-- Last retrieved balance: %s on date: %s -->\n"
							"<!-- Account type: %s --><assetAccount name=\"%s\"\n"
							" accountID=\"%s\"\n"
							" userID=\"%s\"\n"
							" serverID=\"%s\" />\n"
							"<!-- assetTypeID: %s -->\n\n",
							m_BalanceAmount.Get(),
							m_BalanceDate.Get(),
							strAcctType.Get(),
							m_strName.Exists() ? ascName.Get() : "",
							strAccountID.Get(),
							strUserID.Get(),
							strServerID.Get(),
							strAssetTypeID.Get());
	return true;
}


bool OTAccount::SaveContractWallet(std::ofstream & ofs)
{
	OTString strOutput;

	if (SaveContractWallet(strOutput))
	{
		ofs << strOutput.Get();
		return true;
	}

	return false;
}


/*
bool OTAccount::SaveContractWallet(FILE * fl)
{
	OTString strAccountID(GetPurportedAccountID()), strServerID(GetPurportedServerID()), strUserID(GetUserID());

	fprintf(fl, "<assetAccount name=\"%s\"\n file=\"%s\"\n userID=\"%s\"\n serverID=\"%s\"\n accountID=\"%s\"  /> "
			"\n\n", m_strName.Get(), m_strFilename.Get(), strUserID.Get(), strServerID.Get(), strAccountID.Get());

	return true;
}
*/

// Most contracts do not override this function...
// But OTAccount does, because IF THE SIGNER has chosen to SIGN the account based on
// the current balances, then we need to update the m_xmlUnsigned member with the
// current balances and other updated information before the signing occurs. (Presumably
// this is the whole reason why the account is being re-signed.)
//
// Normally, in other OTContract and derived classes, m_xmlUnsigned is read
// from the file and then kept read-only, since contracts do not normally change.
// But as accounts change in balance, they must be re-signed to keep the signatures valid.

void OTAccount::UpdateContents()
{
	OTString strAssetTYPEID(m_AcctAssetTypeID); // asset type

	OTString ACCOUNT_ID(GetPurportedAccountID()), SERVER_ID(GetPurportedServerID()), USER_ID(GetUserID());

	OTString strAcctType;
	TranslateAccountTypeToString(m_AcctType, strAcctType);

	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();

	m_xmlUnsigned.Concatenate("<?xml version=\"%s\"?>\n\n", "1.0");

	m_xmlUnsigned.Concatenate("<assetAccount\n version=\"%s\"\n type=\"%s\"\n accountID=\"%s\"\n userID=\"%s\"\n"
							  " serverID=\"%s\"\n assetTypeID=\"%s\" >\n\n", m_strVersion.Get(), strAcctType.Get(),
							  ACCOUNT_ID.Get(), USER_ID.Get(), SERVER_ID.Get(), strAssetTYPEID.Get());
	if (IsStashAcct())
		m_xmlUnsigned.Concatenate("<stashinfo cronItemNum=\"%lld\"/>\n\n", m_lStashTransNum);

    // -------------------------------------------------
	if (!m_InboxHash.IsEmpty())
    {
        const OTString strHash(m_InboxHash);
		m_xmlUnsigned.Concatenate("<inboxHash value=\"%s\"/>\n\n", strHash.Get());
    }
	if (!m_OutboxHash.IsEmpty())
    {
        const OTString strHash(m_OutboxHash);
		m_xmlUnsigned.Concatenate("<outboxHash value=\"%s\"/>\n\n", strHash.Get());
    }
    // -------------------------------------------------

//	m_xmlUnsigned.Concatenate("<balance amount=\"%s\"/>\n\n", m_BalanceAmount.Get());
	m_xmlUnsigned.Concatenate("<balance date=\"%s\" amount=\"%s\"/>\n\n", m_BalanceDate.Get(), m_BalanceAmount.Get());

    if (m_bMarkForDeletion)
        m_xmlUnsigned.Concatenate("<MARKED_FOR_DELETION>\n"
                                  "%s</MARKED_FOR_DELETION>\n\n",
                                  "THIS ACCOUNT HAS BEEN MARKED FOR DELETION AT ITS OWN REQUEST");

	m_xmlUnsigned.Concatenate("</assetAccount>\n");
}


// return -1 if error, 0 if nothing, and 1 if the node was processed.
int32_t OTAccount::ProcessXMLNode(IrrXMLReader*& xml)
{
	int32_t nReturnVal = 0;

    const OTString strNodeName(xml->getNodeName());

	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do below, in the case of OTAccount.
	//if (nReturnVal = OTTransactionType::ProcessXMLNode(xml))
	//	return nReturnVal;

	if (strNodeName.Compare("assetAccount"))
	{
		OTString strAcctType;

		m_strVersion	= xml->getAttributeValue("version");
		strAcctType		= xml->getAttributeValue("type");

		if (!strAcctType.Exists())
		{
			OTLog::Error("OTAccount::ProcessXMLNode: Failed: Empty assetAccount 'type' attribute.\n");
			return (-1);
		}

		m_AcctType = TranslateAccountTypeStringToEnum(strAcctType);

		if (OTAccount::err_acct == m_AcctType)
		{
			OTLog::Error("OTAccount::ProcessXMLNode: Failed: assetAccount 'type' attribute contains unknown value.\n");
			return (-1);
		}

		// -------------------------------------------------
        const OTString strAcctAssetType	= xml->getAttributeValue("assetTypeID");

        if (strAcctAssetType.Exists())
            m_AcctAssetTypeID.SetString(strAcctAssetType);
		// -------------------------------------------------

		OTString	strAccountID(xml->getAttributeValue("accountID")),
        strServerID(xml->getAttributeValue("serverID")),
        strAcctUserID(xml->getAttributeValue("userID"));

		OTIdentifier	ACCOUNT_ID(strAccountID),
                        SERVER_ID(strServerID),
                        USER_ID(strAcctUserID);

		SetPurportedAccountID(ACCOUNT_ID);
		SetPurportedServerID(SERVER_ID);
		SetUserID(USER_ID);

		OTString strAssetTypeID(m_AcctAssetTypeID);
		OTLog::vOutput(3,
                       //	"\n===> Loading XML for Account into memory structures..."
                       "\n\nAccount Type: %s\nAccountID: %s\nUserID: %s\n"
                       "AssetTypeID: %s\nServerID: %s\n",
                       strAcctType.Get(), strAccountID.Get(), strAcctUserID.Get(),
                       strAssetTypeID.Get(), strServerID.Get());

		nReturnVal = 1;
	}

	else if (strNodeName.Compare("inboxHash"))
	{
		// -------------------------------------------------
        const OTString strHash	= xml->getAttributeValue("value");
        if (strHash.Exists())
            m_InboxHash.SetString(strHash);
		// -------------------------------------------------
		OTLog::vOutput(3, "Account inboxHash: %s\n", strHash.Get());
		// -------------------------------------------------
		nReturnVal = 1;
	}

	else if (strNodeName.Compare("outboxHash"))
	{
		// -------------------------------------------------
        const OTString strHash	= xml->getAttributeValue("value");
        if (strHash.Exists())
            m_OutboxHash.SetString(strHash);
		// -------------------------------------------------
		OTLog::vOutput(3, "Account outboxHash: %s\n", strHash.Get());
		// -------------------------------------------------
		nReturnVal = 1;
	}

    else if (strNodeName.Compare("MARKED_FOR_DELETION"))
    {
        m_bMarkForDeletion = true;
        OTLog::vOutput(3, "This asset account has been MARKED_FOR_DELETION (at some point prior.)\n");

        nReturnVal = 1;
    }

    else if (strNodeName.Compare("balance"))
	{
		m_BalanceDate	= xml->getAttributeValue("date");
		m_BalanceAmount	= xml->getAttributeValue("amount");

		// I convert to integer / int64_t and back to string.
		// (Just an easy way to keep the data clean.)

		int32_t nDate		= atoi(m_BalanceDate.Get());
		int64_t lAmount	= atol(m_BalanceAmount.Get());

		m_BalanceDate.Format("%d", nDate);
		m_BalanceAmount.Format("%lld", lAmount);

//		OTLog::vOutput(1, "\nBALANCE  --  %s\n",
//					   m_BalanceAmount.Get());
		OTLog::vOutput(3, "\nBALANCE  --  %s\nDATE     --  %s\n",
					   m_BalanceAmount.Get(), m_BalanceDate.Get());

		nReturnVal = 1;
	}

    else if (strNodeName.Compare("stashinfo"))
	{
		if (!IsStashAcct())
		{
			OTLog::Error("OTAccount::ProcessXMLNode: Error: Encountered stashinfo tag while loading NON-STASH account. \n");
			return (-1);
		}
		// ------------------------------------------------------------------------
		int64_t lTransNum = 0;
		const OTString	strStashTransNum	= xml->getAttributeValue("cronItemNum");
		if (!strStashTransNum.Exists() || ((lTransNum = atol(strStashTransNum.Get())) <= 0))
		{
			m_lStashTransNum = 0;
			OTLog::vError("OTAccount::ProcessXMLNode: Error: Bad transaction number for supposed corresponding cron item: %lld \n",
						 lTransNum);
			return (-1);
		}
		else
			m_lStashTransNum = lTransNum;

		// ------------------------------

		OTLog::vOutput(3, "\nSTASH INFO:   CronItemNum     --  %lld\n", m_lStashTransNum);

		nReturnVal = 1;
	}

	return nReturnVal;
}


/*
 simple,		// used by users
 issuer,		// used by issuers	(these can only go negative.)

 basket,		// used by basket currencies (for basket issuer account)
 basketsub,		// used by server to store backing reserves for basket sub accounts.
 mint,		// used by mints (to store backing reserves for cash)
 voucher,	// used by the server (to store backing reserves for vouchers)
 stash,		// used by the server (to store backing reserves for stashes, for smart contracts.)

 err_acct
 */

bool OTAccount::IsInternalServerAcct() const
{
	bool bReturnVal = false;

	switch (m_AcctType)
	{
		case OTAccount::simple:
		case OTAccount::issuer:
			bReturnVal = false;
			break;
		case OTAccount::basket:
		case OTAccount::basketsub:
		case OTAccount::mint:
		case OTAccount::voucher:
		case OTAccount::stash:
			bReturnVal = true;
			break;
		default:
			OTLog::Error("OTAccount::IsInternalServerAcct: Unknown account type.\n");
			bReturnVal = false;
			break;
	}

	return bReturnVal;
}


bool OTAccount::IsOwnedByUser() const
{
	bool bReturnVal = false;

	switch (m_AcctType)
	{
		case OTAccount::simple:
		case OTAccount::issuer:
			bReturnVal = true;
			break;
		case OTAccount::basket:
		case OTAccount::basketsub:
		case OTAccount::mint:
		case OTAccount::voucher:
		case OTAccount::stash:
			bReturnVal = false;
			break;
		default:
			OTLog::Error("OTAccount::IsOwnedByUser: Unknown account type.\n");
			bReturnVal = false;
			break;
	}

	return bReturnVal;
}


bool OTAccount::IsOwnedByEntity() const
{
	return false;
}


bool OTAccount::IsIssuer() const
{
    return (OTAccount::issuer == m_AcctType);
}


bool OTAccount::IsAllowedToGoNegative() const
{
	bool bReturnVal = false;

	switch (m_AcctType)
	{
		case OTAccount::issuer:		// issuer acct controlled by a user
		case OTAccount::basket:		// basket issuer acct controlled by the server (for a basket currency)
			bReturnVal = true;
			break;
		case OTAccount::simple:		// user asset acct
		case OTAccount::basketsub:	// internal server acct for storing reserves for basket sub currencies
		case OTAccount::mint:		// internal server acct for storing reserves for cash withdrawals
		case OTAccount::voucher:	// internal server acct for storing reserves for vouchers (like cashier's cheques)
		case OTAccount::stash:		// internal server acct for storing reserves for smart contract stashes. (Money stashed IN the contract.)
			bReturnVal = false;
			break;
		default:
			OTLog::Error("OTAccount::IsAllowedToGoNegative: Unknown account type.\n");
			bReturnVal = false;
			break;
	}

	return bReturnVal;
}


void OTAccount::Release_Account()
{
    m_BalanceDate.Release();
	m_BalanceAmount.Release();

    m_InboxHash.Release();
    m_OutboxHash.Release();
}


void OTAccount::Release()
{
    Release_Account();
    // -----------------------------
    ot_super::Release();
}


OTAccount::~OTAccount()
{
    Release_Account();
}
