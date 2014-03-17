#include "stdafx.hpp"


TEST_MOCK(ot_utility_delay)
{
	EXPECT_MOCK(Sleep(50));

    me.ot_utility_delay();
}

void OtMeChai::ot_utility_delay()
{
	exec("{ var util = Utility(); util.delay(); }");
}

void OtMeExtra::ot_utility_delay()
{
    Utility util;
    util.delay();
}


TEST_MOCK(ot_utility_longDelay)
{
	EXPECT_MOCK(Sleep(250));

    me.ot_utility_longDelay();
}

void OtMeChai::ot_utility_longDelay()
{
    exec("{ var util = Utility(); util.longDelay(); }");
}

void OtMeExtra::ot_utility_longDelay()
{
    Utility util;
    util.longDelay();
}


TEST_MOCK(ot_utility_getNbrTransactionCount)
{
    ASSERT_EQ(10, me.ot_utility_getNbrTransactionCount());
}

int OtMeChai::ot_utility_getNbrTransactionCount()
{
    return execInt("{ var util = Utility(); util.getNbrTransactionCount(); }");
}

int OtMeExtra::ot_utility_getNbrTransactionCount()
{
    Utility util;
    return util.getNbrTransactionCount();
}


TEST_MOCK(ot_utility_setNbrTransactionCount)
{
    ASSERT_EQ(77, me.ot_utility_setNbrTransactionCount());
}

int OtMeChai::ot_utility_setNbrTransactionCount()
{
    return execInt("{ var util = Utility(); util.setNbrTransactionCount(77); util.getNbrTransactionCount(); }");
}

int OtMeExtra::ot_utility_setNbrTransactionCount()
{
    Utility util;
    util.setNbrTransactionCount(77);
    return util.getNbrTransactionCount();
}


TEST_MOCK(ot_utility_getLastReplyReceived)
{
    ASSERT_EQ("", me.ot_utility_getLastReplyReceived());
}

string OtMeChai::ot_utility_getLastReplyReceived()
{
    return execStr("{ var util = Utility(); util.getLastReplyReceived(); }");
}

string OtMeExtra::ot_utility_getLastReplyReceived()
{
    Utility util;
    return util.getLastReplyReceived();
}


TEST_MOCK(ot_utility_setLastReplyReceived)
{
    ASSERT_EQ("test", me.ot_utility_setLastReplyReceived());
}

string OtMeChai::ot_utility_setLastReplyReceived()
{
    return execStr("{ var util = Utility(); util.setLastReplyReceived(\"test\"); util.getLastReplyReceived(); }");
}

string OtMeExtra::ot_utility_setLastReplyReceived()
{
    Utility util;
    util.setLastReplyReceived("test");
    return util.getLastReplyReceived();
}


TEST_MOCK(VerifyMessageSuccess)
{
    ASSERT_EQ(OT_ERROR, me.VerifyMessageSuccess(""));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));
    ASSERT_EQ(OT_TRUE, me.VerifyMessageSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(OT_FALSE, Message_GetSuccess(TOKEN_DATA));
    ASSERT_EQ(OT_FALSE, me.VerifyMessageSuccess(TOKEN_DATA));

	EXPECT_MOCK_STR(77, OT_ERROR, Message_GetSuccess(PURSE_DATA));
    ASSERT_EQ(OT_ERROR, me.VerifyMessageSuccess(PURSE_DATA));
}

int OtMeChai::VerifyMessageSuccess(const char * messageData)
{
    OTString code;
    code.Format("{ VerifyMessageSuccess(\"%s\"); }", messageData);
    return execInt(code.Get());
}

int OtMeExtra::VerifyMessageSuccess(const char * messageData)
{
    return ::VerifyMessageSuccess(messageData);
}


TEST_MOCK(VerifyMsgBalanceAgrmntSuccess)
{
    ASSERT_EQ(OT_ERROR, me.VerifyMsgBalanceAgrmntSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, ""));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
    ASSERT_EQ(OT_TRUE, me.VerifyMsgBalanceAgrmntSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));

	EXPECT_MOCK_RET(OT_FALSE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, TOKEN_DATA));
    ASSERT_EQ(OT_FALSE, me.VerifyMsgBalanceAgrmntSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, TOKEN_DATA));

	EXPECT_MOCK_STR(77, OT_ERROR, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
    ASSERT_EQ(OT_ERROR, me.VerifyMsgBalanceAgrmntSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
}

int OtMeChai::VerifyMsgBalanceAgrmntSuccess(const char * serverId, const char * nymId, const char * accountId, const char * messageData)
{
    OTString code;
    code.Format("{ VerifyMsgBalanceAgrmntSuccess(\"%s\", \"%s\", \"%s\", \"%s\"); }", serverId, nymId, accountId, messageData);
    return execInt(code.Get());
}

int OtMeExtra::VerifyMsgBalanceAgrmntSuccess(const char * serverId, const char * nymId, const char * accountId, const char * messageData)
{
    return ::VerifyMsgBalanceAgrmntSuccess(serverId, nymId, accountId, messageData);
}


TEST_MOCK(VerifyMsgTrnxSuccess)
{
    ASSERT_EQ(OT_ERROR, me.VerifyMsgTrnxSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, ""));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
    ASSERT_EQ(OT_TRUE, me.VerifyMsgTrnxSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));

	EXPECT_MOCK_RET(OT_FALSE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, TOKEN_DATA));
    ASSERT_EQ(OT_FALSE, me.VerifyMsgTrnxSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, TOKEN_DATA));

	EXPECT_MOCK_STR(77, OT_ERROR, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
    ASSERT_EQ(OT_ERROR, me.VerifyMsgTrnxSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
}

int OtMeChai::VerifyMsgTrnxSuccess(const char * serverId, const char * nymId, const char * accountId, const char * messageData)
{
    OTString code;
    code.Format("{ VerifyMsgTrnxSuccess(\"%s\", \"%s\", \"%s\", \"%s\"); }", serverId, nymId, accountId, messageData);
    return execInt(code.Get());
}

int OtMeExtra::VerifyMsgTrnxSuccess(const char * serverId, const char * nymId, const char * accountId, const char * messageData)
{
    return ::VerifyMsgTrnxSuccess(serverId, nymId, accountId, messageData);
}


TEST_MOCK(InterpretTransactionMsgReply)
{
	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetBalanceAgreementSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
	
	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetTransactionSuccess(SERVER_ID, NYM_ID, ACCOUNT_ID, MESSAGE_DATA));
	
    ASSERT_MOCK_EQ(OT_ERROR, OT_TRUE, me.InterpretTransactionMsgReply(SERVER_ID, NYM_ID, ACCOUNT_ID, __FUNCTION__, MESSAGE_DATA));
}

int OtMeChai::InterpretTransactionMsgReply(const char * serverId, const char * nymId, const char * accountId, const char * attempt, const char * response)
{
    OTString code;
    code.Format("{ InterpretTransactionMsgReply(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\"); }", serverId, nymId, accountId, attempt, response);
    return execInt(code.Get());
}

int OtMeExtra::InterpretTransactionMsgReply(const char * serverId, const char * nymId, const char * accountId, const char * attempt, const char * response)
{
    return ::InterpretTransactionMsgReply(serverId, nymId, accountId, attempt, response);
}
