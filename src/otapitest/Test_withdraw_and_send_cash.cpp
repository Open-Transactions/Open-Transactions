#include "stdafx.hpp"


TEST_MULTI(easy_withdraw_cash)
{
	//FIX may want to inline this one and have a shortest-path one in OtMeTest
	OtMeTest::EXPECT_details_withdraw_cash(mock, index, ACCOUNT_ID, AMOUNT);

	ASSERT_MULTI_EQ(OT_ERROR, OT_TRUE, me.easy_withdraw_cash(ACCOUNT_ID, AMOUNT));
}


TEST_MULTI(withdraw_and_send_cash_Fail_HasEmptyPurseEvenAfterCashWithdrawal)
{
	EXPECT_MULTI_RETURN("", NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MULTI_RETURN("", SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MULTI_RETURN("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	if (index >= 0)
	{
		// entering purse_get_indices_or_amount, all 3 pathways return false
		EXPECT_MULTI_RETURN("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

		EXPECT_MULTI_RETURN(OT_ERROR, 0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

		index += 2;
		OtMeTest::EXPECT_details_withdraw_cash(mock, index, ACCOUNT_ID, AMOUNT);

		if (index >= 0)
		{
			// withdrawal successful, but all 3 pathways return false again
			EXPECT_MULTI_RETURN("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

			EXPECT_MULTI_RETURN(OT_ERROR, 0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

			EXPECT_CALL_RETURN("$12.34", FormatAmount(ASSET_ID, AMOUNT));
		}
	}

	ASSERT_FALSE(me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}

TEST_MULTI(withdraw_and_send_cash_PurseHasOneToken)
{
	// no need to retest no/empty purse pathways done before...
	EXPECT_CALL_RETURN(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_CALL_RETURN(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_CALL_RETURN(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	// first we have no purse
	EXPECT_CALL_RETURN("", LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	OtMeTest::EXPECT_details_withdraw_cash(mock, noAltPathways, ACCOUNT_ID, AMOUNT);

	// now we have a non-empty purse
	EXPECT_CALL_RETURN(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));
 
	EXPECT_CALL_RETURN(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MULTI_RETURN("", TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MULTI_RETURN("", PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MULTI_RETURN("", TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	if (index < 0)
	{
		// error message uses this...
		EXPECT_CALL_RETURN("$12.34", FormatAmount(ASSET_ID, AMOUNT));
	}
	else
	{
		// note: we're trying to withdraw tokens totalling to the EXACT amount
		//FIX: what if any of the following 5 fail? (be paranoid!)
		EXPECT_CALL_RETURN(AMOUNT, Token_GetDenomination(SERVER_ID, ASSET_ID, TOKEN_DATA)); // instead of TOKEN_VALUE

		EXPECT_CALL_RETURN(TOKEN_SERIES, Token_GetSeries(SERVER_ID, ASSET_ID, TOKEN_DATA));

		EXPECT_CALL_RETURN(mock.GetTime() - 864000000L, Token_GetValidFrom(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days ago

		EXPECT_CALL_RETURN(mock.GetTime() + 864000000L, Token_GetValidTo(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days aheas

		EXPECT_CALL_RETURN(INDICES_ONE, NumList_Add("", INDICES_ONE));

		OtMeTest::EXPECT_details_export_cash(mock, index, SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false);

		if (index >= 0)
		{
			EXPECT_CALL_RETURN(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

			EXPECT_REQUEST(MESSAGE_DATA, sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, PURSE_DATA_TO, PURSE_DATA_FROM));

			EXPECT_CALL_RETURN(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

			//FIX interesting extra call path here
		}
	}

	ASSERT_MULTI_EQ(false, true, me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}
