#include "stdafx.hpp"


TEST_MOCK(ot_utility_getTransactionNumLowLevel)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_STR(OT_ERROR, REQUEST_NUMBER, getTransactionNumber(SERVER_ID, NYM_ID));

	OtMeTest::EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, SERVER_ID, NYM_ID, REQUEST_NUMBER, "getTransactionNum");

	ASSERT_MOCK_EQ(OT_ERROR, REQUEST_NUMBER, me.ot_utility_getTransactionNumLowLevel(SERVER_ID, NYM_ID));
}


int OtMeChai::ot_utility_getTransactionNumLowLevel(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility(); var bWasSent = OTBool(false);"
                "  util.getTransactionNumLowLevel(\"%s\", \"%s\", bWasSent); }",
                serverId, nymId);
	return execInt(code.Get());
}


int OtMeExtra::ot_utility_getTransactionNumLowLevel(const char * serverId, const char * nymId)
{
    Utility util;
    bool bWasSent = false;
    return util.getTransactionNumLowLevel(serverId, nymId, bWasSent);
}


void OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(REQUEST_NUMBER, getTransactionNumber(serverId, nymId));

	EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, serverId, nymId, REQUEST_NUMBER, "getTransactionNum");
}
