#ifndef _H_OT_UTILITY_OT
#define _H_OT_UTILITY_OT

#include <string>

#include "OTStorage.hpp"


#define OT_UTILITY_OT


using std::string;


inline OT_UTILITY_OT bool VerifyBoolVal(const bool bValue) { return true; }
inline OT_UTILITY_OT bool VerifyIntVal(const int64_t nValue) { return true; }
inline OT_UTILITY_OT bool VerifyStringVal(const string & nValue) { return 0 < nValue.length(); }

extern OT_UTILITY_OT int InterpretTransactionMsgReply(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strAttempt, const string & strResponse);
extern OT_UTILITY_OT bool VerifyExists(const string & name, const bool bFlag = true);
extern OT_UTILITY_OT int VerifyMessageSuccess(const string & message);
extern OT_UTILITY_OT int VerifyMsgBalanceAgrmntSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);  // For when an OTMessage is the input.
extern OT_UTILITY_OT int VerifyMsgTrnxSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);
extern OT_UTILITY_OT int VerifyStorable(OTDB::Storable * theStorableObjectRef, const string & strType);


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

    Utility();
    ~Utility();

    OT_UTILITY_OT void delay();
    OT_UTILITY_OT int getAndProcessNymbox_3(const string & serverID, const string & nymID, bool & bWasMsgSent);
    OT_UTILITY_OT int getAndProcessNymbox_4(const string & serverID, const string & nymID, bool &  bWasMsgSent, const bool bForceDownload);
    OT_UTILITY_OT int getAndProcessNymbox_8(const string & serverID, const string & nymID, bool & bWasMsgSent, const bool bForceDownload, const int nRequestNumber, bool & bFoundNymboxItem, const bool bHarvestingForRetry, const OTfourbool & bMsgFoursome);
    OT_UTILITY_OT bool getBoxReceiptLowLevel(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int64_t strTransactionNum, bool & bWasSent); // bWasSent is OTBool
    OT_UTILITY_OT bool getBoxReceiptWithErrorCorrection(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int64_t strTransactionNum); // nBoxType is int
    OT_UTILITY_OT int getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount);
    OT_UTILITY_OT int getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload); //bForceDownload=false
    OT_UTILITY_OT int getInboxAccount_old(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload); //bForceDownload=false
    OT_UTILITY_OT int getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    OT_UTILITY_OT int getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce); // bForce defaults to FALSE
    OT_UTILITY_OT int getInboxOutboxAccount(const string & accountID);
    OT_UTILITY_OT int getInboxOutboxAccount(const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    OT_UTILITY_OT bool getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID);
    OT_UTILITY_OT bool getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    OT_UTILITY_OT bool getIntermediaryFiles_old(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    OT_UTILITY_OT string getLastReplyReceived();
    OT_UTILITY_OT int getNbrTransactionCount();
    OT_UTILITY_OT int getNymbox(const string & serverID, const string & nymID);
    OT_UTILITY_OT int getNymbox(const string & serverID, const string & nymID, const bool bForceDownload);
    OT_UTILITY_OT int getNymboxLowLevel(const string & serverID, const string & nymID);
    OT_UTILITY_OT int getNymboxLowLevel(const string & serverID, const string & nymID, bool & bWasSent);
    OT_UTILITY_OT int getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    OT_UTILITY_OT int getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce); // bForce defaults to FALSE
    OT_UTILITY_OT int getRequestNumber(const string & serverID, const string & nymID);
    OT_UTILITY_OT int getRequestNumber(const string & serverID, const string & nymID, bool & bWasSent); // bWasSent is an output param allowing to return whether;
    OT_UTILITY_OT bool getTransactionNumbers(const string & serverID, const string & nymID);
    OT_UTILITY_OT bool getTransactionNumbers(const string & serverID, const string & nymID, const bool bForceFirstCall); // boolean bForceFirstCall defaults to true.
    OT_UTILITY_OT int getTransactionNumLowLevel(const string & serverID, const string & nymID, bool & bWasSent); // bWasSent is OTBool
    OT_UTILITY_OT bool insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int nBoxType); // nBoxType is int
    OT_UTILITY_OT bool insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int nRequestSeeking, bool & bFoundIt);
    OT_UTILITY_OT void longDelay();
    OT_UTILITY_OT int processNymbox(const string & serverID, const string & nymID, bool & bWasMsgSent, int & nMsgSentRequestNumOut, int & nReplySuccessOut, int & nBalanceSuccessOut, int & nTransSuccessOut);
    OT_UTILITY_OT string ReceiveReplyLowLevel(const string & serverID17, const string & nymID, const int nRequestNumber8, const string & IN_FUNCTION);
    OT_UTILITY_OT int receiveReplySuccessLowLevel(const string & serverID18, const string & nymID, const int nRequestNumber7, const string & IN_FUNCTION);
    OT_UTILITY_OT int sendProcessNymboxLowLevel(const string & serverID, const string & nymID); // bWasSent is an output param allowing to return whether;
    OT_UTILITY_OT void setLastReplyReceived(const string & strReply);
    OT_UTILITY_OT void setNbrTransactionCount(int new_trans_dl);
};

#endif
