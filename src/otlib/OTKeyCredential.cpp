/************************************************************
 *
 *  OTKeyCredential.cpp
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

#include "OTKeyCredential.hpp"

#include "OTCredential.hpp"
#include "OTLog.hpp"
#include "OTSignature.hpp"


bool OTKeyCredential::VerifySignedBySelf()
{
    return this->VerifyWithKey(m_SigningKey.GetPublicKey());
}


// NOTE: You might ask, if we are using theSignature's metadata to narrow down the key type,
// then why are we still passing the key type as a separate parameter? Good question. Because
// often, theSignature will have no metadata at all! In that case, normally we would just NOT
// return any keys, period. Because we assume, if a key credential signed it, then it WILL have
// metadata, and if it doesn't have metadata, then a key credential did NOT sign it, and therefore
// we know from the get-go that none of the keys from the key credentials will work to verify it,
// either. That's why, normally, we don't return any keys if theSignature has no metadata.
// BUT...Let's say you know this, that the signature has no metadata, yet you also still believe
// it may be signed with one of these keys. Further, while you don't know exactly which key it
// actually is, let's say you DO know by context that it's a signing key, or an authentication key,
// or an encryption key. So you specify that. In which case, OT should return all possible matching
// pubkeys based on that 1-letter criteria, instead of its normal behavior, which is to return all
// possible matching pubkeys based on a full match of the metadata.
//
int32_t OTKeyCredential::GetPublicKeysBySignature(listOfAsymmetricKeys & listOutput,
                                              const OTSignature & theSignature,
                                              char cKeyType/*='0'*/) const // 'S' (signing key) or 'E' (encryption key) or 'A' (authentication key)
{
    // Key type was not specified, because we only want keys that match the metadata on theSignature.
    // And if theSignature has no metadata, then we want to return 0 keys.
    if ((  '0' == cKeyType) &&
        (false == theSignature.m_metadata.HasMetadata()))
        return 0;
    // -----------------
    // By this point, we know that EITHER exact metadata matches must occur, and the signature DOES have metadata, ('0')
    // OR the search is only for 'A', 'E', or 'S' candidates, based on cKeyType, and that the signature's metadata
    // can additionally narrow the search down, if it's present, which in this case it's not guaranteed to be.
    int32_t nCount = 0;
    switch (cKeyType)
    {
            // Specific search only for signatures with metadata.
        case '0':
        {   // FYI, theSignature.m_metadata.HasMetadata() is true, in this case.
            // That's why I can just assume theSignature has a key type here:
            switch (theSignature.m_metadata.GetKeyType())
            {
                case 'A': nCount = m_AuthentKey.GetPublicKeyBySignature(listOutput, theSignature); break; // bInclusive=false by default
                case 'E': nCount = m_EncryptKey.GetPublicKeyBySignature(listOutput, theSignature); break; // bInclusive=false by default
                case 'S': nCount = m_SigningKey.GetPublicKeyBySignature(listOutput, theSignature); break; // bInclusive=false by default
                default: OTLog::vError("%s: Unexpected value for theSignature.m_metadata.GetKeyType: %c (failure)\n",
                                       __FUNCTION__, theSignature.m_metadata.GetKeyType()); return 0;
            }
            break;
        }
            // Generalized search which specifies key type and returns keys
            // even for signatures with no metadata. (When metadata is present,
            // it's still used to eliminate keys.)
        case 'A': nCount = m_AuthentKey.GetPublicKeyBySignature(listOutput, theSignature, true); break; // bInclusive=true
        case 'E': nCount = m_EncryptKey.GetPublicKeyBySignature(listOutput, theSignature, true); break; // bInclusive=true
        case 'S': nCount = m_SigningKey.GetPublicKeyBySignature(listOutput, theSignature, true); break; // bInclusive=true
        default:  OTLog::vError("%s: Unexpected value for cKeyType (should be 0, A, E, or S): %c\n",
                                __FUNCTION__, cKeyType); return 0;
    }
    return nCount;
}


// Verify that m_strNymID is the same as the hash of m_strSourceForNymID.
// Subkey verifies (master does not): NymID against Masterkey NymID, and master credential ID against hash of master credential.
// (How? Because OTMasterkey overrides this function and does NOT call the parent, whereas OTSubkey does.)
// Then verify the (self-signed) signature on *this.
//
bool OTKeyCredential::VerifyInternally()
{
    // Verify that m_strNymID is the same as the hash of m_strSourceForNymID. 
    if (false == ot_super::VerifyInternally())
        return false;
    // ---------------------------------------
    // Any OTKeyCredential (both master and subkeys, but no other credentials) must ** sign itself.**
    //
    if (false == this->VerifySignedBySelf())
    {
        OTLog::vOutput(0, "%s: Failed verifying key credential: it's not signed by itself (its own signing key.)\n",
                       __FUNCTION__);
        return false;
    }
    // ---------------------------------------
    return true;
}


// OTLog::vError("%s line %d: \n", __FILE__, __LINE__);

OTKeyCredential::OTKeyCredential()                        : ot_super()         { }
OTKeyCredential::OTKeyCredential(OTCredential & theOwner) : ot_super(theOwner) { }


OTKeyCredential::~OTKeyCredential()
{
    Release_Subkey();
}


//virtual
void OTKeyCredential::Release()
{
    Release_Subkey();   // My own cleanup is done here.
    
    // Next give the base class a chance to do the same...
	ot_super::Release(); // since I've overridden the base class, I call it now...
}
 

void OTKeyCredential::Release_Subkey()
{
    // Release any dynamically allocated members here. (Normally.)
}


bool OTKeyCredential::GenerateKeys(int32_t nBits/*=1024*/)       // Gotta start somewhere.
{
    const bool bSign = m_SigningKey.MakeNewKeypair(nBits);
    const bool bAuth = m_AuthentKey.MakeNewKeypair(nBits);
    const bool bEncr = m_EncryptKey.MakeNewKeypair(nBits);
    // ----------------------------------------------
    OT_ASSERT(bSign && bAuth && bEncr);
    // ----------------------------------------------
    m_SigningKey.SaveAndReloadBothKeysFromTempFile();  // Keys won't be right until this happens.
    m_AuthentKey.SaveAndReloadBothKeysFromTempFile();  // (Necessary evil until better fix.)
    m_EncryptKey.SaveAndReloadBothKeysFromTempFile();
    // ----------------------------------------------
    // Since the keys were all generated successfully, we need to copy their
    // certificate data into the m_mapPublicInfo and m_mapPrivateInfo (string maps.)
    //
    OTString     strPublicKey, strPrivateCert;
    mapOfStrings mapPublic,    mapPrivate;
    // ------------------------------------------
    const OTString strReason("Generating keys for new credential...");
    // ------------------------------------------                
    const bool b1 = m_SigningKey.GetPublicKey(strPublicKey, false); // bEscaped=true by default.
    const bool b2 = m_SigningKey.SaveCertAndPrivateKeyToString(strPrivateCert, &strReason);
    
    if (b1)
        mapPublic. insert(std::pair<std::string, std::string>("S", strPublicKey.Get()));
    if (b2)
        mapPrivate.insert(std::pair<std::string, std::string>("S", strPrivateCert.Get()));
    // ------------------------------------------------------------------------------------------
    strPublicKey.  Release();
    strPrivateCert.Release();
    const bool b3 = m_AuthentKey.GetPublicKey(strPublicKey, false); // bEscaped=true by default.
    const bool b4 = m_AuthentKey.SaveCertAndPrivateKeyToString(strPrivateCert, &strReason);                
    
    if (b3)
        mapPublic. insert(std::pair<std::string, std::string>("A", strPublicKey.Get()));
    if (b4)
        mapPrivate.insert(std::pair<std::string, std::string>("A", strPrivateCert.Get()));
    // ------------------------------------------------------------------------------------------
    strPublicKey.  Release();
    strPrivateCert.Release();
    const bool b5 = m_EncryptKey.GetPublicKey(strPublicKey, false); // bEscaped=true by default.
    const bool b6 = m_EncryptKey.SaveCertAndPrivateKeyToString(strPrivateCert, &strReason);
    
    if (b5)
        mapPublic. insert(std::pair<std::string, std::string>("E", strPublicKey.Get()));
    if (b6)
        mapPrivate.insert(std::pair<std::string, std::string>("E", strPrivateCert.Get()));
    // ------------------------------------------
    if (3 != mapPublic.size())
    {
        OTLog::vError("In %s, line %d: Failed getting public keys in OTKeyCredential::GenerateKeys.\n",
                      __FILE__, __LINE__);
        return false;
    }
    else
        this->ot_super::SetPublicContents(mapPublic);
    // --------------------------------
    if (3 != mapPrivate.size())
    {
        OTLog::vError("In %s, line %d: Failed getting private keys in OTKeyCredential::GenerateKeys.\n",
                      __FILE__, __LINE__);
        return false;
    }
    else
        this->ot_super::SetPrivateContents(mapPrivate);
    // --------------------------------
    return true;
}


//virtual
bool OTKeyCredential::SetPublicContents(const mapOfStrings & mapPublic)
{
    // NOTE: We might use this on the server side, we'll see, but so far on the client
    // side, we won't need to use this function, since SetPrivateContents already does
    // the dirty work of extracting the public keys and setting them.
    //
    // -------------------------------------------------
    if (mapPublic.size() != 3)
    {
        OTLog::vError("%s line %d: Failure: Expected 3 in mapPublic.size(), but the actual value was: %d\n",
                      __FILE__, __LINE__, mapPublic.size());
        return false;
    }
    // -------------------------------------------------
    mapOfStrings::const_iterator iiAuth = mapPublic.find("A");  // Authentication key
    mapOfStrings::const_iterator iiEncr = mapPublic.find("E");  // Encryption key
    mapOfStrings::const_iterator iiSign = mapPublic.find("S");  // Signing key
    // -------------------------------------------------
    if (mapPublic.end() == iiAuth)
    {
        OTLog::vError("%s line %d: Failure: Unable to find public authentication key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPublic.end() == iiEncr)
    {
        OTLog::vError("%s line %d: Failure: Unable to find public encryption key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPublic.end() == iiSign)
    {
        OTLog::vError("%s line %d: Failure: Unable to find public signing key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (this->ot_super::SetPublicContents(mapPublic))
    {
        // -------------------------------------------------
        OTString strKey;
        strKey.Set((*iiAuth).second.c_str());
        if (false == m_AuthentKey.SetPublicKey(strKey))
        {
            OTLog::vError("%s line %d: Failure: Unable to set public authentication key based on string:\n%s\n",
                          __FILE__, __LINE__, strKey.Get());
            return false;
        }
        // -------------------------------------------------
        strKey.Release();
        strKey.Set((*iiEncr).second.c_str());
        if (false == m_EncryptKey.SetPublicKey(strKey))
        {
            OTLog::vError("%s line %d: Failure: Unable to set public encryption key based on string:\n%s\n",
                          __FILE__, __LINE__, strKey.Get());
            return false;
        }
        // -------------------------------------------------
        strKey.Release();
        strKey.Set((*iiSign).second.c_str());
        if (false == m_SigningKey.SetPublicKey(strKey))
        {
            OTLog::vError("%s line %d: Failure: Unable to set public signing key based on string:\n%s\n",
                          __FILE__, __LINE__, strKey.Get());
            return false;
        }
        // -------------------------------------------------
        return true; // SUCCESS! This means the input, mapPublic, actually contained an "A" key, an "E"
        // key, and an "S" key (and nothing else) and that all three of those public keys actually loaded
        // from string form into their respective key object members.
    }
    // -------------------------------------------------
    return false;
}


// NOTE: With OTKeyCredential, if you call SetPrivateContents, you don't have to call SetPublicContents,
// since SetPrivateContents will automatically set the public contents, since the public certs are available
// from the private certs. Not all credentials do this, but keys do. So you might ask, why did I still
// provide a version of SetPublicContents for OTKeyCredential? Just to fit the convention, also also because
// perhaps on the server side, public contents will be the only ones available, and private ones will never
// be set.

//virtual
bool OTKeyCredential::SetPrivateContents(const mapOfStrings & mapPrivate,
                                               OTPassword   * pImportPassword/*=NULL*/) // if not NULL, it means to use this password by default.
{
    // -------------------------------------------------
    if (mapPrivate.size() != 3)
    {
        OTLog::vError("%s line %d: Failure: Expected 3 in mapPrivate(), but the actual value was: %d\n",
                      __FILE__, __LINE__, mapPrivate.size());
        return false;
    }
    // -------------------------------------------------
    mapOfStrings::const_iterator iiAuth = mapPrivate.find("A");  // Authentication key
    mapOfStrings::const_iterator iiEncr = mapPrivate.find("E");  // Encryption key
    mapOfStrings::const_iterator iiSign = mapPrivate.find("S");  // Signing key
    // -------------------------------------------------
    if (mapPrivate.end() == iiAuth)
    {
        OTLog::vError("%s line %d: Failure: Unable to find private authentication key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPrivate.end() == iiEncr)
    {
        OTLog::vError("%s line %d: Failure: Unable to find private encryption key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPrivate.end() == iiSign)
    {
        OTLog::vError("%s line %d: Failure: Unable to find private signing key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (this->ot_super::SetPrivateContents(mapPrivate, pImportPassword))
    {
        const OTString strReason("Loading private key from credential.");
        mapOfStrings mapPublic;
        // -------------------------------------------------
        OTString strPrivate;
        strPrivate.Set((*iiAuth).second.c_str()); // strPrivate now contains the private Cert string.
        
        if (false == m_AuthentKey.LoadPrivateKeyFromCertString(strPrivate, false /*bEscaped true by default*/,  &strReason, pImportPassword))
        {
            OTLog::vError("%s line %d: Failure: Unable to set private authentication key based on string.\n",
                          __FILE__, __LINE__);
//          OTLog::vError("%s line %d: Failure: Unable to set private authentication key based on string:\n%s\n",
//                        __FILE__, __LINE__, strPrivate.Get());
            return false;
        }
        else // Success loading the private key. Let's grab the public key here.
        {
            OTString strPublic;

            if ((false == m_AuthentKey.LoadPublicKeyFromCertString(strPrivate, false /* bEscaped true by default */, &strReason, pImportPassword)) ||
                (false == m_AuthentKey.GetPublicKey(strPublic, false /* bEscaped true by default */)))
            {
                OTLog::vError("%s line %d: Failure: Unable to set public authentication key based on private string.\n",
                              __FILE__, __LINE__);
//              OTLog::vError("%s line %d: Failure: Unable to set public authentication key based on private string:\n%s\n",
//                            __FILE__, __LINE__, strPrivate.Get());
                return false;
            }
            mapPublic.insert(std::pair<std::string, std::string>("A", strPublic.Get()));
        }
        // -------------------------------------------------
        strPrivate.Release();
        strPrivate.Set((*iiEncr).second.c_str());
        
        if (false == m_EncryptKey.LoadPrivateKeyFromCertString(strPrivate, false /*bEscaped true by default*/,  &strReason, pImportPassword))
        {
            OTLog::vError("%s line %d: Failure: Unable to set private encryption key based on string.\n",
                          __FILE__, __LINE__);
//          OTLog::vError("%s line %d: Failure: Unable to set private encryption key based on string:\n%s\n",
//                        __FILE__, __LINE__, strPrivate.Get());
            return false;
        }
        else // Success loading the private key. Let's grab the public key here.
        {
            OTString strPublic;
            
            if ((false == m_EncryptKey.LoadPublicKeyFromCertString(strPrivate, false /* bEscaped true by default */, &strReason, pImportPassword)) ||
                (false == m_EncryptKey.GetPublicKey(strPublic, false /* bEscaped true by default */)))
            {
                OTLog::vError("%s line %d: Failure: Unable to set public encryption key based on private string.\n",
                              __FILE__, __LINE__);
//              OTLog::vError("%s line %d: Failure: Unable to set public encryption key based on private string:\n%s\n",
//                            __FILE__, __LINE__, strPrivate.Get());
                return false;
            }
            mapPublic.insert(std::pair<std::string, std::string>("E", strPublic.Get()));
        }
        // -------------------------------------------------
        strPrivate.Release();
        strPrivate.Set((*iiSign).second.c_str());
        
        if (false == m_SigningKey.LoadPrivateKeyFromCertString(strPrivate, false /*bEscaped true by default*/,  &strReason, pImportPassword))
        {
            OTLog::vError("%s line %d: Failure: Unable to set private signing key based on string.\n",
                          __FILE__, __LINE__);
//          OTLog::vError("%s line %d: Failure: Unable to set private signing key based on string:\n%s\n",
//                        __FILE__, __LINE__, strPrivate.Get());
            return false;
        }
        else // Success loading the private key. Let's grab the public key here.
        {
            OTString strPublic;
            
            if ((false == m_SigningKey.LoadPublicKeyFromCertString(strPrivate, false /* bEscaped true by default */, &strReason, pImportPassword)) ||
                (false == m_SigningKey.GetPublicKey(strPublic, false /* bEscaped true by default */)))
            {
                OTLog::vError("%s line %d: Failure: Unable to set public signing key based on private string.\n",
                              __FILE__, __LINE__);
//              OTLog::vError("%s line %d: Failure: Unable to set public signing key based on private string:\n%s\n",
//                            __FILE__, __LINE__, strPrivate.Get());
                return false;
            }
            mapPublic.insert(std::pair<std::string, std::string>("S", strPublic.Get()));
        }
        // -------------------------------------------------
        if (false == this->ot_super::SetPublicContents(mapPublic))
        {
            OTLog::vError("%s line %d: Failure: While trying to call: ot_super::SetPublicContents(mapPublic)\n",
                          __FILE__, __LINE__); // Should never happen (it always just returns true.)
            return false;
        }
        // -------------------------------------------------
        return true; // SUCCESS! This means the input, mapPrivate, actually contained an "A" key, an "E"
        // key, and an "S" key (and nothing else) and that all three of those private keys actually loaded
        // from string form into their respective key object members. We also set the public keys in here, FYI.
    }
    // -------------------------------------------------
    return false;
}


bool OTKeyCredential::SignContract(OTContract & theContract, OTPasswordData * pPWData/*=NULL*/)
{
    return m_SigningKey.SignContract(theContract, pPWData);
}


bool OTKeyCredential::ReEncryptKeys(OTPassword & theExportPassword, bool bImporting)
{
    OTString strSign, strAuth, strEncr;
    // ----------------------------------------
    const bool bSign = m_SigningKey.ReEncrypt(theExportPassword, bImporting, strSign);
          bool bAuth = false;
          bool bEncr = false;
    // ----------------------------------------    
    if (bSign)
    {
        bAuth = m_AuthentKey.ReEncrypt(theExportPassword, bImporting, strAuth);

        if (bAuth)
            bEncr = m_EncryptKey.ReEncrypt(theExportPassword, bImporting, strEncr);
    }
    // ----------------------------------------
    const bool bSuccessReEncrypting = (bSign && bAuth && bEncr);
          bool bSuccess = false;
    // ----------------------------------------
    // If success, we now have the updated versions of the private certs.
    // 
    if (bSuccessReEncrypting)
    {
        mapOfStrings mapPrivate;        
        // ----------------------------------------
        FOR_EACH(mapOfStrings, m_mapPrivateInfo)
        {
            std::string  str_key_type     = (*it).first;   // A, E, S.
            std::string  str_key_contents = (*it).second;
            // ----------------------------------------
            if ("A" == str_key_type)
            {
                mapPrivate.insert(std::pair<std::string, std::string>("A", strAuth.Get()));
            }
            else if ("E" == str_key_type)
                mapPrivate.insert(std::pair<std::string, std::string>("E", strEncr.Get()));
            else if ("S" == str_key_type)
                mapPrivate.insert(std::pair<std::string, std::string>("S", strSign.Get()));
            // ----------------------------------------
            else // Should never happen, but if there are other keys here, we'll preserve 'em.
            {
                mapPrivate.insert(std::pair<std::string, std::string>(str_key_type, str_key_contents));
                OT_FAIL; // really this should never happen.
            }
        }
        // ----------------------------------------
        if (3 != mapPrivate.size())
            OTLog::vError("%s: Unexpected, mapPrivate does not have exactly a size of 3. \n", __FUNCTION__);
        // ----------------------------------------
        else
        {
            // Logic: If I'm IMPORTING, bImporting is true, and that means the Nym WAS
            // encrypted to its own external passphrase (whenever it was exported) and
            // in order to IMPORT it, I re-encrypted all the keys from the exported passphrase,
            // to the wallet master key (this was done above in ReEncrypt.)
            // So now that I am loading up the private contents again based on those
            // re-encrypted keys, I will want to use the normal wallet master key to load
            // them. (So I pass NULL.)
            //
            // But if I'm EXPORTING, bImporting is false, and that means the Nym WAS
            // encrypted to the wallet's master passphrase, until just above when I ReEncrypted
            // it to its own external passphrase. So now that I am attempting to reload the
            // keys based on this new external passphrase, I need to pass it in so it can be
            // used for that loading. (So I pass &theExportPassword.)
            //
            bSuccess = this->SetPrivateContents(mapPrivate, bImporting ? NULL : &theExportPassword);
        }
    }
    // ----------------------------------------
    return bSuccess; // Note: Caller must re-sign credential after doing this, to keep these changes.
}


void OTKeyCredential::SetMetadata()
{
    bool bMetadata         = false;
	char cMetaKeyType;            // Can be A, E, or S (authentication, encryption, or signing. Also, E would be unusual.)
	char cMetaNymID        = '0'; // Can be any letter from base62 alphabet. Represents first letter of a Nym's ID.
	char cMetaMasterCredID = '0'; // Can be any letter from base62 alphabet. Represents first letter of a Master Credential ID (for that Nym.)
	char cMetaSubCredID    = '0'; // Can be any letter from base62 alphabet. Represents first letter of a SubCredential ID (signed by that Master.)
    // ----------------------------------------------------
    OTString strSubcredID;
    this->GetIdentifier(strSubcredID);
    // ----------------------------------------------------
    const bool bNymID  = this->GetNymID()           .At(0, cMetaNymID);
    const bool bCredID = m_pOwner->GetMasterCredID().At(0, cMetaMasterCredID);
    const bool bSubID  = strSubcredID               .At(0, cMetaSubCredID); // In the case of the master credential, this will repeat the previous one.

	if (!bNymID || !bCredID || !bSubID)
	{
		OTLog::vOutput(1,"%s: No metadata available:\n %s is %s, %s is %s, %s is %s", __FUNCTION__,
			"bNymID", bNymID ? "True": "False",
			"bCredID",bNymID ? "True": "False",
			"bSubID", bNymID ? "True": "False");
	}

    // ----------------------------------------------------
    OTSignatureMetadata theMetadata;
    // ----------------------------------------------------
    cMetaKeyType   = 'A';
    bMetadata = theMetadata.SetMetadata(cMetaKeyType, cMetaNymID, cMetaMasterCredID, cMetaSubCredID);
    m_AuthentKey.SetMetadata(theMetadata);
    // ----------------------------------------------------
    cMetaKeyType   = 'E';
    bMetadata = theMetadata.SetMetadata(cMetaKeyType, cMetaNymID, cMetaMasterCredID, cMetaSubCredID);
    m_EncryptKey.SetMetadata(theMetadata);
    // ----------------------------------------------------
    cMetaKeyType   = 'S';
    bMetadata = theMetadata.SetMetadata(cMetaKeyType, cMetaNymID, cMetaMasterCredID, cMetaSubCredID);
    m_SigningKey.SetMetadata(theMetadata);
    // ----------------------------------------------------
}
