#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(details_deposit_cheque)
{
	int returnValue = OT_ERROR;

	EXPECT_MOCK_STR("", ASSET_ID, Instrmnt_GetAssetID(PAYMENT_DATA));

	EXPECT_MOCK_STR("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	if (index >= 0)
	{
		EXPECT_TRANSACTION(MESSAGE_DATA, depositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, PAYMENT_DATA));

		OtMeTest::EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID);

		if (index >= 0)
		{
			returnValue = OT_TRUE;
			//FIX what if this one fails?
			OtMeTest::EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, true);
		}
	}

	ASSERT_EQ(returnValue, me.details_deposit_cheque(SERVER_ID, ACCOUNT_ID, NYM_ID, PAYMENT_DATA, PAYMENT_TYPE_CHEQUE));
}


int OtMeExtra::details_deposit_cheque(const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType)
{
	OTString code;
	code.Format("{ details_deposit_cheque(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\"); }",
				serverId, accountId, nymId, paymentData, paymentType);

	return ExecuteScript_ReturnInt(code.Get(), __FUNCTION__);
}


void OtMeTest::EXPECT_details_deposit_cheque(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType)
{
	EXPECT_MOCK_STR("", ASSET_ID, Instrmnt_GetAssetID(paymentData));

	if (index >= 0)
	{
		EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(accountId));

		EXPECT_TRANSACTION_SNA(serverId, nymId, accountId, MESSAGE_DATA, depositCheque(serverId, nymId, accountId, paymentData));

		EXPECT_InterpretTransactionMsgReply(mock, noAltPathways, serverId, nymId, accountId);

		EXPECT_getIntermediaryFiles(mock, noAltPathways, serverId, nymId, accountId, true);
	}
}
