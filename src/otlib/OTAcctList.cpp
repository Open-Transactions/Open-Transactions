/************************************************************
 *
 *  OTAcctList.cpp
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

#include "OTAcctList.hpp"

#include "OTLog.hpp"
#include "OTMessage.hpp"

#include "irrxml/irrXML.hpp"

#ifdef _WIN32
//#include <Mmsystem.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

using namespace irr;
using namespace io;


void TranslateAccountTypeToString(OTAccount::AccountType theType, OTString & strAcctType);


OTAccount::AccountType TranslateAccountTypeStringToEnum(const OTString & strAcctType);


// mapOfStrings			m_mapAcctIDs; // AcctIDs as second mapped by ASSET TYPE ID as first.
// mapOfWeakAccounts	m_mapWeakAccts; // Weak pointers to accounts that may still be in memory, mapped by ACCOUNT ID.

OTAcctList::OTAcctList() : m_AcctType(OTAccount::voucher) // the default type of acct it will create when it needs to, unless default is changed.
{

}


OTAcctList::OTAcctList(OTAccount::AccountType eAcctType) : m_AcctType(eAcctType)
{

}


void OTAcctList::Serialize(OTString & strAppend)
{
	OTString strAcctType;
	TranslateAccountTypeToString(m_AcctType, strAcctType);

	strAppend.Concatenate("<accountList type=\"%s\" count=\"%d\" >\n\n",
						  strAcctType.Get(), m_mapAcctIDs.size());
	// -----------------

	FOR_EACH(mapOfStrings, m_mapAcctIDs)
	{
		const std::string str_asset_type_id	= (*it).first;
		const std::string str_account_id	= (*it).second;
		OT_ASSERT((str_asset_type_id.size()>0) && (str_account_id.size()>0));

		strAppend.Concatenate("<accountEntry assetTypeID=\"%s\" accountID=\"%s\" />\n\n",
							  str_asset_type_id.c_str(), str_account_id.c_str());
	}
	// -----------------
	strAppend.Concatenate("</accountList>\n\n");
}


int32_t OTAcctList::ReadFromXMLNode(irr::io::IrrXMLReader*& xml, const OTString & strAcctType, const OTString & strAcctCount)
{
	if (!strAcctType.Exists())
	{
		OTLog::Error("OTAcctList::ReadFromXMLNode: Failed: Empty accountList 'type' attribute.\n");
		return (-1);
	}

	m_AcctType = TranslateAccountTypeStringToEnum(strAcctType);

	if (OTAccount::err_acct == m_AcctType)
	{
		OTLog::Error("OTAcctList::ReadFromXMLNode: Failed: accountList 'type' attribute contains unknown value.\n");
		return (-1);
	}

	// -----------------------------------------------
	//
	// Load up the account IDs.
	//
	int32_t nCount	= strAcctCount.Exists() ? atoi(strAcctCount.Get()) : 0;
	if (nCount > 0)
	{
		while (nCount-- > 0)
		{
//			xml->read();
			if (false == OTContract::SkipToElement(xml))
			{
				OTLog::Output(0, "OTAcctList::ReadFromXMLNode: Failure: Unable to find expected element.\n");
				return (-1);
			}
			// --------------------------------------

			if ((xml->getNodeType() == EXN_ELEMENT) && (!strcmp("accountEntry", xml->getNodeName())))
			{
				OTString strAssetTypeID	= xml->getAttributeValue("assetTypeID"); // Asset Type ID of this account.
				OTString strAccountID	= xml->getAttributeValue("accountID"); // Account ID for this account.

				// ----------------------------------

				if (!strAssetTypeID.Exists() || !strAccountID.Exists())
				{
					OTLog::vError("OTAcctList::ReadFromXMLNode: Error loading accountEntry: Either the assetTypeID (%s), "
								 "or the accountID (%s) was EMPTY.\n", strAssetTypeID.Get(), strAccountID.Get());
					return (-1);
				}

				// Success
				m_mapAcctIDs.insert(std::pair<std::string, std::string>(strAssetTypeID.Get(), strAccountID.Get())); // <=============
			}
			else
			{
				OTLog::Error("OTAcctList::ReadFromXMLNode: Expected accountEntry element in accountList.\n");
				return (-1); // error condition
			}
		} // while
	}
	// --------------------------------

	if (false == OTContract::SkipAfterLoadingField(xml))	// </accountList>
	{ OTLog::Output(0, "*** OTAcctList::ReadFromXMLNode: Bad data? Expected EXN_ELEMENT_END here, but "
					"didn't get it. Returning false.\n"); return (-1); }

	return 1;
}


// So far, no need to call this in the destructor, since these clean themselves up ANYWAY.
//
void OTAcctList::Release_AcctList()
{
	m_mapAcctIDs.clear();
	m_mapWeakAccts.clear();
}


void OTAcctList::Release()
{
	Release_AcctList();
}


OTAcctList::~OTAcctList()
{
	Release_AcctList();
}


_SharedPtr<OTAccount> OTAcctList::GetOrCreateAccount(OTPseudonym			& theServerNym,
												   const OTIdentifier	& ACCOUNT_OWNER_ID,
												   const OTIdentifier	& ASSET_TYPE_ID,
												   const OTIdentifier	& SERVER_ID,
												   bool					& bWasAcctCreated, // this will be set to true if the acct is created here. Otherwise set to false;
												   const int64_t             lStashTransNum/*=0*/)
{
	_SharedPtr<OTAccount> pRetVal;
	bWasAcctCreated = false;
	// ------------------------------------------------
	if (OTAccount::stash == m_AcctType)
	{
		if (lStashTransNum <= 0)
		{
			OTLog::Error("OTAcctList::GetOrCreateAccount: Failed attempt to create stash account without cron item #.\n");
			return pRetVal;
		}
	}

	// ------------------------------------------------
	// First, we'll see if there's already an account ID available for the requested asset type ID.
	//
	const OTString strAssetTypeID(ASSET_TYPE_ID);
	const std::string str_asset_type_id = strAssetTypeID.Get();

	// ------------------------------------
	OTString strAcctType;
	TranslateAccountTypeToString(m_AcctType, strAcctType);
	// ----------------------------------------------------------------

	mapOfStrings::iterator it_acct_ids = m_mapAcctIDs.find(str_asset_type_id);
	if (m_mapAcctIDs.end() != it_acct_ids) // Account ID *IS* already there for this asset type...
	{
		const std::string			str_account_id	= (*it_acct_ids).second; // grab account ID
		mapOfWeakAccounts::iterator	it_weak			= m_mapWeakAccts.find(str_account_id); // Try to find account pointer...

		if (m_mapWeakAccts.end() != it_weak)  // FOUND the weak ptr to the account! Maybe it's already loaded
		{
//			bool bSuccess = true;

			_WeakPtr<OTAccount>	pWeak	= (*it_weak).second; // first is acct ID, second is weak_ptr to account.

			try
			{
				_SharedPtr<OTAccount>	pShared(pWeak);

				// If success, then we have a shared pointer. But it's worrying (TODO) because this should have
				// gone out of scope and been destroyed by whoever ELSE was using it. The fact that it's still here...
				// well I'm glad not to double-load it, but I wonder why it's still here? And we aren't walking on anyone's
				// toes, right? If this were multi-threaded, then I'd explicitly lock a mutex here, honestly. But since things
				// happen one at a time on OT, I'll settle for a warning for now. I'm assuming that if the account's loaded
				// already somewhere, it's just a pointer sitting there, and we're not walking on each other's toes.
				//
				if (pShared)
				{
					OTLog::vOutput(0, "OTAcctList::GetOrCreateAccount: Warning: account (%s) was already in memory so I gave you a "
								   "pointer to the existing one. (But who else has a copy of it?) \n", str_account_id.c_str());
					return pShared;
				}

			}
			catch (...)
			{

			}


			// Though the weak pointer was there, the resource must have since been destroyed,
			// because I cannot lock a new shared ptr onto it.   :-(
			//
			// Therefore remove it from the map, and RE-LOAD IT.
			//
			m_mapWeakAccts.erase(it_weak);
		}

		// DIDN'T find the acct pointer, even though we had the ID.
		// (Or it was there, but we couldn't lock a shared_ptr onto it, so we erased it...)
		//
		// So let's load it now. After all, the Account ID *does* exist...
		//
		const OTString strAcctID(str_account_id.c_str());
		const OTIdentifier theAccountID(strAcctID);

		// The Account ID exists, but we don't have the pointer to a loaded account for it.
		// Soo.... let's load it.
		//
		OTAccount * pAccount = OTAccount::LoadExistingAccount(theAccountID, SERVER_ID);

		if (NULL == pAccount)
			OTLog::vError("OTAcctList::GetOrCreateAccount: Failed trying to load %s account with account ID: %s\n",
						  strAcctType.Get(),strAcctID.Get());
		else if (!pAccount->VerifySignature(theServerNym))
			OTLog::vError("OTAcctList::GetOrCreateAccount: Failed verifying server's signature on %s account with account ID: %s\n",
						  strAcctType.Get(),strAcctID.Get());
		else if (!pAccount->VerifyOwnerByID(ACCOUNT_OWNER_ID))
		{
			const OTString strOwnerID(ACCOUNT_OWNER_ID);
			OTLog::vError("OTAcctList::GetOrCreateAccount: Failed verifying owner ID (%s) on %s account ID: %s\n",
						  strOwnerID.Get(), strAcctType.Get(),strAcctID.Get());
		}
		else // SUCCESS loading the account...
		{
			OTLog::vOutput(3, "Successfully loaded %s account ID: %s Asset Type ID: %s\n",
						   strAcctType.Get(), strAcctID.Get(), str_asset_type_id.c_str());

			pRetVal								= _SharedPtr<OTAccount>(pAccount); // Create a shared pointer to the account, so it will be cleaned up automatically.
			m_mapWeakAccts [strAcctID.Get()]	= _WeakPtr<OTAccount>(pRetVal); // save a weak pointer to the acct, so we'll never load it twice, but we'll also know if it's been deleted.
		}
		return pRetVal;
		//
	} // (Asset Type ID was found on the AcctID Map -- a corresponding Account ID is already there for that asset type.)

	// ******************************************************************************

	// Not found... There's no account ID yet for that asset type ID.
	// That means we can create it...
	//
	OTMessage theMessage; // Here we set up theMessage
	ACCOUNT_OWNER_ID.GetString(theMessage.m_strNymID);
	ASSET_TYPE_ID.GetString(theMessage.m_strAssetID);
	SERVER_ID.GetString(theMessage.m_strServerID);

	OTAccount * pAccount = OTAccount::GenerateNewAccount(ACCOUNT_OWNER_ID,	// theUserID
														 SERVER_ID,			// theServerID
														 theServerNym,		// theServerNym
														 theMessage,
														 m_AcctType,		// OTAccount::voucher is default.
														 lStashTransNum);
	// ------------------------------------------------------------------------------------------

	if (NULL == pAccount)
		OTLog::vError(" OTAcctList::GetOrCreateAccount: Failed trying to generate %s account with asset type ID: %s\n",
					  strAcctType.Get(), str_asset_type_id.c_str());
	else // SUCCESS creating the account...
	{
		OTString strAcctID;
		pAccount->GetIdentifier(strAcctID);

		OTLog::vOutput(0, "Successfully created %s account ID: %s Asset Type ID: %s\n",
					   strAcctType.Get(), strAcctID.Get(), str_asset_type_id.c_str());

		pRetVal = _SharedPtr<OTAccount>(pAccount); // Create a shared pointer to the account, so it will be cleaned up automatically.

		m_mapWeakAccts	[strAcctID.Get()]				= _WeakPtr<OTAccount>(pRetVal); // save a weak pointer to the acct, so we'll never load it twice, but we'll also know if it's been deleted.
		m_mapAcctIDs	[theMessage.m_strAssetID.Get()]	= strAcctID.Get(); // Save the new acct ID in a map, keyed by asset type ID.

		bWasAcctCreated = true;
	}

	return pRetVal;
}
