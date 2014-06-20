/************************************************************
 *    
 *  OTScript.cpp
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

#include "OTScript.hpp"

#include "OTLog.hpp"
#include "OTParty.hpp"
#include "OTVariable.hpp"

#ifdef OT_USE_SCRIPT_CHAI
#include "OTScriptChai.hpp"
#endif


// A script should be "Dumb", meaning that you just stick it with its
// parties and other resources, and it EXPECTS them to be the correct
// ones.  It uses them low-level style.
//
// Any verification should be done at a higher level, in OTSmartContract.
// There, multiple parties might be loaded, as well as multiple scripts
// (clauses) and that is where the proper resources, accounts, etc are
// instantiated and validated before any use.
// 
// Thus by the time you get down to OTScript, all that validation is already
// done.  The programmatic user will interact with OTSmartContract, likely,
// and not with OTScript itself.
//

// Note: any relevant assets or asset accounts are listed by their owner / contributor
// parties. Therefore there's no need to separately input any accounts or assets to
// a script, since the necessary ones are already present inside their respective parties.
//
//bool OTScript::ExecuteScript()
//{
//    return true;
//}

/*
 
 To use:
 
 const char * default_script_language = "chai";

 ...
 
 OTParty theParty(theNym);
 
 // (Set up theParty here, with his asset accounts, etc)
 // Then...
 //
 _SharedPtr<OTScript> pScript = OTScript::Factory(default_script_language, strScript);
 
 if (pScript)
 {
     pScript->AddParty("mynym", &theParty);
     pScript->Execute();
 }
 
 
 MIGHT WANT TO ADD an AddParty(string, Nym) function, which automatically wraps the Nym in a party.
 That way you can basically treat a Nym like a party to an agreement.
 
 */

_SharedPtr<OTScript> OTScriptFactory(const std::string & script_type)
{
    // -------------------------------------------
#ifdef OT_USE_SCRIPT_CHAI
    // default or explicit chai script interpreter
    if (script_type == "" || script_type =="chai") // todo no hardcoding.
    {
        _SharedPtr<OTScript> pChaiScript(new OTScriptChai);
        return pChaiScript;
    }
    // -------------------------------------------
//#elif OT_USE_SCRIPT_LUA
//  if (script_type =="lua") // todo no hardcoding.
//  {
//      _SharedPtr<OTScript> pLuaScript(new OTScriptLua);
//      return pLuaScript;
//  }
    // -------------------------------------------
#else
    // default no script interpreter
    if (script_type == "")
    {
        OTLog::Error("\n\n WARNING 1: script_type == noscript. \n\n");
        
        _SharedPtr<OTScript> pNoScript(new OTScript);
        return pNoScript;
    }
#endif
    // -------------------------------------------
    OTLog::vError("%s: Script language (%s) not found.\n",
                  __FUNCTION__, script_type.c_str());
    
    _SharedPtr<OTScript> retVal;
    return retVal;
}


_SharedPtr<OTScript> OTScriptFactory(const std::string & script_type, 
                                     const std::string & script_contents)
{
    // -------------------------------------------
#ifdef OT_USE_SCRIPT_CHAI
    // default or explicit chai script interpreter
    if (script_type == "" || script_type == "chai") // todo no hardcoding.
    {
        _SharedPtr<OTScript> pChaiScript(new OTScriptChai(script_contents));
        return pChaiScript;
    }
    // -------------------------------------------
//#elif OT_USE_SCRIPT_LUA
    //  if (script_type =="lua") // todo no hardcoding.
    //  {
    //      _SharedPtr<OTScript> pLuaScript(new OTScriptLua(script_contents));
    //      return pLuaScript;
    //  }
    // -------------------------------------------
#else
    // default no script interpreter
    if (script_type == "")
    {
        OTLog::Error("\n\n WARNING 2: script_type == noscript. \n\n");
        
        _SharedPtr<OTScript> pNoScript(new OTScript);
        return pNoScript;
    }
#endif
    // -------------------------------------------
    OTLog::vError("%s: Script language (%s) not found.\n",
                  __FUNCTION__, script_type.c_str());
    
    _SharedPtr<OTScript> retVal;
    return retVal;
}


OTScript::OTScript()
{
    
}


OTScript::OTScript(const OTString & strValue) : m_str_script(strValue.Get())
{
    
}


OTScript::OTScript(const char * new_string) : m_str_script(new_string)
{
    
}


OTScript::OTScript(const char * new_string, size_t sizeLength) 
    : m_str_script(new_string, sizeLength)
{
    
}


OTScript::OTScript(const std::string & new_string) : m_str_script(new_string)
{
    
}


OTScript::~OTScript()
{
    // mapOfParties; // NO NEED to clean this up, since OTScript doesn't own the parties.
    // See OTSmartContract, rather, for that.
    
    while (!m_mapVariables.empty())
    {
        OTVariable * pVar = m_mapVariables.begin()->second;
        OT_ASSERT(NULL != pVar);

        // NOTE: We're NOT going to delete pVar, since we don't own it.
        // But we ARE going to remove pVar's pointer to this script, so
        // pVar doesn't dereference a bad pointer later on.
        //
        pVar->UnregisterScript();
        m_mapVariables.erase(m_mapVariables.begin());
    }
}


void OTScript::SetScript(const OTString & strValue)
{
    if (strValue.Exists())
        m_str_script = strValue.Get();
}


void OTScript::SetScript(const char * new_string)
{
    if (NULL != new_string)
        m_str_script = new_string;    
}


void OTScript::SetScript(const char * new_string, size_t sizeLength)
{
    if (NULL != new_string)
        m_str_script.assign(new_string, sizeLength);
}


void OTScript::SetScript(const std::string & new_string)
{
    m_str_script = new_string;
}
    

// The same OTSmartContract that loads all the clauses (scripts) will
// also load all the parties, so it will call this function whenever before it
// needs to actually run a script.
//
// NOTE: OTScript does NOT take ownership of the party, since there could be
// multiple scripts (with all scripts and parties being owned by a OTSmartContract.)
// Therefore it's ASSUMED that the owner OTSmartContract will handle all the work of
// cleaning up the mess!  theParty is passed as reference to insure it already exists.
//
void OTScript::AddParty(const std::string str_party_name, OTParty & theParty)
{
//  typedef std::map<std::string, OTParty *> mapOfParties;

    m_mapParties.insert( std::pair<std::string, OTParty *>(str_party_name, &theParty)) ;
    // We're just storing these pointers for reference value. Script doesn't actually Own the
    // parties, and isn't responsible to clean them up.
    
    theParty.RegisterAccountsForExecution(*this);
}


void OTScript::AddAccount (const std::string str_acct_name, OTPartyAccount & theAcct)
{
    m_mapAccounts.insert( std::pair<std::string, OTPartyAccount *>(str_acct_name, &theAcct)) ;
    
    // We're just storing these pointers for reference value. Script doesn't actually Own the
    // accounts, and isn't responsible to clean them up.
}


// If you want to add a variable to a script, you should probably call OTVariable::RegisterForExecution
// so that later if the variable destructs, it will have a pointer to the script and it can remove itself
// from the script's list of variables. (Instead of calling this function, which is lower-level.)
//
void OTScript::AddVariable (const std::string str_var_name, OTVariable & theVar)
{
//  mapOfVariables  m_mapVariables; 

    m_mapVariables.insert( std::pair<std::string, OTVariable *>(str_var_name, &theVar)) ;

    // We're just storing these pointers for reference value. Script doesn't actually Own the
    // variables, and isn't responsible to clean them up.
}


OTVariable * OTScript::FindVariable(const std::string str_var_name)
{
    mapOfVariables::iterator it_var = m_mapVariables.find(str_var_name);
    return it_var != m_mapVariables.end() ? it_var->second : NULL;
}


// If a variable is set onto a script, it sets an internal pointer to that script.
// Later, when the variable destructs, if that pointer is set, it removes itself
// from the script by calling this function. (Yes, this would be better with smart
// pointers. C++11 here we come!)
//
void OTScript::RemoveVariable (OTVariable & theVar)
{
    const std::string str_var_name  = theVar.GetName().Get();
    mapOfVariables::iterator it_var = m_mapVariables.find(str_var_name);
    
    if (it_var != m_mapVariables.end())
    {
        m_mapVariables.erase(it_var); // no need to delete the variable pointer since the script doesn't own it anyway. 
    }
}


bool OTScript::ExecuteScript(OTVariable * pReturnVar/*=NULL*/)
{
    OTLog::vError("OTScript::ExecuteScript: Scripting has been disabled.\n");
    return true;
}
