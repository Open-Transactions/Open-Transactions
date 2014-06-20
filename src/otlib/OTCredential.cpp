/************************************************************
 *
 *  OTCredential.cpp
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

#include "OTCredential.hpp"

#include "OTFolders.hpp"
#include "OTLog.hpp"
#include "OTPasswordData.hpp"
#include "OTStorage.hpp"
#include "OTSubkey.hpp"

#include <algorithm>


// '0' for cKeyType means, theSignature MUST have metadata in order for ANY keys to be returned, and it MUST match.
// Whereas if you pass 'A', 'E', or 'S' for cKeyType, that means it can ONLY return authentication, encryption, or signing
// keys. It also means that metadata must match IF it's present, but that otherwise, if theSignature has no metadata at
// all, then it will still be a "presumed match" and returned as a possibility. (With the 'A', 'E', or 'S' enforced.)
//
int32_t OTCredential::GetPublicKeysBySignature(listOfAsymmetricKeys & listOutput,
                                           const OTSignature & theSignature,
                                           char cKeyType/*='0'*/) const // 'S' (signing key) or 'E' (encryption key) or 'A' (authentication key)
{
    int32_t nCount = 0;
    FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
    {
        const OTSubcredential * pSub = (*it).second;
        OT_ASSERT(NULL != pSub);
        // -------------------------
        const OTSubkey * pKey = dynamic_cast<const OTSubkey *>(pSub);
        if (NULL == pKey) continue; // Skip all non-key credentials. We're looking for keys.
        // -------------------------
        const int32_t nTempCount = pKey->GetPublicKeysBySignature(listOutput, theSignature, cKeyType);
        nCount += nTempCount;
    }
    return nCount;
}


bool OTCredential::VerifyInternally() const
{
    // --------------------------------------
    OTIdentifier theActualMasterCredID;
    theActualMasterCredID.CalculateDigest(m_Masterkey.GetPubCredential());
    const OTString strActualMasterCredID(theActualMasterCredID);
    // --------------------------------------
    if (false == m_strNymID.Compare(m_Masterkey.GetNymID()))
    {
        OTLog::vOutput(0, "%s: NymID did not match its "
                       "counterpart in m_Masterkey (failed to verify): %s\n",
                       __FUNCTION__, this->GetNymID().Get());
        return false;
    }
    // --------------------------------------
    if (false == m_strMasterCredID.Compare(strActualMasterCredID))
    {
        OTLog::vOutput(0, "%s: Master Credential ID did not match its "
                       "counterpart in m_Masterkey:\nExpected Master Credential ID: %s\n "
                       "Hash of m_Masterkey contents: %s\nContents:\n%s\n",
                       __FUNCTION__, this->GetMasterCredID().Get(), strActualMasterCredID.Get(),
                       m_Masterkey.GetPubCredential().Get());
        return false;
    }
    // --------------------------------------
    if (false == const_cast<OTMasterkey&>(m_Masterkey).VerifyContract())
    {
        OTLog::vOutput(0, "%s: Master Credential failed to verify: %s\nNymID: %s\n",
                       __FUNCTION__, this->GetMasterCredID().Get(), this->GetNymID().Get());
        return false;
    }
    // -------------------------------------
    FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
    {
        std::string str_sub_id = (*it).first;
        OTSubcredential * pSub = (*it).second;
        OT_ASSERT(NULL != pSub);
        // ----------------------
        if (false == pSub->VerifyContract())
        {
            OTLog::vOutput(0, "%s: Subcredential failed to verify: %s\nNymID: %s\n", __FUNCTION__,
                           str_sub_id.c_str(), this->GetNymID().Get());
            return false;
        }
    }
    // -------------------------------------
    return true;
}


bool OTCredential::VerifyAgainstSource() const
{
    // * Any OTMasterkey must (at some point, and/or regularly) verify against its own source.
    //
    if (false == m_Masterkey.VerifyAgainstSource())
	{
		OTLog::vOutput(1, "%s: Failed verifying master credential against its own source.\n", __FUNCTION__);
		return false;
	}
    // NOTE: This spot will have a significant delay, TODO OPTIMIZE. Performing a Freenet lookup, or DNS, etc,
    // will introduce delay inside the call VerifyAgainstSource. Therefore in the int64_t term, we must have a
    // separate server process which will verify identities for some specified period of time (specified in
    // their credentials I suppose...) That way, when we call VerifyAgainstSource, we are verifying against
    // some server-signed authorization, based on a lookup that some separate process did within the past
    // X allowed time, such that the lookup is still considered valid (without having to lookup every single
    // time, which is untenable.)
    // -------------------------------------
    return true;
}


// Contains a "master" subkey,
// and a list of "sub" subkeys signed by that master.
// Each subkey can generate its own "credential" contract,
// so OTCredential actually may include many "credentials."
// A nym has multiple OTCredentials because there may be
// several master keys.
//

const OTString & OTCredential::GetNymID() const
{
    return m_strNymID;
}


const OTString & OTCredential::GetSourceForNymID() const
{
    return m_strSourceForNymID;
}


/// This sets m_strSourceForNymID.
/// This also sets m_strNymID, which is always a hash of strSourceForNymID.
///
void OTCredential::SetSourceForNymID(const OTString & strSourceForNymID)
{
    // --------------------------------------
    m_strSourceForNymID = strSourceForNymID;
    // --------------------------------------
    //  Now re-calculate the NymID...
    //
    m_strNymID.Release();
    OTIdentifier theTempID;
    const bool bCalculate = theTempID.CalculateDigest(m_strSourceForNymID);
    OT_ASSERT(bCalculate);
    theTempID.GetString(m_strNymID);
    // ------------------------------
    m_Masterkey.SetNymIDandSource(m_strNymID, m_strSourceForNymID); // The key in here must somehow verify against its own source.
    
    // Success! By this point, m_strSourceForNymID and m_strNymID
    // are both set.
}


const OTString & OTCredential::GetPubCredential() const
{
    return m_Masterkey.GetPubCredential();
}


const OTString & OTCredential::GetPriCredential() const
{
    return m_Masterkey.GetPriCredential();
}


bool OTCredential::SetPublicContents(const mapOfStrings & mapPublic)
{
    return m_Masterkey.SetPublicContents(mapPublic);
}


bool OTCredential::SetPrivateContents(const mapOfStrings & mapPrivate)
{
    return m_Masterkey.SetPrivateContents(mapPrivate);
}


//private
OTCredential::OTCredential() :
    m_Masterkey(*this), m_pImportPassword(NULL)
{ }


void OTCredential::SetMasterCredID(const OTString & strID)
{
    m_strMasterCredID = strID;
}


const OTString & OTCredential::GetMasterCredID() const
{
    return m_strMasterCredID;
}


//static  (Caller is responsible to delete.)
OTCredential * OTCredential::LoadMaster(const OTString & strNymID, // Caller is responsible to delete, in both CreateMaster and LoadMaster.
                                        const OTString & strMasterCredID,
                                        OTPasswordData * pPWData/*=NULL*/)
{
    OTCredential * pCredential = new OTCredential;
    OTCleanup<OTCredential> theCredentialAngel(pCredential);
    OT_ASSERT(NULL != pCredential);
    // -------------------------------------
    OTPasswordData thePWData("Loading master credential. (static 1.)");
    const bool bLoaded = pCredential->Load_Master(strNymID, strMasterCredID, (NULL == pPWData) ? &thePWData : pPWData);
    if (!bLoaded)
    {
        OTLog::vError("%s: Failed trying to load master credential from local storage. 1\n", __FUNCTION__);
        return NULL;
    }
    // --------------------------------------------------
    theCredentialAngel.SetCleanupTargetPointer(NULL); // so pCredential doesn't get cleaned up.
    return pCredential;
}


//static  (Caller is responsible to delete.)
OTCredential * OTCredential::LoadMasterFromString(const OTString & strInput,
                                                  const OTString & strNymID, // Caller is responsible to delete, in both CreateMaster and LoadMaster.
                                                  const OTString & strMasterCredID,
                                                  OTPasswordData * pPWData/*=NULL*/,
                                                  OTPassword     * pImportPassword/*=NULL*/)
{
    OTCredential * pCredential = new OTCredential;
    OTCleanup<OTCredential> theCredentialAngel(pCredential);
    OT_ASSERT(NULL != pCredential);
    // -------------------------------------
    OTPasswordData thePWData(NULL == pImportPassword ? "Enter wallet master passphrase." : "Enter passphrase for exported Nym.");
    const bool bLoaded = pCredential->Load_MasterFromString(strInput, strNymID,
                                                            strMasterCredID,
                                                            (NULL == pPWData) ? &thePWData : pPWData,
                                                            pImportPassword);
    if (!bLoaded)
    {
        OTLog::vError("%s: Failed trying to load master credential from string. 2\n", __FUNCTION__);
        return NULL;
    }
    // --------------------------------------------------
    theCredentialAngel.SetCleanupTargetPointer(NULL); // so pCredential doesn't get cleaned up.
    return pCredential;
}


// called by OTCredential::CreateMaster
bool OTCredential::SignNewMaster(OTPasswordData * pPWData/*=NULL*/)
{
    OTPasswordData thePWData("Signing new master credential... OTCredential::SignNewMaster");
    // ------------------------------------
    m_Masterkey.StoreAsPublic(); // So the version we create here only contains public keys, not private.
    const bool bSignedPublic = m_Masterkey.SignContract(m_Masterkey, NULL == pPWData ? &thePWData : pPWData);
    if (bSignedPublic)
    {
        m_Masterkey.SaveContract();
        // ***********************************************************
        // THE OFFICIAL "PUBLIC CREDENTIAL" FOR THE MASTER KEY
        // (Copied from the raw contents here into a member variable for safe-keeping.)
        // Future verifiers can hash it and the output should match the master credential ID.
        //
        OTString strPublicCredential;
        
        if (m_Masterkey.SaveContractRaw(strPublicCredential))
        {
            m_Masterkey.SetContents(strPublicCredential); // <=== The "master public credential" string.
            // ***********************************************************
            // NEW MASTER CREDENTIAL ID.
            //
            // Only now can we calculate the master key's ID, since the ID is a hash of
            // the contents.
            //
            OTIdentifier theNewID;
            m_Masterkey.CalculateContractID(theNewID);
            m_Masterkey.SetIdentifier(theNewID); // Usually this will be set based on an expected value from above, then loaded from storage, and then verified against what was actually loaded (by hashing it.)
            // -------------------------------
            const OTString strMasterCredID(theNewID);
            this->SetMasterCredID(strMasterCredID);  // <=== Master Credential ID is now set.
        }
        else
        {
            OTLog::vError("In %s, line %d: Failed calling m_Masterkey.SaveContractRaw 1.\n",
                          __FILE__, __LINE__);
            return false;
        }
        // **********************************************************
        // THE PRIVATE KEYS
        //
        // Next, we sign / save it again, this time in its private form, and also
        // m_Masterkey.m_strContents and m_strIDsOnly will be contained within that
        // private form along with the private keys.
        //
        m_Masterkey.ReleaseSignatures(); // This time we'll sign it in private mode.
        const bool bSignedPrivate = m_Masterkey.SignContract(m_Masterkey, NULL == pPWData ? &thePWData : pPWData);
        if (bSignedPrivate)
        {
            m_Masterkey.SaveContract();
            // -------------------------------
            m_Masterkey.SetMetadata();
        }
        else
        {
            OTLog::vError("In %s, line %d: Failed trying to sign the master private credential.\n",
                          __FILE__, __LINE__);
            return false;
        }
    }
    else
    {
        OTLog::vError("In %s, line %d: Failed trying to sign the master public credential.\n",
                      __FILE__, __LINE__);
        return false;
    }
    // ------------------------------------
    return true;
}


// When exporting a Nym, you don't want his private keys encrypted to the cached key
// for the wallet, so you have to load them up, and then pause OTCachedKey, and then
// save them to string again, re-encrypting them to the export passphrase (and not to
// any "master key" from the wallet.) And you have to release all the signatures on
// the private credentials, since the private info is being re-encrypted, and re-sign
// them all. Joy. 
//
bool OTCredential::ReEncryptPrivateCredentials(OTPassword & theExportPassword, bool bImporting)
{
    if (m_Masterkey.GetPrivateMap().size() > 0)
    {
        OTPasswordData thePWData(bImporting ?
                                 "2 Enter passphrase for the Nym being imported." :
                                 "2 Enter new passphrase for exported Nym.");
        // -------------------------------
        // Re-encrypt the private keys in the masterkey. (THEN sign.)
        //
        const bool bReEncryptMaster = m_Masterkey.ReEncryptKeys(theExportPassword, bImporting);
              bool bSignedMaster    = false;
        
        if (bReEncryptMaster)
        {
            m_Masterkey.ReleaseSignatures(); // This time we'll sign it in private mode.
            bSignedMaster = m_Masterkey.SignContract(m_Masterkey, &thePWData);
        }
        else
        {
            OTLog::vError("In %s, line %d: Failed trying to re-encrypt the private masterkey.\n",
                          __FILE__, __LINE__);
            return false;
        }
        // ---------------------------
        if (bSignedMaster)
        {
            m_Masterkey.SaveContract();
            m_Masterkey.SetMetadata (); // todo: can probably remove this, since it was set based on public info when the key was first created.
            // -------------------------------
            FOR_EACH(mapOfSubcredentials, m_mapSubcredentials)
            {
                const std::string str_cred_id = (*it).first;
                      OTSubcredential * pSub  = (*it).second;
                OT_ASSERT(NULL != pSub);
                // ------------------------
                OTSubkey * pKey = dynamic_cast<OTSubkey *>(pSub);
                if (NULL == pKey) continue;
                // ------------------------
                const bool bReEncryptSubkey = pKey->ReEncryptKeys(theExportPassword, bImporting);
                      bool bSignedSubkey    = false;

                if (bReEncryptSubkey)
                {
                    pKey->ReleaseSignatures();
                    bSignedSubkey = pKey->SignContract(*pKey, &thePWData);
                }
                else
                {
                    OTLog::vError("In %s, line %d: Failed trying to re-encrypt the private subkey.\n",
                                  __FILE__, __LINE__);
                    return false;
                }
                // ---------------------
                if (bSignedSubkey)
                {
                    pKey->SaveContract();
                    pKey->SetMetadata (); // todo: can probably remove this, since it was set based on public info when the key was first created.
                }
                else
                {
                    OTLog::vError("In %s, line %d: Failed trying to re-sign the private subkey.\n",
                                  __FILE__, __LINE__);
                    return false;
                }
            } // FOR_EACH
            // -------------------------------
            return true; // <=== Success.
        }
        else
            OTLog::vError("In %s, line %d: Failed trying to re-sign the master private credential.\n",
                          __FILE__, __LINE__);
    }
    else
        OTLog::vError("In %s, line %d: Failed: There is no private info on this master credential.\n",
                      __FILE__, __LINE__);

    return false;
}


bool OTCredential::SignNewSubcredential(OTSubcredential & theSubCred, OTIdentifier & theSubCredID_out, OTPasswordData * pPWData/*=NULL*/)
{
    OTPasswordData thePWData("Signing new subcredential... OTCredential::SignNewSubcredential");
    // ------------------------------------
    // First, we store the subcredential itself with its basic info.
    // This version is signed with the Masterkey. Then we save a copy of it
    // in a member variable for safe-keeping, m_strMasterSigned. Next, we
    // save a "public" version of the subcredential (the official version)
    // which will include m_strMasterSigned inside it, and be signed by the
    // subkey. This version may not need to duplicate all that data, especially
    // if we end up just having to verify it twice as a result. So I might have
    // the public version be sparse (other than including the master signed version,
    // and being signed by the subkey.)
    // Though with many subcredentials, there will ONLY be the master-signed version,
    // and that WILL be the public version. Only with subkeys will that be different!
    //
    OTSubkey * pSubkey   = dynamic_cast<OTSubkey *>(&theSubCred);
    const bool bIsSubkey = (NULL != pSubkey); // It's not just any subcredential -- it's a subkey!
    // --------------------------------------------------------------
	// If it's not a subkey, but rather, a normal subcredential with no keys, then it doesn't need to contain a "master signed" version,
	// since the entire subcredential will already be master signed, since there's no subkey to sign in that case.
    if (!bIsSubkey) 
        theSubCred.SetMasterSigned(OTString("")); 
    // ------------------------
    // ELSE It's a subkey...
    else // Subkeys must be self-signed, and must contain a master-signed version of themselves where the data is actually stored.
    {
        // ***********************************************************
        pSubkey->StoreAsMasterSigned(); // So the version we create here only contains public keys, not private. (And so it won't include
                                        // the "master signed" version in what it stores, since that's what we're creating now.)

        const bool bMasterSigned = m_Masterkey.SignContract(*pSubkey, NULL == pPWData ? &thePWData : pPWData);
        if (!bMasterSigned)
        {
            OTLog::vError("In %s, line %d: Failed calling m_Masterkey.SignContract(*pSubkey) after StoreAsMasterSigned.\n",
                          __FILE__, __LINE__);
            return false;
        }
        else
        {
            pSubkey->SaveContract();
            // ------------------------------------
            // Make a copy of the "master signed" version of the public subcredential.
            //
            OTString strMasterSigned;
            
            if (pSubkey->SaveContractRaw(strMasterSigned)) // <=== The "master signed" version of the "public credential" string. Captured here
                pSubkey->SetMasterSigned(strMasterSigned); // so that the (subkey-signed) public version of the subcredential will contain it.
            else
            {
                OTLog::vError("In %s, line %d: Failed calling pSubkey->SaveContractRaw 1.\n",
                              __FILE__, __LINE__);
                return false;
            }
        }
        // --------------------------
        pSubkey->ReleaseSignatures();
    }
    // ***********************************************************
    theSubCred.StoreAsPublic(); // So the version we create here only contains public keys, not private.
    
    // Here, dynamic cast theSubCred to a subkey and if successful, use it to sign itself.
    // Otherwise, sign it with the master. (If it's a real subkey, then it will contain the
    // master-signed version, and it will be signed with itself, its own subkey. Whereas if
    // it's a subcredential that is NOT a subkey, such as a Google Authenticator or some other
    // 3rd-party authentication, then it will HAVE no key to sign itself with, since its primary
    // purpose in that case is to provide some OTHER authentication info INSTEAD of a key.
    // So in that case, it must be signed by the master.)
    //
    bool bSignedPublic = false;
    
    if (bIsSubkey) // If it's a subkey, its keys are already generated by the time we got here. So use it to sign its own public version.
        bSignedPublic = pSubkey->   SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
    else // It's not a subkey, but some other conventional subcredential. So we sign with master key, since that's all we've got.
        bSignedPublic = m_Masterkey.SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
    // -----------------
    if (!bSignedPublic)
    {
        OTLog::vError("In %s, line %d: Failed trying to sign the public subcredential or subkey.\n",
                      __FILE__, __LINE__);
        return false;
    }
    else
    {
        theSubCred.SaveContract();
        // ***********************************************************
        // THE OFFICIAL "PUBLIC CREDENTIAL STRING" FOR THIS NEW SUB-CREDENTIAL
        // Set it aside for safe-keeping as the official contents, hashable to form
        // the ID for this sub-credential.
        //
        OTString strPublicCredential;
        if (theSubCred.SaveContractRaw(strPublicCredential))
        {
            theSubCred.SetContents(strPublicCredential); // <=== The "public credential" string aka the contents.
            // ***********************************************************
            // NEW SUB-CREDENTIAL ID.
            //
            // Only now that the contents have been set, can we calculate the ID, which
            // is a hash of those contents. (Credential ID is a hash of GetPubCredential instead
            // of m_strRawXML as most contracts would use, since we only want to use the PUBLIC
            // info for calculating the ID, not the private info.)
            //
            theSubCred.CalculateContractID(theSubCredID_out);
            theSubCred.SetIdentifier(theSubCredID_out);
        }
        else
        {
            OTLog::vError("In %s, line %d: Failed calling theSubCred.SaveContractRaw.\n",
                          __FILE__, __LINE__);
            return false;
        }
        // **********************************************************
        // CREATE THE PRIVATE FORM.
        //
        // Next, we sign / save it again, this time in its private form, and also
        // theSubCred.m_strContents will be contained within that private form,
        // along with the private keys.
        //
        theSubCred.ReleaseSignatures(); // This time we'll sign it in private mode.
        bool bSignedPrivate = false;
        
        if (bIsSubkey) // If it's a subkey, its keys are already generated by the time we got here. So use it to sign its own private version.
            bSignedPrivate = pSubkey->   SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
        else // It's not a subkey, but some other conventional subcredential. So we sign the private info with the master key, since that's all we've got.
            bSignedPrivate = m_Masterkey.SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
        
        if (bSignedPrivate)
            theSubCred.SaveContract();
        else
        {
            OTLog::vError("In %s, line %d: Failed trying to sign the private subcredential.\n",
                          __FILE__, __LINE__);
            return false;
        }
    }
    // ------------------------------------
    return true;
}


bool OTCredential::GenerateMasterkey(int32_t nBits/*=1024*/) // CreateMaster is able to create keys from scratch (by calling this function.)
{
    return m_Masterkey.GenerateKeys(nBits);
}


bool OTCredential::Load_MasterFromString(const OTString & strInput,
                                         const OTString & strNymID,
                                         const OTString & strMasterCredID,
                                         OTPasswordData * pPWData/*=NULL*/,
                                         OTPassword     * pImportPassword/*=NULL*/)
{
    m_strNymID          = strNymID;
    m_strMasterCredID   = strMasterCredID;
    // --------------------------------------
    m_Masterkey.SetIdentifier(strMasterCredID);
    // --------------------------------------
    // m_Masterkey and the subkeys all have a pointer to "owner" (who is *this)
    // and so I can set pImportPassword onto a member variable, perform the load,
    // and then set that member NULL again. During the call to LoadContractFromString,
    // m_Masterkey can reference m_pOwner->GetImportPassword() and if it's not NULL,
    // use it instead of using the wallet's cached master key. After all, if it's not
    // NULL here, that's why it was passed in.
    //
    // --------------------------------------
    
    this->SetImportPassword(pImportPassword); // might be NULL.
    
    // --------------------------------------
    const bool bLoaded = m_Masterkey.LoadContractFromString(strInput);
    if (!bLoaded)
    {
        OTLog::vError("%s: Failed trying to load master credential from string.\n", __FUNCTION__);
        return false;
    }
    // --------------------------------------

    this->SetImportPassword(NULL); // It was only set during the m_Masterkey.LoadContractFromString (which references it.)
    
    // --------------------------------------
    m_strNymID          = m_Masterkey.GetNymID();
    m_strSourceForNymID = m_Masterkey.GetNymIDSource();
    // --------------------------------------
    this->ClearSubcredentials();  // The master is loaded first, and then any subcredentials. So this is probably already empty. Just looking ahead.
    // --------------------------------------
    m_Masterkey.SetMetadata();
    // --------------------------------------------------
    return true;
}


bool OTCredential::Load_Master(const OTString & strNymID,
                               const OTString & strMasterCredID,
                               OTPasswordData * pPWData/*=NULL*/)
{
    // --------------------------------------
    std::string str_Folder = OTFolders::Credential().Get(); // Try private credential first. If that fails, then public.
    // --------------------------------------
    if (false == OTDB::Exists(str_Folder, strNymID.Get(), strMasterCredID.Get()))
    {
        str_Folder = OTFolders::Pubcred().Get();
        
        if (false == OTDB::Exists(str_Folder, strNymID.Get(), strMasterCredID.Get()))
        {
            OTLog::vError("%s: Failure: Master Credential %s doesn't exist for Nym %s\n",
                          __FUNCTION__, strMasterCredID.Get(), strNymID.Get());
            return false;
        }
    }
    // ----------------------------------------------------
    OTString strFileContents(OTDB::QueryPlainString(str_Folder,
                                                    strNymID.Get(),
                                                    strMasterCredID.Get()));
    if (!strFileContents.Exists())
    {
        OTLog::vError("%s: Failed trying to load master credential from local storage.\n", __FUNCTION__);
        return false;
    }
    // ---------------------------------------    
    if (false == strFileContents.DecodeIfArmored()) // bEscapedIsAllowed=true by default.
    {
        OTLog::vError("%s: File contents apparently were encoded and then failed decoding. Contents: \n%s\n",
                      __FUNCTION__, strFileContents.Get());
        return false;
    }
    // --------------------------------------------------
    return this->Load_MasterFromString(strFileContents, strNymID, strMasterCredID, pPWData);
}


bool OTCredential::LoadSubkeyFromString(const OTString & strInput, const OTString & strSubID, OTPassword * pImportPassword/*=NULL*/)
{
    // Make sure it's not already there.
    //
    mapOfSubcredentials::iterator it = m_mapSubcredentials.find(strSubID.Get());
    if (it != m_mapSubcredentials.end()) // It was already there. (Reload it.)
    {
        OTLog::vError("%s: Warning: Deleting and re-loading keyCredential that was already loaded.\n",
                      __FUNCTION__);
        OTSubcredential * pSub = (*it).second;
        OT_ASSERT(NULL != pSub);
        delete pSub;
        m_mapSubcredentials.erase(it);
    }
    // -------------------------------------
    OTSubkey * pSub = new OTSubkey(*this);
    OTCleanup<OTSubkey> theSubAngel(pSub);
    OT_ASSERT(NULL != pSub);
    // ----------------------
    pSub->SetIdentifier(strSubID);
    pSub->SetNymIDandSource(this->GetNymID(), this->GetSourceForNymID()); // Set NymID and source string that hashes to it.
    pSub->SetMasterCredID  (this->GetMasterCredID());         // Set master credential ID (onto this new subcredential...)
    // --------------------------------------
    
    this->SetImportPassword(pImportPassword); // might be NULL.

    // --------------------------------------
    if (false == pSub->LoadContractFromString(strInput))
    {
        OTLog::vError("%s: Failed trying to load keyCredential from string.\n", __FUNCTION__);
        return false;
    }
    // --------------------------------------
    
    this->SetImportPassword(NULL); // Only set int64_t enough for LoadContractFromString above to use it.
    
    // --------------------------------------
    pSub->SetMetadata();
    // -------------------------------------
    m_mapSubcredentials.insert(std::pair<std::string, OTSubcredential *>(strSubID.Get(), pSub));
    theSubAngel.SetCleanupTargetPointer(NULL);
    return true;
}


bool OTCredential::LoadSubkey(const OTString & strSubID)
{
    // --------------------------------------
    std::string str_Folder = OTFolders::Credential().Get(); // Try private credential first. If that fails, then public.
    // --------------------------------------
    if (false == OTDB::Exists(str_Folder, this->GetNymID().Get(), strSubID.Get()))
    {
        str_Folder = OTFolders::Pubcred().Get();
        
        if (false == OTDB::Exists(str_Folder, this->GetNymID().Get(), strSubID.Get()))
        {
            OTLog::vError("%s: Failure: Key Credential %s doesn't exist for Nym %s\n",
                          __FUNCTION__, strSubID.Get(), this->GetNymID().Get());
            return false;
        }
    }
    // ----------------------------------------------------    
    OTString strFileContents(OTDB::QueryPlainString(str_Folder,
                                                    this->GetNymID().Get(),
                                                    strSubID.Get()));
    
    if (false == strFileContents.Exists())
    {
        OTLog::vError("%s: Failed trying to load keyCredential from local storage.\n", __FUNCTION__);
        return false;
    }
    // ---------------------------------------
    if (false == strFileContents.DecodeIfArmored()) // bEscapedIsAllowed=true by default.
    {
        OTLog::vError("%s: File contents apparently were encoded and then failed decoding. Contents: \n%s\n",
                      __FUNCTION__, strFileContents.Get());
        return false;
    }
    // --------------------------------------------------
    return this->LoadSubkeyFromString(strFileContents, strSubID);
}


bool OTCredential::LoadSubcredentialFromString(const OTString & strInput, const OTString & strSubID, OTPassword * pImportPassword/*=NULL*/)
{
    // Make sure it's not already there.
    //
    mapOfSubcredentials::iterator it = m_mapSubcredentials.find(strSubID.Get());
    if (it != m_mapSubcredentials.end()) // It was already there. (Reload it.)
    {
        OTLog::vError("%s: Warning: Deleting and re-loading subCredential that was already loaded.\n", __FUNCTION__);
        OTSubcredential * pSub = (*it).second;
        OT_ASSERT(NULL != pSub);
        delete pSub;
        m_mapSubcredentials.erase(it);
    }
    // -------------------------------------
    OTSubcredential * pSub = new OTSubcredential(*this);
    OTCleanup<OTSubcredential> theSubAngel(pSub);
    OT_ASSERT(NULL != pSub);
    // ----------------------
    pSub->SetIdentifier(strSubID);
    pSub->SetNymIDandSource(this->GetNymID(), this->GetSourceForNymID()); // Set NymID and source string that hashes to it.
    pSub->SetMasterCredID  (this->GetMasterCredID());         // Set master credential ID (onto this new subcredential...)
    // --------------------------------------
    
    this->SetImportPassword(pImportPassword); // might be NULL.
    
    // --------------------------------------
    if (false == pSub->LoadContractFromString(strInput))
    {
        OTLog::vError("%s: Failed trying to load subCredential from string.\n", __FUNCTION__);
        return false;
    }
    // --------------------------------------
    
    this->SetImportPassword(NULL); // This is only set int64_t enough for LoadContractFromString to use it. (Then back to NULL.)
    
    // --------------------------------------
    m_mapSubcredentials.insert(std::pair<std::string, OTSubcredential *>(strSubID.Get(), pSub));
    theSubAngel.SetCleanupTargetPointer(NULL);
    return true;
}


bool OTCredential::LoadSubcredential(const OTString & strSubID)
{
    // --------------------------------------
    std::string str_Folder = OTFolders::Credential().Get(); // Try private credential first. If that fails, then public.
    // --------------------------------------
    if (false == OTDB::Exists(str_Folder, this->GetNymID().Get(), strSubID.Get()))
    {
        str_Folder = OTFolders::Pubcred().Get();
        
        if (false == OTDB::Exists(str_Folder, this->GetNymID().Get(), strSubID.Get()))
        {
            OTLog::vError("%s: Failure: Credential %s doesn't exist for Nym %s\n",
                          __FUNCTION__, strSubID.Get(), this->GetNymID().Get());
            return false;
        }
    }
    // ----------------------------------------------------
    OTString strFileContents(OTDB::QueryPlainString(str_Folder,
                                                    this->GetNymID().Get(),
                                                    strSubID.Get()));
    if (!strFileContents.Exists())
    {
        OTLog::vError("%s: Failed trying to load subCredential from local storage.\n", __FUNCTION__);
        return false;
    }
    // ---------------------------------------
    if (false == strFileContents.DecodeIfArmored()) // bEscapedIsAllowed=true by default.
    {
        OTLog::vError("%s: File contents apparently were encoded and then failed decoding. Contents: \n%s\n",
                      __FUNCTION__, strFileContents.Get());
        return false;
    }
    // --------------------------------------------------
    return this->LoadSubcredentialFromString(strFileContents, strSubID);
}


// For adding subcredentials that are specifically *subkeys*. Meaning it will
// contain 3 keypairs: signing, authentication, and encryption.
//
bool OTCredential::AddNewSubkey(const int32_t            nBits       /*=1024*/, // Ignored unless pmapPrivate is NULL
                                const mapOfStrings * pmapPrivate /*=NULL*/, // Public keys are derived from the private.
                                    OTPasswordData * pPWData     /*=NULL*/, // The master key will sign the subkey.
                                    OTSubkey      ** ppSubkey    /*=NULL*/) // output
{
    OTSubkey * pSub = new OTSubkey(*this);
    OT_ASSERT(NULL != pSub);
    // ----------------------
    pSub->SetNymIDandSource(this->GetNymID(), this->GetSourceForNymID()); // Set NymID and source string that hashes to it.
    pSub->SetMasterCredID  (this->GetMasterCredID());         // Set master credential ID (onto this new subcredential...)
    // -------------------------------------
    // If a map of private certs was not passed in, we're expected to
    // generate the keys ourselves.
    //
    bool bContentsReady = false;

    if (NULL != pmapPrivate) // Pre-generated keys were passed in for us to use,
        bContentsReady = pSub->SetPrivateContents(*pmapPrivate); // so let's set them onto the sub key.
    else
        // No keys were provided, so let's generate them ourselves...
        bContentsReady = pSub->GenerateKeys(nBits);
    // -------------------------------------
    if (!bContentsReady)
    {
        OTLog::vError("In %s, line %d: Failed trying to SetPrivateContents or GenerateKeys\n",
                      __FILE__, __LINE__);
        delete pSub; pSub = NULL;
        return false;
    }
    // -------------------------------------
    else // By this point we've set up the subkey with its NymID, the source string for that NymID,
    {    // my master credential ID, and the public and private certs for the subkey. Now let's
         // sign it...
        OTPasswordData thePWData("Signing new subkey... OTCredential::AddNewSubkey");
        OTIdentifier   theSubCredID;
        
        // SignNewSubcredential uses m_Masterkey's actual signing key to sign "pSub the contract."
        //
        if (false == this->SignNewSubcredential(*pSub, theSubCredID, NULL == pPWData ? &thePWData : pPWData))
        {
            OTLog::vError("In %s, line %d: Failed trying to call this->SignNewSubcredential\n",
                          __FILE__, __LINE__);
            delete pSub; pSub = NULL;
            return false;
        }
        // ---------------------------------------------
        const OTString strSubCredID(theSubCredID); // SignNewSubcredential also generates the ID.
        // --------------------------------------
        pSub->SetMetadata();
        // -------------------------------------
        // ADD IT TO THE MAP
        // Only after pSub is signed and saved can we then calculate its ID and use that ID
        // as the key in m_mapSubcredentials (with pSub being the value.)
        //
        m_mapSubcredentials.insert(std::pair<std::string, OTSubcredential *>(strSubCredID.Get(), pSub));

        if (NULL != ppSubkey) // output
        {
            *ppSubkey = pSub;
        }
        
        return true;
    }
}


// For adding non-key credentials, such as for 3rd-party authentication.
//
bool OTCredential::AddNewSubcredential(const mapOfStrings & mapPrivate,
                                       const mapOfStrings & mapPublic,
                                       OTPasswordData  *  pPWData/*=NULL*/, // The master key will sign the subcredential.
                                       OTSubcredential ** ppSubcred/*=NULL*/) // output
{
    OTSubcredential * pSub = new OTSubcredential(*this);
    OT_ASSERT(NULL != pSub);
    // ----------------------
    pSub->SetNymIDandSource(m_strNymID, m_strSourceForNymID); // Set NymID and source string that hashes to it.
    pSub->SetMasterCredID  (this->GetMasterCredID());         // Set master credential ID (onto this new subcredential...)
    // -------------------------------------
    if (false == pSub->SetPublicContents(mapPublic))
    {
        OTLog::vError("In %s, line %d: Failed while calling pSub->SetPublicContents.\n",
                      __FILE__, __LINE__);
        delete pSub; pSub = NULL;
        return false;
    }
    // -------------------------------------
    else if (false == pSub->SetPrivateContents(mapPrivate))
    {
        OTLog::vError("In %s, line %d: Failed while trying to pSub->SetPrivateContents.\n",
                      __FILE__, __LINE__);
        delete pSub; pSub = NULL;
        return false;
    }
    // -------------------------------------
    else // By this point we've set up the subcredential with its NymID, the source string for that NymID,
    {    // my master credential ID, and the public and private contents for the subcredential. Let's sign
         // it...
        OTPasswordData thePWData("Signing new subcredential... OTCredential::AddNewSubcredential");
        OTIdentifier   theSubCredID;
        
        // SignNewSubcredential uses m_Masterkey's actual signing key to sign "pSub the contract."
        //
        if (false == this->SignNewSubcredential(*pSub, theSubCredID, NULL == pPWData ? &thePWData : pPWData))
        {
            OTLog::vError("In %s, line %d: Failed trying to call this->SignNewSubcredential\n",
                          __FILE__, __LINE__);
            delete pSub; pSub = NULL;
            return false;
        }
        // ---------------------------------------------
        const OTString strSubCredID(theSubCredID);
        // -------------------------------
        // ADD IT TO THE MAP
        // Only after pSub is signed and saved can we then calculate its ID and use that ID
        // as the key in m_mapSubcredentials (with pSub being the value.)
        //
        m_mapSubcredentials.insert(std::pair<std::string, OTSubcredential *>(strSubCredID.Get(), pSub));
        if (NULL != ppSubcred) // output
            *ppSubcred = pSub;
        return true;
    }
}


// After calling this, you still need to save it to disk (or not.) This function alone
// doesn't save anything to disk.
//
//static
OTCredential * OTCredential::CreateMaster(const OTString     & strSourceForNymID,
                                          const int32_t            nBits/*=1024*/,       // Ignored unless pmapPrivate is NULL.
                                          const mapOfStrings * pmapPrivate/*=NULL*/, // If NULL, then the keys are generated in here.
                                          const mapOfStrings * pmapPublic /*=NULL*/, // In the case of key credentials, public is optional since it can already be derived from private. But not all credentials are keys...
                                          OTPasswordData * pPWData/*=NULL*/)
{
    OTCredential * pCredential = new OTCredential;
    OT_ASSERT(NULL != pCredential);
    // -------------------------------------
    pCredential->SetSourceForNymID(strSourceForNymID); // This also recalculates and sets  ** m_strNymID **
    // -------------------------------------
    // OTKeyCredential::SetPrivateContents will already set the public keys, which is why this argument is optional. But not all credentials are keys, so we must still retain the ability to explicitly set the public info. Even so, in the case of keys, private is below, so it will overwrite this.
    
    if ((NULL != pmapPublic) &&
        (NULL != pmapPrivate)) // You cannot pass public info in here unless you also pass private info.
    {
        if (false == pCredential->SetPublicContents(*pmapPublic))
        {
            OTLog::vError("In %s, line %d: Failed trying to call pCredential->SetPublicContents\n",
                          __FILE__, __LINE__);
            delete pCredential;
            pCredential = NULL;
            return NULL;
        }
    }
    // -------------------------------------
    // Private info must be passed in to create a credential. This saves a copy of the map, and for keys also loads the map all up into the OTKeypair objects (in the case of OTKeyCredentials anyway -- not all credentials are keys.)
    //
    bool bContentsReady = false;
    
    if (NULL != pmapPrivate) // Pre-generated keys were passed in for us to use.
        bContentsReady = pCredential->SetPrivateContents(*pmapPrivate); // So let's set them onto the master key.
    else
        // No keys were provided, so let's generate them ourselves...
        bContentsReady = pCredential->GenerateMasterkey(nBits);
    // -------------------------------------
    if (!bContentsReady)
    {
        OTLog::vError("In %s, line %d: Failed trying to SetPrivateContents or GenerateMasterkey\n",
                      __FILE__, __LINE__);
        delete pCredential;
        pCredential = NULL;
        return NULL;
    }
    else
    {
        OTPasswordData thePWData("Signing new master credential... OTCredential::CreateMaster");
        
        // Using m_Masterkey's actual signing key to sign "m_Masterkey the contract."
        //
        if (false == pCredential->SignNewMaster(NULL == pPWData ? &thePWData : pPWData))
        {
            OTLog::vError("In %s, line %d: Failed trying to call pCredential->SignNewMaster\n",
                          __FILE__, __LINE__);
            delete pCredential;
            pCredential = NULL;
            return NULL;
        }
    }
    
    // By this point, we have instantiated a new OTCredential, set the source string, hashed that
    // source string to get the NymID for this credential, and set the public and private info for
    // this credential (each a map of strings.) Since pCredential->m_Masterkey is derived from
    // OTKeyCredential, it also loaded up the 3 keypairs (authentication, encryption, and signing.)
    // Then we signed that master key with itself, with its signing key. (It's also an OTContract,
    // so it can be signed.) This also calculated the new master credential ID, and called
    // pCredential->SetMasterCredID. That is, the OTCredential's "master credential ID" is formed
    // as a hash of the signed contract that is its OTMasterkey.
    // BUT!!! We don't want to use a hash of the private key information, since others cannot verify
    // the hash without seeing our private key. We want OTMasterkey to create an 'official' signed
    // public version of itself, minus private keys, which is what can be sent to servers and to
    // other users, and which can be hashed to form the master credential ID (and verified later.)
    // ...Which is exactly what it does. Inside pCredential->SignNewMaster, a public version is created
    // and signed, and set onto that masterkey as m_strContents. It's then re-signed as the private
    // version, which contains m_strContents in encoded form, along with the private keys.
    //
    return pCredential;
}


size_t OTCredential::GetSubcredentialCount() const
{
    return m_mapSubcredentials.size();
}


const OTSubcredential * OTCredential::GetSubcredential(const OTString & strSubID, const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
    {
        const std::string str_cred_id = (*it).first;
        const OTSubcredential * pSub  = (*it).second;
        OT_ASSERT(NULL != pSub);
        // ------------------------
        // See if pSub, with ID str_cred_id, is on plistRevokedIDs...
        //
        if (NULL != plistRevokedIDs)
        {
            listOfStrings::const_iterator iter = std::find(plistRevokedIDs->begin(), plistRevokedIDs->end(), str_cred_id);
            if (iter != plistRevokedIDs->end()) // It was on the revoked list.
                continue; // Skip this revoked credential.
        }
        // At this point we know it's not on the revoked list, if one was passed in.
        // --------------------------------------------------
        if (strSubID.Compare(str_cred_id.c_str()))
            return pSub;
    }
    return NULL;
}


const OTSubcredential * OTCredential::GetSubcredentialByIndex(int32_t nIndex) const
{
    if ((nIndex < 0) || (nIndex >= static_cast<int64_t>(m_mapSubcredentials.size())))
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;
        
        FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
        {
            const std::string str_cred_id = (*it).first;
            const OTSubcredential * pSub  = (*it).second;
            OT_ASSERT(NULL != pSub);
            // ------------------------
            ++nLoopIndex; // 0 on first iteration.
            // ------------------------
            if (nIndex == nLoopIndex)
                return pSub;
        }
    }
    // -------------------------
    return NULL;
}


const std::string OTCredential::GetSubcredentialIDByIndex(size_t nIndex) const
{
    if (nIndex >= m_mapSubcredentials.size())
    {
        OTLog::vError("%s: Index out of bounds: %d\n", __FUNCTION__, nIndex);
    }
    else
    {
        int32_t nLoopIndex = -1;
        
        FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
        {
            const std::string str_cred_id = (*it).first;
            const OTSubcredential * pSub  = (*it).second;
            OT_ASSERT(NULL != pSub);
            // ------------------------
            ++nLoopIndex; // 0 on first iteration.
            // ------------------------
            if (static_cast<int64_t>(nIndex) == nLoopIndex)
                return str_cred_id;
        }
    }
    // -------------------------
    return NULL;
}


const OTKeypair & OTCredential::GetAuthKeypair(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
    {
        const std::string str_cred_id = (*it).first;
        const OTSubcredential * pSub  = (*it).second;
        OT_ASSERT(NULL != pSub);
        // ------------------------
        const OTSubkey * pKey = dynamic_cast<const OTSubkey *>(pSub);
        if (NULL == pKey) continue;
        // ------------------------
        // See if pKey, with ID str_cred_id, is on plistRevokedIDs...
        //
        if (NULL != plistRevokedIDs)
        {
            listOfStrings::const_iterator iter = std::find(plistRevokedIDs->begin(), plistRevokedIDs->end(), str_cred_id);
            if (iter != plistRevokedIDs->end()) // It was on the revoked list.
                continue; // Skip this revoked key.
        }
        // At this point we know it's a key credential, and we know it's not on
        // the revoked list. Therefore, let's return the key! (Any other future
        // smart criteria might go here before taking this final step...)
        //
        return pKey->m_AuthentKey;
    }
    
    // Didn't find any subcredentials we can use? For now, we'll return the master key instead.
    // This is purely for backwards compatibility reasons and eventually should be removed. That is,
    // masters should only be able to verify subkeys, and only subkeys should be able to do actions.
    // Capiche?
    //
    return m_Masterkey.m_AuthentKey;
}


const OTKeypair & OTCredential::GetEncrKeypair(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
    {
        const std::string str_cred_id = (*it).first;
        const OTSubcredential * pSub  = (*it).second;
        OT_ASSERT(NULL != pSub);
        // ------------------------
        const OTSubkey * pKey = dynamic_cast<const OTSubkey *>(pSub);
        if (NULL == pKey) continue;
        // ------------------------
        // See if pKey, with ID str_cred_id, is on plistRevokedIDs...
        //
        if (NULL != plistRevokedIDs)
        {
            listOfStrings::const_iterator iter = std::find(plistRevokedIDs->begin(), plistRevokedIDs->end(), str_cred_id);
            if (iter != plistRevokedIDs->end()) // It was on the revoked list.
                continue; // Skip this revoked key.
        }
        // At this point we know it's a key credential, and we know it's not on
        // the revoked list. Therefore, let's return the key! (Any other future
        // smart criteria might go here before taking this final step...)
        //
        return pKey->m_EncryptKey;
    }
    
    // Didn't find any subcredentials we can use? For now, we'll return the master key instead.
    // This is purely for backwards compatibility reasons and eventually should be removed. That is,
    // masters should only be able to verify subkeys, and only subkeys should be able to do actions.
    // Capiche?
    //
    return m_Masterkey.m_EncryptKey;
}


const OTKeypair & OTCredential::GetSignKeypair(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
    {
        const std::string str_cred_id = (*it).first;
        const OTSubcredential * pSub  = (*it).second;
        OT_ASSERT(NULL != pSub);
        // ------------------------
        const OTSubkey * pKey = dynamic_cast<const OTSubkey *>(pSub);
        if (NULL == pKey) continue;
        // ------------------------
        // See if pKey, with ID str_cred_id, is on plistRevokedIDs...
        //
        if (NULL != plistRevokedIDs)
        {
            listOfStrings::const_iterator iter = std::find(plistRevokedIDs->begin(), plistRevokedIDs->end(), str_cred_id);
            if (iter != plistRevokedIDs->end()) // It was on the revoked list.
                continue; // Skip this revoked key.
        }
        // At this point we know it's a key credential, and we know it's not on
        // the revoked list. Therefore, let's return the key! (Any other future
        // smart criteria might go here before taking this final step...)
        //
        return pKey->m_SigningKey;
    }
    
    // Didn't find any subcredentials we can use? For now, we'll return the master key instead.
    // This is purely for backwards compatibility reasons and eventually should be removed. That is,
    // masters should only be able to verify subkeys, and only subkeys should be able to do actions.
    // Capiche?
    //
    return m_Masterkey.m_SigningKey;
}


// NOTE: Until we figure out the rule by which we decide WHICH authentication key is the right auth key,
// or WHICH signing key is the right signing key, we'll just go with the first one we find.
// We'll also weed out any that appear on plistRevokedIDs, if it's passed in. (Optional.)

const OTAsymmetricKey & OTCredential::GetPublicAuthKey(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    return this->GetAuthKeypair(plistRevokedIDs).GetPublicKey();
}


const OTAsymmetricKey & OTCredential::GetPublicEncrKey(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    return this->GetEncrKeypair(plistRevokedIDs).GetPublicKey();
}


const OTAsymmetricKey & OTCredential::GetPublicSignKey(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    return this->GetSignKeypair(plistRevokedIDs).GetPublicKey();
}


const OTAsymmetricKey & OTCredential::GetPrivateAuthKey(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    return this->GetAuthKeypair(plistRevokedIDs).GetPrivateKey();
}


const OTAsymmetricKey & OTCredential::GetPrivateEncrKey(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    return this->GetEncrKeypair(plistRevokedIDs).GetPrivateKey();
}


const OTAsymmetricKey & OTCredential::GetPrivateSignKey(const listOfStrings * plistRevokedIDs/*=NULL*/) const
{
    return this->GetSignKeypair(plistRevokedIDs).GetPrivateKey();
}


OTCredential::~OTCredential()
{
    this->ClearSubcredentials();
}


void OTCredential::ClearSubcredentials()
{
    // ---------------------------
	while (!m_mapSubcredentials.empty())
	{
		OTSubcredential * pSub = m_mapSubcredentials.begin()->second;
		OT_ASSERT(NULL != pSub);
		// -----------
		delete pSub;
		pSub = NULL;
        // -----------
		m_mapSubcredentials.erase(m_mapSubcredentials.begin());
	} // while
    // --------------------------- 
}


// listRevokedIDs should contain a list of std::strings for IDs of already-revoked subcredentials.
// That way, SerializeIDs will know whether to mark them as valid while serializing them.
// bShowRevoked allows us to include/exclude the revoked credentials from the output (filter for valid-only.)
// bValid=true means we are saving OTPseudonym::m_mapCredentials. Whereas bValid=false means we're saving m_mapRevoked.
// pmapPubInfo is optional output, the public info for all the credentials will be placed inside, if a pointer is provided.
//
void OTCredential::SerializeIDs(OTString & strOutput, listOfStrings & listRevokedIDs,
                                mapOfStrings * pmapPubInfo/*=NULL*/,
                                mapOfStrings * pmapPriInfo/*=NULL*/,
                                bool bShowRevoked/*=false*/, bool bValid/*=true*/) const
{
    if (bValid || bShowRevoked)
    {
        strOutput.Concatenate("<masterCredential\n"
                              " ID=\"%s\"\n"
                              " valid=\"%s\""
                              "/>\n\n",
                              this->GetMasterCredID().Get(),
                              bValid ? "true" : "false");
        // ------------------------------------------------
        if (NULL != pmapPubInfo) // optional out-param.
            pmapPubInfo->insert(std::pair<std::string, std::string>(this->GetMasterCredID().Get(), this->GetPubCredential().Get()));
        // ------------------------------------------------
        if (NULL != pmapPriInfo) // optional out-param.
            pmapPriInfo->insert(std::pair<std::string, std::string>(this->GetMasterCredID().Get(), this->GetPriCredential().Get()));
        // ------------------------------------------------
    }
    // -------------------------------------
    FOR_EACH_CONST(mapOfSubcredentials, m_mapSubcredentials)
    {
        const std::string str_cred_id = (*it).first;
        const OTSubcredential * pSub  = (*it).second;
		OT_ASSERT(NULL != pSub);
        // -----------------------------
        // See if the current subcredential is on the Nym's list of "revoked" subcredential IDs.
        // If so, we'll skip serializing it here.
        //
        listOfStrings::iterator iter = std::find(listRevokedIDs.begin(), listRevokedIDs.end(), str_cred_id);
        
        // Was it on the 'revoked' list?
        // If not, then the subcredential isn't revoked, so it's still valid.
        //
        const bool bSubcredValid = bValid ? (iter == listRevokedIDs.end()) : false;
        // -----------------------------
        if (bSubcredValid || bShowRevoked)
        {
            const OTSubkey * pSubkey = dynamic_cast<const OTSubkey *>(pSub);
            
            if (NULL != pSubkey)
                strOutput.Concatenate("<keyCredential\n"
                                      " ID=\"%s\"\n"
                                      " masterID=\"%s\"\n"
                                      " valid=\"%s\""
                                      "/>\n\n",
                                      str_cred_id.c_str(),
                                      pSubkey->GetMasterCredID().Get(),
                                      bSubcredValid ? "true" : "false");
            else
                strOutput.Concatenate("<subCredential\n"
                                      " ID=\"%s\"\n"
                                      " masterID=\"%s\"\n"
                                      " valid=\"%s\""
                                      "/>\n\n",
                                      str_cred_id.c_str(),
                                      pSub->GetMasterCredID().Get(),
                                      bSubcredValid ? "true" : "false");
            // ------------------------------------------------
            if (NULL != pmapPubInfo) // optional out-param.
                pmapPubInfo->insert(std::pair<std::string, std::string>(str_cred_id.c_str(), pSub->GetPubCredential().Get()));
            // ------------------------------------------------
            if (NULL != pmapPriInfo) // optional out-param.
                pmapPriInfo->insert(std::pair<std::string, std::string>(str_cred_id.c_str(), pSub->GetPriCredential().Get()));
            // ------------------------------------------------
        } // if (bSubcredValid)
    } // FOR_EACH_CONST
    // -------------------------------------
}
