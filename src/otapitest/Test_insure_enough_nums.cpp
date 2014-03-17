#include "stdafx.hpp"


TEST_MULTI(insure_enough_nums)
{
	int returnValue = true;

	EXPECT_MULTI_RETURN(2, 0, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	if (index >= 0)
	{
		returnValue = false;

        //FIX what if this one fails?
        OtMeTest::EXPECT_ot_utility_getTransactionNumbers(mock, noAltPathways, SERVER_ID, NYM_ID);

        OtMeTest::EXPECT_details_refresh_nym(mock, index, SERVER_ID, NYM_ID, false);

        if (index >= 0)
		{
			EXPECT_MULTI_RETURN(0, 2, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));
            if (index >= 0)
            {
                returnValue = true;
            }
        }
	}

	ASSERT_EQ(returnValue, me.make_sure_enough_trans_nums(2, SERVER_ID, NYM_ID));
}


void OtMeTest::EXPECT_insure_enough_nums(Mock_OTAPI_Exec & mock, int & index, const int numberNeeded, const char * serverId, const char * nymId)
{
    EXPECT_CALL_RETURN(0, GetNym_TransactionNumCount(serverId, nymId));

    EXPECT_ot_utility_getTransactionNumbers(mock, noAltPathways, serverId, nymId);

    EXPECT_details_refresh_nym(mock, noAltPathways, serverId, nymId, false);


    EXPECT_MULTI_RETURN(0, numberNeeded, GetNym_TransactionNumCount(serverId, nymId));
}


