#include "stdafx.h"


TEST_MOCK(details_refresh_nym)
{
    OtMeTest::EXPECT_retrieve_nym(mock, index, SERVER_ID, NYM_ID);

    ASSERT_MOCK_EQ(false, true, me.details_refresh_nym(SERVER_ID, NYM_ID, true));
}


bool OtMeExtra::details_refresh_nym(const char * serverId, const char * nymId, const bool bForceDownload)
{
    OTString code;
    code.Format("{ details_refresh_nym(\"%s\", \"%s\", %s); }", serverId, nymId, boolStr(bForceDownload));
    return execBool(code.Get());
}


void OtMeTest::EXPECT_details_refresh_nym(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const bool bForceDownload)
{
    EXPECT_retrieve_nym(mock, index, serverId, nymId);
}