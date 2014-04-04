#ifndef _H_OT_MADE_EASY_OT
#define _H_OT_MADE_EASY_OT

#include "OTCommon.hpp"

#include <string>
#include <vector>

#define OT_MADE_EASY_OT


using std::string;
using std::vector;


class MadeEasy
{
private:
    // do not allow construction
    MadeEasy() {}
    ~MadeEasy() {}

public:

    EXPORT OT_MADE_EASY_OT static string activate_smart_contract(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & AGENT_NAME, const string & THE_SMART_CONTRACT);
    EXPORT OT_MADE_EASY_OT static string adjust_usage_credits(const string & SERVER_ID, const string & USER_NYM_ID, const string & TARGET_NYM_ID, const string & ADJUSTMENT);
    EXPORT OT_MADE_EASY_OT static string cancel_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & THE_PAYMENT_PLAN);
    EXPORT OT_MADE_EASY_OT static string check_user(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    EXPORT OT_MADE_EASY_OT static string create_asset_acct(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_TYPE_ID);
    EXPORT OT_MADE_EASY_OT static string create_market_offer(const string & ASSET_ACCT_ID, const string & CURRENCY_ACCT_ID, const string & scale, const string & minIncrement, const string & quantity, const string & price, const bool bSelling, const string & strLifespanInSeconds, const string & strStopSign, const string & strActivationPrice);
    EXPORT OT_MADE_EASY_OT static string create_pseudonym(const int32_t nKeybits, const string & strNymIDSource, const string & strAltLocation);
    EXPORT OT_MADE_EASY_OT static string deposit_cheque(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_CHEQUE);
    EXPORT OT_MADE_EASY_OT static string deposit_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & THE_PAYMENT_PLAN);
    EXPORT OT_MADE_EASY_OT static string deposit_purse(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_PURSE);
    EXPORT OT_MADE_EASY_OT static int32_t depositCashPurse(const string & serverID, const string & assetID, const string & nymID, const string & oldPurse, const vector<string> & selectedTokens, const string & accountID, const bool bReimportIfFailure); // So we don't re-import a purse that wasn't internal to begin with.
    EXPORT OT_MADE_EASY_OT static string exchange_basket_currency(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_TYPE, const string & THE_BASKET, const string & ACCT_ID, const bool IN_OR_OUT);
    EXPORT OT_MADE_EASY_OT static bool exchangeCashPurse(const string & serverID, const string & assetID, const string & nymID, string & oldPurse, const vector<string> & selectedTokens);
    EXPORT OT_MADE_EASY_OT static string exportCashPurse(const string & serverID, const string & assetID, const string & nymID, const string & oldPurse, const vector<string> & selectedTokens, string & recipientNymID, const bool bPasswordProtected, string & strRetainedCopy);
    EXPORT OT_MADE_EASY_OT static string get_box_receipt(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const int32_t nBoxType, const string & STR_TRANS_NUM);
    EXPORT OT_MADE_EASY_OT static string get_market_list(const string & SERVER_ID, const string & NYM_ID);
    EXPORT OT_MADE_EASY_OT static string get_market_offers(const string & SERVER_ID, const string & NYM_ID, const string & MARKET_ID, const int64_t MAX_DEPTH);
    EXPORT OT_MADE_EASY_OT static string get_market_recent_trades(const string & SERVER_ID, const string & NYM_ID, const string & MARKET_ID);
    EXPORT OT_MADE_EASY_OT static string get_nym_market_offers(const string & SERVER_ID, const string & NYM_ID);
    EXPORT OT_MADE_EASY_OT static string get_payment_instrument(const string & SERVER_ID, const string & NYM_ID, const int32_t nIndex, const string & PRELOADED_INBOX); // PRELOADED_INBOX is optional.
    EXPORT OT_MADE_EASY_OT static bool importCashPurse(const string & serverID, const string & nymID, const string & assetID, string & userInput, const bool isPurse);
    EXPORT OT_MADE_EASY_OT static bool insure_enough_nums(const int32_t nNumberNeeded, const string & strMyServerID, const string & strMyNymID);
    EXPORT OT_MADE_EASY_OT static string issue_asset_type(const string & SERVER_ID, const string & NYM_ID, const string & THE_CONTRACT);
    EXPORT OT_MADE_EASY_OT static string issue_basket_currency(const string & SERVER_ID, const string & NYM_ID, const string & THE_BASKET);
    EXPORT OT_MADE_EASY_OT static string kill_market_offer(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ACCT_ID, const string & STR_TRANS_NUM);
    EXPORT OT_MADE_EASY_OT static string kill_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_TRANS_NUM);
    EXPORT OT_MADE_EASY_OT static string load_or_retrieve_contract(const string & SERVER_ID, const string & NYM_ID, const string & CONTRACT_ID);
    EXPORT OT_MADE_EASY_OT static string load_or_retrieve_encrypt_key(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    EXPORT OT_MADE_EASY_OT static string load_or_retrieve_mint(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ID);
    EXPORT OT_MADE_EASY_OT static string load_or_retrieve_signing_key(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    EXPORT OT_MADE_EASY_OT static string load_public_encryption_key(const string & NYM_ID); // from local storage.
    EXPORT OT_MADE_EASY_OT static string load_public_signing_key(const string & NYM_ID); // from local storage.
    EXPORT OT_MADE_EASY_OT static string pay_dividend(const string & SERVER_ID, const string & NYM_ID, const string & SOURCE_ACCT_ID, const string & SHARES_ASSET_ID, const string & STR_MEMO, const int64_t AMOUNT_PER_SHARE);
    EXPORT OT_MADE_EASY_OT static string process_inbox(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID, const string & RESPONSE_LEDGER);
    EXPORT OT_MADE_EASY_OT static bool processCashPurse(string & newPurse, string & newPurseForSender, const string & serverID, const string & assetID, const string & nymID, string & oldPurse, const vector<string> & selectedTokens, const string & recipientNymID, const bool bPWProtectOldPurse, const bool bPWProtectNewPurse);
    EXPORT OT_MADE_EASY_OT static string query_asset_types(const string & SERVER_ID, const string & NYM_ID, const string & ENCODED_MAP);
    EXPORT OT_MADE_EASY_OT static string register_nym(const string & SERVER_ID, const string & NYM_ID);
    EXPORT OT_MADE_EASY_OT static bool retrieve_account(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID, const bool bForceDownload); // bForceDownload=false
    EXPORT OT_MADE_EASY_OT static string retrieve_contract(const string & SERVER_ID, const string & NYM_ID, const string & CONTRACT_ID);
    EXPORT OT_MADE_EASY_OT static string retrieve_mint(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ID);
    EXPORT OT_MADE_EASY_OT static int32_t retrieve_nym(const string & strServerID, const string & strMyNymID, bool & bWasMsgSent, const bool bForceDownload);
    EXPORT OT_MADE_EASY_OT static string send_transfer(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_FROM, const string & ACCT_TO, const int64_t AMOUNT, const string & NOTE);
    EXPORT OT_MADE_EASY_OT static string send_user_cash(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_PAYMENT, const string & SENDERS_COPY);
    EXPORT OT_MADE_EASY_OT static string send_user_cash_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_INSTRUMENT, const string & INSTRUMENT_FOR_SENDER);
    EXPORT OT_MADE_EASY_OT static string send_user_msg(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_MESSAGE);
    EXPORT OT_MADE_EASY_OT static string send_user_msg_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_MESSAGE);
    EXPORT OT_MADE_EASY_OT static string send_user_payment(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_PAYMENT);
    EXPORT OT_MADE_EASY_OT static string send_user_pmnt_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_INSTRUMENT);
    EXPORT OT_MADE_EASY_OT static string stat_asset_account(const string & ACCOUNT_ID);
    EXPORT OT_MADE_EASY_OT static string trigger_clause(const string & SERVER_ID, const string & NYM_ID, const string & STR_TRANS_NUM, const string & CLAUSE_NAME, const string & STR_PARAM);
    EXPORT OT_MADE_EASY_OT static string withdraw_cash(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const int64_t AMOUNT);
    EXPORT OT_MADE_EASY_OT static string withdraw_voucher(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & RECIP_NYM_ID, const string & STR_MEMO, const int64_t AMOUNT);
};

#endif

