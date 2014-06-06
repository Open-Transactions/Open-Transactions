/************************************************************
 *
 *  OTKeypair.cpp
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

#include "OTKeypair.hpp"

#include "OTAsymmetricKey.hpp"
#include "OTContract.hpp"
#include "OTFolders.hpp"
#include "OTLog.hpp"
#include "OTLowLevelKeyData.hpp"
#include "OTSignature.hpp"


// DONE: Add OTKeypair member for m_pMetadata.
// Add method to set the Metadata. Or instead of a member,
// just have the method set the public and private keys.
//
// Then a Subkey can have a similar function which sets the metadata
// for its three keypairs (they are identical except for the A|E|S.)
//
// When a Nym is loaded, load up its master credentials and all their
// subcredentials. Since their metadata was supposedly set properly at
// creation, verify it at load time.

// TODO: on OTNym, change GetPublicKey to GetPublicKeyForVerify or
// GetPublicKeyForEncrypt or GetPublicKeyForTransmission. Then
// rebuild so that all places using GetPublicKey are forced to choose
// one of those. Same with GetPrivateKeyForSigning, GetPrivateKeyForDecrypt,
// and GetPrivateKeyForAuthentication.

// DONE: add the methods to OTPseudonym for generating a master credential contract
// and a sub contract. Add ability to save / load with this data. Then go from there.

OTKeypair::OTKeypair() :
    m_pkeyPublic (OTAsymmetricKey::KeyFactory()),
    m_pkeyPrivate(OTAsymmetricKey::KeyFactory())
{
    
}


OTKeypair::~OTKeypair()
{
    // -----------------------------
    if (NULL != m_pkeyPublic)
        delete m_pkeyPublic; // todo: else error
	m_pkeyPublic	= NULL;
    // -----------------------------
    if (NULL != m_pkeyPrivate)
        delete m_pkeyPrivate; // todo: else error
	m_pkeyPrivate	= NULL;
    // -----------------------------
}


void OTKeypair::SetMetadata(const OTSignatureMetadata & theMetadata)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    OT_ASSERT(NULL != m_pkeyPrivate);
    OT_ASSERT(NULL != m_pkeyPublic-> m_pMetadata);
    OT_ASSERT(NULL != m_pkeyPrivate->m_pMetadata);
    // ------------------------------
    // Set it for both keys.
    //
    *(m_pkeyPublic-> m_pMetadata) = theMetadata;
    *(m_pkeyPrivate->m_pMetadata) = theMetadata;
}


bool OTKeypair::HasPublicKey()
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
	return m_pkeyPublic->IsPublic(); // This means it actually has a public key in it, or tried to.
}


bool OTKeypair::HasPrivateKey()
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
	return m_pkeyPrivate->IsPrivate(); // This means it actually has a private key in it, or tried to.
}


const OTAsymmetricKey & OTKeypair::GetPublicKey() const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
	return (*m_pkeyPublic);
}


const OTAsymmetricKey & OTKeypair::GetPrivateKey() const
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
	return (*m_pkeyPrivate);
}


bool OTKeypair::SaveCertToString(OTString & strOutput, const OTString * pstrReason/*=NULL*/, OTPassword * pImportPassword/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    OTString strCert, strReason(NULL == pstrReason ? "OTKeypair::SaveCertToString" : pstrReason->Get());
    
    const bool bSaved = m_pkeyPublic->SaveCertToString(strCert, &strReason, pImportPassword);
    // ---------------------------------------------------------------
	if (bSaved)
        strOutput = strCert;
	
	return bSaved;    
}


bool OTKeypair::SavePrivateKeyToString(OTString & strOutput, const OTString * pstrReason/*=NULL*/, OTPassword * pImportPassword/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    OTString strPrivateKey;
    
    const bool bSaved = m_pkeyPrivate->SavePrivateKeyToString(strPrivateKey, pstrReason, pImportPassword);
    // ---------------------------------------------------------------
	if (bSaved)
        strOutput = strPrivateKey;
	
	return bSaved;
}


bool OTKeypair::SaveCertAndPrivateKeyToString(OTString & strOutput, const OTString * pstrReason/*=NULL*/, OTPassword * pImportPassword/*=NULL*/)
{
    OTString strCert, strPrivateKey;
    
    const bool bSaved1 = this->SaveCertToString      (strCert,       pstrReason, pImportPassword);
    const bool bSaved2 = this->SavePrivateKeyToString(strPrivateKey, pstrReason, pImportPassword);
    // ---------------------------------------------------------------
	if (bSaved1 && bSaved2)
		strOutput.Format(const_cast<char*>("%s%s"), strPrivateKey.Get(), strCert.Get());
	
	return (bSaved1 && bSaved2);
}


bool OTKeypair::LoadCertAndPrivateKeyFromString(const OTString & strInput, const OTString * pstrReason/*=NULL*/, OTPassword * pImportPassword/*=NULL*/)
{
	// ---------------------------------------------------------------
    OT_ASSERT(strInput.Exists());
	// ---------------------------------------------------------------
    // "escaped" means pre-pended with "- " as in:   - -----BEGIN CER....
    //
    const bool bPublic  = this->LoadPublicKeyFromCertString (strInput,   false,  //bool bEscaped=true by default
                                                             pstrReason, pImportPassword);
    const bool bPrivate = this->LoadPrivateKeyFromCertString(strInput,   false,  //bool bEscaped=true by default,
                                                             pstrReason, pImportPassword);
    if (!bPublic)
    {
        OTLog::vError("%s: Although the input string apparently exists, "
                      "LoadPublicKeyFromCertString returned false.\n", __FUNCTION__);
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded public key from string.\n",
                       __FUNCTION__);
    }
    // ----------------
    if (!bPrivate)
    {
        OTLog::vError("%s: Although the input string apparently exists, "
                      "LoadPrivateKeyFromCertString returned false.\n", __FUNCTION__);
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded private key from string.\n", __FUNCTION__);
    }
    // ----------------
    return true;
}


bool OTKeypair::SaveAndReloadBothKeysFromTempFile(      OTString   * pstrOutputCert/*=NULL*/,
                                                  const OTString   * pstrReason/*=NULL*/,
                                                        OTPassword * pImportPassword/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    OTString    strOutput;
    const bool  bSuccess   = this->SaveCertAndPrivateKeyToString(strOutput, pstrReason, pImportPassword);
	// ---------------------------------------
	if (bSuccess)
	{
        // todo security. Revisit this part during security audit.
        //
		const OTString strFilename("temp.nym"); // todo stop hardcoding. Plus this maybe should select a random number too.
        
		if (false == OTDB::StorePlainString(strOutput.Get(), OTFolders::Cert().Get(), strFilename.Get())) // temp.nym
		{
			OTLog::vError("%s: Failure storing new cert in temp file: %s\n", __FUNCTION__, strFilename.Get());
			return false;
		}
		// ------------------------------------------
        if (false == this->LoadBothKeysFromCertFile(OTFolders::Cert().Get(), strFilename, pstrReason, pImportPassword))
            return false; // LoadBothKeysFromCertFile already has error logs, no need to log twice at this point.
		// ------------------------------------------
        if (NULL != pstrOutputCert)
            pstrOutputCert->Set(strOutput); // Success!
	}
	
	return bSuccess;   
}


// Load from local storage.
bool OTKeypair::LoadPrivateKey(const OTString & strFoldername,
                               const OTString & strFilename, const OTString * pstrReason/*=NULL*/, OTPassword * pImportPassword/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->LoadPrivateKey(strFoldername, strFilename, pstrReason, pImportPassword);
}


bool OTKeypair::LoadPublicKey (const OTString & strFoldername,
                               const OTString & strFilename)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->LoadPublicKey(strFoldername, strFilename);
}


// LoadPrivateKeyFromCertString
//
// "escaped" means pre-pended with "- " as in:   - -----BEGIN CERTIFICATE....
//
bool OTKeypair::LoadPrivateKeyFromCertString(const OTString & strCert,
                                             bool bEscaped/*=true*/,
                                             const OTString * pstrReason/*=NULL*/,
                                             OTPassword * pImportPassword/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->LoadPrivateKeyFromCertString(strCert, bEscaped, pstrReason, pImportPassword);
}


// Load Public Key from Cert (file or string)
//
bool OTKeypair::LoadPublicKeyFromCertString(const OTString   & strCert, bool bEscaped/*=true*/,
                                            const OTString   * pstrReason/*=NULL*/,
                                                  OTPassword * pImportPassword/*=NULL*/) // DOES handle bookends, AND escapes.
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->LoadPublicKeyFromCertString(strCert, bEscaped, pstrReason, pImportPassword);
}


bool OTKeypair::LoadPublicKeyFromCertFile(const OTString   & strFoldername,
                                          const OTString   & strFilename,
                                          const OTString   * pstrReason/*=NULL*/,
                                                OTPassword * pImportPassword/*=NULL*/) // DOES handle bookends.
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->LoadPublicKeyFromCertFile(strFoldername, strFilename, pstrReason, pImportPassword);
}


bool OTKeypair::MakeNewKeypair(int32_t nBits/*=1024*/)
{
    const char * szFunc = "OTKeypair::MakeNewKeypair";
	// ---------------------------------------------------------------
    OT_ASSERT(NULL != m_pkeyPrivate);
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    OTLowLevelKeyData lowLevelData;
    
    if (!lowLevelData.MakeNewKeypair(nBits))
    {
        OTLog::vError("%s: Failed in a call to OTLowLevelKeyData::MakeNewKeypair(%d).\n",
                      szFunc, nBits);
        return false;
    }
    // ---------------------------------------------------------------
    return lowLevelData.SetOntoKeypair(*this);
    
    // If true is returned:
    // Success! At this point, theKeypair's public and private keys have been set.
    // Keep in mind though, they still won't be "quite right" until saved and loaded
    // again, at least according to existing logic. That saving/reloading is currently
    // performed in OTPseudonym::GenerateNym().
}


bool OTKeypair::LoadBothKeysFromCertFile(const OTString   & strFoldername,
                                         const OTString   & strFilename,
                                         const OTString   * pstrReason/*=NULL*/,
                                               OTPassword * pImportPassword/*=NULL*/)
{
    const char * szFunc = "OTKeypair::LoadBothKeysFromCertFile";
    // -------------------------------------
    OT_ASSERT(NULL != m_pkeyPublic);
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    bool bPublic  = false;
    bool bPrivate = false;
    
    bPublic  = m_pkeyPublic-> LoadPublicKeyFromCertFile (strFoldername.Get(), strFilename.Get(),
                                                         pstrReason, pImportPassword);
    bPrivate = m_pkeyPrivate->LoadPrivateKey            (strFoldername.Get(), strFilename.Get(),
                                                         pstrReason, pImportPassword);
    if (!bPublic)
    {
        OTLog::vError("%s: Although the ascii-armored file (%s) was read, LoadPublicKeyFromCert "
                      "returned false.\n", szFunc, strFilename.Get());
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded public key from Certfile: %s\n",
                       szFunc, strFilename.Get());
    }
    // -----------------
    if (!bPrivate)
    {
        OTLog::vError("%s: Although the ascii-armored file (%s) was read, LoadPrivateKey returned false.\n",
                      szFunc, strFilename.Get());
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded private key from certfile: %s\n",
                       szFunc, strFilename.Get());
    }
    // -----------------------------------------
    return true;
}


bool OTKeypair::SignContract(OTContract & theContract, OTPasswordData  * pPWData/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // --------------------------------------------
    return theContract.SignWithKey(*m_pkeyPrivate, pPWData);
}


// PUBLIC KEY

// * Get the public key in ASCII-armored format                 -- OTASCIIArmor
// * Get the public key in ASCII-armored format WITH bookends   -- OTString
//       - ------- BEGIN PUBLIC KEY --------
//       Notice the "- " before the rest of the bookend starts.
//
bool OTKeypair::GetPublicKey(OTASCIIArmor & strKey) const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->GetPublicKey(strKey);
}


bool OTKeypair::GetPublicKey(OTString & strKey, bool bEscaped/*=true*/) const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->GetPublicKey(strKey, bEscaped);
}


// (Below) Decodes a public key from ASCII armor into an actual key pointer
// and sets that as the m_pKey on this object.
//
bool OTKeypair::SetPublicKey(const OTASCIIArmor & strKey)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->SetPublicKey(strKey);
}


// Decodes a public key from bookended key string into an actual key
// pointer, and sets that as the m_pkeyPublic on this object.
// This is the version that will handle the bookends ( -----BEGIN PUBLIC KEY-----)
//
bool OTKeypair::SetPublicKey(const OTString & strKey, bool bEscaped/*=false*/)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    
    // ---------------------------------------------------------------
    if (strKey.Contains("PGP PUBLIC KEY"))
	{
		OTASCIIArmor theArmor;
		
		if (theArmor.LoadFromString(const_cast<OTString &>(strKey), bEscaped))
		{
			// This function expects that the bookends are already removed.
			// The ascii-armor loading code removes them and handles the escapes also.
			return m_pkeyPublic->LoadPublicKeyFromPGPKey(theArmor);
		}
		else
        {
			OTLog::Output(2, "OTKeypair::SetPublicKey: Failed extracting PGP public key from ascii-armored text.\n");
			return false;
		}
	}
	else // the below function SetPublicKey (in the return call) expects the
        // bookends to still be there, and it will handle removing them. (Unlike PGP code above.)
		return m_pkeyPublic->SetPublicKey(strKey, bEscaped);
}


// PRIVATE KEY
// Get the private key in ASCII-armored format with bookends
// - ------- BEGIN ENCRYPTED PRIVATE KEY --------
// Notice the "- " before the rest of the bookend starts.
//
bool OTKeypair::GetPrivateKey(OTString & strKey, bool bEscaped/*=true*/) const
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->GetPrivateKey(strKey, bEscaped);
}


bool OTKeypair::GetPrivateKey(OTASCIIArmor & strKey) const  // Get the private key in ASCII-armored format
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->GetPrivateKey(strKey);
}


// Decodes a private key from ASCII armor into an actual key pointer
// and sets that as the m_pPrivateKey on this object.
// This is the version that will handle the bookends ( -----BEGIN ENCRYPTED PRIVATE KEY-----)
bool OTKeypair::SetPrivateKey(const OTString & strKey, bool bEscaped/*=false*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    const char * szOverride = "PGP PRIVATE KEY";

	if (strKey.Contains(szOverride))
	{
		OTASCIIArmor theArmor;
        
		if (theArmor.LoadFromString(const_cast<OTString &>(strKey), bEscaped,
                                    szOverride)) // szOverride == "PGP PRIVATE KEY"
		{
			// This function expects that the bookends are already removed.
			// The ascii-armor loading code removes them and handles the escapes also.
//			return m_pkeyPrivate->LoadPrivateKeyFromPGPKey(theArmor);
            //
			OTLog::vOutput(0, "OTKeypair::SetPrivateKey 1: Failure: PGP private keys are NOT YET SUPPORTED.\n\n");
//			OTLog::vOutput(0, "OTKeypair::SetPrivateKey 1: Failure: PGP private keys are NOT YET SUPPORTED:\n\n%s\n\n",
//                           strKey.Get());
			return false;
		}
		else 
        {
			OTLog::vOutput(0, "OTKeypair::SetPrivateKey 2: Failure: PGP private keys are NOT YET SUPPORTED.\n\n");
//			OTLog::vOutput(0, "OTKeypair::SetPrivateKey 2: Failure: PGP private keys are NOT YET SUPPORTED:\n\n%s\n\n",
//                           strKey.Get());
			return false;
		}
	}
	else // the below function SetPrivateKey (in the return call) expects the
         // bookends to still be there, and it will handle removing them. (Unlike PGP code above.)
        //
		return m_pkeyPrivate->SetPrivateKey(strKey, bEscaped);
}


bool OTKeypair::SetPrivateKey(const OTASCIIArmor & strKey) // Decodes a private key from ASCII armor into an actual key pointer and sets that as the m_pKey on this object.
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->SetPrivateKey(strKey);
}


bool OTKeypair::CalculateID(OTIdentifier & theOutput) const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->CalculateID(theOutput); // Only works for public keys.
}


int32_t OTKeypair::GetPublicKeyBySignature(listOfAsymmetricKeys & listOutput, // Inclusive means, return the key even when theSignature has no metadata.
                                       const OTSignature & theSignature, bool bInclusive/*=false*/) const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    OT_ASSERT(NULL != m_pkeyPublic->m_pMetadata);
    
    // We know that EITHER exact metadata matches must occur, and the signature MUST have metadata, (bInclusive=false)
    // OR if bInclusive=true, we know that metadata is still used to eliminate keys where possible, but that otherwise,
    // if the signature has no metadata, then the key is still returned, "just in case."
    //
    if ((false == bInclusive) && (false == theSignature.m_metadata.HasMetadata()))
        return 0;
    // -------------------------
    // Below this point, metadata is used if it's available.
    // It's assumed to be "okay" if it's not available, since any non-inclusive
    // calls would have already returned by now, if that were the case.
    // (But if it IS available, then it must match, or the key won't be returned.)
    //
    if ((false == theSignature.m_metadata.HasMetadata())    || // If the signature has no metadata,
        (false == m_pkeyPublic->m_pMetadata->HasMetadata()) || // Or if m_pkeyPublic has no metadata,
        (m_pkeyPublic->m_pMetadata->HasMetadata() &&           // OR if they BOTH have metadata, and
         theSignature.m_metadata.   HasMetadata() &&           // their metadata is a MATCH...
         (theSignature.m_metadata == *(m_pkeyPublic->m_pMetadata)) ) )
    {
        // ...Then add m_pkeyPublic as a possible match, to listOutput.
        //
        listOutput.push_back(m_pkeyPublic);
        return 1;
    }
    return 0;
}


// Used when importing/exporting a Nym to/from the wallet.
//
bool OTKeypair::ReEncrypt(OTPassword & theExportPassword, bool bImporting, OTString & strOutput)
{
    // --------------------------------------
    OT_ASSERT(NULL != m_pkeyPublic );
    OT_ASSERT(NULL != m_pkeyPrivate);
    // --------------------------------------
    OT_ASSERT(this->HasPublicKey() );
    OT_ASSERT(this->HasPrivateKey());
    // --------------------------------------
    // If we were importing, we were in the exported format but now we're in the internal format.
    // Therefore we want to use the wallet's internal cached master passphrase to save. Therefore
    // strReason will be used for the import case.
    //
    // But if we were exporting, then we were in the internal format and just re-encrypted to the
    // export format. So we'd want to pass the export passphrase when saving.
    //    
    const OTString strReasonAbove(bImporting ?
                                  "Enter the new export passphrase. (Above ReEncryptPrivateKey in OTKeypair::ReEncrypt)" :
                                  "Enter your wallet's master passphrase. (Above ReEncryptPrivateKey in OTKeypair::ReEncrypt)");

    const OTString strReasonBelow(bImporting ?
                                  "Enter your wallet's master passphrase. (Below ReEncryptPrivateKey in OTKeypair::ReEncrypt)" :
                                  "Enter the new export passphrase. (Below ReEncryptPrivateKey in OTKeypair::ReEncrypt)");
    // --------------------------------------
    // At this point the public key was loaded from a public key, not a cert,
    // but the private key was loaded from the cert. Therefore we'll save the
    // public cert from the private key, and then use that to reload the public
    // key after ReEncrypting. (Otherwise the public key would be there, but it
    // would be missing the x509, which is only available in the cert, not the
    // pubkey alone -- and without the x509 being there, the "SaveAndReload" call
    // below would fail.
    // Why don't I just stick the Cert itself into the public data, instead of
    // sticking the public key in there? Because not all key credentials will use
    // certs. Some will use pubkeys from certs, and some will use pubkeys not from
    // certs. But I might still just stick it in there, and code things to be able to
    // load either indiscriminately. After all, that's what I'm doing already in the
    // asset and server contracts. But even in those cases, there will be times when
    // only a pubkey is available, not a cert, so I'll probably still find myself having
    // to do this. Hmm...
    
    // ---------------------------------------
    
    const bool bReEncrypted = m_pkeyPrivate->ReEncryptPrivateKey(theExportPassword, bImporting); // <==== IMPORT or EXPORT occurs here.
          bool bGotCert = false;
    
    if (bReEncrypted)
    {
        // ------------------------------------------------
        // Keys won't be right until this happens. Todo: eliminate this need.
        bGotCert = this->SaveAndReloadBothKeysFromTempFile(&strOutput, &strReasonBelow,
                                                           bImporting ? NULL : &theExportPassword);
    }
    
    const bool bSuccess = (bReEncrypted && bGotCert);
    // --------------------------------------
    if (!bSuccess)
    {
        strOutput.Release();
        OTLog::vError("%s: Failure, either when re-encrypting, or when subsequently retrieving "
                      "the public/private keys. bImporting == %s\n", __FUNCTION__,
                      bImporting ? "true" : "false");
    }
    // --------------------------------------
    return bSuccess;
}
