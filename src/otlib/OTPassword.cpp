/**************************************************************
 *
 *  OTPassword.cpp
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

#include "OTPassword.hpp"

#include "OTCrypto.hpp"
#include "OTLog.hpp"

#include <algorithm>
#include <functional>
#include <numeric>


#ifdef _WIN32
#include <WinsockWrapper.h>
#endif


#ifdef PREDEF_PLATFORM_UNIX
// for mlock and munlock
#include <sys/types.h>
#include <sys/mman.h>
#include <limits.h>

#ifndef PAGESIZE
#include <unistd.h>
#define PAGESIZE sysconf(_SC_PAGESIZE)
#endif

#define mlock(a,b) \
    mlock(((void *)(((size_t)(a)) & (~((PAGESIZE)-1)))), \
    (((((size_t)(a)) + (b)-1) | ((PAGESIZE)-1)) + 1) - (((size_t)(a)) & (~((PAGESIZE)-1))))
#define munlock(a,b) \
    munlock(((void *)(((size_t)(a)) & (~((PAGESIZE)-1)))), \
    (((((size_t)(a)) + (b)-1) | ((PAGESIZE)-1)) + 1) - (((size_t)(a)) & (~((PAGESIZE)-1))))
#endif

static tthread::mutex secure_allocator_mutex;



void * _SecureAllocateVoid(const size_t _Count, const size_t _Size)
{	// allocate storage for _Count elements of type _Ty

    tthread::lock_guard<tthread::mutex> lock(secure_allocator_mutex);

    void *_Ptr = 0;

#ifdef _WIN32
    if (_Count == 0);
    else if (((size_t)(-1) / _Size < _Count)
        || (_Ptr = ::VirtualAlloc(NULL, _Count * _Size, MEM_COMMIT, PAGE_READWRITE)) == 0)
        std::bad_alloc();	// report no memory;
#else
    if (_Count == 0);
    else if (((size_t)(-1) / _Size < _Count)
        || (_Ptr = ::operator new(_Count * _Size)) == 0)
        std::bad_alloc();	// report no memory
#endif
        

    if (NULL != _Ptr)
#ifdef _WIN32
        ::VirtualLock(_Ptr, _Count * _Size); // WINDOWS
#elif PREDEF_PLATFORM_UNIX
        // TODO:  Note: may need to add directives here so that mlock and munlock are not
        // used except where the user is running as a privileged process. (Because that
        // may be the only way we CAN use those functions...)
        if (mlock(_Ptr, _Count * _Size))
        OTLog::vError("WARNING: %s: unable to lock memory, secret keys may be swapped to disk!", __FUNCTION__); // UNIX
#else
        OTLog::vError("ERROR: %s: no mlock support!", __FUNCTION__); OT_FAIL; // OTHER (FAIL)
#endif

    return (_Ptr);
}


void _SecureDeallocateVoid(const size_t _Count, const size_t _Size, void * _Ptr) {
    
    tthread::lock_guard<tthread::mutex> lock(secure_allocator_mutex); // must lock.

    if (NULL != _Ptr && 0 < _Count){

#ifdef _WIN32
        ::SecureZeroMemory(_Ptr, _Count * _Size);
#else
        // This section securely overwrites the contents of a memory buffer
        // (which can otherwise be optimized out by an overzealous compiler...)
        volatile uint8_t * _Ptr = static_cast<volatile uint8_t *>(_Ptr);
        {
            size_t count = _Count * (_Size/sizeof(uint8_t));
            while (count--)
                *_Ptr++ = 0;
        }
#endif

#ifdef _WIN32
        ::VirtualUnlock(_Ptr, _Count * _Size);
#elif PREDEF_PLATFORM_UNIX
        if (munlock(_Ptr, _Count * _Size))
            OTLog::vError("WARNING: %s: unable to unlock memory, secret keys may be swapped to disk!", __FUNCTION__); // UNIX
#else
        OTLog::vError("ERROR: %s: no mlock support!", __FUNCTION__); OT_FAIL; // OTHER (FAIL)
#endif
    }

};

//virtual (pure)
OTPassword & OTPassword::operator=(const OTPassword & rhs) {
    OT_FAIL;  // this should be overidden by a child class.
}


//static
bool OTPassword::randomizeData(SecureDataVector & vData){

    SecureDataVector v(vData.size());

    bool b = OTCrypto::It()->RandomizeMemory(&v.at(0), v.size());

    std::copy(v.begin(), v.end(), vData.begin());

    return b;
}


//static
bool OTPassword::randomizeMemory(void * pMemory, size_t theSize){
    return OTCrypto::It()->RandomizeMemory(static_cast<uint8_t *>(pMemory), theSize);
}



//static
void OTPassword::zeroMemory(void * pMemory, size_t theSize)
{
    if (NULL != pMemory && 0 < theSize){

#ifdef _WIN32
        ::SecureZeroMemory(pMemory, theSize);
#else
        // This section securely overwrites the contents of a memory buffer
        // (which can otherwise be optimized out by an overzealous compiler...)
        volatile uint8_t * pMemory = static_cast<volatile uint8_t *>(pMemory);
        while (theSize--)
            *pMemory++ = 0;
#endif
    }
}

//static
void * OTPassword::safe_memcpy(void * pOut, uint32_t nOut, const void * pIn, const uint32_t nIn) {

    if ((NULL != pOut) || (0 != nOut)) OT_FAIL;

    if ((NULL == pIn) || (0 >= nIn)) {
        pOut = NULL;
        nOut = 0;
        return NULL;
    }

    // make an extra copy here.
    std::vector<uint8_t> v(static_cast<const uint8_t *>(pIn), static_cast<const uint8_t *>(pIn)+nIn);

    if (v.size() > nOut) return NULL;

#ifdef _WIN32
    std::copy(v.begin(), v.end(), stdext::make_checked_array_iterator(static_cast<uint8_t *>(pOut), nOut));
#else
    std::copy(v.begin(), v.end(), static_cast<uint8_t *>(pOut));
#endif

    return pOut;
}


// static
void OTPassword::copyMemory(const void * const pIn, const size_t & nIn, void * pOut, size_t & nOut) {

    if ((NULL != pOut) || (0 != nOut)) OT_FAIL;

    if ((NULL == pIn) || (0 >= nIn)) {
        pOut = NULL;
        nOut = 0;
        return;
    }

    SecureDataVector v(static_cast<const uint8_t *>(pIn), static_cast<const uint8_t *>(pIn)+nIn);

    uint8_t * v_copy = new uint8_t[v.size()];
    OTPassword::zeroMemory(static_cast<void *>(v_copy), v.size());


#ifdef _WIN32
    std::copy(v.begin(), v.end(), stdext::make_checked_array_iterator(v_copy, v.size()));
#else
    std::copy(v.begin(), v.end(), v_copy);
#endif

    pOut = static_cast<void *>(v_copy);
    nOut = sizeof(v.at(0)) * v.size();
}


VoidPointerPair OTPassword::getMemory(){
    void * data = static_cast<void *>(&this->_data.at(0));
    size_t length = sizeof(this->_data.at(0)) * this->_data.size();

    return VoidPointerPair(data, length);
}

void OTPassword::getMemory(void *& data, size_t & length) {
    VoidPointerPair ptr = this->getMemory();
    data = ptr.first;
    length = ptr.second;
}

ConstVoidPointerPair OTPassword::getMemoryConst() const{
    const void * data = static_cast<const void *>(&this->_data.at(0));
    const size_t length = sizeof(this->_data.at(0)) * this->_data.size();

    return ConstVoidPointerPair(data, length);
}


void OTPassword::getMemoryConst(const void *& data, size_t & length) const {
    ConstVoidPointerPair ptr = this->getMemoryConst();
    data = ptr.first;
    length = ptr.second;
}



StringPassword::StringPassword() {
    this->_type = STRING;
}


StringPassword::StringPassword(const std::string & data){
    this->_type = STRING;
    this->zero();

    {
        SecureString ss;
        ss.clear();
        std::copy(data.begin(), data.end(), std::back_inserter(ss));
        this->_string = ss; // copy
    }

    std::copy(data.begin(), data.end(), std::back_inserter(this->_data));
    this->_data.push_back('\0'); // append null terminator
}

StringPassword::StringPassword(const SecureString & data) {
    this->_type = STRING;
    this->zero();
    this->_string = data; // copy
    std::copy(data.begin(), data.end(), std::back_inserter(this->_data));
    this->_data.push_back('\0'); // append null terminator
}

StringPassword::StringPassword(const SecureDataVector & data){
    this->_type = STRING;
    this->zero();

    std::copy(data.begin(), data.end(), std::back_inserter(this->_data));
    std::copy(data.begin(), data.end(), std::back_inserter(this->_string));

    if (!(!this->_data.empty() && ('\0' == this->_data.back())))
        this->_data.push_back('\0'); // append null terminator only if there isn't one yet.
}

const char *StringPassword::getChars() const {
    return reinterpret_cast<const char *>(&this->_data.at(0));
}


void StringPassword::operator()(const SecureString & data) {
    this->zero();
    this->_string = data; // copy
    std::copy(data.begin(), data.end(), std::back_inserter(this->_data));
    this->_data.push_back('\0'); // append null terminator
}

void StringPassword::resize(size_t nNewSize) {
    this->_string.resize(nNewSize);
    this->_data.resize(0 == nNewSize ? 0 : nNewSize -1);
    this->_data.push_back('\0'); // append null terminator
}

void StringPassword::zero() {
    this->_data.clear();
    this->_string.clear();
}


// between the values of 33 and 122 (visible ASCII.)
uint32_t op_to_ascii(uint32_t i) { return i % 89 + 33; };

bool StringPassword::randomize(size_t nNewSize) {
    this->zero();
    this->_data.resize(nNewSize);

    bool ret = OTPassword::randomizeData(this->_data);
    std::transform(this->_data.begin(), this->_data.end(), std::back_inserter(this->_string), op_to_ascii);

    return ret;
}

BinaryPassword::BinaryPassword() {
    this->_type = BINARY;
}

BinaryPassword::BinaryPassword(const SecureDataVector & data) {
    this->_type = BINARY;

    this->_data = data; // copy
}

void BinaryPassword::operator()(const SecureDataVector & data) {
    this->zero();
    this->_data = data; // copy
}

BinaryPassword::BinaryPassword(const void * const data, const size_t length) {
    this->_type = BINARY;

    SecureDataVector v(static_cast<const uint8_t *>(data), static_cast<const uint8_t *>(data)+length);
    this->_data = v; //copy
}

void BinaryPassword::operator()(const void * const data, const size_t length){
    this->zero();
    if (NULL == data) return;
    if (0 >= length) return;

    SecureDataVector v(static_cast<const uint8_t *>(data), static_cast<const uint8_t *>(data)+length);
    this->_data = v; //copy
}


void BinaryPassword::append(const void * const data, const size_t length){
    if (NULL == data) return;
    if (0 >= length) return;

    SecureDataVector v(static_cast<const uint8_t *>(data), static_cast<const uint8_t *>(data)+length);

    std::copy(v.begin(), v.end(), std::back_inserter(this->_data));
}

VoidPointerPair BinaryPassword::getMemoryCopy() const{

    uint8_t * v = new uint8_t[this->_data.size()];

#ifdef _WIN32
    std::copy(this->_data.begin(), this->_data.end(), stdext::make_checked_array_iterator(v,this->_data.size()));       
#else
    std::copy(this->_data.begin(), this->_data.end(), v);
#endif
    
    void * data = static_cast<void *>(v);
    size_t length = sizeof(this->_data.at(0)) * this->_data.size();

    return VoidPointerPair(data, length);
}

void BinaryPassword::getMemoryCopy(void *& data, size_t & length) const{
    VoidPointerPair ptr = this->getMemoryCopy();
    data = ptr.first;
    length = ptr.second;
}

void BinaryPassword::getMemoryCopyOnto(void * const data, const size_t length) const {

    if (0 == length) {
        return;
    }

    SecureDataVector dv = this->_data;

    dv.resize(length);

#ifdef _WIN32
    std::copy(dv.begin(), dv.end(), stdext::make_checked_array_iterator(static_cast<uint8_t * const>(data), length));
#else
    std::copy(dv.begin(), dv.end(), static_cast<uint8_t * const>(data));
#endif
}

SecureString BinaryPassword::toString() {
    SecureString s;
    std::copy(this->_data.begin(), this->_data.end(), std::back_inserter(s));
    return s;
}

void BinaryPassword::resize(size_t nNewSize) {
    this->_data.resize(nNewSize);
}

void BinaryPassword::zero(){
    this->_data.clear();
}

bool BinaryPassword::randomize(size_t nNewSize){
    this->zero();

    this->_data.resize(nNewSize);

    return OTPassword::randomizeData(this->_data);
}





















































// _____________________________________________________________
