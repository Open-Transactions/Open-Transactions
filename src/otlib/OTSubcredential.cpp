/************************************************************
 *
 *  OTSubcredential.cpp
 *
 */

// A nym contains a list of credentials
//
// Each credential contains a "master" subkey, and a list of subkeys
// signed by that master.
//
// The same class (subkey) is used because there are master credentials
// and subkey credentials, so we're using a single "subkey" class to
// encapsulate each credential, both for the master credential and
// for each subkey credential.
//
// Each subkey has 3 key pairs: encryption, signing, and authentication.
//
// Each key pair has 2 OTAsymmetricKeys (public and private.)

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

#include "OTSubcredential.hpp"

#include "OTASCIIArmor.hpp"
#include "OTCredential.hpp"
#include "OTLog.hpp"

#include "irrxml/irrXML.hpp"


// Contains 3 key pairs: signing, authentication, and encryption.
// This is stored as an OTContract, and it must be signed by the
// master key. (which is also an OTSubcredential.)
//

void OTSubcredential::SetOwner(OTCredential & theOwner)
{
    m_pOwner = &theOwner;
}


OTSubcredential::OTSubcredential()
: ot_super(), m_StoreAs(OTSubcredential::credPrivateInfo), m_pOwner(NULL)       { m_strContractType = "CREDENTIAL"; }


OTSubcredential::OTSubcredential(OTCredential & theOwner)
: ot_super(), m_StoreAs(OTSubcredential::credPrivateInfo), m_pOwner(&theOwner)  { m_strContractType = "CREDENTIAL"; }


OTSubcredential::~OTSubcredential()
{
    Release_Subcredential();
    
}


//virtual
void OTSubcredential::Release()
{
    Release_Subcredential();  // My own cleanup is done here.
    
    // Next give the base class a chance to do the same...
	ot_super::Release(); // since I've overridden the base class, I call it now...
}


void OTSubcredential::Release_Subcredential()
{
    // Release any dynamically allocated members here. (Normally.) 
}


//virtual
bool OTSubcredential::SetPublicContents(const mapOfStrings & mapPublic)
{
    m_mapPublicInfo   = mapPublic;
    return true;
}


//virtual
bool OTSubcredential::SetPrivateContents(const mapOfStrings & mapPrivate,
                                               OTPassword   * pImportPassword/*=NULL*/) // if not NULL, it means to use this password by default.)
{
    m_mapPrivateInfo  = mapPrivate;
    return true;
}


void OTSubcredential::SetMasterCredID(const OTString & strMasterCredID)
{
    m_strMasterCredID = strMasterCredID;
}


void OTSubcredential::SetNymIDandSource(const OTString & strNymID, const OTString & strSourceForNymID)
{
    m_strNymID          = strNymID;
    m_strSourceForNymID = strSourceForNymID;
}


void OTSubcredential::UpdateMasterPublicToString(OTString & strAppendTo) // Used in UpdateContents.
{
    OT_ASSERT(NULL != m_pOwner);
    OTASCIIArmor ascMaster(m_pOwner->GetPubCredential());
    strAppendTo.Concatenate("<masterPublic>\n%s</masterPublic>\n\n",
                            ascMaster.Get());
}


void OTSubcredential::UpdatePublicContentsToString(OTString & strAppendTo) // Used in UpdateContents.
{
    if (m_mapPublicInfo.size() > 0)
    {
        strAppendTo.Concatenate("<publicContents count=\"%d\">\n\n", m_mapPublicInfo.size());
        
        FOR_EACH(mapOfStrings, m_mapPublicInfo)
        {
            OTString     strInfo((*it).second);
            OTASCIIArmor ascInfo(strInfo);
            strAppendTo.Concatenate("<publicInfo key=\"%s\">\n%s</publicInfo>\n\n",
                                      (*it).first.c_str(), ascInfo.Get());
        }
        // ------------------------------
        strAppendTo.Concatenate("</publicContents>\n\n");
    }
}


void OTSubcredential::UpdatePublicCredentialToString(OTString & strAppendTo) // Used in UpdateContents.
{
    if (this->GetContents().Exists())
    {
        OTASCIIArmor ascContents(this->GetContents());
        if (ascContents.Exists())
            strAppendTo.Concatenate("<publicCredential>\n%s</publicCredential>\n\n",
                                    ascContents.Get());
    }    
}


void OTSubcredential::UpdatePrivateContentsToString(OTString & strAppendTo) // Used in UpdateContents.
{
    if (m_mapPrivateInfo.size() > 0)
    {
        strAppendTo.Concatenate("<privateContents count=\"%d\">\n\n", m_mapPrivateInfo.size());
        
        FOR_EACH(mapOfStrings, m_mapPrivateInfo)
        {
            OTString     strInfo((*it).second);
            OTASCIIArmor ascInfo(strInfo);
            strAppendTo.Concatenate("<privateInfo key=\"%s\">\n%s</privateInfo>\n\n",
                                    (*it).first.c_str(), ascInfo.Get());
        }
        strAppendTo.Concatenate("</privateContents>\n\n");
    }
}


void OTSubcredential::UpdateContents()
{
	m_xmlUnsigned.Release();
    
	m_xmlUnsigned.Concatenate("<subCredential nymID=\"%s\"\n" // a hash of the nymIDSource
							  " masterCredentialID=\"%s\" >\n\n", // Hash of the master credential that signed this subcredential.
							  this->GetNymID().Get(), this->GetMasterCredID().Get());
    
    if (this->GetNymIDSource().Exists())
    {
        OTASCIIArmor ascSource;
        ascSource.SetString(this->GetNymIDSource()); // A nym should always verify through its own source. (Whatever that may be.)
        m_xmlUnsigned.Concatenate("<nymIDSource>\n%s</nymIDSource>\n\n", ascSource.Get());
    }
    // --------------------------------------------
//  if (OTSubcredential::credPublicInfo == m_StoreAs)  // (Always saving public info.)
    {
        // *****************************************************
        // PUBLIC INFO
        this->UpdateMasterPublicToString(m_xmlUnsigned);
        // --------------------------------------------
        this->UpdatePublicContentsToString(m_xmlUnsigned);
        // *****************************************************
    }
	// -------------------------------------------------
    // If we're saving the private credential info...
    // 
    if (OTSubcredential::credPrivateInfo == m_StoreAs)
    {
        this->UpdatePublicCredentialToString(m_xmlUnsigned);
        // -------------------------------------
        this->UpdatePrivateContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------	
	m_xmlUnsigned.Concatenate("</subCredential>\n");
    // --------------------------------------------
    m_StoreAs = OTSubcredential::credPrivateInfo;  // <=== SET IT BACK TO DEFAULT BEHAVIOR. Any other state processes ONCE, and then goes back to this again.
}


// return -1 if error, 0 if nothing, and 1 if the node was processed.
//
int32_t OTSubcredential::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
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
	// As I do in the case of OTAccount.
    //
	// if (nReturnVal = OTContract::ProcessXMLNode(xml))
    //	  return nReturnVal;
	
    // --------------------------------------------------
	if (strNodeName.Compare("subCredential"))
	{
		m_strNymID			= xml->getAttributeValue("nymID");
		m_strMasterCredID	= xml->getAttributeValue("masterCredentialID");
		
		OTLog::Output(1, "Loading subcredential...\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("nymIDSource"))
	{		
		OTLog::Output(1, "Loading nymIDSource...\n");
		
        OTASCIIArmor ascTemp;
        if (false == OTContract::LoadEncodedTextField(xml, ascTemp))
		{
			OTLog::vError("Error in %s line %d: failed loading expected nymIDSource field.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
		}
        if (ascTemp.Exists())
            ascTemp.GetString(m_strSourceForNymID);

		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("masterPublic"))
	{
        OTString strMasterPublicCredential;
        
		if (false == OTContract::LoadEncodedTextField(xml, strMasterPublicCredential))
		{
			OTLog::vError("Error in %s line %d: failed loading expected master public credential while loading subcredential.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
		}
        // Verify the master public credential we loaded against the one we expected to get, according
        // to the OTCredential that is m_pOwner.
        //
        else if ((NULL != m_pOwner) && false == (m_pOwner->GetPubCredential().Compare(strMasterPublicCredential)))
        {
            OTLog::vError("Failure in %s line %d: while loading subcredential: master public "
                          "credential loaded just now, doesn't match the actual master public credential, "
                          "according to the current owner object.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
        }
		
		nReturnVal = 1;
	}
	// ------------------------------------------------------------------------------------
	else if (strNodeName.Compare("publicContents"))
	{
        OTString strCount;
        strCount = xml->getAttributeValue("count");
        const int32_t nCount = strCount.Exists() ? atoi(strCount.Get()) : 0;
        if (nCount > 0)
        {
            int32_t nTempCount = nCount;
            mapOfStrings mapPublic;
            
            while (nTempCount-- > 0)
            {
                // -----------------------------------------------                
                const char	*	pElementExpected	= "publicInfo";
                OTString		strPublicInfo;
                
                // This map contains values we will also want, when we read the info...
                // (The OTContract::LoadEncodedTextField call below will read all the values
                // as specified in this map.)
                //
                mapOfStrings	temp_MapAttributes;
                temp_MapAttributes.insert(std::pair<std::string, std::string>("key", "")); // Value should be "A" or "E" or "S" after reading.
                
                if (false == OTContract::LoadEncodedTextFieldByName(xml, strPublicInfo, pElementExpected, &temp_MapAttributes)) // </publicInfo>
                {
                    OTLog::vError("%s: Error: "
                                  "Expected %s element with text field.\n", __FUNCTION__,
                                  pElementExpected);
                    return (-1); // error condition
                }
                // ------------------------------------------
                mapOfStrings::iterator it = temp_MapAttributes.find("key");                
                if ((it != temp_MapAttributes.end())) // We expected this much.
                {
                    std::string & str_key = (*it).second;
                    
                    if (str_key.size() > 0) // Success finding key type ('A' 'E' or 'S')
                    {
                        // ---------------------------------------
                        mapPublic.insert(std::pair<std::string, std::string>(str_key, strPublicInfo.Get()));
                        // ---------------------------------------
                    }
                    // else it's empty, which is expected if nothing was there, since that's the default value
                    // that we set above for "name" in temp_MapAttributes.
                    else
                    {
                        OTLog::vError("%s: Expected key type of 'A' or 'E' or 'S'.\n", __FUNCTION__);
                        return (-1); // error condition
                    }
                }
                else
                {
                    OTLog::vError("%s: Strange error: couldn't find key type AT ALL.\n", __FUNCTION__); // should never happen.
                    return (-1); // error condition
                }
            } // while
            // --------------------------------
            if (static_cast<int64_t>(mapPublic.size()) != nCount)
            {
                OTLog::vError("%s, %s, %d: Subcredential expected to load %d publicInfo objects, "
                              "but actually loaded %d. (Mismatch, failure loading.)\n",
                              __FUNCTION__, __FILE__, __LINE__, nCount, mapPublic.size());
                return (-1); // error condition
            }
            // --------------------------------
            if (false == this->SetPublicContents(mapPublic))  // <==============  Success.
            {
                OTLog::vError("%s, %s, %d: Subcredential failed setting public contents while loading.\n",
                              __FUNCTION__, __FILE__, __LINE__);
                return (-1); // error condition    
            }
            // --------------------------------            
        } // if strCount.Exists() && nCount > 0
        // -------------------------------------------------------------------------------
		OTLog::Output(2, "Loaded publicContents for subcredential.\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("publicCredential"))
	{
		if (false == OTContract::LoadEncodedTextField(xml, m_strContents)) // <========= m_strContents.
		{
			OTLog::vError("Error in %s line %d: failed loading expected public credential while loading private subcredential.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
		}
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("privateContents"))
	{
        OTString strCount;
        strCount = xml->getAttributeValue("count");
        const int32_t nCount = strCount.Exists() ? atoi(strCount.Get()) : 0;
        if (nCount > 0)
        {
            int32_t nTempCount = nCount;
            mapOfStrings mapPrivate;
            
            while (nTempCount-- > 0)
            {
                // -----------------------------------------------                
                const char	*	pElementExpected	= "privateInfo";
                OTString		strPrivateInfo;
                
                // This map contains values we will also want, when we read the info...
                // (The OTContract::LoadEncodedTextField call below will read all the values
                // as specified in this map.)
                //
                mapOfStrings	temp_MapAttributes;
                temp_MapAttributes.insert(std::pair<std::string, std::string>("key", "")); // Value should be "A" or "E" or "S" after reading.
                
                if (false == OTContract::LoadEncodedTextFieldByName(xml, strPrivateInfo, pElementExpected, &temp_MapAttributes)) // </privateInfo>
                {
                    OTLog::vError("%s: Error: "
                                  "Expected %s element with text field.\n", __FUNCTION__,
                                  pElementExpected);
                    return (-1); // error condition
                }
                // ------------------------------------------
                mapOfStrings::iterator it = temp_MapAttributes.find("key");                
                if ((it != temp_MapAttributes.end())) // We expected this much.
                {
                    std::string & str_key = (*it).second;
                    
                    if (str_key.size() > 0) // Success finding key type ('A' 'E' or 'S')
                    {
                        // ---------------------------------------
                        mapPrivate.insert(std::pair<std::string, std::string>(str_key, strPrivateInfo.Get()));
                        // ---------------------------------------
                    }
                    // else it's empty, which is expected if nothing was there, since that's the default value
                    // that we set above for "name" in temp_MapAttributes.
                    else
                    {
                        OTLog::vError("%s: Expected key type of 'A' or 'E' or 'S'.\n", __FUNCTION__);
                        return (-1); // error condition
                    }
                }
                else
                {
                    OTLog::vError("%s: Strange error: couldn't find key type AT ALL.\n", __FUNCTION__); // should never happen.
                    return (-1); // error condition
                }
            } // while
            // --------------------------------
            if (static_cast<int64_t>(mapPrivate.size()) != nCount)
            {
                OTLog::vError("%s, %s, %d: Subcredential expected to load %d privateInfo objects, "
                              "but actually loaded %d. (Mismatch, failure loading.)\n",
                              __FUNCTION__, __FILE__, __LINE__, nCount, mapPrivate.size());
                return (-1); // error condition
            }
            // --------------------------------
            OT_ASSERT(NULL != m_pOwner);
            
            // Sometimes we are supposed to use a specific, pre-specified password (versus just
            // blindly asking the user to type a password when it's not cached alrady.) For example,
            // when importing a Nym, the exported version of the Nym is not encrypted to the cached
            // wallet key. It's got its own exported passphrase. So it won't be cached, and we will have
            // the wallet's cached key disabled while loading it. This means we have to enter the same
            // passphrase many times in a row, while OT loads up all the credentials and keys for that
            // Nym. Therefore, instead, we ask the user up front to enter the special passphrase for that
            // exported Nym. Then we just pass it in to all the functions that need it, so none of them have
            // to ask the user to type it.
            //
            // That's what brings us here now... when that happens, m_pOwner->GetImportPassword() will be set
            // with the appropriate pointer to the passphrase. Otherwise it will be NULL. Meanwhile SetPrivateContents
            // below accepts an import passphrase, which it defaults to NULL.
            //
            // So we just pass it in either way (sometimes it's NULL and the wallet cached master key is used, and
            // sometimes an actual passphrase is passed in, so we use it.)
            
            if (false == this->SetPrivateContents(mapPrivate, m_pOwner->GetImportPassword()))
            {
                OTLog::vError("%s, %s, %d: Subcredential failed setting private contents while loading.\n",
                              __FUNCTION__, __FILE__, __LINE__);
                return (-1); // error condition    
            }
            // --------------------------------            
        } // if strCount.Exists() && nCount > 0
        // -------------------------------------------------------------------------------
		OTLog::Output(2, "Loaded privateContents for subcredential.\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	return nReturnVal;
}


// VERIFICATION

// Verify that m_strNymID is the same as the hash of m_strSourceForNymID.
//
bool OTSubcredential::VerifyNymID()
{
    // ---------------------------------------
    // Verify that m_strNymID is the same as the hash of m_strSourceForNymID.
    //
    OTIdentifier theTempID;
    const bool bCalculate = theTempID.CalculateDigest(m_strSourceForNymID);
    OT_ASSERT(bCalculate);
    // ---------------------------------------
    const OTString strNymID(theTempID);
    if (false == m_strNymID.Compare(strNymID))
    {
        OTLog::vOutput(0, "%s: Failure: When the NymID's source is hashed, the result doesn't match the expected NymID.\n"
                       "Expected: %s\n   Found: %s\n  Source: %s\n", __FUNCTION__, m_strNymID.Get(), strNymID.Get(),
                       m_strSourceForNymID.Get());
        return false;
    }
    // ---------------------------------------
    return true;
}


// Call VerifyNymID. Then verify m_strMasterCredID against the hash of
// m_pOwner->GetMasterkey().GetPubCredential() (the master credential.) Verify that
// m_pOwner->GetMasterkey() and *this have the same NymID. Then verify the
// signature of m_pOwner->GetMasterkey().
//
bool OTSubcredential::VerifyInternally()
{
    OT_ASSERT(NULL != m_pOwner);
    // ---------------------------------------
    // Verify that m_strNymID is the same as the hash of m_strSourceForNymID.
    //
    if (false == this->VerifyNymID())
        return false;
    // ---------------------------------------
    // Verify that m_pOwner->GetMasterkey() and *this have the same NymID.
    //
    if (false == m_strNymID.Compare(m_pOwner->GetMasterkey().GetNymID()))
    {
        OTLog::vOutput(0, "%s: Failure: The actual master credential's NymID doesn't match the NymID on this subcredential.\n"
                       "    This NymID: %s\nMaster's NymID: %s\n My Master Cred ID: %s\n", __FUNCTION__,
                       m_strNymID.Get(), m_pOwner->GetMasterkey().GetNymID().Get(),
                       m_strMasterCredID.Get());
        return false;
    }
    // ---------------------------------------
    // Verify m_strMasterCredID against the hash of m_pOwner->GetMasterkey().GetPubCredential()
    // (the master credentialID is a hash of the master credential.)
    //
    OTIdentifier theActualMasterID;
    const bool bCalcMasterCredID = theActualMasterID.CalculateDigest(m_pOwner->GetPubCredential());
    OT_ASSERT(bCalcMasterCredID);
    const OTString strActualMasterID(theActualMasterID);
 
    if (false == m_strMasterCredID.Compare(strActualMasterID))
    {
        OTLog::vOutput(0, "%s: Failure: When the actual Master Credential is hashed, the "
                       "result doesn't match the expected Master Credential ID.\n"
                       "Expected: %s\n   Found: %s\nMaster Cred:\n%s\n", __FUNCTION__,
                       m_strMasterCredID.Get(), strActualMasterID.Get(),
                       m_pOwner->GetPubCredential().Get());
        return false;
    }
    // ---------------------------------------
    // Then verify the signature of m_pOwner->GetMasterkey()...
    // Let's get a few things straight:
    // * OTMasterkey is a key (derived from OTKeyCredential, derived from OTSubcredential) and it can only sign itself.
    // * The only further verification a Masterkey can get is if its hash is posted at the source. Or, if the source
    //   is a public key, then the master key must be signed by the corresponding private key. (Again: itself.)
    // * Conversely to a master key which can ONLY sign itself, all subkeys must ALSO sign themselves.
    //
    // * Thus: Any OTKeyCredential (both master and subkeys, but no other credentials) must ** sign itself.**
    // * Whereas m_strMasterSigned is only used by OTSubkey, and thus only must be verified there.
    // * Any OTSubcredential must also be signed by its master. (Except masters, which already sign themselves.)
    // * Any OTMasterkey must (at some point, and/or regularly) verify against its own source.
    //
    // -----------------
    // * Any OTSubcredential must also be signed by its master. (Except masters, which already sign themselves.)
    //
    if (false == this->VerifySignedByMaster())
    {
        OTLog::vOutput(0, "%s: Failure: This subcredential hasn't been signed by its master credential.\n",
                       __FUNCTION__);
        return false;
    }
    // ---------------------------------------
    return true;
}


bool OTSubcredential::VerifySignedByMaster()
{
    OT_ASSERT(NULL != m_pOwner);
    return this->VerifyWithKey(m_pOwner->GetMasterkey().m_SigningKey.GetPublicKey());
}


bool OTSubcredential::VerifyContract()
{
	if (false == this->VerifyContractID())
	{
		OTLog::vOutput(1, "%s: Failed verifying credential ID against whatever it was expected to be.\n",
                       __FUNCTION__);
		return false;
	}
    // -------------------------------------
	if (false == this->VerifyInternally()) // Logs copiously.
        return false;
    // -------------------------------------
    return true;
}


// Overriding from OTContract.
void OTSubcredential::CalculateContractID(OTIdentifier & newID)
{
	if (!newID.CalculateDigest(this->GetPubCredential()))
		OTLog::vError("%s: Error calculating credential digest.\n", __FUNCTION__);
}


// I needed this for exporting a Nym (with credentials) from the wallet.
const OTString & OTSubcredential::GetPriCredential() const
{
    OT_ASSERT_MSG(m_mapPrivateInfo.size() > 0, "ASSERT: GetPriCredential can only be called on private subcredentials.");
    
    return m_strRawFile;
}


// We don't want to have to figure this out each time we need the public credential, so we just
// call this function wherever we need to get the public credential.
//
const OTString & OTSubcredential::GetPubCredential()  const  // More intelligent version of GetContents. Higher level.
{
    // If this is a private (client-side) credential containing private keys,
    // then the public version is stored in GetContents(), and return that.
    if ((m_mapPrivateInfo.size() > 0) && this->GetContents().Exists())
        return this->GetContents();
    
    // Otherwise this is a server-side copy of a Nym's credential, with no private keys inside it.
    // In which case public info that would have been in GetContents (making room so we can have
    // the private keys in m_strRawFile) is now directly found in m_strRawFile, since that's all the
    // server ever loads up. There is only public info and nothing else, so it's found in the main
    // normal location, m_strRawFile.
    //
    return m_strRawFile;
}
