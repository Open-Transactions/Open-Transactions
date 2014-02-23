#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(details_export_cash)
{
	const char * resultValue = "";

	OtMeTest::EXPECT_load_or_retrieve_contract(mock, index, SERVER_ID, NYM_ID, ASSET_ID);

	EXPECT_MOCK_STR("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	//FIX OT_ERROR also bombs out, and of course we can also have multiple tokens
	EXPECT_MOCK_STR(0, 1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	if (index >= 0)
	{
		OtMeTest::EXPECT_load_or_retrieve_encrypt_key(mock, index, SERVER_ID, NYM_ID, NYM_TO_ID);

		EXPECT_MOCK_STR("", PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		if (index >= 0)
		{
			resultValue = PURSE_TO;

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

				if (index >= 0)
				{
					resultValue = PURSE_DATA_TO;

					EXPECT_MOCK_STR(false, true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_NEW));
				}
			}
		}
	}

	string retainedCopy;
	ASSERT_EQ(resultValue, me.details_export_cash(SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, INDICES_NONE, false, retainedCopy));
}


string OtMeExtra::details_export_cash(const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password, string & retainedCopy)
{
	const string str_var_name1("varRetained");
	OTVariable varRetained(str_var_name1, retainedCopy);
	this->AddVariable(str_var_name1, varRetained);

	OTString code;
	code.Format("{ details_export_cash(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %s, varRetained); }",
				serverId, nymFromId, assetId, nymToId, indices, password ? "true" : "false");

	const string result = ExecuteScript_ReturnString(code.Get(), __FUNCTION__);
	if (!result.empty())
	{
		retainedCopy = varRetained.GetValueString();
	}
	return result;
}


void OtMeTest::EXPECT_details_export_cash(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password)
{
	OtMeTest::EXPECT_load_or_retrieve_contract(mock, index, serverId, nymFromId, assetId);

	if (index >= 0)
	{
		EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

		//FIX can do different things here
		EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

		EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

		EXPECT_MOCK_RET(true, NumList_VerifyQuery(indices, indices));

		OtMeTest::EXPECT_load_or_retrieve_encrypt_key(mock, noAltPathways, SERVER_ID, NYM_ID, NYM_TO_ID);

		EXPECT_MOCK_RET(PURSE_DATA_EMPTY, Purse_Empty(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_MOCK_RET(PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		EXPECT_MOCK_RET(PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

		EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

		EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

		EXPECT_MOCK_RET(TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

		EXPECT_MOCK_RET(TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

		EXPECT_MOCK_RET(PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

		EXPECT_MOCK_RET(PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

		EXPECT_MOCK_RET(true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_EMPTY));
	}
}
