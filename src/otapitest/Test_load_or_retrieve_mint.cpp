#include "stdafx.hpp"


TEST_MULTI(load_or_retrieve_mint)
{
	EXPECT_MULTI_RETURN(true, false, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	if (index >= 0)
	{
		EXPECT_MULTI_REQUEST(MESSAGE_DATA, getMint(SERVER_ID, NYM_ID, ASSET_ID));

		EXPECT_MULTI_RETURN(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

		EXPECT_MULTI_RETURN(false, true, Mint_IsStillGood(SERVER_ID, ASSET_ID));
	}
	else
	{
		index++;
	}

	EXPECT_MULTI_RETURN("", MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_MULTI_EQ("", MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}
