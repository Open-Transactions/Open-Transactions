#include "stdafx.hpp"


TEST_MOCK(ot_utility_receiveReplySuccessLowLevel)
{
	OtMeTest::EXPECT_ot_utility_ReceiveReplyLowLevel(mock, index, SERVER_ID, NYM_ID, REQUEST_NUMBER, __FUNCTION__);

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.ot_utility_receiveReplySuccessLowLevel(SERVER_ID, NYM_ID, REQUEST_NUMBER, __FUNCTION__));
}


int OtMeChai::ot_utility_receiveReplySuccessLowLevel(const char * serverId, const char * nymId, int reqNr, const char * function)
{
	OTString code;
	code.Format("{ var util = Utility(); util.receiveReplySuccessLowLevel(\"%s\", \"%s\", %d, \"%s\"); }",
                serverId, nymId, reqNr, function);
	return execInt(code.Get());
}


int OtMeExtra::ot_utility_receiveReplySuccessLowLevel(const char * serverId, const char * nymId, int reqNr, const char * function)
{
    Utility util;
    return util.receiveReplySuccessLowLevel(serverId, nymId, reqNr, function);
}


void OtMeTest::EXPECT_ot_utility_receiveReplySuccessLowLevel(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, int reqNr, const char * function)
{
	if (index >= 0)
	{
		EXPECT_ot_utility_ReceiveReplyLowLevel(mock, noAltPathways, serverId, nymId, REQUEST_NUMBER, function);

		EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));
	}
}
