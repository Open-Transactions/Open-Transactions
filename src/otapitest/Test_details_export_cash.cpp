#include "stdafx.hpp"


TEST_MULTI(details_export_cash)
{
	const char * resultValue = "";

	OtMeTest::EXPECT_load_or_retrieve_contract(mock, index, SERVER_ID, NYM_ID, ASSET_ID);

	EXPECT_MULTI_RETURN("", PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	//FIX OT_ERROR also bombs out, and of course we can also have multiple tokens
	EXPECT_MULTI_RETURN(0, 1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	if (index >= 0)
	{
		OtMeTest::EXPECT_load_or_retrieve_encrypt_key(mock, index, SERVER_ID, NYM_ID, NYM_TO_ID);

		EXPECT_MULTI_RETURN("", PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		if (index >= 0)
		{
			resultValue = PURSE_TO;

			EXPECT_MULTI_RETURN("", PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

			if (index >= 0)
			{
				EXPECT_CALL_RETURN(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

				//FIX this may fail as well
				EXPECT_CALL_RETURN(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

				EXPECT_MULTI_RETURN("", PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

				EXPECT_MULTI_RETURN("", TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

				EXPECT_MULTI_RETURN("", TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

				EXPECT_MULTI_RETURN("", PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

				EXPECT_MULTI_RETURN("", PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

				if (index >= 0)
				{
					resultValue = PURSE_DATA_TO;

					EXPECT_MULTI_RETURN(false, true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_NEW));
				}
			}
		}
	}

    string hisNymId = NYM_TO_ID;
    string retainedCopy;
    ASSERT_EQ(resultValue, me.details_export_cash(SERVER_ID, NYM_ID, ASSET_ID, hisNymId, INDICES_NONE, false, retainedCopy));
}


string OtMeChai::details_export_cash(const char * serverId, const char * nymFromId, const char *assetId, string & hisNymId, const char *indices, bool password, string & retainedCopy)
{
    const string str_var_name1("varHisNymId");
    OTVariable varHisNymId(str_var_name1, hisNymId);
    this->AddVariable(str_var_name1, varHisNymId);

    const string str_var_name2("varRetained");
    OTVariable varRetained(str_var_name2, retainedCopy);
    this->AddVariable(str_var_name2, varRetained);

    OTString code;
	code.Format("{ details_export_cash(\"%s\", \"%s\", \"%s\", varHisNymId, \"%s\", %s, varRetained); }",
                serverId, nymFromId, assetId, indices, boolStr(password));

	const string result = execStr(code.Get());
	if (!result.empty())
	{
        hisNymId = varHisNymId.GetValueString();
        retainedCopy = varRetained.GetValueString();
    }
	return result;
}


string OtMeExtra::details_export_cash(const char * serverId, const char * nymFromId, const char *assetId, string & hisNymId, const char *indices, bool password, string & retainedCopy)
{
    string varRetained;
	const string result = ::details_export_cash(serverId, nymFromId, assetId, hisNymId, indices, password, varRetained);
	if (!result.empty())
	{
		retainedCopy = varRetained;
	}
	return result;
}


void OtMeTest::EXPECT_details_export_cash(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password)
{
	OtMeTest::EXPECT_load_or_retrieve_contract(mock, index, serverId, nymFromId, assetId);

	if (index >= 0)
	{
		EXPECT_CALL_RETURN(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

		//FIX can do different things here
		EXPECT_CALL_RETURN(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

		EXPECT_CALL_RETURN(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_CALL_RETURN(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_CALL_RETURN(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

		EXPECT_CALL_RETURN(true, NumList_VerifyQuery(indices, indices));

		OtMeTest::EXPECT_load_or_retrieve_encrypt_key(mock, noAltPathways, SERVER_ID, NYM_ID, NYM_TO_ID);

		EXPECT_CALL_RETURN(PURSE_DATA_EMPTY, Purse_Empty(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_CALL_RETURN(PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

		EXPECT_CALL_RETURN(PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

		EXPECT_CALL_RETURN(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

		EXPECT_CALL_RETURN(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_CALL_RETURN(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

		EXPECT_CALL_RETURN(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

		EXPECT_CALL_RETURN(TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

		EXPECT_CALL_RETURN(TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

		EXPECT_CALL_RETURN(PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

		EXPECT_CALL_RETURN(PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

		EXPECT_CALL_RETURN(true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_EMPTY));
	}
}
