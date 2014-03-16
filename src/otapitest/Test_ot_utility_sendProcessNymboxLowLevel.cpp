#include "stdafx.h"


TEST_MOCK(ot_utility_sendProcessNymboxLowLevel)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_STR(OT_ERROR, REQUEST_NUMBER, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_MOCK_EQ(OT_ERROR, REQUEST_NUMBER, me.ot_utility_sendProcessNymboxLowLevel(SERVER_ID, NYM_ID));
}


int OtMeExtra::ot_utility_sendProcessNymboxLowLevel(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility(); util.sendProcessNymboxLowLevel(\"%s\", \"%s\"); }", serverId, nymId);
	return execInt(code.Get());
}


void OtMeTest::EXPECT_ot_utility_sendProcessNymboxLowLevel(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_STR(OT_ERROR, REQUEST_NUMBER, processNymbox(serverId, nymId));
}
