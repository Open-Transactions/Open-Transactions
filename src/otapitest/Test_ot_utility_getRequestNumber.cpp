#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(getRequestNumber)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_STR(OT_ERROR, REQUEST_NUMBER, getRequest(SERVER_ID, NYM_ID));

	OtMeTest::EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, SERVER_ID, NYM_ID, REQUEST_NUMBER, __FUNCTION__);

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.ot_utility_getRequestNumber(SERVER_ID, NYM_ID));
}


int OtMeExtra::ot_utility_getRequestNumber(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility(); util.getRequestNumber(\"%s\", \"%s\"); }", serverId, nymId);
	return execInt(code.Get());
}


void OtMeTest::EXPECT_ot_utility_getRequestNumber(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(REQUEST_NUMBER, getRequest(serverId, nymId));

	EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, serverId, nymId, REQUEST_NUMBER, "Utility::getNymboxLowLevel");
}
