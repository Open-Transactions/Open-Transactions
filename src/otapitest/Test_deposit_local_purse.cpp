#include "stdafx.h"
#include "OtMeTest.hpp"


//SEE ALSO: deposit_cash


TEST_MOCK(deposit_local_purse_EmptyPurse)
{
	// calls details_deposit_purse with PURSE_DATA empty so it must load purse

	EXPECT_MOCK_STR("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_STR("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	// empty purse
	EXPECT_MOCK_INT(OT_ERROR, 0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	ASSERT_EQ(OT_ERROR, me.deposit_local_purse(SERVER_ID, NYM_ID, ACCOUNT_ID, INDICES_NONE));
}


TEST_MOCK(deposit_local_purse_PurseWithOneToken)
{
	// calls details_deposit_purse with PURSE_DATA empty so it must load purse

	// no need to redo negative pathways tested above
	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));
	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	// purse with 1 token
	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_STR("", NYM_TO_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	if (index >= 0)
	{
		EXPECT_MOCK_RET(false, Purse_HasPassword(SERVER_ID, PURSE_DATA));

		EXPECT_MOCK_STR("", PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		EXPECT_MOCK_STR("", PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

		if (index >= 0)
		{
			EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

			//FIX this may fail as well
			EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

			EXPECT_MOCK_STR("", PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

			EXPECT_MOCK_STR("", TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

			EXPECT_MOCK_STR("", TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

			EXPECT_MOCK_STR("", PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

			EXPECT_MOCK_STR("", PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

			EXPECT_MOCK_STR(false, true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_NEW));

			if (index >= 0)
			{
				EXPECT_TRANSACTION_SNA(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, MESSAGE_DATA, notarizeDeposit(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, PURSE_DATA_TO));

				OtMeTest::EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

				if (index >= 0)
				{
					OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_TO_ID, ACCOUNT_ID, false);
				}
				else
				{
					//FIX this one can fail, too
					EXPECT_MOCK_RET(true, Wallet_ImportPurse(SERVER_ID, ASSET_ID, NYM_TO_ID, PURSE_DATA_TO));
				}
			}
		}
	}

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.deposit_local_purse(SERVER_ID, NYM_ID, ACCOUNT_ID, INDICES_NONE));
}
