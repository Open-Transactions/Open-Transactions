#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(ot_utility_getNymboxLowLevel)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_STR(OT_ERROR, REQUEST_NUMBER, getNymbox(SERVER_ID, NYM_ID));

	OtMeTest::EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, SERVER_ID, NYM_ID, REQUEST_NUMBER, "Utility::getNymboxLowLevel");

	ASSERT_MOCK_EQ(OT_ERROR, REQUEST_NUMBER, me.ot_utility_getNymboxLowLevel(SERVER_ID, NYM_ID));
}


int OtMeExtra::ot_utility_getNymboxLowLevel(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility(); util.getNymboxLowLevel(\"%s\", \"%s\"); }", serverId, nymId);
	return execInt(code.Get());
}


void OtMeTest::EXPECT_ot_utility_getNymboxLowLevel(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(REQUEST_NUMBER, getNymbox(serverId, nymId));

	EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, serverId, nymId, REQUEST_NUMBER, "Utility::getNymboxLowLevel");
}
