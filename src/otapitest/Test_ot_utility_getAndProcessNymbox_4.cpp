#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(ot_utility_getAndProcessNymbox_4)
{
	OtMeTest::EXPECT_ot_utility_getNymbox(mock, index, SERVER_ID, NYM_ID, false);

	if (index >= 0)
	{
		OtMeTest::EXPECT_insureHaveAllBoxReceipts(mock, index);

		//FIX what if this one fails?
		EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

		//FIX what if this one fails? VOID function, but can fail!
		EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

		OtMeTest::EXPECT_ot_utility_processNymbox(mock, index, SERVER_ID, NYM_ID);
	}

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.ot_utility_getAndProcessNymbox_4(SERVER_ID, NYM_ID, false));
}


int OtMeExtra::ot_utility_getAndProcessNymbox_4(const char * serverId, const char * nymId, bool bForceDownload)
{
	OTString code;
	code.Format("{ var util = Utility(); var bWasMsgSent = OTBool(false); util.getAndProcessNymbox_4(\"%s\", \"%s\", bWasMsgSent, %s); }", serverId, nymId, boolStr(bForceDownload));
	return execInt(code.Get());
}


void OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, bool bForceDownload)
{
	OtMeTest::EXPECT_ot_utility_getNymbox(mock, noAltPathways, SERVER_ID, NYM_ID, false);

	OtMeTest::EXPECT_insureHaveAllBoxReceipts(mock, noAltPathways);

	//FIX what if this one fails?
	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	//FIX what if this one fails? VOID function, but can fail!
	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	OtMeTest::EXPECT_ot_utility_processNymbox(mock, index, SERVER_ID, NYM_ID);
}
