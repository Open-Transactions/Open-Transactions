#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_F(OtMeTest, retrieve_account_DefaultUnforced)
{
	EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	// defaults to unforced version
	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID));
}


TEST_F(OtMeTest, retrieve_account_Forced)
{
	EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, true);

	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, true));
}


TEST_F(OtMeTest, retrieve_account_Unforced)
{
	EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, false));
}
