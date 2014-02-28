#include "stdafx.h"
#include "OtMeTest.hpp"


int errorPathway = -1;
int noAltPathways = INT_MAX;

int OtMeTest::pathways = 0;
int OtMeTest::singles = 0;


OtMeTest::OtMeTest()
: mock(*new StrictMock<Mock_OTAPI_Exec>())
{
	// default behavior follows max positive path
	index = INT_MAX;

	savePathways = pathways;
}

OtMeTest::~OtMeTest()
{
	if (savePathways == pathways)
	{
		// normal test, is also a single pathway
		pathways++;
		singles++;
	}
	delete &mock;
}

time_t OtMeTest::GetTime()
{
	return mock.GetTime();
}

void OtMeTest::SetUp()
{
}

void OtMeTest::TearDown()
{
	remove("C:/Users/Eric/AppData/Roaming/OpenTransactions/client_data/ot.pid");
}

void OtMeTest::TestAllPathways(TestFunc testFunc)
{
	index = -1;
	for (int i = 0; index < 0; i++)
	{
		cout << "\n********** Pathway " << i << " **********\n\n";
		StrictMock<Mock_OTAPI_Exec> & mock = *new StrictMock<Mock_OTAPI_Exec>();
		index = i;
		testFunc(mock, me, index);
		delete &mock;
		pathways++;
	}
}

void OtMeTest::TestFullPathway(TestFunc testFunc)
{
	// follow max positive path
	index = INT_MAX;
	testFunc(mock, me, index);
}

void OtMeTest::EXPECT_details_withdraw_cash(Mock_OTAPI_Exec & mock, int & index, const char * accountId, const int64_t amount)
{
	EXPECT_MOCK_STR("", NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_STR("", ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_STR("", SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	if (index >= 0)
	{
		// force fail
		EXPECT_MOCK_RET("", LoadAssetContract(ASSET_ID));

		EXPECT_REQUEST(MESSAGE_DATA, getContract(SERVER_ID, NYM_ID, ASSET_ID));

		EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

		EXPECT_MOCK_STR("", CONTRACT_DATA, LoadAssetContract(ASSET_ID));

		EXPECT_MOCK_STR(true, false, Mint_IsStillGood(SERVER_ID, ASSET_ID));

		if (index >= 0)
		{
			EXPECT_REQUEST(MESSAGE_DATA, getMint(SERVER_ID, NYM_ID, ASSET_ID));

			EXPECT_MOCK_STR(OT_FALSE, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

			EXPECT_MOCK_STR(false, true, Mint_IsStillGood(SERVER_ID, ASSET_ID));
		}
		else
		{
			// make sure to take BOTH paths in next call
			index++;
		}

		EXPECT_MOCK_STR("", MINT_DATA, LoadMint(SERVER_ID, ASSET_ID));

		if (index >= 0)
		{
			EXPECT_TRANSACTION(MESSAGE_DATA, notarizeWithdrawal(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));

			EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID);

			if (index >= 0)
			{
				EXPECT_getIntermediaryFiles(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID, false);
			}
		}
	}
}

void OtMeTest::EXPECT_getIntermediaryFiles(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * accountId, bool bForced)
{
	EXPECT_REQUEST_SN(serverId, nymId, MESSAGE_DATA, getAccountFiles(serverId, nymId, accountId));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadInboxNoVerify(serverId, nymId, accountId));

	EXPECT_MOCK_RET(true, VerifySignature(nymId, LEDGER_DATA));

	EXPECT_MOCK_RET(0, Ledger_GetCount(serverId, nymId, accountId, LEDGER_DATA));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadOutboxNoVerify(serverId, nymId, accountId));

	EXPECT_MOCK_RET(true, VerifySignature(nymId, LEDGER_DATA));

	EXPECT_MOCK_RET(0, Ledger_GetCount(serverId, nymId, accountId, LEDGER_DATA));
}

void OtMeTest::EXPECT_getNymBox(bool bForced)
{
	EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(NYM_HASH, GetNym_NymboxHash(SERVER_ID, NYM_ID));

	if (bForced)
	{
		EXPECT_REQUEST(MESSAGE_DATA, getNymbox(SERVER_ID, NYM_ID));
	}
}

void OtMeTest::EXPECT_insureHaveAllBoxReceipts()
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(true, VerifySignature(NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));
}

void OtMeTest::EXPECT_InterpretTransactionMsgReply(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * accountId)
{
	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetBalanceAgreementSuccess(serverId, nymId, accountId, MESSAGE_DATA));

	EXPECT_MOCK_STR(OT_ERROR, OT_TRUE, Message_GetTransactionSuccess(serverId, nymId, accountId, MESSAGE_DATA));
}
