#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(get_payment_instrument_LoadDefaultInBox)
{
	EXPECT_MOCK_STR("", INBOX_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_STR(OT_ERROR, 1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));

	EXPECT_MOCK_STR("", INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA, 0));

	// defaults PRELOADED_INDEX to ""
	ASSERT_MOCK_EQ("", INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0, ""));
}

TEST_MOCK(get_payment_instrument_PreloadedInbox)
{
	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA, 0));

	ASSERT_EQ(INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0, INBOX_DATA));
}


void OtMeTest::EXPECT_get_payment_instrument(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, int paymentIndex, const char * inboxData)
{
	EXPECT_MOCK_STR(OT_ERROR, 1, Ledger_GetCount(serverId, nymId, nymId, inboxData));

	if (index >= 0)
	{
		EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(serverId, nymId, nymId, inboxData, paymentIndex));
	}
}
