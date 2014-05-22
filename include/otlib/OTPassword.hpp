/**************************************************************
 *    
 *  OTPassword.hpp
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

#ifndef __OT_PASSWORD_HPP__
#define __OT_PASSWORD_HPP__

#include "OTCommon.hpp"

#include <vector>

class OTPassword;


// https://github.com/lorf/keepassx/blob/master/src/lib/SecString.cpp


EXPORT void * _SecureAllocateVoid(const size_t _Count, const size_t _Size);

template<class _Ty> inline // convert into secure.
_Ty *_SecureAllocate(size_t _Count, _Ty *) {
    return static_cast<_Ty *>(_SecureAllocateVoid(_Count, sizeof (_Ty)));
}

EXPORT void _SecureDeallocateVoid(const size_t _Count, const size_t _Size, void * _Ptr);

template<class _Ty> inline // convert into secure.
void _SecureDeallocate(size_t _Count, _Ty * _Ptr) {
    return _SecureDeallocateVoid(_Count, sizeof (_Ty), static_cast<void *>(_Ptr));
}



template<class _Ty>
class secure_allocator : public std::allocator<_Ty>
{
public:
    template<class _Other>
    secure_allocator<_Ty>& operator=(const secure_allocator<_Other>&)
    {	// assign from a related LockedVirtualMemAllocator (do nothing)
        return (*this);
    }

    template<class Other>
    struct rebind {
        typedef secure_allocator<Other> other;
    };

    typedef typename std::allocator<_Ty>::pointer pointer;
    typedef typename std::allocator<_Ty>::size_type size_type;

        pointer allocate(size_type _Count)
    {	// allocate array of _Count elements
        return (_SecureAllocate(_Count, (pointer)0));
    }
    pointer allocate(size_type _Count, const void *)
    {	// allocate array of _Count elements, ignore hint
        return (allocate(_Count));
    }

    void deallocate(pointer _Ptr, size_type _Count)
    {	// deallocate object at _Ptr, ignore size
        return (_SecureDeallocate(_Count, _Ptr));
    }
};

typedef std::basic_string<char, std::char_traits<char>, secure_allocator<char> > SecureString;

typedef std::vector<uint8_t, secure_allocator<uint8_t> > SecureDataVector;

typedef std::pair<void * const, const size_t> VoidPointerPair;
typedef std::pair<const void * const, const size_t> ConstVoidPointerPair;


template <typename T>
struct SecureVector {
    typedef std::vector<T, secure_allocator<T> > type;
};

#define OTPASSWORD_BLOCKSIZE    128

class OTPassword{
public:
    enum TYPE{
        STRING,
        BINARY
    };
protected:
    TYPE _type;
    SecureDataVector _data;

public:
    TYPE getType() const { return _type; }

    // convertable to a uint8_t vector.
    operator const SecureDataVector &() const { return this->_data; }
    SecureDataVector & getData()  { return this->_data; }
    const SecureDataVector & getDataConst() const  { return this->_data; }

    bool operator ==(const OTPassword & rhs) const {
        if (this->_type != rhs.getType()) return false;

        const SecureDataVector & a = rhs;
        return this->_data == a;
    }

    bool operator !=(const OTPassword & rhs) const { return !(this->operator==(rhs)); }

    virtual ~OTPassword() {};

    // do not pre-allocate!
    EXPORT VoidPointerPair getMemory(); //unsafe
    EXPORT void getMemory(void *& data, size_t & length); //unsafe

    // do not pre-allocate!
    EXPORT ConstVoidPointerPair getMemoryConst() const;
    EXPORT void getMemoryConst(const void *& data, size_t & length) const;

    virtual OTPassword & operator=(const OTPassword & rhs) = 0;
    virtual size_t length() const = 0;
    virtual void resize(size_t) = 0;
    virtual void zero() = 0;
    virtual bool randomize(size_t) = 0;


    static bool randomizeData(SecureDataVector & vData);
    static bool randomizeMemory(void * pMemory, size_t theSize);
    static void zeroMemory(void * pMemory, size_t theSize);

    // takes in pIn and nIn, and make a new array (no need to pre-allocate), caller deletes.
    static void copyMemory(const void * const pIn, const size_t & nIn, void * pOut, size_t & nOut);

};


class StringPassword : public OTPassword{
    SecureString _string;

public:
    EXPORT StringPassword();
    EXPORT StringPassword(const std::string & data);
    EXPORT StringPassword(const SecureString & data);
    EXPORT StringPassword(const SecureDataVector & data);

    EXPORT void operator()(const SecureString & data);
    SecureString getCopy() const { return this->_string; }

    const char * getChars() const;

    operator const SecureString &() const { return this->_string; }

    OTPassword & operator=(const OTPassword & rhs) {
        this->zero();
        this->operator()(StringPassword(rhs.getDataConst()));
        return *this;
    };

    // from Password.
    size_t length() const { return this->_string.length(); }
    EXPORT void resize(size_t nNewSize);
    EXPORT void zero();
    EXPORT bool randomize(size_t nNewSize = OTPASSWORD_BLOCKSIZE);
};

class BinaryPassword : public OTPassword{

public:
    EXPORT BinaryPassword();
    EXPORT BinaryPassword(const SecureDataVector & data);
    EXPORT void operator()(const SecureDataVector & data);
    SecureDataVector getCopy() const { return this->_data; }

    EXPORT BinaryPassword(const void * const data, const size_t length);
    EXPORT void operator()(const void * const data, const size_t length);

    EXPORT void append(const void * const data, const size_t length);

    // do not pre-allocate!
    EXPORT VoidPointerPair getMemoryCopy() const; // caller must delete
    EXPORT void getMemoryCopy(void *& data, size_t & length) const;

    // memory must be pre-allocated.
    EXPORT void getMemoryCopyOnto(void * const data, const size_t length) const;

    EXPORT SecureString toString();

    OTPassword & operator=(const OTPassword & rhs) {
        this->zero();
        this->operator()(rhs.getDataConst());
        return *this;
    }

    // from Password.
    size_t length() const { return this->_data.size(); }
    EXPORT void resize(size_t nNewSize);
    EXPORT void zero();
    EXPORT bool randomize(size_t nNewSize = OTPASSWORD_BLOCKSIZE);
};




#endif //__OT_PASSWORD_HPP__







