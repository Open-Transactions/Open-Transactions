#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(ot_utility_getTransactionNumbers_1)
{
	bool returnValue = true;

	// check 0
	OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(mock, noAltPathways, SERVER_ID, NYM_ID);

	// check 1
	int invertPathways = INVERT_MOCK;
	OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, invertPathways, SERVER_ID, NYM_ID, true);

	OtMeTest::EXPECT_ot_utility_getTransactionNumbers_part2(mock, index, SERVER_ID, NYM_ID, returnValue);

	ASSERT_EQ(returnValue, me.ot_utility_getTransactionNumbers(SERVER_ID, NYM_ID));
}

TEST_MOCK(ot_utility_getTransactionNumbers_2)
{
	bool returnValue = false;

	// check 0
	int errorPathway = 0;
	OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(mock, errorPathway, SERVER_ID, NYM_ID);

	// check 2
	OtMeTest::EXPECT_ot_utility_getRequestNumber(mock, index, SERVER_ID, NYM_ID);

	if (index >= 0)
	{
		// check 3
		OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, index, SERVER_ID, NYM_ID, true);

		if (index >= 0)
		{
			returnValue = true;

			// check 5
			OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(mock, noAltPathways, SERVER_ID, NYM_ID);

			// check 6
			int invertPathways = INVERT_MOCK;
			OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, invertPathways, SERVER_ID, NYM_ID, true);

			OtMeTest::EXPECT_ot_utility_getTransactionNumbers_part2(mock, index, SERVER_ID, NYM_ID, returnValue);
		}
	}

	ASSERT_EQ(returnValue, me.ot_utility_getTransactionNumbers(SERVER_ID, NYM_ID));
}

TEST_MOCK(ot_utility_getTransactionNumbers_3)
{
	bool returnValue = false;

	// check 0
	int errorPathway = 0;
	OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(mock, errorPathway, SERVER_ID, NYM_ID);

	// check 2
	OtMeTest::EXPECT_ot_utility_getRequestNumber(mock, noAltPathways, SERVER_ID, NYM_ID);

	// check 3
	OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, noAltPathways, SERVER_ID, NYM_ID, true);

	// check 5
	errorPathway = 0;
	OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(mock, errorPathway, SERVER_ID, NYM_ID);

	// check 7
	OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, index, SERVER_ID, NYM_ID, true);

	if (index >= 0)
	{
		returnValue = true;

		// check 9
		//FIX errorpathway goes to check 11
		OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(mock, noAltPathways, SERVER_ID, NYM_ID);

		// check 10
		int invertPathways = INVERT_MOCK;
		OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, invertPathways, SERVER_ID, NYM_ID, true);

		OtMeTest::EXPECT_ot_utility_getTransactionNumbers_part2(mock, index, SERVER_ID, NYM_ID, returnValue);
	}

	ASSERT_EQ(returnValue, me.ot_utility_getTransactionNumbers(SERVER_ID, NYM_ID));
}


bool OtMeExtra::ot_utility_getTransactionNumbers(const char * serverId, const char * nymId)
{
	OTString code;
	code.Format("{ var util = Utility(); util.getTransactionNumbers(\"%s\", \"%s\", true); }", serverId, nymId);
	return execBool(code.Get());
}


void OtMeTest::EXPECT_ot_utility_getTransactionNumbers(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId)
{
	OtMeTest::EXPECT_ot_utility_getTransactionNumLowLevel(mock, noAltPathways, SERVER_ID, NYM_ID);

	int errorPathway = 0;
	OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, errorPathway, SERVER_ID, NYM_ID, true);

	EXPECT_MOCK_RET(NYM_HASH, Message_GetNymboxHash(MESSAGE_DATA));

	EXPECT_MOCK_RET(NYM_HASH2, GetNym_NymboxHash(serverId, nymId));

	OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, index, serverId, nymId, true);
}


void OtMeTest::EXPECT_ot_utility_getTransactionNumbers_part2(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, bool & returnValue)
{
	if (index >= 0)
	{
		returnValue = true;

		// check 12
		EXPECT_MOCK_RET(NYM_HASH, Message_GetNymboxHash(MESSAGE_DATA));

		// check 13
		EXPECT_MOCK_STR(NYM_HASH, NYM_HASH2, GetNym_NymboxHash(serverId, nymId));

		if (index >= 0)
		{
			returnValue = false;

			// check 14
			OtMeTest::EXPECT_ot_utility_getAndProcessNymbox_4(mock, index, serverId, nymId, true);

			if (index >= 0)
			{
				returnValue = true;
			}
		}
	}
}
