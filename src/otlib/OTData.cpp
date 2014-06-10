/************************************************************
 *    
 *  OTData.cpp
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

#include "OTData.hpp"

#include "OTASCIIArmor.hpp"
#include "OTLog.hpp"
#include "OTPassword.hpp"


#if defined (OPENTXS_HAVE_NETINET_IN_H)
extern "C"
{
#include <netinet/in.h>
}
#endif


bool OTData::operator==(const OTData &s2) const
{
	if (m_lSize != s2.m_lSize) 
	{
		return false;
	}
	
	if (m_lSize == 0 && s2.m_lSize == 0) 
	{
		return true;
	}
	
	if (0 == memcmp(m_pData, s2.m_pData, m_lSize)) // TODO security: replace memcmp with a more secure version. Still, though, I am managing it internal to the class.
	{
		return true;
	}
	
	return false;
}


bool OTData::operator!=(const OTData &s2) const
{
	if (m_lSize == s2.m_lSize) 
	{
		return false;
	}
	
	if (m_lSize == 0 && s2.m_lSize == 0) 
	{
		return true;
	}
	
	if (0 == memcmp(m_pData, s2.m_pData, m_lSize) )  // TODO security: replace memcmp with a more secure version. Still, though, I am managing it internal to the class.
	{
		return false;
	}
	
	return true;
}


// First use reset() to set the internal position to 0.
// Then you pass in the buffer where the results go.
// You pass in the length of that buffer.
// It returns how much was actually read.
// If you start at position 0, and read 100 bytes, then
// you are now on position 100, and the next OTfread will 
// proceed from that position. (Unless you reset().)
//
uint32_t OTData::OTfread(uint8_t * buf, const uint32_t buflen)
{
    OT_ASSERT((NULL != buf) && (buflen > 0));

    std::vector<uint8_t> v;

    if ((NULL != m_pData) && (m_lSize > 0))
        v = std::vector<uint8_t>(static_cast<const uint8_t *>(m_pData), static_cast<const uint8_t *>(m_pData)+m_lSize);

    if (m_lPosition >= v.size()) {
        buf = NULL;
        return 0;
    }

    std::vector<uint8_t> v_out;

    size_t i = 0, len = buflen;
    for (std::vector<uint8_t>::iterator ii = v.begin(); ii != v.end(); ++ii){
        if (i++ == m_lPosition && len != 0) {
            m_lPosition++; len--;

            v_out.push_back(*ii);
        }
    }

#ifdef _WIN32
    std::copy(v_out.begin(), v_out.end(), stdext::make_checked_array_iterator(buf, v_out.size()));
#else
    std::copy(v_out.begin(), v_out.end(), buf);
#endif

    return v_out.size();
}


template<typename _Ty>
EXPORT	uint32_t OTData::OTfreadNetwork(_Ty & _Ref) {
    uint8_t * buf = new uint8_t[sizeof(_Ty)];

    uint32_t len = this->OTfread(buf, sizeof(_Ty));

    _Ty * ptr = reinterpret_cast<_Ty *>(buf);

    if (sizeof(_Ty) == sizeof(short))
        _Ref = ntohs(*ptr);

    if (sizeof(_Ty) == sizeof(long))
        _Ref = ntohl(*ptr);

    delete buf;

    OT_ASSERT(sizeof(_Ref) == len);

    return len;
}

template EXPORT uint32_t OTData::OTfreadNetwork(uint16_t & _Ref);
template EXPORT uint32_t OTData::OTfreadNetwork(uint32_t & _Ref);

size_t OTData::OTfreadData(void * data, const size_t size) {

    size_t len = this->OTfread(static_cast<uint8_t *>(data), static_cast<uint32_t>(size));

    if (0 == len) {
        OTLog::vError("%s: Error reading data.\n", __FUNCTION__);
        return false;
    }

    OT_ASSERT(len == size);

    return len;
}



OTData::OTData() : m_pData(NULL), m_lPosition(0), m_lSize(0)
{

}


OTData::OTData(const OTData &theSource) : m_pData(NULL), m_lPosition(0), m_lSize(0)
{	
	Assign(theSource);  // ***********
}


OTData::OTData(const OTASCIIArmor &theSource) : m_pData(NULL), m_lPosition(0), m_lSize(0)
{	
	if (theSource.Exists())
		theSource.GetData(*this); // ***********
}


OTData::OTData(const void * pNewData, uint32_t lNewSize) : m_pData(NULL), m_lPosition(0), m_lSize(0)
{	
	Assign(pNewData, lNewSize);
}


OTData::~OTData()
{ 
    Release_Data(); 
}


void OTData::zeroMemory()
{
    if (m_pData != NULL)
    {
        OTPassword::zeroMemory(m_pData, m_lSize);
    }
}


void OTData::Release_Data()
{
   if (m_pData != NULL)
   {
	   // For security reasons, we clear the memory to 0 when deleting the object. (Seems smart.)
       //
       OTPassword::zeroMemory(m_pData, m_lSize);
//	   memset(m_pData, 0, m_lSize);
       // --------------------------------------
       
	   delete [] (static_cast<uint8_t *>(m_pData));
	   
       // --------------------------------------
       // inline void Initialize() { m_pData = NULL; m_lSize = 0; m_lPosition = 0; }
       //
	   Initialize(); // If m_pData was already NULL, no need to re-Initialize().
   }
}


void OTData::Release()
{
    Release_Data();
    
    // no ot_super here since this is a base class.
}


OTData & OTData::operator=(OTData rhs) 
{
	this->swap(rhs);
	return *this;
}


void OTData::swap(OTData & rhs) 
{
	std::swap(m_pData,		rhs.m_pData);
	std::swap(m_lPosition,	rhs.m_lPosition);
	std::swap(m_lSize,		rhs.m_lSize);
}


void OTData::Assign(const OTData &theSource)
{
	if ((&theSource) == this)
		return; // can't assign to self.
	
	if (false == theSource.IsEmpty()) // If something is there... *********
	{
		Assign(theSource.m_pData, theSource.m_lSize); // Copy it.
	}
	else
		Release(); // Otherwise if it's empty, then empty this also.
}


bool OTData::IsEmpty() const
{
    return (m_lSize > 0) ? false : true;
}


void OTData::Assign(const void * pNewData, uint32_t lNewSize)
{
    Release(); // This releases all memory and zeros out all members.


    if (NULL == pNewData) return;
    if (0 >= lNewSize) return;


    std::vector<uint8_t> v(static_cast<const uint8_t *>(pNewData), static_cast<const uint8_t *>(pNewData)+lNewSize);


    uint8_t * v_copy = new uint8_t[v.size()];


#ifdef _WIN32
    std::copy(v.begin(), v.end(), stdext::make_checked_array_iterator(v_copy, v.size()));
#else
    std::copy(v.begin(), v.end(), v_copy);
#endif


    this->m_pData = static_cast<void *>(v_copy);
    this->m_lSize = sizeof(v.at(0)) * v.size();
}



bool OTData::Randomize(uint32_t lNewSize)
{
    BinaryPassword mem;
    mem.randomize(lNewSize);
    mem.getMemoryCopyOnto(m_pData, m_lSize);

    return true;
}



void OTData::Concatenate(const void * pAppendData, uint32_t lAppendSize)
{
    std::vector<uint8_t> v;
    std::vector<uint8_t> vAppend;


    if ((NULL != m_pData) && (m_lSize > 0))
        v = std::vector<uint8_t>(static_cast<const uint8_t *>(m_pData), static_cast<const uint8_t *>(m_pData)+m_lSize);


    if ((NULL != pAppendData) && (lAppendSize > 0))
        vAppend = std::vector<uint8_t>(static_cast<const uint8_t *>(pAppendData), static_cast<const uint8_t *>(pAppendData)+lAppendSize);


    std::copy(vAppend.begin(), vAppend.end(), std::back_inserter(v));


    this->Release();


    uint8_t * v_copy = new uint8_t[v.size()];


#ifdef _WIN32
    std::copy(v.begin(), v.end(), stdext::make_checked_array_iterator(v_copy, v.size()));
#else
    std::copy(v.begin(), v.end(), v_copy);
#endif


    this->m_pData = static_cast<void *>(v_copy);
    this->m_lSize = sizeof(v.at(0)) * v.size();
}



OTData & OTData::operator+=(const OTData & rhs)
{
    if (rhs.GetSize() > 0)
        this->Concatenate(rhs.m_pData, rhs.GetSize());

	return *this;
}


void OTData::SetSize(uint32_t lNewSize)
{
	Release();
	
	if (lNewSize > 0)
	{
		m_pData = static_cast<void*>(new uint8_t[lNewSize]);
		OT_ASSERT(NULL != m_pData);
		
        OTPassword::zeroMemory(m_pData, lNewSize);
        
		m_lSize = lNewSize;
	}
}
