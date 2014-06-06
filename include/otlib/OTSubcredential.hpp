/************************************************************
 *    
 *  OTSubcredential.hpp
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

#ifndef __OT_SUBCREDENTIAL_HPP__
#define __OT_SUBCREDENTIAL_HPP__

#include "OTContract.hpp"

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

class OTContract;
class OTCredential;
class OTIdentifier;
class OTPassword;
class OTString;

// This is stored as an OTContract, and it must be signed by the
// master key. (which is also an OTSubcredential.)
//
class OTSubcredential : public OTContract
{
private:  // Private prevents erroneous use by other classes.
    typedef OTContract ot_super;
    friend class OTCredential;
// ------------------------------
protected:
    enum CredStoreAs {
        credPrivateInfo  = 0, // For saving the private keys, too. Default behavior.
        credPublicInfo   = 1, // For saving a version with public keys only.
        credMasterSigned = 2  // For saving a version with the master signature included, so the subkey can then countersign on top of that. (To prove that the subkey authorizes the master key's signature.) Only used by subkeys.
    };
    CredStoreAs     m_StoreAs; // Not serialized. 
// ------------------------------
protected:
    OTCredential  * m_pOwner;  // a pointer for convenience only. Do not cleanup.
    // ------------------------------
    OTString        m_strMasterCredID;    // All subcredentials within the same OTCredential share the same m_strMasterCredID. It's a hash of the signed master credential.
    OTString        m_strNymID;           // All subcredentials within the same OTCredential (including m_MasterKey) must have
    OTString        m_strSourceForNymID;  // the same NymID and source.
    // ------------------------------
    mapOfStrings    m_mapPublicInfo;  // A map of strings containing the credential's public info. This was originally 1 string but subclasses ended up needing a map of them. Who'da thought.
    mapOfStrings    m_mapPrivateInfo;  // A map of strings containing the credential's private info. This was originally 1 string but subclasses ended up needing a map of them. Who'da thought.
    // ------------------------------
    OTString        m_strMasterSigned; // A public version of the credential with the master credential's signature on it. (The final public version will contain the subkey's own signature on top of that.)
    OTString        m_strContents; // The actual final public credential as sent to the server. Does not include private keys, even on client side.
    // ------------------------------
    void UpdateMasterPublicToString    (OTString & strAppendTo); // Used in UpdateContents.
    void UpdatePublicContentsToString  (OTString & strAppendTo); // Used in UpdateContents.
    void UpdatePublicCredentialToString(OTString & strAppendTo); // Used in UpdateContents.
    void UpdatePrivateContentsToString (OTString & strAppendTo); // Used in UpdateContents.
    // ------------------------------
    inline void SetMasterSigned(const OTString & strMasterSigned) { m_strMasterSigned = strMasterSigned; }
    inline void SetContents    (const OTString & strContents)     { m_strContents     = strContents;     }
    // ------------------------------
    void SetNymIDandSource(const OTString & strNymID, const OTString & strSourceForNymID);
    void SetMasterCredID  (const OTString & strMasterCredID); // Used in all subclasses except OTMasterkey. (It can't contain its own ID, since it is signed, and the ID is its hash AFTER it's signed. So it could never contain its own ID.)
    // ------------------------------
    inline void StoreAsMasterSigned() { m_StoreAs = credMasterSigned; } // Upon signing, the credential reverts to credPrivateInfo again.
    inline void StoreAsPublic      () { m_StoreAs = credPublicInfo;   } // Upon signing, the credential reverts to credPrivateInfo again.
    // ------------------------------
    virtual bool SetPublicContents (const mapOfStrings & mapPublic );
    virtual bool SetPrivateContents(const mapOfStrings & mapPrivate,
                                          OTPassword   * pImportPassword=NULL); // if not NULL, it means to use this password by default.
    // ------------------------------
public:
    const mapOfStrings & GetPublicMap () const { return m_mapPublicInfo;  }
    const mapOfStrings & GetPrivateMap() const { return m_mapPrivateInfo; }
    // ------------------------------
    const OTString & GetMasterCredID()   const { return m_strMasterCredID;   } // MasterCredentialID (usually applicable.) OTMasterkey doesn't use this.
    const OTString & GetNymID()          const { return m_strNymID;          } // NymID for this credential.
    const OTString & GetNymIDSource()    const { return m_strSourceForNymID; } // Source for NymID for this credential. (Hash it to get ID.)
    const OTString & GetContents()       const { return m_strContents;       } // The actual, final, signed public credential. Public keys only.

EXPORT    const OTString & GetPubCredential()  const;  // More intelligent version of GetContents. Higher level.
    const OTString & GetPriCredential()  const;  // I needed this for exporting a Nym (with credentials) from the wallet.
        
    const OTString & GetMasterSigned()   const { return m_strMasterSigned;   } // For subkeys, the master credential signs first, then the subkey signs a version which contains the "master signed" version. (This proves the subkey really authorizes all this.) That "master signed" version is stored here in m_strMasterSigned. But the final actual public credential (which must be hashed to get the credential ID) is the contents, not the master signed. The contents is the public version, signed by the subkey, which contains the master-signed version inside of it as a data member (this variable in fact, m_strMasterSigned.) You might ask: then what's in m_strRawContents? Answer: the version that includes the private keys. Well at least, on the client side. On the server side, the raw contents will contain only the public version because that's all the client will send it. Que sera sera.
    // ------------------------------
    virtual bool VerifyInternally();    // Call VerifyNymID. Also verify m_strMasterCredID against the hash of m_pOwner->m_MasterKey (the master credential.) Verify that m_pOwner->m_MasterKey and *this have the same NymID. Then verify the signature of m_pOwner->m_MasterKey on m_strMasterSigned.
    // ------------------------------
    // We also inherit OTContract::VerifyContractID() which hashes the contents and compares to the ID as already set.
    // Unlike OTContract, a credential's ID is formed by hashing GetContents(), not by hashing m_xmlRawContents,
    // (that is, the public info only, not the version containing the private keys.) So we override CalculateContractID
    // to account for that.
    //
EXPORT virtual void CalculateContractID(OTIdentifier & newID);
    
    // We also inherit OTContract::VerifyContract() which tries to find the "contract" key. Of course, there is no
    // "contract" key in this case, so we should override it and provide our own version. What should it do? Well, it
    // should call VerifyContractID, VerifyInternally, VerifyMaster, and VerifyAgainstSource. (If that last step later
    // on adds too much slowdown, then we'll modify that function to check a signed file left for us by the IDENTITY
    // VERIFICATION SREVER which we can stick in a separate process.)
    // HOWEVER!! This may add vast unnecessary delay. For example, if we "VerifyContract" on EACH subcredential, which
    // we SHOULD do, then that means EACH subcredential is going to verify its Master (when they share the same master...)
    // and EACH subcredential is going to also re-verify its source (when they all share the same source!)
    // Solution?
    // Clearly the master itself only needs to be verified once, including its source, when the Nym is first loaded.
    // (Verifying it twice would be redundant.) After that, each subcredential should be verified internally and against
    // its master -- again, when first loaded. No need to verify it again after that, since it wouldn't have even loaded.
    // After that, any signature for that Nym should be verifiable using one of that Nym's subcredentials.
    //
    virtual bool VerifyContract();
    // ------------------------------
    bool VerifyNymID(); // Verifies that m_strNymID is the same as the hash of m_strSourceForNymID.
    // ------------------------------
    virtual bool VerifySignedByMaster();
    // ------------------------------
    void SetOwner(OTCredential & theOwner);
    // ------------------------------
    virtual void SetMetadata() {} // Only key-based subclasses will use this.
    // ------------------------------
    OTSubcredential();
    OTSubcredential(OTCredential & theOwner);
    // ------------------------------
    virtual ~OTSubcredential();
    virtual void Release();
    void Release_Subcredential();
    // ------------------------------
    virtual void UpdateContents();
    virtual int32_t  ProcessXMLNode(irr::io::IrrXMLReader*& xml);
    // ------------------------------
    virtual bool SaveContractWallet(std::ofstream & ofs) { return false; }
};


#endif // __OT_SUBCREDENTIAL_HPP__
