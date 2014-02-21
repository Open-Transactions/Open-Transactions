#include "stdafx.h"

#include "OtMeTest.hpp"

//#define ALLTESTS

#ifdef ALLTESTS

TEST_MOCK(accept_inbox_items)
{
	bool response = false;

	EXPECT_MOCK_STR("", NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_STR("", SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	if (index >= 0)
	{
		//FIX bombs with OT_ERROR
		OtMeTest::EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_ID, ACCOUNT_ID, false);

		// madeEasy.insure_enough_nums bombs with OT_ERROR
		EXPECT_MOCK_RET(10, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

		EXPECT_MOCK_STR("", LEDGER_DATA, LoadInbox(SERVER_ID, NYM_ID, ACCOUNT_ID));

		EXPECT_MOCK_STR(0, 1, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

		//FIX next behavior only for ITEM_TYPE_ALL and INDICES_ALL

		if (index >= 0)
		{
			// go once through the loop

			//FIX what if this one fails?
			EXPECT_MOCK_RET(TRANSACTION_DATA, Ledger_GetTransactionByIndex(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA, 0));

			EXPECT_MOCK_STR("", LEDGER_DATA2, Ledger_CreateResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

			EXPECT_MOCK_STR("", LEDGER_DATA3, Transaction_CreateResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA2, TRANSACTION_DATA, true));

			EXPECT_MOCK_STR("", LEDGER_DATA4, Ledger_FinalizeResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA3));

			EXPECT_MOCK_TRANSACTION(MESSAGE_DATA, processInbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA4));

			OtMeTest::EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID);

			if (index >= 0)
			{
				response = true;

				OtMeTest::EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_ID, ACCOUNT_ID, true);
			}
		}
	}

	ASSERT_EQ(response, me.accept_inbox_items(ACCOUNT_ID, ITEM_TYPE_ALL, INDICES_ALL));
}

#endif // ALLTESTS
