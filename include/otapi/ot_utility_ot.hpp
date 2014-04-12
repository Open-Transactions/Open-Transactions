#ifndef _H_OT_UTILITY_OT
#define _H_OT_UTILITY_OT

#include "OTCommon.hpp"

#include <string>

#include <OTStorage.hpp>

#define OT_UTILITY_OT


using std::string;


inline OT_UTILITY_OT bool VerifyBoolVal(const bool bValue) { return true; }
//extern OT_UTILITY_OT bool VerifyBoolVal(const int32_t bValue);
//extern OT_UTILITY_OT bool VerifyBoolVal(const int64_t bValue);
//extern OT_UTILITY_OT bool VerifyIntVal(const bool nValue);
//inline OT_UTILITY_OT bool VerifyIntVal(const int32_t nValue) { return true; }
inline OT_UTILITY_OT bool VerifyIntVal(const int64_t nValue) { return true; }
//inline OT_UTILITY_OT bool VerifyIntVal(const time_t nValue) { return true; }
inline OT_UTILITY_OT bool VerifyStringVal(const string & nValue) { return 0 < nValue.length(); }

EXPORT OT_UTILITY_OT int32_t InterpretTransactionMsgReply(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strAttempt, const string & strResponse);
EXPORT OT_UTILITY_OT bool VerifyExists(const string & name, const bool bFlag = true);
EXPORT OT_UTILITY_OT int32_t VerifyMessageSuccess(const string & message);
EXPORT OT_UTILITY_OT int32_t VerifyMsgBalanceAgrmntSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);
EXPORT OT_UTILITY_OT int32_t VerifyMsgTrnxSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);
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
    int32_t delay_ms;
    int32_t max_trans_dl;

    EXPORT OT_UTILITY_OT Utility();
    EXPORT OT_UTILITY_OT ~Utility();

    EXPORT OT_UTILITY_OT void delay();
    EXPORT OT_UTILITY_OT int32_t getAndProcessNymbox_3(const string & serverID, const string & nymID, bool & bWasMsgSent);
    EXPORT OT_UTILITY_OT int32_t getAndProcessNymbox_4(const string & serverID, const string & nymID, bool &  bWasMsgSent, const bool bForceDownload);
    EXPORT OT_UTILITY_OT int32_t getAndProcessNymbox_8(const string & serverID, const string & nymID, bool & bWasMsgSent, const bool bForceDownload, const int32_t nRequestNumber, bool & bFoundNymboxItem, const bool bHarvestingForRetry, const OTfourbool & bMsgFoursome);
    EXPORT OT_UTILITY_OT bool getBoxReceiptLowLevel(const string & serverID, const string & nymID, const string & accountID, const int32_t nBoxType, const int64_t strTransactionNum, bool & bWasSent);
    EXPORT OT_UTILITY_OT bool getBoxReceiptWithErrorCorrection(const string & serverID, const string & nymID, const string & accountID, const int32_t nBoxType, const int64_t strTransactionNum);
    EXPORT OT_UTILITY_OT int32_t getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount);
    EXPORT OT_UTILITY_OT int32_t getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload);
    EXPORT OT_UTILITY_OT int32_t getInboxAccount_old(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload);
    EXPORT OT_UTILITY_OT int32_t getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    EXPORT OT_UTILITY_OT int32_t getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce);
    EXPORT OT_UTILITY_OT bool getInboxOutboxAccount(const string & accountID);
    EXPORT OT_UTILITY_OT bool getInboxOutboxAccount(const string & accountID, const bool bForceDownload);
    EXPORT OT_UTILITY_OT bool getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID);
    EXPORT OT_UTILITY_OT bool getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload);
    EXPORT OT_UTILITY_OT bool getIntermediaryFiles_old(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload);
    EXPORT OT_UTILITY_OT string getLastReplyReceived();
    EXPORT OT_UTILITY_OT int32_t getNbrTransactionCount();
    EXPORT OT_UTILITY_OT int32_t getNymbox(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT int32_t getNymbox(const string & serverID, const string & nymID, const bool bForceDownload);
    EXPORT OT_UTILITY_OT int32_t getNymboxLowLevel(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT int32_t getNymboxLowLevel(const string & serverID, const string & nymID, bool & bWasSent);
    EXPORT OT_UTILITY_OT int32_t getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    EXPORT OT_UTILITY_OT int32_t getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce);
    EXPORT OT_UTILITY_OT int32_t getRequestNumber(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT int32_t getRequestNumber(const string & serverID, const string & nymID, bool & bWasSent);
    EXPORT OT_UTILITY_OT bool getTransactionNumbers(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT bool getTransactionNumbers(const string & serverID, const string & nymID, const bool bForceFirstCall);
    EXPORT OT_UTILITY_OT int32_t getTransactionNumLowLevel(const string & serverID, const string & nymID, bool & bWasSent);
    EXPORT OT_UTILITY_OT bool insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int32_t nBoxType);
    EXPORT OT_UTILITY_OT bool insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int32_t nBoxType, const int32_t nRequestSeeking, bool & bFoundIt);
    EXPORT OT_UTILITY_OT void longDelay();
    EXPORT OT_UTILITY_OT int32_t processNymbox(const string & serverID, const string & nymID, bool & bWasMsgSent, int32_t & nMsgSentRequestNumOut, int32_t & nReplySuccessOut, int32_t & nBalanceSuccessOut, int32_t & nTransSuccessOut);
    EXPORT OT_UTILITY_OT string ReceiveReplyLowLevel(const string & serverID17, const string & nymID, const int32_t nRequestNumber8, const string & IN_FUNCTION);
    EXPORT OT_UTILITY_OT int32_t receiveReplySuccessLowLevel(const string & serverID18, const string & nymID, const int32_t nRequestNumber7, const string & IN_FUNCTION);
    EXPORT OT_UTILITY_OT int32_t sendProcessNymboxLowLevel(const string & serverID, const string & nymID);
    EXPORT OT_UTILITY_OT void setLastReplyReceived(const string & strReply);
    EXPORT OT_UTILITY_OT void setNbrTransactionCount(int32_t new_trans_dl);
};

#endif
