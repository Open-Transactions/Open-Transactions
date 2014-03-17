#include "stdafx.hpp"


TEST_MULTI(load_or_retrieve_contract)
{
	//NOTE: we invert the negative/positive pathways here,
	//      since the function will 'bomb out' whenever it finds a contract

	const char * expectResult = CONTRACT_DATA;
	EXPECT_MULTI_RETURN(CONTRACT_DATA, "", LoadAssetContract(CONTRACT_ID));

	if (index >= 0)
	{
		expectResult = "";
		EXPECT_MULTI_REQUEST(CONTRACT_DATA, getContract(SERVER_ID, NYM_ID, CONTRACT_ID));

		EXPECT_MULTI_RETURN(OT_FALSE, OT_TRUE, Message_GetSuccess(CONTRACT_DATA));

		if (index >= 0)
		{
			expectResult = CONTRACT_DATA;
			EXPECT_MULTI_RETURN(CONTRACT_DATA, "", LoadAssetContract(CONTRACT_ID));
			if (index >= 0)
			{
				expectResult = "";
			}
		}
	}

	ASSERT_EQ(expectResult, me.load_or_retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID));
}


void OtMeTest::EXPECT_load_or_retrieve_contract(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * contractId)
{
	EXPECT_CALL_RETURN("", LoadAssetContract(contractId));
	
	EXPECT_REQUEST(CONTRACT_DATA, getContract(serverId, nymId, contractId));

	EXPECT_CALL_RETURN(OT_TRUE, Message_GetSuccess(CONTRACT_DATA));

	EXPECT_MULTI_RETURN("", CONTRACT_DATA, LoadAssetContract(contractId));
}
