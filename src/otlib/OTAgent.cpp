/************************************************************
 *
 *  OTAgent.cpp
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

#include "OTAgent.hpp"

#include "OTAgreement.hpp"
#include "OTLog.hpp"
#include "OTParty.hpp"
#include "OTPartyAccount.hpp"
#include "OTPseudonym.hpp"
#include "OTSmartContract.hpp"


// Have the agent try to verify his own signature against any contract.
//
// NOTE: This function assumes that you have already taken actions that would have loaded the Nym's pointer
// and placed it within this Agent. This is a low-level call and it expects that you have already been using
// calls such as HasAgent(), HasAuthorizingAgent(), LoadAuthorizingAgent(), etc.
// This function also assumes that once you are done, you will call ClearTemporaryPointers().
//
bool OTAgent::VerifySignature(OTContract & theContract)
{
	// Only individual agents can sign for things, not groups (groups vote, they don't sign.)
	// Thus, an individual can verify a signature, whereas a voting group would verify an election result (or whatever.)
	//
	if (!IsAnIndividual() || !DoesRepresentHimself())
	{
		OTLog::vError("OTAgent::VerifySignature: Entities and roles are not yet supported. Agent: %s.\n",
					  m_strName.Get());
		return false;
	}// todo: when adding entities, this will change.

//	if (DoesRepresentAnEntity)
//	{
//		// The original version of a smartcontract might show that Frank, the Sales Director, signed it.
//		// Years later, Frank is fired, and Jim is appointed to his former Role of sales director, in the same entity.
//		// The original copy of the smart contract still contains Frank's signature, and thus we still need to load Frank
//		// in order to verify that original signature.  That's why we load Frank by the NymID stored there. He was the Nym
//		// at the time, so that's the key we load.
//		//
//		// NEXT: What if JIM tries to verify the signature on the contract, even though FRANK was the original signer?
//		// Should OTAgent be smart enough here to substitute Frank whenever Jim tries to verify? I argue no: this function is
//		// too low-level. Plus it's backwards. If Jim tries to DO an action, THEN OT should be smart enough to verify that Jim
//		// is in the proper Role and that Jim's signature is good enough to authorize actions. But if OT is verifying Frank's
//		// signature on some old copy of something that Frank formerly signed, then this function should clearly tell me if Frank's
//		// sig verified... or not.
//		//
//		// Therefore the "DoesRepresentAnEntity()" option is useless here, since we are verifying the same Nym's signature whether
//		// he represents an entity or not.
//		//
//	}
//	else
	if (NULL == m_pNym)
	{
		OTString strTemp(theContract);
		OTLog::vError("OTAgent::VerifySignature: Attempted to verify signature on contract, "
					 "but no Nym had ever been loaded for this agent:\n\n%s\n\n",
					 strTemp.Get());
		return false;
	}

	return theContract.VerifySignature(*m_pNym);
}


// Low-level.
// Caller is responsible to delete.
// Don't call this unless you're sure the same Nym isn't already loaded, or unless
// you are prepared to compare the returned Nym with all the Nyms you already have loaded.
//
// This call may always fail for a specific agent, if the agent isn't a Nym
// (the agent could be a voting group.)
//
OTPseudonym * OTAgent::LoadNym(OTPseudonym & theServerNym)
{
	OTIdentifier theAgentNymID;
	bool bNymID = this->GetNymID(theAgentNymID);

	if (bNymID)
	{
		OTPseudonym * pNym = new OTPseudonym;
		OT_ASSERT(NULL != pNym);

		pNym->SetIdentifier(theAgentNymID);

		if (false == pNym->LoadPublicKey())
		{
			OTString strNymID(theAgentNymID);
			OTLog::vError("OTAgent::LoadNym: Failure loading "
						  "agent's public key:\n%s\n", strNymID.Get());
			delete pNym; pNym=NULL;
		}
		else if (pNym->VerifyPseudonym() &&
				 pNym->LoadSignedNymfile(theServerNym))
		{
			this->SetNymPointer(*pNym); // set this pointer in case I need it for later.
										// also remember, caller is responsible to delete, so there's no guarantee the pointer
			return pNym;				// is any good.  Then again, caller is also responsible to call ClearTemporaryPointers().
		}
		else
		{
			OTString strNymID(theAgentNymID);
			OTLog::vError("OTAgent::LoadNym: Failure verifying agent's public key or loading signed nymfile: %s\n",
						  strNymID.Get());
			delete pNym; pNym=NULL;
		}
	}
	else
		OTLog::Error("OTAgent::LoadNym: Failure. Are you sure this agent IS a Nym at all? \n");

	return NULL;
}


OTAgent::OTAgent() : m_bNymRepresentsSelf(false), m_bIsAnIndividual(false), m_pNym(NULL), m_pForParty(NULL)
{

}


OTAgent::OTAgent(bool bNymRepresentsSelf, bool bIsAnIndividual,
				 const OTString& strName,
				 const OTString& strNymID,
				 const OTString& strRoleID,
				 const OTString& strGroupName)
: m_bNymRepresentsSelf(bNymRepresentsSelf), m_bIsAnIndividual(bIsAnIndividual), m_pNym(NULL), m_pForParty(NULL),
  m_strName(strName), m_strNymID(strNymID), m_strRoleID(strRoleID), m_strGroupName(strGroupName)
{

}


OTAgent::OTAgent(const std::string str_agent_name, OTPseudonym & theNym,
				 bool bNymRepresentsSelf/*=true*/)
		/*IF false, then: ROLE parameter goes here.*/
: m_bNymRepresentsSelf(bNymRepresentsSelf), m_bIsAnIndividual(true), m_pNym(&theNym), m_pForParty(NULL),
  m_strName(str_agent_name.c_str())
{
	// Grab m_strNymID
	OTIdentifier theNymID;
	theNym.GetIdentifier(theNymID);
	theNymID.GetString(m_strNymID);

	//

	if (false == bNymRepresentsSelf)
	{
		// Todo: if the Nym represents an Entity, then RoleID should
		// be passed in, and set here.  I WILL PROBABLY make that part into a SEPARATE CONSTRUCTOR.
		// (Once I get around to adding Entities.)
		//
		OTLog::Error("OTAgent::OTAgent: THIS HASN'T BEEN WRITTEN YET!!\n");
	}
}


void OTAgent::SetParty(OTParty & theOwnerParty) // This happens when the agent is added to the party.
{
	m_pForParty = &theOwnerParty;

	// A Nym can only act as agent for himself or for an entity
	// (never for another Nym. Start an entity if you want that.)
	// If the owner party is a Nym, therefore this agent IS the Nym acting for himself.
	// Whereas if the owner party were an entity, then this agent could be a Nym or a voting group.
	// Since inside this block the owner party IS a Nym, not an entity, then the agent can therefore
	// only be THAT Nym, acting as an agent for himself. Remember, a Nym cannot act as agent for
	// another Nym. That is only possible by an agreement between them, and that agreement becomes
	// the entity (therefore it's only possible using an entity.)
	//
	if (theOwnerParty.IsNym()) // Thus, this basically means the agent IS the party.
	{
		m_bNymRepresentsSelf	= true;
		m_bIsAnIndividual		= true;

		bool bGetOwnerNymID = false;
		const std::string str_owner_nym_id = theOwnerParty.GetNymID(&bGetOwnerNymID);
		m_strNymID.Set(bGetOwnerNymID ? str_owner_nym_id.c_str() : "");

		// Todo here, instead of copying the Owner's Nym ID like above, just make sure they match.
		// Similarly, make sure that the RoleID or GroupName, whichever is relevant, is validated for the owner.
	}
}


OTAgent::~OTAgent()
{
	m_pNym      = NULL;  // this pointer is not owned by this object, and is here for convenience only.
	m_pForParty = NULL;  // The agent probably has a pointer to the party it acts on behalf of.

}


// If the agent is a Nym acting for himself, this will be true. Otherwise, if agent is a Nym acting in a role for an entity, or if agent is a voting group acting for the entity to which it belongs, either way, this will be false.

bool OTAgent::DoesRepresentHimself() const
{

    return m_bNymRepresentsSelf;
}


// Whether the agent is a voting group acting for an entity, or is a Nym acting in a Role for an entity, this will be true either way. (Otherwise, if agent is a Nym acting for himself, then this will be false.)

bool OTAgent::DoesRepresentAnEntity() const
{
    return !m_bNymRepresentsSelf;
}


// Only one of these can be true:
//
// - Agent is either a Nym acting for himself or some entity,
// - or agent is a group acting for some entity.

// Agent is an individual Nym. (Meaning either he IS ALSO the party and thus represents himself, OR he is an agent for an entity who is the party, and he's acting in a role for that entity.) If agent were a group, this would be false.

bool OTAgent::IsAnIndividual() const
{
	return m_bIsAnIndividual;
}


// OR: Agent is a voting group, which cannot take proactive or instant action, but only passive and delayed. Entity-ONLY. (A voting group cannot decide on behalf of individual, but only on behalf of the entity it belongs to.)

bool OTAgent::IsAGroup() const
{
    return !m_bIsAnIndividual;
}


// A Nym cannot act as "agent" for another Nym.
// Nor can a Group act as "agent" for a Nym. Why not? Because:
//
// An entity is COMPOSED of its voting groups and its employee Nyms.
// These don't merely act "on behalf" of the entity, but in fact they comprise the entity.
// Therefore the entity can use voting groups and employee Nyms to make decisions BECAUSE
// IT **HAS** voting groups and employee nyms that it can use.
//
// Whereas an individual Nym is NOT composed of voting groups or employee Nyms. So how could
// he designate to act "on his behalf" something that does not even exist?
// So we must ask, how can another Nym, then, be appointed to act as my agent without some
// agreement designating him as such? And that agreement is the entity itself, which is nothing
// more than an agreement between several owners to designate agents to operate according to their
// interests.

// To directly appoint one Nym to act on behalf of another, yet WITHOUT any agreement in place,
// is to behave as one is the same as the other. But still, who has the key? If both have absolutely
// access and rights to the same key, then why not just both keep a copy of it? In which case now
// it really IS only one Nym in reality, as well as in the software.
// But if one prefers to have his private key, and another his, then they will begin as separate and
// independent individuals. One Nym will not be found within the other as a int64_t-lost, under-developed
// twin!
// Just as reality enforces separate individuals, so does the software end up in the situation where
// two separate Nyms now wish to act with one as agent for the other. This wish is perfectly valid and
// can be accommodated, but logically the software cannot provide the same ONENESS of ACTUALLY SHARING
// THE PRIVATE KEY IN REAL LIFE (which allows the software to ACTUALLY only deal with a single key),
// as opposed to the oneness of "we have separate keys but we want to act in this way". There is oneness,
// and then there is oneness. OT is about contracts between Nyms, and therefore that is the mechanism
// for implementing ANY OTHER FORM OF AGENCY. Whether that agent is your "best man" or a board of voters,
// and whether the agent acts on behalf of you, or some corporation or democracy, either way, either his
// key is the same bits as your key, or they are separate keys in which case there is an agreement
// between them. Otherwise OT simply does not know which agents have authority--and which do not. This
// knowledge is necessary just for being able to function, and is imposed by the natural law.

// IDEA: Have a factory for smart contracts, such that not only are different subclasses instantiated,
// but more usefully, common configurations such as new democracy, new corporation, new board-with-veto, etc.
//

// For when the agent is an individual:
//

// If IsIndividual(), then this is his own personal NymID,
// (whether he DoesRepresentHimself() or DoesRepresentAnEntity() -- either way).
// Otherwise if IsGroup(), this returns false.
//
bool OTAgent::GetNymID(OTIdentifier& theOutput) const
{
    if (IsAnIndividual())
    {
		theOutput.SetString(m_strNymID);

        return true;
    }

    return false;
}


// IF IsIndividual() AND DoesRepresentAnEntity(), then this is his RoleID within that Entity. Otherwise, if IsGroup() or DoesRepresentHimself(), then this returns false.

bool OTAgent::GetRoleID(OTIdentifier& theOutput) const
{
    if (IsAnIndividual() && DoesRepresentAnEntity())
    {
		theOutput.SetString(m_strRoleID);

        return true;
    }


    return false;
}


// Notice if the agent is a voting group, then it has no signer. (Instead it will have an election.)
// That is why certain agents are unacceptable in certain scripts. They are PASSIVE.
//
// There is an "active" agent who has a signerID, but there is also a "passive" agent who only has
// a group name, and acts based on notifications and replies in the int64_t-term, versus being immediately
// able to act as part of the operation of a script.
//
// Basically if !IsIndividual(), then GetSignerID() will fail and thus anything needing that,
// as part of the script, would also therefore be impossible.
//
bool OTAgent::GetSignerID(OTIdentifier& theOutput) const
{
    // If IsIndividual() and DoesRepresentAnEntity() then this returns GetRoleID().
    // else if Individual() and DoesRepresentHimself() then this returns GetNymID().
    // else (if IsGroup()) then return false;

    if (IsAnIndividual())
    {
        if (DoesRepresentAnEntity())
        {
            return GetRoleID(theOutput);
        }
        else // DoesRepresentHimself()
        {
            return GetNymID(theOutput);
        }
    }
    // ---------------------------------
    // else IsGroup()... unable to sign directly; must hold votes instead.
    //
    return false;
}


bool OTAgent::IsValidSignerID(const OTIdentifier & theNymID)
{
	OTIdentifier theAgentNymID;
	bool bNymID = this->GetNymID(theAgentNymID);

	// If there's a NymID on this agent, and it matches theNymID...
	//
	if (bNymID && (theNymID == theAgentNymID))
		return true;

	// TODO Entities...
	//
	return false;
}


// See if theNym is a valid signer for this agent.
//
bool OTAgent::IsValidSigner(OTPseudonym & theNym)
{
	OTIdentifier theAgentNymID;
	bool bNymID = this->GetNymID(theAgentNymID);

	// If there's a NymID on this agent, and it matches theNym's ID...
	//
	if (bNymID && theNym.CompareID(theAgentNymID))
	{
		// That means theNym *is* the Nym for this agent!
		// We'll save his pointer, for future reference...
		//
		this->SetNymPointer(theNym);

		return true;
	}

	// TODO Entity: Perhaps the original Nym was fired from his role... another Nym has now
	// taken his place. In which case, the original Nym should be refused as a valid
	// signer, and the new Nym should be allowed to sign in his place!
	//
	// This means if DoesRepresentAnEntity(), then I have to load the Role, and verify
	// the Nym against that Role (which contains the updated status). Since I haven't
	// coded Entities/Roles yet, then I don't have to do this just yet...
	// Might even update the NymID on this agent, for updated copies of the agreement.
	// (Obviously the original can't be changed...)
	//

	return false;
}


// For when the agent DoesRepresentAnEntity():
//
// Whether this agent IsGroup() (meaning he is a voting group that DoesRepresentAnEntity()),
// OR whether this agent is an individual acting in a role for an entity (IsIndividual() && DoesRepresentAnEntity())
// ...EITHER WAY, the agent DoesRepresentAnEntity(), and this function returns the ID of that Entity.
//
// Otherwise, if the agent DoesRepresentHimself(), then this returns false.
// I'm debating making this function private along with DoesRepresentHimself / DoesRepresentAnEntity().
//
bool OTAgent::GetEntityID(OTIdentifier& theOutput) const
{
	// IF represents an entity, then this is its ID. Else fail.
	//
	if (DoesRepresentAnEntity() && (NULL != m_pForParty) && m_pForParty->IsEntity() )
    {
		bool bSuccessEntityID = false;
		std::string str_entity_id = m_pForParty->GetEntityID(&bSuccessEntityID);

		if (bSuccessEntityID && (str_entity_id.size() > 0))
		{
			OTString strEntityID(str_entity_id.c_str());
			theOutput.SetString(strEntityID);

			return true;
		}
    }

    return false;
}


// Returns true/false whether THIS agent is the authorizing agent for his party.
//
bool OTAgent::IsAuthorizingAgentForParty()
{
	if (NULL == m_pForParty)
		return false;

	if (m_strName.Compare(m_pForParty->GetAuthorizingAgentName().c_str()))
		return true;

	return false;
}


// Returns the number of accounts, owned by this agent's party, that this agent
// is the authorized agent FOR.
//
int32_t OTAgent::GetCountAuthorizedAccts()
{
	if (NULL == m_pForParty)
	{
		OTLog::Error("OTAgent::CountAuthorizedAccts: Error: m_pForParty was NULL.\n");
		return 0; // Maybe should log here...
	}
    // -------------------------------------
	return m_pForParty->GetAccountCount(m_strName.Get());
}


// For when the agent is a voting group:
// If !IsGroup() aka IsIndividual(), then this will return false.
//
bool OTAgent::GetGroupName(OTString & strGroupName)
{
	if (IsAGroup())
    {
		strGroupName.Set(m_strGroupName);

        return true;
    }

    return false;
}


//    bool DoesRepresentHimself();
//    bool DoesRepresentAnEntity();
//
//    bool IsIndividual();
//    bool IsGroup();

// PARTY is either a NYM or an ENTITY. This returns ID for that Nym or Entity.
//
bool OTAgent::GetPartyID(OTIdentifier& theOutput) const
{
    // If DoesRepresentHimself() then return GetNymID()
    // else (thus DoesRepresentAnEntity()) so return GetEntityID()
    //

    if (DoesRepresentHimself())
        return GetNymID(theOutput);

    return GetEntityID(theOutput);
}


void OTAgent::RetrieveNymPointer(mapOfNyms & map_Nyms_Already_Loaded)
{
	const std::string str_agent_name(m_strName.Get());

	//  We actually have a Nym pointer on this agent somehow (so let's add it to the list.)
	//
	if (NULL != m_pNym)
	{
		if (!m_strName.Exists())  // Whoaa!! Can't add it without the agent's name for the map!
		{
			OTLog::Error("OTAgent::RetrieveNymPointers: Failed: m_strName is empty!\n");
		}
		else if (map_Nyms_Already_Loaded.end() ==
				 map_Nyms_Already_Loaded.insert(map_Nyms_Already_Loaded.begin(), std::pair<std::string, OTPseudonym *>(str_agent_name, m_pNym)))
			OTLog::vError("OTAgent::RetrieveNymPointer: Failed on insertion, as though another nym were already "
						 "there with the same agent name! (%s)\n", m_strName.Get());
		// (else it was inserted successfully.)
	}
	// else nothing, since it's normal that most of them are NULL, even when one is goood.
}


bool OTAgent::VerifyAgencyOfAccount(const OTAccount & theAccount) const
{
	OTIdentifier theSignerID;

	if (!this->GetSignerID(theSignerID))
	{
		OTLog::Error("OTAgent::VerifyAgencyOfAccount: ERROR: Entities and roles haven't been coded yet.\n");
		return false;
	}
	// --------------------

	return theAccount.VerifyOwnerByID(theSignerID); // todo when entities and roles come, won't this "just work", or do I also have to warn the acct whether it's a Nym or a Role being passed?
}


bool OTAgent::DropFinalReceiptToInbox(mapOfNyms * pNymMap,
									  const OTString & strServerID,
									  OTPseudonym & theServerNym,
									  OTSmartContract & theSmartContract,
									  const OTIdentifier & theAccountID,
									  const int64_t & lNewTransactionNumber,
									  const int64_t & lClosingNumber,
									  const OTString & strOrigCronItem,
									  OTString * pstrNote/*=NULL*/,
									  OTString * pstrAttachment/*=NULL*/)
{
	// TODO: When entites and ROLES are added, this function may change a bit to accommodate them.
    const char * szFunc = "OTAgent::DropFinalReceiptToInbox";

	OTIdentifier theAgentNymID;
	bool bNymID = this->GetNymID(theAgentNymID);

	// Not all agents have Nyms. (Might be a voting group.)
	// But in the case of Inboxes for asset accounts, shouldn't the agent be a Nym?
	// Perhaps not... perhaps not... we shall see.

	if (true == bNymID) // therefore IsAnIndividual() is definitely true.
	{
		OTPseudonym *	pNym		= NULL;
		OTCleanup<OTPseudonym> theNymAngel;

		// -------------------------------------------------
		// If a list of pre-loaded Nyms was passed in, see if one of them is ours.
		//
		if (NULL != pNymMap)
		{
			const OTString	strNymID	(theAgentNymID);
			OT_ASSERT(strNymID.Exists());

			mapOfNyms::iterator ittt = pNymMap->find(strNymID.Get());

			if (pNymMap->end() != ittt) // found it!
			{
				pNym = (*ittt).second;
				OT_ASSERT(NULL != pNym);
			}
		}
		// -------------------------------------------------

		if (NULL == pNym) // It wasn't on the list of already-loaded nyms that was passed in, so we have to load it.
		{
			// By this point we also know that pNym is NOT the server Nym, nor is it the
			// Originator, nor pActingNym, nor pPartyNym, as they were all loaded already and
			// were added to pNymMap, yet we didn't find the Nym we were looking for among them.
			//
			// (Therefore this is some new Nym, and doesn't need to be verified against those Nyms again,
			// before loading it. Let's load it up!)
			//
			if (NULL == (pNym = this->LoadNym(theServerNym)))
				OTLog::vError("%s: Failed loading Nym.\n", szFunc);
			else
				theNymAngel.SetCleanupTarget(*pNym); // CLEANUP  :-)
		}
		// ************************************************************

		// I call this because LoadNym sets my internal Nym pointer to pNym, and then
		// it goes out of scope before the end of this function and gets cleaned-up.
		// Therefore, no point in letting this agent continue to point to bad memory...
		//
		this->ClearTemporaryPointers();

		if ( (NULL != pNym) &&
			(lClosingNumber > 0) &&
			pNym->VerifyIssuedNum(strServerID, lClosingNumber)) // <====================
		{
			return theSmartContract.DropFinalReceiptToInbox(theAgentNymID,         theAccountID,
															lNewTransactionNumber, lClosingNumber,
															strOrigCronItem,       pstrNote,
                                                            pstrAttachment); // pActualAcct=NULL here. (This call will load the acct up and update its inbox hash.)
		}
		else
			OTLog::vError("%s: Error: pNym is NULL, or lClosingNumber <=0, "
						 "or pNym->VerifyIssuedNum(strServerID, lClosingNumber)) failed to verify.\n",
                         szFunc);
	}
	else
		OTLog::vError("%s: No NymID available for this agent...\n", szFunc);

	return false;
}


bool OTAgent::DropFinalReceiptToNymbox(OTSmartContract & theSmartContract,
									   const int64_t & lNewTransactionNumber,
									   const OTString & strOrigCronItem,
									   OTString      * pstrNote/*=NULL*/,
									   OTString      * pstrAttachment/*=NULL*/,
                                       OTPseudonym   * pActualNym/*=NULL*/) // IF the Nym was already loaded, then I HAD to pass it here. But it may not be here. Also: It may not be the right Nym, so need to check before actually using for anything.
{
	OTIdentifier theAgentNymID;
	bool bNymID = this->GetNymID(theAgentNymID);

	// Not all agents have Nyms. (Might be a voting group.)

	if (true == bNymID)
	{
        OTPseudonym * pToActualNym = NULL;

        if ((NULL != pActualNym) && pActualNym->CompareID(theAgentNymID))
            pToActualNym = pActualNym;

		return theSmartContract.DropFinalReceiptToNymbox(theAgentNymID, lNewTransactionNumber,
														 strOrigCronItem, pstrNote, pstrAttachment,
                                                         pToActualNym);
	}

	// TODO: When entites and roles are added, this function may change a bit to accommodate them.

	return false;
}


bool OTAgent::DropServerNoticeToNymbox(bool bSuccessMsg, // Added this so we can notify smart contract parties when it FAILS to activate.
                                       OTPseudonym & theServerNym,
									   const OTIdentifier & theServerID,
									   const int64_t & lNewTransactionNumber,
									   const int64_t & lInReferenceTo,
									   const OTString & strReference,
									   OTString      * pstrNote/*=NULL*/,
									   OTString      * pstrAttachment/*=NULL*/,
                                       OTPseudonym   * pActualNym/*=NULL*/)
{
	OTIdentifier theAgentNymID;
	bool bNymID = this->GetNymID(theAgentNymID);

	// Not all agents have Nyms. (Might be a voting group.)

	if (true == bNymID)
	{
        OTPseudonym * pToActualNym = NULL;

        if ((NULL != pActualNym) && pActualNym->CompareID(theAgentNymID))
            pToActualNym = pActualNym;
        else if ((NULL != m_pNym) && m_pNym->CompareID(theAgentNymID))
            pToActualNym = m_pNym;

		return OTAgreement::DropServerNoticeToNymbox(bSuccessMsg,
                                                     theServerNym,
                                                     theServerID,
                                                     theAgentNymID,
                                                     lNewTransactionNumber,
                                                     lInReferenceTo,
                                                     strReference,
                                                     pstrNote,
                                                     pstrAttachment,
                                                     pToActualNym);
	}

	// TODO: When entites and roles are added, this function may change a bit to accommodate them.

	return false;
}


bool OTAgent::SignContract(OTContract & theInput)
{
	if (!IsAnIndividual() || !DoesRepresentHimself())
	{
		OTLog::vError("OTAgent::SignContract: Entities and roles are not yet supported. Agent: %s.\n",
					  m_strName.Get());
		return false;
	}// todo: when adding entities, this will change.
	// ---------------------------
	if (NULL == m_pNym)
	{
		OTLog::vError("OTAgent::SignContract: Nym was NULL while trying to sign contract. Agent: %s.\n",
					  m_strName.Get());
		return false;
	}// todo: when adding entities, this will change.

	return theInput.SignContract(*m_pNym);
}


bool OTAgent::VerifyIssuedNumber(const int64_t & lNumber, const OTString & strServerID)
{
	// Todo: this function may change when entities / roles are added.
	if (!IsAnIndividual() || !DoesRepresentHimself())
	{
		OTLog::vError("OTAgent::VerifyIssuedNumber:  Error: Entities and Roles are not yet supported. Agent: %s\n",
					 m_strName.Get());
		return false;
	}
	// -----------------------------------------
	if (NULL != m_pNym)
		return m_pNym->VerifyIssuedNum(strServerID, lNumber);
	else
		OTLog::vError("OTAgent::VerifyIssuedNumber: Error: m_pNym was NULL. For agent: %s\n",
					  m_strName.Get());

	return false;
}


bool OTAgent::VerifyTransactionNumber(const int64_t & lNumber, const OTString & strServerID)
{
	// Todo: this function may change when entities / roles are added.
	if (!IsAnIndividual() || !DoesRepresentHimself())
	{
		OTLog::vError("OTAgent::VerifyTransactionNumber:  Error: Entities and Roles are not yet supported. Agent: %s\n",
					 m_strName.Get());
		return false;
	}
	// -----------------------------------------
	if (NULL != m_pNym)
		return m_pNym->VerifyTransactionNum(strServerID, lNumber);
	else
		OTLog::vError("OTAgent::VerifyTransactionNumber: Error: m_pNym was NULL. For agent: %s\n",
					  m_strName.Get());

	return false;
}


// Done
// ASSUMES m_pNym is set already -- doesn't bother loading the nym!
//
bool OTAgent::HarvestTransactionNumber(const int64_t & lNumber,
                                       const OTString & strServerID,
                                       bool bSave/*=false*/, // Each agent's nym is used if pSignerNym is NULL, whereas the server
                                       OTPseudonym * pSignerNym/*=NULL*/) // uses this optional arg to substitute serverNym as signer.
{
    // -------------------------------------
	// Todo: this function may change when entities / roles are added.
    //
	if (!IsAnIndividual() || !DoesRepresentHimself())
	{
		OTLog::vError("%s:  Error: Entities and Roles are not yet supported. Agent: %s\n",
					 __FUNCTION__, m_strName.Get());
		return false;
	}
	// -----------------------------------------
	if (NULL != m_pNym)
	{
        // If a signer wasn't passed in (the server-side uses server nym to sign)
        // then we use the Nym himself as his own signer (common to client-side.)
        //
        if (NULL == pSignerNym)
            pSignerNym = m_pNym;
        // -----------------------------------------------
        const OTIdentifier theServerID(strServerID);

		// This won't "add it back" unless we're SURE he had it in the first place...
        //
        const bool bSuccess = m_pNym->ClawbackTransactionNumber(theServerID, lNumber, bSave, pSignerNym);

		if (bSuccess)
        {
            // The transaction is being removed from play, so we will remove it from this list.
            // That is, when we called RemoveTransactionNumber, the number was being put into play
            // until RemoveIssuedNumber is called to close it out. But now RemoveIssuedNumber won't
            // ever be called, since we are harvesting it back for future use. Therefore the number
            // is currently no longer in play, therefore we remove it from the list of open cron numbers.
            //
            std::set<int64_t>         & theIDSet = m_pNym->GetSetOpenCronItems();
            std::set<int64_t>::iterator theSetIT = theIDSet.find(lNumber);

            if (theIDSet.end() != theSetIT) // IF it was there, THEN remove it. (Client doesn't even track these, though server does.)
                theIDSet.erase(lNumber);

			return true;
        }
		else
			OTLog::vError("%s: Number (%lld) failed to verify for agent: %s (Thus didn't bother "
                          "'adding it back'.)\n", __FUNCTION__, lNumber, m_strName.Get());
	}
	else
		OTLog::vError("%s: Error: m_pNym was NULL. For agent: %s\n",
					  __FUNCTION__, m_strName.Get());

	return false;
}


// This means the transaction number has just been USED (and it now must stay open/outstanding until CLOSED.)
// Therefore we also add it to the set of open cron items, which the server keeps track of (for opening AND closing numbers.)
//
bool OTAgent::RemoveTransactionNumber(const int64_t & lNumber, const OTString & strServerID, OTPseudonym & SIGNER_NYM, bool bSave/*=true*/)
{
	// Todo: this function may change when entities / roles are added.
	if (!IsAnIndividual() || !DoesRepresentHimself())
	{
		OTLog::vError("OTAgent::%s:  Error: Entities and Roles are not yet supported. Agent: %s\n",
                      __FUNCTION__, m_strName.Get());
		return false;
	}
	// -----------------------------------------
	if (NULL != m_pNym)
	{
		std::set<int64_t> & theIDSet = m_pNym->GetSetOpenCronItems(); // The transaction is now in play, so we are going to add it to this list.
        const bool bSuccess       = m_pNym->RemoveTransactionNum(strServerID, lNumber);  // Doesn't save.

        if (bSuccess)
        {
            theIDSet.insert(lNumber); // Since the Trans# is now in play, the server records it as an open cron item.

            if (bSave)
                m_pNym->SaveSignedNymfile(SIGNER_NYM);
        }
        else
            OTLog::vError("OTAgent::%s: Error, should never happen. (I'd assume you aren't "
                          "removing numbers without verifying first if they're there.)\n", __FUNCTION__);
        return bSuccess;
	}
	else
		OTLog::vError("OTAgent::%s: Error: m_pNym was NULL. For agent: %s\n",
					  __FUNCTION__, m_strName.Get());

	return false;
}


// This means the transaction number has just been CLOSED.
// Therefore we remove it from the set of open cron items, which the server keeps track of (for opening AND closing numbers.)
//
bool OTAgent::RemoveIssuedNumber(const int64_t & lNumber,
                                 const OTString & strServerID,
                                 bool bSave/*=false*/,
                                 OTPseudonym * pSignerNym/*=NULL*/)
{
	// Todo: this function may change when entities / roles are added.
	if (!IsAnIndividual() || !DoesRepresentHimself())
	{
		OTLog::vError("OTAgent::%s:  Error: Entities and Roles are not yet supported. Agent: %s\n",
                      __FUNCTION__, m_strName.Get());
		return false;
	}
	// -----------------------------------------
	if (NULL != m_pNym)
    {
        std::set<int64_t> & theIDSet = m_pNym->GetSetOpenCronItems(); // The transaction is being removed from play, so we will remove it from this list.
        const bool bSuccess       = m_pNym->RemoveIssuedNum(strServerID, lNumber);  // Doesn't save.

        if (bSuccess)
        {
            if (NULL == pSignerNym)
                pSignerNym = m_pNym;
            // -----------------------------------
            // Since the Trans# is now out of play, the server removes it as an open cron item.
            //
            std::set<int64_t>::iterator theSetIT = theIDSet.find(lNumber);

            if (theIDSet.end() != theSetIT) // IF it was there, THEN remove it. (Client doesn't even track these, though server does.)
                theIDSet.erase(lNumber);

            if (bSave)
                m_pNym->SaveSignedNymfile(*pSignerNym);
        }
        else
            OTLog::vError("OTAgent::%s: Error, should never happen. (I'd assume you aren't "
                          "removing issued numbers without verifying first if they're there.)\n", __FUNCTION__);
        return bSuccess;
    }
	else
		OTLog::vError("OTAgent::%s: Error: m_pNym was NULL. For agent: %s\n",
					  __FUNCTION__, m_strName.Get());

	return false;
}


// Done
bool OTAgent::ReserveClosingTransNum(const OTString & strServerID, OTPartyAccount & thePartyAcct)
{
	int64_t lTransactionNumber = 0;

	if (IsAnIndividual() && DoesRepresentHimself() && (NULL != m_pNym))
	{
		if (thePartyAcct.GetClosingTransNo() > 0)
		{
			OTLog::Output(0, "OTAgent::ReserveClosingTransNum: Failure: The account ALREADY has a closing transaction number "
						  "set on it. Don't you want to save that first, before overwriting it?\n");
			return false;
		}
		// ----------------------------------------------
		if (m_pNym->GetTransactionNumCount(strServerID) < 1) // Need a closing number...
		{
			OTLog::Output(0, "OTAgent::ReserveClosingTransNum: *** Failure *** Nym needs at least 1 transaction number available in order to do this.\n");
			return false;
		}
		// ----------------------------------------------
		else if (false == m_pNym->GetNextTransactionNum(*m_pNym, strServerID, lTransactionNumber))
		{
			OTLog::Error("OTAgent::ReserveClosingTransNum: Error: Strangely, unable to get a transaction number, even though supposedly one was there.\n");
			return false;
		}
		// ------------------------------------------------
		// BELOW THIS POINT, TRANSACTION # HAS BEEN RESERVED, AND MUST BE SAVED...
		// Any errors below this point will require this call before returning:
		// HarvestAllTransactionNumbers(strServerID);
		//
		thePartyAcct.SetClosingTransNo(lTransactionNumber);
		thePartyAcct.SetAgentName(m_strName);

		return true;
	}
	// -------------------------------------------------
	else // todo: when entities and roles are added... this function will change.
	{
		OTLog::vError("OTAgent::ReserveClosingTransNum: Either the Nym pointer isn't set properly, "
					  "or you tried to use Entities when they haven't been coded yet. Agent: %s \n",
					  m_strName.Get());
	}

	return false;
}


// Done
bool OTAgent::ReserveOpeningTransNum(const OTString & strServerID)
{
	int64_t lTransactionNumber = 0;

	if (IsAnIndividual() && DoesRepresentHimself() && (NULL != m_pNym))
	{
		if (NULL == m_pForParty)
		{
			OTLog::Error("OTAgent::ReserveOpeningTransNum: Error: Party pointer was NULL.  SHOULD NEVER HAPPEN!!\n");
			return false;
		}
		if (m_pForParty->GetOpeningTransNo() > 0)
		{
			OTLog::Output(0, "OTAgent::ReserveOpeningTransNum: Failure: Party ALREADY had an opening transaction number "
						  "set on it. Don't you want to save that first, before overwriting it?\n");
			return false;
		}
		// ----------------------------------------------
		if (m_pNym->GetTransactionNumCount(strServerID) < 1) // Need opening number...
		{
			OTLog::Output(0, "OTAgent::ReserveOpeningTransNum: *** Failure *** Nym needs at least 1 transaction number available in order to do this.\n");
			return false;
		}
		// ----------------------------------------------
		else if (false == m_pNym->GetNextTransactionNum(*m_pNym, strServerID, lTransactionNumber))
		{
			OTLog::Error("OTAgent::ReserveOpeningTransNum: Error: Strangely, unable to get a transaction number, even though supposedly one was there.\n");
			return false;
		}
		// ------------------------------------------------
		// BELOW THIS POINT, TRANSACTION # HAS BEEN RESERVED, AND MUST BE SAVED...
		// Any errors below this point will require this call before returning:
		// HarvestAllTransactionNumbers(strServerID);
		//
		m_pForParty->SetOpeningTransNo(lTransactionNumber);
		m_pForParty->SetAuthorizingAgentName(m_strName.Get());

		return true;
	}
	// -------------------------------------------------
	else // todo: when entities and roles are added... this function will change.
	{
		OTLog::vError("OTAgent::ReserveOpeningTransNum: Either the Nym pointer isn't set properly, "
					 "or you tried to use Entities when they haven't been coded yet. Agent: %s \n",
					  m_strName.Get());
	}

	return false;
}


void OTAgent::Serialize(OTString & strAppend)
{
//	strAppend.Concatenate("<agent>\n\n");

	strAppend.Concatenate("<agent\n name=\"%s\"\n"
						  " doesAgentRepresentHimself=\"%s\"\n"
						  " isAgentAnIndividual=\"%s\"\n"
						  " nymID=\"%s\"\n"
						  " roleID=\"%s\"\n"
						  " groupName=\"%s\" />\n\n",
						  m_strName.Get(),
						  m_bNymRepresentsSelf ? "true" : "false",
						  m_bIsAnIndividual ? "true" : "false",
						  m_strNymID.Get(),
						  m_strRoleID.Get(),
						  m_strGroupName.Get());

//	strAppend.Concatenate("</agent>\n");
}
