#ifndef _H_OT_UTILITY_OT
#define _H_OT_UTILITY_OT

#include "stdafx.hpp"

#include <ExportWrapper.h>

#include "OTStorage.hpp"

#include <string>




#define OT_UTILITY_OT


using std::string;


inline OT_UTILITY_OT bool VerifyBoolVal(const bool bValue) { return true; }
//extern OT_UTILITY_OT bool VerifyBoolVal(const int bValue);
//extern OT_UTILITY_OT bool VerifyBoolVal(const int64_t bValue);
//extern OT_UTILITY_OT bool VerifyIntVal(const bool nValue);
//inline OT_UTILITY_OT bool VerifyIntVal(const int nValue) { return true; }
inline OT_UTILITY_OT bool VerifyIntVal(const int64_t nValue) { return true; }
//inline OT_UTILITY_OT bool VerifyIntVal(const time_t nValue) { return true; }
inline OT_UTILITY_OT bool VerifyStringVal(const string & nValue) { return 0 < nValue.length(); }

EXPORT OT_UTILITY_OT int InterpretTransactionMsgReply(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strAttempt, const string & strResponse);
EXPORT OT_UTILITY_OT bool VerifyExists(const string & name, const bool bFlag = true);
EXPORT OT_UTILITY_OT int VerifyMessageSuccess(const string & message);
EXPORT OT_UTILITY_OT int VerifyMsgBalanceAgrmntSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);  // For when an OTMessage is the input.
EXPORT OT_UTILITY_OT int VerifyMsgTrnxSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);
EXPORT OT_UTILITY_OT bool VerifyNotNull(const void * theObjectRef);
EXPORT OT_UTILITY_OT bool VerifyStorable(OTDB::Storable * theStorableObjectRef, const string & strType);
EXPORT OT_UTILITY_OT bool VerifyType(const void * theObjectRef, const string & strType);


class OTfourbool
{
public:
    bool one;
    bool two;
    bool three;
    bool four;

    OTfourbool()
    {
        one = false;
        two = false;
        three = false;
        four = false;
    }

    OTfourbool(const bool param_one, const bool param_two, const bool param_three, const bool param_four)
    {
        one = param_one;
        two = param_two;
        three = param_three;
        four = param_four;
    }
};


class Utility
{
public:
    string strLastReplyReceived;
    int delay_ms;
    int max_trans_dl;

    EXPORT OT_UTILITY_OT Utility();
    EXPORT OT_UTILITY_OT ~Utility();

    EXPORT OT_UTILITY_OT void delay();
    EXPORT OT_UTILITY_OT int getAndProcessNymbox_3(const string & serverID, const string & nymID, bool & bWasMsgSent);
    EXPORT OT_UTILITY_OT int getAndProcessNymbox_4(const string & serverID, const string & nymID, bool &  bWasMsgSent, const bool bForceDownload);
    EXPORT OT_UTILITY_OT int getAndProcessNymbox_8(const string & serverID, const string & nymID, bool & bWasMsgSent, const bool bForceDownload, const int nRequestNumber, bool & bFoundNymboxItem, const bool bHarvestingForRetry, const OTfourbool & bMsgFoursome);
    EXPORT OT_UTILITY_OT bool getBoxReceiptLowLevel(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int64_t strTransactionNum, bool & bWasSent); // bWasSent is OTBool
    EXPORT OT_UTILITY_OT bool getBoxReceiptWithErrorCorrection(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int64_t strTransactionNum); // nBoxType is int
    EXPORT OT_UTILITY_OT int getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount);
    EXPORT OT_UTILITY_OT int getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload); //bForceDownload=false
    EXPORT OT_UTILITY_OT int getInboxAccount_old(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload); //bForceDownload=false
    EXPORT OT_UTILITY_OT int getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    EXPORT OT_UTILITY_OT int getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce); // bForce defaults to FALSE
    EXPORT OT_UTILITY_OT int getInboxOutboxAccount(const string & accountID);
    EXPORT OT_UTILITY_OT int getInboxOutboxAccount(const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    EXPORT OT_UTILITY_OT bool getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID);
    EXPORT OT_UTILITY_OT bool getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    EXPORT OT_UTILITY_OT bool getIntermediaryFiles_old(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    EXPORT OT_UTILITY_OT string getLastReplyReceived();
    EXPORT OT_UTILITY_OT int getNbrTransactionCount();
    EXPORT OT_UTILITY_OT int getNymbox(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT int getNymbox(const string & serverID, const string & nymID, const bool bForceDownload);
    EXPORT OT_UTILITY_OT int getNymboxLowLevel(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT int getNymboxLowLevel(const string & serverID, const string & nymID, bool & bWasSent);
    EXPORT OT_UTILITY_OT int getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    EXPORT OT_UTILITY_OT int getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce); // bForce defaults to FALSE
    EXPORT OT_UTILITY_OT int getRequestNumber(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT int getRequestNumber(const string & serverID, const string & nymID, bool & bWasSent); // bWasSent is an output param allowing to return whether;
    EXPORT OT_UTILITY_OT bool getTransactionNumbers(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT bool getTransactionNumbers(const string & serverID, const string & nymID, const bool bForceFirstCall); // boolean bForceFirstCall defaults to true.
    EXPORT OT_UTILITY_OT int getTransactionNumLowLevel(const string & serverID, const string & nymID, bool & bWasSent); // bWasSent is OTBool
    EXPORT OT_UTILITY_OT bool insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int nBoxType); // nBoxType is int
    EXPORT OT_UTILITY_OT bool insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int nRequestSeeking, bool & bFoundIt);
    EXPORT OT_UTILITY_OT void longDelay();
    EXPORT OT_UTILITY_OT int processNymbox(const string & serverID, const string & nymID, bool & bWasMsgSent, int & nMsgSentRequestNumOut, int & nReplySuccessOut, int & nBalanceSuccessOut, int & nTransSuccessOut);
    EXPORT OT_UTILITY_OT string ReceiveReplyLowLevel(const string & serverID17, const string & nymID, const int nRequestNumber8, const string & IN_FUNCTION);
    EXPORT OT_UTILITY_OT int receiveReplySuccessLowLevel(const string & serverID18, const string & nymID, const int nRequestNumber7, const string & IN_FUNCTION);
    EXPORT OT_UTILITY_OT int sendProcessNymboxLowLevel(const string & serverID, const string & nymID); // bWasSent is an output param allowing to return whether;
    EXPORT OT_UTILITY_OT void setLastReplyReceived(const string & strReply);
    EXPORT OT_UTILITY_OT void setNbrTransactionCount(int new_trans_dl);
};

#endif
