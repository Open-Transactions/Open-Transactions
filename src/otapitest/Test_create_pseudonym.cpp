#include "stdafx.hpp"


TEST_MULTI(create_pseudonym)
{
	EXPECT_MULTI_RETURN("", NYM_ID, CreateNym(2048, NYM_SOURCE, ""));

	ASSERT_MULTI_EQ("", NYM_ID, me.create_pseudonym(2048, NYM_SOURCE, ""));
}
