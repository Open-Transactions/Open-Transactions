#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(create_pseudonym)
{
	EXPECT_MOCK_STR("", NYM_ID, CreateNym(2048, NYM_SOURCE, ""));

	ASSERT_MOCK_EQ("", NYM_ID, me.create_pseudonym(2048, NYM_SOURCE, ""));
}
