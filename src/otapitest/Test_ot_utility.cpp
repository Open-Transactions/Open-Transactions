#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(ot_utility_delay)
{
	EXPECT_MOCK(Sleep(50));

	me.exec("{ var util = Utility(); util.delay(); }");
}

TEST_MOCK(ot_utility_longDelay)
{
	EXPECT_MOCK(Sleep(250));

	me.exec("{ var util = Utility(); util.longDelay(); }");
}

TEST_MOCK(ot_utility_getNbrTransactionCount)
{
	ASSERT_EQ(10, me.execInt("{ var util = Utility(); util.getNbrTransactionCount(); }"));
	ASSERT_EQ(22, me.execInt("{ var util = Utility(); util.max_trans_dl = 22; util.getNbrTransactionCount(); }"));
}

TEST_MOCK(ot_utility_setNbrTransactionCount)
{
	ASSERT_EQ(77, me.execInt("{ var util = Utility(); util.setNbrTransactionCount(77); util.getNbrTransactionCount(); }"));
}

TEST_MOCK(ot_utility_getLastReplyReceived)
{
	ASSERT_EQ("", me.execStr("{ var util = Utility(); util.getLastReplyReceived(); }"));
	ASSERT_EQ("test", me.execStr("{ var util = Utility(); util.strLastReplyReceived = \"test\"; util.getLastReplyReceived(); }"));
}

TEST_MOCK(ot_utility_setLastReplyReceived)
{
	ASSERT_EQ("test", me.execStr("{ var util = Utility(); util.setLastReplyReceived(\"test\"); util.getLastReplyReceived(); }"));
}
