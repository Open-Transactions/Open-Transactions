#ifndef _H_OT_MADE_EASY_OT
#define _H_OT_MADE_EASY_OT

#include "OTCommon.hpp"

#include <string>
#include <vector>

#define OT_MADE_EASY_OT


using std::string;
using std::vector;


EXPORT OT_MADE_EASY_OT int32_t depositCashPurse(const string & serverID, const string & assetID, const string & nymID, const string & oldPurse, const vector<string> & selectedTokens, const string & accountID, const bool bReimportIfFailure); // So we don't re-import a purse that wasn't internal to begin with.
EXPORT OT_MADE_EASY_OT bool exchangeCashPurse(const string & serverID, const string & assetID, const string & nymID, string & oldPurse, const vector<string> & selectedTokens);
EXPORT OT_MADE_EASY_OT string exportCashPurse(const string & serverID, const string & assetID, const string & nymID, const string & oldPurse, const vector<string> & selectedTokens, string & recipientNymID, const bool bPasswordProtected, string & strRetainedCopy);
EXPORT OT_MADE_EASY_OT bool importCashPurse(const string & serverID, const string & nymID, const string & assetID, string & userInput, const bool isPurse);
EXPORT OT_MADE_EASY_OT bool processCashPurse(string & newPurse, string & newPurseForSender, const string & serverID, const string & assetID, const string & nymID, string & oldPurse, const vector<string> & selectedTokens, const string & recipientNymID, const bool bPWProtectOldPurse, const bool bPWProtectNewPurse);

class MadeEasy
{
public:
    MadeEasy();
    ~MadeEasy();

    OT_MADE_EASY_OT string activate_smart_contract(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & AGENT_NAME, const string & THE_SMART_CONTRACT);
    OT_MADE_EASY_OT string adjust_usage_credits(const string & SERVER_ID, const string & USER_NYM_ID, const string & TARGET_NYM_ID, const string & ADJUSTMENT);
    OT_MADE_EASY_OT string cancel_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & THE_PAYMENT_PLAN);
    OT_MADE_EASY_OT string check_user(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    OT_MADE_EASY_OT string create_asset_acct(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_TYPE_ID);
    OT_MADE_EASY_OT string create_market_offer(const string & ASSET_ACCT_ID, const string & CURRENCY_ACCT_ID, const string & scale, const string & minIncrement, const string & quantity, const string & price, const bool bSelling, const string & strLifespanInSeconds, const string & strStopSign, const string & strActivationPrice);
    OT_MADE_EASY_OT string create_pseudonym(const int32_t nKeybits, const string & strNymIDSource, const string & strAltLocation);
    OT_MADE_EASY_OT string deposit_cheque(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_CHEQUE);
    OT_MADE_EASY_OT string deposit_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & THE_PAYMENT_PLAN);
    OT_MADE_EASY_OT string deposit_purse(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_PURSE);
    OT_MADE_EASY_OT string exchange_basket_currency(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_TYPE, const string & THE_BASKET, const string & ACCT_ID, const bool IN_OR_OUT);
    OT_MADE_EASY_OT string get_box_receipt(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const int32_t nBoxType, const string & STR_TRANS_NUM);
    OT_MADE_EASY_OT string get_market_list(const string & SERVER_ID, const string & NYM_ID);
    OT_MADE_EASY_OT string get_market_offers(const string & SERVER_ID, const string & NYM_ID, const string & MARKET_ID, const int64_t MAX_DEPTH);
    OT_MADE_EASY_OT string get_market_recent_trades(const string & SERVER_ID, const string & NYM_ID, const string & MARKET_ID);
    OT_MADE_EASY_OT string get_nym_market_offers(const string & SERVER_ID, const string & NYM_ID);
    OT_MADE_EASY_OT string get_payment_instrument(const string & SERVER_ID, const string & NYM_ID, const int32_t nIndex);
    OT_MADE_EASY_OT string get_payment_instrument(const string & SERVER_ID, const string & NYM_ID, const int32_t nIndex, const string & PRELOADED_INBOX); // PRELOADED_INBOX is optional.
    OT_MADE_EASY_OT bool insure_enough_nums(const int32_t nNumberNeeded, const string & strMyServerID, const string & strMyNymID);
    OT_MADE_EASY_OT string issue_asset_type(const string & SERVER_ID, const string & NYM_ID, const string & THE_CONTRACT);
    OT_MADE_EASY_OT string issue_basket_currency(const string & SERVER_ID, const string & NYM_ID, const string & THE_BASKET);
    OT_MADE_EASY_OT string kill_market_offer(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ACCT_ID, const string & STR_TRANS_NUM);
    OT_MADE_EASY_OT string kill_payment_plan(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & STR_TRANS_NUM);
    OT_MADE_EASY_OT string load_or_retrieve_contract(const string & SERVER_ID, const string & NYM_ID, const string & CONTRACT_ID);
    OT_MADE_EASY_OT string load_or_retrieve_encrypt_key(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    OT_MADE_EASY_OT string load_or_retrieve_mint(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ID);
    OT_MADE_EASY_OT string load_or_retrieve_signing_key(const string & SERVER_ID, const string & NYM_ID, const string & TARGET_NYM_ID);
    OT_MADE_EASY_OT string load_public_encryption_key(const string & NYM_ID); // from local storage.
    OT_MADE_EASY_OT string load_public_signing_key(const string & NYM_ID); // from local storage.
    OT_MADE_EASY_OT string pay_dividend(const string & SERVER_ID, const string & NYM_ID, const string & SOURCE_ACCT_ID, const string & SHARES_ASSET_ID, const string & STR_MEMO, const int64_t AMOUNT_PER_SHARE);
    OT_MADE_EASY_OT string process_inbox(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID, const string & RESPONSE_LEDGER);
    OT_MADE_EASY_OT string query_asset_types(const string & SERVER_ID, const string & NYM_ID, const string & ENCODED_MAP);
    OT_MADE_EASY_OT string register_nym(const string & SERVER_ID, const string & NYM_ID);
    OT_MADE_EASY_OT bool retrieve_account(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID);
    OT_MADE_EASY_OT bool retrieve_account(const string & SERVER_ID, const string & NYM_ID, const string & ACCOUNT_ID, const bool bForceDownload); // bForceDownload=false
    OT_MADE_EASY_OT string retrieve_contract(const string & SERVER_ID, const string & NYM_ID, const string & CONTRACT_ID);
    OT_MADE_EASY_OT string retrieve_mint(const string & SERVER_ID, const string & NYM_ID, const string & ASSET_ID);
    OT_MADE_EASY_OT int32_t retrieve_nym(const string & strServerID, const string & strMyNymID, bool & bWasMsgSent, const bool bForceDownload);
    OT_MADE_EASY_OT string send_transfer(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_FROM, const string & ACCT_TO, const int64_t AMOUNT, const string & NOTE);
    OT_MADE_EASY_OT string send_user_cash(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_PAYMENT, const string & SENDERS_COPY);
    OT_MADE_EASY_OT string send_user_cash_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_INSTRUMENT, const string & INSTRUMENT_FOR_SENDER);
    OT_MADE_EASY_OT string send_user_msg(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_MESSAGE);
    OT_MADE_EASY_OT string send_user_msg_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_MESSAGE);
    OT_MADE_EASY_OT string send_user_payment(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & THE_PAYMENT);
    OT_MADE_EASY_OT string send_user_pmnt_pubkey(const string & SERVER_ID, const string & NYM_ID, const string & RECIPIENT_NYM_ID, const string & RECIPIENT_PUBKEY, const string & THE_INSTRUMENT);
    OT_MADE_EASY_OT string stat_asset_account(const string & ACCOUNT_ID);
    OT_MADE_EASY_OT string trigger_clause(const string & SERVER_ID, const string & NYM_ID, const string & STR_TRANS_NUM, const string & CLAUSE_NAME, const string & STR_PARAM);
    OT_MADE_EASY_OT string withdraw_cash(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const int64_t AMOUNT);
    OT_MADE_EASY_OT string withdraw_voucher(const string & SERVER_ID, const string & NYM_ID, const string & ACCT_ID, const string & RECIP_NYM_ID, const string & STR_MEMO, const int64_t AMOUNT);
};

#endif

