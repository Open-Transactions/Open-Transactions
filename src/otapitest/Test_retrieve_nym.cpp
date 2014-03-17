#include "stdafx.hpp"


TEST_MULTI(retrieve_nym)
{
    OtMeTest::EXPECT_ot_utility_getRequestNumber(mock, index, SERVER_ID, NYM_ID);

    if (index >= 0)
    {
        OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, index, SERVER_ID, NYM_ID, false);
    }

	// defaults to forced version
	ASSERT_MULTI_EQ(false, true, me.retrieve_nym(SERVER_ID, NYM_ID));
}

void OtMeTest::EXPECT_retrieve_nym(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
    EXPECT_ot_utility_getRequestNumber(mock, noAltPathways, SERVER_ID, NYM_ID);
    EXPECT_ot_utility_getAndProcessNymbox_4(mock, index, SERVER_ID, NYM_ID, false);
}
