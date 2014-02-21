#ifndef _H_OTMETEST

#include "stdafx.h"


#define ALLTESTS


#define EXPECT_MOCK(func) \
	EXPECT_CALL(mock, func)

#define EXPECT_MOCK_FUNC(ret, func)	\
	{ EXPECT_MOCK(FlushMessageBuffer()); EXPECT_MOCK_RET(ret, func); }

#define EXPECT_MOCK_RET(ret, func) \
	EXPECT_CALL(mock, func).WillOnce(Return(ret))

#define EXPECT_REQUEST(data, func) \
	EXPECT_REQUEST_SN(SERVER_ID, NYM_ID, data, func)

#define EXPECT_REQUEST_SN(serverId, nymId, data, func) \
	EXPECT_MOCK_FUNC(REQUEST_NUMBER, func); \
	EXPECT_MOCK_RET(data, PopMessageBuffer(REQUEST_NUMBER, serverId, nymId)); \
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(data));

#define EXPECT_TRANSACTION(data, func) \
	EXPECT_TRANSACTION_SNA(SERVER_ID, NYM_ID, ACCOUNT_ID, data, func)

#define EXPECT_TRANSACTION_SNA(serverId, nymId, accountId, data, func) \
	OtMeTest::EXPECT_getIntermediaryFiles(mock, serverId, nymId, accountId, false); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_MOCK_RET(100, GetNym_TransactionNumCount(serverId, nymId)); \
	EXPECT_REQUEST_SN(serverId, nymId, data, func); \
	EXPECT_MOCK_RET(OT_TRUE, Message_GetBalanceAgreementSuccess(serverId, nymId, accountId, data)); \
	EXPECT_MOCK_RET(OT_FALSE, Message_IsTransactionCanceled(serverId, nymId, accountId, data)); \
	EXPECT_MOCK_RET(OT_TRUE, Message_GetTransactionSuccess(serverId, nymId, accountId, data)); \
	OtMeTest::EXPECT_getIntermediaryFiles(mock, serverId, nymId, accountId, true);


#define ASSERT_MOCK_EQ(fail, ret, func) \
	ASSERT_EQ((index >= 0 ? ret : fail), func);

#define EXPECT_MOCK_INT(fail, ret, func) \
	if (index-- >= 0) { EXPECT_MOCK_RET(index >= 0 ? ret : fail, func); }

#define EXPECT_MOCK_REQ(data, func) \
	if (index >= 0) { EXPECT_REQUEST(data, func); }

#define EXPECT_MOCK_REQUEST(data, func) \
	if (index-- >= 0) { if (index >= 0) { EXPECT_REQUEST(data, func); } \
	else { EXPECT_MOCK_FUNC(OT_ERROR, func); } }

#define EXPECT_MOCK_TRANSACTION(data, func) \
	if (index-- >= 0) { if (index >= 0) { EXPECT_TRANSACTION(data, func); } \
	else { EXPECT_MOCK_FUNC(OT_ERROR, getAccountFiles(SERVER_ID, NYM_ID, ACCOUNT_ID)); }	}

#define EXPECT_MOCK_SUB(func) \
	if (index >= 0) { EXPECT_MOCK(func); }

#define EXPECT_MOCK_STR(fail, ret, func) \
	if (index-- >= 0) { EXPECT_MOCK_RET(index >= 0 ? ret : fail, func); }

#define TEST_MOCK(name) \
	static void test_##name(Mock_OTAPI_Exec & mock, OT_ME & me, int & index); \
	TEST_F(OtMeTest, _##name) { TestAllPaths(test_##name); } \
	static void test_##name(Mock_OTAPI_Exec & mock, OT_ME & me, int & index)



static const char * ACCOUNT_FROM_ID				= "AccountFromId_______";
static const char * ACCOUNT_ID					= "AccountId___________";
static const char * ACCOUNT_TO_ID				= "AccountToId_________";
static const char * AGENT_NAME					= "AgentName___________";
static const long   AMOUNT						= 1234;
static const char * ASSET_ID					= "AssetId_____________";
static const char * ASSET_NAME					= "AssetName___________";
static const int    BASKET_COUNT				= 1;
static const char * BASKET_DATA					= "BasketData__________";
static const int    BOX_TYPE_INBOX				= 1;
static const int    BOX_TYPE_NYMBOX				= 0;
static const int    BOX_TYPE_OUTBOX				= 2;
static const char * CONTRACT_DATA				= "ContractData________";
static const char * CONTRACT_ID					= "ContractId__________";
static const char * ENCODED_MAP					= "EncodedMap__________";
static const char * INBOX_DATA					= "InboxData___________";
static const char * INDICES_ALL					= ""; //FIX note sometimes "all" is used. What's the difference?
static const char * INDICES_NONE				= "";
static const char * INDICES_ONE					= "0";
static const char * INDICES_TWO					= "0,1";
static const char * INSTRUMENT_DATA				= "InstrumentData______";
static const char * INSTRUMENT_TO_DATA			= "InstrumentToData____";
static const int    ITEM_TYPE_ALL				= 0;
static const int    ITEM_TYPE_TRANSFER			= 1;
static const int    ITEM_TYPE_RECEIPT			= 2;
static const int    LEDGER_COUNT				= 1;
static const char * LEDGER_DATA					= "LedgerData__________";
static const char * LEDGER_DATA2				= "LedgerData2_________";
static const char * LEDGER_DATA3				= "LedgerData3_________";
static const char * LEDGER_DATA4				= "LedgerData4_________";
static const char * LEDGER_DATA5				= "LedgerData5_________";
static const char * MARKET_ID					= "MarketId____________";
static const char * MEMO_TEXT					= "MemoText____________";
static const char * MESSAGE_DATA				= "MessageData_________";
static const char * MESSAGE_DATA2				= "MessageData22222____";
static const char * MINT_DATA					= "MintData____________";
static const char * NYM_FROM_ID					= "NymFromId___________";
static const char * NYM_HASH					= "NymHash_____________";
static const char * NYM_HASH2					= "NymHash_____________";
static const char * NYM_ID						= "NymId_______________";
static const char * NYM_NAME					= "NymName_____________";
static const char * NYM_TO_ID					= "NymToId_____________";
static const int    OT_ERROR					= -1;
static const int    OT_FALSE					= 0;
static const int    OT_TRUE						= 1;
static const char * PAYMENT_DATA				= "PaymentData_________";
static const char * PAYMENT_PLAN				= "PaymentPlan_________";
static const char * PAYMENT_TYPE_ANY			= "ANY";
static const char * PAYMENT_TYPE_CHEQUE			= "CHEQUE";
static const char * PAYMENT_TYPE_INVOICE		= "INVOICE";
static const char * PAYMENT_TYPE_PAYMENT_PLAN	= "PAYMENT PLAN";
static const char * PAYMENT_TYPE_PURSE			= "PURSE";
static const char * PAYMENT_TYPE_SMARTCONTRACT	= "SMARTCONTRACT";
static const char * PAYMENT_TYPE_VOUCHER		= "VOUCHER";
static const char * PUBLIC_KEY					= "PublicKey___________";
static const char * PURSE_DATA					= "PurseData___________";
static const char * PURSE_DATA_EMPTY			= "PurseDataEmpty______";
static const char * PURSE_DATA_FROM				= "PurseDataFrom_______";
static const char * PURSE_DATA_NEW				= "PurseDataNew________";
static const char * PURSE_DATA_TO				= "PurseDataTo_________";
static const char * PURSE_FROM					= "PurseFrom___________";
static const char * PURSE_TO					= "PurseTo_____________";
static const int    REQUEST_NUMBER				= 666;
static const char * SERVER_FROM_ID				= "ServerFromId________";
static const char * SERVER_ID					= "ServerId____________";
static const char * SERVER_NAME					= "ServerName__________";
static const char * SMART_CONTRACT				= "SmartContract_______";
static const long   TIME_STAMP					= 20140213114322L;
static const char * TOKEN_DATA					= "TokenData___________";
static const char * TOKEN_FROM_ID				= "TokenFromId_________";
static const char * TOKEN_ID					= "TokenId_____________";
static const char * TOKEN_TO_ID					= "TokenToId___________";
static const int    TOKEN_SERIES				= 99;
static const int    TOKEN_VALUE					= 5678;
static const char * TRANSACTION_DATA			= "TransactionData_____";
static const int    TRANSACTION_NUMBER			= 345;
static const char * WALLET_NAME					= "WalletName__________";


using namespace ::std;
using namespace ::testing;

class Mock_OTAPI_Exec;
class OT_ME;


typedef void (*TestFunc) (Mock_OTAPI_Exec & mock, OT_ME & me, int & index);

class OtMeTest : public Test
{
private:

	int savePathways;

public:

	static int pathways;
	static int singles;

	int index;

	OtMeTest();
	virtual ~OtMeTest();

	StrictMock<Mock_OTAPI_Exec> & mock;
	OT_ME me;
	InSequence seq;

	void EXPECT_detailsDepositCheque(const char * serverId, const char * nymId, const char * accountId, const char * paymentData);
	void EXPECT_detailsExportCash(const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password);
	void EXPECT_detailsWithdrawCash(const char * accountId, const int64_t amount);
	static void EXPECT_getIntermediaryFiles(Mock_OTAPI_Exec & mock, const char * serverId, const char * nymId, const char * accountId, bool bForced);
	void EXPECT_getNymBox(bool bForced);
	time_t GetTime();
	void EXPECT_insureHaveAllBoxReceipts();
	static void EXPECT_InterpretTransactionMsgReply(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * accountId);
	static void EXPECT_load_or_retrieve_encrypt_key(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char *nymToId);
	virtual void SetUp();
	virtual void TearDown();
	void TestAllPaths(TestFunc testFunc);
	void TestPositivePath(TestFunc testFunc);
};

#endif // _H_OTMETEST
