#include "stdafx.h"

#include "OtMeTest.hpp"

//#define ALLTESTS

#ifdef ALLTESTS

TEST_MOCK(deposit_cash_EmptyPurse)
{
	// calls details_deposit_purse with INDICES empty

	EXPECT_MOCK_STR("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	// note that if PURSE_DATA is empty then it will load the local account purse
	//EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	// when PURSE_DATA is different from local account purse a warning will be printed

	// when purse was loaded, collect token id's via INDICES

	EXPECT_MOCK_STR("", NYM_TO_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	if (index >= 0)
	{
		EXPECT_MOCK_RET(false, Purse_HasPassword(SERVER_ID, PURSE_DATA));

		EXPECT_MOCK_STR("", PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		EXPECT_MOCK_STR("", PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

		if (index >= 0)
		{
			EXPECT_MOCK_RET(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

			EXPECT_MOCK_STR(false, true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

			if (index >= 0)
			{
				EXPECT_TRANSACTION_SNA(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, MESSAGE_DATA, notarizeDeposit(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, PURSE_TO));

				OtMeTest::EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

				if (index >= 0)
				{
					OtMeTest::EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_TO_ID, ACCOUNT_ID, false);
				}
			}
		}
	}

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.deposit_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
}

TEST_MOCK(deposit_cash_PurseWithOneToken)
{
	// calls details_deposit_purse with INDICES empty

	EXPECT_MOCK_STR("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	// note that if PURSE_DATA is empty then it will load the local account purse
	//EXPECT_MOCK_STR("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	// when PURSE_DATA is different from local account purse a warning will be printed

	// when purse was loaded, collect token id's via INDICES

	EXPECT_MOCK_STR("", NYM_TO_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	if (index >= 0)
	{
		EXPECT_MOCK_RET(false, Purse_HasPassword(SERVER_ID, PURSE_DATA));

		EXPECT_MOCK_STR("", PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		EXPECT_MOCK_STR("", PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

		if (index >= 0)
		{
			EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

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
					OtMeTest::EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_TO_ID, ACCOUNT_ID, false);
				}
			}
		}
	}

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.deposit_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
}

#endif // ALLTESTS
