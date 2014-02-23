#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(cancel_outgoing_payments)
{
	bool returnValue = false;
	//FIX what if this one fails?
	EXPECT_MOCK_RET(0, NumList_Count(INDICES_NONE));

	//FIX what if this one fails?
	EXPECT_MOCK_STR(0, 1, GetNym_OutpaymentsCount(NYM_ID));

	if (index >= 0)
	{
		returnValue = true;
		//FIX won't bomb out when fail?
		EXPECT_MOCK_STR("", SERVER_ID, GetNym_OutpaymentsServerIDByIndex(NYM_ID, 0));

		EXPECT_MOCK_STR("", PAYMENT_DATA, GetNym_OutpaymentsContentsByIndex(NYM_ID, 0));

		if (index >= 0)
		{
			//FIX none of the failure paths here bomb out
			EXPECT_MOCK_RET(PAYMENT_TYPE_CHEQUE, Instrmnt_GetType(PAYMENT_DATA));

			EXPECT_MOCK_RET(ACCOUNT_ID, Instrmnt_GetSenderAcctID(PAYMENT_DATA));

			EXPECT_MOCK_RET(NYM_ID, Instrmnt_GetSenderUserID(PAYMENT_DATA));

			OtMeTest::EXPECT_details_deposit_cheque(mock, index, SERVER_ID, ACCOUNT_ID, NYM_ID, PAYMENT_DATA, PAYMENT_TYPE_CHEQUE);
		}
	}

	ASSERT_EQ(returnValue, me.cancel_outgoing_payments(NYM_ID, ACCOUNT_ID, INDICES_NONE));
}
