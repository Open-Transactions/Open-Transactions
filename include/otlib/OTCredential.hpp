/************************************************************
 *    
 *  OTCredential.hpp
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

#ifndef __OT_CREDENTIAL_HPP__
#define __OT_CREDENTIAL_HPP__

#include "OTMasterkey.hpp"
#include "OTString.hpp"

// A nym contains a list of master credentials, via OTCredential.
// The whole purpose of a Nym is to be an identity, which can have
// master credentials.
//
// Each credential is like a master key for the Nym's identity,
// which can issue its own subkeys.
//
// Each subkey has 3 key pairs: encryption, signing, and authentication.
// Not all subcredentials are a subkey. For example, you might have a
// subcredential that uses Google Authenticator, and thus doesn't contain
// any keys, because it uses alternate methods for its own authentication.
//
// Each OTCredential contains a "master" subkey, and a list of subcredentials
// (some of them subkeys) signed by that master.
//
// The same class (subcredential/subkey) is used because there are master
// credentials and subcredentials, so we're using inheritance for "subcredential"
// and "subkey" to encapsulate the credentials, so we don't have to repeat code
// across both.
// We're using a "has-a" model here, since the OTCredential "has a" master
// subkey, and also "has a" list of subcredentials, some of which are subkeys.
//
// Each subcredential must be signed by the subkey that is the master key.
// Each subkey has 3 key pairs: encryption, signing, and authentication.
//
// Each key pair has 2 OTAsymmetricKeys (public and private.)
//
// I'm thinking that the Nym should also have a key pair (for whatever is
// its current key pair, copied from its credentials.)
//
// the master should never be able to do any actions except for sign subkeys.
// the subkeys, meanwhile should only be able to do actions, and not issue
// any new keys.

class OTCredential;
class OTIdentifier;
class OTPassword;
class OTPasswordData;
class OTSubcredential;
class OTSubkey;

typedef std::map<std::string, OTSubcredential *> mapOfSubcredentials;


// THE MASTER CREDENTIAL (below -- OTCredential)
//
// Contains a "master" subkey,
// and a list of subcredentials signed by that master.
// (Some of which are subkeys, since subkey inherits from
// subcredential.)
// Each subcredential can generate its own "credential" contract,
// even the master subcredential, so an OTCredential object
// actually may include many "credentials." (That is, each may be
// issued at separate times. Each may be registered on a server at
// separate times. Etc.)
//
// Each nym has multiple OTCredentials because there may be
// several master keys, each with their own subcredentials.
//
// ------------------------------------------------
// Two things to verify on a master credential:
//
// 1. If you hash m_pstrSourceForNymID, you should get m_pstrNymID.
// 2. m_pstrSourceForNymID should somehow verify m_Masterkey.GetContents().
//    For example, if m_pstrSourceForNymID contains CA DN info, then GetContents
//    should contain a verifiable Cert with that same DN info. Another example,
//    if m_pstrSourceForNymID contains a public key, then m_Masterkey.GetContents
//    should contain that same public key, or a cert that contains it. Another example,
//    if m_pstrSourceForNymID contains a URL, then m_Masterkey.GetContents should contain
//    a public key found at that URL, or a public key that, when hashed, matches one of
//    the hashes posted at that URL.
//
class OTCredential
{ 
private:
    OTMasterkey m_Masterkey;
    mapOfSubcredentials m_mapSubcredentials;
    // --------------------------------------
    OTString m_strNymID;
    OTString m_strSourceForNymID;
    // -------------------------------------- 
    OTString m_strMasterCredID; // This can't be stored in the master itself since it's a hash of that master. But this SHOULD be found in every subcredential signed by that master.

    OTPassword * m_pImportPassword; // Not owned. Just here for convenience. Sometimes it will be set, so that when loading something up (and decrypting it) the password is already available, so the user doesn't have to type it a million times (such as during import.) So we use it when it's available. And usually whoever set it, will immediately set it back to NULL when he's done.
private:
    OTCredential();
    // -------------------------------------------------------------------------------
    bool SetPublicContents (const mapOfStrings & mapPublic); // For master credential.
    bool SetPrivateContents(const mapOfStrings & mapPrivate); // For master credential.
    // -------------------------------------------------------------------------------
    void SetSourceForNymID(const OTString & strSourceForNymID); // The source is the URL/DN/pubkey that hashes to form the NymID. Any credential must verify against its own source.
    void SetMasterCredID (const OTString & strID); // The master credential ID is a hash of the master credential m_MasterKey
    // -------------------------------------------------------------------------------
    bool GenerateMasterkey(int32_t nBits=1024); // CreateMaster is able to create keys from scratch (by calling this function.)
    // -------------------------------------------------------------------------------
    bool SignNewMaster (OTPasswordData * pPWData=NULL); // SignMaster is used when creating master credential.
    bool SignNewSubcredential(OTSubcredential & theSubCred, OTIdentifier & theSubCredID_out, OTPasswordData * pPWData=NULL); // Used when creating a new subcredential.
    // -------------------------------------------------------------------------------
public:
    EXPORT OTPassword * GetImportPassword() { return m_pImportPassword; }
    EXPORT void SetImportPassword(OTPassword * pImportPassword) { m_pImportPassword = pImportPassword; }
    // -------------------------------------------------------------------------------
    static OTCredential * CreateMaster        (const OTString       & strSourceForNymID,
                                               const int32_t              nBits = 1024, // Ignored unless pmapPrivate is NULL
                                               const mapOfStrings   * pmapPrivate = NULL,
                                               const mapOfStrings   * pmapPublic = NULL,
                                                     OTPasswordData * pPWData=NULL);
    // -------------------------------------------------------------------------------
    static OTCredential * LoadMaster          (const OTString       & strNymID, // Caller is responsible to delete, in both CreateMaster and LoadMaster.
                                               const OTString       & strMasterCredID,
                                                     OTPasswordData * pPWData=NULL);
    // -------------------------------------------------------------------------------
    static OTCredential * LoadMasterFromString(const OTString       & strInput,
                                               const OTString       & strNymID, // Caller is responsible to delete, in both CreateMaster and LoadMaster.
                                               const OTString       & strMasterCredID,
                                                     OTPasswordData * pPWData=NULL,
                                                     OTPassword     * pImportPassword=NULL);
    // -------------------------------------------------------------------------------
    EXPORT bool Load_Master                   (const OTString       & strNymID,
                                               const OTString       & strMasterCredID,
                                                     OTPasswordData * pPWData=NULL);
    // -------------------------------------------------------------------------------
    EXPORT bool Load_MasterFromString         (const OTString       & strInput,
                                               const OTString       & strNymID,
                                               const OTString       & strMasterCredID,
                                                     OTPasswordData * pPWData=NULL,
                                                     OTPassword     * pImportPassword=NULL);
    // -------------------------------------------------------------------------------
    // For subcredentials that are specifically *subkeys*. Meaning it will
    // contain 3 keypairs: signing, authentication, and encryption. 
    //
    EXPORT bool AddNewSubkey       (const int32_t                nBits = 1024, // Ignored unless pmapPrivate is NULL
                                    const mapOfStrings     * pmapPrivate = NULL, // Public keys are derived from the private.
                                          OTPasswordData   * pPWData=NULL, // The master key will sign the subkey.
                                          OTSubkey        ** ppSubkey=NULL); // output
    // -------------------------------------------------------------------------------
    // For non-key credentials, such as for 3rd-party authentication.
    //
    EXPORT bool AddNewSubcredential(const mapOfStrings     & mapPrivate,
                                    const mapOfStrings     & mapPublic,
                                          OTPasswordData   * pPWData=NULL, // The master key will sign the subcredential.
                                          OTSubcredential ** ppSubcred=NULL); // output
    // ------------------------------
    EXPORT bool ReEncryptPrivateCredentials(OTPassword & theExportPassword, bool bImporting); // Like for when you are exporting a Nym from the wallet.
    // ------------------------------
    EXPORT bool LoadSubkey (const OTString & strSubID);
    EXPORT bool LoadSubcredential (const OTString & strSubID);
    EXPORT bool LoadSubkeyFromString (const OTString & strInput, const OTString & strSubID, OTPassword * pImportPassword=NULL);
    EXPORT bool LoadSubcredentialFromString(const OTString & strInput, const OTString & strSubID, OTPassword * pImportPassword=NULL);
    // ------------------------------
    EXPORT size_t GetSubcredentialCount() const;
    EXPORT const OTSubcredential * GetSubcredential (const OTString & strSubID, const listOfStrings * plistRevokedIDs=NULL) const;
    EXPORT const OTSubcredential * GetSubcredentialByIndex (int32_t nIndex) const;
    EXPORT const std::string GetSubcredentialIDByIndex(size_t nIndex) const;
    // ------------------------------
    EXPORT const OTString & GetPubCredential() const; // Returns: m_Masterkey's public credential string.
    EXPORT const OTString & GetPriCredential() const; // Returns: m_Masterkey's private credential string.
    EXPORT const OTString & GetMasterCredID() const; // Returns: Master Credential ID!
    EXPORT const OTString & GetNymID() const;
    EXPORT const OTString & GetSourceForNymID() const;
    // ------------------------------
    // listRevokedIDs should contain a list of std::strings for IDs of already-revoked subcredentials.
    // That way, SerializeIDs will know whether to mark them as valid while serializing them.
    // bShowRevoked allows us to include/exclude the revoked credentials from the output (filter for valid-only.)
    // bValid=true means we are saving OTPseudonym::m_mapCredentials. Whereas bValid=false means we're saving m_mapRevoked.
    //
    EXPORT void SerializeIDs(OTString      & strOutput,
                             listOfStrings & listRevokedIDs,
                             mapOfStrings  * pmapPubInfo=NULL,
                             mapOfStrings  * pmapPriInfo=NULL,
                             bool            bShowRevoked=false,
                             bool            bValid=true ) const;
    // ------------------------------
    EXPORT bool VerifyInternally() const;
    EXPORT bool VerifyAgainstSource() const;
    // ------------------------------
    EXPORT const OTMasterkey & GetMasterkey() const { return m_Masterkey; }
    // ------------------------------
    EXPORT int32_t GetPublicKeysBySignature(      listOfAsymmetricKeys & listOutput,
                                        const OTSignature          & theSignature,
                                              char                   cKeyType='0' ) const; // 'S' (signing key) or 'E' (encryption key) or 'A' (authentication key)
    // ------------------------------
    EXPORT const OTAsymmetricKey & GetPublicAuthKey(const listOfStrings * plistRevokedIDs=NULL) const;
    EXPORT const OTAsymmetricKey & GetPublicEncrKey(const listOfStrings * plistRevokedIDs=NULL) const;
    EXPORT const OTAsymmetricKey & GetPublicSignKey(const listOfStrings * plistRevokedIDs=NULL) const;
    // ------------------------------
    EXPORT const OTAsymmetricKey & GetPrivateSignKey(const listOfStrings * plistRevokedIDs=NULL) const;
    EXPORT const OTAsymmetricKey & GetPrivateEncrKey(const listOfStrings * plistRevokedIDs=NULL) const;
    EXPORT const OTAsymmetricKey & GetPrivateAuthKey(const listOfStrings * plistRevokedIDs=NULL) const;
    // ------------------------------
    EXPORT const OTKeypair & GetAuthKeypair(const listOfStrings * plistRevokedIDs=NULL) const;
    EXPORT const OTKeypair & GetEncrKeypair(const listOfStrings * plistRevokedIDs=NULL) const;
    EXPORT const OTKeypair & GetSignKeypair(const listOfStrings * plistRevokedIDs=NULL) const;
    // ------------------------------
    EXPORT void ClearSubcredentials();
    EXPORT ~OTCredential();
    // --------------------------------------
};


#endif // __OT_CREDENTIAL_HPP__
