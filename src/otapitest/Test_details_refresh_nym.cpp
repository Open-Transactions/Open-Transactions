#include "stdafx.hpp"


TEST_MULTI(details_refresh_nym)
{
    OtMeTest::EXPECT_retrieve_nym(mock, index, SERVER_ID, NYM_ID);

    ASSERT_MULTI_EQ(false, true, me.details_refresh_nym(SERVER_ID, NYM_ID, true));
}


bool OtMeChai::details_refresh_nym(const char * serverId, const char * nymId, const bool bForceDownload)
{
    OTString code;
    code.Format("{ details_refresh_nym(\"%s\", \"%s\", %s); }",
                serverId, nymId, boolStr(bForceDownload));
    return execBool(code.Get());
}


bool OtMeExtra::details_refresh_nym(const char * serverId, const char * nymId, const bool bForceDownload)
{
    return ::details_refresh_nym(serverId, nymId, bForceDownload);
}


void OtMeTest::EXPECT_details_refresh_nym(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const bool bForceDownload)
{
    EXPECT_retrieve_nym(mock, index, serverId, nymId);
}