#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(load_or_retrieve_mint)
{
	EXPECT_MOCK_STR(true, false, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	if (index >= 0)
	{
		EXPECT_MOCK_REQUEST(MESSAGE_DATA, getMint(SERVER_ID, NYM_ID, ASSET_ID));

		EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

		EXPECT_MOCK_STR(false, true, Mint_IsStillGood(SERVER_ID, ASSET_ID));
	}
	else
	{
		index++;
	}

	EXPECT_MOCK_STR("", MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_MOCK_EQ("", MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}
