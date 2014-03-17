#include "stdafx.hpp"


TEST_MULTI(accept_from_paymentbox)
{
	int returnValue = OT_ERROR;
	EXPECT_MULTI_RETURN("", NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MULTI_RETURN("", SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MULTI_RETURN("", INBOX_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	if (index >= 0)
	{
		returnValue = OT_TRUE;

		//FIX what if this one fails?
		EXPECT_MULTI_RETURN(0, 1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));

		if (index >= 0)
		{
			//FIX what if this one fails?
			OtMeTest::EXPECT_handle_payment_index(mock, index, ACCOUNT_ID, 0, PAYMENT_TYPE_CHEQUE, INBOX_DATA);
		}
	}

	//FIX other indices and payment types
	ASSERT_EQ(returnValue, me.accept_from_paymentbox(ACCOUNT_ID, INDICES_NONE, PAYMENT_TYPE_CHEQUE));
}


void OtMeTest::EXPECT_accept_from_paymentbox_HasNonEmptyLedger(Mock_OTAPI_Exec & mock, int & index, const char * accountId, const char * indices, const char * paymentType)
{
	EXPECT_MULTI_RETURN("", NYM_ID, GetAccountWallet_NymID(accountId));

	if (index >= 0)
	{
		EXPECT_CALL_RETURN(SERVER_ID, GetAccountWallet_ServerID(accountId));

		EXPECT_CALL_RETURN(INBOX_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

		EXPECT_CALL_RETURN(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));
	}
}
