// ------------------------------------------------------------------
// This is a library written in OTScript, which makes the OT-API
// much easier to use from inside your own OTScripts, by providing
// a higher-level layer.
//
// Think of it as the "standard header" for using OT from a script.
//
// There is similar code to this in Java also, in the OTAPI_Func and
// Utility classes, in the Moneychanger project. They also make the
// OTAPI much easier to use, by providing a higher-level layer.
//
//  http://www.chaiscript.com/doxygen/namespace_chai_script___language.html
//

// *************************************************************************************

#include <stdafx.hpp>

#include "OTAPI.hpp"
#include "OT_ME.hpp"
#include "ot_command_ot.hpp"
#include "ot_made_easy_ot.hpp"
#include "ot_otapi_ot.hpp"
#include "ot_utility_ot.hpp"

string Args;
string HisAcct;
string HisNym;
string HisPurse;
string MyAcct;
string MyNym;
string MyPurse;
string Server;


/*
* FT:  I noticed a lot of code duplication, when sending messages and transaction
* requests. I could basically remove all that duplication, except there are a couple
* of OT_API calls inside each one, that are different, and that take different
* parameters.
* Best way to get around that, is to just make an object that will do the appropriate
* API call, and store the necessary parameters inside. (A "functor" aka function
* object.) Then pass it in as a parameter and trigger it at the appropriate time.
* (That's what this is.)
*/


/* public String   serverID;
public String   nymID, nymID2;
public String   assetID, assetID2;
public String   accountID;
public String   accountID2;
public String   basket;
public String   strData, strData2, strData3, strData4;
public boolean  bBool;
public int      nData;
public long     lData;
public int      nTransNumsNeeded;
public int      nRequestNum;
*/


OT_OTAPI_OT void OTAPI_Func::InitCustom()
{
    bBool = false;
    nData = 0;
    lData = int64_t(0);
    tData = OTAPI_Wrap::GetTime(); // So it gets created as a time_t
    tData = 0; // initialize it to 0.;
    nTransNumsNeeded = 0;
    nRequestNum = -1;
    funcType = NO_FUNC;
}


OTAPI_Func::OTAPI_Func() // 0 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 0 arguments.)\n");

    InitCustom();
}


OTAPI_Func::~OTAPI_Func()
{

}

OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID) // 3 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 3 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }


    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;
}


OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_strParam) // 4 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 4 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }
    if (!VerifyStringVal(p_strParam))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strParam"));
    }


    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;

    if (theType == ISSUE_BASKET)
    {
        basket = p_strParam;
    }
    else if ((theType == GET_MINT) || (theType == GET_CONTRACT) || (theType == CREATE_ASSET_ACCT))
    {
        assetID = p_strParam;
    }
    else if (theType == CHECK_USER)
    {
        nymID2 = p_strParam;
    }
    else if ((theType == DELETE_ASSET_ACCT))
    {
        accountID = p_strParam;
    }
    else if ((theType == ISSUE_ASSET_TYPE) || (theType == GET_MARKET_RECENT_TRADES) || (theType == QUERY_ASSET_TYPES))
    {
        strData = p_strParam;
    }
    else
    {
        OTAPI_Wrap::Output(0, "ERROR! WRONG TYPE passed to OTAPI_Func.OTAPI_Func()\n");
    }
}


OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_strParam, const string & p_strData) // 5 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 5 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID \n"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID \n"));
    }

    if (!VerifyStringVal(p_strParam))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strParam \n"));
    }

    if (!VerifyStringVal(p_strData))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strData \n"));
    }

    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;

    //if ((theType == KILL_MARKET_OFFER) || (theType == KILL_PAYMENT_PLAN) || (theType == PROCESS_INBOX) ||
    //   (theType == DEPOSIT_CASH) || (theType == DEPOSIT_CHEQUE) || (theType == WITHDRAW_CASH))

    if ((theType == KILL_MARKET_OFFER) || (theType == KILL_PAYMENT_PLAN) || (theType == PROCESS_INBOX) || (theType == DEPOSIT_CASH) || (theType == DEPOSIT_CHEQUE) || (theType == DEPOSIT_PAYMENT_PLAN))
    {
        accountID = p_strParam;
        strData = p_strData;
    }
    else if (theType == ADJUST_USAGE_CREDITS)
    {
        nymID2 = p_strParam; // target nym ID
        strData = p_strData; // adjustment (up or down.)
    }
    else if (theType == EXCHANGE_CASH)
    {
        assetID = p_strParam;
        strData = p_strData;
    }
    else
    {
        OTAPI_Wrap::Output(0, "ERROR! WRONG TYPE passed to OTAPI_Func.OTAPI_Func()\n");
    }
}

OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_strParam, const int64_t p_lData) // 5 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 5 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID \n"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID \n"));
    }

    if (!VerifyStringVal(p_strParam))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strParam \n"));
    }

    if (!VerifyIntVal(p_lData))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_lData l\n"));
    }


    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;

    //if ((theType == KILL_MARKET_OFFER) || (theType == KILL_PAYMENT_PLAN) || (theType == PROCESS_INBOX) ||
    //   (theType == DEPOSIT_CASH) || (theType == DEPOSIT_CHEQUE) || (theType == WITHDRAW_CASH))

    if (theType == WITHDRAW_CASH)
    {
        accountID = p_strParam;
        lData = p_lData;
    }
    else if (theType == GET_MARKET_OFFERS)
    {
        strData = p_strParam;
        lData = p_lData;
    }
    else
    {
        OTAPI_Wrap::Output(0, "ERROR! WRONG TYPE passed to OTAPI_Func.OTAPI_Func()\n");
    }
}


OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_nymID2, const string & p_strData, const string & p_strData2) // 6 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 6 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }
    if (!VerifyStringVal(p_nymID2))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID2"));
    }
    if (!VerifyStringVal(p_strData))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strData"));
    }
    if (!VerifyStringVal(p_strData2))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strData2"));
    }


    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;

    if ((theType == SEND_USER_MESSAGE) || (theType == SEND_USER_INSTRUMENT))
    {
        nymID2 = p_nymID2;
        strData = p_strData;
        strData2 = p_strData2;
    }
    /*

    OTAPI_Func(ot_Msg.TRIGGER_CLAUSE, SERVER_ID, NYM_ID, STR_TRANS_NUM, CLAUSE_NAME, STR_PARAM)
    */
    else if (theType == TRIGGER_CLAUSE)
    {
        strData = p_nymID2;
        strData2 = p_strData;
        strData3 = p_strData2;
    }
    else if (theType == ACTIVATE_SMART_CONTRACT)
    {
        //      OTAPI_Func(ot_Msg.ACTIVATE_SMART_CONTRACT, SERVER_ID, NYM_ID, ACCT_ID, AGENT_NAME, THE_SMART_CONTRACT)
        //          def OTAPI_Func::OTAPI_Func  (theType, p_serverID, p_nymID, p_nymID2, p_strData, p_strData2) // 6 args

        accountID = p_nymID2; // the "official" asset account of the party activating the contract.;
        strData = p_strData; // the agent's name for that party, as listed on the contract.;
        strData2 = p_strData2; // the smart contract itself.;

        int nNumsNeeded = OTAPI_Wrap::SmartContract_CountNumsNeeded(p_strData2, p_strData);

        if (VerifyIntVal(nNumsNeeded) && nNumsNeeded > 0)
        {
            nTransNumsNeeded = nNumsNeeded;
        }
    }
    else if (theType == GET_BOX_RECEIPT)
    {
        accountID = p_nymID2; // accountID (inbox/outbox) or NymID (nymbox) is passed here.;
        nData = to_int(p_strData);
        strData = p_strData2; // transaction number passed here as string;
    }
    else
    {
        OTAPI_Wrap::Output(0, "ERROR! WRONG TYPE passed to OTAPI_Func.OTAPI_Func() ERROR!!!!!!\n");
    }
}


OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_accountID, const string & p_strParam, const int64_t p_lData, const string & p_strData2) // 7 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 7 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }
    if (!VerifyStringVal(p_accountID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_accountID"));
    }
    if (!VerifyStringVal(p_strParam))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strParam"));
    }

    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;
    accountID = p_accountID;

    //      var theRequest := OTAPI_Func(ot_Msg.SEND_TRANSFER, SERVER_ID, NYM_ID, ACCT_FROM, ACCT_TO, AMOUNT, NOTE)
    if (theType == SEND_TRANSFER)
    {
        if (!VerifyIntVal(p_lData))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strData"));
        }
        if (!VerifyStringVal(p_strData2))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strData2"));
        }
        accountID2 = p_strParam;
        lData = p_lData; // long Amount;
        strData = p_strData2; // str  Note;
    }
    else
    {
        OTAPI_Wrap::Output(0, "ERROR! WRONG TYPE passed to OTAPI_Func.OTAPI_Func() ERROR!!!!!!\n");
    }
}

OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_accountID, const string & p_strParam, const string & p_strData, const int64_t p_lData2) // 7 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 7 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }
    if (!VerifyStringVal(p_accountID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_accountID"));
    }
    if (!VerifyStringVal(p_strParam))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strParam"));
    }

    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;
    accountID = p_accountID;

    //      var theRequest := OTAPI_Func(ot_Msg.WITHDRAW_VOUCHER, SERVER_ID, NYM_ID, ACCT_ID, RECIP_NYM_ID, STR_MEMO, STR_AMOUNT)
    if (theType == WITHDRAW_VOUCHER)
    {
        if (!VerifyStringVal(p_strData))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strData"));
        }
        if (!VerifyIntVal(p_lData2))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strData2"));
        }
        nymID2 = p_strParam; // str  Recipient Nym ID;
        strData = p_strData; // str  Memo;
        lData = p_lData2; // long Amount;
    }

    //      var theRequest := OTAPI_Func(ot_Msg.PAY_DIVIDEND, SERVER_ID, NYM_ID, SOURCE_ACCT_ID, SHARES_ASSET_ID, STR_MEMO, STR_AMOUNT_PER_SHARE)
    else if (theType == PAY_DIVIDEND)
    {
        if (!VerifyStringVal(p_strData))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strData"));
        }
        if (!VerifyIntVal(p_lData2))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strData2"));
        }
        assetID = p_strParam; // str  Shares Asset ID;
        strData = p_strData; // str  Memo;
        lData = p_lData2; // long Amount Per Share;
    }

    else
    {
        OTAPI_Wrap::Output(0, "ERROR! WRONG TYPE passed to OTAPI_Func.OTAPI_Func() ERROR!!!!!!\n");
    }
}

OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_accountID, const string & p_strParam, const string & p_strData, const string & p_strData2) // 7 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 7 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }
    if (!VerifyStringVal(p_accountID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_accountID"));
    }
    if (!VerifyStringVal(p_strParam))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_strParam"));
    }

    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = 1;
    bBool = false;
    accountID = p_accountID;

    if (theType == SEND_USER_INSTRUMENT)
    {
        if (!VerifyStringVal(p_accountID))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_accountID"));
        }
        if (!VerifyStringVal(p_strParam))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strParam"));
        }
        if (!VerifyStringVal(p_strData))
        {
            OTAPI_Wrap::Output(0, concat(strError, "p_strData"));
        }
        nymID2 = p_accountID; // Recipient Nym;
        strData = p_strParam; // Recipient pubkey;
        strData2 = p_strData; // Instrument for recipient.;
        accountID = p_strData2; // sender_instrument is attached here. (Optional.);
    }
    else
    {
        OTAPI_Wrap::Output(0, "ERROR! WRONG TYPE passed to OTAPI_Func.OTAPI_Func() ERROR!!!!!!\n");
    }
}


OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_assetID,  // 8 args
    const string & p_basket, const string & p_accountID, const bool p_bBool, const int p_nTransNumsNeeded)
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 8 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }
    if (!VerifyStringVal(p_assetID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_assetID"));
    }
    if (!VerifyStringVal(p_accountID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_accountID"));
    }
    if (!VerifyStringVal(p_basket))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_basket"));
    }


    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    nTransNumsNeeded = p_nTransNumsNeeded;
    bBool = p_bBool;
    assetID = p_assetID;
    basket = p_basket;
    accountID = p_accountID;
}


// CREATE_MARKET_OFFER
//
OTAPI_Func::OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & assetAccountID, const string & currencyAcctID, const string & scale, const string & minIncrement, const string & quantity, const string & price, const bool bSelling) // 10 args
{
    // OTAPI_Wrap::Output(0, "(Version of OTAPI_Func with 10 arguments.)\n");

    InitCustom();

    string strError = "ERROR! Empty string passed to OTAPI_Func.OTAPI_Func() as: ";
    if (!VerifyStringVal(p_serverID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_serverID"));
    }
    if (!VerifyStringVal(p_nymID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "p_nymID"));
    }
    if (!VerifyStringVal(assetAccountID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "assetAccountID"));
    }
    if (!VerifyStringVal(currencyAcctID))
    {
        OTAPI_Wrap::Output(0, concat(strError, "currencyAcctID"));
    }
    if (!VerifyStringVal(scale))
    {
        OTAPI_Wrap::Output(0, concat(strError, "scale"));
    }
    if (!VerifyStringVal(minIncrement))
    {
        OTAPI_Wrap::Output(0, concat(strError, "minIncrement"));
    }
    if (!VerifyStringVal(quantity))
    {
        OTAPI_Wrap::Output(0, concat(strError, "quantity"));
    }
    if (!VerifyStringVal(price))
    {
        OTAPI_Wrap::Output(0, concat(strError, "price"));
    }


    funcType = theType;
    serverID = p_serverID;
    nymID = p_nymID;
    accountID = assetAccountID;
    accountID2 = currencyAcctID;

    strData = scale;
    strData2 = minIncrement;
    strData3 = quantity;
    strData4 = price;

    strData5 = ""; // Will be set after this function is called, since there were too many arguments.

    bBool = bSelling;

    nTransNumsNeeded = 3; // An opening transaction number, plus another for each asset account, total of 3.
}


// **********************************************************************


OT_OTAPI_OT int OTAPI_Func::Run()
{
    // -1 means error, no message was sent.
    //  0 means NO error, yet still no message was sent.
    // >0 means (usually) the request number is being returned.
    //
    switch (funcType)
    {
    case CHECK_USER:
        return OTAPI_Wrap::checkUser(serverID, nymID, nymID2);
    case CREATE_USER_ACCT:
        return OTAPI_Wrap::createUserAccount(serverID, nymID);
    case DELETE_USER_ACCT:
        return OTAPI_Wrap::deleteUserAccount(serverID, nymID);
    case SEND_USER_MESSAGE:
        return OTAPI_Wrap::sendUserMessage(serverID, nymID, nymID2, strData, strData2);
    case SEND_USER_INSTRUMENT:
        // accountID stores here the sender's copy of the instrument, which is used only in the case of a cash purse.
        return OTAPI_Wrap::sendUserInstrument(serverID, nymID, nymID2, strData, strData2, accountID);
    case GET_NYM_MARKET_OFFERS:
        return OTAPI_Wrap::getNym_MarketOffers(serverID, nymID);
    case CREATE_ASSET_ACCT:
        return OTAPI_Wrap::createAssetAccount(serverID, nymID, assetID);
    case DELETE_ASSET_ACCT:
        return OTAPI_Wrap::deleteAssetAccount(serverID, nymID, accountID);
    case ACTIVATE_SMART_CONTRACT:
        return OTAPI_Wrap::activateSmartContract(serverID, nymID, strData2);
    case TRIGGER_CLAUSE:
        return OTAPI_Wrap::triggerClause(serverID, nymID, to_long(strData), strData2, strData3);
    case EXCHANGE_BASKET:
        return OTAPI_Wrap::exchangeBasket(serverID, nymID, assetID, basket, bBool);
    case GET_CONTRACT:
        return OTAPI_Wrap::getContract(serverID, nymID, assetID);
    case GET_MINT:
        return OTAPI_Wrap::getMint(serverID, nymID, assetID);
    case QUERY_ASSET_TYPES:
        return OTAPI_Wrap::queryAssetTypes(serverID, nymID, strData);
    case ISSUE_ASSET_TYPE:
        return OTAPI_Wrap::issueAssetType(serverID, nymID, strData);
    case ISSUE_BASKET:
        return OTAPI_Wrap::issueBasket(serverID, nymID, basket);
    case EXCHANGE_CASH:
        return OTAPI_Wrap::exchangePurse(serverID, assetID, nymID, strData);
    case KILL_MARKET_OFFER:
        return OTAPI_Wrap::killMarketOffer(serverID, nymID, accountID, to_long(strData));
    case KILL_PAYMENT_PLAN:
        return OTAPI_Wrap::killPaymentPlan(serverID, nymID, accountID, to_long(strData));
    case GET_BOX_RECEIPT:
        return OTAPI_Wrap::getBoxReceipt(serverID, nymID, accountID, nData, to_long(strData));
    case PROCESS_INBOX:
        return OTAPI_Wrap::processInbox(serverID, nymID, accountID, strData);
    case DEPOSIT_CASH:
        return OTAPI_Wrap::notarizeDeposit(serverID, nymID, accountID, strData);
    case DEPOSIT_CHEQUE:
        return OTAPI_Wrap::depositCheque(serverID, nymID, accountID, strData);
    case DEPOSIT_PAYMENT_PLAN:
        return OTAPI_Wrap::depositPaymentPlan(serverID, nymID, strData);
    case WITHDRAW_CASH:
        return OTAPI_Wrap::notarizeWithdrawal(serverID, nymID, accountID, lData);
    case WITHDRAW_VOUCHER:
        return OTAPI_Wrap::withdrawVoucher(serverID, nymID, accountID, nymID2, strData, lData);
    case PAY_DIVIDEND:
        return OTAPI_Wrap::payDividend(serverID, nymID, accountID, assetID, strData, lData);
    case SEND_TRANSFER:
        return OTAPI_Wrap::notarizeTransfer(serverID, nymID, accountID, accountID2, lData, strData);
    case GET_MARKET_LIST:
        return OTAPI_Wrap::getMarketList(serverID, nymID);
    case GET_MARKET_OFFERS:
        return OTAPI_Wrap::getMarketOffers(serverID, nymID, strData, lData);
    case GET_MARKET_RECENT_TRADES:
        return OTAPI_Wrap::getMarketRecentTrades(serverID, nymID, strData);
    case CREATE_MARKET_OFFER:
        return OTAPI_Wrap::issueMarketOffer(accountID, accountID2, to_long(strData), to_long(strData2), to_long(strData3), to_long(strData4), bBool, tData, strData5, lData);
    case ADJUST_USAGE_CREDITS:
        return OTAPI_Wrap::usageCredits(serverID, nymID, nymID2, to_long(strData));
    default:
        break;
    }

    OTAPI_Wrap::Output(0, "ERROR! OTAPI_Func.Send() activated, with bad function type: ");
    OTAPI_Wrap::Output(0, concat(to_string(funcType), "\n"));

    return -1;
}


// **********************************************************************


OT_OTAPI_OT int OTAPI_Func::SendRequestLowLevel(OTAPI_Func & theFunction, const string & IN_FUNCTION)
{
    Utility MsgUtil;
    string strLocation = concat("OTAPI_Func::SendRequestLowLevel: ", IN_FUNCTION);

    OTAPI_Wrap::FlushMessageBuffer();

    int nRun = theFunction.Run(); // <===== ATTEMPT TO SEND THE MESSAGE HERE...;

    if (nRun == -1)  // if the requestNumber returned by the send-attempt is -1, that means it DIDN'T SEND (error)
    {
        OTAPI_Wrap::Output(0, strLocation + ": Failed to send message due to error.\n");

        theFunction.nRequestNum = -1;
    }
    else if (nRun == 0) // if the requestNumber returned by the send-attempt is 0, it means no error, but nothing was sent. (Like processing an empty box.)
    {
        OTAPI_Wrap::Output(0, strLocation + ": Didn't send this message, but NO error occurred, either. (For example, a request to process an empty Nymbox will return 0, meaning, nothing was sent, but also no error occurred.)\n");

        theFunction.nRequestNum = 0;
    }
    else if (nRun == (-2)) // -2 is also possible at some future date. (If the request number won't fit in an int, this is returned and then you can retrieve the actual number via a separate call.)
    {
        OTAPI_Wrap::Output(0, strLocation + ": ERROR, not supported. (-2 was returned.)\n");

        // TODO: Have an OT API call here, which retrieves the request number
        // (It must be too large to fit into an integer, which is why this happened.)

        theFunction.nRequestNum = -1;
    }
    else
    {
        theFunction.nRequestNum = nRun;
    }

    // BY this point, we definitely have the request number, which means the
    // message was actually SENT. (At least.) This also means we can use nRun
    // later to query for a copy of that sent message (like if we need to clawback
    // the transaction numbers from it later, once we confirm whether the server
    // actually never got it.)
    //
    return theFunction.nRequestNum;
}

// **********************************************************************

OT_OTAPI_OT string OTAPI_Func::SendTransaction(OTAPI_Func & theFunction, const string & IN_FUNCTION)
{
    int nTotalRetries = 2;
    return SendTransaction(theFunction, IN_FUNCTION, nTotalRetries);
}

OT_OTAPI_OT string OTAPI_Func::SendTransaction(OTAPI_Func & theFunction, const string & IN_FUNCTION, const int nTotalRetries)
{
    Utility MsgUtil;
    string strLocation = concat("OTAPI_Func::SendTransaction: ", IN_FUNCTION);


    if (!MsgUtil.getIntermediaryFiles(theFunction.serverID, theFunction.nymID, theFunction.accountID, false)) // bForceDownload=false))
    {
        OTAPI_Wrap::Output(0, strLocation + ", getIntermediaryFiles returned false. (It couldn't download files that it needed.)\n");
        return "";
    }

    // **********************************************************************
    // GET TRANSACTION NUMBERS HERE IF NECESSARY.
    //
    int getnym_trnsnum_count = OTAPI_Wrap::GetNym_TransactionNumCount(theFunction.serverID, theFunction.nymID);
    int configTxnCount = MsgUtil.getNbrTransactionCount();
    bool b1 = (theFunction.nTransNumsNeeded > configTxnCount);
    int comparative = 0;

    if (b1)
    {
        comparative = theFunction.nTransNumsNeeded;
    }
    else
    {
        comparative = configTxnCount;
    }

    if (getnym_trnsnum_count < comparative)
    {
        OTAPI_Wrap::Output(0, strLocation + ", I don't have enough transaction numbers to perform this transaction. Grabbing more now...\n");
        MsgUtil.setNbrTransactionCount(comparative);
        MsgUtil.getTransactionNumbers(theFunction.serverID, theFunction.nymID);
        MsgUtil.setNbrTransactionCount(configTxnCount);
    }

    // second try
    getnym_trnsnum_count = OTAPI_Wrap::GetNym_TransactionNumCount(serverID, nymID);
    if (getnym_trnsnum_count < comparative) // try a second time.
    {
        OTAPI_Wrap::Output(0, strLocation + ", failure: MsgUtil.getTransactionNumbers. (Trying again...)\n");

        // (the final parameter, the 'false' is us telling getTransNumbers that
        // it can skip the first call to getTransNumLowLevel)
        //
        MsgUtil.setNbrTransactionCount(comparative);
        MsgUtil.getTransactionNumbers(serverID, nymID, false);
        MsgUtil.setNbrTransactionCount(configTxnCount);
    }

    // third try
    getnym_trnsnum_count = OTAPI_Wrap::GetNym_TransactionNumCount(serverID, nymID);
    if (getnym_trnsnum_count < comparative) // try a second time.
    {
        OTAPI_Wrap::Output(0, strLocation + ", failure: MsgUtil.getTransactionNumbers. (Trying again...)\n");

        // (the final parameter, the 'false' is us telling getTransNumbers that
        // it can skip the first call to getTransNumLowLevel)
        //
        MsgUtil.setNbrTransactionCount(comparative);
        MsgUtil.getTransactionNumbers(serverID, nymID, false);
        MsgUtil.setNbrTransactionCount(configTxnCount);
    }


    // Giving up, if still a failure by this point.
    //
    getnym_trnsnum_count = OTAPI_Wrap::GetNym_TransactionNumCount(theFunction.serverID, theFunction.nymID);

    if (getnym_trnsnum_count < comparative)
    {
        OTAPI_Wrap::Output(0, strLocation + ", third failure: MsgUtil.getTransactionNumbers. (Giving up.)\n");
        return "";
    }
    // ************************************************************************

    bool bCanRetryAfterThis = false;

    string strResult = SendRequestOnce(theFunction,
        IN_FUNCTION,
        true,   // bIsTransaction      = true;
        true,   // bWillRetryAfterThis = true
        bCanRetryAfterThis); // output


    if (VerifyStringVal(strResult))
    {
        OTAPI_Wrap::Output(0, " Getting Intermediary files.. \n");

        if (!MsgUtil.getIntermediaryFiles(theFunction.serverID, theFunction.nymID, theFunction.accountID, true)) // bForceDownload=true
        {
            OTAPI_Wrap::Output(0, strLocation + ", getIntermediaryFiles returned false. (After a success sending the transaction. Strange...)\n");
            return "";
        }

        return strResult; // success!;
    }


    //
    // Maybe we have an old Inbox or something.
    //


    // TODO!!  SECURITY:  This is where a GOOD CLIENT (vs. a test client)
    // will verify these intermediary files against your LAST SIGNED RECEIPT,
    // using OTAPI_Wrap::VerifySomethingorother().
    // See verifyFiles() at the bottom of this file.
    // Add some kind of warning Modal Dialog here, since it's actually
    // normal for a NEW account (never had any receipts yet.) But for
    // any other account, this should ALWAYS VERIFY!
    //
    // Another note: this should happen INSIDE the getIntermediaryFiles call itself,
    // and all similar calls.  You simply should not download those files,
    // without verifying them also. Otherwise you could end up signing
    // a future bad receipt, based on malicious, planted intermediary files.

    int nRetries = nTotalRetries;

    while ((nRetries > 0) && !VerifyStringVal(strResult) && bCanRetryAfterThis)
    {
        --nRetries;

        bool bWillRetryAfterThis = true;

        if ((nRetries == 0) || !bCanRetryAfterThis)
        {
            bWillRetryAfterThis = false;
        }

        strResult = SendRequestOnce(theFunction, IN_FUNCTION, true, bWillRetryAfterThis, bCanRetryAfterThis);


        // In case of failure, we want to get these before we re-try.
        // But in case of success, we also want to get these, so we can
        // see the results of our success. So we get these either way...
        //
        if (VerifyStringVal(strResult))
        {
            if (!MsgUtil.getIntermediaryFiles(theFunction.serverID, theFunction.nymID, theFunction.accountID, true)) // bForceDownload=true
            {
                OTAPI_Wrap::Output(0, strLocation + ", getIntermediaryFiles (loop) returned false even after successfully sending the transaction.\n");
                return "";
            }
            break;
        }

    } // while

    // Here we return strResult, for good or ill.
    //
    return strResult;
}


// **********************************************************************


OT_OTAPI_OT string OTAPI_Func::SendRequest(OTAPI_Func & theFunction, const string & IN_FUNCTION)
{
    Utility MsgUtil;

    bool bCanRetryAfterThis = false;

    string strResult = SendRequestOnce(theFunction, IN_FUNCTION, false,/*bIsTransaction=false*/ true, /* bWillRetryAfterThis=true*/ bCanRetryAfterThis);


    if (!VerifyStringVal(strResult) && bCanRetryAfterThis)
    {
        strResult = SendRequestOnce(theFunction, IN_FUNCTION, false, /* bIsTransaction=false;*/ false, /*bWillRetryAfterThis=false*/ bCanRetryAfterThis); // unused in this case, I suppose. It's still returned as output.
    }
    // Here we return strResult.
    //
    return strResult;
}


// **********************************************************************


OT_OTAPI_OT string OTAPI_Func::SendRequestOnce(OTAPI_Func & theFunction, const string & IN_FUNCTION, const bool bIsTransaction, const bool bWillRetryAfterThis, bool & bCanRetryAfterThis)
{
    Utility MsgUtil;
    string strLocation = concat("OTAPI_Func::SendRequestOnce: ", IN_FUNCTION);

    bCanRetryAfterThis = false;

    string strReply = "";
    int nlocalRequestNum = SendRequestLowLevel(theFunction, IN_FUNCTION); // <========   FIRST ATTEMPT!!!!!!;

    if ((nlocalRequestNum == -1) || (nlocalRequestNum == 0))
    {
        return "";
    }
    else // 1 and default.
    {
        if (nlocalRequestNum < -1)
        {
            return "";
        }

        strReply = MsgUtil.ReceiveReplyLowLevel(theFunction.serverID, theFunction.nymID, nlocalRequestNum, IN_FUNCTION); // <==== Here we RECEIVE the REPLY...;
    }

    // Below this point, we definitely have a request number.
    // (But not yet necessarily a reply...)
    //


    // nlocalRequestNum is positive and contains the request number from sending.
    //
    // nReplySuccess contains status of the REPLY to that sent message.
    // nReplySuccess contains:
    //   0 == FAILURE reply msg from server,
    //   1 == SUCCESS reply msg from server (transaction could be success or fail.)
    //  -1 == (ERROR)
    //
    // strReply contains the reply itself (or null.)
    //
    int nReplySuccess = VerifyMessageSuccess(strReply);

    bool bMsgReplyError = (!VerifyStringVal(strReply) || (nReplySuccess < 0));

    bool bMsgReplySuccess = (!bMsgReplyError && (nReplySuccess  > 0));
    bool bMsgReplyFailure = (!bMsgReplyError && (nReplySuccess == 0));


    bool bMsgBalanceError;
    bool bMsgBalanceSuccess;
    bool bMsgBalanceFailure;

    bool bMsgTransError;
    bool bMsgTransSuccess;
    bool bMsgTransFailure;


    bool bMsgAnyError;
    bool bMsgAnyFailure;

    bool bMsgAllSuccess;


    // If you EVER are in a situation where you have to harvest numbers
    // back, it will ONLY be for transactions, not normal messages. (Those
    // are the only ones that USE transaction numbers.)
    //
    int nTransSuccess;
    int nBalanceSuccess;
    //
    if (bIsTransaction) // This request contains a TRANSACTION...
    {
        if (bMsgReplySuccess) // If message was success, then let's see if the transaction was, too.
        {
            nBalanceSuccess = OTAPI_Wrap::Message_GetBalanceAgreementSuccess(theFunction.serverID, theFunction.nymID, theFunction.accountID, strReply);

            if (nBalanceSuccess > 0)
            {
                // Sometimes a transaction is sent that is meant to "fail" in order to cancel itself from
                // ever being run in the future. It's being cancelled. In that case, whether the server reply
                // itself is acknowledged or rejection, either way, IsCancelled() will be set to TRUE.
                // This is used when cancelling a cheque, or a payment plan, or a smart contract, so that it
                // can never be activated at some future time.
                //
                // Therefore when we see that IsCancelled is set to TRUE, we interpret it as a "success" as far
                // as the UI is concerned, even though behind the scenes, it is still "rejected" and transaction
                // numbers were harvested from it.
                //
                int nTransCancelled = 1;
                nTransCancelled = OTAPI_Wrap::Message_IsTransactionCanceled(theFunction.serverID, theFunction.nymID, theFunction.accountID, strReply);

                // If it's not cancelled, then we assume it's a normal transaction (versus a cancellation)
                // and we check for success/failure as normal...
                //
                if (1 != nTransCancelled)
                {
                    nTransSuccess = OTAPI_Wrap::Message_GetTransactionSuccess(theFunction.serverID, theFunction.nymID, theFunction.accountID, strReply);
                }
                else // If it WAS cancelled, then for the UI we say "Success" even though OT behind the scenes is harvesting as though it failed.
                {    // (Which is what we want to happen, in the case that a cancellation was performed.)
                    // This way, the UI won't go off doing a bunch of unnecessary retries for a "failed" transaction.
                    // (After all, if it was cancelled, then we know for a fact that all future retries will fail anyway.)
                    //
                    nTransSuccess = 1;
                }
            }
            else
            {
                nTransSuccess = -1;
            }
        }
        else
        {
            nBalanceSuccess = -1;
            nTransSuccess = -1;
        }
        // All of these booleans (except "error") represent RECEIVED ANSWERS from the server.
        // In other words, "failure" does not mean "failed to find message."
        // Rather, it means "DEFINITELY got a reply, and that reply says status==failure."
        //

        bMsgBalanceError = (!VerifyStringVal(strReply) || (nBalanceSuccess < 0));
        bMsgBalanceSuccess = (!bMsgReplyError && !bMsgBalanceError && (nBalanceSuccess  > 0));
        bMsgBalanceFailure = (!bMsgReplyError && !bMsgBalanceError && (nBalanceSuccess == 0));

        bMsgTransError = (!VerifyStringVal(strReply) || (nTransSuccess   < 0));
        bMsgTransSuccess = (!bMsgReplyError && !bMsgBalanceError && !bMsgTransError && (nTransSuccess  > 0));
        bMsgTransFailure = (!bMsgReplyError && !bMsgBalanceError && !bMsgTransError && (nTransSuccess == 0));


        bMsgAnyError = (bMsgReplyError || bMsgBalanceError || bMsgTransError);
        bMsgAnyFailure = (bMsgReplyFailure || bMsgBalanceFailure || bMsgTransFailure);

        bMsgAllSuccess = (bMsgReplySuccess && bMsgBalanceSuccess && bMsgTransSuccess);

    }
    else // it's NOT a transaction, but a normal message..
    {
        nBalanceSuccess = -1;
        nTransSuccess = -1;

        bMsgBalanceError = false;
        bMsgBalanceSuccess = false;
        bMsgBalanceFailure = false;

        bMsgTransError = false;
        bMsgTransSuccess = false;
        bMsgTransFailure = false;


        bMsgAnyError = (bMsgReplyError);
        bMsgAnyFailure = (bMsgReplyFailure);

        bMsgAllSuccess = (bMsgReplySuccess);

    }
    // ****************************************************************************

    // We know the message SENT. The above logic is about figuring out whether the reply message,
    // the transaction inside it, and the balance agreement inside that transaction, whether
    // any of those three things is a definite error, a definite failure, or a definite success.
    // (Any one of those things could be true, OR NOT, and we can only act as if they are, if we
    // have definitive proof in any of those cases.)
    //
    // The below logic is about what sort of REPLY we may have gotten (if anything.)
    // Without a definite reply we cannot claw back. But the Nymbox can show us this answer,
    // either now, or later...
    //
    if (bMsgAllSuccess)
    {
        // the Msg was a complete success, including the message
        // AND the transaction AND the balance agreement.
        // Therefore, there's DEFINITELY nothing to clawback.
        //
        // (Thus I RemoveSentMessage for the message, since
        // I'm totally done with it now. NO NEED TO HARVEST anything, either.)
        //
        //          var nRemoved = OTAPI_Wrap::RemoveSentMessage(Integer.toString(nlocalRequestNum), theFunction.serverID, theFunction.nymID);
        //
        // NOTE: The above call is unnecessary, since a successful reply means
        // we already received the successful server reply, and OT's "ProcessServerReply"
        // already removed the sent message from the sent buffer (so no need to do that here.)

        //          OTAPI_Wrap::Output(0, strLocation + ", SendRequestOnce(): OT_API_RemoveSentMessage: " + nRemoved);

        return strReply;

    }
    // In this case we want to grab the Nymbox and see if the replyNotice is there.
    // If it IS, then OT server DEFINITELY replied to it (the MESSAGE was a success,
    // whether the transaction inside of it was success or fail.) So we know bMsgReplySuccess
    // is true, if we find a replyNotice.
    // From there, we can also check for transaction success.
    //
    else if (bMsgAnyError || bMsgAnyFailure) // let's resync, and clawback whatever transaction numbers we might have used on the Request...
    {
        bool bWasGetReqSent = false;
        int nGetRequest = MsgUtil.getRequestNumber(theFunction.serverID, theFunction.nymID, bWasGetReqSent); // <==== RE-SYNC ATTEMPT...;

        // GET REQUEST WAS A SUCCESS.
        //
        if (bWasGetReqSent && (nGetRequest > 0)) // success
        {
            bCanRetryAfterThis = true;

            // But--if it was a TRANSACTION, then we're not done syncing yet!
            //
            if (bIsTransaction)
            {
                bCanRetryAfterThis = false;

                //
                // Maybe we have an old Inbox or something.
                // NEW CODE HERE FOR DEBUGGING (THIS BLOCK)
                //
                bool bForceDownload = true;
                if (!MsgUtil.getIntermediaryFiles(theFunction.serverID, theFunction.nymID, theFunction.accountID, bForceDownload)) // bForceDownload=true
                {
                    OTAPI_Wrap::Output(0, strLocation + ", getIntermediaryFiles returned false. (After a failure to send the transaction. Thus, I give up.)\n");
                    return "";
                }

                bool bWasFound = false;
                bool bWasSent = false;

                OTfourbool the_foursome(bMsgReplySuccess, bMsgReplyFailure, bMsgTransSuccess, bMsgTransFailure);

                bForceDownload = false;

                int nProcessNymboxResult = MsgUtil.getAndProcessNymbox_8(theFunction.serverID, theFunction.nymID, bWasSent, bForceDownload, nlocalRequestNum, bWasFound, bWillRetryAfterThis, the_foursome);

                // bHarvestingForRetry,// bHarvestingForRetry is INPUT, in the case nlocalRequestNum needs to be harvested before a flush occurs.


                //  bMsgReplySuccess,    // bMsgReplySuccess is INPUT, and is in case nlocalRequestNum needs to be HARVESTED before a FLUSH happens.
                //  bMsgReplyFailure,    // bMsgReplyFailure is INPUT, and is in case nlocalRequestNum needs to be HARVESTED before a FLUSH happens.
                //  bMsgTransSuccess,    // bMsgTransSuccess is INPUT, and is in case nlocalRequestNum needs to be HARVESTED before a FLUSH happens.
                //  bMsgTransFailure)    // Etc.

                //FIX: Add '(' and ')' here to silence warning. But where?
                if ((bWasSent && (1 == nProcessNymboxResult)) || !bWasSent && (0 == nProcessNymboxResult))// success processing Nymbox.
                {
                    bCanRetryAfterThis = true;
                }


                // This means a request number was returned, since the processNymbox failed,
                // and hasn't been properly harvested, so we either need to harvest it for a re-try,
                // or flush it.
                //
                else if (bWasSent && (nProcessNymboxResult > 1))
                {
                    string strNymbox = OTAPI_Wrap::LoadNymboxNoVerify(theFunction.serverID, theFunction.nymID); // FLUSH SENT MESSAGES!!!!  (AND HARVEST.);

                    // *******************************************************
                    if (VerifyStringVal(strNymbox))
                    {
                        OTAPI_Wrap::FlushSentMessages(false, /*harvesting-for-retry==OT_FALSE*/ theFunction.serverID, theFunction.nymID, strNymbox);
                    }
                }
            } // if (bIsTransaction)

        } // if getRequest was success.
        else
        {
            OTAPI_Wrap::Output(0, strLocation + ", Failure: Never got reply from server, so tried getRequest, and that failed too. (I give up.)\n");

            // Note: cannot harvest transaction nums here because I do NOT know for sure
            // whether the server has replied to the message or not! (Not until I successfully
            // download my Nymbox.) Therefore, do NOT harvest or flush, but hold back and wait
            // until the next attempt does a successful getNymbox and THEN do a "flush sent" after
            // that. (That's the time we'll know for SURE what happened to the original reply.)
            //
            // (Therefore LEAVE the sent message in the sent queue.)

            return "";
        }
    } // else if (bMsgAnyError || bMsgAnyFailure)


    // Returning an empty string.

    return "";
}


// used for passing and returning values when giving a
//lambda function to a loop function.
//
the_lambda_struct::the_lambda_struct()
{
}


OT_OTAPI_OT OTDB::OfferListNym * loadNymOffers(const string & serverID, const string & nymID)
{
    OTDB::OfferListNym * offerList = NULL;

    if (OTDB::Exists("nyms", serverID, "offers", nymID + ".bin"))
    {
        OTAPI_Wrap::Output(1, "Offers file exists... Querying nyms...\n");
        OTDB::Storable * storable = OTDB::QueryObject(OTDB::STORED_OBJ_OFFER_LIST_NYM, "nyms", serverID, "offers", nymID + ".bin");

        if (!VerifyStorable(storable, "OTDB::Storable"))
        {
            OTAPI_Wrap::Output(0, "Unable to verify storable object. Probably doesn't exist.\n");
            return NULL; // containing null or undef;
        }

        OTAPI_Wrap::Output(1, "QueryObject worked. Now dynamic casting from storable to a (nym) offerList...\n");
        offerList = dynamic_cast<OTDB::OfferListNym *>(storable);

        if (!VerifyStorable(offerList, "OTDB::OfferListNym"))
        {
            OTAPI_Wrap::Output(0, "Unable to dynamic cast a storable to a (nym) offerList.\n");
            return NULL;
        }
    }

    return offerList; // possibly containing the offerList (if success), or possibly containing a null/undef value (if failure.);
}


OT_OTAPI_OT MapOfMaps * convert_offerlist_to_maps(OTDB::OfferListNym & offerList)
{
    string strLocation = "convert_offerlist_to_maps";

    MapOfMaps * map_of_maps = NULL; // return value. (currently undefined or null or whatever. VerifyType("Map") will return false at this point.;
    
    // LOOP THROUGH THE OFFERS and sort them into a map_of_maps, key is: scale-assetID-currencyID
    // the value for each key is a sub-map, with the key: transaction ID and value: the offer data itself.
    //
    int nCount = offerList.GetOfferDataNymCount(); // size_t;
    int nTemp = nCount; // so it's created as size_t;

    if (VerifyIntVal(nCount) && (nCount > 0))
    {
        for (int nIndex = 0; nIndex < nCount; ++nIndex)
        {
            nTemp = nIndex; // convert from int to size_t;
            OTDB::OfferDataNym & offerData = *offerList.GetOfferDataNym(nTemp);

            if (!VerifyStorable(&offerData, "OTDB::OfferDataNym"))
            {
                OTAPI_Wrap::Output(0, strLocation + ": Unable to reference (nym) offerData on offerList, at index: " + to_string(nIndex) + "\n");
                return map_of_maps;
            }

            string strScale = to_string(offerData.scale);
            string strAssetTypeID = offerData.asset_type_id;
            string strCurrencyTypeID = offerData.currency_type_id;
            string strSellStatus = offerData.selling ? "SELL" : "BUY";
            string strTransactionID = offerData.transaction_id;

            string strMapKey = strScale + "-" + strAssetTypeID + "-" + strCurrencyTypeID;

            SubMap * sub_map = NULL;
            if (VerifyType(map_of_maps, "Map") && !map_of_maps->empty() && (map_of_maps->count(strMapKey) > 0))
            {
                sub_map = (*map_of_maps)[strMapKey];
            }

            if (VerifyType(sub_map, "Map")) // the submap already exists for this market.
            {
                OTAPI_Wrap::Output(1, strLocation + ": The sub-map already exists!\n");

                // Let's just add this offer to the existing submap
                // (There must be other offers already there for the same market,
                // since the submap already exists.)
                //
                // the sub_map for this market is mapped by BUY/SELL ==> the actual
                // offerData.
                //

                (*sub_map)[strTransactionID] = &offerData;
            }
            else // submap does NOT already exist for this market. (Create it...)
            {
                OTAPI_Wrap::Output(1, strLocation + ": The sub-map does NOT already exist!\n");
                //
                // Let's create the submap with this new offer, and add it
                // to the main map.
                //
                sub_map = new SubMap();
                (*sub_map)[strTransactionID] = &offerData;
                
                if (VerifyType(map_of_maps, "Map"))
                {
                    map_of_maps = new MapOfMaps;
                }
                (*map_of_maps)[strMapKey] = sub_map;
            }

            // Supposedly by this point I have constructed a map keyed by the market,
            // which returns a sub_map for each market. Each sub map uses the key "BUY"
            // or "SELL" and that points to the actual offer data. (Like a Multimap.)
            //
            // Therefore we have sorted out all the buys and sells for each market.
            // Later on, we can loop through the main map, and for each market, we can
            // loop through all the buys and sells.
        } // for (constructing the map_of_maps and all the sub_maps, so that the offers are sorted
        // by market and buy/sell status.
    }

    return map_of_maps;
}


OT_OTAPI_OT int output_nymoffer_data(OTDB::OfferDataNym & offer_data, const int nIndex, MapOfMaps & map_of_maps, SubMap & sub_map, the_lambda_struct & extra_vals) // if 10 offers are printed for the SAME market, nIndex will be 0..9
{ // extra_vals unused in this function, but not in others that share this parameter profile.
    // (It's used as a lambda.)

    string strScale = to_string(offer_data.scale);
    string strAssetTypeID = offer_data.asset_type_id;
    string strCurrencyTypeID = offer_data.currency_type_id;
    string strSellStatus = offer_data.selling ? "SELL" : "BUY";
    string strTransactionID = offer_data.transaction_id;
    string strAvailableAssets = to_string(to_int(offer_data.total_assets) - to_int(offer_data.finished_so_far));

    if (0 == nIndex) // first iteration! (Output a header.)
    {
        OTAPI_Wrap::Output(0, "Scale:\t\t" + strScale + "\n");
        OTAPI_Wrap::Output(0, "Asset:\t\t" + strAssetTypeID + "\n");
        OTAPI_Wrap::Output(0, "Currency:\t" + strCurrencyTypeID + "\n");
        OTAPI_Wrap::Output(0, "\nIndex\tTrans#\tType\tPrice\tAvailable\n");
    }

    //
    // Okay, we have the offer_data, so let's output it!
    //
    print(to_string(nIndex) + "\t" + offer_data.transaction_id + "\t" + strSellStatus + "\t" + offer_data.price_per_scale + "\t" + strAvailableAssets);

    return 1;
}


// If you have a buy offer, to buy silver for $30, and to sell silver for $35,
// what happens tomorrow when the market shifts, and you want to buy for $40 and
// sell for $45 ?
//
// Well, now you need to cancel certain sell orders from yesterday! Because why on
// earth would you want to sell silver for $35 while buying it for $40? (knotwork
// raised ) That would be buy-high, sell-low.
//
// Any rational trader would cancel the old $35 sell order before placing a new $40
// buy order!
//
// Similarly, if the market went DOWN such that my old offers were $40 buy / $45 sell,
// and my new offers are going to be $30 buy / $35 sell, then I want to cancel certain
// buy orders for yesterday. After all, why on earth would you want to buy silver for
// $40 meanwhile putting up a new sell order at $35! You would immediately just turn
// around, after buying something, and sell it for LESS?
//
// Since the user would most likely be forced anyway to do this, for reasons of self-interest,
// it will probably end up as the default behavior here.
//


// RETURN VALUE: extra_vals will contain a list of offers that need to be removed AFTER

OT_OTAPI_OT int find_strange_offers(OTDB::OfferDataNym & offer_data, const int nIndex, MapOfMaps & map_of_maps, SubMap & sub_map, the_lambda_struct & extra_vals) // if 10 offers are printed for the SAME market, nIndex will be 0..9
{
    string strLocation = "find_strange_offers";
    /*
    me: How about this — when you do "opentxs newoffer" I can alter that
    script to automatically cancel any sell offers for a lower amount
    than my new buy offer, if they're on the same market at the same scale.
    and vice versa. Vice versa meaning, cancel any bid offers for a higher
    amount than my new sell offer.

    knotwork: yeah that would work.

    So when placing a buy offer, check all the other offers I already have at the same scale,
    same asset and currency ID. (That is, the same "market" as denoted by strMapKey in "opentxs showmyoffers")
    For each, see if it's a sell offer and if so, if the amount is lower than the amount on
    the new buy offer, then cancel that sell offer from the market. (Because I don't want to buy-high, sell low.)

    Similarly, if placing a sell offer, then check all the other offers I already have at the
    same scale, same asset and currency ID, (the same "market" as denoted by strMapKey....) For
    each, see if it's a buy offer and if so, if the amount is higher than the amount of my new
    sell offer, then cancel that buy offer from the market. (Because I don't want some old buy offer
    for $10 laying around for the same stock that I'm SELLING for $8! If I dump 100 shares, I'll receive
    $800--I don't want my software to automatically turn around and BUY those same shares again for $1000!
    That would be a $200 loss.)

    This is done here. This function gets called once for each offer that's active for this Nym.
    extra_vals contains the relevant info we're looking for, and offer_data contains the current
    offer (as we loop through ALL this Nym's offers, this function gets called for each one.)
    So here we just need to compare once, and add to the list if the comparison matches.
    */
    /*
    attr the_lambda_struct::the_vector        // used for returning a list of something.
    attr the_lambda_struct::the_asset_acct    // for newoffer, we want to remove existing offers for the same accounts in certain cases.
    attr the_lambda_struct::the_currency_acct // for newoffer, we want to remove existing offers for the same accounts in certain cases.
    attr the_lambda_struct::the_scale         // for newoffer as well.
    attr the_lambda_struct::the_price         // for newoffer as well.
    attr the_lambda_struct::bSelling          // for newoffer as well.
    */
    OTAPI_Wrap::Output(4, strLocation + ": About to compare the new potential offer against one of the existing ones...");

    if ((extra_vals.the_asset_acct == offer_data.asset_acct_id) && (extra_vals.the_currency_acct == offer_data.currency_acct_id) && (extra_vals.the_scale == offer_data.scale))
    {
        OTAPI_Wrap::Output(4, strLocation + ": the account IDs and the scale match...");

        // By this point we know the current offer_data has the same asset acct, currency acct, and scale
        // as the offer we're comparing to all the rest.
        //
        // But that's not enough: we also need to compare some prices:
        //
        // So when placing a buy offer, check all the other offers I already have.
        // For each, see if it's a sell offer and if so, if the amount is lower than the amount on
        // the new buy offer, then cancel that sell offer from the market. (Because I don't want to buy-high, sell low.)
        //
        if (!extra_vals.bSelling && offer_data.selling && (to_int(offer_data.price_per_scale) < to_int(extra_vals.the_price)))
        {
            extra_vals.the_vector.push_back(offer_data.transaction_id);
        }
        // Similarly, when placing a sell offer, check all the other offers I already have.
        // For each, see if it's a buy offer and if so, if the amount is higher than the amount of my new
        // sell offer, then cancel that buy offer from the market.
        //
        else if (extra_vals.bSelling && !offer_data.selling && (to_int(offer_data.price_per_scale) > to_int(extra_vals.the_price)))
        {
            extra_vals.the_vector.push_back(offer_data.transaction_id);
        }
    }
    // We don't actually do the removing here, since we are still looping through the maps.
    // So we just add the IDs to a vector so that the caller can do the removing once this loop
    // is over.

    return 1;
}


OT_OTAPI_OT int iterate_nymoffers_sub_map(MapOfMaps & map_of_maps, SubMap & sub_map, LambdaFunc the_lambda)
{
    the_lambda_struct extra_vals;
    return iterate_nymoffers_sub_map(map_of_maps, sub_map, the_lambda, extra_vals);
}


// low level. map_of_maps and sub_map must be good. (assumed.)
//
// extra_vals allows you to pass any extra data you want into your
// lambda, for when it is called. (Like a functor.)
//
OT_OTAPI_OT int iterate_nymoffers_sub_map(MapOfMaps & map_of_maps, SubMap & sub_map, LambdaFunc the_lambda, the_lambda_struct & extra_vals)
{
    // the_lambda must be good (assumed) and must have the parameter profile like this sample:
    // def the_lambda(offer_data, nIndex, map_of_maps, sub_map, extra_vals) // if 10 offers are printed for the SAME market, nIndex will be 0..9

    string strLocation = "iterate_nymoffers_sub_map";

    // Looping through the map_of_maps, we are now on a valid sub_map in this iteration.
    // Therefore let's loop through the offers on that sub_map and output them!
    //
    //var range_sub_map = sub_map.range();

    if (!VerifyNotNull(&sub_map))
    {
        OTAPI_Wrap::Output(0, strLocation + ": No range retrieved from sub_map. It must be non-existent, I guess.\n");
        return -1;
    }
    if (sub_map.empty())
    {
        // Should never happen since we already made sure all the sub_maps
        // have data on them. Therefore if this range is empty now, it's a chaiscript
        // bug (extremely unlikely.)
        //
        OTAPI_Wrap::Output(0, strLocation + ": Error: A range was retrieved for the sub_map, but the range is empty.\n");
        return -1;
    }

    int nIndex = -1;
    for (SubMap::iterator it = sub_map.begin(); it != sub_map.end(); it++)
    {
        ++nIndex;
        //var offer_data_pair = range_sub_map.front();

        if (!VerifyNotNull(it->second))
        {
            OTAPI_Wrap::Output(0, strLocation + ": Looping through range_sub_map range, and first offer_data_pair fails to verify.\n");
            return -1;
        }

        OTDB::OfferDataNym & offer_data = *it->second;
        if (!VerifyStorable(&offer_data, "OTDB::OfferDataNym"))
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error: offer_data is not an OTDB::OfferDataNym.\n");
            return -1;
        }

        int nLambda = (*the_lambda)(offer_data, nIndex, map_of_maps, sub_map, extra_vals); // if 10 offers are printed for the SAME market, nIndex will be 0..9;
        if (-1 == nLambda)
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error: the_lambda failed.\n");
            return -1;
        }
    }
    sub_map.clear();

    return 1;
}


OT_OTAPI_OT int iterate_nymoffers_maps(MapOfMaps & map_of_maps, LambdaFunc the_lambda) // low level. map_of_maps must be good. (assumed.)
{
    the_lambda_struct extra_vals;
    return iterate_nymoffers_maps(map_of_maps, the_lambda, extra_vals);
}


// extra_vals allows you to pass any extra data you want into your
// lambda, for when it is called. (Like a functor.)
//
OT_OTAPI_OT int iterate_nymoffers_maps(MapOfMaps & map_of_maps, LambdaFunc the_lambda, the_lambda_struct & extra_vals) // low level. map_of_maps must be good. (assumed.)
{
    // the_lambda must be good (assumed) and must have the parameter profile like this sample:
    // def the_lambda(offer_data, nIndex, map_of_maps, sub_map, extra_vals) // if 10 offers are printed for the SAME market, nIndex will be 0..9

    string strLocation = "iterate_nymoffers_maps";

    // Next let's loop through the map_of_maps and output the offers for each market therein...
    //
    //var range_map_of_maps = map_of_maps.range();
    if (!VerifyType(&map_of_maps, "Map_Range"))
    {
        OTAPI_Wrap::Output(0, strLocation + ": No range retrieved from map_of_maps.\n");
        return -1;
    }
    if (map_of_maps.empty())
    {
        OTAPI_Wrap::Output(0, strLocation + ": A range was retrieved for the map_of_maps, but the range is empty.\n");
        return -1;
    }

    int nMainIndex = -1;
    for (MapOfMaps::iterator it = map_of_maps.begin(); it != map_of_maps.end(); it++)
    {
        ++nMainIndex; // so we can output a header on the FIRST one only.

        //var sub_map_pair = range_map_of_maps.front();
        if (!VerifyType(it->second, "Map_Pair"))
        {
            OTAPI_Wrap::Output(0, strLocation + ": Looping through map_of_maps range, and first sub_map_pair fails to verify.\n");
            return -1;
        }

        string strMapKey = it->first;

        SubMap & sub_map = *it->second;
        if (!VerifyNotNull(&sub_map))
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error: Sub_map is not a map. (Then how is it even here?? Submaps are only added based on existing offers.)\n");
            return -1;
        }
        if (sub_map.empty())
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error: Sub_map is empty (Then how is it even here?? Submaps are only added based on existing offers.)\n");
            return -1;
        }

        if (0 == nMainIndex) // this is the first iteration of the main output loop...
        {
            //          OTAPI_Wrap::Output(0, "\n** MY OFFERS **\n\n")
        }

        int nSubMap = iterate_nymoffers_sub_map(map_of_maps, sub_map, the_lambda, extra_vals);
        if (-1 == nSubMap)
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error: while trying to iterate_nymoffers_sub_map.\n");
            return -1;
        }
    }
    map_of_maps.clear();

    return 1;
}
