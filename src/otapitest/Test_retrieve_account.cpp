#include "stdafx.hpp"


TEST_MOCK(retrieve_account_DefaultUnforced)
{
	OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	// defaults to unforced version
	ASSERT_MOCK_EQ(false, true, me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID));
}


TEST_MOCK(retrieve_account_Forced)
{
    OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, true);

    ASSERT_MOCK_EQ(false, true, me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, true));
}


TEST_MOCK(retrieve_account_Unforced)
{
    OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

    ASSERT_MOCK_EQ(false, true, me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, false));
}
