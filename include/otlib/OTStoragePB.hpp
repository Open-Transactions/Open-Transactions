/************************************************************
*
*  OTStoragePB.hpp
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

#ifndef __OT_STORAGE_PB_HPP__
#define __OT_STORAGE_PB_HPP__

#include "OTCommon.hpp"

#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "OTAssert.hpp"

#include <deque>
#include <iostream>
#include <map>
#include <vector>


#if defined(OTDB_PROTOCOL_BUFFERS)

#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4267 )
#endif


#if defined(ANDROID) || defined(OT_KEYRING_IOS)
#include "Generics-lite.pb.h"
#include "Markets-lite.pb.h"
#include "Bitcoin-lite.pb.h"
#include "Moneychanger-lite.pb.h"
#else


// (NOT Android.)
//
#include "Generics.pb.h"
#include "Markets.pb.h"
#include "Bitcoin.pb.h"
#include "Moneychanger.pb.h"
#endif


#ifdef _WIN32
#pragma warning( pop )
#endif


// To make subclasses of the various data objects (for Protocol Buffers):
//
// typedef ProtobufSubclass<theBaseType, theInternalType> theType;
//
// Also, REMEMBER for each object type declared, to add the hooks to the CPP file.
// (Instructions are below.)
//
// ----------------------------------------------------
/*
REPLACING OT_PROTOBUF_DECLARE() WITH A TEMPLATE FOR NOW...

#define OT_PROTOBUF_DECLARE(theType, theBaseType, theInternalType) \
class theType : public theBaseType, implements IStorablePB \
{		\
private: \
theInternalType __pb_obj; \
protected: \
theType() : theBaseType() { } \
public: \
::google::protobuf::MessageLite & getPBMessage() { return dynamic_cast<::google::protobuf::MessageLite>(__pb_obj); } \
static Storable * Instantiate() { return dynamic_cast<Storable *>(new theType()); } \
virtual ~theType() { } \
virtual void hookBeforePack(); \
virtual void hookAfterUnpack(); \
}
//	OT_PROTOBUF_DECLARE(BitcoinAcctPB, BitcoinAcct, BitcoinAcct_InternalPB);
//	OT_PROTOBUF_DECLARE(BitcoinServerPB, BitcoinServer, BitcoinServer_InternalPB);



#define DECLARE_PACKED_BUFFER_SUBCLASS(theNewType, thePackerType, theInterfaceType, theInternalType) \
class theNewType : public PackedBuffer \
{ \
friend class		thePackerType; \
friend OTInterface	theInterfaceType; \
theInternalType		m_buffer; \
\
public: \
theNewType() : PackedBuffer() {} \
virtual ~theNewType(); \
virtual bool PackString(std::string& theString); \
virtual bool UnpackString(std::string& theString); \
virtual bool ReadFromIStream(std::istream &inStream, int64_t lFilesize); \
virtual bool WriteToOStream(std::ostream &outStream); \
}
*/


namespace OTDB
{

	// Interface:    IStorablePB
	//
	DeclareBasedInterface(IStorablePB, IStorable)
		virtual ::google::protobuf::MessageLite * getPBMessage();
	virtual bool onPack(PackedBuffer& theBuffer, Storable& inObj);
	virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj);
	OT_USING_ISTORABLE_HOOKS;
	EndInterface

		// ----------------------------------------------------
		// BUFFER for Protocol Buffers.
		// Google's protocol buffers serializes to std::strings and streams. How conveeeeeenient.
		//
		//typedef PackedBufferSubclass<PackerPB, IStorablePB, std::string> BufferPB;
		DECLARE_PACKED_BUFFER_SUBCLASS(BufferPB, PackerSubclass<BufferPB>, IStorablePB, std::string);

	// ---------------
	// Protocol Buffers packer.
	//
	typedef PackerSubclass<BufferPB> PackerPB;

	// ----------------------------------------------------
	// Used for subclassing IStorablePB:
	//
	template<class theBaseType, class theInternalType, StoredObjectType theObjectType>
	class ProtobufSubclass : public theBaseType, implements IStorablePB
	{
	private:
		theInternalType __pb_obj;
		std::string m_Type;
	public:
		static Storable * Instantiate()
		{ return dynamic_cast<Storable *>(new ProtobufSubclass<theBaseType, theInternalType, theObjectType>); }

		ProtobufSubclass() : theBaseType(), IStorablePB() { m_Type = StoredObjectTypeStrings[static_cast<int32_t>(theObjectType)]; m_Type += "PB";
		/*std::cout << m_Type.c_str() << " -- Constructor" << std::endl;*/ }

		ProtobufSubclass(const ProtobufSubclass<theBaseType,theInternalType,theObjectType> & rhs) : theBaseType(), IStorablePB()
		{ m_Type = StoredObjectTypeStrings[static_cast<int32_t>(theObjectType)]; m_Type += "PB";
		/*std::cout << m_Type.c_str() << " -- Copy Constructor" << std::endl; */ rhs.CopyToObject(*this); }

		ProtobufSubclass<theBaseType,theInternalType,theObjectType> &
			operator= (const ProtobufSubclass<theBaseType,theInternalType,theObjectType> & rhs)
		{ rhs.CopyToObject(*this); return *this; }

		void CopyToObject(ProtobufSubclass<theBaseType,theInternalType,theObjectType> & theNewStorable) const
		{
			OTPacker * pPacker = OTPacker::Create(PACK_PROTOCOL_BUFFERS);
			const OTDB::Storable * pIntermediate = dynamic_cast<const OTDB::Storable *>(this);

			if (NULL == pPacker) { OT_FAIL; }
			PackedBuffer * pBuffer = pPacker->Pack(*(const_cast<OTDB::Storable*>(pIntermediate)));
			if (NULL == pBuffer) { OT_FAIL; }
			if (!pPacker->Unpack(*pBuffer, theNewStorable)) { OT_FAIL; }
			if (NULL != pPacker) { delete pPacker; pPacker = NULL; }
			if (NULL != pBuffer) { delete pBuffer; pBuffer = NULL; }
		}

		virtual ::google::protobuf::MessageLite * getPBMessage();

//		IStorable * clone(void) const
//			{return dynamic_cast<IStorable *>(new ProtobufSubclass<theBaseType, theInternalType, theObjectType>(*this));}

		virtual theBaseType * clone(void) const
		{  /*std::cout << "Cloning a " << m_Type.c_str() << std::endl;*/ return dynamic_cast<theBaseType *>(do_clone()); }

		IStorable * do_clone(void) const
		{  Storable * pNewStorable = Storable::Create(theObjectType, PACK_PROTOCOL_BUFFERS);
		if(NULL == pNewStorable) OT_FAIL;
		CopyToObject(*(dynamic_cast< ProtobufSubclass<theBaseType,theInternalType,theObjectType> * > (pNewStorable))); return dynamic_cast<IStorable *>(pNewStorable);}

		virtual ~ProtobufSubclass() { }
		OT_USING_ISTORABLE_HOOKS;
		virtual void hookBeforePack();  // <=== Implement this if you subclass.
		virtual void hookAfterUnpack(); // <=== Implement this if you subclass.
	};


#define DECLARE_PROTOBUF_SUBCLASS(theBaseType, theInternalType, theNewType, theObjectType) \
	template<> void ProtobufSubclass<theBaseType, theInternalType, theObjectType>::hookBeforePack(); \
	template<> void ProtobufSubclass<theBaseType, theInternalType, theObjectType>::hookAfterUnpack(); \
	typedef ProtobufSubclass<theBaseType, theInternalType, theObjectType>	theNewType

	// ---------------------------------------------
	// THE ACTUAL SUBCLASSES:

	DECLARE_PROTOBUF_SUBCLASS(OTDBString,	String_InternalPB,			StringPB,			STORED_OBJ_STRING);
	DECLARE_PROTOBUF_SUBCLASS(Blob,			Blob_InternalPB,			BlobPB,				STORED_OBJ_BLOB);
	DECLARE_PROTOBUF_SUBCLASS(StringMap,	StringMap_InternalPB,		StringMapPB,		STORED_OBJ_STRING_MAP);
	DECLARE_PROTOBUF_SUBCLASS(BitcoinAcct,	BitcoinAcct_InternalPB,		BitcoinAcctPB,		STORED_OBJ_BITCOIN_ACCT);
	DECLARE_PROTOBUF_SUBCLASS(BitcoinServer,BitcoinServer_InternalPB,	BitcoinServerPB,	STORED_OBJ_BITCOIN_SERVER);
	DECLARE_PROTOBUF_SUBCLASS(RippleServer,	RippleServer_InternalPB,	RippleServerPB,		STORED_OBJ_RIPPLE_SERVER);
	DECLARE_PROTOBUF_SUBCLASS(LoomServer,	LoomServer_InternalPB,		LoomServerPB,		STORED_OBJ_LOOM_SERVER);
	DECLARE_PROTOBUF_SUBCLASS(ServerInfo,	ServerInfo_InternalPB,		ServerInfoPB,		STORED_OBJ_SERVER_INFO);
	DECLARE_PROTOBUF_SUBCLASS(ContactAcct,	ContactAcct_InternalPB,		ContactAcctPB,		STORED_OBJ_CONTACT_ACCT);
	DECLARE_PROTOBUF_SUBCLASS(ContactNym,	ContactNym_InternalPB,		ContactNymPB,		STORED_OBJ_CONTACT_NYM);
	DECLARE_PROTOBUF_SUBCLASS(Contact,		Contact_InternalPB,			ContactPB,			STORED_OBJ_CONTACT);
	DECLARE_PROTOBUF_SUBCLASS(AddressBook,	AddressBook_InternalPB,		AddressBookPB,		STORED_OBJ_ADDRESS_BOOK);
	DECLARE_PROTOBUF_SUBCLASS(WalletData,	WalletData_InternalPB,		WalletDataPB,		STORED_OBJ_WALLET_DATA);
	DECLARE_PROTOBUF_SUBCLASS(MarketData,	MarketData_InternalPB,		MarketDataPB,		STORED_OBJ_MARKET_DATA);
	DECLARE_PROTOBUF_SUBCLASS(MarketList,	MarketList_InternalPB,		MarketListPB,		STORED_OBJ_MARKET_LIST);

	DECLARE_PROTOBUF_SUBCLASS(BidData,			OfferDataMarket_InternalPB,	BidDataPB,			STORED_OBJ_BID_DATA);
	DECLARE_PROTOBUF_SUBCLASS(AskData,			OfferDataMarket_InternalPB,	AskDataPB,			STORED_OBJ_ASK_DATA);
	DECLARE_PROTOBUF_SUBCLASS(OfferListMarket,	OfferListMarket_InternalPB,	OfferListMarketPB,	STORED_OBJ_OFFER_LIST_MARKET);
	DECLARE_PROTOBUF_SUBCLASS(TradeDataMarket,	TradeDataMarket_InternalPB,	TradeDataMarketPB,	STORED_OBJ_TRADE_DATA_MARKET);
	DECLARE_PROTOBUF_SUBCLASS(TradeListMarket,	TradeListMarket_InternalPB,	TradeListMarketPB,	STORED_OBJ_TRADE_LIST_MARKET);
	DECLARE_PROTOBUF_SUBCLASS(OfferDataNym,		OfferDataNym_InternalPB,	OfferDataNymPB,		STORED_OBJ_OFFER_DATA_NYM);
	DECLARE_PROTOBUF_SUBCLASS(OfferListNym,		OfferListNym_InternalPB,	OfferListNymPB,		STORED_OBJ_OFFER_LIST_NYM);
	DECLARE_PROTOBUF_SUBCLASS(TradeDataNym,		TradeDataNym_InternalPB,	TradeDataNymPB,		STORED_OBJ_TRADE_DATA_NYM);
	DECLARE_PROTOBUF_SUBCLASS(TradeListNym,		TradeListNym_InternalPB,	TradeListNymPB,		STORED_OBJ_TRADE_LIST_NYM);

	typedef OfferDataMarket_InternalPB BidData_InternalPB;
	typedef OfferDataMarket_InternalPB AskData_InternalPB;

	// !! ALL OF THESE have to provide implementations for hookBeforePack() and hookAfterUnpack().
	// In .cpp file:
	/*
	void SUBCLASS_HERE::hookBeforePack()
	{
	__pb_obj.set_PROPERTY_NAME_GOES_HERE(PROPERTY_NAME_GOES_HERE);
	}
	void SUBCLASS_HERE::hookAfterUnpack()
	{
	PROPERTY_NAME_GOES_HERE	= __pb_obj.PROPERTY_NAME_GOES_HERE();
	}
	*/


} // namespace OTDB

#endif // defined(OTDB_PROTOCOL_BUFFERS)


#if __clang__
#pragma clang diagnostic pop
#endif

#endif // __OT_STORAGE_PB_HPP__
