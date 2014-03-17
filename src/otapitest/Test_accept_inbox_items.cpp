#include "stdafx.hpp"


TEST_MULTI(accept_inbox_items)
{
	bool response = false;

	EXPECT_MULTI_RETURN("", NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MULTI_RETURN("", SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	if (index >= 0)
	{
		OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

        if (index >= 0)
        {
            OtMeTest::EXPECT_insure_enough_nums(mock, index, 10, SERVER_ID, NYM_ID);

            EXPECT_MULTI_RETURN("", LEDGER_DATA, LoadInbox(SERVER_ID, NYM_ID, ACCOUNT_ID));

            EXPECT_MULTI_RETURN(0, 1, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

            //FIX next behavior only for ITEM_TYPE_ALL and INDICES_ALL

            if (index >= 0)
            {
                // go once through the loop

                //FIX what if this one fails?
                EXPECT_CALL_RETURN(TRANSACTION_DATA, Ledger_GetTransactionByIndex(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA, 0));

                EXPECT_MULTI_RETURN("", LEDGER_DATA2, Ledger_CreateResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

                EXPECT_MULTI_RETURN("", LEDGER_DATA3, Transaction_CreateResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA2, TRANSACTION_DATA, true));

                EXPECT_MULTI_RETURN("", LEDGER_DATA4, Ledger_FinalizeResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA3));

                EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, processInbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA4));

                OtMeTest::EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID);

                if (index >= 0)
                {
                    response = true;

                    OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, true);
                }
            }
        }
    }

	ASSERT_EQ(response, me.accept_inbox_items(ACCOUNT_ID, ITEM_TYPE_ALL, INDICES_ALL));
}
