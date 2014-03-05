#ifndef _H_OT_UTILITY_OT
#define _H_OT_UTILITY_OT

#include <string>


#define OT_UTILITY_OT


using std::string;

inline bool OT_UTILITY_OT VerifyBoolVal(const bool bValue) { return true; }
inline bool OT_UTILITY_OT VerifyIntVal(const int64_t nValue) { return true; }
inline bool OT_UTILITY_OT VerifyStringVal(const string & nValue) { return 0 < nValue.length(); }

extern int OT_UTILITY_OT InterpretTransactionMsgReply(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strAttempt, const string & strResponse);
extern bool OT_UTILITY_OT VerifyExists(const string & name, const bool bFlag = true);
extern int OT_UTILITY_OT VerifyMessageSuccess(const string & message);
extern int OT_UTILITY_OT VerifyMsgBalanceAgrmntSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);  // For when an OTMessage is the input.
extern int OT_UTILITY_OT VerifyMsgTrnxSuccess(const string & SERVER_ID, const string & USER_ID, const string & ACCOUNT_ID, const string & strMessage);


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

    void OT_UTILITY_OT delay();
    int OT_UTILITY_OT getAndProcessNymbox_3(const string & serverID, const string & nymID, bool & bWasMsgSent);
    int OT_UTILITY_OT getAndProcessNymbox_4(const string & serverID, const string & nymID, bool &  bWasMsgSent, const bool bForceDownload);
    int OT_UTILITY_OT getAndProcessNymbox_8(const string & serverID, const string & nymID, bool & bWasMsgSent, const bool bForceDownload, const int nRequestNumber, bool & bFoundNymboxItem, const bool bHarvestingForRetry, const OTfourbool & bMsgFoursome);
    bool OT_UTILITY_OT getBoxReceiptLowLevel(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int64_t strTransactionNum, bool & bWasSent); // bWasSent is OTBool
    bool OT_UTILITY_OT getBoxReceiptWithErrorCorrection(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int64_t strTransactionNum); // nBoxType is int
    int OT_UTILITY_OT getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount);
    int OT_UTILITY_OT getInboxAccount(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload); //bForceDownload=false
    int OT_UTILITY_OT getInboxAccount_old(const string & serverID, const string & nymID, const string & accountID, bool & bWasSentInbox, bool & bWasSentAccount, const bool bForceDownload); //bForceDownload=false
    int OT_UTILITY_OT getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    int OT_UTILITY_OT getInboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce); // bForce defaults to FALSE
    int OT_UTILITY_OT getInboxOutboxAccount(const string & accountID);
    int OT_UTILITY_OT getInboxOutboxAccount(const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    bool OT_UTILITY_OT getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID);
    bool OT_UTILITY_OT getIntermediaryFiles(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    bool OT_UTILITY_OT getIntermediaryFiles_old(const string & serverID, const string & nymID, const string & accountID, const bool bForceDownload); // booleanbForceDownload = false;
    string OT_UTILITY_OT getLastReplyReceived();
    int OT_UTILITY_OT getNbrTransactionCount();
    int OT_UTILITY_OT getNymbox(const string & serverID, const string & nymID);
    int OT_UTILITY_OT getNymbox(const string & serverID, const string & nymID, const bool bForceDownload);
    int OT_UTILITY_OT getNymboxLowLevel(const string & serverID, const string & nymID);
    int OT_UTILITY_OT getNymboxLowLevel(const string & serverID, const string & nymID, bool & bWasSent);
    int OT_UTILITY_OT getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent);
    int OT_UTILITY_OT getOutboxLowLevel(const string & serverID, const string & nymID, const string & accountID, bool & bWasSent, const bool bForce); // bForce defaults to FALSE
    int OT_UTILITY_OT getRequestNumber(const string & serverID, const string & nymID);
    int OT_UTILITY_OT getRequestNumber(const string & serverID, const string & nymID, bool & bWasSent); // bWasSent is an output param allowing to return whether;
    bool OT_UTILITY_OT getTransactionNumbers(const string & serverID, const string & nymID);
    bool OT_UTILITY_OT getTransactionNumbers(const string & serverID, const string & nymID, const bool bForceFirstCall); // boolean bForceFirstCall defaults to true.
    int OT_UTILITY_OT getTransactionNumLowLevel(const string & serverID, const string & nymID, bool & bWasSent); // bWasSent is OTBool
    bool OT_UTILITY_OT insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int nBoxType); // nBoxType is int
    bool OT_UTILITY_OT insureHaveAllBoxReceipts(const string & serverID, const string & nymID, const string & accountID, const int nBoxType, const int nRequestSeeking, bool & bFoundIt);
    void OT_UTILITY_OT longDelay();
    int OT_UTILITY_OT processNymbox(const string & serverID, const string & nymID, bool & bWasMsgSent, int & nMsgSentRequestNumOut, int & nReplySuccessOut, int & nBalanceSuccessOut, int & nTransSuccessOut);
    string OT_UTILITY_OT ReceiveReplyLowLevel(const string & serverID17, const string & nymID, const int nRequestNumber8, const string & IN_FUNCTION);
    int OT_UTILITY_OT receiveReplySuccessLowLevel(const string & serverID18, const string & nymID, const int nRequestNumber7, const string & IN_FUNCTION);
    int OT_UTILITY_OT sendProcessNymboxLowLevel(const string & serverID, const string & nymID); // bWasSent is an output param allowing to return whether;
    void OT_UTILITY_OT setLastReplyReceived(const string & strReply);
    void OT_UTILITY_OT setNbrTransactionCount(int new_trans_dl);
};

#endif
