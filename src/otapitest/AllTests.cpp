#include "stdafx.h"

#include "OtMeTest.hpp"


#ifdef ALLTESTS


// *** make_sure_enough_trans_nums

TEST_F(OtMeTest, make_sure_enough_trans_nums)
{
	EXPECT_MOCK_RET(1, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.make_sure_enough_trans_nums(1, SERVER_ID, NYM_ID));
}


TEST_F(OtMeTest, make_sure_enough_trans_nums_HasToGetMore)
{
	EXPECT_MOCK_RET(1, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	EXPECT_REQUEST(MESSAGE_DATA, getTransactionNumber(SERVER_ID, NYM_ID));

	// getNymbox
	EXPECT_getNymBox(true);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(REQUEST_NUMBER, getRequest(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(NYM_HASH, GetNym_NymboxHash(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(true, VerifySignature(NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(2, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.make_sure_enough_trans_nums(2, SERVER_ID, NYM_ID));
}


// *** create_pseudonym

TEST_F(OtMeTest, create_pseudonym)
{
	EXPECT_MOCK_RET(NYM_ID, CreateNym(2048, "NymSource", ""));

	ASSERT_EQ(NYM_ID, me.create_pseudonym(2048, "NymSource", ""));
}


// *** load_or_retrieve_contract

TEST_F(OtMeTest, load_or_retrieve_contract)
{
	EXPECT_MOCK_RET(MESSAGE_DATA, LoadAssetContract(CONTRACT_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID));
}


TEST_F(OtMeTest, load_or_retrieve_contract_MustRetrieeve)
{
	EXPECT_MOCK_RET("", LoadAssetContract(CONTRACT_ID));

	EXPECT_REQUEST(MESSAGE_DATA, getContract(SERVER_ID, NYM_ID, CONTRACT_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadAssetContract(CONTRACT_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID));
}


// *** stat_asset_account

TEST_F(OtMeTest, stat_asset_account)
{
	//NOTE: Not important whether the retrieval functions will fail
	//      The resulting empty strings are simply returned, too
	EXPECT_MOCK_RET(WALLET_NAME, GetAccountWallet_Name(ACCOUNT_ID));

	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(AMOUNT, GetAccountWallet_Balance(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_NAME, GetAssetType_Name(ASSET_ID));

	EXPECT_MOCK_RET(NYM_NAME, GetNym_Name(NYM_ID));

	EXPECT_MOCK_RET(SERVER_NAME, GetServer_Name(SERVER_ID));

	EXPECT_MOCK_RET("$12.34", FormatAmount(ASSET_ID, AMOUNT));

	std::string msgData = "   Balance: $12.34   (";
	msgData = msgData + WALLET_NAME + ")\n"
		"Account ID: " + ACCOUNT_ID + " ( " + WALLET_NAME + " )\n"
		"Asset Type: " + ASSET_ID + " ( " + ASSET_NAME + " )\n"
		"Owner Nym:  " + NYM_ID + " ( " + NYM_NAME + " )\n"
		"Server:     " + SERVER_ID + " ( " + SERVER_NAME + " )";
	ASSERT_EQ(msgData, me.stat_asset_account(ACCOUNT_ID));
}


// *** retrieve_account

TEST_F(OtMeTest, retrieve_account_DefaultUnforced)
{
	EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	// defaults to unforced version
	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID));
}


TEST_F(OtMeTest, retrieve_account_Forced)
{
	EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_ID, ACCOUNT_ID, true);

	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, true));
}


TEST_F(OtMeTest, retrieve_account_Unforced)
{
	EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, false));
}


// *** retrieve_nym

TEST_F(OtMeTest, retrieve_nym_DefaultForced)
{
	EXPECT_REQUEST(MESSAGE_DATA, getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(true);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	// defaults to forced version
	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID));
}


TEST_F(OtMeTest, retrieve_nym_Forced)
{
	EXPECT_REQUEST(MESSAGE_DATA, getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(true);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID, true));
}


TEST_F(OtMeTest, retrieve_nym_Unforced)
{
	EXPECT_REQUEST(MESSAGE_DATA, getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(false);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID, false));
}


// *** discard_incoming_payments

TEST_F(OtMeTest, discard_incoming_payments_Fail_NoIndices)
{
	ASSERT_FALSE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_NONE));
}


TEST_F(OtMeTest, discard_incoming_payments_Fail_EmptyLedger)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	ASSERT_FALSE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_ONE));
}


TEST_F(OtMeTest, discard_incoming_payments_HasOneIndices)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(1, NumList_Count(INDICES_ONE));

	EXPECT_MOCK_RET(true, NumList_VerifyQuery(INDICES_ONE, "0"));

	EXPECT_MOCK_RET(true, RecordPayment(SERVER_ID, NYM_ID, true, 0, false));

	ASSERT_TRUE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_ONE));
}


TEST_F(OtMeTest, discard_incoming_payments_HasTwoIndices)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(2, NumList_Count(INDICES_TWO));

	//FIX note the complex interaction in otcommands.ot line 816
	//    we need many more unit tests
	EXPECT_MOCK_RET(true, NumList_VerifyQuery(INDICES_TWO,"0"));

	EXPECT_MOCK_RET(true, RecordPayment(SERVER_ID, NYM_ID, true, 0, false));

	ASSERT_TRUE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_TWO));
}


// *** cancel_outgoing_payments

TEST_F(OtMeTest, cancel_outgoing_payments_Fail_OutboxEmpty)
{
	EXPECT_MOCK_RET(0, NumList_Count(INDICES_NONE));

	EXPECT_MOCK_RET(0, GetNym_OutpaymentsCount(NYM_ID));

	ASSERT_FALSE(me.cancel_outgoing_payments(NYM_ID, ACCOUNT_ID, INDICES_NONE));
}


TEST_F(OtMeTest, cancel_outgoing_payments_HasPaymentInOutbox)
{
	EXPECT_MOCK_RET(0, NumList_Count(INDICES_NONE));

	EXPECT_MOCK_RET(1, GetNym_OutpaymentsCount(NYM_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetNym_OutpaymentsServerIDByIndex(NYM_ID, 0));

	EXPECT_MOCK_RET(PAYMENT_DATA, GetNym_OutpaymentsContentsByIndex(NYM_ID, 0));

	//FIX definitely tinker with these
	EXPECT_MOCK_RET(PAYMENT_TYPE_CHEQUE, Instrmnt_GetType(PAYMENT_DATA));

	EXPECT_MOCK_RET(ACCOUNT_ID, Instrmnt_GetSenderAcctID(PAYMENT_DATA));

	EXPECT_MOCK_RET(NYM_ID, Instrmnt_GetSenderUserID(PAYMENT_DATA));

	EXPECT_detailsDepositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, PAYMENT_DATA);

	//FIX highlight the fact that ACCOUNT_ID is not used by using ACCOUNT_FROM_ID
	ASSERT_TRUE(me.cancel_outgoing_payments(NYM_ID, ACCOUNT_FROM_ID, INDICES_NONE));
}


// *** accept_from_paymentbox

TEST_F(OtMeTest, accept_from_paymentbox_HasEmptyLedger)
{
	const int LEDGER_COUNT = 0;

	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_COUNT, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	ASSERT_EQ(OT_TRUE, me.accept_from_paymentbox(ACCOUNT_ID, INDICES_NONE, PAYMENT_TYPE_CHEQUE));
}


TEST_F(OtMeTest, accept_from_paymentbox_HasNonEmptyLedger)
{
	//FIX definitely tinker with these
	const int LEDGER_COUNT = 1;

	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_COUNT, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	// handle_payment_index
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(LEDGER_COUNT, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA, 0));

	//FIX definitely tinker with these
	EXPECT_MOCK_RET(PAYMENT_TYPE_CHEQUE, Instrmnt_GetType(INSTRUMENT_DATA));

	EXPECT_MOCK_RET(NYM_ID, Instrmnt_GetRecipientUserID(INSTRUMENT_DATA));

	EXPECT_MOCK_RET(ASSET_ID, Instrmnt_GetAssetID(INSTRUMENT_DATA));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	//FIX definitely tinker with these
	EXPECT_MOCK_RET(GetTime() - 864000000L, Instrmnt_GetValidFrom(INSTRUMENT_DATA)); // 10 days ago

	EXPECT_MOCK_RET(GetTime() + 864000000L, Instrmnt_GetValidTo(INSTRUMENT_DATA)); // 10 days ahead

	EXPECT_detailsDepositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, INSTRUMENT_DATA);

	ASSERT_EQ(OT_TRUE, me.accept_from_paymentbox(ACCOUNT_ID, INDICES_NONE, PAYMENT_TYPE_CHEQUE));
}


// *** load_public_encryption_key

TEST_F(OtMeTest, load_public_encryption_key_Pubkey)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_encryption_key(NYM_ID));
}


TEST_F(OtMeTest, load_public_encryption_key_UserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Encryption(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_encryption_key(NYM_ID));
}


// *** load_public_signing_key

TEST_F(OtMeTest, load_public_signing_key_Pubkey)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Signing(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_signing_key(NYM_ID));
}

TEST_F(OtMeTest, load_public_signing_key_UserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Signing(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_signing_key(NYM_ID));
}


// *** withdraw_and_send_cash

TEST_F(OtMeTest, withdraw_and_send_cash_Fail_HasEmptyPurseEvenAfterCashWithdrawal)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	//FIX can do different things here
	EXPECT_MOCK_RET(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_detailsWithdrawCash(ACCOUNT_ID, AMOUNT);

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	EXPECT_MOCK_RET(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET("$12.34", FormatAmount(ASSET_ID, AMOUNT));

	ASSERT_FALSE(me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}


TEST_F(OtMeTest, withdraw_and_send_cash_HasEmptyPurseDoesCashWithdrawal)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	//FIX can do different things here
	EXPECT_MOCK_RET(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_detailsWithdrawCash(ACCOUNT_ID, AMOUNT);

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	// note: we're trying to withdraw tokens totalling to the EXACT amount
	EXPECT_MOCK_RET(AMOUNT, Token_GetDenomination(SERVER_ID, ASSET_ID, TOKEN_DATA)); // instead of TOKEN_VALUE

	EXPECT_MOCK_RET(TOKEN_SERIES, Token_GetSeries(SERVER_ID, ASSET_ID, TOKEN_DATA));

	EXPECT_MOCK_RET(GetTime() - 864000000L, Token_GetValidFrom(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days ago

	EXPECT_MOCK_RET(GetTime() + 864000000L, Token_GetValidTo(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days aheas

	EXPECT_MOCK_RET("0", NumList_Add("", "0"));

	EXPECT_detailsExportCash(SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, "0", false);

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(MESSAGE_DATA, sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, PURSE_DATA_TO, PURSE_DATA_FROM));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	//FIX interesting extra call path here

	ASSERT_TRUE(me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}


// *** get_payment_instrument

TEST_F(OtMeTest, get_payment_instrument_DefaultPreloadedInboxNone)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA, 0));

	// defaults PRELOADED_INDEX to ""
	ASSERT_EQ(INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0));
}

TEST_F(OtMeTest, get_payment_instrument_PreloadedInboxNone)
{
	EXPECT_MOCK_RET(INBOX_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA, 0));

	ASSERT_EQ(INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0, ""));
}

TEST_F(OtMeTest, get_payment_instrument)
{
	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA, 0));

	ASSERT_EQ(INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0, INBOX_DATA));
}


// *** load_or_retrieve_mint

TEST_F(OtMeTest, load_or_retrieve_mint_Load)
{
	EXPECT_MOCK_RET(true, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}


TEST_F(OtMeTest, Lload_or_retrieve_mint_Retrieve)
{
	EXPECT_MOCK_RET(false, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_REQUEST(MESSAGE_DATA, getMint(SERVER_ID, NYM_ID, ASSET_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(true, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}


// *** easy_withdraw_cash

TEST_F(OtMeTest, easy_withdraw_cash)
{
	EXPECT_detailsWithdrawCash(ACCOUNT_ID, AMOUNT);

	ASSERT_EQ(1, me.easy_withdraw_cash(ACCOUNT_ID, AMOUNT));
}


// *** export_cash

TEST_F(OtMeTest, export_cash)
{
	EXPECT_detailsExportCash(SERVER_ID, NYM_FROM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false);

	std::string retainedCopy;
	ASSERT_EQ(PURSE_DATA_TO, me.export_cash(SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false, retainedCopy));
	ASSERT_EQ(PURSE_DATA_FROM, retainedCopy);
}

#endif // ALLTESTS
