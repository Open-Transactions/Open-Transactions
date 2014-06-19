/************************************************************
 *    
 *  OTWallet.hpp
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

#ifndef __OT_WALLET_HPP__
#define __OT_WALLET_HPP__

#include "OTString.hpp"

#include <set>

class OTAccount;
class OTAssetContract;
class OTContract;
class OTIdentifier;
class OTMessage;
class OTPassword;
class OTPasswordData;
class OTPseudonym;
class OTPurse;
class OTServerContract;
class OTString;
class OTSymmetricKey;

typedef std::map<std::string, OTAccount *>                 mapOfAccounts;
typedef std::map<std::string, OTAssetContract *>           mapOfContracts;
typedef std::map<std::string, OTPseudonym *>               mapOfNyms;
typedef std::map<std::string, OTServerContract *>          mapOfServers;
typedef std::map<std::string, _SharedPtr<OTSymmetricKey> > mapOfSymmetricKeys;
typedef std::set<OTIdentifier>                             setOfIdentifiers;


class OTWallet
{
private:
	mapOfNyms           m_mapNyms;
	mapOfContracts      m_mapContracts;
	mapOfServers        m_mapServers;
	mapOfAccounts       m_mapAccounts;

    setOfIdentifiers    m_setNymsOnCachedKey;  // All the Nyms that use the Master key are listed here (makes it easy to see which ones are converted already.)
    
	OTString            m_strName;
	OTString            m_strVersion;
	
    // Let's say you have some private data that you want to store safely.
    // For example, your Bitmessage user/pass. Perhaps you want to throw
    // your Bitmessage connect string into your client-side sql*lite DB.
    // But you can't leave the password there in plaintext form! So instead,
    // you create a symmetric key to encrypt it with (stored here on this
    // map.)
    // Therefore your data, such as your Bitmessage password, is stored in
    // encrypted form to a symmetric key stored in the wallet. Then that
    // symmetric key is encrypted to the master password in the wallet.
    // If the master password ever changes, the symmetric keys on this map
    // can be re-encrypted to the new master password. Meanwhile the Bitmessage
    // connection string ITSELF, in your sql*lite DB, doesn't need to be re-
    // encrypted at all, since it's encrypted to the symmetric key, which,
    // though itself may be re-encrypted to another master password, the actual
    // contents of the symmetric key haven't changed.
    //
    // (This way you can change the wallet master passphrase, WITHOUT having
    // to go through your sql*lite database re-encrypting all the crap in there
    // that you might have encrypted previously before you changed your wallet
    // password.)
    //
    // That's why these are "extra" keys -- because you can create as many of
    // them as you want, and just use them for encrypting various data on the
    // client side.
    //
    mapOfSymmetricKeys  m_mapExtraKeys;
    
    // While waiting on server response to withdrawal,
    // store private coin data here for unblinding
	OTPurse     *	m_pWithdrawalPurse; 
    
public:
	OTString m_strFilename;
	OTString m_strDataFolder;
	
EXPORT	OTWallet();
        virtual ~OTWallet();
        virtual void Release();
        void Release_Wallet();
	//------------------------------------------------------------
EXPORT    bool IsNymOnCachedKey(const OTIdentifier & needle) const; // needle and haystack.
EXPORT    bool ConvertNymToCachedKey(OTPseudonym & theNym);
	//------------------------------------------------------------
    
EXPORT	OTPseudonym * GetOrLoadNym(const OTIdentifier & NYM_ID, const bool bChecking=false, const char * szFuncName=NULL,
                                   OTPasswordData * pPWData=NULL);
EXPORT	OTPseudonym * GetOrLoadPublicNym(const OTIdentifier & NYM_ID, const char * szFuncName=NULL);
EXPORT	OTPseudonym * GetOrLoadPrivateNym(const OTIdentifier & NYM_ID,
                                          const bool bChecking=false,
                                          const char * szFuncName=NULL,
                                          OTPasswordData * pPWData=NULL,
                                          OTPassword * pImportPassword=NULL);
	
EXPORT	OTAccount	* LoadAccount(OTPseudonym & theNym, 
                                  const OTIdentifier & ACCT_ID, 
                                  const OTIdentifier & SERVER_ID, const char * szFuncName=NULL);
    
EXPORT	OTAccount	* GetOrLoadAccount(OTPseudonym & theNym, 
                                       const OTIdentifier & ACCT_ID, 
                                       const OTIdentifier & SERVER_ID, const char * szFuncName=NULL);
	//------------------------------------------------------------	
	// Used by high-level wrapper.
	
EXPORT	int32_t GetNymCount(); 
EXPORT	int32_t GetServerCount();
EXPORT	int32_t GetAssetTypeCount();
EXPORT	int32_t GetAccountCount(); 

EXPORT	bool GetNym			(const int32_t iIndex, OTIdentifier & NYM_ID, OTString & NYM_NAME);
EXPORT	bool GetServer		(const int32_t iIndex, OTIdentifier & THE_ID, OTString & THE_NAME);
EXPORT	bool GetAssetType	(const int32_t iIndex, OTIdentifier & THE_ID, OTString & THE_NAME);
EXPORT	bool GetAccount		(const int32_t iIndex, OTIdentifier & THE_ID, OTString & THE_NAME);
	//------------------------------------------------------------
	
EXPORT	void DisplayStatistics(OTString & strOutput);
	
EXPORT	OTPseudonym *		GetNymByID(const OTIdentifier & NYM_ID);
EXPORT	OTPseudonym *		GetNymByIDPartialMatch(const std::string PARTIAL_ID);  // wallet name for nym also accepted.
	
EXPORT	void				AddServerContract(const OTServerContract & theContract);
EXPORT	OTServerContract *	GetServerContract(const OTIdentifier & SERVER_ID);
EXPORT	OTServerContract *	GetServerContractPartialMatch(const std::string PARTIAL_ID);  // wallet name for server also accepted.
	
EXPORT	void				AddNym			(const OTPseudonym & theNym);
EXPORT	void				AddAccount		(const OTAccount & theAcct);
	
EXPORT	void				AddAssetContract(const OTAssetContract & theContract);
EXPORT	OTAssetContract *	GetAssetContract(const OTIdentifier & theContractID);
EXPORT	OTAssetContract *	GetAssetContractPartialMatch(const std::string PARTIAL_ID);	  // wallet name for asset also accepted.
	// --------------------------------------------------------
        bool VerifyAssetAccount(OTPseudonym & theNym, 
                                OTAccount & theAcct, 
                                const OTIdentifier & SERVER_ID,
                                const OTString & strAcctID,
                                const char * szFuncName =NULL);	
	// --------------------------------------------------------
EXPORT	OTAccount * GetAccount(const OTIdentifier & theAccountID);
EXPORT	OTAccount * GetAccountPartialMatch(const std::string PARTIAL_ID);  // wallet name for account also accepted.
	// --------------------------------------------------------
EXPORT	OTAccount * GetIssuerAccount(const OTIdentifier & theAssetTypeID);
	// --------------------------------------------------------
	// While waiting on server response to a withdrawal, we keep the private coin
	// data here so we can unblind the response.
	// This information is so important (as important as the digital cash token
	// itself, until the unblinding is done) that we need to save the file right away.
EXPORT	void AddPendingWithdrawal(const OTPurse & thePurse);
        void RemovePendingWithdrawal();
        inline OTPurse * GetPendingWithdrawal() const { return m_pWithdrawalPurse; }
    // --------------------------------------------------------
EXPORT	bool LoadWallet(const char * szFilename=NULL);
EXPORT	bool SaveWallet(const char * szFilename=NULL);
        bool SaveContract(OTString & strContract); // For saving the wallet to a string.

EXPORT	bool SignContractWithFirstNymOnList(OTContract & theContract); // todo : follow-up on this and see what it's about.
    // --------------------------------------------------------
    // When the wallet's master passphrase changes, the extra symmetric keys
    // need to be updated to reflect that.
EXPORT  bool ChangePassphrasesOnExtraKeys(const OTPassword & oldPassphrase,
                                          const OTPassword & newPassphrase);
    // --------------------------------------------------------
    // These allow the client application to encrypt its own sensitive data.
    // For example, let's say the client application is storing your Bitmessage
    // username and password in its database. It can't store those in the clear,
    // so it encrypts the DB's sensitive data using Encrypt_ByKeyID("sql_db")
    // and accesses the data using Decrypt_ByKeyID("sql_db").
    // The string acts as a key to look up a symmetric key which is normally
    // stored in encrypted form, using the wallet's master key. Whenever the
    // wallet's master key is available (until it times out) the client app will
    // thus be able to use these symmetric keys without having to ask the user
    // to type a passphrase.
    // (We do this for Nyms already. These methods basically give us the same
    // functionality for symmetric keys as we already had for the wallet's Nyms.)
    //
EXPORT  bool Encrypt_ByKeyID(const std::string & key_id,
                             const OTString    & strPlaintext,
                                   OTString    & strOutput,
                             const OTString    * pstrDisplay=NULL,
                             const bool          bBookends  =true);

EXPORT  bool Decrypt_ByKeyID(const std::string & key_id,
                                   OTString    & strCiphertext,
                                   OTString    & strOutput,
                             const OTString    * pstrDisplay=NULL);
    // ------------------------------------------------------------------------
EXPORT  _SharedPtr<OTSymmetricKey> getOrCreateExtraKey(const std::string & str_KeyID,
                                                       const std::string * pReason=NULL); // Use this one.
EXPORT	_SharedPtr<OTSymmetricKey> getExtraKey(const std::string & str_id);            // Low level.
EXPORT	bool addExtraKey(const std::string & str_id, _SharedPtr<OTSymmetricKey> pKey); // Low level.
    // --------------------------------------------------------
	// These functions are low-level. They don't check for dependent data before deleting,
	// and they don't save the wallet after they do.
	//
	// (You have to handle that at a higher level.)
	
EXPORT	bool RemoveAssetContract (const OTIdentifier & theTargetID);
EXPORT	bool RemoveServerContract(const OTIdentifier & theTargetID);
	
	// higher level version of these two will require a server message, 
	// in addition to removing from wallet. (To delete them on server side.)
	//
EXPORT	bool RemoveAccount(const OTIdentifier & theTargetID);
EXPORT	bool RemoveNym    (const OTIdentifier & theTargetID);
    // --------------------------------------------------------

};


#endif // __OT_WALLET_HPP__
