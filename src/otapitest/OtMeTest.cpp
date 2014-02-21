#include "stdafx.h"

#include "OtMeTest.hpp"


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

void OtMeTest::TestAllPaths(TestFunc testFunc)
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

void OtMeTest::TestPositivePath(TestFunc testFunc)
{
	// follow max positive path
	index = INT_MAX;
	testFunc(mock, me, index);
}

void OtMeTest::EXPECT_detailsDepositCheque(const char * serverId, const char * nymId, const char * accountId, const char * paymentData)
{
	EXPECT_MOCK_RET(ASSET_ID, Instrmnt_GetAssetID(paymentData));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(accountId));

	EXPECT_TRANSACTION_SNA(serverId, nymId, accountId, MESSAGE_DATA, depositCheque(serverId, nymId, accountId, paymentData));

	EXPECT_InterpretTransactionMsgReply(mock, index, serverId, nymId, accountId);

	EXPECT_getIntermediaryFiles(mock, serverId, nymId, accountId, true);
}

void OtMeTest::EXPECT_detailsExportCash(const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password)
{
	EXPECT_MOCK_RET(CONTRACT_DATA, LoadAssetContract(ASSET_ID));

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	//FIX can do different things here
	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	EXPECT_MOCK_RET(true, NumList_VerifyQuery(indices, indices));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_RET(PURSE_DATA_EMPTY, Purse_Empty(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

	EXPECT_MOCK_RET(PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	EXPECT_MOCK_RET(TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

	EXPECT_MOCK_RET(TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

	EXPECT_MOCK_RET(PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

	EXPECT_MOCK_RET(PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

	EXPECT_MOCK_RET(true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_EMPTY));
}

void OtMeTest::EXPECT_detailsWithdrawCash(const char * accountId, const int64_t amount)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(CONTRACT_DATA, LoadAssetContract(ASSET_ID));

	//FIX alternate path here
	//EXPECT_REQUEST(getContract(SERVER_ID, NYM_ID, CONTRACT_DATA));

	//EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	//EXPECT_MOCK_RET(CONTRACT_DATA, LoadAssetContract(ASSET_ID));

	//FIX another possible alternate path
	EXPECT_MOCK_RET(true, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_MOCK_RET(MINT_DATA, LoadMint(SERVER_ID, ASSET_ID));

	EXPECT_TRANSACTION(MESSAGE_DATA, notarizeWithdrawal(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));
	
	EXPECT_InterpretTransactionMsgReply(mock, index, SERVER_ID, NYM_ID, ACCOUNT_ID);

	EXPECT_getIntermediaryFiles(mock, SERVER_ID, NYM_ID, ACCOUNT_ID, false);
}

void OtMeTest::EXPECT_getIntermediaryFiles(Mock_OTAPI_Exec & mock, const char * serverId, const char * nymId, const char * accountId, bool bForced)
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

void OtMeTest::EXPECT_load_or_retrieve_encrypt_key(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * nymToId)
{
	//NOTE: this function will only follow one negative pathway
	//FIX need to fully test it separately

	// always fail initial load
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(nymToId));
	EXPECT_MOCK_RET("", LoadUserPubkey_Encryption(nymToId));

	// always succeed checkUser
	EXPECT_REQUEST(MESSAGE_DATA, checkUser(serverId, nymId, nymToId));
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	// again, fail initial loading
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(nymToId));

	// finally we can follow a negative pathway
	EXPECT_MOCK_STR("", PUBLIC_KEY, LoadUserPubkey_Encryption(nymToId));
}
