/************************************************************
 *    
 *  OTKeyCredential.hpp
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

#ifndef __OT_KEY_CREDENTIAL_HPP__
#define __OT_KEY_CREDENTIAL_HPP__

#include "OTKeypair.hpp"
#include "OTSubcredential.hpp"

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

class OTAsymmetricKey;
class OTCredential;
class OTPassword;
class OTPasswordData;

typedef std::list<OTAsymmetricKey *> listOfAsymmetricKeys;


// CONTENTS needs to be PUBLIC and PRIVATE contents, EACH being a string map.
//
// The server (or anyone else) will only be able to see my public contents, not my private
// contents.
//
// The credential ID comes from a hash of the credential. (Which must be signed before it can be hashed.)
//
// Since I will have a public version of the credential, signed, for others, and I will have a private version
// signed, for myself, then I will have to store both signed versions, yes? I can't be re-signing things because
// the public version is hashed to form my credential ID. So once signed, we can't be signing it again later.
//
// So I think OTCredential will store a string containing the signed public version. Then it can include a copy
// of this string in the signed private version. (That way it always has both versions safe and signed, and it can
// always pull out its public version and send it to servers or whoever when it needs to.
//
// A subcredential can store its own signed public version, which must contain the master credential ID and be
// signed by that master key. If a subcredential is a subkey, then it must also be signed by itself.
//
// This is packaged up and attached to the signed private version, which includes the private keys, and is only
// stored on the client side.
//
// Might want also a version with IDs only.
//
// When creating a new credential, I want the ability to specify the public and private key information.
// But what if I don't specify? I should be able to pass NULL, and OT should be smart enough to generate
// the three certs and the three private keys, without me having to pass anything at all.
//
// If it's a master, this subcredential should be signed with itself.
// If it's a normal subcredential (not master) then it should be signed with
// its master, but not signed by itself since it may have no key.
// If it's a subkey (a form of subcredential) then it should be signed by itself
// AND by its master. And it must contain its master's ID.
// But if it's a master, it cannot contain its master's ID except maybe its own ID,
// but it is impossible for a contract to contain its own ID when its ID is a hash
// of the signed contract!
//
// I might make OTKeycredential and then have OTSubkey and OTMasterkey both derive from that.
// That way the master key doesn't have to contain its own ID, while the subkey can still contain
// its master's ID.

/// OTKeyCredential
/// A form of OTSubcredential that contains 3 key pairs: signing, authentication, and encryption.
/// We won't use OTKeyCredential directly but only as a common base class for OTSubkey and OTMasterkey.
///
class OTKeyCredential : public OTSubcredential
{
private:  // Private prevents erroneous use by other classes.
    typedef OTSubcredential ot_super;
    friend class OTCredential;
    // ------------------------------
protected:
    virtual bool SetPublicContents (const mapOfStrings & mapPublic);
    virtual bool SetPrivateContents(const mapOfStrings & mapPrivate,
                                          OTPassword   * pImportPassword=NULL); // if not NULL, it means to use this password by default.
    // ------------------------------
public:
    OTKeypair   m_SigningKey;  // Signing keys, for signing/verifying a "legal signature".
    OTKeypair   m_AuthentKey;  // Authentication keys, used for signing/verifying transmissions and stored files.
    OTKeypair   m_EncryptKey;  // Encryption keys, used for sealing/opening OTEnvelopes.
    // ------------------------------
    bool GenerateKeys(int32_t nBits=1024);   // Gotta start somewhere.
    bool ReEncryptKeys(OTPassword & theExportPassword, bool bImporting); // Used when importing/exporting a Nym to/from the wallet.
    // ------------------------------
    virtual bool VerifyInternally();     // Verify that m_strNymID is the same as the hash of m_strSourceForNymID. Also verify that *this == m_pOwner->m_MasterKey (the master credential.) Then verify the (self-signed) signature on *this.
    // ------------------------------
    bool VerifySignedBySelf();
    // ------------------------------
    virtual void SetMetadata();
    // ------------------------------
    OTKeyCredential();
    OTKeyCredential(OTCredential & theOwner);
    // ------------------------------
    bool SignContract(OTContract & theContract, OTPasswordData * pPWData=NULL);
    // ------------------------------
EXPORT int32_t GetPublicKeysBySignature(listOfAsymmetricKeys & listOutput,
                                    const OTSignature & theSignature,
                                    char cKeyType='0') const; // 'S' (signing key) or 'E' (encryption key) or 'A' (authentication key)
    // ------------------------------
    virtual ~OTKeyCredential();
    virtual void Release();
    void Release_Subkey();
};


#endif // __OT_KEY_CREDENTIAL_HPP__
