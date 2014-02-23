#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(easy_withdraw_cash)
{
	//FIX may want to inline this one and have a shortest-path one in OtMeTest
	OtMeTest::EXPECT_details_withdraw_cash(mock, index, ACCOUNT_ID, AMOUNT);

	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.easy_withdraw_cash(ACCOUNT_ID, AMOUNT));
}

TEST_MOCK(withdraw_and_send_cash_Fail_HasEmptyPurseEvenAfterCashWithdrawal)
{
	EXPECT_MOCK_STR("", NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_STR("", SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_STR("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	if (index >= 0)
	{
		// entering purse_get_indices_or_amount, all 3 pathways return false
		EXPECT_MOCK_STR("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

		EXPECT_MOCK_STR(OT_ERROR, 0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

		index += 2;
		OtMeTest::EXPECT_details_withdraw_cash(mock, index, ACCOUNT_ID, AMOUNT);

		if (index >= 0)
		{
			// withdrawal successful, but all 3 pathways return false again
			EXPECT_MOCK_STR("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

			EXPECT_MOCK_STR(OT_ERROR, 0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

			EXPECT_MOCK_RET("$12.34", FormatAmount(ASSET_ID, AMOUNT));
		}
	}

	ASSERT_FALSE(me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}

TEST_MOCK(withdraw_and_send_cash_PurseHasOneToken)
{
	// no need to retest no/empty purse pathways done before...
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	// first we have no purse
	EXPECT_MOCK_RET("", LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	OtMeTest::EXPECT_details_withdraw_cash(mock, noAltPathways, ACCOUNT_ID, AMOUNT);

	// now we have a non-empty purse
	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));
 
	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_STR("", TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_STR("", PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_STR("", TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	if (index < 0)
	{
		// error message uses this...
		EXPECT_MOCK_RET("$12.34", FormatAmount(ASSET_ID, AMOUNT));
	}
	else
	{
		// note: we're trying to withdraw tokens totalling to the EXACT amount
		//FIX: what if any of the following 5 fail? (be paranoid!)
		EXPECT_MOCK_RET(AMOUNT, Token_GetDenomination(SERVER_ID, ASSET_ID, TOKEN_DATA)); // instead of TOKEN_VALUE

		EXPECT_MOCK_RET(TOKEN_SERIES, Token_GetSeries(SERVER_ID, ASSET_ID, TOKEN_DATA));

		EXPECT_MOCK_RET(mock.GetTime() - 864000000L, Token_GetValidFrom(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days ago

		EXPECT_MOCK_RET(mock.GetTime() + 864000000L, Token_GetValidTo(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days aheas

		EXPECT_MOCK_RET(INDICES_ONE, NumList_Add("", INDICES_ONE));

		OtMeTest::EXPECT_details_export_cash(mock, index, SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false);

		if (index >= 0)
		{
			EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

			EXPECT_REQUEST(MESSAGE_DATA, sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, PURSE_DATA_TO, PURSE_DATA_FROM));

			EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

			//FIX interesting extra call path here
		}
	}

	ASSERT_MOCK_EQ(false, true, me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}
