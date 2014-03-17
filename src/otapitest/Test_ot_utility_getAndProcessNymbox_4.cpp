#include "stdafx.hpp"


TEST_MOCK(ot_utility_getAndProcessNymbox_4)
{
	OtMeTest::EXPECT_ot_utility_getNymbox(mock, index, SERVER_ID, NYM_ID, false);

	if (index >= 0)
	{
        OtMeTest::EXPECT_ot_utility_insureHaveAllBoxReceipts(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, 0);

        if (index >= 0)
        {
            //FIX what if this one fails?
            EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

            //FIX what if this one fails? VOID function, but can fail!
            EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

            OtMeTest::EXPECT_ot_utility_processNymbox(mock, index, SERVER_ID, NYM_ID);

            //FIX figure out how to get into the rest of the alternative pathways
        }
	}

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.ot_utility_getAndProcessNymbox_4(SERVER_ID, NYM_ID, false));
}


int OtMeChai::ot_utility_getAndProcessNymbox_4(const char * serverId, const char * nymId, bool bForceDownload)
{
    OTString code;
    code.Format("{ var util = Utility(); var bWasSent = OTBool(false);"
                "  util.getAndProcessNymbox_4(\"%s\", \"%s\", bWasSent, %s); }",
                serverId, nymId, boolStr(bForceDownload));
    return execInt(code.Get());
}


int OtMeExtra::ot_utility_getAndProcessNymbox_4(const char * serverId, const char * nymId, bool bForceDownload)
{
    Utility util;
    bool bWasSent = false;
    return util.getAndProcessNymbox_4(serverId, nymId, bWasSent, bForceDownload);
}


void OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, bool bForceDownload)
{
	OtMeTest::EXPECT_ot_utility_getNymbox(mock, noAltPathways, SERVER_ID, NYM_ID, false);

    OtMeTest::EXPECT_ot_utility_insureHaveAllBoxReceipts(mock, noAltPathways, SERVER_ID, NYM_ID, ACCOUNT_ID, 0);

	//FIX what if this one fails?
	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	//FIX what if this one fails? VOID function, but can fail!
	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	OtMeTest::EXPECT_ot_utility_processNymbox(mock, index, SERVER_ID, NYM_ID);
}
