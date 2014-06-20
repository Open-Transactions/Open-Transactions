/************************************************************
 *
 *  OTVariable.cpp
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

#include "OTVariable.hpp"

#include "OTASCIIArmor.hpp"
#include "OTLog.hpp"
#include "OTScript.hpp"


void OTVariable::Serialize(OTString & strAppend,
						   bool bCalculatingID/*=false*/)
{
	// ---------------------------------------
	std::string str_access("");

	switch (m_Access) {
		case OTVariable::Var_Constant:		// This cannot be changed from inside the script.
			str_access = "constant";
			break;
		case OTVariable::Var_Persistent:	// This can be changed without notifying the parties.
			str_access = "persistent";
			break;
		case OTVariable::Var_Important:		// This cannot be changed without notifying the parties.
			str_access = "important";
			break;
		default:
			OTLog::Error("OTVariable::Serialize:  ERROR:  Bad variable type.\n");
			break;
	}
	// ---------------------------------------
	std::string str_type;

	switch (m_Type) {
		case OTVariable::Var_String:
		{
			str_type = "string";

			if ((false == bCalculatingID) && // we don't serialize the variable's value when calculating the
				(m_str_Value.size() > 0)) // owner OTScriptable's ID, since the value can change over time.
			{
				OTString strVal(m_str_Value.c_str());
				OTASCIIArmor ascVal(strVal);
				strAppend.Concatenate("<variable\n name=\"%s\"\n"
									  " value=\"%s\"\n"
									  " type=\"%s\"\n"
									  " access=\"%s\" >\n%s</variable>\n\n",
									  m_strName.Get(),
									  "exists",
									  str_type.c_str(),
									  str_access.c_str(),
									  ascVal.Get());
			}
			else
			{
				strAppend.Concatenate("<variable\n name=\"%s\"\n"
									  " value=\"%s\"\n"
									  " type=\"%s\"\n"
									  " access=\"%s\" />\n\n",
									  m_strName.Get(),
									  "none", // value
									  str_type.c_str(),
									  str_access.c_str());
			}
		}
			break;
		case OTVariable::Var_Integer:
			str_type = "integer";
			strAppend.Concatenate("<variable\n name=\"%s\"\n"
								  " value=\"%d\"\n"
								  " type=\"%s\"\n"
								  " access=\"%s\" />\n\n",
								  m_strName.Get(),
								  bCalculatingID ? 0 : m_nValue, // we don't serialize the variable's value when calculating the smart contract's ID.
								  str_type.c_str(), str_access.c_str());
			break;
		case OTVariable::Var_Bool:
			str_type = "bool";
			strAppend.Concatenate("<variable\n name=\"%s\"\n"
								  " value=\"%s\"\n"
								  " type=\"%s\"\n"
								  " access=\"%s\" />\n\n",
								  m_strName.Get(),
								  bCalculatingID ? "false" : (m_bValue ? "true" : "false"), // we don't serialize the variable's value when calculating the smart contract's ID.
								  str_type.c_str(), str_access.c_str());
			break;
		default:
			str_type = "ERROR_VARIABLE_TYPE";
			OTLog::Error("OTVariable::Serialize: Error, Wrong Type -- not serializing.\n");
			break;
	}
	// ---------------------------------------
}


// NO TYPE (YET)
OTVariable::OTVariable()
: m_nValue(0), m_bValue(false),
  m_nValueBackup(0), m_bValueBackup(false),
  m_pBylaw(NULL),
  m_Type(OTVariable::Var_Error_Type),
  m_Access(Var_Error_Access),
  m_pScript(NULL)
{

}


// STRING
OTVariable::OTVariable(const std::string str_Name, const std::string str_Value,	const OTVariable_Access theAccess/*=Var_Persistent*/)
: m_strName(str_Name.c_str()),
  m_str_Value(str_Value),
  m_nValue(0),
  m_bValue(false),
  m_str_ValueBackup(str_Value),
  m_nValueBackup(0),
  m_bValueBackup(false),
  m_pBylaw(NULL),
  m_Type(OTVariable::Var_String),
  m_Access(theAccess),
  m_pScript(NULL)
{
	if (m_str_Value.empty())
        m_str_Value = "";
	if (m_str_ValueBackup.empty())
        m_str_ValueBackup = "";
}


// INT
OTVariable::OTVariable(const std::string str_Name, const int32_t nValue, const OTVariable_Access theAccess/*=Var_Persistent*/)
: m_strName(str_Name.c_str()),
  m_nValue(nValue),
  m_bValue(false),
  m_nValueBackup(nValue),
  m_bValueBackup(false),
  m_pBylaw(NULL),
  m_Type(OTVariable::Var_Integer),
  m_Access(theAccess),
  m_pScript(NULL)
{

}


// BOOL
OTVariable::OTVariable(const std::string str_Name, const bool bValue, const OTVariable_Access theAccess/*=Var_Persistent*/)
: m_strName(str_Name.c_str()),
  m_nValue(0),
  m_bValue(bValue),
  m_nValueBackup(0),
  m_bValueBackup(bValue),
  m_pBylaw(NULL),
  m_Type(OTVariable::Var_Bool),
  m_Access(theAccess),
  m_pScript(NULL)
{

}


OTVariable::~OTVariable()
{
    if (NULL != m_pScript)
    {
        m_pScript->RemoveVariable(*this);
    }

	m_pScript = NULL;  // I wasn't the owner, it was a pointer for convenience only.
    m_pBylaw  = NULL;  // I wasn't the owner, it was a pointer for convenience only.
}


bool OTVariable::SetValue(const int32_t & nValue)
{
	if (!IsInteger())
	{
		OTLog::vError("OTVariable::SetValue(int64_t): Error: This variable (%s) is not an integer.\n",
					  m_strName.Get());
		return false;
	}

	m_nValue = m_nValueBackup = nValue;

	return true;
}


bool OTVariable::SetValue(const bool bValue)
{
	if (!IsBool())
	{
		OTLog::vError("OTVariable::SetValue(bool): Error: This variable (%s) is not a bool.\n",
					  m_strName.Get());
		return false;
	}

	m_bValue = m_bValueBackup = bValue;

	return true;
}


bool OTVariable::SetValue(const std::string & str_Value)
{
	if (!IsString())
	{
		OTLog::vError("OTVariable::SetValue(std::string): Error: This variable (%s) is not a string.\n",
					  m_strName.Get());
		return false;
	}

	m_str_Value = m_str_ValueBackup = str_Value;

    if (m_str_Value.empty())
        m_str_Value = "";
	if (m_str_ValueBackup.empty())
        m_str_ValueBackup = "";

	return true;
}



// So you can tell if the variable has CHANGED since it was last set clean.
// (Usually you set clean just before running the script, and you check dirty just AFTER running the script.)
//
bool OTVariable::IsDirty() const
{
	bool bReturnVal = false;

	switch (m_Type)
	{
		case OTVariable::Var_String:
			if (0 != m_str_Value.compare(m_str_ValueBackup)) // If they do NOT match, then it's dirty.
				bReturnVal = true;
			break;
		case OTVariable::Var_Integer:
			if (m_nValue != m_nValueBackup) // If they do NOT match, then it's dirty.
				bReturnVal = true;
			break;
		case OTVariable::Var_Bool:
			if (m_bValue != m_bValueBackup) // If they do NOT match, then it's dirty.
				bReturnVal = true;
			break;
		default:
			OTLog::vError("OTVariable::IsDirty: Error: unknown type for variable: %s\n", m_strName.Get());
			break;
	}

	return bReturnVal;
}


// Sets the variable as clean, so you can check it later and see if it's been changed (if it's DIRTY again.)
void OTVariable::SetAsClean()
{
	switch (m_Type)
	{
		case OTVariable::Var_String:
			m_str_ValueBackup = m_str_Value; // Save a copy of the current value, so we can check later and see if they're different.
			break;
		case OTVariable::Var_Integer:
			m_nValueBackup = m_nValue; // Save a copy of the current value, so we can check later and see if they're different.
			break;
		case OTVariable::Var_Bool:
			m_bValueBackup = m_bValue; // Save a copy of the current value, so we can check later and see if they're different.
			break;
		default:
			OTLog::vError("OTVariable::SetAsClean: Error: unknown type for variable: %s\n", m_strName.Get());
			m_str_ValueBackup	= m_str_Value;
			m_nValueBackup		= m_nValue;
			m_bValueBackup		= m_bValue;
			break;
	}
}


// If the script destructs before the variable does, it unregisters
// itself here, so the variable isn't stuck with a bad pointer.
//
void OTVariable::UnregisterScript()
{
    this->m_pScript = NULL;
}


// We keep an internal script pointer here, so if we destruct,
// we can remove ourselves from the script.
//
void OTVariable::RegisterForExecution(OTScript& theScript)
{
	this->SetAsClean(); // so we can check for dirtiness after execution.
	// -------------------------------------------------------------------------
	const std::string str_var_name = m_strName.Get();
	// -------------------------------------------------------------------------
	theScript.AddVariable (str_var_name, *this);
	// -------------------------------------------------------------------------
    this->m_pScript = &theScript; // So later, if the variable destructs, and this pointer is set, the variable can remove itself from the script.
}


// Done
bool OTVariable::Compare(OTVariable & rhs)
{
	if (!(GetName().Compare(rhs.GetName())))
	{
		OTLog::vOutput(0, "OTVariable::Compare: Names don't match: %s / %s \n",
					   GetName().Get(), rhs.GetName().Get());
		return false;
	}
	if ( ! (GetType() == rhs.GetType()) )
	{
		OTLog::vOutput(0, "OTVariable::Compare: Type doesn't match: %s \n",
					   GetName().Get());
		return false;
	}
	if ( ! (GetAccess() == rhs.GetAccess()) )
	{
		OTLog::vOutput(0, "OTVariable::Compare: Access types don't match: %s \n",
					   GetName().Get());
		return false;
	}
	// -------------------------------

	bool bMatch = false;

	switch (GetType())
	{
		case OTVariable::Var_Integer:
			bMatch = (GetValueInteger() == rhs.GetValueInteger());
			break;
		case OTVariable::Var_Bool:
			bMatch = (GetValueBool() == rhs.GetValueBool());
			break;
		case OTVariable::Var_String:
			bMatch = (GetValueString().compare(rhs.GetValueString()) == 0);
			break;
		default:
			OTLog::vError("OTVariable::Compare: Unknown type in variable %s.\n",
						 m_strName.Get());
			break;
	}

	return bMatch;
}
