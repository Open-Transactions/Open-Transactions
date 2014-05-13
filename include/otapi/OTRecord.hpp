/************************************************************
 *    
 *  OTRecord.hpp   (Used with OTRecordList)
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


#ifndef __OTClient__OTRecord__
#define __OTClient__OTRecord__

#include "OTCommon.hpp"


#include _CINTTYPES
#include _MEMORY


#include <iostream>
#include <string>


const std::string & OTRecord_GetTypeString(int32_t theType);


/*
 Could you add this to OTRecord:
 
 - Sender Nym, Account Ids
 - Accept & reject actions
 - Delete action
 
 */

class OTRecord
{
public:
    enum OTRecordType
    {
        Mail = 0,
        Transfer,
        Receipt,
        Instrument,
        ErrorState
    };
private:
    int32_t      m_nBoxIndex;
    time64_t     m_ValidFrom;
    time64_t     m_ValidTo;
    // ---------------------------------------
    const std::string & m_str_server_id;
    const std::string & m_str_asset_id;
    const std::string & m_str_currency_tla;
    const std::string & m_str_nym_id;
    const std::string & m_str_account_id;
    // ---------------------------------------
    std::string   m_str_other_nym_id;
    std::string   m_str_other_account_id;
    // ---------------------------------------
    std::string   m_str_name;
    std::string   m_str_date;
    std::string   m_str_amount;
    std::string   m_str_type;
    std::string   m_str_memo;
    // ---------------------------------------
    // Contains payment instrument or mail message (or nothing, if not applicable.)
    //
    std::string   m_str_contents;
    // ---------------------------------------
    // Contains transaction number of actual receipt in inbox,
    // or payment inbox, or record box. (If outpayment, contains
    // transaction number on outgoing instrument.)
    //
    int64_t       m_lTransactionNum;
    int64_t       m_lTransNumForDisplay;
    // ---------------------------------------
    bool          m_bIsPending;
    bool          m_bIsOutgoing;
    bool          m_bIsRecord;  // record box (closed, finished, historical only.)
    bool          m_bIsReceipt; // It's a receipt, not a payment.
    // ---------------------------------------
    bool          m_bIsPaymentPlan;
    bool          m_bIsSmartContract;
    bool          m_bIsVoucher;
    bool          m_bIsCheque;
    bool          m_bIsInvoice;
    bool          m_bIsCash;
    // ---------------------------------------
    bool          m_bIsExpired;
    bool          m_bIsCanceled;
    // ---------------------------------------
    OTRecordType        m_RecordType;
    // ---------------------------------------
    bool  AcceptIncomingTransferOrReceipt();
public:
    // ---------------------------------------
EXPORT    bool  IsPending()     const;
EXPORT    bool  IsOutgoing()    const;
EXPORT    bool  IsRecord()      const;
EXPORT    bool  IsReceipt()     const;
EXPORT    bool  IsMail()        const;
EXPORT    bool  IsTransfer()    const;
EXPORT    bool  IsCheque()      const;
EXPORT    bool  IsInvoice()     const;
EXPORT    bool  IsVoucher()     const;
EXPORT    bool  IsContract()    const;
EXPORT    bool  IsPaymentPlan() const;
EXPORT    bool  IsCash()        const;
EXPORT    bool  HasContents()   const;
EXPORT    bool  HasMemo()       const;
    // ---------------------------------------
EXPORT    bool  IsExpired()     const;
EXPORT    bool  IsCanceled()    const;
    // ---------------------------------------
EXPORT    void  SetExpired();
EXPORT    void  SetCanceled();
    // ---------------------------------------
EXPORT    time64_t GetValidFrom();
EXPORT    time64_t GetValidTo();
    // ---------------------------------------
EXPORT    void  SetDateRange(time64_t tValidFrom, time64_t tValidTo); // Todo: convert to time64_t
    // ---------------------------------------
EXPORT    bool  CanDeleteRecord()        const;  // For completed records (not pending.)
EXPORT    bool  CanAcceptIncoming()      const;  // For incoming, pending (not-yet-accepted) instruments.
EXPORT    bool  CanDiscardIncoming()     const;  // For INcoming, pending (not-yet-accepted) instruments.
EXPORT    bool  CanCancelOutgoing()      const;  // For OUTgoing, pending (not-yet-accepted) instruments.
EXPORT    bool  CanDiscardOutgoingCash() const;  // For OUTgoing cash. (No way to see if it's been accepted, so this lets you erase the record of sending it.)
    // ---------------------------------------
EXPORT    bool  CancelOutgoing(const std::string str_via_acct); // For outgoing, pending (not-yet-accepted) instruments. NOTE: str_via_acct can be blank if a cheque. But if voucher, smart contract, payment plan, you must provide.
EXPORT    bool  AcceptIncomingInstrument(const std::string & str_into_acct);   // For incoming, pending (not-yet-accepted) instruments.
EXPORT    bool  AcceptIncomingTransfer();     // For incoming, pending (not-yet-accepted) transfers.
EXPORT    bool  AcceptIncomingReceipt();      // For incoming, (not-yet-accepted) receipts.
EXPORT    bool  DiscardIncoming();            // For incoming, pending (not-yet-accepted) instruments.
EXPORT    bool  DeleteRecord();               // For completed records (not pending.)
EXPORT    bool  DiscardOutgoingCash();        // For OUTgoing cash. (No way to see if it's been accepted, so this lets you erase the record of sending it.)
    // ---------------------------------------
EXPORT    int32_t GetBoxIndex() const; // If this is set to 3, for example, for a payment in the payments inbox, then index 3 in that same box refers to the payment corresponding to this record.
EXPORT    void    SetBoxIndex(int32_t nBoxIndex);
    // ---------------------------------------
EXPORT    int64_t GetTransactionNum() const; // Trans Num of receipt in the box. (Unless outpayment, contains number for instrument.)
EXPORT    void    SetTransactionNum(int64_t lTransNum);
    // ---------------------------------------
EXPORT    int64_t GetTransNumForDisplay() const; // Trans Num of the cheque inside the receipt in the box.
EXPORT    void    SetTransNumForDisplay(int64_t lTransNum);
    // ---------------------------------------
EXPORT    OTRecordType  GetRecordType() const;
    // ---------------------------------------
EXPORT    const std::string & GetServerID()       const;
EXPORT    const std::string & GetAssetID()        const;
EXPORT    const std::string & GetCurrencyTLA()    const; // BTC, USD, etc.
EXPORT    const std::string & GetNymID()          const;
EXPORT    const std::string & GetAccountID()      const;
    // ---------------------------------------
EXPORT    const std::string & GetOtherNymID()     const; // Could be sender OR recipient depending on whether incoming/outgoing.
EXPORT    const std::string & GetOtherAccountID() const; // Could be sender OR recipient depending on whether incoming/outgoing.
    // ---------------------------------------
EXPORT    const std::string & GetName()           const;
EXPORT    const std::string & GetDate()           const;
EXPORT    const std::string & GetAmount()         const;
EXPORT    const std::string & GetInstrumentType() const;
EXPORT    const std::string & GetMemo()           const;
EXPORT    const std::string & GetContents()       const;
    // ---------------------------------------
EXPORT    void  SetOtherNymID    (const std::string & str_ID);
EXPORT    void  SetOtherAccountID(const std::string & str_ID);
EXPORT    void  SetMemo          (const std::string & str_memo);
EXPORT    void  SetContents      (const std::string & str_contents);
    // ---------------------------------------
    // These don't work unless the record is for a pending
    // payment plan.
    //
EXPORT    bool   HasInitialPayment();
EXPORT    bool   HasPaymentPlan();
    
EXPORT    time64_t GetInitialPaymentDate();
EXPORT    time64_t GetPaymentPlanStartDate();
EXPORT    time64_t GetTimeBetweenPayments();
    
EXPORT    int64_t   GetInitialPaymentAmount();
EXPORT    int64_t   GetPaymentPlanAmount();
    
EXPORT    int32_t   GetMaximumNoPayments();
    // ---------------------------------------
EXPORT    bool  FormatAmount              (std::string & str_output);
EXPORT    bool  FormatDescription         (std::string & str_output);
EXPORT    bool  FormatShortMailDescription(std::string & str_output);
EXPORT    bool  FormatMailSubject         (std::string & str_output);
    // ---------------------------------------
          bool operator<(const OTRecord& rhs);
    // ---------------------------------------
    OTRecord(const std::string & str_server_id,
             const std::string & str_asset_id,
             const std::string & str_currency_tla,
             const std::string & str_nym_id,
             const std::string & str_account_id,
             // -------------------------------
             const std::string & str_name,
             const std::string & str_date,
             const std::string & str_amount,
             const std::string & str_type,
             bool  bIsPending,
             bool  bIsOutgoing,
             bool  bIsRecord,
             bool  bIsReceipt,
             OTRecordType eRecordType
             );
};



#endif /* defined(__OTClient__OTRecord__) */
