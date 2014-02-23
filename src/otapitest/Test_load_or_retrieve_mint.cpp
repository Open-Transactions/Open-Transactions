#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_F(OtMeTest, load_or_retrieve_mint_Load)
{
	EXPECT_MOCK_RET(true, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}

TEST_F(OtMeTest, load_or_retrieve_mint_Retrieve)
{
	EXPECT_MOCK_RET(false, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_REQUEST(MESSAGE_DATA, getMint(SERVER_ID, NYM_ID, ASSET_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(true, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}
