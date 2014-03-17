#include "stdafx.hpp"


TEST_MOCK(ot_utility_getNymbox_NoForceDownloadAlreadyHaveNymbox)
{
	EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));
	EXPECT_MOCK_RET(NYM_HASH, GetNym_NymboxHash(SERVER_ID, NYM_ID));

	ASSERT_EQ(OT_TRUE, me.ot_utility_getNymbox(SERVER_ID, NYM_ID, false));
}

TEST_MOCK(ot_utility_getNymbox_NoForceDownloadGetNymbox)
{
	int returnValue = REQUEST_NUMBER;

	// force non-matching nym hashes
	EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));
	EXPECT_MOCK_RET(NYM_HASH2, GetNym_NymboxHash(SERVER_ID, NYM_ID));

    int invertPathways = INVERT_MOCK;
    OtMeTest::EXPECT_ot_utility_getNymboxLowLevel(mock, invertPathways, SERVER_ID, NYM_ID);

	if (index >= 0)
	{
		returnValue = OT_ERROR;
		OtMeTest::EXPECT_ot_utility_getRequestNumber(mock, index, SERVER_ID, NYM_ID);
		if (index >= 0)
		{
			EXPECT_MOCK_RET(NYM_HASH, Message_GetNymboxHash(MESSAGE_DATA));
			EXPECT_MOCK_RET(NYM_HASH2, GetNym_NymboxHash(SERVER_ID, NYM_ID));
			OtMeTest::EXPECT_ot_utility_getNymboxLowLevel(mock, index, SERVER_ID, NYM_ID);
			if (index >= 0)
			{
				returnValue = REQUEST_NUMBER;
			}
		}
	}

	ASSERT_EQ(returnValue, me.ot_utility_getNymbox(SERVER_ID, NYM_ID, false));
}


int OtMeChai::ot_utility_getNymbox(const char * serverId, const char * nymId, bool bForceDownload)
{
	OTString code;
	code.Format("{ var util = Utility(); util.getNymbox(\"%s\", \"%s\", %s); }",
                serverId, nymId, boolStr(bForceDownload));
	return execInt(code.Get());
}


int OtMeExtra::ot_utility_getNymbox(const char * serverId, const char * nymId, bool bForceDownload)
{
    Utility util;
    return util.getNymbox(serverId, nymId, bForceDownload);
}


void OtMeTest::EXPECT_ot_utility_getNymbox(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, bool bForceDownload)
{
	// force non-matching nym hashes
	EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));
	EXPECT_MOCK_RET(NYM_HASH2, GetNym_NymboxHash(SERVER_ID, NYM_ID));

	int errorPathwayOnly = 0;
	OtMeTest::EXPECT_ot_utility_getNymboxLowLevel(mock, errorPathwayOnly, SERVER_ID, NYM_ID);

	EXPECT_ot_utility_getRequestNumber(mock, noAltPathways, SERVER_ID, NYM_ID);

	EXPECT_MOCK_RET(NYM_HASH, Message_GetNymboxHash(MESSAGE_DATA));
	EXPECT_MOCK_RET(NYM_HASH2, GetNym_NymboxHash(SERVER_ID, NYM_ID));

	EXPECT_ot_utility_getNymboxLowLevel(mock, index, SERVER_ID, NYM_ID);
}
