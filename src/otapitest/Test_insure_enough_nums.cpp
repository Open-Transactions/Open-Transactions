#include "stdafx.h"
#include "OtMeTest.hpp"

#ifdef NOT_READY_YET

TEST_MOCK(insure_enough_nums)
{
	int returnValue = true;

	EXPECT_MOCK_STR(2, 1, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	if (index >= 0)
	{
		returnValue = false;

		OtMeTest::EXPECT_ot_utility_getTransactionNumbers(mock, index, SERVER_ID, NYM_ID);

		if (index >= 0)
		{
			//// getNymbox
//			OtMeTest::EXPECT_getNymBox(mock, noAltPathways, true);

			//OtMeTest::EXPECT_insureHaveAllBoxReceipts(mock, noAltPathways);

			//EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

			//EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

			//EXPECT_MOCK(FlushMessageBuffer());

			//EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

			//EXPECT_MOCK(FlushMessageBuffer());

			//EXPECT_MOCK_RET(REQUEST_NUMBER, getRequest(SERVER_ID, NYM_ID));

			//EXPECT_MOCK(Sleep(50));

			//EXPECT_MOCK_RET(MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, NYM_ID));

			//EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

			//EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));

			//EXPECT_MOCK_RET(NYM_HASH, GetNym_NymboxHash(SERVER_ID, NYM_ID));

			//EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

			//EXPECT_MOCK_RET(true, VerifySignature(NYM_ID, LEDGER_DATA));

			//EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

			//EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

			//EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

			//EXPECT_MOCK(FlushMessageBuffer());

			//EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

			//EXPECT_MOCK_RET(2, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

			returnValue = true;
		}
	}

	ASSERT_EQ(returnValue, me.make_sure_enough_trans_nums(2, SERVER_ID, NYM_ID));
}

#endif
