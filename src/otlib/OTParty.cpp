/************************************************************
 *
 *  OTParty.cpp
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

#include "OTParty.hpp"

#include "OTAgent.hpp"
#include "OTLog.hpp"
#include "OTPartyAccount.hpp"
#include "OTPseudonym.hpp"
#include "OTSmartContract.hpp"


// Checks opening number on party, and closing numbers on his accounts.
//
bool OTParty::HasTransactionNum(const int64_t & lInput) const
{
    if (lInput == m_lOpeningTransNo)
        return true;
    // ------------------------------------
    FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		const OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL  != pAcct, "Unexpected NULL partyaccount pointer in party map.");
		// ---------------------------------
        if (lInput == pAcct->GetClosingTransNo())
            return true;
	}
    // -------------------------------------
    return false;
}


void OTParty::GetAllTransactionNumbers(OTNumList & numlistOutput) const
{
    if (m_lOpeningTransNo > 0)
        numlistOutput.Add(m_lOpeningTransNo);
    // ------------------------------------
    FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		const OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL  != pAcct, "Unexpected NULL partyaccount pointer in party map.");
		// ---------------------------------
        const int64_t lTemp = pAcct->GetClosingTransNo();
        if (lTemp > 0)
            numlistOutput.Add(lTemp);
	}
    // -------------------------------------
}


// Only counts accounts authorized for str_agent_name.
//
int32_t OTParty::GetAccountCount(const std::string str_agent_name) const
{
	int32_t nCount = 0;

	FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		const OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL != pAcct, "Unexpected NULL partyaccount pointer in party map.");
		// -------------------------------------
		const OTString & strAgentName = pAcct->GetAgentName();
		// -------------------------------------
		if (strAgentName.Compare(str_agent_name.c_str()))
			nCount++;
	}

	return nCount;
}


// Party is always either an Owner Nym, or an Owner Entity formed by Contract.
//
// Either way, the agents are there to represent the interests of the parties.
//
// This is meant in the sense of "actually" since the agent is not just a trusted
// friend of the party, but is either the party himself (if party is a Nym), OR is
// a voting group or employee that belongs to the party. (If party is an entity.)
// Either way, the point is that in this context, the agent is ACTUALLY authorized
// by the party by virtue of its existence, versus being a "separate but authorized"
// party in the legal sense. No need exists to "grant" the authority since the
// authority is already INHERENT.
//
// A party may also have multiple agents.
//

// std::string * m_pstr_party_name;

OTParty::OTParty()
: m_pstr_party_name(NULL), m_bPartyIsNym(false),
  m_lOpeningTransNo(0), m_pOwnerAgreement(NULL)
{

}


OTParty::OTParty(const char * szName, bool bIsOwnerNym, const char * szOwnerID, const char * szAuthAgent, const bool bCreateAgent/*=false*/)
: m_pstr_party_name(NULL), m_bPartyIsNym(bIsOwnerNym), m_str_owner_id(szOwnerID != NULL ? szOwnerID : ""),
  m_str_authorizing_agent(szAuthAgent != NULL ? szAuthAgent : ""),
  m_lOpeningTransNo(0), m_pOwnerAgreement(NULL)
{
    m_pstr_party_name = new std::string(szName != NULL ? szName : "");

	// ------------------------------------------
	if (bCreateAgent)
	{
		const OTString	strName(m_str_authorizing_agent.c_str()),
						strNymID(""), strRoleID(""), strGroupName("");
		OTAgent * pAgent = new OTAgent(true /*bNymRepresentsSelf*/, true /*bIsAnIndividual*/,
									   strName, strNymID, strRoleID, strGroupName);
		OT_ASSERT(NULL != pAgent);

		if (!AddAgent(*pAgent))
		{
			OTLog::Error("OTParty::OTParty: *** Failed *** while adding default agent in CONSTRUCTOR! 2\n");
			delete pAgent; pAgent = NULL;
		}
	}
	// ------------------------------------------
}


OTParty::OTParty(const std::string		str_PartyName,
				 OTPseudonym &			theNym, // Nym is BOTH owner AND agent, when using this constructor.
				 const std::string		str_agent_name,
				 OTAccount *			pAccount/*=NULL*/,
				 const std::string *	pstr_account_name/*=NULL*/,
				 const int64_t				lClosingTransNo/*=0*/
				 )
: m_pstr_party_name(new std::string(str_PartyName)), m_bPartyIsNym(true),
  m_lOpeningTransNo(0), m_pOwnerAgreement(NULL)
{
//  m_pstr_party_name = new std::string(str_PartyName);
	OT_ASSERT(NULL != m_pstr_party_name);

	// theNym is owner, therefore save his ID information, and create the agent
	// for this Nym automatically (that's why it was passed in.)
	// This code won't compile until you do.  :-)

	OTString strNymID;
	theNym.GetIdentifier(strNymID);
    m_str_owner_id = strNymID.Get();

//	std::string			m_str_authorizing_agent;	// Empty until contract is confirmed. Contains the name of the authorizing agent (the one who supplied the opening Trans#)
//	int64_t				m_lOpeningTransNo;			// Empty until contract is confirmed. Each party (to a smart contract anyway) must provide an opening transaction #.
//	OTString			m_strMySignedCopy;			// Empty until contract is confirmed.
//	mapOfAgents			m_mapAgents;				// (Often) empty until contract is confirmed. These are owned.
//	mapOfPartyAccounts	m_mapPartyAccounts;			// These are owned. Each contains a Closing Transaction#.

	OTAgent * pAgent = new OTAgent(str_agent_name, theNym); // (The third arg, bRepresentsSelf, defaults here to true.)
	OT_ASSERT(NULL != pAgent);

	if (!AddAgent(*pAgent))
	{
		OTLog::Error("OTParty::OTParty: *** Failed *** while adding default agent in CONSTRUCTOR!\n");
		delete pAgent; pAgent = NULL;
	}
	else
		m_str_authorizing_agent = str_agent_name;
	// ------------------------------------------

	// if pAccount is NOT NULL, then an account was passed in, so
	// let's also create a default partyaccount for it.
	//
	if (NULL != pAccount)
	{
		OT_ASSERT(NULL != pstr_account_name); // If passing an account, then you MUST pass an account name also.

		bool bAdded = AddAccount(str_agent_name.c_str(), pstr_account_name->c_str(),
								 *pAccount, lClosingTransNo);

		if (!bAdded)
			OTLog::Error("OTParty::OTParty: *** Failed *** while adding default account in CONSTRUCTOR!\n");
	}
}


bool OTParty::AddAgent(OTAgent& theAgent)
{
	const std::string str_agent_name = theAgent.GetName().Get();

	if (!OTScriptable::ValidateName(str_agent_name))
	{
		OTLog::Error("OTParty::AddAgent: Failed validating Agent name.");
		return false;
	}
	// -------------------------------------------------

	mapOfAgents::iterator ii = m_mapAgents.find(str_agent_name);

	if (m_mapAgents.end() == ii) // If it wasn't already there...
	{
		// TODO: Validate here that the same agent isn't already on this party under a different name.
		// Server either has to validate this as well, or be smart enough to juggle the Nyms inside the
		// agents so that they aren't loaded twice.

		// -------------------------------
		// Then insert it...
		m_mapAgents.insert(std::pair<std::string, OTAgent *>(str_agent_name, &theAgent));

		// Make sure it has a pointer back to me.
		theAgent.SetParty(*this);

		return true;
	}
	else
		OTLog::vOutput(0, "OTParty::AddAgent: Failed -- Agent was already there named %s.\n", str_agent_name.c_str());

	return false;
}


bool OTParty::AddAccount(const OTString& strAgentName,
						 const OTString& strName,
						 const OTString & strAcctID,
						 const OTString & strAssetTypeID,
						 const int64_t lClosingTransNo)
{
	OTPartyAccount * pPartyAccount = new OTPartyAccount(strName, strAgentName, strAcctID, strAssetTypeID, lClosingTransNo);
	OT_ASSERT(NULL != pPartyAccount);

	if (false == AddAccount(*pPartyAccount))
	{
		delete pPartyAccount;
		return false;
	}

	return true;
}


bool OTParty::AddAccount(const OTString& strAgentName,
						 const char * szAcctName,
						 OTAccount& theAccount,
						 const int64_t lClosingTransNo)
{
	OTPartyAccount * pPartyAccount = new OTPartyAccount(szAcctName, strAgentName, theAccount, lClosingTransNo);
	OT_ASSERT(NULL != pPartyAccount);

	if (false == AddAccount(*pPartyAccount))
	{
		delete pPartyAccount;
		return false;
	}

	return true;
}


bool OTParty::AddAccount(OTPartyAccount& thePartyAcct)
{
	const std::string str_acct_name = thePartyAcct.GetName().Get();

	if (!OTScriptable::ValidateName(str_acct_name))
	{
		OTLog::Error("OTParty::AddAccount: Failed validating Account name.");
		return false;
	}
	// -------------------------------------------------

	mapOfPartyAccounts::iterator ii = m_mapPartyAccounts.find(str_acct_name);

	if (m_mapPartyAccounts.end() == ii) // If it wasn't already there...
	{
		// Todo:  Validate here that there isn't another account already on the same party
		// that, while it has a different "account name" actually has the same Account ID.
		// We do not want the same Account ID on multiple accounts. (Unless the script
		// interpreter is going to be smart enough to make them available that way without
		// ever loading the same account twice.) We can't otherwise take the risk, si server
		//  will have to validate this unless it juggles the accounts like that.
		//
		// ----------------

		// Then insert it...
		m_mapPartyAccounts.insert(std::pair<std::string, OTPartyAccount *>(str_acct_name, &thePartyAcct));

		// Make sure it has a pointer back to me.
		thePartyAcct.SetParty(*this);

		return true;
	}
	else
		OTLog::vOutput(0, "OTParty::AddAccount: Failed -- Account was already on party named %s.\n",
					   str_acct_name.c_str());

	return false;
}


int64_t OTParty::GetClosingTransNo(const std::string str_for_acct_name) const
{
	mapOfPartyAccounts::const_iterator it = m_mapPartyAccounts.find(str_for_acct_name);

	if (m_mapPartyAccounts.end() == it) // If it wasn't already there...
	{
		OTLog::vOutput(0, "OTParty::GetClosingTransNo: Failed -- Account wasn't found: %s.\n",
					   str_for_acct_name.c_str());
		return 0;
	}

	OTPartyAccount * pPartyAccount = (*it).second;
	OT_ASSERT(NULL != pPartyAccount);

	return pPartyAccount->GetClosingTransNo();
}


//OTParty::OTParty(const OTParty & rhs)
//{
//    this->SetPartyName(rhs.GetPartyName());
//    m_bPartyIsNym = rhs.m_bPartyIsNym;
//    m_pAccount = rhs.m_pAccount;
//}
//
//OTParty& OTParty::operator= (const OTParty & rhs)
//{
//    this->SetPartyName(rhs.GetPartyName());
//    m_bPartyIsNym = rhs.m_bPartyIsNym;
//    m_pAccount = rhs.m_pAccount;
//
//    return *this;
//}

void OTParty::CleanupAgents()
{
	// ------------------------
	while (!m_mapAgents.empty())
	{
		OTAgent * pTemp = m_mapAgents.begin()->second;
		OT_ASSERT(NULL != pTemp);
		delete pTemp; pTemp = NULL;
		m_mapAgents.erase(m_mapAgents.begin());
	}
	// ------------------------
}


void OTParty::CleanupAccounts()
{
	// ------------------------
	while (!m_mapPartyAccounts.empty())
	{
		OTPartyAccount * pTemp = m_mapPartyAccounts.begin()->second;
		OT_ASSERT(NULL != pTemp);
		delete pTemp; pTemp = NULL;
		m_mapPartyAccounts.erase(m_mapPartyAccounts.begin());
	}
	// ------------------------
}


OTParty::~OTParty()
{
	CleanupAgents();
	CleanupAccounts();

    if (NULL != m_pstr_party_name)
        delete m_pstr_party_name;
	m_pstr_party_name = NULL;

	m_pOwnerAgreement = NULL;
}


void OTParty::ClearTemporaryPointers()
{
	FOR_EACH(mapOfAgents, m_mapAgents)
	{
		OTAgent * pAgent = (*it).second;
		OT_ASSERT_MSG(NULL != pAgent, "Unexpected NULL agent pointer in party map.");

		pAgent->ClearTemporaryPointers();
	}
	// -------------------------------------

	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL != pAcct, "Unexpected NULL partyaccount pointer in party map.");

		pAcct->ClearTemporaryPointers();
	}
	// -------------------------------------
}


// as used "IN THE SCRIPT."
//
std::string OTParty::GetPartyName(bool * pBoolSuccess/*=NULL*/) const
{
    std::string retVal("");

	// "sales_director", "marketer", etc
    if (NULL == m_pstr_party_name)
    {
        if (NULL != pBoolSuccess)
            *pBoolSuccess = false;

        return retVal;
    }

    if (NULL != pBoolSuccess)
        *pBoolSuccess = true;

    retVal = *m_pstr_party_name;

    return retVal;
}


bool OTParty::SetPartyName(const std::string & str_party_name_input)
{
	if (!OTScriptable::ValidateName(str_party_name_input))
	{
		OTLog::Error("OTParty::SetPartyName: Failed: Invalid name was passed in.\n");
		return false;
	}
	// -------------------------------------

    if (NULL == m_pstr_party_name)
        OT_ASSERT(NULL != (m_pstr_party_name = new std::string));

    *m_pstr_party_name = str_party_name_input;

	return true;
}


// ACTUAL PARTY OWNER (Only ONE of these can be true...)
// Debating whether these two functions should be private. (Should it matter to outsider?)
//
bool OTParty::IsNym() const
{
    // If the party is a Nym. (The party is the actual owner/beneficiary.)
    return m_bPartyIsNym;
}


bool OTParty::IsEntity() const
{
    // If the party is an Entity. (Either way, the AGENT carries out all wishes.)
    return !m_bPartyIsNym;
}


// ACTUAL PARTY OWNER
//
std::string OTParty::GetNymID(bool * pBoolSuccess/*=NULL*/) const
{
	if (IsNym() && (m_str_owner_id.size() > 0))
	{
		if (NULL != pBoolSuccess)
            *pBoolSuccess = true;

		return m_str_owner_id;
	}

    if (NULL != pBoolSuccess)
        *pBoolSuccess = false;

	std::string retVal("");

    return retVal; // empty ID on failure.
}


std::string OTParty::GetEntityID(bool * pBoolSuccess/*=NULL*/) const
{
	if (IsEntity() && (m_str_owner_id.size() > 0))
	{
		if (NULL != pBoolSuccess)
            *pBoolSuccess = true;

		return m_str_owner_id;
	}

    if (NULL != pBoolSuccess)
        *pBoolSuccess = false;

    std::string retVal("");

    return retVal;
}


std::string OTParty::GetPartyID(bool * pBoolSuccess/*=NULL*/) const
{
    // If party is a Nym, this is the NymID. Else return EntityID().
    // if error, return false.

    if (IsNym())
        return GetNymID(pBoolSuccess);

    return GetEntityID(pBoolSuccess);
}


// Some agents are passive (voting groups) and cannot behave actively, and so cannot do
// certain things that only Nyms can do. But they can still act as an agent in CERTAIN
// respects, so they are still allowed to do so. However, likely many functions will
// require that HasActiveAgent() be true for a party to do various actions. Attempts to
// do those actions otherwise will fail.
// It's almost a separate kind of party but not worthy of a separate class.
//
bool OTParty::HasActiveAgent() const
{
    // Loop through all agents and call IsAnIndividual() on each.
    // then return true if any is true. else return false;
	//
	FOR_EACH_CONST(mapOfAgents, m_mapAgents)
	{
		OTAgent * pAgent = (*it).second;
		OT_ASSERT(NULL != pAgent);
		// -------------------------------

		if (pAgent->IsAnIndividual())
			return true;
	}

    return false;
}


/// Get Agent pointer by Name. Returns NULL on failure.
///
OTAgent * OTParty::GetAgent(const std::string & str_agent_name)
{
	if (OTScriptable::ValidateName(str_agent_name))
	{
		mapOfAgents::iterator it = m_mapAgents.find(str_agent_name);

		if (m_mapAgents.end() != it) // If we found something...
		{
			OTAgent * pAgent = (*it).second;
			OT_ASSERT(NULL != pAgent);
			// -------------------------------

			return pAgent;
		}
	}
	else
		OTLog::vError("%s: Failed: str_agent_name is invalid...\n", __FUNCTION__);

	return NULL;
}


/// Get Agent pointer by Index. Returns NULL on failure.
///
OTAgent * OTParty::GetAgentByIndex(int32_t nIndex)
{
    if (false == ((nIndex >= 0) && (nIndex < static_cast<int64_t>(m_mapAgents.size()))))
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;

        FOR_EACH(mapOfAgents, m_mapAgents)
        {
            OTAgent * pAgent = (*it).second;
            OT_ASSERT(NULL != pAgent);
            // -------------------------------
            ++nLoopIndex; // 0 on first iteration.

            if (nLoopIndex == nIndex)
                return pAgent;
        }
    }
    return NULL;
}


// Get PartyAccount pointer by Name. Returns NULL on failure.
//
OTPartyAccount * OTParty::GetAccount(const std::string & str_acct_name) const
{
//	OTLog::vError("DEBUGGING OTParty::GetAccount: above find. str_acct_name: %s \n", str_acct_name.c_str());

	if (OTScriptable::ValidateName(str_acct_name))
	{
		mapOfPartyAccounts::const_iterator it = m_mapPartyAccounts.find(str_acct_name);

		if (m_mapPartyAccounts.end() != it) // If we found something...
		{
			OTPartyAccount * pAcct = (*it).second;
			OT_ASSERT(NULL != pAcct);
			// -------------------------------

			return pAcct;
		}
	}
	else
		OTLog::Error("OTParty::GetAccount: Failed: str_acct_name is invalid.\n");

//	OTLog::vError("DEBUGGING OTParty::GetAccount: After find attempt, didn't find account on this party (%s).  \n",
//				  "Looping through accounts, to show you their names...\n", GetPartyName().c_str());
//
//	FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
//	{
//		std::string str_map_key = (*it).first;
//		OTPartyAccount * pAcct = (*it).second;
//		OT_ASSERT(NULL != pAcct);
//		// -------------------------------
//
//		OTLog::vError("DEBUGGING OTParty::GetAccount: Account name: %s.  Name as used for map key: %s \n",
//					  pAcct->GetName().Get(), str_map_key.c_str());
//	}
//
//	OTLog::Error("OTParty::GetAccount: DEBUGGING: (Finished displaying account names.)\n");

	return NULL;
}


/// Get OTPartyAccount pointer by Index. Returns NULL on failure.
///
OTPartyAccount * OTParty::GetAccountByIndex(int32_t nIndex)
{
    if (false == ((nIndex >= 0) && (nIndex < static_cast<int64_t>(m_mapPartyAccounts.size()))))
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;

        FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
        {
            OTPartyAccount * pAcct = (*it).second;
            OT_ASSERT(NULL != pAcct);
            // -------------------------------
            ++nLoopIndex; // 0 on first iteration.

            if (nLoopIndex == nIndex)
                return pAcct;
        }
    }
    return NULL;
}


// Get PartyAccount pointer by Agent Name. (It just grabs the first one.)
//
// Returns NULL on failure.
OTPartyAccount * OTParty::GetAccountByAgent(const std::string & str_agent_name)
{
	if (OTScriptable::ValidateName(str_agent_name))
	{
		FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
		{
			OTPartyAccount * pAcct = (*it).second;
			OT_ASSERT(NULL != pAcct);
			// ----------------

			if (pAcct->GetAgentName().Compare(str_agent_name.c_str()))
				return pAcct;
		}
	}
	else
		OTLog::vError("%s: Failed: str_agent_name is invalid.\n", __FUNCTION__);

	return NULL;
}


// Get PartyAccount pointer by Acct ID.
//
// Returns NULL on failure.
OTPartyAccount * OTParty::GetAccountByID(const OTIdentifier & theAcctID) const
{
	FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT(NULL != pAcct);
		// ----------------

		if (pAcct->IsAccountByID(theAcctID))
			return pAcct;
	}

	return NULL;
}


//bool OTPartyAccount::IsAccountByID(const OTIdentifier & theAcctID) const

// If account is present for Party, return true.
bool OTParty::HasAccountByID(const OTIdentifier & theAcctID, OTPartyAccount ** ppPartyAccount/*=NULL*/) const
{
	FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT(NULL != pAcct);
		// -------------------------------

		if (pAcct->IsAccountByID(theAcctID))
		{
			if (NULL != ppPartyAccount)
				*ppPartyAccount = pAcct;

			return true;
		}
	}

	return false;
}


// If account is present for Party, set account's pointer to theAccount and return true.
bool OTParty::HasAccount(OTAccount & theAccount, OTPartyAccount ** ppPartyAccount/*=NULL*/) const
{
	FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT(NULL != pAcct);
		// -------------------------------

		if (pAcct->IsAccount(theAccount))
		{
			if (NULL != ppPartyAccount)
				*ppPartyAccount = pAcct;

			return true;
		}
	}

	return false;
}


// Find out if theNym is an agent for Party.
// If so, make sure that agent has a pointer to theNym and return true.
// else return false.
//
bool OTParty::HasAgent(OTPseudonym & theNym, OTAgent ** ppAgent/*=NULL*/) const
{
	FOR_EACH_CONST(mapOfAgents, m_mapAgents)
	{
		OTAgent * pAgent = (*it).second;
		OT_ASSERT(NULL != pAgent);
		// -------------------------------

		if (pAgent->IsValidSigner(theNym))
		{
			if (NULL != ppAgent)
				*ppAgent = pAgent;

			return true;
		}
	}

	return false;
}


bool OTParty::HasAgentByNymID(const OTIdentifier & theNymID, OTAgent ** ppAgent/*=NULL*/) const
{
	FOR_EACH_CONST(mapOfAgents, m_mapAgents)
	{
		OTAgent * pAgent = (*it).second;
		OT_ASSERT(NULL != pAgent);
		// -------------------------------
		if (pAgent->IsValidSignerID(theNymID))
		{
			if (NULL != ppAgent)
				*ppAgent = pAgent;

			return true;
		}
	}

	return false;
}


// Find out if theNym is authorizing agent for Party. (Supplied opening transaction #)
// If so, make sure that agent has a pointer to theNym and return true.
// else return false.
//
bool OTParty::HasAuthorizingAgent(OTPseudonym & theNym, OTAgent ** ppAgent/*=NULL*/) const // ppAgent lets you get the agent ptr if it was there.
{
	if (OTScriptable::ValidateName(m_str_authorizing_agent))
	{
		mapOfAgents::const_iterator it = m_mapAgents.find(m_str_authorizing_agent);

		if (m_mapAgents.end() != it) // If we found something...
		{
			OTAgent * pAgent = (*it).second;
			OT_ASSERT(NULL != pAgent);
			// -------------------------------

			if (pAgent->IsValidSigner(theNym)) // if theNym is valid signer for pAgent.
			{
				// Optionally can pass in a pointer-to-pointer-to-Agent, in order to get the Agent pointer back.
				if (NULL != ppAgent)
					*ppAgent = pAgent;

				return true;
			}
		}
		else // found nothing.
			OTLog::Error("OTParty::HasAuthorizingAgent: named agent wasn't found on list.\n");
	}

	return false;
}


bool OTParty::HasAuthorizingAgentByNymID(const OTIdentifier & theNymID, OTAgent ** ppAgent/*=NULL*/) const // ppAgent lets you get the agent ptr if it was there.
{
	if (OTScriptable::ValidateName(m_str_authorizing_agent))
	{
		mapOfAgents::const_iterator it = m_mapAgents.find(m_str_authorizing_agent);

		if (m_mapAgents.end() != it) // If we found something...
		{
			OTAgent * pAgent = (*it).second;
			OT_ASSERT(NULL != pAgent);
			// -------------------------------

			if (pAgent->IsValidSignerID(theNymID)) // if theNym is valid signer for pAgent.
			{
				// Optionally can pass in a pointer-to-pointer-to-Agent, in order to get the Agent pointer back.
				if (NULL != ppAgent)
					*ppAgent = pAgent;

				return true;
			}
		}
		else // found nothing.
			OTLog::Error("OTParty::HasAuthorizingAgentByNymID: named agent wasn't found on list.\n");
	}

	return false;
}


void OTParty::RetrieveNymPointers(mapOfNyms & map_Nyms_Already_Loaded)
{
	FOR_EACH(mapOfAgents, m_mapAgents)
	{
		OTAgent * pAgent = (*it).second;
		OT_ASSERT(NULL != pAgent);
		// -------------------------------

		pAgent->RetrieveNymPointer(map_Nyms_Already_Loaded);
	}
}


// Load up the Nym that authorized the agreement for this party
// (the nym who supplied the opening trans# to sign it.)
//
// This function ASSUMES that you ALREADY called HasAuthorizingAgentNym(), for example
// to verify that the serverNym isn't the one you were looking for.
// This is a low-level function.
// CALLER IS RESPONSIBLE TO DELETE.
//
OTPseudonym * OTParty::LoadAuthorizingAgentNym(OTPseudonym & theSignerNym, OTAgent ** ppAgent/*=NULL*/) // ppAgent lets you get the agent ptr if it was there.
{
	if (OTScriptable::ValidateName(m_str_authorizing_agent))
	{
		mapOfAgents::iterator it = m_mapAgents.find(m_str_authorizing_agent);

		if (m_mapAgents.end() != it) // If we found something...
		{
			OTAgent * pAgent = (*it).second;
			OT_ASSERT(NULL != pAgent);
			// -------------------------------

			OTPseudonym * pNym = NULL;

			if (false == pAgent->IsAnIndividual())
				OTLog::Error("OTParty::LoadAuthorizingAgentNym: This agent is not an individual--there's no Nym to load.\n");
			else if (NULL == (pNym = pAgent->LoadNym(theSignerNym)))
				OTLog::Error("OTParty::LoadAuthorizingAgentNym: Failed loading Nym.\n");
			else
			{
				if (NULL != ppAgent)	// Pass the agent back, too, if it was requested.
					*ppAgent = pAgent;

				return pNym;		// Success
			}
		}
		else // found nothing.
			OTLog::Error("OTParty::LoadAuthorizingAgentNym: named agent wasn't found on list.\n");
	}

	return NULL;
}


bool OTParty::VerifyOwnershipOfAccount(const OTAccount & theAccount) const
{
	if (this->IsNym()) // For those cases where the party is actually just a solitary Nym (not an entity.)
	{
		bool bNymID = false;
		std::string str_nym_id = this->GetNymID(&bNymID); // If the party is a Nym, this is the Nym's ID. Otherwise this is false.

		if (!bNymID || (str_nym_id.size() <= 0))
		{
			OTLog::Error(" OTParty::VerifyOwnershipOfAccount: Although party is a Nym, unable to retrieve NymID!\n");
			return false;
		}

		const OTIdentifier thePartyNymID(str_nym_id.c_str());

		return theAccount.VerifyOwnerByID(thePartyNymID);
	}
	else if (this->IsEntity())
		OTLog::Error("OTParty::VerifyOwnershipOfAccount: Error: Entities have not been implemented yet, "
					 "but somehow this party is an entity.\n");
	else
		OTLog::Error("OTParty::VerifyOwnershipOfAccount: Error: Unknown party type.\n");

	return false;
}


// This is only for SmartContracts, NOT all scriptables.
//
bool OTParty::DropFinalReceiptToInboxes(mapOfNyms * pNymMap,
										const OTString & strServerID,
										OTPseudonym & theServerNym,
										const int64_t & lNewTransactionNumber,
										const OTString & strOrigCronItem,
										OTString * pstrNote/*=NULL*/,
										OTString * pstrAttachment/*=NULL*/)
{
	bool bSuccess = true; // Success is defined as "all inboxes were notified"
	const
    char * szFunc = "OTParty::DropFinalReceiptToInboxes";

	OTSmartContract * pSmartContract = NULL;

	if (NULL == m_pOwnerAgreement)
	{
		OTLog::vError("%s: Missing pointer to owner agreement.\n", szFunc);
		return false;
	}
	else if (NULL == (pSmartContract = dynamic_cast<OTSmartContract*> (m_pOwnerAgreement)))
	{
		OTLog::vError("%s: Can only drop finalReceipts for smart contracts.\n", szFunc);
		return false;
	}

	// By this point, we know pSmartContract is a good pointer.
	// ----------------------------------------------

	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL != pAcct, "Unexpected NULL partyaccount pointer in party map.");
		// -------------------------------------

		if (false == pAcct->DropFinalReceiptToInbox(pNymMap,	// contains any Nyms who might already be loaded, mapped by ID.
													strServerID,
													theServerNym,
													*pSmartContract,
													lNewTransactionNumber,
													strOrigCronItem,
													pstrNote, pstrAttachment))
		{
			OTLog::vError("%s: Failed dropping final Receipt to agent's Inbox.\n", szFunc);
			bSuccess = false; // Notice: no break. We still try to notify them all, even if one fails.
		}
	}

	return bSuccess;
}


// This is only for SmartContracts, NOT all scriptables.
//
bool OTParty::DropFinalReceiptToNymboxes(const int64_t & lNewTransactionNumber,
										 const OTString & strOrigCronItem,
										 OTString      * pstrNote/*=NULL*/,
										 OTString      * pstrAttachment/*=NULL*/,
                                         OTPseudonym   * pActualNym/*=NULL*/)
{
	bool bSuccess = false; // Success is defined as "at least one agent was notified"

	OTSmartContract * pSmartContract = NULL;

	if (NULL == m_pOwnerAgreement)
	{
		OTLog::Error("OTParty::DropFinalReceiptToNymboxes: Missing pointer to owner agreement.\n");
		return false;
	}
	else if (NULL == (pSmartContract = dynamic_cast<OTSmartContract*> (m_pOwnerAgreement)))
	{
		OTLog::Error("OTParty::DropFinalReceiptToNymboxes: Can only drop finalReceipts for smart contracts.\n");
		return false;
	}

	// By this point, we know pSmartContract is a good pointer.
	// ----------------------------------------------

	FOR_EACH(mapOfAgents, m_mapAgents)
	{
		OTAgent * pAgent = (*it).second;
		OT_ASSERT_MSG(NULL != pAgent, "Unexpected NULL agent pointer in party map.");
		// -------------------------------------

		if (false == pAgent->DropFinalReceiptToNymbox(*pSmartContract, lNewTransactionNumber, strOrigCronItem,
													  pstrNote, pstrAttachment, pActualNym))
			OTLog::Error("OTParty::DropFinalReceiptToNymboxes: Failed dropping final Receipt to agent's Nymbox.\n");
		else
			bSuccess = true;
	}

	return bSuccess;
}


bool OTParty::SendNoticeToParty(bool bSuccessMsg,
                                OTPseudonym & theServerNym,
								const OTIdentifier & theServerID,
								const int64_t & lNewTransactionNumber,
//								const int64_t & lInReferenceTo, // todo Maybe have each party just use their own opening trans# here. Maybe not.
								const OTString & strReference,
								OTString      * pstrNote/*=NULL*/,
								OTString      * pstrAttachment/*=NULL*/,
                                OTPseudonym   * pActualNym/*=NULL*/)
{
	bool bSuccess = false; // Success is defined as "at least one agent was notified"

	if (NULL == m_pOwnerAgreement)
	{
		OTLog::vError("%s: Missing pointer to owner agreement.\n", __FUNCTION__);
		return false;
	}
	// ----------------------------------------------
	const int64_t lOpeningTransNo = this->GetOpeningTransNo();

    if (lOpeningTransNo > 0)
        FOR_EACH(mapOfAgents, m_mapAgents)
        {
            OTAgent * pAgent = (*it).second;
            OT_ASSERT_MSG(NULL != pAgent, "Unexpected NULL agent pointer in party map.");
            // -------------------------------------
            if (false == pAgent->DropServerNoticeToNymbox(bSuccessMsg,
                                                          theServerNym, theServerID,
                                                          lNewTransactionNumber,
                                                          lOpeningTransNo, // lInReferenceTo
                                                          strReference, pstrNote, pstrAttachment,
                                                          pActualNym))
                OTLog::vError("%s: Failed dropping server notice to agent's Nymbox.\n",
                              __FUNCTION__);
            else
                bSuccess = true;
        }

	return bSuccess;
}


bool OTParty::LoadAndVerifyAssetAccounts(OTPseudonym	& theServerNym,
										 const OTString	& strServerID,
										 mapOfAccounts	& map_Accts_Already_Loaded,
										 mapOfAccounts	& map_NewlyLoaded)
{
	std::set<std::string> theAcctIDSet; // Make sure all the acct IDs are unique.

	FOR_EACH_IT(mapOfPartyAccounts, m_mapPartyAccounts, it_acct)
	{
		const std::string str_acct_name = (*it_acct).first;
		OTPartyAccount * pPartyAcct = (*it_acct).second;
		OT_ASSERT(NULL != pPartyAcct);
		// --------------

		bool bHadToLoadtheAcctMyself = true;
		OTAccount * pAccount = NULL;

		const OTString & strAcctID = pPartyAcct->GetAcctID();

		if (!strAcctID.Exists())
		{
			OTLog::vOutput(0, "OTParty::LoadAndVerifyAssetAccounts: Bad: Acct ID is blank for account: %s, on party: %s.\n",
						   str_acct_name.c_str(), GetPartyName().c_str());
			return false;
		}
		// ----------------------
		// Disallow duplicate Acct IDs.
		// (Only can use an acct once inside a smart contract.)
		//
		std::set<std::string>::iterator it_acct_id = theAcctIDSet.find(strAcctID.Get());

		if (theAcctIDSet.end() == it_acct_id) // It's not already there (good).
		{
			theAcctIDSet.insert(strAcctID.Get()); // Save a copy so we can make sure there's no duplicate acct IDs. (Not allowed.)
		}
		else
		{
			OTLog::vOutput(0, "OTParty::LoadAndVerifyAssetAccounts: Failure: Found a duplicate Acct ID (%s), on acct: %s.\n",
						   strAcctID.Get(), str_acct_name.c_str());
			return false;
		}
		// ----------------------
		mapOfAccounts::iterator ii = map_Accts_Already_Loaded.find(strAcctID.Get()); // If it's there, it's mapped by Acct ID, so we can look it up.

		if (map_Accts_Already_Loaded.end() != ii) // Found it.
		{
			pAccount = (*ii).second;
			OT_ASSERT(NULL != pAccount);
			// ---------------
			// Now we KNOW the Account is "already loaded" and we KNOW the partyaccount has a POINTER to that Acct:
			//
			const bool bIsPartyAcct = pPartyAcct->IsAccount(*pAccount);
			if (!bIsPartyAcct)
				OTLog::Error("OTParty::LoadAndVerifyAssetAccounts: Failed call: pPartyAcct->IsAccount(*pAccount); \n");
			OT_ASSERT_MSG(bIsPartyAcct, "OTParty::LoadAndVerifyAssetAccounts: Failed call: pPartyAcct->IsAccount(*pAccount); \n"); // assert because the Acct was already mapped by ID, so it should already have been validated.

			bHadToLoadtheAcctMyself = false; // Whew. The Acct was already loaded. Found it. (And the ptr is now set.)
		}
		// -----------------------------------------------

		// Looks like the Acct wasn't already loaded....
		// Let's load it up...
		//
		if (bHadToLoadtheAcctMyself == true)
		{
			if (NULL == (pAccount = pPartyAcct->LoadAccount(theServerNym, strServerID))) // This calls VerifyAccount(), AND it sets pPartyAcct's internal ptr.
			{
				OTLog::vOutput(0, "OTParty::LoadAndVerifyAssetAccounts: Failed loading Account with name: %s and ID: %s\n",
							  str_acct_name.c_str(), strAcctID.Get());
				return false;
			}
			// Successfully loaded the Acct! We add to this map so it gets cleaned-up properly later.
			map_NewlyLoaded.insert(std::pair<std::string, OTAccount *>(strAcctID.Get(), pAccount));
		}
		// ---------------------------------------
	}

	return true;
}


// After calling this, map_NewlyLoaded will contain pointers to Nyms that MUST BE CLEANED UP.
// This function will not bother loading any Nyms which appear on map_Nyms_Already_Loaded.
//
bool OTParty::LoadAndVerifyAgentNyms(OTPseudonym & theServerNym, mapOfNyms & map_Nyms_Already_Loaded, mapOfNyms & map_NewlyLoaded)
{
	const bool bIsNym = this->IsNym();

	if (!bIsNym) // Owner MUST be a Nym (until I code Entities.)
	{
		OTLog::Error("OTParty::LoadAndVerifyAgents: Entities and roles have not been coded yet. Party owner MUST be a Nym. \n");
		return false;
	}
	if (GetOpeningTransNo() <= 0)	// Opening Trans Number MUST be set for the party! VerifyPartyAuthorization() only verifies it if it's set. Therefore
	{								// if we are verifying the agent Nyms based on the assumption that the authorizing Nym is valid, then we want to make sure
		OTLog::Error("OTParty::LoadAndVerifyAgents: This party doesn't have a valid opening transaction number. Sorry. \n"); // the Opening Num is being checked for that Nym. (And if it's above 0, then it IS being checked.)
		return false;
	}
	// ----------------------------------
	bool bGotPartyNymID=false;
	const std::string str_owner_id = this->GetNymID(&bGotPartyNymID); // str_owner_id  is the NymID of the party OWNER.
	OT_ASSERT(bGotPartyNymID);
	// ----------------------------------
	const OTString strServerNymID(theServerNym);

	FOR_EACH_IT(mapOfAgents, m_mapAgents, it_agent)	// Until entities are coded, there can only be one agent, who has the same ID as the owner (Nym representing himself)
	{
		OTAgent * pAgent = (*it_agent).second;
		OT_ASSERT_MSG(NULL != pAgent, "Unexpected NULL agent pointer in party map.");
		// -------------------------------------

		if (!pAgent->IsAnIndividual() || ! pAgent->DoesRepresentHimself())
		{
			OTLog::Error("OTParty::LoadAndVerifyAgents: Entities and roles have not been coded yet. "
						 "Agent needs to be an individual who represents himself, and Party owner needs to be the same Nym.\n");
			return false;
		}
		// ----------------------
		OTIdentifier theNymID;
		bool bGotAgentNymID = pAgent->GetNymID(theNymID);
		const OTString strNymID(theNymID);
		const std::string str_agent_id = bGotAgentNymID ? strNymID.Get() : ""; // str_agent_id is the NymID of the AGENT.
		OT_ASSERT(bGotAgentNymID);
		// ---------

		// COMPARE THE IDS...... Since the Nym for this agent is representing himself (he is also owner)
		// therefore they should have the same NymID.

		if ( !(str_agent_id.compare(str_owner_id) == 0) ) // If they don't match. (Until I code entities, a party can only be a Nym representing himself as an agent.)
		{
			OTLog::vError("OTParty::LoadAndVerifyAgents: Nym supposedly represents himself (owner AND agent) yet "
                          "they have different Nym IDs:  %s / %s.\n", str_owner_id.c_str(), str_agent_id.c_str());
			return false;
		}
		// ---------------------------------
		// Server Nym is not allowed as a party (at this time :-)
		if ( str_agent_id.compare(strServerNymID.Get()) == 0 ) // If they DO match.
		{
			OTLog::Error("OTParty::LoadAndVerifyAgents: Server Nym is not allowed to serve as an agent for smart contracts. Sorry.\n");
			return false;
		}
		// ----------------------
		// BY THIS POINT we know that the Party is a Nym, the Agent is an individual representing himself, and
		// we know that they have the SAME NYM ID.
		//
		// Next step: See if the Nym is already loaded and if not, load him up.

		bool bHadToLoadtheNymMyself = true;
		OTPseudonym * pNym = NULL;

		mapOfNyms::iterator ii = map_Nyms_Already_Loaded.find(str_agent_id); // If it's there, it's mapped by Nym ID, so we can look it up.

		if (map_Nyms_Already_Loaded.end() != ii) // Found it.
		{
			pNym = (*ii).second;
			OT_ASSERT(NULL != pNym);
			// ---------------
			// Now we KNOW the Nym is "already loaded" and we KNOW the agent has a POINTER to that Nym:
			//
			OT_ASSERT(pAgent->IsValidSigner( *pNym )); // assert because the Nym was already mapped by ID, so it should already have been validated.

			bHadToLoadtheNymMyself = false; // Whew. He was already loaded. Found him.
		}
		// -----------------------------------------------

		// Looks like the Nym wasn't already loaded....
		// Let's load him up
		//
		if (bHadToLoadtheNymMyself)
		{
			if (NULL == (pNym = pAgent->LoadNym(theServerNym)))
			{
				OTLog::vError("OTParty::LoadAndVerifyAgents: Failed loading Nym with ID: %s\n", str_agent_id.c_str());
				return false;
			}
			// Successfully loaded the Nym! We add to this map so it gets cleaned-up properly later.
			map_NewlyLoaded.insert(std::pair<std::string, OTPseudonym *>(str_agent_id, pNym)); // I use str_agent_id here because it contains the right NymID.
		}
		// -----------------------------------------------
		// BY THIS POINT, we know the Nym is available for use, whether I had to load it myself first or not.
		// We also know that if I DID have to load it myself, the pointer was saved in map_NewlyLoaded for cleanup later.
		//
		// Until entities are coded, by this point we also KNOW that
		// the agent's NymID and the Party (owner)'s NymID are identical.
		//
		// Before this function was even called, we knew that OTScriptable::VerifyPartyAuthorization() was already called
		// on all the parties, and we know that every party's signed copy was verified against the signature of its authorizing
		// agent, and that the Opening trans# for that party is currently signed out to THAT AGENT.
		//
		// If the NymIDs are identical between agent and owner, and the owner's authorizing agent (that same nym) has SIGNED
		// its party's copy, and the Opening Trans# is signed out to that agent, then we have basically verified that agent.
		// Right?
		//
		// WHAT if one of the Nyms loaded by this agent was NOT the same Nym as the owner? In that case, it would have to be
		// a Nym working for an entity in a role, and I haven't coded entities yet, so I just disallow that case entirely
		//
		// By this point, the call to LoadNym also did a LoadSignedNymFile() and a call to VerifyPseudonym().
		//
		// FINALLY, the calls to pAgent->IsValidSigner( *pNym ) or pAgent->LoadNym(theServerNym) (whichever occurred -- one or the other)
		// have now insured by this point that pAgent continues to have an INTERNAL POINTER to pNym...
	}

	return true;
}


// This is only meant to be used in OTSmartContract::VerifySmartContract() RIGHT AFTER the call
// to VerifyPartyAuthorization(). It ASSUMES the nyms and asset accounts are all loaded up, with
// internal pointers to them available.
//
bool OTParty::VerifyAccountsWithTheirAgents(OTPseudonym		& theSignerNym,
											const OTString	& strServerID,
											const bool		  bBurnTransNo/*=false*/)
{
	OT_ASSERT(NULL != m_pOwnerAgreement);

	bool bAllSuccessful = true;

	// By this time this function is called, ALL the Nyms and Asset Accounts should ALREADY
	// be loaded up in memory!
	//
	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		const std::string str_acct_name = (*it).first;
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL != pAcct, "Unexpected NULL partyaccount pointer in party map.");
		// -------------------------------------
		const bool bVerified = m_pOwnerAgreement->VerifyPartyAcctAuthorization(*pAcct,			// The party is assumed to have been verified already via VerifyPartyAuthorization()
																			   theSignerNym,	// For verifying signature on the authorizing Nym and for accts as well.
																			   strServerID,		// For verifying issued num, need the serverID the # goes with.
																			   bBurnTransNo);	// bBurnTransNo=false ) // In OTServer::VerifySmartContract(), it not only wants to verify the closing # is properly issued, but it additionally wants to see that it hasn't been USED yet -- AND it wants to burn it, so it can't be used again!  This bool allows you to tell the function whether or not to do that.
		if (false == bVerified)		// This mechanism is here because we still want to let them ALL verify, before returning false.
		{
			bAllSuccessful = false;	// That is, we don't want to return at the first failure, but let them all go through. (This is in order to keep the output consistent.)
			OTLog::vOutput(0, "OTParty::%s: Ownership, agency, or potentially "
						   "closing transaction # failed to verify on account: %s \n",
                           __FUNCTION__, str_acct_name.c_str());
		}
	}
	// -------------

	return bAllSuccessful;
}


// Done
// The party will use its authorizing agent.
//
bool OTParty::SignContract(OTContract & theInput)
{
	if (GetAuthorizingAgentName().size() <= 0)
	{
		OTLog::vError("OTParty::%s: Error: Authorizing agent name is blank.\n", __FUNCTION__);
		return false;
	}
	// ---------------------------------------------
	OTAgent * pAgent = GetAgent(GetAuthorizingAgentName());

	if (NULL == pAgent)
	{
		OTLog::vError("OTParty::%s: Error: Unable to find Authorizing agent (%s) for party: %s.\n",
					  __FUNCTION__, GetAuthorizingAgentName().c_str(), GetPartyName().c_str());
		return false;
	}

	return pAgent->SignContract(theInput);
}


// done
// for whichever partyaccounts have agents that happen to be loaded, this will harvest the closing trans#s.
// Calls OTAgent::HarvestTransactionNumber
//
void OTParty::HarvestClosingNumbers(const OTString & strServerID, bool bSave/*=false*/, OTPseudonym * pSignerNym/*=NULL*/)
{
    // ------------------------------------------------
	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL != pAcct, "OTParty::HarvestClosingNumbers: Unexpected NULL partyaccount pointer in party map.");
		// -------------------------------------
		if (pAcct->GetClosingTransNo() <= 0)
			continue; // No log, for now.
		// -------------------------------------
		const std::string str_agent_name(pAcct->GetAgentName().Get());
		if (str_agent_name.size() <= 0)
		{
			OTLog::vError("%s: Missing agent name on party account: %s \n",
						 __FUNCTION__, pAcct->GetName().Get());
			continue;
		}
		// ----------------------------------
		OTAgent * pAgent = this->GetAgent(str_agent_name);
		if (NULL == pAgent)
			OTLog::vError("%s: Couldn't find agent (%s) for asset account: %s\n",
						  __FUNCTION__, str_agent_name.c_str(), pAcct->GetName().Get());
		else
			pAgent->HarvestTransactionNumber(pAcct->GetClosingTransNo(),
                                             strServerID,
                                             bSave,
                                             pSignerNym);   // server passes in serverNym here, otherwise each agent uses its own nym.
	} // FOR_EACH
}


//Done
// Calls OTAgent::HarvestTransactionNumber
//
void OTParty::HarvestClosingNumbers(OTAgent & theAgent, const OTString & strServerID)
{
	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT_MSG(NULL != pAcct, "OTParty::HarvestClosingNumbers: Unexpected NULL partyaccount pointer in partyaccount map.");
		// -------------------------------------
		if (pAcct->GetClosingTransNo() <= 0)
			continue; // No log, for now.
		// -------------------------------------
		const std::string str_agent_name (pAcct->GetAgentName().Get());
		if (str_agent_name.size() <= 0)
		{
//			OTLog::vError("OTParty::%s: Missing agent name on party account: %s \n",
//						  __FUNCTION__, pAcct->GetName().Get());
			continue;
		}
		// ----------------------------------
		if (theAgent.GetName().Compare(str_agent_name.c_str()))
			theAgent.HarvestTransactionNumber(pAcct->GetClosingTransNo(), strServerID);
			// We don't break here, on success, because this agent might represent multiple accounts.
		// else nothing...
	} // FOR_EACH
}


// Done.
// IF theNym is one of my agents, then grab his numbers back for him.
// If he is NOT one of my agents, then do nothing.
//
void OTParty::HarvestClosingNumbers(OTPseudonym & theNym, const OTString & strServerID)
{
	OTAgent * pAgent = NULL;

	if (HasAgent(theNym, &pAgent))
	{
		OT_ASSERT(NULL != pAgent);
		HarvestClosingNumbers(*pAgent, strServerID);
	}
	// else nothing...
}


// Done
// IF theNym is one of my agents, then grab his opening number back for him.
// If he is NOT one of my agents, then do nothing.
//
void OTParty::HarvestOpeningNumber(OTPseudonym & theNym, const OTString & strServerID)
{
	OTAgent * pAgent = NULL;

	if (HasAuthorizingAgent(theNym, &pAgent))
	{
		OT_ASSERT(NULL != pAgent);
		HarvestOpeningNumber(*pAgent, strServerID);
	}
	// else no error, since many nyms could get passed in here (in a loop)
} // The function above me, calls the one below.


// Done
// Calls OTAgent::HarvestTransactionNumber
//
void OTParty::HarvestOpeningNumber(OTAgent & theAgent, const OTString & strServerID)
{
	if ( ! (GetAuthorizingAgentName().compare(theAgent.GetName().Get()) == 0))
		OTLog::vError("OTParty::%s: Error: Agent name doesn't match:  %s / %s  \n",
                      __FUNCTION__, GetAuthorizingAgentName().c_str(), theAgent.GetName().Get());
	else if (GetOpeningTransNo() > 0)
		theAgent.HarvestTransactionNumber(GetOpeningTransNo(), strServerID); // bSave=false, pSignerNym=NULL
	else
		OTLog::vOutput(0, "OTParty::%s: Nothing to harvest, it was already 0 for party: %s\n",
                       __FUNCTION__, GetPartyName().c_str());
}


// Done.
// The function below me, calls the one above.
void OTParty::HarvestOpeningNumber(const OTString & strServerID)
{
	if (GetAuthorizingAgentName().size() <= 0)
	{
		OTLog::vError("OTParty::%s: Error: Authorizing agent name is blank.\n", __FUNCTION__);
		return;
	}
	// ---------------------------------------------
	OTAgent * pAgent = GetAgent(GetAuthorizingAgentName());
	if (NULL == pAgent)
		OTLog::vError("OTParty::%s: Error: Unable to find Authorizing agent (%s) for party: %s.\n",
					 __FUNCTION__, GetAuthorizingAgentName().c_str(), GetPartyName().c_str());
	else
		HarvestOpeningNumber(*pAgent, strServerID);
}


// Done
void OTParty::HarvestAllTransactionNumbers(const OTString & strServerID)
{
	HarvestOpeningNumber (strServerID);
	HarvestClosingNumbers(strServerID);
}


// Calls OTAgent::RemoveIssuedNumber (above)
//
void OTParty::CloseoutOpeningNumber(const OTString & strServerID, bool bSave/*=false*/,
                                    OTPseudonym * pSignerNym/*=NULL*/)
{
	if (GetAuthorizingAgentName().size() <= 0)
	{
		OTLog::vError("OTParty::%s: Error: Authorizing agent name is blank.\n", __FUNCTION__);
		return;
	}
	// ---------------------------------------------
	OTAgent * pAgent = GetAgent(GetAuthorizingAgentName());
	if (NULL == pAgent)
		OTLog::vError("OTParty::%s: Error: Unable to find Authorizing agent (%s) for party: %s.\n",
                      __FUNCTION__, GetAuthorizingAgentName().c_str(), GetPartyName().c_str());
	else if (GetOpeningTransNo() > 0)
        pAgent->RemoveIssuedNumber(GetOpeningTransNo(), strServerID, bSave, pSignerNym);
    else
		OTLog::vOutput(0, "OTParty::%s: Nothing to closeout, it was already 0 for party: %s\n",
                       __FUNCTION__, GetPartyName().c_str());
}


// Done
// This function ASSUMES that the internal Nym pointer (on the authorizing agent) is set,
// and also that the Nym pointer is set on the authorized agent for each asset account as well.
//
// The party is getting ready to CONFIRM the smartcontract, so he will have to provide
// the appropriate transaction #s to do so.  This is the function where he tries to reserve
// those. Client-side.
//
bool OTParty::ReserveTransNumsForConfirm(const OTString & strServerID)
{
	// -----------------------------------------------
	// RESERVE THE OPENING TRANSACTION NUMBER, LOCATED ON THE AUTHORIZING AGENT FOR THIS PARTY.

	if (GetAuthorizingAgentName().size() <= 0)
	{
		OTLog::vOutput(0, "OTParty::ReserveTransNumsForConfirm: Failure: Authorizing agent's name is empty on this party: %s \n",
					   GetPartyName().c_str());
		return false;
	}
    // -----------------------------------------------
	OTAgent * pMainAgent = GetAgent(GetAuthorizingAgentName());

	if (NULL == pMainAgent)
	{
		OTLog::vOutput(0, "OTParty::ReserveTransNumsForConfirm: Failure: Authorizing agent (%s) not found on this party: %s \n",
					   GetAuthorizingAgentName().c_str(), GetPartyName().c_str());
		return false;
	}
	// ----------------------------------------------
	if (false == pMainAgent->ReserveOpeningTransNum(strServerID))  // <==============================
	{
		OTLog::vOutput(0, "OTParty::ReserveTransNumsForConfirm: Failure: Authorizing agent (%s) didn't have an opening transaction #, on party: %s \n",
					   GetAuthorizingAgentName().c_str(), GetPartyName().c_str());
		return false;
	}
	// BELOW THIS POINT, the OPENING trans# has been RESERVED and
	// must be RETRIEVED in the event of failure, using this call:
	// this->HarvestAllTransactionNumbers(strServerID);

	// ****************************************************
	//
	// RESERVE THE CLOSING TRANSACTION NUMBER for each asset account, LOCATED ON ITS AUTHORIZED AGENT.
	// (Do this for each account on this party.)
	//
	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pPartyAccount = (*it).second;
		OT_ASSERT(NULL != pPartyAccount);
		// -------------------------------

		if (!pPartyAccount->GetAgentName().Exists())
		{
			OTLog::vOutput(0, "OTParty::ReserveTransNumsForConfirm: Failure: Authorized agent name is blank for account: %s \n",
						 pPartyAccount->GetName().Get());
			HarvestAllTransactionNumbers(strServerID);  // We have to put them back before returning, since this function has failed.
			return false;
		}
		// -----------------------------------
		OTAgent * pAgent = GetAgent(pPartyAccount->GetAgentName().Get());

		if (NULL == pAgent)
		{
			OTLog::vOutput(0, "OTParty::ReserveTransNumsForConfirm: Failure: Unable to locate Authorized agent for account: %s \n",
						   pPartyAccount->GetName().Get());
			HarvestAllTransactionNumbers(strServerID);  // We have to put them back before returning, since this function has failed.
			return false;
		}
		// Below this point, pAgent is good.
		// -----------------------------------

		if (false == pAgent->ReserveClosingTransNum(strServerID, *pPartyAccount)) // <==============================
		{
			OTLog::vOutput(0, "OTParty::ReserveTransNumsForConfirm: Failure: Authorizing agent (%s) didn't have a closing transaction #, on party: %s \n",
						   GetAuthorizingAgentName().c_str(), GetPartyName().c_str());
			HarvestAllTransactionNumbers(strServerID);  // We have to put them back before returning, since this function has failed.
			return false;
		}
		// BELOW THIS POINT, the CLOSING TRANSACTION # has been reserved for this account,
		// and MUST BE RETRIEVED in the event of failure.
		// ----------------------------------
	} // FOR_EACH

	// ----------------------------------------------------
	// BY THIS POINT, we have successfully reserved the Opening Transaction # for the party (from its
	// authorizing agent) and we have also successfully reserved Closing Transaction #s for EACH ASSET
	// ACCOUNT, from the authorized agent for each asset account.
	// Therefore we have reserved ALL the needed transaction #s, so let's return true.

	return true;
}


void OTParty::Serialize(OTString & strAppend,
						bool bCalculatingID/*=false*/,
						bool bSpecifyAssetID/*=false*/,
						bool bSpecifyParties/*=false*/)
{
	strAppend.Concatenate("<party\n name=\"%s\"\n"
						  " ownerType=\"%s\"\n" // "nym" or "entity"
						  " ownerID=\"%s\"\n"  // Entity or Nym ID.  Perhaps should just have both...
						  " openingTransNo=\"%lld\"\n"  // fine here.
						  " signedCopyProvided=\"%s\"\n" // true/false
						  " authorizingAgent=\"%s\"\n" // When an agent activates this contract, it's HIS opening trans#.
						  " numAgents=\"%d\"\n" // integer count.
						  " numAccounts=\"%d\" >\n\n", // integer count.
						  GetPartyName().c_str(),
						  bCalculatingID ? "" : (m_bPartyIsNym ? "nym" : "entity"),
						  (bCalculatingID &&
						  !bSpecifyParties) ? "" : m_str_owner_id.c_str(),
						  bCalculatingID ? 0 : m_lOpeningTransNo,
						  (!bCalculatingID && m_strMySignedCopy.Exists()) ? "true" : "false",
						  bCalculatingID ? "" : m_str_authorizing_agent.c_str(),
						  bCalculatingID ? 0 : m_mapAgents.size(),
						  m_mapPartyAccounts.size());
	// -----------------
	if (!bCalculatingID)
	{
		FOR_EACH(mapOfAgents, m_mapAgents)
		{
			OTAgent * pAgent = (*it).second;
			OT_ASSERT(NULL != pAgent);
			pAgent->Serialize(strAppend);
		}
	}
	// -----------------
	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		OTPartyAccount * pAcct = (*it).second;
		OT_ASSERT(NULL != pAcct);
		pAcct->Serialize(strAppend, bCalculatingID, bSpecifyAssetID);
	}
	// -----------------
	if (!bCalculatingID && m_strMySignedCopy.Exists())
	{
		OTASCIIArmor ascTemp(m_strMySignedCopy);
		strAppend.Concatenate("<mySignedCopy>\n%s</mySignedCopy>\n\n", ascTemp.Get());
	}
	// -----------------
	strAppend.Concatenate("</party>\n\n");
}


// Register the variables of a specific Bylaw into the Script interpreter,
// so we can execute a script.
//
void OTParty::RegisterAccountsForExecution(OTScript& theScript)
{
	FOR_EACH(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		const std::string str_acct_name	= (*it).first;
		OTPartyAccount * pAccount		= (*it).second;
		OT_ASSERT((NULL != pAccount) && (str_acct_name.size() > 0));
		// -----------------------
		pAccount->RegisterForExecution(theScript);
	}
}


// Done.
bool OTParty::Compare(const OTParty & rhs) const
{
	const std::string str_party_name(rhs.GetPartyName());

	if (!(str_party_name.compare(GetPartyName()) == 0))
	{
		OTLog::vOutput(0, "OTParty::Compare: Names don't match.  %s  /  %s \n",
					   GetPartyName().c_str(), str_party_name.c_str());
		return false;
	}

	// The party might first be added WITHOUT filling out the Nym/Agent info.
	// As long as the party's name is right, and the accounts are all there with the
	// correct asset type IDs, then it should matter if LATER, when the party CONFIRMS
	// the agreement, he supplies himself as an entity or a Nym, or whether he supplies this
	// agent or that agent.  That information is important and is stored, but is not relevant
	// for a Compare().
//	if (IsNym() != rhs.IsNym())
//	{
//		OTLog::vOutput(0, "OTParty::Compare: One of these parties is a Nym and the other is not:  %s  /  %s \n",
//					   GetPartyName().c_str(), str_party_name.c_str());
//		return false;
//	}

	if ((this->GetOpeningTransNo() > 0) &&
		(rhs.GetOpeningTransNo() > 0) &&
		(this->GetOpeningTransNo() != rhs.GetOpeningTransNo())
	   )
	{
		OTLog::vOutput(0, "OTParty::Compare: Opening transaction numbers don't match for party %s. ( %lld  /  %lld ) \n",
					   GetPartyName().c_str(), this->GetOpeningTransNo(), rhs.GetOpeningTransNo());
		return false;
	}
	// ---------------------------------------------------
	if (
		(this->GetPartyID().size() > 0) &&
		(rhs.  GetPartyID().size() > 0) &&
		!(this->GetPartyID().compare(rhs.GetPartyID()) == 0)
		)
	{
		OTLog::vOutput(0, "OTParty::Compare: Party IDs don't match for party %s. ( %s  /  %s ) \n",
					   GetPartyName().c_str(), this->GetPartyID().c_str(), rhs.GetPartyID().c_str());
		return false;
	}
	// ----------------------------------------------------
	if (
		(this->GetAuthorizingAgentName().size() > 0) &&
		(rhs.  GetAuthorizingAgentName().size() > 0) &&
		!(this->GetAuthorizingAgentName().compare(rhs.GetAuthorizingAgentName()) == 0)
		)
	{
		OTLog::vOutput(0, "OTParty::Compare: Authorizing agent names don't match for party %s. ( %s  /  %s ) \n",
					   GetPartyName().c_str(), this->GetAuthorizingAgentName().c_str(),
					   rhs.GetAuthorizingAgentName().c_str());
		return false;
	}
	// ----------------------------------------------------
	//
	// No need to compare agents... right?
	//
//	mapOfAgents			m_mapAgents; // These are owned.

	if (this->GetAccountCount() != rhs.GetAccountCount())
	{
		OTLog::vOutput(0, "OTParty::Compare: Mismatched number of accounts when comparing party %s. \n",
					   GetPartyName().c_str());
		return false;
	}

	FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		const std::string str_acct_name	= (*it).first;
		OTPartyAccount * pAcct			= (*it).second;
		OT_ASSERT(NULL != pAcct);
		// ----------------------------------

		OTPartyAccount *p2 = rhs.GetAccount(str_acct_name);

		if (NULL == p2)
		{
			OTLog::vOutput(0, "OTParty::Compare: Unable to find Account %s on rhs, when comparing party %s. \n",
						   str_acct_name.c_str(), GetPartyName().c_str());
			return false;
		}
		if (!pAcct->Compare(*p2))
		{
			OTLog::vOutput(0, "OTParty::Compare: Accounts (%s) don't match when comparing party %s. \n",
						   str_acct_name.c_str(), GetPartyName().c_str());
			return false;
		}
	}
	// -----------------------------------

	return true;
}


// When confirming a party, a new version replaces the original. This is part of that process.
// *this is the old one, and theParty is the new one.
//
bool OTParty::CopyAcctsToConfirmingParty(OTParty & theParty) const
{
	theParty.CleanupAccounts(); // (We're going to copy our own accounts into theParty.)

	FOR_EACH_CONST(mapOfPartyAccounts, m_mapPartyAccounts)
	{
		const std::string str_acct_name	= (*it).first;
		OTPartyAccount * pAcct			= (*it).second;
		OT_ASSERT(NULL != pAcct);
		// ----------------------------------

		if (false == theParty.AddAccount(pAcct->GetAgentName(),	pAcct->GetName(),
										 pAcct->GetAcctID(),	pAcct->GetAssetTypeID(),
										 pAcct->GetClosingTransNo()))
		{
			OTLog::vOutput(0, "OTParty::CopyAcctsToConfirmingParty: Unable to add Account %s, when copying from *this party %s. \n",
						   str_acct_name.c_str(), GetPartyName().c_str());
			return false;
		}
	}
	// -----------------------------------

	return true;
}
