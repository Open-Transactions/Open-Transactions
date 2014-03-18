#ifndef _H_OT_ME_EXTRA
#define _H_OT_ME_EXTRA

#include "OT_ME.hpp"


using namespace std;


#define EXTRA_FUNCTIONS \
    virtual int     details_deposit_cheque(const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType); \
    virtual string  details_export_cash(const char * serverId, const char * nymFromId, const char *assetId, string & hisNymId, const char *indices, bool password, string & retainedCopy); \
    virtual bool    details_refresh_nym(const char * serverId, const char * nymId, const bool bForceDownload); \
    virtual int     handle_payment_index(const char * accountId, int32_t paymentIndex, const char * paymentType, const char * inboxData); \
    virtual int     InterpretTransactionMsgReply(const char * serverId, const char * nymId, const char * accountId, const char * attempt, const char * response); \
    virtual void    ot_utility_delay(); \
    virtual int     ot_utility_getAndProcessNymbox_4(const char * serverId, const char * nymId, bool bForceDownload); \
    virtual bool    ot_utility_getBoxReceiptLowLevel(const char * serverId, const char * nymId, const char * accountId, const int boxType, const int64_t transactionNumber); \
    virtual bool    ot_utility_getBoxReceiptWithErrorCorrection(const char * serverId, const char * nymId, const char * accountId, const int boxType, const int64_t transactionNumber); \
    virtual string  ot_utility_getLastReplyReceived(); \
    virtual int     ot_utility_getNbrTransactionCount(); \
    virtual int     ot_utility_getNymbox(const char * serverId, const char * nymId, bool bForceDownload); \
    virtual int     ot_utility_getNymboxLowLevel(const char * serverId, const char * nymId); \
    virtual int     ot_utility_getRequestNumber(const char * serverId, const char * nymId); \
    virtual bool    ot_utility_getTransactionNumbers(const char * serverId, const char * nymId); \
    virtual int     ot_utility_getTransactionNumLowLevel(const char * serverId, const char * nymId); \
    virtual bool    ot_utility_insureHaveAllBoxReceipts(const char * serverId, const char * nymId, const char * accountId, const int boxType); \
    virtual int     ot_utility_processNymbox(const char * serverId, const char * nymId); \
    virtual string  ot_utility_ReceiveReplyLowLevel(const char * serverId, const char * nymId, int reqNr, const char * function); \
    virtual int     ot_utility_receiveReplySuccessLowLevel(const char * serverId, const char * nymId, int reqNr, const char * function); \
    virtual int     ot_utility_sendProcessNymboxLowLevel(const char * serverId, const char * nymId); \
    virtual string  ot_utility_setLastReplyReceived(); \
    virtual int     ot_utility_setNbrTransactionCount(); \
    virtual int     VerifyMessageSuccess(const char * messageData); \
    virtual int     VerifyMsgBalanceAgrmntSuccess(const char * serverId, const char * nymId, const char * accountId, const char * messageData); \
    virtual int     VerifyMsgTrnxSuccess(const char * serverId, const char * nymId, const char * accountId, const char * messageData); \
    virtual void    ot_utility_longDelay(); \

class OtMeExtra : public OT_ME
{
public:

    OtMeExtra();
    virtual ~OtMeExtra();

    EXTRA_FUNCTIONS
};


class OtMeChai : public OtMeExtra
{
private:

    const char * boolStr(bool bValue);
    void exec(const string & script);
    bool execBool(const string & script);
    int execInt(const string & script);
    string execStr(const string & script);

public:

    OtMeChai();
    virtual ~OtMeChai();

    EXTRA_FUNCTIONS
};

#endif // _H_OT_ME_EXTRA
