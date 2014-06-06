/************************************************************
 *
 *  OTAgent.hpp
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

#ifndef __OT_AGENT_HPP__
#define __OT_AGENT_HPP__

#include "OTString.hpp"

#include <map>

class OTAccount;
class OTAgent;
class OTIdentifier;
class OTParty;
class OTPartyAccount;
class OTPseudonym;
class OTSmartContract;

typedef std::map<std::string, OTPseudonym *>	mapOfNyms;


// Agent is always either the Owner Nym acting in his own interests,
// or is an employee Nym acting actively in a role on behalf of an Entity formed by contract
// or is a voting group acting passively in a role on behalf of an Entity formed by contract
//
// QUESTION: What about having an agent being one Nym representing another?
// NO: because then he needs a ROLE in order to act as agent. In which case, the other
// nym should just create an entity he controls, and make the first nym an agent for that entity.
//
class OTAgent
{
private:
    bool m_bNymRepresentsSelf; // Whether this agent represents himself (a nym) or whether he represents an entity of some sort.
    bool m_bIsAnIndividual; // Whether this agent is a voting group or Nym (whether Nym acting for himself or for some entity.)

	// If agent is active (has a nym), here is the sometimes-available pointer to said Agent Nym.
    OTPseudonym *	m_pNym; // this pointer is not owned by this object, and is here for convenience only.
	// someday may add a "role" pointer here.

	OTParty *		m_pForParty; // The agent probably has a pointer to the party it acts on behalf of.

	/*
	 <Agent type=“group”// could be “nym”, or “role”, or “group”.
			Nym_id=“” // In case of “nym”, this is the Nym’s ID. If “role”, this is NymID of employee in role.
			Role_id=“” // In case of “role”, this is the Role’s ID.
			Entity_id=“this” // same as OwnerID if ever used. Should remove.
			Group_Name=“class_A” // “class A shareholders” are the voting group that controls this agent.
	 */

	OTString m_strName; // agent name (accessible within script language.)

	// info about agent.
	//
	OTString m_strNymID;		// If agent is a Nym, then this is the NymID of that Nym (whether that Nym is owner or not.)
								// If agent is a group (IsAGroup()) then this will be blank. This is different than the
								// Nym stored in OTParty, which if present ALWAYS refers to the OWNER Nym (Though this Nym
								// MAY ALSO be the owner, that fact is purely incidental here AND this NymID could be blank.)
	OTString m_strRoleID;		// If agent is Nym working in a role on behalf of an entity, then this is its RoleID in Entity.
	OTString m_strGroupName;	// If agent is a voting group in an Entity, this is group's Name (inside Entity.)

    // ------------------------------------------------

public:
	OTAgent();
	OTAgent(const std::string str_agent_name, OTPseudonym & theNym, bool bNymRepresentsSelf=true);
	/*IF false, then: ENTITY and ROLE parameters go here.*/
	//
	// Someday another constructor here like the above, for
	// instantiating with an Entity/Group instead of with a Nym.

	OTAgent(bool bNymRepresentsSelf,
			bool bIsAnIndividual,
			const OTString& strName,
			const OTString& strNymID,
			const OTString& strRoleID,
			const OTString& strGroupName);

	virtual ~OTAgent();

	void Serialize(OTString & strAppend);

	// For pointers I don't own, but store for convenience.
	// This clears them once we're done processing, so I don't
	// end up stuck with bad pointers on the next go-around.
	//
	void ClearTemporaryPointers() { m_pNym = NULL; } /* Someday clear entity/role ptr here? And do NOT
													    clear party ptr here (since it's not temporary.)  */
    // ---------------------------------
	// NOTE: Current iteration, these functions ASSUME that m_pNym is loaded.
	// They will definitely fail if you haven't already loaded the Nym.
	//
	bool VerifyIssuedNumber(const int64_t & lNumber, const OTString & strServerID);
	bool VerifyTransactionNumber(const int64_t & lNumber, const OTString & strServerID);

	bool RemoveIssuedNumber(const int64_t & lNumber,
                            const OTString & strServerID,
                            bool bSave=false,
                            OTPseudonym * pSignerNym=NULL);
	bool RemoveTransactionNumber(const int64_t & lNumber, const OTString & strServerID, OTPseudonym & SIGNER_NYM, bool bSave=true);

	bool HarvestTransactionNumber(const int64_t & lNumber, const OTString & strServerID,
                                  bool bSave=false, // Each agent's nym is used if pSignerNym is NULL, whereas the server
                                  OTPseudonym * pSignerNym=NULL); // uses this optional arg to substitute serverNym as signer.

    // ---------------------------------
	bool ReserveOpeningTransNum(const OTString & strServerID);
	bool ReserveClosingTransNum(const OTString & strServerID, OTPartyAccount & thePartyAcct);
    // ---------------------------------
EXPORT	bool SignContract(OTContract & theInput);

	// Verify that this agent somehow has legitimate agency over this account. (According to the account.)
	//
	bool VerifyAgencyOfAccount(const OTAccount & theAccount) const;
    // ---------------------------------
	bool VerifySignature(OTContract & theContract); // Have the agent try to verify his own signature against any contract.

    void SetParty(OTParty & theOwnerParty); // This happens when the agent is added to the party.

	void SetNymPointer(OTPseudonym & theNym) { m_pNym = &theNym; }

EXPORT	bool IsValidSigner(OTPseudonym & theNym);
EXPORT	bool IsValidSignerID(const OTIdentifier & theNymID);

	bool IsAuthorizingAgentForParty();	// true/false whether THIS agent is the authorizing agent for his party.
	int32_t  GetCountAuthorizedAccts();		// The number of accounts, owned by this agent's party, that this agent is the authorized agent FOR.

	// ---------------------------------
    // Only one of these can be true:
    // (I wrestle with making these 2 calls private, since technically it should be irrelevant to the external.)
    //
    bool DoesRepresentHimself() const; // If the agent is a Nym acting for himself, this will be true. Otherwise, if agent is a Nym acting in a role for an entity, or if agent is a voting group acting for the entity to which it belongs, either way, this will be false.
	// ** OR **
    bool DoesRepresentAnEntity() const; // Whether the agent is a voting group acting for an entity, or is a Nym acting in a Role for an entity, this will be true either way. (Otherwise, if agent is a Nym acting for himself, then this will be false.)

	// --------------------
	// Only one of these can be true:
    // - Agent is either a Nym acting for himself or some entity,
    // - or agent is a group acting for some entity.

EXPORT	bool IsAnIndividual() const;	// Agent is an individual Nym. (Meaning either he IS ALSO the party and thus represents himself, OR he is an agent for an entity who is the party, and he's acting in a role for that entity.) If agent were a group, this would be false.
	// ** OR **
    bool IsAGroup() const;			// OR: Agent is a voting group, which cannot take proactive or instant action, but only passive and delayed. Entity-ONLY. (A voting group cannot decide on behalf of individual, but only on behalf of the entity it belongs to.)

    // ---------------------

    // FYI: A Nym cannot act as agent for another Nym.
    // Nor can a Group act as agent for a Nym.
    //
    // If you want those things, then the owner Nym should form an Entity, and
    // then groups and nyms can act as agents for that entity. You cannot have
    // an agent without an entity formed by contract, since you otherwise have no agency agreement.

	// ----------------------
	// For when the agent is an individual:
	//
EXPORT	bool GetNymID(OTIdentifier& theOutput) const;		// If IsIndividual(), then this is his own personal NymID, (whether he DoesRepresentHimself() or DoesRepresentAnEntity() -- either way). Otherwise if IsGroup(), this returns false.

	bool GetRoleID(OTIdentifier& theOutput) const;		// IF IsIndividual() AND DoesRepresentAnEntity(), then this is his RoleID within that Entity. Otherwise, if IsGroup() or DoesRepresentHimself(), then this returns false.

    // --------------------------------------
    // Notice if the agent is a voting group, then it has no signer. (Instead it will have an election.)
    // That is why certain agents are unacceptable in certain scripts.
    // There is an "active" agent who has a signerID, but there is also a "passive" agent who only has
    // a group name, and acts based on notifications and replies in the long-term, versus being immediately
    // able to act as part of the operation of a script.
    // Basically if !IsIndividual(), then GetSignerID() will fail and thus anything needing it as part of the
    // script would also therefore be impossible.
    //
    bool GetSignerID(OTIdentifier& theOutput) const;
	// If IsIndividual() and DoesRepresentAnEntity() then this returns GetRoleID().
	// else if Individual() and DoesRepresentHimself() then this returns GetNymID().
	// else (if IsGroup()) then return false;

    // --------------------------------------------------
    // For when the agent DoesRepresentAnEntity():
    //
    // Whether this agent IsGroup() (meaning he is a voting group that DoesRepresentAnEntity()),
    // OR whether this agent is an individual acting in a role for an entity (IsIndividual() && DoesRepresentAnEntity())
    // ...EITHER WAY, the agent DoesRepresentAnEntity(), and this function returns the ID of that Entity.
    //
    // Otherwise, if the agent DoesRepresentHimself(), then this returns false.
    // I'm debating making this function private along with DoesRepresentHimself / DoesRepresentAnEntity().
    //
	bool GetEntityID(OTIdentifier& theOutput) const; // IF represents an entity, this is its ID. Else fail.

EXPORT	const OTString & GetName() { return m_strName; } // agent's name as used in a script.
    // ------------------------------------------
	// For when the agent is a voting group:
    //
	bool GetGroupName(OTString & strGroupName); // The GroupName group will be found in the EntityID entity.
	//
    // If !IsGroup() aka IsIndividual(), then this will return false.
    //
	// --------------------

//  bool DoesRepresentHimself();
//  bool DoesRepresentAnEntity();
//
//  bool IsIndividual();
//  bool IsGroup();

    // PARTY is either a NYM or an ENTITY. This returns ID for that Nym or Entity.
    //
    // If DoesRepresentHimself() then return GetNymID()
    // else (thus DoesRepresentAnEntity()) so return GetEntityID()
    //
    bool GetPartyID(OTIdentifier& theOutput) const;

	OTParty * GetParty() { return m_pForParty; }

    // IDEA: Put a Nym in the Nyms folder for each entity. While it may
    // not have a public key in the pubkey folder, or embedded within it,
    // it can still have information about the entity or role related to it,
    // which becomes accessible when that Nym is loaded based on the Entity ID.
    // This also makes sure that Nyms and Entities don't ever share IDs, so the
    // IDs become more and more interchangeable.

	// ----------------
	// Often we endeavor to avoid loading the same Nym twice, and a higher-level function
	// will ask an OTParty for a list of all the Nym pointers that it already has,
	// so they can be checked for various things if they are already loaded (when they are needed)
	// without having to load them again in order to check those things, purely out of blindness
	// to the fact that they had infact already been loaded and were floating around in memory somewhere.
	//
	void RetrieveNymPointer(mapOfNyms & map_Nyms_Already_Loaded);

	OTPseudonym * LoadNym(OTPseudonym & theServerNym);

	bool DropFinalReceiptToNymbox(OTSmartContract & theSmartContract,
								  const int64_t & lNewTransactionNumber,
								  const OTString & strOrigCronItem,
								  OTString      * pstrNote=NULL,
								  OTString      * pstrAttachment=NULL,
                                  OTPseudonym   * pActualNym=NULL);

	bool DropFinalReceiptToInbox(mapOfNyms * pNymMap,
								 const OTString & strServerID,
								 OTPseudonym & theServerNym,
								 OTSmartContract & theSmartContract,
								 const OTIdentifier & theAccountID,
								 const int64_t & lNewTransactionNumber,
								 const int64_t & lClosingNumber,
								 const OTString & strOrigCronItem,
								 OTString * pstrNote=NULL,
								 OTString * pstrAttachment=NULL);

	bool DropServerNoticeToNymbox(bool bSuccessMsg, // the notice can be "acknowledgment" or "rejection"
                                  OTPseudonym & theServerNym,
								  const OTIdentifier & theServerID,
								  const int64_t & lNewTransactionNumber,
								  const int64_t & lInReferenceTo,
								  const OTString & strReference,
								  OTString      * pstrNote=NULL,
								  OTString      * pstrAttachment=NULL,
                                  OTPseudonym   * pActualNym=NULL);

};


#endif // __OT_AGENT_HPP__
