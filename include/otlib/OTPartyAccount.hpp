/************************************************************
 *
 *  OTPartyAccount.hpp
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

#ifndef __OT_PARTY_ACCOUNT_HPP__
#define __OT_PARTY_ACCOUNT_HPP__

#include "OTString.hpp"

class OTAccount;
class OTAgent;
class OTIdentifier;
class OTParty;
class OTPseudonym;
class OTScript;
class OTSmartContract;

typedef std::map<std::string, OTPseudonym *>	mapOfNyms;


// Each party has a list of accounts. Just as the agent, depending on context, MAY
// have an unowned-but-useful pointer to its active Nym, similarly a partyaccount
// MAY have an unowned-but-useful point to its actual Account.
//
// (Normally, an OTPartyAccount is loaded with the party, as part of an OTScriptable-
// derived object, and it doesn't actually load a copy of the actual Nyms and Accounts
// at that time, it just stores their IDs. But times may also come when the actual pointer
// is passed in for use by the Parties, who are not otherwise expected to do anything
// with it, or to clean it up or rely on it for their normal data storage.)
//
// Represents an account (to a party.) This is because ACTUALLY loading the REAL account is a pain in the ass,
// and we just want to store its ID, etc.  This way, the party can OWN this information about this list of
// accounts, and store it, load it, destroy it, etc, often without involving the actual account file at all.
//
// (Even if a this isn't currently doing anything with any of the party's accounts, the contract still
// has to have a LIST of them, so it knows what to do in those cases when it DOES need to do something.)
//
// For example, this is where we store the CLOSING TRANSACTION # for that account (for this agreement.)
// That number can't be found in the account itself, but all smart contracts involving asset accounts must
// provide a closing number for each asset account.
//
class OTPartyAccount
{
	OTParty *	m_pForParty; // When being added to a party, this pointer will be set.
	// -------------------------
	// NOTE: each party needs to have a list of partyaccounts, AND each account on that list needs to have a CLOSING #!!! Ahh...
	OTAccount * m_pAccount;
	int64_t		m_lClosingTransNo; // Any account that is party to an agreement, must have a closing transaction # for finalReceipt.
	// -------------------------
	// account name (inside the script language, "gold_acct_A" could be used to reference this acct.)
	//
	OTString	m_strName;			// Name of the account (for use in scripts.)
	OTString	m_strAcctID;		// The Account ID itself.
	OTString	m_strAssetTypeID;	// The asset type ID for the account. Stored because parties agree on this even before the account ID is selected. Compare() uses this even when the account ID is blank, and when acct ID *is* added, its asset type must match this.
	OTString	m_strAgentName;		// The name of the agent who has rights to this account.
	// -------------------------
	// Entity, role, and Nym information are not stored here.
	// Entity is already known on the party who owns this account (and I should have a ptr to him.)
	// Role is already known on the agent who is presumably on the party's list of agents.
	// Nym is known on the party (for owner) and on the agent.

	// "GetOwnerID()" for a partyaccount (if it were to store NymID, EntityID, and a bool to choose
	// between them) should be logically the same as m_pOwnerParty->GetPartyID().
	//
public:
EXPORT	void RegisterForExecution(OTScript & theScript);

	OTParty * GetParty() { return m_pForParty; }
	void SetParty(OTParty & theOwnerParty); // This happens when the partyaccount is added to the party. (so I have a ptr back)

EXPORT	const OTString & GetName()			const	{ return m_strName; }			// account's name as used in a script.
        const OTString & GetAgentName()		const	{ return m_strAgentName; }		// agent's name as used in a script.
        const OTString & GetAcctID()		const	{ return m_strAcctID; }			// account's ID as used internal to OT.
        const OTString & GetAssetTypeID()	const	{ return m_strAssetTypeID; }	// asset type ID for the account.

	void SetAgentName(const OTString & strAgentName)	{ m_strAgentName	= strAgentName; }
	void SetAcctID(const OTString & strAccountID)		{ m_strAcctID		= strAccountID; }
    // ----------------------------
EXPORT	OTAgent   * GetAuthorizedAgent();
	// ----------------------------
	OTAccount * LoadAccount(OTPseudonym & theSignerNym, const OTString & strServerID);
	// ----------------------------
	bool IsAccount(OTAccount & theAccount);
	bool IsAccountByID(const OTIdentifier & theAcctID) const;
	// ----------------------------
	bool VerifyOwnership() const; // I have a ptr to my owner (party), as well as to the actual account. I will ask him to verify whether he actually owns it.
	bool VerifyAgency(); // I can get a ptr to my agent, and I have one to the actual account. I will ask him to verify whether he actually has agency over it.
	// -------------------
	int64_t GetClosingTransNo() const { return m_lClosingTransNo; }
	void SetClosingTransNo(const int64_t lTransNo) { m_lClosingTransNo = lTransNo; }
	// -----------
	bool Compare(const OTPartyAccount & rhs) const;
	// -----------
	bool DropFinalReceiptToInbox(mapOfNyms * pNymMap,
								 const OTString & strServerID,
								 OTPseudonym & theServerNym,
								 OTSmartContract & theSmartContract,
								 const int64_t & lNewTransactionNumber,
								 const OTString & strOrigCronItem,
								 OTString * pstrNote=NULL,
								 OTString * pstrAttachment=NULL);
	// ------------------------------------------------------------
	OTPartyAccount();
	OTPartyAccount(const std::string str_account_name, const OTString & strAgentName, OTAccount & theAccount, int64_t lClosingTransNo);
	OTPartyAccount(const OTString & strName, const OTString & strAgentName, const OTString & strAcctID, const OTString & strAssetTypeID, int64_t lClosingTransNo);

	virtual ~OTPartyAccount();

	void Serialize(OTString & strAppend,
				   bool bCalculatingID=false,
				   bool bSpecifyAssetID=false);

	// For pointers I don't own, but store for convenience.
	// This clears them once we're done processing, so I don't
	// end up stuck with bad pointers on the next go-around.
	//
	void ClearTemporaryPointers() { m_pAccount = NULL; }
};


#endif // __OT_PARTY_ACCOUNT_HPP__
