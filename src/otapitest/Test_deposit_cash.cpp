#include "stdafx.hpp"


//SEE ALSO: deposit_local_purse


TEST_MULTI(deposit_cash_EmptyPurse)
{
	// calls details_deposit_purse with INDICES empty

	EXPECT_MULTI_RETURN("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	// note that if PURSE_DATA is empty then it will load the local account purse
	//EXPECT_CALL_RETURN(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	// when PURSE_DATA is different from local account purse a warning will be printed

	// when purse was loaded, collect token id's via INDICES

	EXPECT_MULTI_RETURN("", NYM_TO_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	if (index >= 0)
	{
		EXPECT_CALL_RETURN(false, Purse_HasPassword(SERVER_ID, PURSE_DATA));

		EXPECT_MULTI_RETURN("", PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		EXPECT_MULTI_RETURN("", PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

		if (index >= 0)
		{
			EXPECT_CALL_RETURN(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

			EXPECT_MULTI_RETURN(false, true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

			if (index >= 0)
			{
				EXPECT_TRANSACTION_SNA(MESSAGE_DATA, notarizeDeposit(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, PURSE_TO), SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

				OtMeTest::EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

				if (index >= 0)
				{
					OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_TO_ID, ACCOUNT_ID, false);
				}
			}
		}
	}

	ASSERT_MULTI_EQ(OT_ERROR, OT_TRUE, me.deposit_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
}

TEST_MULTI(deposit_cash_PurseWithOneToken)
{
	// calls details_deposit_purse with INDICES empty

	EXPECT_MULTI_RETURN("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	// note that if PURSE_DATA is empty then it will load the local account purse
	//EXPECT_MULTI_RETURN("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	// when PURSE_DATA is different from local account purse a warning will be printed

	// when purse was loaded, collect token id's via INDICES

	EXPECT_MULTI_RETURN("", NYM_TO_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	if (index >= 0)
	{
		EXPECT_CALL_RETURN(false, Purse_HasPassword(SERVER_ID, PURSE_DATA));

		EXPECT_MULTI_RETURN("", PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		EXPECT_MULTI_RETURN("", PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

		if (index >= 0)
		{
			EXPECT_CALL_RETURN(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

			EXPECT_CALL_RETURN(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

			EXPECT_MULTI_RETURN("", PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

			EXPECT_MULTI_RETURN("", TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

			EXPECT_MULTI_RETURN("", TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

			EXPECT_MULTI_RETURN("", PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

			EXPECT_MULTI_RETURN("", PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

			EXPECT_MULTI_RETURN(false, true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_NEW));

			if (index >= 0)
			{
				EXPECT_TRANSACTION_SNA(MESSAGE_DATA, notarizeDeposit(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, PURSE_DATA_TO), SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

				OtMeTest::EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

				if (index >= 0)
				{
					OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_TO_ID, ACCOUNT_ID, false);
				}
			}
		}
	}

	ASSERT_MULTI_EQ(OT_ERROR, OT_TRUE, me.deposit_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
}
