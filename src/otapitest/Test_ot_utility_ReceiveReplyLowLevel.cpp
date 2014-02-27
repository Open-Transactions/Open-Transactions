#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(ot_utility_ReceiveReplyLowLevel)
{
	EXPECT_MOCK(Sleep(50));

	EXPECT_MOCK_STR("", MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, NYM_ID));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.ot_utility_ReceiveReplyLowLevel(SERVER_ID, NYM_ID, REQUEST_NUMBER, __FUNCTION__));
}


string OtMeExtra::ot_utility_ReceiveReplyLowLevel(const char * serverId, const char * nymId, int reqNr, const char * function)
{
	OTString code;
	code.Format("{ var util = Utility(); util.ReceiveReplyLowLevel(\"%s\", \"%s\", %d, \"%s\"); }", serverId, nymId, reqNr, function);
	return execStr(code.Get());
}


void OtMeTest::EXPECT_ot_utility_ReceiveReplyLowLevel(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, int reqNr, const char * function)
{
	if (index >= 0)
	{
		EXPECT_MOCK(Sleep(50));

		EXPECT_MOCK_STR("", MESSAGE_DATA, PopMessageBuffer(reqNr, serverId, nymId));
	}
}
