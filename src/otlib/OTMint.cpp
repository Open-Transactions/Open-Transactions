/************************************************************
 *    
 *  OTMint.cpp
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

#include "stdafx.hpp"

#include "OTMint.hpp"

#include "OTAccount.hpp"
#include "OTAsymmetricKey.hpp"
#include "OTFolders.hpp"
#include "OTLog.hpp"
#include "OTMessage.hpp"
#include "OTMintLucre.hpp"

#include "irrxml/irrXML.hpp"

#if defined (OT_CASH_USING_LUCRE)
//#include "OpenSSL_BIO.hpp"
#endif


//static
OTMint * OTMint::MintFactory()
{
    OTMint * pMint = NULL;
    
#if defined (OT_CASH_USING_LUCRE)
    pMint = new OTMint_Lucre;
#elif defined (OT_CASH_USING_MAGIC_MONEY)
//  pMint = new OTMint_MagicMoney;
    OTLog::vError("%s: Open-Transactions doesn't support Magic Money by Pr0duct Cypher (yet), "
                  "so it's impossible to instantiate a mint.\n", __FUNCTION__);
#else
    OTLog::vError("%s: Open-Transactions isn't built with any digital cash algorithms, "
                  "so it's impossible to instantiate a mint.\n", __FUNCTION__);
#endif
    return pMint;
}


//static
OTMint * OTMint::MintFactory(const OTString & strServerID, const OTString & strAssetTypeID)
{
    OTMint * pMint = NULL;
    
#if defined (OT_CASH_USING_LUCRE)
    pMint = new OTMint_Lucre(strServerID, strAssetTypeID);
#elif defined (OT_CASH_USING_MAGIC_MONEY)
//  pMint = new OTMint_MagicMoney;
    OTLog::vError("%s: Open-Transactions doesn't support Magic Money by Pr0duct Cypher (yet), "
                  "so it's impossible to instantiate a mint.\n", __FUNCTION__);
#else
    OTLog::vError("%s: Open-Transactions isn't built with any digital cash algorithms, "
                  "so it's impossible to instantiate a mint.\n", __FUNCTION__);
#endif
    return pMint;
}


//static
OTMint * OTMint::MintFactory(const OTString & strServerID, const OTString & strServerNymID, const OTString & strAssetTypeID)
{
    OTMint * pMint = NULL;
    
#if defined (OT_CASH_USING_LUCRE)
    pMint = new OTMint_Lucre(strServerID, strServerNymID, strAssetTypeID);
#elif defined (OT_CASH_USING_MAGIC_MONEY)
//  pMint = new OTMint_MagicMoney;
    OTLog::vError("%s: Open-Transactions doesn't support Magic Money by Pr0duct Cypher (yet), "
                  "so it's impossible to instantiate a mint.\n", __FUNCTION__);
#else
    OTLog::vError("%s: Open-Transactions isn't built with any digital cash algorithms, "
                  "so it's impossible to instantiate a mint.\n", __FUNCTION__);
#endif
    return pMint;
}


// SUBCLASSES OF OTMINT FOR EACH DIGITAL CASH ALGORITHM.

#if defined (OT_CASH_USING_MAGIC_MONEY)
// Todo:  Someday...
#endif // Magic Money


// Verify the current date against the VALID FROM / EXPIRATION dates.
// (As opposed to tokens, which are verified against the valid from/to dates.)
bool OTMint::Expired() const
{
	const time64_t CURRENT_TIME =	OTTimeGetCurrentTime();
	
	if ((CURRENT_TIME >= m_VALID_FROM) && (CURRENT_TIME <= m_EXPIRATION))
		return false;
	else
		return true;
}


void OTMint::ReleaseDenominations()
{
	while (!m_mapPublic.empty())
	{		
		OTASCIIArmor * pArmor = m_mapPublic.begin()->second;
		m_mapPublic.erase(m_mapPublic.begin());
		delete pArmor;
		pArmor = NULL;
	}
	while (!m_mapPrivate.empty())
	{		
		OTASCIIArmor * pArmor = m_mapPrivate.begin()->second;
		m_mapPrivate.erase(m_mapPrivate.begin());
		delete pArmor;
		pArmor = NULL;
	}
}


// If you want to load a certain Mint from string, then
// you will call LoadContractFromString() (say). Well this Releases the contract,
// before loading it, which calls InitMint() to zero out all the important pieces of
// data.
//
void OTMint::Release_Mint()
{
	ReleaseDenominations();
	
	m_CashAccountID.Release();
	
	if (m_pReserveAcct)
	{
		delete m_pReserveAcct;
		m_pReserveAcct = NULL;
	}
}


void OTMint::Release()
{
	Release_Mint();
    
	ot_super::Release(); // I overrode the parent, so now I give him a chance to clean up.
    
    InitMint();
}


OTMint::~OTMint()
{
    Release_Mint();
    
    if (NULL != m_pKeyPublic)
    {
        delete m_pKeyPublic;
        m_pKeyPublic = NULL;
    }
    else
        OTLog::vError("%s: the logic: if (NULL != m_pKeyPublic) failed, though it NEVER should. "
                      "(That pointer should never be NULL.)\n", __FUNCTION__);
}


void OTMint::InitMint()
{
	m_strContractType.Set("MINT");
	    
	m_nDenominationCount = 0;
	
	m_bSavePrivateKeys = false; // Determines whether it serializes private keys (no if false)
    
	// Mints expire and new ones are rotated in.
	// All tokens have the same series, and validity dates,
	// of the mint that created them.
	m_nSeries		= 0;
	m_VALID_FROM	= OT_TIME_ZERO;
	m_VALID_TO		= OT_TIME_ZERO;	
	m_EXPIRATION	= OT_TIME_ZERO;

	m_pReserveAcct	= NULL;
}


OTMint::OTMint(const OTString & strServerID, const OTString & strServerNymID, const OTString & strAssetTypeID)
: ot_super(strAssetTypeID), 
	m_ServerID(strServerID), 
	m_ServerNymID(strServerNymID),
    m_pKeyPublic(OTAsymmetricKey::KeyFactory()),
	m_AssetID(strAssetTypeID),
    m_nDenominationCount(0),
    m_bSavePrivateKeys(false),
    m_nSeries(0),
    m_VALID_FROM(OT_TIME_ZERO),
    m_VALID_TO(OT_TIME_ZERO),
    m_EXPIRATION(OT_TIME_ZERO),
    m_pReserveAcct(NULL)
{
	m_strFoldername.Set(OTFolders::Mint().Get());
	m_strFilename.Format("%s%s%s", strServerID.Get(), OTLog::PathSeparator(), strAssetTypeID.Get());
	
	InitMint();
}


OTMint::OTMint(const OTString & strServerID, const OTString & strAssetTypeID)
: ot_super(strAssetTypeID), 
	m_ServerID(strServerID), 
    m_pKeyPublic(OTAsymmetricKey::KeyFactory()),
	m_AssetID(strAssetTypeID),
    m_nDenominationCount(0),
    m_bSavePrivateKeys(false),
    m_nSeries(0),
    m_VALID_FROM(OT_TIME_ZERO),
    m_VALID_TO(OT_TIME_ZERO),
    m_EXPIRATION(OT_TIME_ZERO),
    m_pReserveAcct(NULL)
{
	m_strFoldername.Set(OTFolders::Mint().Get());
	m_strFilename.Format("%s%s%s", strServerID.Get(), OTLog::PathSeparator(), strAssetTypeID.Get());
	
	InitMint();
}


OTMint::OTMint() : ot_super(),
    m_pKeyPublic(OTAsymmetricKey::KeyFactory()),
    m_nDenominationCount(0),
    m_bSavePrivateKeys(false),
    m_nSeries(0),
    m_VALID_FROM(OT_TIME_ZERO),
    m_VALID_TO(OT_TIME_ZERO),
    m_EXPIRATION(OT_TIME_ZERO),
    m_pReserveAcct(NULL)
{
	InitMint();
}


bool OTMint::LoadContract()
{
	OTLog::Output(0, "OTMint::LoadContract OVERRIDE.\n");
	return LoadMint();
}


bool OTMint::LoadMint(const char * szAppend/*=NULL*/) // todo: server should always pass something here. client never should. Enforcement?
{
	if (!m_strFoldername.Exists())
		m_strFoldername.Set(OTFolders::Mint().Get());
	
	const OTString strServerID(m_ServerID), strAssetTypeID(m_AssetID);

	if (!m_strFilename.Exists())
	{
		if (NULL != szAppend)
			m_strFilename.Format("%s%s%s%s", strServerID.Get(), OTLog::PathSeparator(),  // server appends ".1" or ".PUBLIC" here.
								 strAssetTypeID.Get(), szAppend);
		else
			m_strFilename.Format("%s%s%s", strServerID.Get(), OTLog::PathSeparator(), strAssetTypeID.Get()); // client uses only asset ID, no append.
	}
	// --------------------------------------------------------------------
	OTString strFilename;
	if (NULL != szAppend)
		strFilename.Format("%s%s", strAssetTypeID.Get(), szAppend); // server side
	else
		strFilename = strAssetTypeID.Get();  // client side

	const char * szFolder1name	= OTFolders::Mint().Get();  // "mints"
	const char * szFolder2name	= strServerID.Get();    // "mints/SERVER_ID"
	const char * szFilename		= strFilename.Get();    // "mints/SERVER_ID/ASSET_TYPE_ID<szAppend>"
	// --------------------------------------------------------------------
	if (false == OTDB::Exists(szFolder1name, szFolder2name, szFilename))
	{
		OTLog::vOutput(0, "OTMint::LoadMint: File does not exist: %s%s%s%s%s\n", 
					   szFolder1name, OTLog::PathSeparator(), szFolder2name, OTLog::PathSeparator(), szFilename);
		return false;
	}
	// --------------------------------------------------------------------
	std::string strFileContents(OTDB::QueryPlainString(szFolder1name, szFolder2name, szFilename)); // <=== LOADING FROM DATA STORE.
	
	if (strFileContents.length() < 2)
	{
		OTLog::vError("OTMint::LoadMint: Error reading file: %s%s%s%s%s\n", 
					  szFolder1name, OTLog::PathSeparator(), szFolder2name, OTLog::PathSeparator(), szFilename);
		return false;
	}
	// --------------------------------------------------------------------
	// NOTE: No need to worry about the OT ARMORED file format, since
    // LoadContractFromString already handles that internally.
    
	OTString strRawFile(strFileContents.c_str());
	
	bool bSuccess = LoadContractFromString(strRawFile); // Note: This handles OT ARMORED file format.
	
	return bSuccess;
}


bool OTMint::SaveMint(const char * szAppend/*=NULL*/)
{
	if (!m_strFoldername.Exists())
		m_strFoldername.Set(OTFolders::Mint().Get());
	
	const OTString strServerID(m_ServerID), strAssetTypeID(m_AssetID);
	
	if (!m_strFilename.Exists())
	{
		if (NULL != szAppend)
			m_strFilename.Format("%s%s%s%s", strServerID.Get(), OTLog::PathSeparator(), // server side
								 strAssetTypeID.Get(), szAppend);
		else
			m_strFilename.Format("%s%s%s", strServerID.Get(), OTLog::PathSeparator(), strAssetTypeID.Get()); // client side
	}
	
	OTString strFilename;
	if (NULL != szAppend) 
		strFilename.Format("%s%s", strAssetTypeID.Get(), szAppend);
	else
		strFilename = strAssetTypeID.Get();
	
	const char * szFolder1name	= OTFolders::Mint().Get();
	const char * szFolder2name	= strServerID.Get();
	const char * szFilename		= strFilename.Get();
	// --------------------------------------------------------------------
	OTString strRawFile;

	if (!SaveContractRaw(strRawFile))
	{
		OTLog::vError("OTMint::SaveMint: Error saving Mintfile (to string):\n%s%s%s%s%s\n", szFolder1name,
					  OTLog::PathSeparator(), szFolder2name, OTLog::PathSeparator(), szFilename);
		return false;
	}
	// --------------------------------------------------------------------
	OTString strFinal;
    OTASCIIArmor ascTemp(strRawFile);
    
    if (false == ascTemp.WriteArmoredString(strFinal, m_strContractType.Get()))
    {
		OTLog::vError("OTMint::SaveMint: Error saving mint (failed writing armored string):\n%s%s%s%s%s\n",
					  szFolder1name, OTLog::PathSeparator(), szFolder2name, OTLog::PathSeparator(), szFilename);
		return false;
    }
    // --------------------------------------------------------------------
	bool bSaved = OTDB::StorePlainString(strFinal.Get(), szFolder1name, 
										 szFolder2name, szFilename); // <=== SAVING TO LOCAL DATA STORE.
	if (!bSaved)
	{
		if (NULL != szAppend) 
			OTLog::vError("OTMint::SaveMint: Error writing to file: %s%s%s%s%s%s\n", szFolder1name,
					  OTLog::PathSeparator(), szFolder2name, OTLog::PathSeparator(), szFilename, szAppend);
		else
			OTLog::vError("OTMint::SaveMint: Error writing to file: %s%s%s%s%s\n", szFolder1name,
						  OTLog::PathSeparator(), szFolder2name, OTLog::PathSeparator(), szFilename);	

		return false;
	}
	// --------------------------------------------------------------------
	return true;
}


// Make sure this contract checks out. Very high level. 
// Verifies ID and signature.
bool OTMint::VerifyMint(const OTPseudonym & theOperator)
{
	// Make sure that the supposed Contract ID that was set is actually
	// a hash of the contract file, signatures and all.
	if (false == VerifyContractID())
	{
		OTLog::Error("Error comparing Mint ID to Asset Contract ID in OTMint::VerifyMint\n");
		return false;
	}
	else if (false == VerifySignature(theOperator))
	{
		OTLog::Error("Error verifying signature on mint in OTMint::VerifyMint.\n");
		return false;
	}
	
	OTLog::Output(3, "\nWe now know that...\n"
			"1) The Asset Contract ID matches the Mint ID loaded from the Mint file.\n"
			"2) The SIGNATURE VERIFIED.\n\n");
	return true;
}


// Unlike other contracts, which calculate their ID from a hash of the file itself, a mint has
// the same ID as its Asset Contract.  When we open the Mint file, we read the Asset Type ID
// from it and then verify that it matches what we were expecting from the asset type.
bool OTMint::VerifyContractID()
{
	// I use the == operator here because there is no != operator at this time.
	// That's why you see the ! outside the parenthesis.
	if (!(m_ID == m_AssetID))
	{
		OTString str1(m_ID), str2(m_AssetID);
		
		OTLog::vError("\nMint ID does NOT match Asset Type ID in OTMint::VerifyContractID.\n%s\n%s\n"
				//				"\nRAW FILE:\n--->%s<---"
				"\n",
				str1.Get(), str2.Get()
				//				m_strRawFile.Get()
				);
		return false;
	}
	else {
		OTString str1(m_ID);
		OTLog::vOutput(2, "\nMint ID *SUCCESSFUL* match to Asset Contract ID:\n%s\n\n", str1.Get());
		return true;
	}
}


// The mint has a different key pair for each denomination.
// Pass in the actual denomination such as 5, 10, 20, 50, 100...
bool OTMint::GetPrivate(OTASCIIArmor & theArmor, int64_t lDenomination)
{
	FOR_EACH(mapOfArmor, m_mapPrivate)
	{
		OTASCIIArmor * pArmor = (*it).second;
		OT_ASSERT_MSG(NULL != pArmor, "NULL mint pointer in OTMint::GetPrivate.\n");
	
		if ((*it).first == lDenomination) // if this denomination (say, 50) matches the one passed in...
		{							   
			theArmor.Set(*pArmor);
			return true;
		}
	}
	
	return false;	
}


// The mint has a different key pair for each denomination.
// Pass in the actual denomination such as 5, 10, 20, 50, 100...
bool OTMint::GetPublic(OTASCIIArmor & theArmor, int64_t lDenomination)
{
	FOR_EACH(mapOfArmor, m_mapPublic)
	{
		OTASCIIArmor * pArmor = (*it).second;
		OT_ASSERT_MSG(NULL != pArmor, "NULL mint pointer in OTMint::GetPublic.\n");
		
		if ((*it).first == lDenomination) // if this denomination (say, 50) matches the one passed in...
		{
			theArmor.Set(*pArmor);
			return true;
		}
	}
	
	return false;
}


// If you need to withdraw a specific amount, pass it in here and the
// mint will return the largest denomination that is equal to or smaller
// than the amount.
// Then you can subtract the denomination from the amount and call this method
// again, and again, until it reaches 0, in order to create all the necessary
// tokens to reach the full withdrawal amount.
int64_t OTMint::GetLargestDenomination(int64_t lAmount)
{
	for (int32_t nIndex = GetDenominationCount()-1; nIndex >= 0; nIndex--)
	{
		int64_t lDenom = GetDenomination(nIndex);
		
		if (lDenom <= lAmount)
			return lDenom;
	}
	
	return 0;
}


// If you call GetDenominationCount, you can then use this method
// to look up a denomination by index.
// You could also iterate through them by index.
int64_t OTMint::GetDenomination(int32_t nIndex)
{
	// index out of bounds.
	if (nIndex > (m_nDenominationCount-1))
	{
		return 0;
	}
	
	int32_t nIterateIndex	= 0;
	
	for (mapOfArmor::iterator ii = m_mapPublic.begin(); 
		 ii != m_mapPublic.end(); 
		 ++ii, nIterateIndex++)
	{		
		OTASCIIArmor *	pArmor = (*ii).second;
		OT_ASSERT_MSG(NULL != pArmor, "NULL mint pointer in OTMint::GetDenomination.\n");
		
		if (nIndex == nIterateIndex)
			return (*ii).first;
	}
	
	return 0;
}


// The default behavior of this function does NOT save the private keys. It only
// serializes the public keys, and it is safe to send the object to the client.
// If the server needs to save the private keys, then call SetSavePrivateKeys() first.
void OTMint::UpdateContents()
{
    OT_ASSERT(NULL != m_pKeyPublic);
    
	OTString SERVER_ID(m_ServerID), SERVER_NYM_ID(m_ServerNymID),
             ASSET_ID(m_AssetID),   CASH_ACCOUNT_ID(m_CashAccountID);
	
    int64_t lFrom = OTTimeGetSecondsFromTime(m_VALID_FROM);
    int64_t lTo = OTTimeGetSecondsFromTime(m_VALID_TO);
    int64_t lExpiration = OTTimeGetSecondsFromTime(m_EXPIRATION);
	
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();
	
	m_xmlUnsigned.Concatenate("<?xml version=\"%s\"?>\n\n", "1.0");		
	
	m_xmlUnsigned.Concatenate("<mint version=\"%s\"\n"
							  " serverID=\"%s\"\n"
							  " serverNymID=\"%s\"\n"
							  " assetTypeID=\"%s\"\n"
							  " cashAcctID=\"%s\"\n"
							  " series=\"%d\"\n"
							  " expiration=\"%" PRId64"\"\n"
							  " validFrom=\"%" PRId64"\"\n"
							  " validTo=\"%" PRId64"\""
							  " >\n\n", 
							  m_strVersion.Get(), 
							  SERVER_ID.Get(), 
							  SERVER_NYM_ID.Get(), 
							  ASSET_ID.Get(),
							  CASH_ACCOUNT_ID.Get(),
							  m_nSeries, 
                              lExpiration, lFrom, lTo );
	
	OTASCIIArmor	armorPublicKey;
	m_pKeyPublic->GetPublicKey(armorPublicKey);
	m_xmlUnsigned.Concatenate("<mintPublicKey>\n%s</mintPublicKey>\n\n", armorPublicKey.Get());
	
	if (m_nDenominationCount)
	{
		if (m_bSavePrivateKeys)
		{
			m_bSavePrivateKeys = false;  // reset this back to false again. Use SetSavePrivateKeys() to set it true.
			
			FOR_EACH(mapOfArmor, m_mapPrivate)
			{	
				OTASCIIArmor * pArmor = (*it).second;
				OT_ASSERT_MSG(NULL != pArmor, "NULL private mint pointer in OTMint::UpdateContents.\n");
				
				m_xmlUnsigned.Concatenate("<mintPrivateInfo denomination=\"%lld\">\n"
										  "%s</mintPrivateInfo>\n\n", 
										  (*it).first, pArmor->Get());
			}
		}
		FOR_EACH(mapOfArmor, m_mapPublic)
		{		
			OTASCIIArmor * pArmor = (*it).second;
			OT_ASSERT_MSG(NULL != pArmor, "NULL public mint pointer in OTMint::UpdateContents.\n");
			
			m_xmlUnsigned.Concatenate("<mintPublicInfo denomination=\"%lld\">\n"
										  "%s</mintPublicInfo>\n\n", 
										  (*it).first, pArmor->Get());
		}
	}
	
	m_xmlUnsigned.Concatenate("</mint>\n");			
}


// return -1 if error, 0 if nothing, and 1 if the node was processed.
int32_t OTMint::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
    OT_ASSERT(NULL != m_pKeyPublic);

	int32_t nReturnVal = 0;
	
    const OTString strNodeName(xml->getNodeName());
    
	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do below, in the case of OTAccount.
	//if (nReturnVal = ot_super::ProcessXMLNode(xml))
	//	return nReturnVal;
	
	if (strNodeName.Compare("mint"))
	{
		OTString strServerID, strServerNymID, strAssetID, strCashAcctID;
		
		m_strVersion	= xml->getAttributeValue("version");					
		strServerID		= xml->getAttributeValue("serverID");
		strServerNymID	= xml->getAttributeValue("serverNymID");
		strAssetID		= xml->getAttributeValue("assetTypeID");
		strCashAcctID	= xml->getAttributeValue("cashAcctID");
		
		m_nSeries		= atoi(xml->getAttributeValue("series"));
		m_EXPIRATION	= OTTimeGetTimeFromSeconds(xml->getAttributeValue("expiration"));
        
        const OTString str_valid_from = xml->getAttributeValue("validFrom");
        const OTString str_valid_to   = xml->getAttributeValue("validTo");
        
        m_VALID_FROM = OTTimeGetTimeFromSeconds(str_valid_from.ToLong());
        m_VALID_TO = OTTimeGetTimeFromSeconds(str_valid_to.ToLong());
		
		m_ServerID.SetString(strServerID);
		m_ServerNymID.SetString(strServerNymID);
		m_AssetID.SetString(strAssetID);
		m_CashAccountID.SetString(strCashAcctID);
				
		if (m_pReserveAcct)
		{
			delete m_pReserveAcct;
			m_pReserveAcct = NULL;
		}
		
		// Every Mint has its own cash account. Here we load ours so it's ready for transactions.
		if (strCashAcctID.Exists())
			m_pReserveAcct = OTAccount::LoadExistingAccount(m_CashAccountID, m_ServerID);

        int64_t nValidFrom = OTTimeGetSecondsFromTime(m_VALID_FROM);
        int64_t nValidTo = OTTimeGetSecondsFromTime(m_VALID_TO);
        int64_t nExpiration = OTTimeGetSecondsFromTime(m_EXPIRATION);
		
		OTLog::vOutput(1,  
				//	"\n===> Loading XML for mint into memory structures..."
				"\n\nMint version: %s\n Server ID: %s\n Asset Type ID: %s\n Cash Acct ID: %s\n"
				"%s loading Cash Account into memory for pointer: OTMint::m_pReserveAcct\n"
				" Series: %d\n Expiration: %" PRId64"\n Valid From: %" PRId64"\n Valid To: %" PRId64"\n",
				m_strVersion.Get(), strServerID.Get(), strAssetID.Get(), strCashAcctID.Get(),
				(m_pReserveAcct != NULL) ? "SUCCESS" : "FAILURE",
				m_nSeries, nExpiration, nValidFrom, nValidTo);
		
		nReturnVal = 1;
	}
	
	else if (strNodeName.Compare("mintPublicKey"))
	{		
		OTASCIIArmor armorPublicKey;

		if (false == OTContract::LoadEncodedTextField(xml, armorPublicKey) || !armorPublicKey.Exists())
		{
			OTLog::Error("Error in OTMint::ProcessXMLNode: mintPublicKey field without value.\n");
			return (-1); // error condition
		}
		else 
		{
			m_pKeyPublic->SetPublicKey(armorPublicKey); // todo check this for failure.
		}
		
		return 1;
	}

	else if (strNodeName.Compare("mintPrivateInfo"))
	{		
		int64_t lDenomination = atol(xml->getAttributeValue("denomination"));					
		
		OTASCIIArmor * pArmor = new OTASCIIArmor;
		
		OT_ASSERT(NULL != pArmor);
		
		if (!OTContract::LoadEncodedTextField(xml, *pArmor) || !pArmor->Exists())
		{
			OTLog::Error("Error in OTMint::ProcessXMLNode: mintPrivateInfo field without value.\n");
			
			delete pArmor;
			pArmor = NULL;
			
			return (-1); // error condition
		}
		else 
		{			
			m_mapPrivate[lDenomination] = pArmor;
		}
		
		return 1;
	}
	
	else if (strNodeName.Compare("mintPublicInfo"))
	{		
		int64_t lDenomination = atol(xml->getAttributeValue("denomination"));					
		
		OTASCIIArmor * pArmor = new OTASCIIArmor;
		
		OT_ASSERT(NULL != pArmor);
		
		if (!OTContract::LoadEncodedTextField(xml, *pArmor) || !pArmor->Exists())
		{
			OTLog::Error("Error in OTMint::ProcessXMLNode: mintPublicInfo field without value.\n");
			
			delete pArmor;
			pArmor = NULL;
			
			return (-1); // error condition
		}
		else 
		{			
			m_mapPublic[lDenomination] = pArmor;
			m_nDenominationCount++; // Whether client or server, both sides have public. Each public denomination should increment this count.
		}
		
		return 1;
	}
		
	return nReturnVal;
}


/*
 // Just make sure theMessage has these members populated:
 //
 // theMessage.m_strNymID;
 // theMessage.m_strAssetID; 
 // theMessage.m_strServerID;
 
 // static method (call it without an instance, using notation: OTAccount::GenerateNewAccount)
 OTAccount * OTAccount::GenerateNewAccount(	const OTIdentifier & theUserID,	const OTIdentifier & theServerID, 
											const OTPseudonym & theServerNym,	const OTMessage & theMessage,
											const OTAccount::AccountType eAcctType=OTAccount::simple)
 
 
 // The above method uses this one internally...
 bool OTAccount::GenerateNewAccount(const OTPseudonym & theServer, const OTMessage & theMessage,
									const OTAccount::AccountType eAcctType=OTAccount::simple)
 
 
 OTAccount * pAcct = NULL;
 pAcct = OTAccount::LoadExistingAccount(ACCOUNT_ID, SERVER_ID);
 */


// Lucre step 1: generate new mint
// Make sure the issuer here has a private key
// theMint.GenerateNewMint(nSeries, VALID_FROM, VALID_TO, ASSET_ID, m_nymServer, 1, 5, 10, 20, 50, 100, 500, 1000, 10000, 100000);
void OTMint::GenerateNewMint(int32_t nSeries, time64_t VALID_FROM, time64_t VALID_TO, time64_t MINT_EXPIRATION,
							 const OTIdentifier & theAssetID, const OTIdentifier & theServerID, 
							 OTPseudonym & theNotary, 
							 int64_t nDenom1, int64_t nDenom2, int64_t nDenom3, int64_t nDenom4, int64_t nDenom5,
							 int64_t nDenom6, int64_t nDenom7, int64_t nDenom8, int64_t nDenom9, int64_t nDenom10)
{
	Release();
	
	m_AssetID		= theAssetID;
	m_ServerID		= theServerID;
	
	OTIdentifier SERVER_NYM_ID(theNotary);
	m_ServerNymID	= SERVER_NYM_ID;

	m_nSeries		= nSeries;
	m_VALID_FROM	= VALID_FROM;
	m_VALID_TO		= VALID_TO;
	m_EXPIRATION	= MINT_EXPIRATION;
	
	// Normally asset accounts are created based on an incoming message, 
	// so I'm just simulating that in order to make sure it gets its
	// necessary input values, such as asset type, server ID, etc.
	OTMessage theMessage;
	SERVER_NYM_ID.GetString(theMessage.m_strNymID);
	theAssetID.GetString(	theMessage.m_strAssetID);
	theServerID.GetString(	theMessage.m_strServerID);
	 
	/* OTAccount::
	 GenerateNewAccount(const OTIdentifier & theUserID, const OTIdentifier & theServerID, 
						const OTPseudonym & theServerNym, const OTMessage & theMessage,
						const AccountType eAcctType=simple);
	 */
	m_pReserveAcct	= OTAccount::GenerateNewAccount(SERVER_NYM_ID, theServerID, theNotary, theMessage, OTAccount::mint);

	if (m_pReserveAcct)
	{
		m_pReserveAcct->GetIdentifier(m_CashAccountID);
		OTLog::Output(0, "Successfully created cash reserve account for new mint.\n");
	}
	else
    {
		OTLog::Error("Error creating cash reserve account for new mint.\n");
	}
    // ----------------------------------------------------------------
	if (nDenom1)
	{
		AddDenomination(theNotary, nDenom1); // int32_t nPrimeLength default = 1024
	}
	if (nDenom2)
	{
		AddDenomination(theNotary, nDenom2); // int32_t nPrimeLength default = 1024
	}
	if (nDenom3)
	{
		AddDenomination(theNotary, nDenom3); // int32_t nPrimeLength default = 1024
	}
	if (nDenom4)
	{
		AddDenomination(theNotary, nDenom4); // int32_t nPrimeLength default = 1024
	}
	if (nDenom5)
	{
		AddDenomination(theNotary, nDenom5); // int32_t nPrimeLength default = 1024
	}
	if (nDenom6)
	{
		AddDenomination(theNotary, nDenom6); // int32_t nPrimeLength default = 1024
	}
	if (nDenom7)
	{
		AddDenomination(theNotary, nDenom7); // int32_t nPrimeLength default = 1024
	}
	if (nDenom8)
	{
		AddDenomination(theNotary, nDenom8); // int32_t nPrimeLength default = 1024
	}
	if (nDenom9)
	{
		AddDenomination(theNotary, nDenom9); // int32_t nPrimeLength default = 1024
	}
	if (nDenom10)
	{
		AddDenomination(theNotary, nDenom10); // int32_t nPrimeLength default = 1024
	}
}


bool OTMint::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}
