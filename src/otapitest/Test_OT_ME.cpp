#include "stdafx.h"


#ifdef OLDCODE


#define ALLTESTS


#define EXPECT_MOCK(func) \
	EXPECT_CALL(mock, func)

#define EXPECT_MOCK_RET(ret, func) \
	EXPECT_CALL(mock, func).WillOnce(Return(ret))

#define EXPECT_REQUEST(func) \
	EXPECT_REQUEST_SN(SERVER_ID, NYM_ID, func)

#define EXPECT_REQUEST_SN(serverId, nymId, func) \
	EXPECT_MOCK(FlushMessageBuffer()); \
	EXPECT_MOCK_RET(REQUEST_NUMBER, func); \
	EXPECT_MOCK_RET(MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, serverId, nymId)); \
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

#define EXPECT_TRANSACTION(func) \
	EXPECT_TRANSACTION_SNA(SERVER_ID, NYM_ID, ACCOUNT_ID, func)

#define EXPECT_TRANSACTION_SNA(serverId, nymId, accountId, func) \
	EXPECT_getIntermediaryFiles(serverId, nymId, accountId, false); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_REQUEST_SN(serverId, nymId, func); \
	EXPECT_MOCK_RET(OT_TRUE, Message_GetBalanceAgreementSuccess(serverId, nymId, accountId, MESSAGE_DATA)); \
	EXPECT_MOCK_RET(OT_FALSE, Message_IsTransactionCanceled(serverId, nymId, accountId, MESSAGE_DATA)); \
	EXPECT_MOCK_RET(OT_TRUE, Message_GetTransactionSuccess(serverId, nymId, accountId, MESSAGE_DATA)); \
	EXPECT_getIntermediaryFiles(serverId, nymId, accountId, true);


static const char * ACCOUNT_FROM_ID				= "AccountFromIdxx";
static const char * ACCOUNT_ID					= "AccountIdxxxxxx";
static const char * ACCOUNT_TO_ID				= "AccountToIdxxxx";
static const char * AGENT_NAME					= "AgentName";
static const long   AMOUNT						= 1234;
static const char * ASSET_ID					= "AssetIdxxxxxxxx";
static const char * ASSET_NAME					= "AssetName";
static const int    BASKET_COUNT				= 1;
static const char * BASKET_DATA					= "BasketData";
static const int    BOX_TYPE_INBOX				= 1;
static const int    BOX_TYPE_NYMBOX				= 0;
static const int    BOX_TYPE_OUTBOX				= 2;
static const char * CONTRACT_DATA				= "ContractData";
static const char * CONTRACT_ID					= "ContractIdxxxxx";
static const char * ENCODED_MAP					= "EncodedMap";
static const char * INBOX_DATA					= "InboxData";
static const char * INDICES_ALL					= ""; //FIX note sometimes "all" is used. What's the difference?
static const char * INDICES_NONE				= "";
static const char * INDICES_ONE					= "0";
static const char * INDICES_TWO					= "0,1";
static const char * INSTRUMENT_DATA				= "InstrumentData";
static const char * INSTRUMENT_TO_DATA			= "InstrumentToData";
static const int    ITEM_TYPE_ALL				= 0;
static const int    ITEM_TYPE_TRANSFER			= 1;
static const int    ITEM_TYPE_RECEIPT			= 2;
static const int    LEDGER_COUNT				= 1;
static const char * LEDGER_DATA					= "LedgerData";
static const char * LEDGER_DATA2				= "LedgerData2";
static const char * LEDGER_DATA3				= "LedgerData3";
static const char * LEDGER_DATA4				= "LedgerData4";
static const char * LEDGER_DATA5				= "LedgerData5";
static const char * MARKET_ID					= "MarketId";
static const char * MEMO_TEXT					= "MemoText";
static const char * MESSAGE_DATA				= "MessageData";
static const char * MINT_DATA					= "MintData";
static const char * NYM_FROM_ID					= "NymFromIdxxxxxx";
static const char * NYM_HASH					= "NymHash";
static const char * NYM_HASH2					= "NymHash";
static const char * NYM_ID						= "NymIdxxxxxxxxxx";
static const char * NYM_NAME					= "NymName";
static const char * NYM_TO_ID					= "NymToIdxxxxxxxx";
static const int    OT_ERROR					= -1;
static const int    OT_FALSE					= 0;
static const int    OT_TRUE						= 1;
static const char * PAYMENT_DATA				= "PaymentData";
static const char * PAYMENT_PLAN				= "PaymentPlan";
static const char * PAYMENT_TYPE_ANY			= "ANY";
static const char * PAYMENT_TYPE_CHEQUE			= "CHEQUE";
static const char * PAYMENT_TYPE_INVOICE		= "INVOICE";
static const char * PAYMENT_TYPE_PAYMENT_PLAN	= "PAYMENT PLAN";
static const char * PAYMENT_TYPE_PURSE			= "PURSE";
static const char * PAYMENT_TYPE_SMARTCONTRACT	= "SMARTCONTRACT";
static const char * PAYMENT_TYPE_VOUCHER		= "VOUCHER";
static const char * PUBLIC_KEY					= "PublicKey";
static const char * PURSE_DATA					= "PurseData";
static const char * PURSE_DATA_EMPTY			= "PurseDataEmpty";
static const char * PURSE_DATA_FROM				= "PurseDataFrom";
static const char * PURSE_DATA_NEW				= "PurseDataNew";
static const char * PURSE_DATA_TO				= "PurseDataTo";
static const char * PURSE_FROM					= "PurseFrom";
static const char * PURSE_TO					= "PurseTo";
static const int    REQUEST_NUMBER				= 666;
static const char * SERVER_FROM_ID				= "ServerFromIdxxx";
static const char * SERVER_ID					= "ServerIdxxxxxxx";
static const char * SERVER_NAME					= "ServerName";
static const char * SMART_CONTRACT				= "SmartContract";
static const long   TIME_STAMP					= 20140213114322L;
static const char * TOKEN_DATA					= "TokenData";
static const char * TOKEN_FROM_ID				= "TokenFromIdxxx";
static const char * TOKEN_ID					= "TokenIdxxxxxxxx";
static const char * TOKEN_TO_ID					= "TokenToIdxxxxx";
static const int    TOKEN_SERIES				= 99;
static const int    TOKEN_VALUE					= 5678;
static const char * TRANSACTION_DATA			= "TransactionData";
static const int    TRANSACTION_NUMBER			= 345;


using namespace std;
using namespace testing;


class OtMeTest : public ::testing::Test
{
public:
	StrictMock<Mock_OTAPI_Exec> mock;
	OT_ME me;
	InSequence seq;

	time_t GetTime()
	{
		return mock.GetTime();
	}

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
		remove("C:/Users/Eric/AppData/Roaming/OpenTransactions/client_data/ot.pid");
	}

	void EXPECT_detailsDepositCheque(const char * serverId, const char * nymId, const char * accountId, const char * paymentData)
	{
		EXPECT_MOCK_RET(ASSET_ID, Instrmnt_GetAssetID(paymentData));

		EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(accountId));

		EXPECT_TRANSACTION_SNA(serverId, nymId, accountId, depositCheque(serverId, nymId, accountId, paymentData));

		EXPECT_InterpretTransactionMsgReply(serverId, nymId, accountId);

		EXPECT_getIntermediaryFiles(serverId, nymId, accountId, true);
	}

	void EXPECT_detailsExportCash(const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password)
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

	void EXPECT_detailsWithdrawCash(const char * accountId, const int64_t amount)
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

		EXPECT_TRANSACTION(notarizeWithdrawal(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));
	
		EXPECT_InterpretTransactionMsgReply(SERVER_ID, NYM_ID, ACCOUNT_ID);

		EXPECT_getIntermediaryFiles(SERVER_ID, NYM_ID, ACCOUNT_ID, false);
	}

	void EXPECT_getIntermediaryFiles(const char * serverId, const char * nymId, const char * accountId, bool bForced)
	{
		EXPECT_MOCK(FlushMessageBuffer());

		EXPECT_MOCK_RET(REQUEST_NUMBER, getAccountFiles(serverId, nymId, accountId));

		EXPECT_MOCK_RET(MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, serverId, nymId));

		EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

		EXPECT_MOCK_RET(LEDGER_DATA, LoadInboxNoVerify(serverId, nymId, accountId));

		EXPECT_MOCK_RET(true, VerifySignature(nymId, LEDGER_DATA));

		EXPECT_MOCK_RET(0, Ledger_GetCount(serverId, nymId, accountId, LEDGER_DATA));

		EXPECT_MOCK_RET(LEDGER_DATA, LoadOutboxNoVerify(serverId, nymId, accountId));

		EXPECT_MOCK_RET(true, VerifySignature(nymId, LEDGER_DATA));

		EXPECT_MOCK_RET(0, Ledger_GetCount(serverId, nymId, accountId, LEDGER_DATA));
	}

	void EXPECT_getNymBox(bool bForced)
	{
		EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));

		EXPECT_MOCK_RET(NYM_HASH, GetNym_NymboxHash(SERVER_ID, NYM_ID));

		if (bForced)
		{
			EXPECT_REQUEST(getNymbox(SERVER_ID, NYM_ID));
		}
	}

	void EXPECT_insureHaveAllBoxReceipts()
	{
		EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

		EXPECT_MOCK_RET(true, VerifySignature(NYM_ID, LEDGER_DATA));

		EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));
	}

	void EXPECT_InterpretTransactionMsgReply(const char * serverId, const char * nymId, const char * accountId)
	{
		EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

		EXPECT_MOCK_RET(OT_TRUE, Message_GetBalanceAgreementSuccess(serverId, nymId, accountId, MESSAGE_DATA));

		EXPECT_MOCK_RET(OT_TRUE, Message_GetTransactionSuccess(serverId, nymId, accountId, MESSAGE_DATA));
	}
};


#ifdef ALLTESTS


// *** make_sure_enough_trans_nums

TEST_F(OtMeTest, make_sure_enough_trans_nums)
{
	EXPECT_MOCK_RET(1, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.make_sure_enough_trans_nums(1, SERVER_ID, NYM_ID));
}


TEST_F(OtMeTest, make_sure_enough_trans_nums_HasToGetMore)
{
	EXPECT_MOCK_RET(1, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	EXPECT_REQUEST(getTransactionNumber(SERVER_ID, NYM_ID));

	// getNymbox
	EXPECT_getNymBox(true);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(REQUEST_NUMBER, getRequest(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(NYM_HASH, GetNym_RecentHash(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(NYM_HASH, GetNym_NymboxHash(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(true, VerifySignature(NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(2, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.make_sure_enough_trans_nums(2, SERVER_ID, NYM_ID));
}


// *** register_nym

TEST_F(OtMeTest, register_nym)
{
	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(REQUEST_NUMBER, createUserAccount(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(REQUEST_NUMBER, getRequest(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.register_nym(SERVER_ID, NYM_ID));
}


// *** check_user

TEST_F(OtMeTest, check_user)
{
	EXPECT_REQUEST(checkUser(SERVER_ID, NYM_ID, NYM_ID));

	ASSERT_EQ(MESSAGE_DATA, me.check_user(SERVER_ID, NYM_ID, NYM_ID));
}


// *** create_pseudonym

TEST_F(OtMeTest, create_pseudonym)
{
	EXPECT_MOCK_RET(NYM_ID, CreateNym(2048, "NymSource", ""));

	ASSERT_EQ(NYM_ID, me.create_pseudonym(2048, "NymSource", ""));
}


// *** issue_asset_type

TEST_F(OtMeTest, issue_asset_type)
{
	EXPECT_REQUEST(issueAssetType(SERVER_ID, NYM_ID, CONTRACT_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.issue_asset_type(SERVER_ID, NYM_ID, CONTRACT_DATA));
}


// *** issue_basket_currency

TEST_F(OtMeTest, issue_basket_currency)
{
	EXPECT_REQUEST(issueBasket(SERVER_ID, NYM_ID, CONTRACT_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.issue_basket_currency(SERVER_ID, NYM_ID, CONTRACT_DATA));
}


// *** exchange_basket_currency

TEST_F(OtMeTest, exchange_basket_currency)
{
	EXPECT_MOCK_RET(0, Basket_GetMemberCount(BASKET_DATA));

	EXPECT_TRANSACTION(exchangeBasket(SERVER_ID, NYM_ID, ASSET_ID, BASKET_DATA, false));

	ASSERT_EQ(MESSAGE_DATA, me.exchange_basket_currency(SERVER_ID, NYM_ID, ASSET_ID, BASKET_DATA, ACCOUNT_ID, false));
}


// *** retrieve_contract

TEST_F(OtMeTest, retrieve_contract)
{
	EXPECT_REQUEST(getContract(SERVER_ID, NYM_ID, CONTRACT_ID));

	ASSERT_EQ(MESSAGE_DATA, me.retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID));
}


// *** load_or_retrieve_contract

TEST_F(OtMeTest, load_or_retrieve_contract)
{
	EXPECT_MOCK_RET(MESSAGE_DATA, LoadAssetContract(CONTRACT_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID));
}


TEST_F(OtMeTest, load_or_retrieve_contract_MustRetrieeve)
{
	EXPECT_MOCK_RET("", LoadAssetContract(CONTRACT_ID));

	EXPECT_REQUEST(getContract(SERVER_ID, NYM_ID, CONTRACT_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadAssetContract(CONTRACT_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID));
}


// *** create_asset_acct

TEST_F(OtMeTest, create_asset_acct)
{
	EXPECT_REQUEST(createAssetAccount(SERVER_ID, NYM_ID, CONTRACT_ID));

	ASSERT_EQ(MESSAGE_DATA, me.create_asset_acct(SERVER_ID, NYM_ID, CONTRACT_ID));
}


// *** stat_asset_account

TEST_F(OtMeTest, stat_asset_account)
{
	EXPECT_MOCK_RET("WalletName", GetAccountWallet_Name(ACCOUNT_ID));

	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(AMOUNT, GetAccountWallet_Balance(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_NAME, GetAssetType_Name(ASSET_ID));

	EXPECT_MOCK_RET(NYM_NAME, GetNym_Name(NYM_ID));

	EXPECT_MOCK_RET(SERVER_NAME, GetServer_Name(SERVER_ID));

	EXPECT_MOCK_RET("$12.34", FormatAmount(ASSET_ID, AMOUNT));

	std::string msgData = "   Balance: $12.34   (WalletName)\n"
						  "Account ID: AccountIdxxxxxx ( WalletName )\n"
						  "Asset Type: AssetIdxxxxxxxx ( AssetName )\n"
						  "Owner Nym:  NymIdxxxxxxxxxx ( NymName )\n"
						  "Server:     ServerIdxxxxxxx ( ServerName )";
	ASSERT_EQ(msgData, me.stat_asset_account(ACCOUNT_ID));
}


// *** retrieve_account

TEST_F(OtMeTest, retrieve_account_DefaultUnforced)
{
	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	// defaults to unforced version
	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID));
}


TEST_F(OtMeTest, retrieve_account_Forced)
{
	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_ID, ACCOUNT_ID, true);

	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, true));
}


TEST_F(OtMeTest, retrieve_account_Unforced)
{
	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	ASSERT_TRUE(me.retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, false));
}


// *** retrieve_nym

TEST_F(OtMeTest, retrieve_nym_DefaultForced)
{
	EXPECT_REQUEST(getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(true);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	// defaults to forced version
	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID));
}


TEST_F(OtMeTest, retrieve_nym_Forced)
{
	EXPECT_REQUEST(getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(true);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID, true));
}


TEST_F(OtMeTest, retrieve_nym_Unforced)
{
	EXPECT_REQUEST(getRequest(SERVER_ID, NYM_ID));

	EXPECT_getNymBox(false);

	EXPECT_insureHaveAllBoxReceipts();

	EXPECT_MOCK_RET(LEDGER_DATA, LoadNymboxNoVerify(SERVER_ID, NYM_ID));

	EXPECT_MOCK(FlushSentMessages(false, SERVER_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK(FlushMessageBuffer());

	EXPECT_MOCK_RET(0, processNymbox(SERVER_ID, NYM_ID));

	ASSERT_TRUE(me.retrieve_nym(SERVER_ID, NYM_ID, false));
}


// *** send_transfer

TEST_F(OtMeTest, send_transfer)
{
	EXPECT_TRANSACTION(notarizeTransfer(SERVER_ID, NYM_ID, ACCOUNT_ID, ACCOUNT_TO_ID, AMOUNT, "Note"));

	ASSERT_EQ(MESSAGE_DATA, me.send_transfer(SERVER_ID, NYM_ID, ACCOUNT_ID, ACCOUNT_TO_ID, AMOUNT, "Note"));
}


// *** process_inbox

TEST_F(OtMeTest, process_inbox)
{
	EXPECT_TRANSACTION(processInbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.process_inbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));
}


// *** accept_inbox_items

TEST_F(OtMeTest, accept_inbox_items_Fail_NoNym)
{
	EXPECT_MOCK_RET("", GetAccountWallet_NymID(ACCOUNT_ID));

	ASSERT_FALSE(me.accept_inbox_items(ACCOUNT_ID, ITEM_TYPE_ALL, INDICES_ALL));
}


TEST_F(OtMeTest, accept_inbox_items_Fail_NoServer)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET("", GetAccountWallet_ServerID(ACCOUNT_ID));

	ASSERT_FALSE(me.accept_inbox_items(ACCOUNT_ID, ITEM_TYPE_ALL, INDICES_ALL));
}


TEST_F(OtMeTest, accept_inbox_items_Fail_HasEmptyInbox)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	EXPECT_MOCK_RET(10, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadInbox(SERVER_ID, NYM_ID, ACCOUNT_ID));

	EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

	ASSERT_FALSE(me.accept_inbox_items(ACCOUNT_ID, ITEM_TYPE_ALL, INDICES_ALL));
}


TEST_F(OtMeTest, accept_inbox_items_HasOneTransactionInInbox)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_ID, ACCOUNT_ID, false);

	EXPECT_MOCK_RET(10, GetNym_TransactionNumCount(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadInbox(SERVER_ID, NYM_ID, ACCOUNT_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(TRANSACTION_DATA, Ledger_GetTransactionByIndex(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA, 0));

	EXPECT_MOCK_RET(LEDGER_DATA2, Ledger_CreateResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(LEDGER_DATA3, Transaction_CreateResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA2, TRANSACTION_DATA, true));

	EXPECT_MOCK_RET(LEDGER_DATA4, Ledger_FinalizeResponse(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA3));

	EXPECT_TRANSACTION(processInbox(SERVER_ID, NYM_ID, ACCOUNT_ID, LEDGER_DATA4));

	EXPECT_InterpretTransactionMsgReply(SERVER_ID, NYM_ID, ACCOUNT_ID);

	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_ID, ACCOUNT_ID, true);

	ASSERT_TRUE(me.accept_inbox_items(ACCOUNT_ID, ITEM_TYPE_ALL, INDICES_ALL));
}


// *** discard_incoming_payments

TEST_F(OtMeTest, discard_incoming_payments_Fail_NoIndices)
{
	ASSERT_FALSE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_NONE));
}


TEST_F(OtMeTest, discard_incoming_payments_Fail_EmptyLedger)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(0, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	ASSERT_FALSE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_ONE));
}


TEST_F(OtMeTest, discard_incoming_payments_HasOneIndices)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(1, NumList_Count(INDICES_ONE));

	EXPECT_MOCK_RET(true, NumList_VerifyQuery(INDICES_ONE, "0"));

	EXPECT_MOCK_RET(true, RecordPayment(SERVER_ID, NYM_ID, true, 0, false));

	ASSERT_TRUE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_ONE));
}


TEST_F(OtMeTest, discard_incoming_payments_HasTwoIndices)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(2, NumList_Count(INDICES_TWO));

	//FIX note the complex interaction in otcommands.ot line 816
	//    we need many more unit tests
	EXPECT_MOCK_RET(true, NumList_VerifyQuery(INDICES_TWO,"0"));

	EXPECT_MOCK_RET(true, RecordPayment(SERVER_ID, NYM_ID, true, 0, false));

	ASSERT_TRUE(me.discard_incoming_payments(SERVER_ID, NYM_ID, INDICES_TWO));
}


// *** cancel_outgoing_payments

TEST_F(OtMeTest, cancel_outgoing_payments_Fail_OutboxEmpty)
{
	EXPECT_MOCK_RET(0, NumList_Count(INDICES_NONE));

	EXPECT_MOCK_RET(0, GetNym_OutpaymentsCount(NYM_ID));

	ASSERT_FALSE(me.cancel_outgoing_payments(NYM_ID, ACCOUNT_ID, INDICES_NONE));
}


TEST_F(OtMeTest, cancel_outgoing_payments_HasPaymentInOutbox)
{
	EXPECT_MOCK_RET(0, NumList_Count(INDICES_NONE));

	EXPECT_MOCK_RET(1, GetNym_OutpaymentsCount(NYM_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetNym_OutpaymentsServerIDByIndex(NYM_ID, 0));

	EXPECT_MOCK_RET(PAYMENT_DATA, GetNym_OutpaymentsContentsByIndex(NYM_ID, 0));

	//FIX definitely tinker with these
	EXPECT_MOCK_RET(PAYMENT_TYPE_CHEQUE, Instrmnt_GetType(PAYMENT_DATA));

	EXPECT_MOCK_RET(ACCOUNT_ID, Instrmnt_GetSenderAcctID(PAYMENT_DATA));

	EXPECT_MOCK_RET(NYM_ID, Instrmnt_GetSenderUserID(PAYMENT_DATA));

	EXPECT_detailsDepositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, PAYMENT_DATA);

	//FIX highlight the fact that ACCOUNT_ID is not used by using ACCOUNT_FROM_ID
	ASSERT_TRUE(me.cancel_outgoing_payments(NYM_ID, ACCOUNT_FROM_ID, INDICES_NONE));
}


// *** accept_from_paymentbox

TEST_F(OtMeTest, accept_from_paymentbox_HasEmptyLedger)
{
	const int LEDGER_COUNT = 0;

	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_COUNT, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	ASSERT_EQ(OT_TRUE, me.accept_from_paymentbox(ACCOUNT_ID, INDICES_NONE, PAYMENT_TYPE_CHEQUE));
}


TEST_F(OtMeTest, accept_from_paymentbox_HasNonEmptyLedger)
{
	//FIX definitely tinker with these
	const int LEDGER_COUNT = 1;

	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(LEDGER_COUNT, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	// handle_payment_index
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(LEDGER_COUNT, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA, 0));

	//FIX definitely tinker with these
	EXPECT_MOCK_RET(PAYMENT_TYPE_CHEQUE, Instrmnt_GetType(INSTRUMENT_DATA));

	EXPECT_MOCK_RET(NYM_ID, Instrmnt_GetRecipientUserID(INSTRUMENT_DATA));

	EXPECT_MOCK_RET(ASSET_ID, Instrmnt_GetAssetID(INSTRUMENT_DATA));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	//FIX definitely tinker with these
	EXPECT_MOCK_RET(GetTime() - 864000000L, Instrmnt_GetValidFrom(INSTRUMENT_DATA)); // 10 days ago

	EXPECT_MOCK_RET(GetTime() + 864000000L, Instrmnt_GetValidTo(INSTRUMENT_DATA)); // 10 days ahead

	EXPECT_detailsDepositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, INSTRUMENT_DATA);

	ASSERT_EQ(OT_TRUE, me.accept_from_paymentbox(ACCOUNT_ID, INDICES_NONE, PAYMENT_TYPE_CHEQUE));
}


// *** load_public_encryption_key

TEST_F(OtMeTest, load_public_encryption_key_Pubkey)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_encryption_key(NYM_ID));
}


TEST_F(OtMeTest, load_public_encryption_key_UserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Encryption(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_encryption_key(NYM_ID));
}


// *** load_public_signing_key

TEST_F(OtMeTest, load_public_signing_key_Pubkey)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Signing(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_signing_key(NYM_ID));
}

TEST_F(OtMeTest, load_public_signing_key_UserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Signing(NYM_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_public_signing_key(NYM_ID));
}


// *** load_or_retrieve_encrypt_key

TEST_F(OtMeTest, load_or_retrieve_encrypt_key_LoadPubkey)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_encrypt_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_encrypt_key_LoadUserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Encryption(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_encrypt_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_encrypt_key_RetrievePubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

	//FIX overkill, EXPECT_REQUEST already did this
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_encrypt_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_encrypt_key_RetrieveUserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

	//FIX overkill, EXPECT_REQUEST already did this
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Encryption(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_encrypt_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_encrypt_key_Fail_All)
{
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

	//FIX overkill, EXPECT_REQUEST already did this
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET("", LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Encryption(NYM_TO_ID));

	ASSERT_EQ("", me.load_or_retrieve_encrypt_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


// *** load_or_retrieve_signing_key

TEST_F(OtMeTest, load_or_retrieve_signing_key_LoadPubkey)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Signing(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_signing_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_signing_key_LoadUserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_TO_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Signing(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_signing_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_signing_key_RetrievePubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Signing(NYM_TO_ID));

	EXPECT_REQUEST(checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

	//FIX overkill, EXPECT_REQUEST already did this
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Signing(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_signing_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_signing_key_RetrieveUserPubkey)
{
	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Signing(NYM_TO_ID));

	EXPECT_REQUEST(checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

	//FIX overkill, EXPECT_REQUEST already did this
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_TO_ID));

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadUserPubkey_Signing(NYM_TO_ID));

	ASSERT_EQ(PUBLIC_KEY, me.load_or_retrieve_signing_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


TEST_F(OtMeTest, load_or_retrieve_signing_key_Fail_All)
{
	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Signing(NYM_TO_ID));

	EXPECT_REQUEST(checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

	//FIX overkill, EXPECT_REQUEST already did this
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET("", LoadPubkey_Signing(NYM_TO_ID));

	EXPECT_MOCK_RET("", LoadUserPubkey_Signing(NYM_TO_ID));

	ASSERT_EQ("", me.load_or_retrieve_signing_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


// *** send_user_msg_pubkey

TEST_F(OtMeTest, send_user_msg_pubkey)
{
	EXPECT_REQUEST(sendUserMessage(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, MESSAGE_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.send_user_msg_pubkey(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, MESSAGE_DATA));
}


// *** send_user_pmnt_pubkey

TEST_F(OtMeTest, send_user_pmnt_pubkey)
{
	EXPECT_REQUEST(sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, INSTRUMENT_DATA, ""));

	ASSERT_EQ(MESSAGE_DATA, me.send_user_pmnt_pubkey(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, INSTRUMENT_DATA));
}


// *** send_user_cash_pubkey

TEST_F(OtMeTest, send_user_cash_pubkey)
{
	EXPECT_REQUEST(sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, INSTRUMENT_DATA, INSTRUMENT_TO_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.send_user_cash_pubkey(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, INSTRUMENT_DATA, INSTRUMENT_TO_DATA));
}


// *** send_user_msg

TEST_F(OtMeTest, send_user_msg)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(sendUserMessage(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, MESSAGE_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.send_user_msg(SERVER_ID, NYM_ID, NYM_TO_ID, MESSAGE_DATA));
}


// *** send_user_payment

TEST_F(OtMeTest, send_user_payment)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, INSTRUMENT_DATA, ""));

	ASSERT_EQ(MESSAGE_DATA, me.send_user_payment(SERVER_ID, NYM_ID, NYM_TO_ID, INSTRUMENT_DATA));
}


// *** send_user_cash

TEST_F(OtMeTest, send_user_cash)
{
	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, INSTRUMENT_DATA, INSTRUMENT_TO_DATA));

	ASSERT_EQ(MESSAGE_DATA, me.send_user_cash(SERVER_ID, NYM_ID, NYM_TO_ID, INSTRUMENT_DATA, INSTRUMENT_TO_DATA));
}


// *** withdraw_and_send_cash

TEST_F(OtMeTest, withdraw_and_send_cash_Fail_HasEmptyPurseEvenAfterCashWithdrawal)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	//FIX can do different things here
	EXPECT_MOCK_RET(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_detailsWithdrawCash(ACCOUNT_ID, AMOUNT);

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	EXPECT_MOCK_RET(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET("$12.34", FormatAmount(ASSET_ID, AMOUNT));

	ASSERT_FALSE(me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}


TEST_F(OtMeTest, withdraw_and_send_cash_HasEmptyPurseDoesCashWithdrawal)
{
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	//FIX can do different things here
	EXPECT_MOCK_RET(0, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_detailsWithdrawCash(ACCOUNT_ID, AMOUNT);

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	// note: we're trying to withdraw tokens totalling to the EXACT amount
	EXPECT_MOCK_RET(AMOUNT, Token_GetDenomination(SERVER_ID, ASSET_ID, TOKEN_DATA)); // instead of TOKEN_VALUE

	EXPECT_MOCK_RET(TOKEN_SERIES, Token_GetSeries(SERVER_ID, ASSET_ID, TOKEN_DATA));

	EXPECT_MOCK_RET(GetTime() - 864000000L, Token_GetValidFrom(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days ago

	EXPECT_MOCK_RET(GetTime() + 864000000L, Token_GetValidTo(SERVER_ID, ASSET_ID, TOKEN_DATA)); // 10 days aheas

	EXPECT_MOCK_RET("0", NumList_Add("", "0"));

	EXPECT_detailsExportCash(SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, "0", false);

	EXPECT_MOCK_RET(PUBLIC_KEY, LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_REQUEST(sendUserInstrument(SERVER_ID, NYM_ID, NYM_TO_ID, PUBLIC_KEY, PURSE_DATA_TO, PURSE_DATA_FROM));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	//FIX interesting extra call path here

	ASSERT_TRUE(me.withdraw_and_send_cash(ACCOUNT_ID, NYM_TO_ID, MEMO_TEXT, AMOUNT));
}


// *** get_payment_instrument

TEST_F(OtMeTest, get_payment_instrument_DefaultPreloadedInboxNone)
{
	EXPECT_MOCK_RET(LEDGER_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, LEDGER_DATA, 0));

	// defaults PRELOADED_INDEX to ""
	ASSERT_EQ(INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0));
}

TEST_F(OtMeTest, get_payment_instrument_PreloadedInboxNone)
{
	EXPECT_MOCK_RET(INBOX_DATA, LoadPaymentInbox(SERVER_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA, 0));

	ASSERT_EQ(INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0, ""));
}

TEST_F(OtMeTest, get_payment_instrument)
{
	EXPECT_MOCK_RET(1, Ledger_GetCount(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA));

	EXPECT_MOCK_RET(INSTRUMENT_DATA, Ledger_GetInstrument(SERVER_ID, NYM_ID, NYM_ID, INBOX_DATA, 0));

	ASSERT_EQ(INSTRUMENT_DATA, me.get_payment_instrument(SERVER_ID, NYM_ID, 0, INBOX_DATA));
}


// *** get_box_receipt

TEST_F(OtMeTest, get_box_receipt_Nymbox)
{
	EXPECT_REQUEST(getBoxReceipt(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER));

	ASSERT_EQ(MESSAGE_DATA, me.get_box_receipt(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_NYMBOX, TRANSACTION_NUMBER));
}

TEST_F(OtMeTest, get_box_receipt_Inbox)
{
	EXPECT_REQUEST(getBoxReceipt(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_INBOX, TRANSACTION_NUMBER));

	ASSERT_EQ(MESSAGE_DATA, me.get_box_receipt(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_INBOX, TRANSACTION_NUMBER));
}

TEST_F(OtMeTest, get_box_receipt_Outbox)
{
	EXPECT_REQUEST(getBoxReceipt(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_OUTBOX, TRANSACTION_NUMBER));

	ASSERT_EQ(MESSAGE_DATA, me.get_box_receipt(SERVER_ID, NYM_ID, ACCOUNT_ID, BOX_TYPE_OUTBOX, TRANSACTION_NUMBER));
}


// *** retrieve_mint

TEST_F(OtMeTest, retrieve_mint)
{
	EXPECT_REQUEST(getMint(SERVER_ID, NYM_ID, ASSET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}


// *** load_or_retrieve_mint

TEST_F(OtMeTest, load_or_retrieve_mint_Load)
{
	EXPECT_MOCK_RET(true, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}


TEST_F(OtMeTest, Lload_or_retrieve_mint_Retrieve)
{
	EXPECT_MOCK_RET(false, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_REQUEST(getMint(SERVER_ID, NYM_ID, ASSET_ID));

	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	EXPECT_MOCK_RET(true, Mint_IsStillGood(SERVER_ID, ASSET_ID));

	EXPECT_MOCK_RET(MESSAGE_DATA, LoadMint(SERVER_ID, ASSET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID));
}


// *** query_asset_types

TEST_F(OtMeTest, query_asset_types)
{
	EXPECT_REQUEST(queryAssetTypes(SERVER_ID, NYM_ID, ENCODED_MAP));

	ASSERT_EQ(MESSAGE_DATA, me.query_asset_types(SERVER_ID, NYM_ID, ENCODED_MAP));
}


// *** create_market_offer

TEST_F(OtMeTest, create_market_offer)
{
	//FIX seems unnecessary
	EXPECT_MOCK_RET(SERVER_ID, GetAccountWallet_ServerID(ACCOUNT_ID));

	//FIX seems unnecessary
	EXPECT_MOCK_RET(NYM_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_TRANSACTION(issueMarketOffer(ACCOUNT_ID, ACCOUNT_TO_ID, 1, 2, 10, AMOUNT, false, "", 0));

	ASSERT_EQ(MESSAGE_DATA, me.create_market_offer(ACCOUNT_ID, ACCOUNT_TO_ID, 1, 2, 10, AMOUNT, false, 0, "", 0));
}


// *** kill_market_offer

TEST_F(OtMeTest, kill_market_offer)
{
	EXPECT_TRANSACTION(killMarketOffer(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));

	ASSERT_EQ(MESSAGE_DATA, me.kill_market_offer(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));
}


// *** kill_payment_plan

TEST_F(OtMeTest, kill_payment_plan)
{
	EXPECT_TRANSACTION(killPaymentPlan(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));

	ASSERT_EQ(MESSAGE_DATA, me.kill_payment_plan(SERVER_ID, NYM_ID, ACCOUNT_ID, 9876));
}


// *** cancel_payment_plan

TEST_F(OtMeTest, cancel_payment_plan)
{
	EXPECT_MOCK_RET(ACCOUNT_ID, Instrmnt_GetRecipientAcctID(PAYMENT_PLAN));

	EXPECT_TRANSACTION(depositPaymentPlan(SERVER_ID, NYM_ID, PAYMENT_PLAN));

	ASSERT_EQ(MESSAGE_DATA, me.cancel_payment_plan(SERVER_ID, NYM_ID, PAYMENT_PLAN));
}


// *** activate_smart_contract

TEST_F(OtMeTest, activate_smart_contract)
{
	//FIX This one is called in OTAPI_Func itself? (otapi.ot line 365)
	EXPECT_MOCK_RET(1, SmartContract_CountNumsNeeded(SMART_CONTRACT, AGENT_NAME));

	EXPECT_TRANSACTION(activateSmartContract(SERVER_ID, NYM_ID, SMART_CONTRACT));

	//FIX AGENT_NAME is never used?
	ASSERT_EQ(MESSAGE_DATA, me.activate_smart_contract(SERVER_ID, NYM_ID, ACCOUNT_ID, AGENT_NAME, SMART_CONTRACT));
}


// *** trigger_clause

TEST_F(OtMeTest, trigger_clause)
{
	EXPECT_REQUEST(triggerClause(SERVER_ID, NYM_ID, 6767, "ClauseName", "Param"));

	ASSERT_EQ(MESSAGE_DATA, me.trigger_clause(SERVER_ID, NYM_ID, 6767, "ClauseName", "Param"));
}


// *** withdraw_cash

TEST_F(OtMeTest, withdraw_cash)
{
	EXPECT_TRANSACTION(notarizeWithdrawal(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));

	ASSERT_EQ(MESSAGE_DATA, me.withdraw_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, AMOUNT));
}


// *** easy_withdraw_cash

TEST_F(OtMeTest, easy_withdraw_cash)
{
	EXPECT_detailsWithdrawCash(ACCOUNT_ID, AMOUNT);

	ASSERT_EQ(1, me.easy_withdraw_cash(ACCOUNT_ID, AMOUNT));
}


// *** export_cash

TEST_F(OtMeTest, export_cash)
{
	EXPECT_detailsExportCash(SERVER_ID, NYM_FROM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false);

	std::string retainedCopy;
	ASSERT_EQ(PURSE_DATA_TO, me.export_cash(SERVER_ID, NYM_ID, ASSET_ID, NYM_TO_ID, INDICES_ONE, false, retainedCopy));
	ASSERT_EQ(PURSE_DATA_FROM, retainedCopy);
}


// *** withdraw_voucher

TEST_F(OtMeTest, withdraw_voucher)
{
	EXPECT_TRANSACTION(withdrawVoucher(SERVER_ID, NYM_ID, ACCOUNT_ID, NYM_TO_ID, "Memo", AMOUNT));

	ASSERT_EQ(MESSAGE_DATA, me.withdraw_voucher(SERVER_ID, NYM_ID, ACCOUNT_ID, NYM_TO_ID, "Memo", AMOUNT));
}


// *** pay_dividend

TEST_F(OtMeTest, pay_dividend)
{
	EXPECT_TRANSACTION(payDividend(SERVER_ID, NYM_ID, ACCOUNT_ID, ASSET_ID, "Memo", AMOUNT));

	ASSERT_EQ(MESSAGE_DATA, me.pay_dividend(SERVER_ID, NYM_ID, ACCOUNT_ID, ASSET_ID, "Memo", AMOUNT));
}


// *** deposit_cheque

TEST_F(OtMeTest, deposit_cheque)
{
	EXPECT_TRANSACTION(depositCheque(SERVER_ID, NYM_ID, ACCOUNT_ID, "Cheque"));

	ASSERT_EQ(MESSAGE_DATA, me.deposit_cheque(SERVER_ID, NYM_ID, ACCOUNT_ID, "Cheque"));
}


// *** deposit_cash

TEST_F(OtMeTest, deposit_cash)
{
	// calls details_deposit_purse with INDICES empty

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	// note that if PURSE_DATA is empty then it will load the local account purse
	//EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	// when PURSE_DATA is different from local account purse a warning will be printed

	// when purse was loaded, collect token id's via INDICES

	EXPECT_MOCK_RET(NYM_TO_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(false, Purse_HasPassword(SERVER_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

	EXPECT_MOCK_RET(PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	//EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	EXPECT_MOCK_RET(TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

	EXPECT_MOCK_RET(TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

	EXPECT_MOCK_RET(PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

	EXPECT_MOCK_RET(PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

	EXPECT_MOCK_RET(true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_NEW));

	EXPECT_TRANSACTION_SNA(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, notarizeDeposit(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, PURSE_DATA_TO));

	EXPECT_InterpretTransactionMsgReply(SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, false);

	ASSERT_EQ(1, me.deposit_cash(SERVER_ID, NYM_ID, ACCOUNT_ID, PURSE_DATA));
}


// *** deposit_local_purse

TEST_F(OtMeTest, deposit_local_purse)
{
	// calls details_deposit_purse with PURSE_DATA empty

	EXPECT_MOCK_RET(ASSET_ID, GetAccountWallet_AssetTypeID(ACCOUNT_ID));

	EXPECT_MOCK_RET(PURSE_DATA, LoadPurse(SERVER_ID, ASSET_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET(NYM_TO_ID, GetAccountWallet_NymID(ACCOUNT_ID));

	EXPECT_MOCK_RET(false, Purse_HasPassword(SERVER_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_TO, CreatePurse(SERVER_ID, ASSET_ID, NYM_TO_ID, NYM_ID));

	EXPECT_MOCK_RET(PURSE_FROM, CreatePurse(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID));

	EXPECT_MOCK_RET(1, Purse_Count(SERVER_ID, ASSET_ID, PURSE_DATA));

	EXPECT_MOCK_RET(TOKEN_DATA, Purse_Peek(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	EXPECT_MOCK_RET(PURSE_DATA_NEW, Purse_Pop(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA));

	//EXPECT_MOCK_RET(TOKEN_ID, Token_GetID(SERVER_ID, ASSET_ID, TOKEN_DATA));

	EXPECT_MOCK_RET(TOKEN_TO_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_TO_ID));

	EXPECT_MOCK_RET(TOKEN_FROM_ID, Token_ChangeOwner(SERVER_ID, ASSET_ID, TOKEN_DATA, NYM_ID, NYM_ID, NYM_ID));

	EXPECT_MOCK_RET(PURSE_DATA_TO, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_TO_ID, PURSE_TO, TOKEN_TO_ID));

	EXPECT_MOCK_RET(PURSE_DATA_FROM, Purse_Push(SERVER_ID, ASSET_ID, NYM_ID, NYM_ID, PURSE_FROM, TOKEN_FROM_ID));

	EXPECT_MOCK_RET(true, SavePurse(SERVER_ID, ASSET_ID, NYM_ID, PURSE_DATA_NEW));

	EXPECT_TRANSACTION_SNA(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, notarizeDeposit(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, PURSE_DATA_TO));

	EXPECT_InterpretTransactionMsgReply(SERVER_ID, NYM_TO_ID, ACCOUNT_ID);

	EXPECT_getIntermediaryFiles(SERVER_ID, NYM_TO_ID, ACCOUNT_ID, false);

	ASSERT_EQ(1, me.deposit_local_purse(SERVER_ID, NYM_ID, ACCOUNT_ID, INDICES_NONE));
}


// *** get_market_list

TEST_F(OtMeTest, get_market_list)
{
	EXPECT_REQUEST(getMarketList(SERVER_ID, NYM_ID));

	ASSERT_EQ(MESSAGE_DATA, me.get_market_list(SERVER_ID, NYM_ID));
}


// *** get_market_offers

TEST_F(OtMeTest, get_market_offers)
{
	EXPECT_REQUEST(getMarketOffers(SERVER_ID, NYM_ID, MARKET_ID, 5));

	ASSERT_EQ(MESSAGE_DATA, me.get_market_offers(SERVER_ID, NYM_ID, MARKET_ID, 5));
}


// *** get_nym_market_offers

TEST_F(OtMeTest, get_nym_market_offers)
{
	EXPECT_REQUEST(getNym_MarketOffers(SERVER_ID, NYM_ID));

	ASSERT_EQ(MESSAGE_DATA, me.get_nym_market_offers(SERVER_ID, NYM_ID));
}


// *** get_market_recent_trades

TEST_F(OtMeTest, get_market_recent_trades)
{
	EXPECT_REQUEST(getMarketRecentTrades(SERVER_ID, NYM_ID, MARKET_ID));

	ASSERT_EQ(MESSAGE_DATA, me.get_market_recent_trades(SERVER_ID, NYM_ID, MARKET_ID));
}


// *** adjust_usage_credits

TEST_F(OtMeTest, adjust_usage_credits)
{
	EXPECT_REQUEST(usageCredits(SERVER_ID, NYM_ID, NYM_TO_ID, 224488));

	ASSERT_EQ(MESSAGE_DATA, me.adjust_usage_credits(SERVER_ID, NYM_ID, NYM_TO_ID, "224488"));
}

#endif // ALLTESTS

#endif // OLDCODE
