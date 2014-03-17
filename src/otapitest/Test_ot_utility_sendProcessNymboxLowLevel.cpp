#include "stdafx.hpp"


TEST_MULTI(ot_utility_sendProcessNymboxLowLevel)
{
	EXPECT_CALL_VOID(FlushMessageBuffer());

	EXPECT_MULTI_RETURN(OT_ERROR, REQUEST_NUMBER, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_MULTI_EQ(OT_ERROR, REQUEST_NUMBER, me.ot_utility_sendProcessNymboxLowLevel(SERVER_ID, NYM_ID));
}


int OtMeChai::ot_utility_sendProcessNymboxLowLevel(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility(); util.sendProcessNymboxLowLevel(\"%s\", \"%s\"); }",
                serverId, nymId);
	return execInt(code.Get());
}


int OtMeExtra::ot_utility_sendProcessNymboxLowLevel(const char * serverId, const char * nymId)
{
    Utility util;
    return util.sendProcessNymboxLowLevel(serverId, nymId);
}


void OtMeTest::EXPECT_ot_utility_sendProcessNymboxLowLevel(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	EXPECT_CALL_VOID(FlushMessageBuffer());

	EXPECT_MULTI_RETURN(OT_ERROR, REQUEST_NUMBER, processNymbox(serverId, nymId));
}
