#include "stdafx.h"


TEST_MOCK(ot_utility_getBoxReceiptWithErrorCorrection)
{
    bool returnValue = true;

    int invertPathways = INVERT_MOCK;
    OtMeTest::EXPECT_ot_utility_getBoxReceiptLowLevel(mock, invertPathways, SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER);

    if (index >= 0)
    {
        returnValue = false;
        OtMeTest::EXPECT_ot_utility_getRequestNumber(mock, index, SERVER_ID, NYM_ID);

        if (index >= 0)
        {
            OtMeTest::EXPECT_ot_utility_getBoxReceiptLowLevel(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER);
            if (index >= 0)
            {
                returnValue = true;
            }
        }
    }

    ASSERT_EQ(returnValue, me.ot_utility_getBoxReceiptWithErrorCorrection(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER));
}


bool OtMeExtra::ot_utility_getBoxReceiptWithErrorCorrection(const char * serverId, const char * nymId, const char * accountId, const int boxType, const int64_t transactionNumber)
{
	OTString code;
    code.Format("{ var util = Utility(); util.getBoxReceiptWithErrorCorrection(\"%s\", \"%s\", \"%s\", %d, int64_t(%lld)); }", serverId, nymId, accountId, boxType, transactionNumber);
	return execBool(code.Get());
}


void OtMeTest::EXPECT_ot_utility_getBoxReceiptWithErrorCorrection(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * accountId, const int boxType, const int64_t transactionNumber)
{
    int errorPathway = 0;
    EXPECT_ot_utility_getBoxReceiptLowLevel(mock, errorPathway, SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER);

    EXPECT_ot_utility_getRequestNumber(mock, noAltPathways, SERVER_ID, NYM_ID);

    EXPECT_ot_utility_getBoxReceiptLowLevel(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER);
}
