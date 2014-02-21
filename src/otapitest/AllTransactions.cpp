#include "stdafx.h"

#include "OtMeTest.hpp"

//#define ALLTESTS

#ifdef ALLTESTS

TEST_MOCK(activate_smart_contract)
{
	//FIX This one is called in OTAPI_Func itself? (otapi.ot line 365)
	//FIX what should happen if this function fails?
	EXPECT_MOCK_RET(1, SmartContract_CountNumsNeeded(SMART_CONTRACT, AGENT_NAME));

	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, activateSmartContract(SERVER_ID, NYM_ID, SMART_CONTRACT));

	//FIX AGENT_NAME is never used?
	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.activate_smart_contract(SERVER_ID, NYM_ID, ACCOUNT_ID, AGENT_NAME, SMART_CONTRACT));
}

TEST_MOCK(cancel_payment_plan)
{
	//FIX what if this one fails?
	EXPECT_MOCK_RET(ACCOUNT_ID, Instrmnt_GetRecipientAcctID(PAYMENT_PLAN));

	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, depositPaymentPlan(SERVER_ID, NYM_ID, PAYMENT_PLAN));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.cancel_payment_plan(SERVER_ID, NYM_ID, PAYMENT_PLAN));
}

TEST_MOCK(create_market_offer)
{
	//FIX what if this one fails?
	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	//FIX what if this one fails?
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, issueMarketOffer(ACCOUNT_ID, ACCOUNT_TO_ID, 1, 2, 10, AMOUNT, false, "", 0));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.create_market_offer(ACCOUNT_ID, ACCOUNT_TO_ID, 1, 2, 10, AMOUNT, false, 0, "", 0));
}

TEST_MOCK(deposit_cheque)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, depositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, "Cheque"));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.deposit_cheque(SERVER_ID, NYM_ID, ACCOUNT_ID, "Cheque"));
}

TEST_MOCK(exchange_basket_currency)
{
	//FIX what if this one fails?
	EXPECT_MOCK_RET(0, Basket_GetMemberCount(BASKET_DATA));

	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, exchangeBasket(SERVER_ID, NYM_ID, ASSET_ID, BASKET_DATA, false));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.exchange_basket_currency(SERVER_ID, NYM_ID, ASSET_ID, BASKET_DATA, ACCOUNT_ID, false));
}

TEST_MOCK(kill_market_offer)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, killMarketOffer(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.kill_market_offer(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));
}

TEST_MOCK(kill_payment_plan)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, killPaymentPlan(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.kill_payment_plan(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));
}

TEST_MOCK(pay_dividend)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, payDividend(SERVER_ID, NYM_ID, ACCOUNT_ID, ASSET_ID, "Memo", AMOUNT));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.pay_dividend(SERVER_ID, NYM_ID, ACCOUNT_ID, ASSET_ID, "Memo", AMOUNT));
}

TEST_MOCK(process_inbox)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, processInbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.process_inbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));
}

TEST_MOCK(send_transfer)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, notarizeTransfer(SERVER_ID, NYM_ID, ACCOUNT_ID, ACCOUNT_TO_ID, AMOUNT, "Note"));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.send_transfer(SERVER_ID, NYM_ID, ACCOUNT_ID, ACCOUNT_TO_ID, AMOUNT, "Note"));
}

TEST_MOCK(withdraw_cash)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, notarizeWithdrawal(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.withdraw_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));
}

TEST_MOCK(withdraw_voucher)
{
	EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, withdrawVoucher(SERVER_ID, NYM_ID, ACCOUNT_ID, NYM_TO_ID, "Memo", AMOUNT));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.withdraw_voucher(SERVER_ID, NYM_ID, ACCOUNT_ID, NYM_TO_ID, "Memo", AMOUNT));
}

#endif // ALLTESTS

