#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_F(OtMeTest, stat_asset_account)
{
	//NOTE: Not important whether the retrieval functions will fail
	//      The resulting empty strings are simply returned, too
	EXPECT_MOCK_RET(WALLET_NAME, GetAccountWallet_Name(ACCOUNT_ID));

	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(AMOUNT, GetAccountWallet_Balance(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_NAME, GetAssetType_Name(ASSET_ID));

	EXPECT_MOCK_RET(NYM_NAME, GetNym_Name(NYM_ID));

	EXPECT_MOCK_RET(SERVER_NAME, GetServer_Name(SERVER_ID));

	EXPECT_MOCK_RET("$12.34", FormatAmount(ASSET_ID, AMOUNT));

	std::string msgData = "   Balance: $12.34   (";
	msgData = msgData + WALLET_NAME + ")\n"
		"Account ID: " + ACCOUNT_ID + " ( " + WALLET_NAME + " )\n"
		"Asset Type: " + ASSET_ID + " ( " + ASSET_NAME + " )\n"
		"Owner Nym:  " + NYM_ID + " ( " + NYM_NAME + " )\n"
		"Server:     " + SERVER_ID + " ( " + SERVER_NAME + " )";
	ASSERT_EQ(msgData, me.stat_asset_account(ACCOUNT_ID));
}
