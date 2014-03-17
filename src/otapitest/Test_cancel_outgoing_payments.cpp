#include "stdafx.hpp"


TEST_MULTI(cancel_outgoing_payments)
{
	bool returnValue = false;
	//FIX what if this one fails?
	EXPECT_CALL_RETURN(0, NumList_Count(INDICES_NONE));

	//FIX what if this one fails?
	EXPECT_MULTI_RETURN(0, 1, GetNym_OutpaymentsCount(NYM_ID));

	if (index >= 0)
	{
		returnValue = true;
		//FIX won't bomb out when fail?
		EXPECT_MULTI_RETURN("", SERVER_ID, GetNym_OutpaymentsServerIDByIndex(NYM_ID, 0));

		EXPECT_MULTI_RETURN("", PAYMENT_DATA, GetNym_OutpaymentsContentsByIndex(NYM_ID, 0));

		if (index >= 0)
		{
			//FIX none of the failure paths here bomb out
			EXPECT_CALL_RETURN(PAYMENT_TYPE_CHEQUE, Instrmnt_GetType(PAYMENT_DATA));

			EXPECT_CALL_RETURN(ACCOUNT_ID, Instrmnt_GetSenderAcctID(PAYMENT_DATA));

			EXPECT_CALL_RETURN(NYM_ID, Instrmnt_GetSenderUserID(PAYMENT_DATA));

			OtMeTest::EXPECT_details_deposit_cheque(mock, index, SERVER_ID, ACCOUNT_ID, NYM_ID, PAYMENT_DATA, PAYMENT_TYPE_CHEQUE);
		}
	}

	ASSERT_EQ(returnValue, me.cancel_outgoing_payments(NYM_ID, ACCOUNT_ID, INDICES_NONE));
}
