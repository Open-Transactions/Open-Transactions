#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(discard_incoming_payments_NoIndices)
{
	// calls details_discard_incoming

	ASSERT_FALSE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_NONE));
}

TEST_MOCK(discard_incoming_payments_OneIndices)
{
	// calls details_discard_incoming
	bool returnValue = false;

	EXPECT_MOCK_STR("", LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_STR(0, 1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	if (index >= 0)
	{
		returnValue = true;

		//FIX what if this one fails?
		EXPECT_MOCK_STR(0, 1, NumList_Count(INDICES_ONE));
		if (index < 0)
		{
			EXPECT_MOCK_RET(true, RecordPayment(SERVER_ID, NYM_ID, true, 0, false));
		}
		else
		{
			EXPECT_MOCK_STR(false, true, NumList_VerifyQuery(INDICES_ONE, "0"));

			//FIX the loop returns a random success status
			//        depending on whether this one fails the last time in the loop
			EXPECT_MOCK_STR(true, false, RecordPayment(SERVER_ID, NYM_ID, true, 0, false));
			if (index >= 0)
			{
				returnValue = false;
			}
		}
	}

	ASSERT_EQ(returnValue, me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_ONE));
}

TEST_MOCK(discard_incoming_payments_TwoIndices)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(2, NumList_Count(INDICES_TWO));

	//FIX note the complex interaction in otcommands.ot line 816
	//    we need many more unit tests
	EXPECT_MOCK_STR(false, true, NumList_VerifyQuery(INDICES_TWO,"0"));

	EXPECT_MOCK_STR(true, false, RecordPayment(SERVER_ID, NYM_ID, true, 0, false));

	ASSERT_MOCK_EQ(true, false, me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_TWO));
}
