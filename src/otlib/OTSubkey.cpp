/************************************************************
 *
 *  OTSubkey.cpp
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

#include "OTSubkey.hpp"

#include "OTASCIIArmor.hpp"
#include "OTCredential.hpp"
#include "OTLog.hpp"

#include "irrxml/irrXML.hpp"


// return -1 if error, 0 if nothing, and 1 if the node was processed.
//
int32_t OTSubkey::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	int32_t nReturnVal = ot_super::ProcessXMLNode(xml);
	
	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do in the case of OTAccount.
    //
	if (0 != nReturnVal)
       return nReturnVal;
	// else it was 0 (continue...)
    // --------------------------------------------------
    const OTString strNodeName(xml->getNodeName());
    // --------------------------------------------------
	if (strNodeName.Compare("keyCredential"))
	{
		m_strNymID			= xml->getAttributeValue("nymID");
		m_strMasterCredID	= xml->getAttributeValue("masterCredentialID");
		
		OTLog::Output(1, "Loading keyCredential...\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("masterSigned"))
	{
		if (false == OTContract::LoadEncodedTextField(xml, m_strMasterSigned))
		{
			OTLog::vError("Error in %s line %d: failed loading expected master-signed version while loading keyCredential.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
		}
		
		nReturnVal = 1;
	}
	// ------------------
	return nReturnVal;
}


void OTSubkey::UpdateContents()
{
	m_xmlUnsigned.Release();
    
	m_xmlUnsigned.Concatenate("<keyCredential nymID=\"%s\"\n" // a hash of the nymIDSource
							  " masterCredentialID=\"%s\" >\n\n", // Hash of the master credential that signed this subcredential.
							  this->GetNymID().Get(), this->GetMasterCredID().Get());
    
    if (this->GetNymIDSource().Exists())
    {
        OTASCIIArmor ascSource;
        ascSource.SetString(this->GetNymIDSource()); // A nym should always verify through its own source. (Whatever that may be.)
        m_xmlUnsigned.Concatenate("<nymIDSource>\n%s</nymIDSource>\n\n", ascSource.Get());
    }
    // --------------------------------------------
    // MASTER-SIGNED INFO
    //
    if ((OTSubcredential::credMasterSigned == m_StoreAs) || // MASTER-SIGNED INFO
        (OTSubcredential::credPrivateInfo  == m_StoreAs))
    {
        // --------------------------------------------
        this->UpdateMasterPublicToString(m_xmlUnsigned);
        // --------------------------------------------
        this->UpdatePublicContentsToString(m_xmlUnsigned);
    }
    // --------------------------------------------
    // PUBLIC INFO
    //
    if ((OTSubcredential::credPublicInfo  == m_StoreAs)  || // PUBLIC INFO (signed by subkey, contains master signed info.)
        (OTSubcredential::credPrivateInfo == m_StoreAs))
    {
        OTASCIIArmor ascMasterSigned(this->GetMasterSigned()); // GetMasterSigned() returns the contract containing the master-signed contents from the above block.
        m_xmlUnsigned.Concatenate("<masterSigned>\n%s</masterSigned>\n\n", // Contains all the public info, signed by the master key.
                                  ascMasterSigned.Get());                  // Packaged up here inside a final, subkey-signed credential.
    }
	// -------------------------------------------------
    // PRIVATE INFO
    //
    // If we're saving the private credential info...
    // 
    if (OTSubcredential::credPrivateInfo == m_StoreAs)  // PRIVATE INFO
    {
        this->UpdatePublicCredentialToString(m_xmlUnsigned);
        // -------------------------------------
        this->UpdatePrivateContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------	
	m_xmlUnsigned.Concatenate("</keyCredential>\n");
    // --------------------------------------------
    m_StoreAs = OTSubcredential::credPrivateInfo;  // <=== SET IT BACK TO DEFAULT BEHAVIOR. Any other state processes ONCE, and then goes back to this again.
}


bool OTSubkey::VerifySignedByMaster()
{
    // See if m_strMasterSigned was signed by my master credential.
    //
    OTSubkey theMasterSigned(*(this->m_pOwner));
    
    if (m_strMasterSigned.Exists() && theMasterSigned.LoadContractFromString(m_strMasterSigned))
    {
        // Here we need to MAKE SURE that the "master signed" version contains the same
        // CONTENTS as the actual version.
        
        if (false == this->GetNymID().Compare(theMasterSigned.GetNymID()))
        {
            OTLog::vOutput(0, "%s: Failure, NymID of this key credential doesn't match NymID of master-signed version of this key credential.\n", __FUNCTION__);
            return false;
        }
        
        if (false == this->GetNymIDSource().Compare(theMasterSigned.GetNymIDSource()))
        {
            OTLog::vOutput(0, "%s: Failure, NymIDSource of this key credential doesn't match NymIDSource of master-signed version of this key credential.\n", __FUNCTION__);
            return false;
        }
        
        if (false == this->GetMasterCredID().Compare(theMasterSigned.GetMasterCredID()))
        {
            OTLog::vOutput(0, "%s: Failure, MasterCredID of this key credential doesn't match MasterCredID of master-signed version of this key credential.\n", __FUNCTION__);
            return false;
        }
        
        if ((this->GetPublicMap().size() > 0) && (this->GetPublicMap() != theMasterSigned.GetPublicMap()))
        {
            OTLog::vOutput(0, "%s: Failure, public info of this key credential doesn't match public info of master-signed version of this key credential.\n", __FUNCTION__);
            return false;
        }

        // Master-signed version of subkey does not contain the private keys, since normally the master is signing
        // the public version of the sub credential (to validate it) and you don't want the public seeing your private keys.
        // So we would never expect these to match, since the master signed version should have no private keys in it.
        //
//        if (this->GetPrivateMap() != theMasterSigned.GetPrivateMap())
//        {
//            OTLog::vOutput(0, "%s: Failure, private info of this key credential doesn't match private info of master-signed version of this key credential.\n", __FUNCTION__);
//            return false;
//        }
        
        const bool bVerifiedWithKey = theMasterSigned.VerifyWithKey(m_pOwner->GetMasterkey().m_SigningKey.GetPublicKey());
        
        // ON SERVER SIDE, THE ACTUAL SUBKEY doesn't have any public key, only the master-signed version of it.
        // (The master-signed version being basically the only contents of the public version.)
        // So we need to be able to, after verifying, load up those contents so they are available on the
        // subkey itself, and not just on some master-signed version of itself hidden inside itself.
        // Otherwise I would have to load up the master-signed version anytime the server-side wanted to
        // mess with any of the keys.
        // Thus: copy the public info from master signed, to *this, if the above call was successful
        //
        if (bVerifiedWithKey && (0 == this->GetPublicMap().size()))
            return this->SetPublicContents(theMasterSigned.GetPublicMap());    // For master credential.

        return bVerifiedWithKey;
    } // if (m_strMasterSigned.Exists() && theMasterSigned.LoadContractFromString(m_strMasterSigned))
    
    return false;
}


OTSubkey::OTSubkey() : ot_super()
{
    m_strContractType = "KEY CREDENTIAL";
}


OTSubkey::OTSubkey(OTCredential & theOwner) : ot_super(theOwner)
{
    m_strContractType = "KEY CREDENTIAL";    
}


OTSubkey::~OTSubkey() { }
