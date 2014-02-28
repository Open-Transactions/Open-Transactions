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

TEST_MOCK(ot_utility_VerifyMessageSuccess)
{
	string code = "{ VerifyMessageSuccess(\"";
	string code2 = "\"); }";

	ASSERT_EQ(OT_ERROR, me.execInt(code + "" + code2));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));
	ASSERT_EQ(OT_TRUE, me.execInt(code + MESSAGE_DATA + code2));

	EXPECT_MOCK_RET(OT_FALSE, Message_GetSuccess(TOKEN_DATA));
	ASSERT_EQ(OT_FALSE, me.execInt(code + TOKEN_DATA + code2));

	EXPECT_MOCK_STR(77, OT_ERROR, Message_GetSuccess(PURSE_DATA));
	ASSERT_EQ(OT_ERROR, me.execInt(code + PURSE_DATA + code2));
}

TEST_MOCK(ot_utility_VerifyMsgBalanceAgrmntSuccess)
{
	string code = "{ VerifyMsgBalanceAgrmntSuccess(\"";
	code = code + SERVER_ID + "\", \"" + NYM_ID + "\", \"" + ACCOUNT_ID + "\", \"";
	string code2 = "\"); }";

	ASSERT_EQ(OT_ERROR, me.execInt(code + "" + code2));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
	ASSERT_EQ(OT_TRUE, me.execInt(code + MESSAGE_DATA + code2));

	EXPECT_MOCK_RET(OT_FALSE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, TOKEN_DATA));
	ASSERT_EQ(OT_FALSE, me.execInt(code + TOKEN_DATA + code2));

	EXPECT_MOCK_STR(77, OT_ERROR, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
	ASSERT_EQ(OT_ERROR, me.execInt(code + PURSE_DATA + code2));
}

TEST_MOCK(ot_utility_VerifyMsgTrnxSuccess)
{
	string code = "{ VerifyMsgTrnxSuccess(\"";
	code = code + SERVER_ID + "\", \"" + NYM_ID + "\", \"" + ACCOUNT_ID + "\", \"";
	string code2 = "\"); }";

	ASSERT_EQ(OT_ERROR, me.execInt(code + "" + code2));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
	ASSERT_EQ(OT_TRUE, me.execInt(code + MESSAGE_DATA + code2));

	EXPECT_MOCK_RET(OT_FALSE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, TOKEN_DATA));
	ASSERT_EQ(OT_FALSE, me.execInt(code + TOKEN_DATA + code2));

	EXPECT_MOCK_STR(77, OT_ERROR, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
	ASSERT_EQ(OT_ERROR, me.execInt(code + PURSE_DATA + code2));
}

TEST_MOCK(ot_utility_InterpretTransactionMsgReply)
{
	string code = "{ InterpretTransactionMsgReply(\"";
	code = code + SERVER_ID + "\", \"" + NYM_ID + "\", \"" + ACCOUNT_ID + "\", \"ATTEMPT\", \"";
	string code2 = "\"); }";

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
	
	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
	
	ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.execInt(code + MESSAGE_DATA + code2));
}
