#include "stdafx.hpp"


TEST_MULTI(details_deposit_cheque)
{
	int returnValue = OT_ERROR;

	EXPECT_MULTI_RETURN("", ASSET_ID, Instrmnt_GetAssetID(PAYMENT_DATA));

	EXPECT_MULTI_RETURN("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

    EXPECT_MULTI_TRANSACTION(MESSAGE_DATA, depositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, PAYMENT_DATA));

    if (index >= 0)
	{
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


int OtMeChai::details_deposit_cheque(const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType)
{
	OTString code;
	code.Format("{ details_deposit_cheque(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\"); }",
				serverId, accountId, nymId, paymentData, paymentType);
	return execInt(code.Get());
}


int OtMeExtra::details_deposit_cheque(const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType)
{
	return ::details_deposit_cheque(serverId, accountId, nymId, paymentData, paymentType);
}


void OtMeTest::EXPECT_details_deposit_cheque(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType)
{
	EXPECT_MULTI_RETURN("", ASSET_ID, Instrmnt_GetAssetID(paymentData));

	if (index >= 0)
	{
		EXPECT_CALL_RETURN(ASSET_ID, GetAccountWallet_AssetTypeID(accountId));

		EXPECT_TRANSACTION_SNA(MESSAGE_DATA, depositCheque(serverId, nymId, accountId, paymentData), serverId, nymId, accountId);

		EXPECT_InterpretTransactionMsgReply(mock, noAltPathways, serverId, nymId, accountId);

		EXPECT_getIntermediaryFiles(mock, noAltPathways, serverId, nymId, accountId, true);
	}
}
