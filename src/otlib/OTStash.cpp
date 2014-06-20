/************************************************************
 *
 *  OTStash.cpp
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

#include "OTStash.hpp"

#include "OTContract.hpp"
#include "OTLog.hpp"
#include "OTStashItem.hpp"
#include "OTStorage.hpp"

#include "irrxml/irrXML.hpp"


void OTStash::Serialize(OTString & strAppend)
{
	strAppend.Concatenate("<stash name=\"%s\" count=\"%d\" >\n\n",
						  m_str_stash_name.c_str(), m_mapStashItems.size());
	// -----------------

	FOR_EACH(mapOfStashItems, m_mapStashItems)
	{
		const	std::string		str_asset_type_id	= (*it).first;
				OTStashItem *	pStashItem			= (*it).second;
		OT_ASSERT((str_asset_type_id.size()>0) && (NULL != pStashItem));

		strAppend.Concatenate("<stashItem assetTypeID=\"%s\" balance=\"%lld\" />\n\n",
							  pStashItem->GetAssetTypeID().Get(), pStashItem->GetAmount());
	}
	// -----------------
	strAppend.Concatenate("</stash>\n\n");
}


int32_t OTStash::ReadFromXMLNode(irr::io::IrrXMLReader*& xml, const OTString & strStashName, const OTString & strItemCount)
{
	if (!strStashName.Exists())
	{
		OTLog::Error("OTStash::ReadFromXMLNode: Failed: Empty stash 'name' attribute.\n");
		return (-1);
	}

	m_str_stash_name = strStashName.Get();

	// -----------------------------------------------
	//
	// Load up the stash items.
	//
	int32_t nCount	= strItemCount.Exists() ? atoi(strItemCount.Get()) : 0;
	if (nCount > 0)
	{
		while (nCount-- > 0)
		{
//			xml->read();
			if (false == OTContract::SkipToElement(xml))
			{
				OTLog::Output(0, "OTStash::ReadFromXMLNode: Failure: Unable to find expected element.\n");
				return (-1);
			}
			// --------------------------------------
			if ((xml->getNodeType() == irr::io::EXN_ELEMENT) && (!strcmp("stashItem", xml->getNodeName())))
			{
				OTString strAssetTypeID	= xml->getAttributeValue("assetTypeID"); // Asset Type ID of this account.
				OTString strAmount		= xml->getAttributeValue("balance"); // Account ID for this account.

				// ----------------------------------

				if (!strAssetTypeID.Exists() || !strAmount.Exists())
				{
					OTLog::vError("OTStash::ReadFromXMLNode: Error loading stashItem: Either the assetTypeID (%s), "
								  "or the balance (%s) was EMPTY.\n", strAssetTypeID.Get(), strAmount.Get());
					return (-1);
				}

				if (!CreditStash(strAssetTypeID.Get(), atol(strAmount.Get()) ))  // <===============
				{
					OTLog::vError("OTStash::ReadFromXMLNode: Failed crediting stashItem for stash %s. assetTypeID (%s), "
								  "balance (%s).\n", strStashName.Get(), strAssetTypeID.Get(), strAmount.Get());
					return (-1);
				}

				// (Success)
			}
			else
			{
				OTLog::Error("OTStash::ReadFromXMLNode: Expected stashItem element.\n");
				return (-1); // error condition
			}
		} // while
	}
	// --------------------------------
	if (false == OTContract::SkipAfterLoadingField(xml))	// </stash>
	{ OTLog::Output(0, "*** OTStash::ReadFromXMLNode: Bad data? Expected EXN_ELEMENT_END here, but "
					"didn't get it. Returning -1.\n"); return (-1); }

	return 1;
}


OTStash::OTStash()
{
	//m_mapStashItems
}


OTStash::OTStash(const OTString & strAssetTypeID, const int64_t lAmount/*=0*/)
{
	OTStashItem * pItem = new OTStashItem(strAssetTypeID, lAmount);
	OT_ASSERT(NULL != pItem);

	m_mapStashItems.insert(std::pair<std::string, OTStashItem *>(strAssetTypeID.Get(), pItem));
}


OTStash::OTStash(const OTIdentifier & theAssetTypeID, const int64_t lAmount/*=0*/)
{
	OTStashItem * pItem = new OTStashItem(theAssetTypeID, lAmount);
	OT_ASSERT(NULL != pItem);

	OTString strAssetTypeID(theAssetTypeID);

	m_mapStashItems.insert(std::pair<std::string, OTStashItem *>(strAssetTypeID.Get(), pItem));
}


OTStash::~OTStash()
{
	while (!m_mapStashItems.empty())
	{
		OTStashItem * pTemp = m_mapStashItems.begin()->second;
		OT_ASSERT(NULL != pTemp);
		delete pTemp; pTemp = NULL;
		m_mapStashItems.erase(m_mapStashItems.begin());
	}
}


// Creates it if it's not already there.
// (*this owns it and will clean it up when destroyed.)
//
OTStashItem * OTStash::GetStash(const std::string & str_asset_type_id)
{
	mapOfStashItems::iterator it = m_mapStashItems.find(str_asset_type_id);

	if (m_mapStashItems.end() == it) // It's not already there for this asset type.
	{
		const OTString strAssetTypeID(str_asset_type_id.c_str());
		OTStashItem * pStashItem = new OTStashItem (strAssetTypeID);
		OT_ASSERT(NULL != pStashItem);

		m_mapStashItems.insert(std::pair<std::string, OTStashItem *>(strAssetTypeID.Get(), pStashItem));
		return pStashItem;
	}

	OTStashItem * pStashItem = (*it).second;
	OT_ASSERT(NULL != pStashItem);

	return pStashItem;
}


int64_t OTStash::GetAmount(const std::string str_asset_type_id)
{
	OTStashItem * pStashItem = GetStash(str_asset_type_id); // (Always succeeds, and will OT_ASSERT() if failure.)

	return pStashItem->GetAmount();
}


bool OTStash::CreditStash(const std::string str_asset_type_id, const int64_t &lAmount)
{
	OTStashItem * pStashItem = GetStash(str_asset_type_id); // (Always succeeds, and will OT_ASSERT() if failure.)

	return pStashItem->CreditStash(lAmount);
}


bool OTStash::DebitStash(const std::string str_asset_type_id, const int64_t &lAmount)
{
	OTStashItem * pStashItem = GetStash(str_asset_type_id); // (Always succeeds, and will OT_ASSERT() if failure.)

	return pStashItem->DebitStash(lAmount);
}
