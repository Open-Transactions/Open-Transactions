#include "stdafx.h"


TEST_MOCK(ot_utility_insureHaveAllBoxReceipts_TypeNymbox_Receipts0)
{
    EXPECT_MOCK_STR("", LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

    EXPECT_MOCK_STR(false, true, VerifySignature(NYM_ID, LEDGER_DATA));

    if (index >= 0)
    {
        //FIX what if this one fails?
        EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));
    }

    ASSERT_MOCK_EQ(false, true, me.ot_utility_insureHaveAllBoxReceipts(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX));
}

TEST_MOCK(ot_utility_insureHaveAllBoxReceipts_TypeNymbox_Receipts1)
{
    EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

    EXPECT_MOCK_RET(true, VerifySignature(NYM_ID, LEDGER_DATA));

    EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

    bool returnValue = true;

    //FIX if this one fails function still returns true?
    EXPECT_MOCK_STR(OT_ERROR, TRANSACTION_NUMBER, Ledger_GetTransactionIDByIndex(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA, 0));

    if (index >= 0)
    {
        returnValue = false;

        EXPECT_MOCK_STR("", TRANSACTION_DATA, Ledger_GetTransactionByID(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA, TRANSACTION_NUMBER));

        if (index >= 0)
        {
            returnValue = true;

            //FIX what if this one fails?
            //FIX more values possible, especially test TYPE_REPLY_NOTICE
            EXPECT_MOCK_RET(TYPE_BLANK, Transaction_GetType(SERVER_ID, NYM_ID, ACCOUNT_ID, TRANSACTION_DATA));

            EXPECT_MOCK_STR(true, false, DoesBoxReceiptExist(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER));

            if (index >= 0)
            {
                int invertPathways = INVERT_MOCK;
                OtMeTest::EXPECT_ot_utility_getBoxReceiptWithErrorCorrection(mock, invertPathways, SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER);

                if (index >= 0)
                {
                    returnValue = false;
                }
            }
        }
    }

    ASSERT_EQ(returnValue, me.ot_utility_insureHaveAllBoxReceipts(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX));
}

TEST_MOCK(ot_utility_insureHaveAllBoxReceipts_TypeInbox_Receipts0)
{
    EXPECT_MOCK_STR("", LEDGER_DATA, LoadInboxNoVerify(SERVER_ID, NYM_ID, ACCOUNT_ID));

    EXPECT_MOCK_STR(false, true, VerifySignature(NYM_ID, LEDGER_DATA));

    if (index >= 0)
    {
        //FIX what if this one fails?
        EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));
    }

    ASSERT_MOCK_EQ(false, true, me.ot_utility_insureHaveAllBoxReceipts(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_INBOX));
}

TEST_MOCK(ot_utility_insureHaveAllBoxReceipts_TypeOutbox_Receipts0)
{
    EXPECT_MOCK_STR("", LEDGER_DATA, LoadOutboxNoVerify(SERVER_ID, NYM_ID, ACCOUNT_ID));

    EXPECT_MOCK_STR(false, true, VerifySignature(NYM_ID, LEDGER_DATA));

    if (index >= 0)
    {
        //FIX what if this one fails?
        EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));
    }

    ASSERT_MOCK_EQ(false, true, me.ot_utility_insureHaveAllBoxReceipts(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_OUTBOX));
}


bool OtMeExtra::ot_utility_insureHaveAllBoxReceipts(const char * serverId, const char * nymId, const char * accountId, const int boxType)
{
	OTString code;
	code.Format("{ var util = Utility(); util.insureHaveAllBoxReceipts(\"%s\", \"%s\", \"%s\", %d); }",
		serverId, nymId, accountId, boxType);
	return execBool(code.Get());
}


void OtMeTest::EXPECT_ot_utility_insureHaveAllBoxReceipts(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * accountId, const int boxType)
{
    switch (boxType)
    {
    case BOX_TYPE_INBOX:
        EXPECT_MOCK_RET(LEDGER_DATA, LoadInboxNoVerify(SERVER_ID, NYM_ID, ACCOUNT_ID));
        break;
    case BOX_TYPE_NYMBOX:
        EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));
        break;
    case BOX_TYPE_OUTBOX:
        EXPECT_MOCK_RET(LEDGER_DATA, LoadOutboxNoVerify(SERVER_ID, NYM_ID, ACCOUNT_ID));
        break;
    }

    EXPECT_MOCK_STR(false, true, VerifySignature(NYM_ID, LEDGER_DATA));

    if (index >= 0)
    {
        EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));
    }
}
