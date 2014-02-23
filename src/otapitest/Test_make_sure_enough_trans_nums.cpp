#include "stdafx.h"
#include "OtMeTest.hpp"


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
