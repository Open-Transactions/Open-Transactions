//
//  OTRecord.h
//  OTClient module
//
//  Created by Chris Odom on 4/28/13.
//  Copyright (c) 2013 Monetas. All rights reserved.
//


#ifndef __OTClient__OTRecord__
#define __OTClient__OTRecord__

#include "OTCommon.hpp"


#include _CINTTYPES
#include _MEMORY


#include <iostream>
#include <string>


const std::string & OTRecord_GetTypeString(int theType);


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
    int        m_nBoxIndex;
    time_t     m_ValidFrom;
    time_t     m_ValidTo;
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
    long          m_lTransactionNum;
    long          m_lTransNumForDisplay;
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
EXPORT    int64_t GetValidFrom(); // Todo: convert to time64_t
EXPORT    int64_t GetValidTo();   // Todo: convert to time64_t
    // ---------------------------------------
EXPORT    void  SetDateRange(int64_t tValidFrom, int64_t tValidTo); // Todo: convert to time64_t
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
    
EXPORT    int64_t GetInitialPaymentDate();      // Todo: convert to time64_t
EXPORT    int64_t GetPaymentPlanStartDate();    // Todo: convert to time64_t
EXPORT    int64_t GetTimeBetweenPayments();     // Todo: convert to time64_t
    
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
