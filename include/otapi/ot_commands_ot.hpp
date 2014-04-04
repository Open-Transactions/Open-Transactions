#ifndef _H_OT_COMMAND_OT
#define _H_OT_COMMAND_OT

#include "OTCommon.hpp"

#include <map>
#include <vector>

#include <OTStorage.hpp>

#define OT_COMMANDS_OT


using std::map;
using std::string;
using std::vector;


EXPORT OT_COMMANDS_OT int32_t accept_from_paymentbox(const string & strMyAcctID, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t accept_from_paymentbox(const string & strMyAcctID, const string & strIndices, const string & strPaymentType);
EXPORT OT_COMMANDS_OT int32_t accept_inbox_items(const string & strMyAcctID, const int32_t nItemType, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t details_accept_invoices(const string & strMyAcctID); // Use this function when you want to loop through all accounts and accept all invoices for them.
EXPORT OT_COMMANDS_OT int32_t details_accept_invoices(const string & strMyAcctID, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t details_accept_payments(const string & strMyAcctID);
EXPORT OT_COMMANDS_OT int32_t details_accept_payments(const string & strMyAcctID, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t details_account_balance(const string & strID);
EXPORT OT_COMMANDS_OT int32_t details_cancel_outgoing(const string & strMyNym, const string & strMyAcct, const string & strIndices);
EXPORT OT_COMMANDS_OT string details_check_user(const string & strServerID, const string & strMyNymID, const string & strHisNymID);
EXPORT OT_COMMANDS_OT int32_t details_clear_expired(const string & strServerID, const string & strMyNymID);
EXPORT OT_COMMANDS_OT int32_t details_clear_records(const string & strServerID, const string & strMyNymID, const string & strMyAcctID);
EXPORT OT_COMMANDS_OT int32_t details_confirm_plan(const string & strPlan, const int32_t nIndex);
EXPORT OT_COMMANDS_OT int32_t details_confirm_smart_contract(string & strSmartContract, const int32_t nIndex);
EXPORT OT_COMMANDS_OT int32_t details_create_nym(const int32_t nKeybits, const string & strName, const string & strSourceForNymID, const string & strAltLocation);
EXPORT OT_COMMANDS_OT int32_t details_create_offer(const string & strScale, const string & strMinIncrement, const string & strQuantity, const string & strPrice, const bool bSelling, const string & strLifespan);
EXPORT OT_COMMANDS_OT int32_t details_del_mail(const string & strMyNymID, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t details_del_outmail(const string & strMyNymID, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t details_deposit(const string & strServerID, const string & strMyAcctID);
EXPORT OT_COMMANDS_OT int32_t details_deposit_cheque(const string & strServerID, const string & strMyAcct, const string & strMyNymID, const string & strInstrument, const string & strType);
EXPORT OT_COMMANDS_OT int32_t details_deposit_purse(const string & strServerID, const string & strMyAcct, const string & strFromNymID, const string & strInstrument, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t details_discard_incoming(const string & strServer, const string & strMyNym, const string & strIndices);
EXPORT OT_COMMANDS_OT int32_t details_download_box_receipt(const string & strID, const int32_t nBoxType);
EXPORT OT_COMMANDS_OT int32_t details_download_contract(const string & strServerID, const string & strNymID, const string & strContractID);
EXPORT OT_COMMANDS_OT int32_t details_exchange_basket(const string & strServer, const string & strNym, const string & strAcct, const string & strBasketType);
EXPORT OT_COMMANDS_OT string details_export_cash(const string & strServerID, const string & strFromNymID, const string & strAssetTypeID, string & strHisNymID, const string & strIndices, const bool bPasswordProtected, string & strRetainedCopy);
EXPORT OT_COMMANDS_OT string details_export_nym(const string & strNymID);
EXPORT OT_COMMANDS_OT string details_get_nym_market_offers(const string & strServerID, const string & strNymID);
EXPORT OT_COMMANDS_OT int32_t details_import_cash(const string & strInstrument);
EXPORT OT_COMMANDS_OT bool details_import_nym(const string & strNymImportFile, string & strOutNymID);
EXPORT OT_COMMANDS_OT int32_t details_import_purse(const string & strInstrument, const bool bHasPassword, const string & strPurseOwner);
EXPORT OT_COMMANDS_OT int32_t details_kill_offer(const string & strServerID, const string & strNymID, const string & strAcctID, const string & strTransNum);
EXPORT OT_COMMANDS_OT int32_t details_new_basket(const string & strServer, const string & strNym);
EXPORT OT_COMMANDS_OT int32_t details_nym_stat(const string & strID);
EXPORT OT_COMMANDS_OT int32_t details_pay_dividend(const string & strAmount, const string & strMemo);
EXPORT OT_COMMANDS_OT int32_t details_propose_plan(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const string & strHisNymID, const string & strHisAcctID, const string & strDates, const string & strConsideration, const string & strInitialPayment, const string & strPaymentPlan, const string & strExpiry);
EXPORT OT_COMMANDS_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID);
EXPORT OT_COMMANDS_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID, const bool bForceDownload);
EXPORT OT_COMMANDS_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID, bool & bWasMsgSent, const bool bForceDownload);
EXPORT OT_COMMANDS_OT int32_t details_send_cash(string & strResponse, const string & strServerID, const string & strAssetTypeID, const string & strMyNymID, const string & strMyAcctID, string & strHisNymID, const string & strMemo, const string & strAmount, string & strIndices, const bool bPasswordProtected);
EXPORT OT_COMMANDS_OT int32_t details_send_transfer(const string & strMyAcctID, const string & strHisAcctID, const string & strAmount, const string & strNote);
EXPORT OT_COMMANDS_OT int32_t details_show_basket();
EXPORT OT_COMMANDS_OT bool details_show_credential(const string & strMyNymID, const string & strCredID);
EXPORT OT_COMMANDS_OT int32_t details_show_credentials(const string & strMyNymID);
EXPORT OT_COMMANDS_OT int32_t details_show_expired(const string & strServerID, const string & strMyNymID, const int32_t nIndex);
EXPORT OT_COMMANDS_OT int32_t details_show_expired(const string & strServerID, const string & strMyNymID, const int32_t nIndex, const string & strExpiredBox);
EXPORT OT_COMMANDS_OT int32_t details_show_expired_records(const string & strServerID, const string & strMyNymID);
EXPORT OT_COMMANDS_OT int32_t details_show_market_offers(const string & strServerID, const string & strMarketID);
EXPORT OT_COMMANDS_OT int32_t details_show_nym_offers(const string & strServerID, const string & strNymID);
EXPORT OT_COMMANDS_OT int32_t details_show_record(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const int32_t nIndex);
EXPORT OT_COMMANDS_OT int32_t details_show_record(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const int32_t nIndex, const string & strRecordBox);
EXPORT OT_COMMANDS_OT int32_t details_show_records(const string & strServerID, const string & strMyNymID, const string & strMyAcctID);
EXPORT OT_COMMANDS_OT int32_t details_stat_account(const string & strID);
EXPORT OT_COMMANDS_OT int32_t details_trigger_clause(const string & strServerID, const string & strMyNymID, const string & strTransNum, const string & strClause, const string & strParam);
EXPORT OT_COMMANDS_OT int32_t details_withdraw_cash(const string & strMyAcctID, const int64_t lAmount);
EXPORT OT_COMMANDS_OT int32_t details_withdraw_voucher(string & strOutput);
EXPORT OT_COMMANDS_OT int32_t details_write_cheque(string & strCheque, const bool bIsInvoice); // strCheque is output.
EXPORT OT_COMMANDS_OT int32_t download_acct_files();
EXPORT OT_COMMANDS_OT string find_masterID_for_subcred(const string & strMyNymID, const string & strInputID);
EXPORT OT_COMMANDS_OT string find_revokedID_for_subcred(const string & strMyNymID, const string & strInputID);
EXPORT OT_COMMANDS_OT int32_t handle_payment_index(const string & strMyAcctID, const int32_t nIndex); // (If nIndex is -1, then it will ask user to paste an invoice.);
EXPORT OT_COMMANDS_OT int32_t handle_payment_index(const string & strMyAcctID, const int32_t nIndex, const string & strPaymentType); // (If nIndex is -1, then it will ask user to paste an invoice.);
EXPORT OT_COMMANDS_OT int32_t handle_payment_index(const string & strMyAcctID, const int32_t nIndex, const string & strPaymentType, const string & strInbox); // (If nIndex is -1, then it will ask user to paste an invoice.);
EXPORT OT_COMMANDS_OT int32_t impl_show_market_offers(string & strMarket);
EXPORT OT_COMMANDS_OT OTDB::MarketList * loadMarketList(const string & strerverID);
EXPORT OT_COMMANDS_OT OTDB::OfferListMarket * loadMarketOffers(const string & strerverID, const string & strMarketID);
EXPORT OT_COMMANDS_OT int32_t main_accept_all();
EXPORT OT_COMMANDS_OT int32_t main_accept_inbox();
EXPORT OT_COMMANDS_OT int32_t main_accept_invoices();
EXPORT OT_COMMANDS_OT int32_t main_accept_money();
EXPORT OT_COMMANDS_OT int32_t main_accept_payments();
EXPORT OT_COMMANDS_OT int32_t main_accept_receipts();
EXPORT OT_COMMANDS_OT int32_t main_accept_transfers();
EXPORT OT_COMMANDS_OT int32_t main_add_asset();
EXPORT OT_COMMANDS_OT int32_t main_add_server();
EXPORT OT_COMMANDS_OT int32_t main_add_signature();
EXPORT OT_COMMANDS_OT int32_t main_adjust_usage_credits();
EXPORT OT_COMMANDS_OT int32_t main_balance();
EXPORT OT_COMMANDS_OT int32_t main_cancel_outgoing();
EXPORT OT_COMMANDS_OT int32_t main_change_passphrase();
EXPORT OT_COMMANDS_OT int32_t main_check_user();
EXPORT OT_COMMANDS_OT int32_t main_clear_expired();
EXPORT OT_COMMANDS_OT int32_t main_clear_records();
EXPORT OT_COMMANDS_OT int32_t main_confirm(); // smart contract and payment plan
EXPORT OT_COMMANDS_OT int32_t main_create_acct();
EXPORT OT_COMMANDS_OT int32_t main_create_asset_contract();
EXPORT OT_COMMANDS_OT int32_t main_create_nym();
EXPORT OT_COMMANDS_OT int32_t main_create_offer();
EXPORT OT_COMMANDS_OT int32_t main_create_server_contract();
EXPORT OT_COMMANDS_OT int32_t main_decode();
EXPORT OT_COMMANDS_OT int32_t main_decrypt();
EXPORT OT_COMMANDS_OT int32_t main_del_mail();
EXPORT OT_COMMANDS_OT int32_t main_del_outmail();
EXPORT OT_COMMANDS_OT int32_t main_deposit();
EXPORT OT_COMMANDS_OT int32_t main_discard_incoming();
EXPORT OT_COMMANDS_OT int32_t main_dl_acct_files();
EXPORT OT_COMMANDS_OT int32_t main_download_contract();
EXPORT OT_COMMANDS_OT int32_t main_edit_account();
EXPORT OT_COMMANDS_OT int32_t main_edit_asset();
EXPORT OT_COMMANDS_OT int32_t main_edit_nym();
EXPORT OT_COMMANDS_OT int32_t main_edit_server();
EXPORT OT_COMMANDS_OT int32_t main_encode();
EXPORT OT_COMMANDS_OT int32_t main_encrypt();
EXPORT OT_COMMANDS_OT int32_t main_exchange_basket();
EXPORT OT_COMMANDS_OT int32_t main_export_cash();
EXPORT OT_COMMANDS_OT int32_t main_export_nym();
EXPORT OT_COMMANDS_OT int32_t main_get_box_receipt();
EXPORT OT_COMMANDS_OT int32_t main_get_market_list();
EXPORT OT_COMMANDS_OT int32_t main_get_market_offers();
EXPORT OT_COMMANDS_OT int32_t main_get_nym_market_offers();
EXPORT OT_COMMANDS_OT int32_t main_import_cash();
EXPORT OT_COMMANDS_OT int32_t main_import_nym();
EXPORT OT_COMMANDS_OT int32_t main_issue_asset();
EXPORT OT_COMMANDS_OT int32_t main_kill_offer();
EXPORT OT_COMMANDS_OT int32_t main_kill_plan();
EXPORT OT_COMMANDS_OT int32_t main_new_basket();
EXPORT OT_COMMANDS_OT int32_t main_new_credential();
EXPORT OT_COMMANDS_OT int32_t main_new_symmetric_key();
EXPORT OT_COMMANDS_OT int32_t main_nym_stat();
EXPORT OT_COMMANDS_OT int32_t main_password_decrypt();
EXPORT OT_COMMANDS_OT int32_t main_password_encrypt();
EXPORT OT_COMMANDS_OT int32_t main_pay_dividend();
EXPORT OT_COMMANDS_OT int32_t main_payinvoice();
EXPORT OT_COMMANDS_OT int32_t main_propose_plan(); // payment plan -- called by recipient. (Who generates the proposal.);
EXPORT OT_COMMANDS_OT int32_t main_refresh_all();
EXPORT OT_COMMANDS_OT int32_t main_refresh_nym();
EXPORT OT_COMMANDS_OT int32_t main_register_nym();
EXPORT OT_COMMANDS_OT int32_t main_revoke_credential();
EXPORT OT_COMMANDS_OT int32_t main_sendcash();
EXPORT OT_COMMANDS_OT int32_t main_sendcheque();
EXPORT OT_COMMANDS_OT int32_t main_sendinvoice();
EXPORT OT_COMMANDS_OT int32_t main_sendmsg();
EXPORT OT_COMMANDS_OT int32_t main_sendvoucher();
EXPORT OT_COMMANDS_OT int32_t main_show_active();
EXPORT OT_COMMANDS_OT int32_t main_show_basket();
EXPORT OT_COMMANDS_OT int32_t main_show_credential();
EXPORT OT_COMMANDS_OT int32_t main_show_credentials();
EXPORT OT_COMMANDS_OT int32_t main_show_expired();
EXPORT OT_COMMANDS_OT int32_t main_show_inbox();
EXPORT OT_COMMANDS_OT int32_t main_show_incoming();
EXPORT OT_COMMANDS_OT int32_t main_show_mail();
EXPORT OT_COMMANDS_OT int32_t main_show_market_list();
EXPORT OT_COMMANDS_OT int32_t main_show_market_offers();
EXPORT OT_COMMANDS_OT int32_t main_show_mint();
EXPORT OT_COMMANDS_OT int32_t main_show_nym_offers();
EXPORT OT_COMMANDS_OT int32_t main_show_outbox();
EXPORT OT_COMMANDS_OT int32_t main_show_outgoing();
EXPORT OT_COMMANDS_OT int32_t main_show_outmail();
EXPORT OT_COMMANDS_OT int32_t main_show_outpayment();
EXPORT OT_COMMANDS_OT int32_t main_show_payment();
EXPORT OT_COMMANDS_OT int32_t main_show_payments_inbox();
EXPORT OT_COMMANDS_OT int32_t main_show_purse();
EXPORT OT_COMMANDS_OT int32_t main_show_records();
EXPORT OT_COMMANDS_OT int32_t main_sign_contract();
EXPORT OT_COMMANDS_OT int32_t main_stat();
EXPORT OT_COMMANDS_OT int32_t main_stat_acct();
EXPORT OT_COMMANDS_OT int32_t main_transfer();
EXPORT OT_COMMANDS_OT int32_t main_trigger_clause();
EXPORT OT_COMMANDS_OT int32_t main_verify_last_receipt();
EXPORT OT_COMMANDS_OT int32_t main_verify_signature();
EXPORT OT_COMMANDS_OT int32_t main_withdraw_cash();
EXPORT OT_COMMANDS_OT int32_t main_withdraw_voucher();
EXPORT OT_COMMANDS_OT int32_t main_write_cheque();
EXPORT OT_COMMANDS_OT int32_t main_write_invoice();
EXPORT OT_COMMANDS_OT bool purse_get_indices_or_amount(const string & strServerID, const string & strAssetTypeID, const string & strMyNymID, int64_t & lAmount, string & strIndices); // If strIndices is input, lAmount is output. (And vice-versa.);
EXPORT OT_COMMANDS_OT int32_t show_mail_message(const string & strMyNymID, const int32_t nIndex, const bool bShowContents);
EXPORT OT_COMMANDS_OT int32_t show_outmail_message(const string & strMyNymID, const int32_t nIndex, const bool bShowContents);
EXPORT OT_COMMANDS_OT bool show_outpayment(const string & strMyNym, const int32_t nIndex);
EXPORT OT_COMMANDS_OT bool show_outpayment(const string & strMyNym, const int32_t nIndex, const bool bShowInFull);
EXPORT OT_COMMANDS_OT bool show_unconfirmed_parties(const string & strSmartContract);
EXPORT OT_COMMANDS_OT bool show_unconfirmed_parties(const string & strSmartContract, int32_t & nPartyCount);
EXPORT OT_COMMANDS_OT int32_t stat_accounts();
EXPORT OT_COMMANDS_OT int32_t stat_assets();
EXPORT OT_COMMANDS_OT int32_t stat_basket_accounts();
EXPORT OT_COMMANDS_OT int32_t stat_basket_accounts(const string & strServer, const string & strNym);
EXPORT OT_COMMANDS_OT int32_t stat_basket_accounts(const string & strServer, const string & strNym, const bool bFilter, const string & strBasketType);
EXPORT OT_COMMANDS_OT int32_t stat_nyms();
EXPORT OT_COMMANDS_OT bool stat_partyaccount(const string & strSmartContract, const string & strPartyName, const string & strAcctName, const int32_t nCurrentAccount);
EXPORT OT_COMMANDS_OT bool stat_partyaccount_index(const string & strSmartContract, const string & strPartyName, const int32_t nCurrentAccount);
EXPORT OT_COMMANDS_OT bool stat_partyaccounts(const string & strSmartContract, const string & strPartyName, const int32_t nDepth);
EXPORT OT_COMMANDS_OT bool stat_partyagent(const string & strSmartContract, const string & strPartyName, const string & strAgentName, const int32_t nIndex);
EXPORT OT_COMMANDS_OT bool stat_partyagent_index(const string & strSmartContract, const string & strPartyName, const int32_t nCurrentAgent);
EXPORT OT_COMMANDS_OT bool stat_partyagents(const string & strSmartContract, const string & strPartyName, const int32_t nDepth);
EXPORT OT_COMMANDS_OT int32_t stat_servers();
EXPORT OT_COMMANDS_OT bool withdraw_and_send_cash(const string & strMyAcctID, string & strHisNymID, const string & strMemo, const string & strAmount);

#endif
