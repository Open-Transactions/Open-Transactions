#include "stdafx.hpp"


TEST_MULTI(ot_utility_getRequestNumber)
{
	EXPECT_CALL_VOID(FlushMessageBuffer());

	EXPECT_MULTI_RETURN(OT_ERROR, REQUEST_NUMBER, getRequest(SERVER_ID, NYM_ID));

	OtMeTest::EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, SERVER_ID, NYM_ID, REQUEST_NUMBER, __FUNCTION__);

	ASSERT_MULTI_EQ(OT_ERROR, OT_TRUE, me.ot_utility_getRequestNumber(SERVER_ID, NYM_ID));
}


int OtMeChai::ot_utility_getRequestNumber(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility(); util.getRequestNumber(\"%s\", \"%s\"); }",
                serverId, nymId);
	return execInt(code.Get());
}


int OtMeExtra::ot_utility_getRequestNumber(const char * serverId, const char * nymId)
{
    Utility util;
    return util.getRequestNumber(serverId, nymId);
}


void OtMeTest::EXPECT_ot_utility_getRequestNumber(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	EXPECT_CALL_VOID(FlushMessageBuffer());

	EXPECT_CALL_RETURN(REQUEST_NUMBER, getRequest(serverId, nymId));

	EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, serverId, nymId, REQUEST_NUMBER, "Utility::getNymboxLowLevel");
}
