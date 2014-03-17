#include "stdafx.hpp"


TEST_MULTI(ot_utility_getBoxReceiptLowLevel)
{
    EXPECT_CALL_VOID(FlushMessageBuffer());

    EXPECT_MULTI_RETURN(OT_ERROR, REQUEST_NUMBER, getBoxReceipt(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER));

    OtMeTest::EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, SERVER_ID, NYM_ID, REQUEST_NUMBER, "Utility::getBoxReceiptLowLevel");

    ASSERT_MULTI_EQ(false, true, me.ot_utility_getBoxReceiptLowLevel(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER));
}


bool OtMeChai::ot_utility_getBoxReceiptLowLevel(const char * serverId, const char * nymId, const char * accountId, const int boxType, const int64_t transactionNumber)
{
    OTString code;
    code.Format("{ var util = Utility(); var bWasSent = OTBool(false);"
                "  util.getBoxReceiptLowLevel(\"%s\", \"%s\", \"%s\", %d, int64_t(%lld), bWasSent); }",
                serverId, nymId, accountId, boxType, transactionNumber);
    return execBool(code.Get());
}


bool OtMeExtra::ot_utility_getBoxReceiptLowLevel(const char * serverId, const char * nymId, const char * accountId, const int boxType, const int64_t transactionNumber)
{
    Utility util;
    bool bWasSent = false;
    return util.getBoxReceiptLowLevel(serverId, nymId, accountId, boxType, transactionNumber, bWasSent);
}


void OtMeTest::EXPECT_ot_utility_getBoxReceiptLowLevel(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * accountId, const int boxType, const int64_t transactionNumber)
{
	EXPECT_CALL_VOID(FlushMessageBuffer());

    EXPECT_CALL_RETURN(REQUEST_NUMBER, getBoxReceipt(serverId, nymId, accountId, boxType, transactionNumber));

	EXPECT_ot_utility_receiveReplySuccessLowLevel(mock, index, serverId, nymId, REQUEST_NUMBER, "Utility::getBoxReceiptLowLevel");
}
