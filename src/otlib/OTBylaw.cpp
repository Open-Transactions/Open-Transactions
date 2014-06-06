/************************************************************
 *
 *  OTBylaw.cpp
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

#include "OTBylaw.hpp"

#include "OTClause.hpp"
#include "OTLog.hpp"
#include "OTScriptable.hpp"
#include "OTStorage.hpp"

#include <set>


void OTBylaw::Serialize(OTString & strAppend,
						bool bCalculatingID/*=false*/)
{
	strAppend.Concatenate("<bylaw\n name=\"%s\"\n"
						  " numVariables=\"%d\"\n"
						  " numClauses=\"%d\"\n"
						  " numHooks=\"%d\"\n"
						  " numCallbacks=\"%d\"\n"
						  " language=\"%s\" >\n\n",
						  m_strName.Get(),
						  m_mapVariables.size(), // HOW MANY VARIABLES?
						  m_mapClauses.size(), // HOW MANY CLAUSES?
						  m_mapHooks.size(), // How many HOOKS?
						  m_mapCallbacks.size(), // How many CALLBACK?
						  m_strLanguage.Get());
	// ------------------------------

	FOR_EACH(mapOfVariables, m_mapVariables)
	{
		OTVariable * pVar = (*it).second;
		OT_ASSERT(NULL != pVar);

		pVar->Serialize(strAppend, bCalculatingID); // Variables save in a specific state during ID calculation (no matter their current actual value.)
	}
	// ------------------------------

	FOR_EACH(mapOfClauses, m_mapClauses)
	{
		OTClause * pClause = (*it).second;
		OT_ASSERT(NULL != pClause);

		pClause->Serialize(strAppend);
	}
	// ------------------------------

	FOR_EACH(mapOfHooks, m_mapHooks)
	{
		const std::string & str_hook_name	= (*it).first;
		const std::string & str_clause_name	= (*it).second;

		strAppend.Concatenate("<hook\n name=\"%s\"\n"
							  " clause=\"%s\" />\n\n",
							  str_hook_name.c_str(),
							  str_clause_name.c_str());
	}
	// ------------------------------

	FOR_EACH(mapOfCallbacks, m_mapCallbacks)
	{
		const std::string & str_callback_name	= (*it).first;
		const std::string & str_clause_name		= (*it).second;

		strAppend.Concatenate("<callback\n name=\"%s\"\n"
							  " clause=\"%s\" />\n\n",
							  str_callback_name.c_str(),
							  str_clause_name.c_str());
	}
	// ------------------------------
	strAppend.Concatenate("</bylaw>\n\n");
}


// So you can tell if the persistent or important variables have CHANGED since it was last set clean.
//
bool OTBylaw::IsDirty() const
{
	bool bIsDirty = false;

	FOR_EACH_CONST(mapOfVariables, m_mapVariables)
	{
		OTVariable * pVar	= (*it).second;
		OT_ASSERT(NULL != pVar);
		// ---------------------------------------------------

		// "Persistent" *AND* "Important" Variables are both considered "persistent".
		// Important has the added distinction that notices are required when important variables change.
		//
		if (pVar->IsDirty())
		{
			if (pVar->IsPersistent())
			{
				bIsDirty = true;
				break;
			}
			else	// If it's not persistent (which also includes important) the only other option is CONSTANT. Then why is it dirty?
				OTLog::vError("OTBylaw::IsDirty: Error: Why is it that a variable is CONSTANT, yet DIRTY at the same time?\n");
		}
	}

	return bIsDirty;
}


// So you can tell if ONLY the IMPORTANT variables have changed since the last "set clean".
//
bool OTBylaw::IsDirtyImportant() const
{
	bool bIsDirty = false;

	FOR_EACH_CONST(mapOfVariables, m_mapVariables)
	{
		OTVariable * pVar = (*it).second;
		OT_ASSERT(NULL != pVar);
		// ---------------------------------------------------

		// "Persistent" *AND* "Important" Variables are both considered "persistent".
		// But: Important has the added distinction that notices are required when important variables change.
		// (So sometimes you need to know if important variables have changed, so you know whether to send a notice.)
		//
		if (pVar->IsDirty() && pVar->IsImportant())
		{
			bIsDirty = true;
			break;
		}
	}

	return bIsDirty;
}


// Sets the variables as clean, so you can check later and see if any have been changed (if it's DIRTY again.)
//
void OTBylaw::SetAsClean()
{
	FOR_EACH(mapOfVariables, m_mapVariables)
	{
		OTVariable * pVar	= (*it).second;
		OT_ASSERT(NULL != pVar);
		// ---------------------------------------------------
		pVar->SetAsClean(); // so we can check for dirtiness later, if it's changed.
	}
}


// Register the variables of a specific Bylaw into the Script interpreter,
// so we can execute a script.
//
void OTBylaw::RegisterVariablesForExecution(OTScript& theScript)
{
	FOR_EACH(mapOfVariables, m_mapVariables)
	{
		const std::string str_var_name	= (*it).first;
		OTVariable * pVar				= (*it).second;
		OT_ASSERT((NULL != pVar)&&(str_var_name.size() > 0));
		// ---------------------------------------------------
		pVar->RegisterForExecution(theScript);
	}
}


// Done:
bool OTBylaw::Compare(OTBylaw & rhs)
{
	if (
		(m_strName.Compare(rhs.GetName())) &&
		(m_strLanguage.Compare(rhs.GetLanguage()))
		)
	{
		if (GetVariableCount() != rhs.GetVariableCount())
		{
			OTLog::vOutput(0, "OTBylaw::Compare: The variable count doesn't match for bylaw: %s\n",
						   m_strName.Get());
			return false;
		}
		if (GetClauseCount() != rhs.GetClauseCount())
		{
			OTLog::vOutput(0, "OTBylaw::Compare: The clause count doesn't match for bylaw: %s\n",
						   m_strName.Get());
			return false;
		}
		if (GetHookCount() != rhs.GetHookCount())
		{
			OTLog::vOutput(0, "OTBylaw::Compare: The hook count doesn't match for bylaw: %s\n",
						   m_strName.Get());
			return false;
		}
		if (GetCallbackCount() != rhs.GetCallbackCount())
		{
			OTLog::vOutput(0, "OTBylaw::Compare: The callback count doesn't match for bylaw: %s\n",
						   m_strName.Get());
			return false;
		}
		// THE COUNTS MATCH, Now let's look up each one by NAME and verify that they match...
		// ---------------------
		//
		FOR_EACH_CONST(mapOfVariables, m_mapVariables)
		{
			OTVariable * pVar = (*it).second;
			OT_ASSERT(NULL != pVar);
			// -----------------------------

			OTVariable * pVar2 = rhs.GetVariable(pVar->GetName().Get());

			if (NULL == pVar2)
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed: Variable not found: %s.\n",
							   pVar->GetName().Get());
				return false;
			}
			if (!pVar->Compare(*pVar2))
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed comparison between 2 variables named %s.\n",
							   pVar->GetName().Get());
				return false;
			}
		}
		// ---------------------
		FOR_EACH_CONST(mapOfClauses, m_mapClauses)
		{
			OTClause * pClause = (*it).second;
			OT_ASSERT(NULL != pClause);
			// -----------------------------

			OTClause * pClause2 = rhs.GetClause(pClause->GetName().Get());

			if (NULL == pClause2)
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed: Clause not found: %s.\n",
							   pClause->GetName().Get());
				return false;
			}
			if (!pClause->Compare(*pClause2))
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed comparison between 2 clauses named %s.\n",
							   pClause->GetName().Get());
				return false;
			}
		}
		// ---------------------
		FOR_EACH_CONST(mapOfCallbacks, m_mapCallbacks)
		{
			const std::string & str_callback_name	= (*it).first;
			const std::string & str_clause_name		= (*it).second;
			// ---------------------------------

			OTClause * pCallbackClause  = this->GetCallback(str_callback_name);
			OTClause * pCallbackClause2 = rhs.GetCallback(str_callback_name);

			if (NULL == pCallbackClause)
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed: Callback (%s) clause (%s) not found on this bylaw: %s.\n",
							   str_callback_name.c_str(), str_clause_name.c_str(), m_strName.Get());
				return false;
			}
			else if (NULL == pCallbackClause2)
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed: Callback (%s) clause (%s) not found on rhs bylaw: %s.\n",
							   str_callback_name.c_str(), str_clause_name.c_str(), rhs.GetName().Get());
				return false;
			}
			else if (!(pCallbackClause->GetName().Compare(pCallbackClause2->GetName())))
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed: Callback (%s) clause (%s) on rhs has a different name (%s) than *this bylaw: %s.\n",
							   str_callback_name.c_str(), str_clause_name.c_str(), pCallbackClause2->GetName().Get(), m_strName.Get());
				return false;
			}

			// OPTIMIZE: Since ALL the clauses are already compared, one-by-one, in the above block, then we don't
			// actually HAVE to do a compare clause here. We just need to make sure that we got them both via the same
			// name, and that the counts are the same (as already verified above) and that should actually be good enough.
			// For now though, I'm leaving this verification commented out.
//			else if (!pCallbackClause->Compare(*pCallbackClause2))
//			{
//				OTLog::vOutput(0, "OTBylaw::Compare: Failed comparison between 2 callback (%s) clauses (%s) on bylaws both named %s.\n",
//							   str_callback_name.c_str(), str_clause_name.c_str(), rhs.GetName().Get());
//				return false;
//			}
		}
		// ---------------------
		//typedef std::multimap	<std::string, std::string> mapOfHooks;
		std::set<std::string> theHookSet;

		// There might be MANY entries with the SAME HOOK NAME. So we add them
		// all to a SET in order to get unique keys.
		FOR_EACH_CONST(mapOfHooks, m_mapHooks)
		{
			const std::string & str_hook_name	= (*it).first;
//			const std::string & str_clause_name	= (*it).second;
			// -----------------------------------------

			theHookSet.insert(str_hook_name);
		}
		// Now we loop through all the unique hook names, and get
		// the list of clauses for EACH bylaw for THAT HOOK.
		FOR_EACH_IT_CONST(std::set<std::string>, theHookSet, it_hook)
		{
			const std::string & str_hook_name = *it_hook;
			// ------------------------------------

			mapOfClauses theHookClauses, theHookClauses2;

			if (	!this->GetHooks(str_hook_name, theHookClauses)
				||	!rhs.  GetHooks(str_hook_name, theHookClauses2))
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Failed finding hook (%s) clauses on this bylaw or rhs bylaw: %s\n",
							   str_hook_name.c_str(), m_strName.Get());
				return false;
			}

			if (theHookClauses.size() != theHookClauses2.size())
			{
				OTLog::vOutput(0, "OTBylaw::Compare: Hook (%s) clauses count doesn't match between this bylaw and the rhs bylaw named: %s\n",
							   str_hook_name.c_str(), m_strName.Get());
				return false;
			}
			// -----------------------------------------------
//			typedef std::map<std::string, OTClause *> mapOfClauses;

			FOR_EACH(mapOfClauses, theHookClauses)
			{
				const std::string  str_clause_name = (*it).first;
				OTClause * pClause = (*it).second;
				OT_ASSERT(NULL != pClause);
				// --------------------------------

				mapOfClauses::iterator it_rhs = theHookClauses2.find(str_clause_name);

				if (theHookClauses2.end() == it_rhs)
				{
					OTLog::vOutput(0, "OTBylaw::Compare: Unable to find hook clause (%s) on rhs that was definitely present on *this. Bylaw: %s\n",
								   str_clause_name.c_str(), m_strName.Get());
					return false;
				}

				// OPTIMIZE: Since ALL the clauses are already compared, one-by-one, in an above block, then we don't
				// actually HAVE to do a compare clause here. We just need to make sure that we got them both via the same
				// name, and that the counts are the same (as already verified above) and that should actually be good enough.
//				OTClause * pClause2 = (*it_rhs).second;
//				OT_ASSERT(NULL != pClause2);
//
//				if (!pClause->Compare(*pClause2))
//				{
//					OTLog::vOutput(0, "OTBylaw::Compare: Failed comparison between 2 hook clauses named %s.\n",
//								   str_clause_name.c_str());
//					return false;
//				}
				// -------------------------------
			}
		} // FOR_EACH_IT(std::set<std::string>, theHookSet, it_hook)

		return true;
	}

	return false;
}


const std::string OTBylaw::GetCallbackNameByIndex(int32_t nIndex)
{
    if ((nIndex < 0) || (nIndex >= static_cast<int64_t>(m_mapCallbacks.size())))
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;

        FOR_EACH(mapOfCallbacks, m_mapCallbacks)
        {
            const std::string & str_callback_name	= (*it).first;
//          const std::string & str_clause_name		= (*it).second;  // FYI.
            // ---------------------------------
            ++nLoopIndex; // 0 on first iteration.

            if (nLoopIndex == nIndex)
                return str_callback_name;
        }
    }
    return "";
}


OTClause * OTBylaw::GetCallback(const std::string str_CallbackName)
{
	if ((false == OTScriptable::ValidateName(str_CallbackName)) ||	// Invalid callback name was passed in.
		(str_CallbackName.compare(0,9,"callback_") != 0))	// The first 9 characters do not match callback_
	{
		OTLog::vError("OTBylaw::GetCallback: Callback name MUST begin with callback_ but value passed in was: %s\n",
					  str_CallbackName.c_str());
		return NULL;
	}
	// ------------------------------------

	FOR_EACH(mapOfCallbacks, m_mapCallbacks)
	{
		const std::string & str_callback_name	= (*it).first;
		const std::string & str_clause_name		= (*it).second;
		// ---------------------------------
		// IF this entry (of a clause registered for a specific callback) MATCHES the callback name passed in...
		//
		if (0 == (str_callback_name.compare(str_CallbackName)))
		{
			OTClause * pClause = this->GetClause(str_clause_name);

			if (NULL != pClause) // found it
			{
				return pClause;
			}
			else
			{
				OTLog::vOutput(0, "OTBylaw::GetCallback: Couldn't find clause (%s) that was registered for callback (%s)\n",
							   str_clause_name.c_str(), str_callback_name.c_str());
			}
		}
		// else no error, since it's normal for nothing to match.
	}

	return NULL;
}


// You are NOT allowed to add multiple callbacks for any given callback trigger.
// There can be only one clause that answers to any given callback.
//
bool OTBylaw::AddCallback(const std::string str_CallbackName, const std::string str_ClauseName)
{
	// Make sure it's not already there...
	//
	mapOfCallbacks::iterator it = m_mapCallbacks.find(str_CallbackName);

	if (m_mapCallbacks.end() != it) // It's already there. (Can't add it twice.)
	{
		const std::string str_existing_clause = (*it).second;
		OTLog::vOutput(0, "OTBylaw::AddCallback: Failed to add callback (%s) to bylaw %s, already there as %s.\n",
					   str_CallbackName.c_str(), m_strName.Get(),
					   str_existing_clause.c_str());
		return false;
	}
	// Below this point, we know the callback wasn't already there.
	// --------------------------------------------------------------

	if (!OTScriptable::ValidateName(str_CallbackName) || !OTScriptable::ValidateName(str_ClauseName))
		OTLog::vError("OTBylaw::AddCallback: Error: empty name (%s) or clause (%s).",
					  str_CallbackName.c_str(), str_ClauseName.c_str());
	else if (str_CallbackName.compare(0,9,"callback_") != 0) // If the callback name DOESN'T begin with callback_ then it is rejected.
		OTLog::vOutput(0, "OTBylaw::AddCallback: Callback name MUST begin with callback_ in order to be accepted: Failure. (callback name %s)  (clause name %s) \n",
					   str_CallbackName.c_str(), str_ClauseName.c_str());
	else if (m_mapCallbacks.end() == m_mapCallbacks.insert(m_mapCallbacks.begin(), std::pair<std::string,std::string>
														   (str_CallbackName.c_str(), str_ClauseName.c_str())))
		OTLog::vError("OTBylaw::AddCallback: Failed inserting to m_mapCallbacks:   %s  /  %s \n",
					  str_CallbackName.c_str(), str_ClauseName.c_str());
	else
		return true;

	return false;
}


// You ARE allowed to add multiple clauses for the same hook.
// They will ALL trigger on that hook.
//
bool OTBylaw::AddHook(const std::string str_HookName, const std::string str_ClauseName)
{
	if (!OTScriptable::ValidateName(str_HookName) || !OTScriptable::ValidateName(str_ClauseName))
		OTLog::vError("OTBylaw::AddHook: Error: empty hook name (%s) or clause name (%s).",
					  str_HookName.c_str(), str_ClauseName.c_str());
	else if ((str_HookName.compare(0,5,"cron_") != 0) && (str_HookName.compare(0,5,"hook_") != 0))
		OTLog::vOutput(0, "OTBylaw::AddHook: hook name MUST begin with either hook_ or cron_ in order to be accepted: Failure. (hook name %s)  (clause name %s) \n",
					  str_HookName.c_str(), str_ClauseName.c_str());
	else if (m_mapHooks.end() == m_mapHooks.insert(std::pair<std::string,std::string>
												   (str_HookName.c_str(), str_ClauseName.c_str())))
		OTLog::vError("OTBylaw::AddHook: Failed inserting to m_mapHooks:   %s  /  %s \n",
					  str_HookName.c_str(), str_ClauseName.c_str());
	else
		return true;

	return false;
}


OTVariable * OTBylaw::GetVariable(const std::string str_var_name) // not a reference, so you can pass in char *. Maybe that's bad? todo: research that.
{
	if (!OTScriptable::ValidateName(str_var_name))
	{
		OTLog::Error("OTBylaw::GetVariable:  Error: invalid str_var_name.\n");
		return NULL;
	}
	// --------------------------------------
	mapOfVariables::iterator it = m_mapVariables.find(str_var_name);

	if (m_mapVariables.end() == it)
		return NULL;

	OTVariable * pVar = (*it).second;
	OT_ASSERT(NULL != pVar);

	return pVar;
}


/// Get Variable pointer by Index. Returns NULL on failure.
///
OTVariable * OTBylaw::GetVariableByIndex(int32_t nIndex)
{
    if (false == ((nIndex >= 0) && (nIndex < static_cast<int64_t>(m_mapVariables.size()))))
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;

        FOR_EACH(mapOfVariables, m_mapVariables)
        {
            OTVariable * pVar = (*it).second;
            OT_ASSERT(NULL != pVar);
            // -------------------------------
            ++nLoopIndex; // 0 on first iteration.

            if (nLoopIndex == nIndex)
                return pVar;
        }
    }
    return NULL;
}


OTClause * OTBylaw::GetClause(const std::string str_clause_name)
{
	if (!OTScriptable::ValidateName(str_clause_name))
	{
		OTLog::Error("OTBylaw::GetClause:  Error: empty str_clause_name.\n");
		return NULL;
	}
	// --------------------------------------
	mapOfClauses::iterator it = m_mapClauses.find(str_clause_name);

	if (m_mapClauses.end() == it)
		return NULL;

	OTClause * pClause = (*it).second;
	OT_ASSERT(NULL != pClause);

	return pClause;
}


/// Get Clause pointer by Index. Returns NULL on failure.
///
OTClause * OTBylaw::GetClauseByIndex(int32_t nIndex)
{
    if (false == ((nIndex >= 0) && (nIndex < static_cast<int64_t>(m_mapClauses.size()))))
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;

        FOR_EACH(mapOfClauses, m_mapClauses)
        {
            OTClause * pClause = (*it).second;
            OT_ASSERT(NULL != pClause);
            // -------------------------------
            ++nLoopIndex; // 0 on first iteration.

            if (nLoopIndex == nIndex)
                return pClause;
        }
    }
    return NULL;
}


const std::string OTBylaw::GetHookNameByIndex(int32_t nIndex)
{
    if ((nIndex < 0) || (nIndex >= static_cast<int64_t>(m_mapHooks.size())))
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;

        FOR_EACH(mapOfHooks, m_mapHooks)
        {
            const std::string & str_hook_name	= (*it).first;
//          const std::string & str_clause_name	= (*it).second; // FYI.
            // ---------------------------------
            ++nLoopIndex; // 0 on first iteration.

            if (nLoopIndex == nIndex)
                return str_hook_name;
        }
    }
    return "";
}


// Returns a map of clause pointers (or not) based on the HOOK name.
// ANY clauses on the list for that hook. (There could be many for each hook.)
// "GetHooks" could have been termed, "GetAMapOfAllClausesRegisteredForTheHookWithName(str_HookName)
//
bool OTBylaw::GetHooks(const std::string str_HookName, mapOfClauses & theResults)
{
	if (!OTScriptable::ValidateName(str_HookName))
	{
		OTLog::vError("%s: Error: invalid str_HookName.\n");
		return false;
	}
	// --------------------------------------
	if ((str_HookName.compare(0,5,"cron_") != 0) && (str_HookName.compare(0,5,"hook_") != 0))
	{
		OTLog::vOutput(0, "%s: hook name MUST begin with either hook_ or cron_ in order to be accepted: Failure. (hook name %s)\n",
					   __FUNCTION__, str_HookName.c_str());
		return false;
	}
	// -----------------------
	bool bReturnVal = false;

	FOR_EACH(mapOfHooks, m_mapHooks)
	{
		const std::string & str_hook_name	= (*it).first;
		const std::string & str_clause_name	= (*it).second;
		// -----------------------------------------

		// IF this entry (of a clause registered for a specific hook) MATCHES the hook name passed in...
		//
		if (0 == (str_hook_name.compare(str_HookName)))
		{
			OTClause * pClause = this->GetClause(str_clause_name);

			if (NULL != pClause) // found it
			{
				// mapOfClauses is a map, meaning it will only allow one entry per unique clause name.
				// Remember, mapOfHooks is a multimap, since there may be multiple clauses registered to
				// the same hook. (Which is fine.) But what if someone registers the SAME clause MULTIPLE
				// TIMES to the SAME HOOK? No need for that. So by the time the clauses are inserted into
				// the result map, the duplicates are automatically weeded out.
				//
				if (theResults.end() != theResults.insert(theResults.begin(), std::pair<std::string, OTClause *>(str_clause_name, pClause)))
					bReturnVal = true;
			}
			else
			{
				OTLog::vOutput(0, "%s: Couldn't find clause (%s) that was registered for hook (%s)\n",
							   __FUNCTION__, str_clause_name.c_str(), str_hook_name.c_str());
			}
		}
		// else no error, since it's normal for nothing to match.
	}

	return bReturnVal;
}


bool OTBylaw::AddVariable(OTVariable& theVariable)
{
	const std::string str_name = theVariable.GetName().Get();

	if (!OTScriptable::ValidateName(str_name))
	{
		OTLog::vError("OTBylaw::AddVariable: Failed due to invalid variable name. In Bylaw: %s\n",
					  m_strName.Get());
		return false;
	}

	// This prefix is disallowed since it's reserved for clause parameter names.
	//
	if (str_name.compare(0,6,"param_") == 0)
	{
		OTLog::vError("OTBylaw::AddVariable: Failed due to invalid variable name (%s). In Bylaw: %s. (param_ is reserved.)\n",
					  str_name.c_str(), m_strName.Get());
		return false;
	}
	if (str_name.compare(0,7,"return_") == 0)
	{
		OTLog::vError("OTBylaw::AddVariable: Failed due to invalid variable name (%s). In Bylaw: %s. (return_ is reserved.)\n",
					  str_name.c_str(), m_strName.Get());
		return false;
	}
	// --------------------------------------------------------------
	// todo security: validate the name.
	//
	mapOfVariables::iterator ii = m_mapVariables.find(str_name);

	// Make sure it's not already there...
	//
	if (m_mapVariables.end() == ii) // If it wasn't already there...
	{
		// -------------------------------
		// Then insert it...
		m_mapVariables.insert(std::pair<std::string, OTVariable *>(str_name, &theVariable));

		// Make sure it has a pointer back to me.
		theVariable.SetBylaw(*this);

		return true;
	}
	else
		OTLog::vOutput(0, "OTBylaw::AddVariable: Failed -- A variable was already there named: %s\n", str_name.c_str());

	return false;
}


bool OTBylaw::AddVariable(const std::string str_Name, const bool bValue, const OTVariable::OTVariable_Access theAccess/*=Var_Persistent*/)
{
	OTVariable * pVar = new OTVariable(str_Name, bValue, theAccess);
	OT_ASSERT(NULL != pVar);

	if (false == AddVariable(*pVar))
	{
		delete pVar;
		return false;
	}

	return true;
}


bool OTBylaw::AddVariable(const std::string str_Name, const std::string str_Value,	const OTVariable::OTVariable_Access theAccess/*=Var_Persistent*/)
{
	OTVariable * pVar = new OTVariable(str_Name, str_Value, theAccess);
	OT_ASSERT(NULL != pVar);

	if (false == AddVariable(*pVar))
	{
		delete pVar;
		return false;
	}

	return true;
}


bool OTBylaw::AddVariable(const std::string str_Name, const int32_t nValue, const OTVariable::OTVariable_Access theAccess/*=Var_Persistent*/)
{
	OTVariable * pVar = new OTVariable(str_Name, nValue, theAccess);
	OT_ASSERT(NULL != pVar);

	if (false == AddVariable(*pVar))
	{
		delete pVar;
		return false;
	}

	return true;
}


bool OTBylaw::AddClause(const char * szName, const char * szCode)
{
	// todo security: validate the input, especially name.
	//

	OT_ASSERT(NULL != szName);
	OT_ASSERT(NULL != szCode);

	OTClause * pClause = new OTClause(szName, szCode);
	OT_ASSERT(NULL != pClause);

	if (false == AddClause(*pClause))
	{
		delete pClause;
		return false;
	}

	return true;
}


bool OTBylaw::AddClause(OTClause& theClause)
{
	if (!theClause.GetName().Exists())
	{
		OTLog::Error("OTBylaw::AddClause: Failed attempt to add a clause with a blank name.\n");
		return false;
	}
	// -----------------------------------
	// To avoid confusion, we disallow clauses beginning in cron_ or hook_ or callback_
	//
	const std::string str_clause_name =  theClause.GetName().Get();

	if (!OTScriptable::ValidateName(str_clause_name))
	{
		OTLog::vError("OTBylaw::AddClause: Failed due to invalid clause name. In Bylaw: %s\n",
					  m_strName.Get());
		return false;
	}
	// -----------------------------------
	if (str_clause_name.compare(0,5,"cron_") == 0) // todo stop hardcoding
	{
		OTLog::Output(0, "OTBylaw::AddClause: Clauses may not be added with a name beginning in cron_\n");
		return false;
	}

	if (str_clause_name.compare(0,5,"hook_") == 0) // todo stop hardcoding
	{
		OTLog::Output(0, "OTBylaw::AddClause: Clauses may not be added with a name beginning in hook_\n");
		return false;
	}

	if (str_clause_name.compare(0,9,"callback_") == 0) // todo stop hardcoding
	{
		OTLog::Output(0, "OTBylaw::AddClause: Clauses may not be added with a name beginning in callback_\n");
		return false;
	}
	// Todo: any other validation on the name. security.
	// -----------------------------------------------------

	mapOfClauses::iterator ii = m_mapClauses.find(str_clause_name);

	if (m_mapClauses.end() == ii) // If it wasn't already there...
	{
		// -------------------------------
		// Then insert it...
		m_mapClauses.insert(std::pair<std::string, OTClause *>(str_clause_name, &theClause));

		// Make sure it has a pointer back to me.
		theClause.SetBylaw(*this);

		return true;
	}
	else
		OTLog::vOutput(0, "OTBylaw::AddClause: Failed -- Clause was already there named %s.\n", str_clause_name.c_str());

	return false;
}


const char * OTBylaw::GetLanguage() const
{
	return m_strLanguage.Exists() ? m_strLanguage.Get() : "chai"; // todo add default script to config files. no hardcoding.
}


OTBylaw::OTBylaw() : m_pOwnerAgreement(NULL)
{

}


OTBylaw::OTBylaw(const char * szName, const char * szLanguage) : m_pOwnerAgreement(NULL)
{
	if (NULL != szName)
		m_strName.Set(szName);
	else
		OTLog::Error("NULL szName passed in to OTBylaw::OTBylaw \n");

	if (NULL != szLanguage)
		m_strLanguage = szLanguage;   // "chai", "angelscript" etc.
	else
		OTLog::Error("NULL szLanguage passed in to OTBylaw::OTBylaw \n");

	// ------------------------
	const std::string str_bylaw_name = m_strName.Get();
	const std::string str_language = m_strLanguage.Get();

	// Let the calling function validate these, if he doesn't want to risk an ASSERT...
	//
	if (!OTScriptable::ValidateName(str_bylaw_name) ||
		!OTScriptable::ValidateName(str_language))
	{
		OTLog::Error("Failed validation in to OTBylaw::OTBylaw \n");
	}
}


OTBylaw::~OTBylaw()
{
	// A Bylaw owns its clauses and variables.
	//
	while (!m_mapClauses.empty())
	{
		OTClause * pClause = m_mapClauses.begin()->second;
		OT_ASSERT(NULL != pClause);

		m_mapClauses.erase(m_mapClauses.begin());

		delete pClause;
		pClause = NULL;
	}
	// -------------------------------
	while (!m_mapVariables.empty())
	{
		OTVariable * pVar = m_mapVariables.begin()->second;
		OT_ASSERT(NULL != pVar);

        m_mapVariables.erase(m_mapVariables.begin());

		delete pVar;
		pVar = NULL;
	}
	// --------------------------------

	m_pOwnerAgreement = NULL; // This Bylaw is owned by an agreement (OTScriptable-derived.)

	// Hooks and Callbacks are maps of std::string to std::string.
	//
	// (THEREFORE NO NEED TO CLEAN THEM UP HERE.)
	//
}
