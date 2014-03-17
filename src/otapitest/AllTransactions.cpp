#include "stdafx.hpp"


TEST_MULTI(activate_smart_contract)
{
	//FIX This one is called in OTAPI_Func itself? (otapi.ot line 365)
	//FIX what should happen if this function fails?
	EXPECT_CALL_RETURN(1, SmartContract_CountNumsNeeded(SMART_CONTRACT, AGENT_NAME));

	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, activateSmartContract(SERVER_ID, NYM_ID, SMART_CONTRACT));

	//FIX AGENT_NAME is never used?
	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.activate_smart_contract(SERVER_ID, NYM_ID, ACCOUNT_ID, AGENT_NAME, SMART_CONTRACT));
}

TEST_MULTI(cancel_payment_plan)
{
	//FIX what if this one fails?
	EXPECT_CALL_RETURN(ACCOUNT_ID, Instrmnt_GetRecipientAcctID(PAYMENT_PLAN));

	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, depositPaymentPlan(SERVER_ID, NYM_ID, PAYMENT_PLAN));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.cancel_payment_plan(SERVER_ID, NYM_ID, PAYMENT_PLAN));
}

TEST_MULTI(create_market_offer)
{
	//FIX what if this one fails?
	EXPECT_CALL_RETURN(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	//FIX what if this one fails?
	EXPECT_CALL_RETURN(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, issueMarketOffer(ACCOUNT_ID, ACCOUNT_TO_ID, 1, 2, 10, AMOUNT, false, "", 0));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.create_market_offer(ACCOUNT_ID, ACCOUNT_TO_ID, 1, 2, 10, AMOUNT, false, 0, "", 0));
}

TEST_MULTI(deposit_cheque)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, depositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, "Cheque"));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.deposit_cheque(SERVER_ID, NYM_ID, ACCOUNT_ID, "Cheque"));
}

TEST_MULTI(exchange_basket_currency)
{
	//FIX what if this one fails?
	EXPECT_CALL_RETURN(0, Basket_GetMemberCount(BASKET_DATA));

	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, exchangeBasket(SERVER_ID, NYM_ID, ASSET_ID, BASKET_DATA, false));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.exchange_basket_currency(SERVER_ID, NYM_ID, ASSET_ID, BASKET_DATA, ACCOUNT_ID, false));
}

TEST_MULTI(kill_market_offer)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, killMarketOffer(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.kill_market_offer(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));
}

TEST_MULTI(kill_payment_plan)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, killPaymentPlan(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.kill_payment_plan(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));
}

TEST_MULTI(pay_dividend)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, payDividend(SERVER_ID, NYM_ID, ACCOUNT_ID, ASSET_ID, "Memo", AMOUNT));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.pay_dividend(SERVER_ID, NYM_ID, ACCOUNT_ID, ASSET_ID, "Memo", AMOUNT));
}

TEST_MULTI(process_inbox)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, processInbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.process_inbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));
}

TEST_MULTI(send_transfer)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, notarizeTransfer(SERVER_ID, NYM_ID, ACCOUNT_ID, ACCOUNT_TO_ID, AMOUNT, "Note"));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.send_transfer(SERVER_ID, NYM_ID, ACCOUNT_ID, ACCOUNT_TO_ID, AMOUNT, "Note"));
}

TEST_MULTI(withdraw_cash)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, notarizeWithdrawal(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.withdraw_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));
}

TEST_MULTI(withdraw_voucher)
{
	EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, withdrawVoucher(SERVER_ID, NYM_ID, ACCOUNT_ID, NYM_TO_ID, "Memo", AMOUNT));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.withdraw_voucher(SERVER_ID, NYM_ID, ACCOUNT_ID, NYM_TO_ID, "Memo", AMOUNT));
}
