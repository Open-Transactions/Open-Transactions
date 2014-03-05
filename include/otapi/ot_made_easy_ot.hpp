#ifndef _H_OT_MADE_EASY_OT
#define _H_OT_MADE_EASY_OT

#include <string>


#define OT_MADE_EASY_OT


using std::string;


extern int OT_MADE_EASY_OT depositCashPurse(const string & serverID, const string & assetID, const string & nymID, const string & oldPurse, const vector<string> & selectedTokens, const string & accountID, const bool bReimportIfFailure); // So we don't re-import a purse that wasn't internal to begin with.
extern bool OT_MADE_EASY_OT exchangeCashPurse(const string & serverID, const string & assetID, const string & nymID, string & oldPurse, const vector<string> & selectedTokens);
extern string OT_MADE_EASY_OT exportCashPurse(const string & serverID, const string & assetID, const string & nymID, const string & oldPurse, const vector<string> & selectedTokens, string & recipientNymID, const bool bPasswordProtected, string & strRetainedCopy);
extern bool OT_MADE_EASY_OT importCashPurse(const string & serverID, const string & nymID, const string & assetID, string & userInput, const bool isPurse);
extern bool OT_MADE_EASY_OT processCashPurse(string & newPurse, string & newPurseForSender, const string & serverID, const string & assetID, const string & nymID, string & oldPurse, const vector<string> & selectedTokens, const string & recipientNymID, const bool bPWProtectOldPurse, const bool bPWProtectNewPurse);


class MadeEasy
{
public:
    MadeEasy();
    ~MadeEasy();

    string OT_MADE_EASY_OT activate_smart_contract(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & AGENT_NAME, const string & THE_SMART_CONTRACT);
    string OT_MADE_EASY_OT adjust_usage_credits(const string & SERVER_ID, const string & USER_NYM_ID, const string & TARGET_NYM_ID, const string & ADJUSTMENT);
    string OT_MADE_EASY_OT cancel_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & THE_PAYMENT_PLAN);
    string OT_MADE_EASY_OT check_user(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    string OT_MADE_EASY_OT create_asset_acct(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_TYPE_ID);
    string OT_MADE_EASY_OT create_market_offer(const string & ASSET_ACCT_ID, const string & CURRENCY_ACCT_ID, const string & scale, const string & minIncrement, const string & quantity, const string & price, const bool bSelling, const string & strLifespanInSeconds, const string & strStopSign, const string & strActivationPrice);
    string OT_MADE_EASY_OT create_pseudonym(const int nKeybits, const string & strNymIDSource, const string & strAltLocation);
    string OT_MADE_EASY_OT deposit_cheque(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_CHEQUE);
    string OT_MADE_EASY_OT deposit_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & THE_PAYMENT_PLAN);
    string OT_MADE_EASY_OT deposit_purse(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_PURSE);
    string OT_MADE_EASY_OT exchange_basket_currency(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_TYPE, const string & THE_BASKET, const string & ACCT_ID, const bool IN_OR_OUT);
    string OT_MADE_EASY_OT get_box_receipt(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const int nBoxType, const string & STR_TRANS_NUM);
    string OT_MADE_EASY_OT get_market_list(const string & SERVER_ID, const string & NYM_ID);
    string OT_MADE_EASY_OT get_market_offers(const string & SERVER_ID, const string & NYM_ID, const string & MARKET_ID, const int64_t MAX_DEPTH);
    string OT_MADE_EASY_OT get_market_recent_trades(const string & SERVER_ID, const string & NYM_ID, const string & MARKET_ID);
    string OT_MADE_EASY_OT get_nym_market_offers(const string & SERVER_ID, const string & NYM_ID);
    string OT_MADE_EASY_OT get_payment_instrument(const string & SERVER_ID, const string & NYM_ID, const int nIndex);
    string OT_MADE_EASY_OT get_payment_instrument(const string & SERVER_ID, const string & NYM_ID, const int nIndex, const string & PRELOADED_INBOX); // PRELOADED_INBOX is optional.
    bool OT_MADE_EASY_OT insure_enough_nums(const int nNumberNeeded, const string & strMyServerID, const string & strMyNymID);
    string OT_MADE_EASY_OT issue_asset_type(const string & SERVER_ID, const string & NYM_ID, const string & THE_CONTRACT);
    string OT_MADE_EASY_OT issue_basket_currency(const string & SERVER_ID, const string & NYM_ID, const string & THE_BASKET);
    string OT_MADE_EASY_OT kill_market_offer(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ACCT_ID, const string & STR_TRANS_NUM);
    string OT_MADE_EASY_OT kill_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_TRANS_NUM);
    string OT_MADE_EASY_OT load_or_retrieve_contract(const string & SERVER_ID, const string & NYM_ID, const string & CONTRACT_ID);
    string OT_MADE_EASY_OT load_or_retrieve_encrypt_key(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    string OT_MADE_EASY_OT load_or_retrieve_mint(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ID);
    string OT_MADE_EASY_OT load_or_retrieve_signing_key(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    string OT_MADE_EASY_OT load_public_encryption_key(const string & NYM_ID); // from local storage.
    string OT_MADE_EASY_OT load_public_signing_key(const string & NYM_ID); // from local storage.
    string OT_MADE_EASY_OT pay_dividend(const string & SERVER_ID, const string & NYM_ID, const string & SOURCE_ACCT_ID, const string & SHARES_ASSET_ID, const string & STR_MEMO, const int64_t AMOUNT_PER_SHARE);
    string OT_MADE_EASY_OT process_inbox(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID, const string & RESPONSE_LEDGER);
    string OT_MADE_EASY_OT query_asset_types(const string & SERVER_ID, const string & NYM_ID, const string & ENCODED_MAP);
    string OT_MADE_EASY_OT register_nym(const string & SERVER_ID, const string & NYM_ID);
    bool OT_MADE_EASY_OT retrieve_account(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID);
    bool OT_MADE_EASY_OT retrieve_account(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID, const bool bForceDownload); // bForceDownload=false
    string OT_MADE_EASY_OT retrieve_contract(const string & SERVER_ID, const string & NYM_ID, const string & CONTRACT_ID);
    string OT_MADE_EASY_OT retrieve_mint(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ID);
    int OT_MADE_EASY_OT retrieve_nym(const string & strServerID, const string & strMyNymID, bool & bWasMsgSent, const bool bForceDownload);
    string OT_MADE_EASY_OT send_transfer(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_FROM, const string & ACCT_TO, const int64_t AMOUNT, const string & NOTE);
    string OT_MADE_EASY_OT send_user_cash(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_PAYMENT, const string & SENDERS_COPY);
    string OT_MADE_EASY_OT send_user_cash_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_INSTRUMENT, const string & INSTRUMENT_FOR_SENDER);
    string OT_MADE_EASY_OT send_user_msg(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_MESSAGE);
    string OT_MADE_EASY_OT send_user_msg_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_MESSAGE);
    string OT_MADE_EASY_OT send_user_payment(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_PAYMENT);
    string OT_MADE_EASY_OT send_user_pmnt_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_INSTRUMENT);
    string OT_MADE_EASY_OT stat_asset_account(const string & ACCOUNT_ID);
    string OT_MADE_EASY_OT trigger_clause(const string & SERVER_ID, const string & NYM_ID, const string & STR_TRANS_NUM, const string & CLAUSE_NAME, const string & STR_PARAM);
    string OT_MADE_EASY_OT withdraw_cash(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const int64_t AMOUNT);
    string OT_MADE_EASY_OT withdraw_voucher(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & RECIP_NYM_ID, const string & STR_MEMO, const int64_t AMOUNT);
};

#endif

