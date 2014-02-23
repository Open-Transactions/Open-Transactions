#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(export_cash)
{
	OtMeTest::EXPECT_details_export_cash(mock, index, SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false);

	std::string retainedCopy;
	ASSERT_MOCK_EQ("", PURSE_DATA_TO, me.export_cash(SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false, retainedCopy));

	if (index >= 0)
	{
		ASSERT_EQ(PURSE_DATA_FROM, retainedCopy);
	}
}
