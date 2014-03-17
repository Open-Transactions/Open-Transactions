#ifndef _H_OT_COMMAND_OT
#define _H_OT_COMMAND_OT

#include <algorithm>
#include <string>
#include <vector>

#ifndef EXPORT
#define EXPORT
#endif
#ifndef NOEXPORT
#include <ExportWrapper.h>
#endif

#include "OTStorage.hpp"


#define OT_COMMAND_OT  EXPORT


using std::map;
using std::string;
using std::vector;


extern OT_COMMAND_OT int accept_from_paymentbox(const string & strMyAcctID, const string & strIndices);
extern OT_COMMAND_OT int accept_from_paymentbox(const string & strMyAcctID, const string & strIndices, const string & strPaymentType);
extern OT_COMMAND_OT int accept_inbox_items(const string & strMyAcctID, const int nItemType, const string & strIndices);
extern OT_COMMAND_OT int details_accept_invoices(const string & strMyAcctID); // Use this function when you want to loop through all accounts and accept all invoices for them.
extern OT_COMMAND_OT int details_accept_invoices(const string & strMyAcctID, const string & strIndices);
extern OT_COMMAND_OT int details_accept_payments(const string & strMyAcctID);
extern OT_COMMAND_OT int details_accept_payments(const string & strMyAcctID, const string & strIndices);
extern OT_COMMAND_OT int details_account_balance(const string & strID);
extern OT_COMMAND_OT int details_cancel_outgoing(const string & strMyNym, const string & strMyAcct, const string & strIndices);
extern OT_COMMAND_OT string details_check_user(const string & strServerID, const string & strMyNymID, const string & strHisNymID);
extern OT_COMMAND_OT int details_clear_expired(const string & strServerID, const string & strMyNymID);
extern OT_COMMAND_OT int details_clear_records(const string & strServerID, const string & strMyNymID, const string & strMyAcctID);
extern OT_COMMAND_OT int details_confirm_plan(const string & strPlan, const int nIndex);
extern OT_COMMAND_OT int details_confirm_smart_contract(string & strSmartContract, const int nIndex);
extern OT_COMMAND_OT int details_create_nym(const int nKeybits, const string & strName, const string & strSourceForNymID, const string & strAltLocation);
extern OT_COMMAND_OT int details_create_offer(const string & strScale, const string & strMinIncrement, const string & strQuantity, const string & strPrice, const bool bSelling, const string & strLifespan);
extern OT_COMMAND_OT int details_del_mail(const string & strMyNymID, const string & strIndices);
extern OT_COMMAND_OT int details_del_outmail(const string & strMyNymID, const string & strIndices);
extern OT_COMMAND_OT int details_deposit(const string & strServerID, const string & strMyAcctID);
extern OT_COMMAND_OT int details_deposit_cheque(const string & strServerID, const string & strMyAcct, const string & strMyNymID, const string & strInstrument, const string & strType);
extern OT_COMMAND_OT int details_deposit_purse(const string & strServerID, const string & strMyAcct, const string & strFromNymID, const string & strInstrument, const string & strIndices);
extern OT_COMMAND_OT int details_discard_incoming(const string & strServer, const string & strMyNym, const string & strIndices);
extern OT_COMMAND_OT int details_download_box_receipt(const string & strID, const int nBoxType);
extern OT_COMMAND_OT int details_download_contract(const string & strServerID, const string & strNymID, const string & strContractID);
extern OT_COMMAND_OT int details_exchange_basket(const string & strServer, const string & strNym, const string & strAcct, const string & strBasketType);
extern OT_COMMAND_OT string details_export_cash(const string & strServerID, const string & strFromNymID, const string & strAssetTypeID, string & strHisNymID, const string & strIndices, const bool bPasswordProtected, string & strRetainedCopy);
extern OT_COMMAND_OT string details_export_nym(const string & strNymID);
extern OT_COMMAND_OT string details_get_nym_market_offers(const string & strServerID, const string & strNymID);
extern OT_COMMAND_OT int details_import_cash(const string & strInstrument);
extern OT_COMMAND_OT bool details_import_nym(const string & strNymImportFile, string & strOutNymID);
extern OT_COMMAND_OT int details_import_purse(const string & strInstrument, const bool bHasPassword, const string & strPurseOwner);
extern OT_COMMAND_OT int details_kill_offer(const string & strServerID, const string & strNymID, const string & strAcctID, const string & strTransNum);
extern OT_COMMAND_OT int details_new_basket(const string & strServer, const string & strNym);
extern OT_COMMAND_OT int details_nym_stat(const string & strID);
extern OT_COMMAND_OT int details_pay_dividend(const string & strAmount, const string & strMemo);
extern OT_COMMAND_OT int details_propose_plan(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const string & strHisNymID, const string & strHisAcctID, const string & strDates, const string & strConsideration, const string & strInitialPayment, const string & strPaymentPlan, const string & strExpiry);
extern OT_COMMAND_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID);
extern OT_COMMAND_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID, const bool bForceDownload);
extern OT_COMMAND_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID, bool & bWasMsgSent, const bool bForceDownload);
extern OT_COMMAND_OT int details_send_cash(string & strResponse, const string & strServerID, const string & strAssetTypeID, const string & strMyNymID, const string & strMyAcctID, string & strHisNymID, const string & strMemo, const string & strAmount, string & strIndices, const bool bPasswordProtected);
extern OT_COMMAND_OT int details_send_transfer(const string & strMyAcctID, const string & strHisAcctID, const string & strAmount, const string & strNote);
extern OT_COMMAND_OT int details_show_basket();
extern OT_COMMAND_OT bool details_show_credential(const string & strMyNymID, const string & strCredID);
extern OT_COMMAND_OT int details_show_credentials(const string & strMyNymID);
extern OT_COMMAND_OT int details_show_expired(const string & strServerID, const string & strMyNymID, const int nIndex);
extern OT_COMMAND_OT int details_show_expired(const string & strServerID, const string & strMyNymID, const int nIndex, const string & strExpiredBox);
extern OT_COMMAND_OT int details_show_expired_records(const string & strServerID, const string & strMyNymID);
extern OT_COMMAND_OT int details_show_market_offers(const string & strServerID, const string & strMarketID);
extern OT_COMMAND_OT int details_show_nym_offers(const string & strServerID, const string & strNymID);
extern OT_COMMAND_OT int details_show_record(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const int nIndex);
extern OT_COMMAND_OT int details_show_record(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const int nIndex, const string & strRecordBox);
extern OT_COMMAND_OT int details_show_records(const string & strServerID, const string & strMyNymID, const string & strMyAcctID);
extern OT_COMMAND_OT int details_stat_account(const string & strID);
extern OT_COMMAND_OT int details_trigger_clause(const string & strServerID, const string & strMyNymID, const string & strTransNum, const string & strClause, const string & strParam);
extern OT_COMMAND_OT int details_withdraw_cash(const string & strMyAcctID, const int64_t lAmount);
extern OT_COMMAND_OT int details_withdraw_voucher(string & strOutput);
extern OT_COMMAND_OT int details_write_cheque(string & strCheque, const bool bIsInvoice); // strCheque is output.
extern OT_COMMAND_OT int download_acct_files();
extern OT_COMMAND_OT string find_masterID_for_subcred(const string & strMyNymID, const string & strInputID);
extern OT_COMMAND_OT string find_revokedID_for_subcred(const string & strMyNymID, const string & strInputID);
extern OT_COMMAND_OT int handle_payment_index(const string & strMyAcctID, const int nIndex); // (If nIndex is -1, then it will ask user to paste an invoice.);
extern OT_COMMAND_OT int handle_payment_index(const string & strMyAcctID, const int nIndex, const string & strPaymentType); // (If nIndex is -1, then it will ask user to paste an invoice.);
extern OT_COMMAND_OT int handle_payment_index(const string & strMyAcctID, const int nIndex, const string & strPaymentType, const string & strInbox); // (If nIndex is -1, then it will ask user to paste an invoice.);
extern OT_COMMAND_OT int impl_show_market_offers(string & strMarket);
extern OT_COMMAND_OT OTDB::MarketList * loadMarketList(const string & strerverID);
extern OT_COMMAND_OT OTDB::OfferListMarket * loadMarketOffers(const string & strerverID, const string & strMarketID);
extern OT_COMMAND_OT int main_accept_all();
extern OT_COMMAND_OT int main_accept_inbox();
extern OT_COMMAND_OT int main_accept_invoices();
extern OT_COMMAND_OT int main_accept_money();
extern OT_COMMAND_OT int main_accept_payments();
extern OT_COMMAND_OT int main_accept_receipts();
extern OT_COMMAND_OT int main_accept_transfers();
extern OT_COMMAND_OT int main_add_asset();
extern OT_COMMAND_OT int main_add_server();
extern OT_COMMAND_OT int main_add_signature();
extern OT_COMMAND_OT int main_adjust_usage_credits();
extern OT_COMMAND_OT int main_balance();
extern OT_COMMAND_OT int main_cancel_outgoing();
extern OT_COMMAND_OT int main_change_passphrase();
extern OT_COMMAND_OT int main_check_user();
extern OT_COMMAND_OT int main_clear_expired();
extern OT_COMMAND_OT int main_clear_records();
extern OT_COMMAND_OT int main_confirm(); // smart contract and payment plan
extern OT_COMMAND_OT int main_create_acct();
extern OT_COMMAND_OT int main_create_asset_contract();
extern OT_COMMAND_OT int main_create_nym();
extern OT_COMMAND_OT int main_create_offer();
extern OT_COMMAND_OT int main_create_server_contract();
extern OT_COMMAND_OT int main_decode();
extern OT_COMMAND_OT int main_decrypt();
extern OT_COMMAND_OT int main_del_mail();
extern OT_COMMAND_OT int main_del_outmail();
extern OT_COMMAND_OT int main_deposit();
extern OT_COMMAND_OT int main_discard_incoming();
extern OT_COMMAND_OT int main_dl_acct_files();
extern OT_COMMAND_OT int main_download_contract();
extern OT_COMMAND_OT int main_edit_account();
extern OT_COMMAND_OT int main_edit_asset();
extern OT_COMMAND_OT int main_edit_nym();
extern OT_COMMAND_OT int main_edit_server();
extern OT_COMMAND_OT int main_encode();
extern OT_COMMAND_OT int main_encrypt();
extern OT_COMMAND_OT int main_exchange_basket();
extern OT_COMMAND_OT int main_export_cash();
extern OT_COMMAND_OT int main_export_nym();
extern OT_COMMAND_OT int main_get_box_receipt();
extern OT_COMMAND_OT int main_get_market_list();
extern OT_COMMAND_OT int main_get_market_offers();
extern OT_COMMAND_OT int main_get_nym_market_offers();
extern OT_COMMAND_OT int main_import_cash();
extern OT_COMMAND_OT int main_import_nym();
extern OT_COMMAND_OT int main_issue_asset();
extern OT_COMMAND_OT int main_kill_offer();
extern OT_COMMAND_OT int main_kill_plan();
extern OT_COMMAND_OT int main_new_basket();
extern OT_COMMAND_OT int main_new_credential();
extern OT_COMMAND_OT int main_new_symmetric_key();
extern OT_COMMAND_OT int main_nym_stat();
extern OT_COMMAND_OT int main_password_decrypt();
extern OT_COMMAND_OT int main_password_encrypt();
extern OT_COMMAND_OT int main_pay_dividend();
extern OT_COMMAND_OT int main_payinvoice();
extern OT_COMMAND_OT int main_propose_plan(); // payment plan -- called by recipient. (Who generates the proposal.);
extern OT_COMMAND_OT int main_refresh_all();
extern OT_COMMAND_OT int main_refresh_nym();
extern OT_COMMAND_OT int main_register_nym();
extern OT_COMMAND_OT int main_revoke_credential();
extern OT_COMMAND_OT int main_sendcash();
extern OT_COMMAND_OT int main_sendcheque();
extern OT_COMMAND_OT int main_sendinvoice();
extern OT_COMMAND_OT int main_sendmsg();
extern OT_COMMAND_OT int main_sendvoucher();
extern OT_COMMAND_OT int main_show_basket();
extern OT_COMMAND_OT int main_show_credential();
extern OT_COMMAND_OT int main_show_credentials();
extern OT_COMMAND_OT int main_show_expired();
extern OT_COMMAND_OT int main_show_inbox();
extern OT_COMMAND_OT int main_show_incoming();
extern OT_COMMAND_OT int main_show_mail();
extern OT_COMMAND_OT int main_show_market_list();
extern OT_COMMAND_OT int main_show_market_offers();
extern OT_COMMAND_OT int main_show_mint();
extern OT_COMMAND_OT int main_show_nym_offers();
extern OT_COMMAND_OT int main_show_outbox();
extern OT_COMMAND_OT int main_show_outgoing();
extern OT_COMMAND_OT int main_show_outmail();
extern OT_COMMAND_OT int main_show_outpayment();
extern OT_COMMAND_OT int main_show_payment();
extern OT_COMMAND_OT int main_show_payments_inbox();
extern OT_COMMAND_OT int main_show_purse();
extern OT_COMMAND_OT int main_show_records();
extern OT_COMMAND_OT int main_sign_contract();
extern OT_COMMAND_OT int main_stat();
extern OT_COMMAND_OT int main_stat_acct();
extern OT_COMMAND_OT int main_transfer();
extern OT_COMMAND_OT int main_trigger_clause();
extern OT_COMMAND_OT int main_verify_last_receipt();
extern OT_COMMAND_OT int main_verify_signature();
extern OT_COMMAND_OT int main_withdraw_cash();
extern OT_COMMAND_OT int main_withdraw_voucher();
extern OT_COMMAND_OT int main_write_cheque();
extern OT_COMMAND_OT int main_write_invoice();
extern OT_COMMAND_OT bool purse_get_indices_or_amount(const string & strServerID, const string & strAssetTypeID, const string & strMyNymID, int64_t & lAmount, string & strIndices); // If strIndices is input, lAmount is output. (And vice-versa.);
extern OT_COMMAND_OT int show_mail_message(const string & strMyNymID, const int nIndex, const bool bShowContents);
extern OT_COMMAND_OT int show_outmail_message(const string & strMyNymID, const int nIndex, const bool bShowContents);
extern OT_COMMAND_OT bool show_outpayment(const string & strMyNym, const int nIndex);
extern OT_COMMAND_OT bool show_outpayment(const string & strMyNym, const int nIndex, const bool bShowInFull);
extern OT_COMMAND_OT bool show_unconfirmed_parties(const string & strSmartContract);
extern OT_COMMAND_OT bool show_unconfirmed_parties(const string & strSmartContract, int & nPartyCount);
extern OT_COMMAND_OT int stat_accounts();
extern OT_COMMAND_OT int stat_assets();
extern OT_COMMAND_OT int stat_basket_accounts();
extern OT_COMMAND_OT int stat_basket_accounts(const string & strServer, const string & strNym);
extern OT_COMMAND_OT int stat_basket_accounts(const string & strServer, const string & strNym, const bool bFilter, const string & strBasketType);
extern OT_COMMAND_OT int stat_nyms();
extern OT_COMMAND_OT bool stat_partyaccount(const string & strSmartContract, const string & strPartyName, const string & strAcctName, const int nCurrentAccount);
extern OT_COMMAND_OT bool stat_partyaccount_index(const string & strSmartContract, const string & strPartyName, const int nCurrentAccount);
extern OT_COMMAND_OT bool stat_partyaccounts(const string & strSmartContract, const string & strPartyName, const int nDepth);
extern OT_COMMAND_OT bool stat_partyagent(const string & strSmartContract, const string & strPartyName, const string & strAgentName, const int nIndex);
extern OT_COMMAND_OT bool stat_partyagent_index(const string & strSmartContract, const string & strPartyName, const int nCurrentAgent);
extern OT_COMMAND_OT bool stat_partyagents(const string & strSmartContract, const string & strPartyName, const int nDepth);
extern OT_COMMAND_OT int stat_servers();
extern OT_COMMAND_OT bool withdraw_and_send_cash(const string & strMyAcctID, string & strHisNymID, const string & strMemo, const string & strAmount);

#endif
