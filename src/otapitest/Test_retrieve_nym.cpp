#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_F(OtMeTest, retrieve_nym_DefaultForced)
{
	EXPECT_REQUEST(MESSAGE_DATA, getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(mock, index, true);

	EXPECT_insureHaveAllBoxReceipts(mock, index);

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

	EXPECT_getNymBox(mock, index, true);

	EXPECT_insureHaveAllBoxReceipts(mock, index);

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID, true));
}


TEST_F(OtMeTest, retrieve_nym_Unforced)
{
	EXPECT_REQUEST(MESSAGE_DATA, getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(mock, index, false);

	EXPECT_insureHaveAllBoxReceipts(mock, index);

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID, false));
}
