#include "stdafx.hpp"


TEST_MOCK(ot_utility_processNymbox)
{
	OtMeTest::EXPECT_ot_utility_sendProcessNymboxLowLevel(mock, index, SERVER_ID, NYM_ID);

	OtMeTest::EXPECT_ot_utility_ReceiveReplyLowLevel(mock, index, SERVER_ID, NYM_ID, REQUEST_NUMBER, "processNymbox / sendProcessNymboxLowLevel / ReceiveReplyLowLevel");

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	if (index >= 0)
	{
		EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, NYM_ID, MESSAGE_DATA));

		if (index >= 0)
		{
			EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, NYM_ID, MESSAGE_DATA));
		}
	}

	ASSERT_MOCK_EQ(OT_ERROR, REQUEST_NUMBER, me.ot_utility_processNymbox(SERVER_ID, NYM_ID));
}


int OtMeChai::ot_utility_processNymbox(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility();"
		        "  var bWasSent = OTBool(false);"
		        "  var nRequestNumOut = OTInteger(-1);"
		        "  var nReplySuccessOut = OTInteger(-1);"
		        "  var nBalanceSuccessOut = OTInteger(-1);"
		        "  var nTransSuccessOut = OTInteger(-1);"
		        "  util.processNymbox(\"%s\", \"%s\", bWasSent, nRequestNumOut,"
		        " nReplySuccessOut, nBalanceSuccessOut, nTransSuccessOut); }",
		        serverId, nymId);
	return execInt(code.Get());
}


int OtMeExtra::ot_utility_processNymbox(const char * serverId, const char * nymId)
{
    Utility util;
    bool bWasSent = false;
    int nRequestNumOut = -1;
    int nReplySuccessOut = -1;
    int nBalanceSuccessOut = -1;
    int nTransSuccessOut = -1;
    return util.processNymbox(serverId, nymId, bWasSent, nRequestNumOut, nReplySuccessOut, nBalanceSuccessOut, nTransSuccessOut);
}


void OtMeTest::EXPECT_ot_utility_processNymbox(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	OtMeTest::EXPECT_ot_utility_sendProcessNymboxLowLevel(mock, noAltPathways, SERVER_ID, NYM_ID);

	OtMeTest::EXPECT_ot_utility_ReceiveReplyLowLevel(mock, noAltPathways, SERVER_ID, NYM_ID, REQUEST_NUMBER, "processNymbox / sendProcessNymboxLowLevel / ReceiveReplyLowLevel");

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, NYM_ID, MESSAGE_DATA));

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, NYM_ID, MESSAGE_DATA));
}
