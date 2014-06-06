/************************************************************
 *
 *  OTMasterkey.cpp
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

#include "OTMasterkey.hpp"

#include "OTASCIIArmor.hpp"
#include "OTCredential.hpp"
#include "OTLog.hpp"

#include "irrxml/irrXML.hpp"


// return -1 if error, 0 if nothing, and 1 if the node was processed.
//
int32_t OTMasterkey::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
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
	if (strNodeName.Compare("masterCredential"))
	{
		m_strNymID = xml->getAttributeValue("nymID");

		m_strMasterCredID.Release();
		
		OTLog::Output(1, "Loading masterCredential...\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	return nReturnVal;
}


void OTMasterkey::UpdateContents() 
{
	m_xmlUnsigned.Release();
    
	m_xmlUnsigned.Concatenate("<masterCredential nymID=\"%s\" >\n\n", // a hash of the nymIDSource
							  this->GetNymID().Get());
    
    if (this->GetNymIDSource().Exists())
    {
        OTASCIIArmor ascSource;
        ascSource.SetString(this->GetNymIDSource()); // A nym should always verify through its own source. (Whatever that may be.)
        m_xmlUnsigned.Concatenate("<nymIDSource>\n%s</nymIDSource>\n\n", ascSource.Get());
    }
    // --------------------------------------------
    // PUBLIC INFO
    //
//  if (OTSubcredential::credPublicInfo == m_StoreAs)   // PUBLIC INFO  (Always save this in every state.)
    {        
        this->UpdatePublicContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------
    // PRIVATE INFO
    //
    // If we're saving the private credential info...
    // 
    if (OTSubcredential::credPrivateInfo == m_StoreAs)   // PRIVATE INFO
    {
        this->UpdatePublicCredentialToString(m_xmlUnsigned);
        // -------------------------------------
        this->UpdatePrivateContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------	
	m_xmlUnsigned.Concatenate("</masterCredential>\n");
    // --------------------------------------------
    m_StoreAs = OTSubcredential::credPrivateInfo;  // <=== SET IT BACK TO DEFAULT BEHAVIOR. Any other state processes ONCE, and then goes back to this again.
}


// Verify that m_strNymID is the same as the hash of m_strSourceForNymID. Also verify that
// *this == m_pOwner->GetMasterkey() (the master credential.) Verify the (self-signed)
// signature on *this.
//
bool OTMasterkey::VerifyInternally()
{
    // Verify that m_strNymID is the same as the hash of m_strSourceForNymID.
    //
    // We can't use super here, since OTSubcredential::VerifyInternally will verify
    // m_strMasterCredID against the actual Master, which is not relevant to us in
    // OTMasterkey. But this means if we need anything else that OTKeyCredential::VerifyInternally
    // was doing, we will have to duplicate that here as well...
//  if (false == ot_super::VerifyInternally())
//      return false;
    if (false == this->VerifyNymID())
        return false;
    // ---------------------------------------
    OT_ASSERT(NULL != m_pOwner);
    // Verify that *this == m_pOwner->GetMasterkey() (the master credential.)
    //
    if (this != &(m_pOwner->GetMasterkey()))
    {
        OTLog::vOutput(0, "%s: Failure: Expected *this object to be the same as m_pOwner->GetMasterkey(), "
                       "but it wasn't.\n", __FUNCTION__);
        return false;
    }
    // ---------------------------------------
    // Remember this note above: ...if we need anything else that OTKeyCredential::VerifyInternally
    // was doing, we will have to duplicate that here as well...
    // Since we aren't calling OTKeyCredential::VerifyInternally (the super) and since that function
    // verifies that the credential is self-signed, we must do the same verification here:
    //
    // Any OTKeyCredential (both master and subkeys, but no other credentials) must ** sign itself.**
    //
    if (false == this->VerifySignedBySelf())
    {
        OTLog::vOutput(0, "%s: Failed verifying master credential: it's not signed by itself (its own signing key.)\n",
                       __FUNCTION__);
        return false;
    }
    // ---------------------------------------
    return true;
}


// Should actually curl the URL, or lookup the blockchain value, or verify Cert against
// Cert Authority, etc. Due to the network slowdown of this step, we will eventually make
// a separate identity verification server.
//
bool OTMasterkey::VerifyAgainstSource() const
{
    // RULE: *Any* source except for a public key, will begin with a
    // protocol specifier. Such as:
    //
    // http:        (a normal URL)
    // https:       (a normal URL on https)
    // bitcoin:     (a bitcoin address)
    // namecoin:    (a namecoin address)
    // i2p:         (an i2p address)
    // tor:         (a tor address)
    // freenet:     (a freenet address)
    // cert:        (Subject and Issuer DN from the cert)
    //
    // If NO protocol specifier is found, the source is assumed
    // to be a public key.
    // Public key is the default because that's the original behavior
    // of OT anyway: the public key was hashed to form the NymID. We will
    // continue to support this as a default, but now we are additionally
    // also allowing other sources such as Namecoin, Freenet, etc. As int64_t
    // as a Nym's source hashes to its correct ID, and as long as its master
    // credentials can be verified from that same source, then all master
    // credentials can be verified (as well as subcredentials) from any source
    // the user prefers.
    //
    // ---------------------------------
    bool bVerified = false;
    // ---------------------------------
    const std::string str_raw_source(m_strSourceForNymID.Get());
    std::string str_source;
    
    // It's a URL.
    if (str_raw_source.compare(0,5,"http:")  == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+5, str_raw_source.end());
        bVerified = this->VerifySource_HTTP(str_source.c_str());
    }
    else if (str_raw_source.compare(0,6,"https:")  == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+6, str_raw_source.end());
        bVerified = this->VerifySource_HTTPS(str_source.c_str());
    }
    // It's a Bitcoin address.
    else if (str_raw_source.compare(0,8,"bitcoin:") == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+8, str_raw_source.end());
        bVerified = this->VerifySource_Bitcoin(str_source.c_str());
    }
    // It's a Namecoin address.
    else if (str_raw_source.compare(0,9,"namecoin:") == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+9, str_raw_source.end());
        bVerified = this->VerifySource_Namecoin(str_source.c_str());
    }
    // It's a Freenet URL.
    else if (str_raw_source.compare(0,8,"freenet:") == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+8, str_raw_source.end());
        bVerified = this->VerifySource_Freenet(str_source.c_str());
    }
    // It's a Tor URL.
    else if (str_raw_source.compare(0,4,"tor:") == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+4, str_raw_source.end());
        bVerified = this->VerifySource_TOR(str_source.c_str());
    }
    // It's an I2P URL.
    else if (str_raw_source.compare(0,4,"i2p:") == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+4, str_raw_source.end());
        bVerified = this->VerifySource_I2P(str_source.c_str());
    }
    // It's the Issuer/Subject DN info from a cert issued by a traditional certificate authority.
    else if (str_raw_source.compare(0,5,"cert:") == 0)
    {
        str_source.insert(str_source.begin(), str_raw_source.begin()+5, str_raw_source.end());
        bVerified = this->VerifySource_CA(str_source.c_str());
    }
    else // It's presumably a public key.
    {
        str_source = str_raw_source;
        bVerified = this->VerifySource_Pubkey(str_source.c_str());
    }
    // -----------------------------------------------------------------
    return bVerified;
}


bool OTMasterkey::VerifySource_HTTP(const OTString strSource) const
{
    /*
     The source is a URL, http://blah.com/folder
     If I download files from there, will I find my own masterkey inside?
     If so, then I verify.
     */
    
    OTLog::vError("%s: Failure: this function has not yet been written, so this HTTP source cannot be verified.\n",
                  __FUNCTION__);
//    return false;
    
    // Todo security
    OTLog::vError("\nNOTE: Returning TRUE for TESTING PURPOSES, as if HTTP source had verified."
                  "\n\n\n ----------------------- \n\n");

    return true;
}


bool OTMasterkey::VerifySource_HTTPS(const OTString strSource) const
{
    /*
     The source is a URL, https://blah.com/folder
     If I download files from there, will I find my own masterkey inside?
     If so, then I verify.
     */

    OTLog::vError("%s: Failure: this function has not yet been written, so this HTTPS source cannot be verified.\n",
                  __FUNCTION__);
//    return false;

    // Todo security
    OTLog::vError("\nNOTE: Returning TRUE for TESTING PURPOSES, as if HTTPS source had verified."
                  "\n\n\n ----------------------- \n\n");
    
    return true;
}


bool OTMasterkey::VerifySource_Bitcoin(const OTString strSource) const
{
    /*
     The source is a Bitcoin address
     The last transfer from that address should have memo data with the hash of the master credential.
     I compare that to my own ID and they should match.
     Alternately, to support multiple master credentials, have the last transfer go to multiple addresses,
     and each should have a memo with the master cred ID for each credential, one of which should match my own.
     If so, then I verify.
     */

    OTLog::vError("%s: Failure: this function has not yet been written, so this Bitcoin source cannot be verified.\n",
                  __FUNCTION__);
//    return false;

    // Todo security
    OTLog::vError("\nNOTE: Returning TRUE for TESTING PURPOSES, as if Bitcoin had verified."
                  "\n\n\n ----------------------- \n\n");
    
    return true;
}


bool OTMasterkey::VerifySource_Namecoin(const OTString strSource) const
{
    /*
     The source is a URL, http://blah.bit/folder
     If I download files from there, will I find my own masterkey inside?
     If so, then I verify.
     */

    OTLog::vError("%s: Failure: this function has not yet been written, so this Namecoin source cannot be verified.\n",
                  __FUNCTION__);
//    return false;

    // Todo security
    OTLog::vError("\nNOTE: Returning TRUE for TESTING PURPOSES, as if Namecoin had verified."
                  "\n\n\n ----------------------- \n\n");
    
    return true;
}


bool OTMasterkey::VerifySource_Freenet(const OTString strSource) const
{
    OTLog::vError("%s: Failure: this function has not yet been written, so this Freenet source cannot be verified.\n",
                  __FUNCTION__);
    return false;
}


bool OTMasterkey::VerifySource_TOR(const OTString strSource) const
{
    OTLog::vError("%s: Failure: this function has not yet been written, so this Tor source cannot be verified.\n",
                  __FUNCTION__);
    return false;
}


bool OTMasterkey::VerifySource_I2P(const OTString strSource) const
{
    OTLog::vError("%s: Failure: this function has not yet been written, so this I2P source cannot be verified.\n",
                  __FUNCTION__);
    return false;
}


bool OTMasterkey::VerifySource_CA(const OTString strSource) const
{
    
    /*
     The Source is the DN info on the Cert.
     Therefore look at the Cert being used in this Masterkey.
     Does it have the same DN info? Does it verify through its CA ?
     Then it verifies.
     */
    
    OTLog::vError("%s: Failure: this function has not yet been written, so this CA source cannot be verified.\n",
                  __FUNCTION__);
    return false;
}


bool OTMasterkey::VerifySource_Pubkey(const OTString strSource) const
{
    // Verify signed by self.
    //
    // Note: Whenever VerifyAgainstSource is called, VerifyInternally is also called.
    // And VerifyInternally, for all OTKeyCredentials, verifies already that the
    // credential has been signed by its own private signing key.
    // Since the credential is already verified as having signed itself, there's no
    // reason to verify that redundantly here, so we just return true.
    //
    return true;
}


OTMasterkey::OTMasterkey() : ot_super()
{
    m_strContractType = "MASTER KEY CREDENTIAL";    
}


OTMasterkey::OTMasterkey(OTCredential & theOwner) : ot_super(theOwner)
{
    m_strContractType = "MASTER KEY CREDENTIAL";    
}


OTMasterkey::~OTMasterkey() { }
