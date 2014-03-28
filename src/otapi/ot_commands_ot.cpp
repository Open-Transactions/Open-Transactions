// NEW RETURN CODE CONVENTION!

// OT API already returns: -1 for error, 0 for "didn't need to do anything" and 1 for success (or larger.)
// All of the below functions follow that convention (they just return the same values.)
//
// But for the OT command line tool, we need to return 0 for success, and non-zero codes for errors.
// This is because it's a UNIX convention and will be expected by anyone writing bash scripts.
//
// However, I don't want to physically change all the below functions, so I'm going to change the
// opentxs script itself, so that it translates the return value. That way I only have to change it
// in one spot, and we have access to use these scripts both ways.
//
// THE POINT? If you notice these scripts returning 1, which is then interpreted as 0 by bash scripts,
// it's because the script that CALLS these scripts, is doing that translation (for the above described
// reasons.)
//

#include <stdafx.hpp>

#include "OTAPI.hpp"
#include "OT_ME.hpp"
#include "ot_command_ot.hpp"
#include "ot_made_easy_ot.hpp"
#include "ot_otapi_ot.hpp"
#include "ot_utility_ot.hpp"


extern string OT_CLI_GetValueByKey(string, string);



OT_COMMAND_OT int32_t main_revoke_credential()
{
    OTAPI_Wrap::Output(0, "\nThis command not coded yet. We need to use the OT_API_RevokeSubcredential API call here.\n\n");

    return -1;
}


OT_COMMAND_OT int32_t main_new_credential()
{
    OTAPI_Wrap::Output(0, "\nThis command not coded yet. A Nym is created with credentials already,\nbut to add MORE credentials to an existing Nym, I need to use the OT_API_AddSubcredential API call.\n\n");

    return -1;
}


// Also TODO:
// Update the "cancel" command, for outgoing cash, to give you a choice to deposit the cash instead
// of discarding it.
// details_deposit_purse(strServerID, strMyAcctID, strToNymID, strInstrument, "") // strIndices is left blank in this case


// BASKETS

OT_COMMAND_OT int32_t main_show_basket()
{
    string strUsage = "Usage:    opentxs showbasket\nOPTIONAL:   --args \"index BASKET_INDEX\"\n\nNOTE: If you leave off the index, then it lists all the basket currencies.\nBut if an index is provided, this command will zoom in and show the details\nfor that specific basket currency.\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    return details_show_basket();
}

OT_COMMAND_OT int32_t details_show_basket()
{
    bool bOnFirstIteration = true;
    int32_t nAssetCount = OTAPI_Wrap::GetAssetTypeCount();

    if (VerifyIntVal(nAssetCount) && (nAssetCount > 0))
    {
        string strIndex = "";

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            string strTempIndex = OT_CLI_GetValueByKey(Args, "index");

            if (VerifyStringVal(strTempIndex))
            {
                strIndex = strTempIndex;
            }
        } // args

        // Zoom in on a specific basket currency.
        //
        if (VerifyStringVal(strIndex))
        {
            int32_t nIndex = to_int(strIndex);

            if (!VerifyIntVal(nIndex))
            {
                return -1;
            }
            else if ((nIndex < 0) || (nIndex >= nAssetCount))
            {
                OTAPI_Wrap::Output(0, "Error: index out of bounds.\n");
                return -1;
            }
            else
            {
                string strAssetID = OTAPI_Wrap::GetAssetType_ID(nIndex);
                if (!VerifyStringVal(strAssetID))
                {
                    OTAPI_Wrap::Output(0, "ERROR: Failed getting asset type ID at index: " + to_string(nIndex) + "\n");
                }
                else
                {
                    string strAssetName = OTAPI_Wrap::GetAssetType_Name(strAssetID);
                    if (!VerifyStringVal(strAssetName))
                    {
                        strAssetName = "";
                    }

                    if (!OTAPI_Wrap::IsBasketCurrency(strAssetID))
                    {
                        OTAPI_Wrap::Output(0, "Failure: not a basket currency: " + strAssetID + " : " + strAssetName + "\n");
                    }
                    else
                    {
                        // DISPLAY ALL THE DETAILS ABOUT THIS BASKET CURRENCY:
                        //
                        print("Name: " + strAssetName);
                        print("ID:   " + strAssetID);

                        int32_t nMemberCount = OTAPI_Wrap::Basket_GetMemberCount(strAssetID);

                        if (!VerifyIntVal(nMemberCount))
                        {
                            OTAPI_Wrap::Output(0, "ERROR: expected int32_t return value from OT_API_Basket_GetMemberCount(strAssetID)\n");
                        }
                        else if (nMemberCount <= 0)
                        {
                            OTAPI_Wrap::Output(0, "Strange: this basket has " + to_string(nMemberCount) + " sub-currencies. (Expected 1 or more.)\n");
                        }
                        else
                        {
                            int64_t nBasketMinTransAmt = OTAPI_Wrap::Basket_GetMinimumTransferAmount(strAssetID);

                            if (!VerifyIntVal(nBasketMinTransAmt))
                            {
                                OTAPI_Wrap::Output(0, "Strange: expected minimum transfer amount for basket, but got bad value instead.\n");
                            }
                            else
                            {
                                print("Minimum transfer amount for basket:     " + to_string(nBasketMinTransAmt));
                                print("Number of sub-currencies in the basket: " + to_string(nMemberCount));

                                bool bFirstMember = true;

                                for (int32_t nMemberIndex = 0; nMemberIndex < nMemberCount; ++nMemberIndex)
                                {
                                    string strMemberType = OTAPI_Wrap::Basket_GetMemberType(strAssetID, nMemberIndex);
                                    string strMemberName = VerifyStringVal(strMemberType) ? OTAPI_Wrap::GetAssetType_Name(strMemberType) : "";

                                    int64_t nMinTransAmt = OTAPI_Wrap::Basket_GetMemberMinimumTransferAmount(strAssetID, nMemberIndex);

                                    if (bFirstMember)
                                    {
                                        bFirstMember = false;

                                        OTAPI_Wrap::Output(0, "    Index  :  Min Transfer Amount  :  Member currency  \n---------------------------------------\n");
                                    }
                                    print("    " + to_string(nMemberIndex) + "      : " + (VerifyIntVal(nMinTransAmt) ? to_string(nMinTransAmt) : "ERROR_AMT") + " : " + strMemberType + " : " + (VerifyStringVal(strMemberName) ? strMemberName : "ERROR_NAME"));
                                    OTAPI_Wrap::Output(0, "---------------------------------------\n");
                                }
                            }
                        }
                    }
                }
            }
            return 1;
        }

        // List ALL the basket currencies.
        //
        for (int32_t nAssetIndex = 0; nAssetIndex < nAssetCount; ++nAssetIndex)
        {
            string strAssetID = OTAPI_Wrap::GetAssetType_ID(nAssetIndex);
            if (VerifyStringVal(strAssetID) && OTAPI_Wrap::IsBasketCurrency(strAssetID))
            {
                if (bOnFirstIteration)
                {
                    bOnFirstIteration = false;
                    OTAPI_Wrap::Output(0, "Index |  Basket currencies:\n------------------------------------\n");
                }

                string strAssetName = OTAPI_Wrap::GetAssetType_Name(strAssetID);

                if (VerifyStringVal(strAssetName))
                {
                    print(to_string(nAssetIndex) + ": " + strAssetID + " : " + strAssetName);
                }
                else
                {
                    print(to_string(nAssetIndex) + ": " + strAssetID);
                }
            }
        } // for
        if (nAssetCount > 0) { OTAPI_Wrap::Output(0, "\n"); }
    }

    return -1;
}


OT_COMMAND_OT int32_t main_new_basket()
{
    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        return details_new_basket(Server, MyNym);
    }

    return -1;
}

OT_COMMAND_OT int32_t details_new_basket(const string & strServer, const string & strNym)
{
    MadeEasy madeEasy;

    int32_t nBasketCount = 2;
    OTAPI_Wrap::Output(0, "How many different asset types will compose this new basket currency? [2]: ");

    string strBasketCount = OT_CLI_ReadLine();

    if (VerifyStringVal(strBasketCount))
    {
        nBasketCount = to_int(strBasketCount);

        if (nBasketCount < 2)
        {
            OTAPI_Wrap::Output(0, "Sorry, but a basket currency must be composed of at least 2 sub-currencies.\n");
            return -1;
        }
    }

    int64_t lMinimumTransAmount = int64_t(100);

    OTAPI_Wrap::Output(0, "\nIf your basket has a minimum transfer amount of 100, you might have 2 or 3 sub-currencies,\nwith the first being a minimum of 2 gold, the second being a minimum of 50 dollars, and the\nthird being a minimum of 30 silver.\nIn this example, 100 units of the basket currency is transferrable in or out of the\nbasket currency, in return for 2 gold, 50 dollars, and 30 silver.\n\n");
    OTAPI_Wrap::Output(0, "What is the minimum transfer amount for the basket currency itself? [100]: ");

    string strMinAmount = OT_CLI_ReadLine();

    if (VerifyStringVal(strMinAmount))
    {
        lMinimumTransAmount = to_long(strMinAmount);

        if (lMinimumTransAmount < 1)
        {
            OTAPI_Wrap::Output(0, "Sorry, but this needs to be a non-zero value. Minimum is 1.\n");
            return -1;
        }
    }

    string strBasket = OTAPI_Wrap::GenerateBasketCreation(strNym, lMinimumTransAmount);

    if (!VerifyStringVal(strBasket))
    {
        OTAPI_Wrap::Output(0, "Error while generating initial basket object.\n");
        return -1;
    }

    for (int32_t ibasket = 0; ibasket < nBasketCount; ++ibasket)
    {
        stat_assets();

        OTAPI_Wrap::Output(0, "\nThis basket currency has " + to_string(nBasketCount) + " subcurrencies.\n");
        OTAPI_Wrap::Output(0, "So far you have defined " + to_string(ibasket) + " of them.\n");
        OTAPI_Wrap::Output(0, "Please PASTE the asset type ID for a subcurrency of this basket: ");

        string strSubcurrencyID = OT_CLI_ReadLine();

        if (!VerifyStringVal(strSubcurrencyID))
        {
            return -1;
        }

        string strSubcurrencyContract = OTAPI_Wrap::GetAssetType_Contract(strSubcurrencyID);

        if (!VerifyStringVal(strSubcurrencyContract))
        {
            OTAPI_Wrap::Output(0, "Sorry, but " + strSubcurrencyID + " is apparently not a currency contract in your wallet.\n");
            ibasket -= 1;
            continue;
        }

        OTAPI_Wrap::Output(0, "Enter minimum transfer amount for that asset type [100]: ");

        lMinimumTransAmount = 100;
        strMinAmount = OT_CLI_ReadLine();

        if (VerifyStringVal(strMinAmount))
        {
            lMinimumTransAmount = OTAPI_Wrap::StringToAmount(strSubcurrencyID, strMinAmount);

            if (lMinimumTransAmount < 1)
            {
                OTAPI_Wrap::Output(0, "Sorry, but this needs to be a non-zero value. Minimum is 1.\n");
                ibasket -= 1;
                continue;
            }
        }

        string strTempBasket = OTAPI_Wrap::AddBasketCreationItem(strNym, strBasket, strSubcurrencyID, lMinimumTransAmount);

        if (!VerifyStringVal(strTempBasket))
        {
            OTAPI_Wrap::Output(0, "Error: OT_API_AddBasketCreationItem returned NULL. (Failure.)\n");
            return -1;
        }
        else
        {
            strBasket = strTempBasket;
        }
    }


    OTAPI_Wrap::Output(0, "Here's the basket we're issuing:\n\n" + strBasket + "\n");


    string strResponse = madeEasy.issue_basket_currency(strServer, strNym, strBasket);
    int32_t nStatus = VerifyMessageSuccess(strResponse);

    // NOTICE: No need here to deal with retries, timeouts, request number,
    // syncing transaction number, download / process nymbox, etc! It's all
    // handled at a lower level!  Instead, simply check for success or failure:
    //
    // -1 is error,
    //  0 is reply received: failure
    //  1 is reply received: success
    //
    switch (nStatus)
    {
    case 1:
    {
              OTAPI_Wrap::Output(0, "\n\n SUCCESS in issue_basket_currency! Server response:\n\n");
              print(strResponse); // stdout

              string strNewID = OTAPI_Wrap::Message_GetNewAssetTypeID(strResponse);
              bool bGotNewID = VerifyStringVal(strNewID);
              bool bRetrieved = false;
              string strEnding = ".";

              if (bGotNewID)
              {
                  string strRetrieved = madeEasy.retrieve_contract(strServer, strNym, strNewID);
                  strEnding = ": " + strNewID;

                  if (1 == VerifyMessageSuccess(strRetrieved))
                  {
                      bRetrieved = true;
                  }
              }
              OTAPI_Wrap::Output(0, "Server response: SUCCESS in issue_basket_currency!\n");
              OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving new basket contract" + strEnding + "\n");
              break;
    }
    case 0:
        OTAPI_Wrap::Output(0, "\n\n FAILURE in issue_basket_currency! Server response:\n\n");
        print(strResponse); // stdout
        OTAPI_Wrap::Output(0, " FAILURE in issue_basket_currency!\n");
        break;
    default:
        OTAPI_Wrap::Output(0, "\n\nError in issue_basket_currency! nStatus is: " + to_string(nStatus) + "\n");

        if (VerifyStringVal(strResponse))
        {
            OTAPI_Wrap::Output(0, "Server response:\n\n");
            print(strResponse); // stdout
            OTAPI_Wrap::Output(0, "\nError in issue_basket_currency! nStatus is: " + to_string(nStatus) + "\n");
        }
        break;
    }
    OTAPI_Wrap::Output(0, "\n"); //stderr

    return (0 == nStatus) ? -1 : nStatus;
}


OT_COMMAND_OT int32_t details_exchange_basket(const string & strServer, const string & strNym, const string & strAcct, const string & strBasketType)
{
    // NOTE: details_exchange_basket ASSUMES that strAcct has a server of strServer and
    // a NymID of strNym and an asset type of strBasketType. (These are already verified
    // in main_exchange_basket.)
    //
    MadeEasy madeEasy;

    int32_t nMemberCount = OTAPI_Wrap::Basket_GetMemberCount(strBasketType);

    if (!VerifyIntVal(nMemberCount) || (nMemberCount < 2))
    {
        OTAPI_Wrap::Output(0, "Strange, the chosen basket asset type apparently has no sub-currencies. (Failure.)\n");
        return -1;
    }

    int64_t lMinimumTransAmount = OTAPI_Wrap::Basket_GetMinimumTransferAmount(strBasketType);

    if (!VerifyIntVal(lMinimumTransAmount))
    {
        OTAPI_Wrap::Output(0, "Strange, the chosen basket asset type apparently has no minimum transfer amount. (Failure.)\n");
        return -1;
    }

    bool bExchangingIn = true;

    OTAPI_Wrap::Output(0, "Are you exchanging IN or OUT of the basket? [IN]: ");
    string strInOrOut = OT_CLI_ReadLine();

    if (!VerifyStringVal(strInOrOut))
    {
        strInOrOut = "in";
    }

    int64_t lBalance = OTAPI_Wrap::GetAccountWallet_Balance(strAcct);

    if (!VerifyIntVal(lBalance))
    {
        OTAPI_Wrap::Output(0, "Strange: unable to retrieve balance for basket account: " + strAcct + "\n");
        return -1;
    }

    if ((strInOrOut == "out") || (strInOrOut == "OUT"))
    {
        OTAPI_Wrap::Output(0, "Exchanging OUT of the basket currency...\n\n");
        bExchangingIn = false;

        if (lBalance < lMinimumTransAmount)
        {
            OTAPI_Wrap::Output(0, "Sorry, but the minimum transfer amount for this basket currency is " + to_string(lMinimumTransAmount) + "\nand the chosen account's balance is only " + to_string(lBalance) + ". (Failure.)\n");
            return -1;
        }
    }
    else
    {
        OTAPI_Wrap::Output(0, "Exchanging IN to the basket currency...\n\n");
    }

    int32_t nTransferMultiple = 1;

    OTAPI_Wrap::Output(0, "This basket currency has a minimum transfer amount of " + to_string(lMinimumTransAmount) + ".\n");
    OTAPI_Wrap::Output(0, "Now you must choose the Transfer Multiple for the exchange. For example:\n");

    for (int32_t i = 1; i < 5; ++i)
    {
        int64_t lUnits = i * lMinimumTransAmount;

        OTAPI_Wrap::Output(0, "A transfer multiple of " + to_string(i) + " will exchange " + to_string(lUnits) + " units of the basket currency.\n");
    }
    OTAPI_Wrap::Output(0, "Etc.\n");

    if (!bExchangingIn) { OTAPI_Wrap::Output(0, "Keep in mind, the balance in the basket account is: " + to_string(lBalance) + "\n\n"); }

    OTAPI_Wrap::Output(0, "Please choose a transfer multiple [1]: ");
    string strTransferMultiple = OT_CLI_ReadLine();

    if (VerifyStringVal(strTransferMultiple))
    {
        int32_t nTempMultiple = to_int(strTransferMultiple);

        if (VerifyIntVal(nTempMultiple) && (nTempMultiple > 1)) { nTransferMultiple = nTempMultiple; }
    }

    int64_t lAttemptedTransfer = (nTransferMultiple * lMinimumTransAmount);

    if (!bExchangingIn && (lAttemptedTransfer > lBalance))
    {
        OTAPI_Wrap::Output(0, "A transfer multiple of " + to_string(nTransferMultiple) + " will exchange " + to_string(lAttemptedTransfer) + " units out of the basket currency.\nUnfortunately, you only have a " + to_string(lBalance) + " balance in your basket account. (Failed.)\n");
        return -1;
    }

    if (!madeEasy.insure_enough_nums(20, strServer, strNym))
    {
        return -1;
    }

    string strBasket = OTAPI_Wrap::GenerateBasketExchange(strServer, strNym, strBasketType, strAcct, nTransferMultiple);

    if (!VerifyStringVal(strBasket))
    {
        OTAPI_Wrap::Output(0, "Failed generating basket exchange request.\n");
        return -1;
    }

    // Below this point, after any failure, call this before returning:
    //
    // OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false)
    //
    // NOTE: Only do this up until the message is sent. Once it's sent, the harvesting is already
    // handled internally. (Only need to harvest in the event that some failure occurs in the middle of
    // constructing the basket exchange request, for any time BEFORE actually trying to send it.)


    // SUB-CURRENCIES!

    for (int32_t nMember = 0; nMember < nMemberCount; ++nMember)
    {
        string strMemberType = OTAPI_Wrap::Basket_GetMemberType(strBasketType, nMember);

        if (!VerifyStringVal(strMemberType))
        {
            OTAPI_Wrap::Output(0, "Error retrieving member type from index " + to_string(nMember) + " of basket currency: " + strBasketType + "\n");
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        string strMemberTypeName = OTAPI_Wrap::GetAssetType_Name(strMemberType);

        if (!VerifyStringVal(strMemberTypeName))
        {
            strMemberTypeName = "";
        }

        int64_t lMemberAmount = OTAPI_Wrap::Basket_GetMemberMinimumTransferAmount(strBasketType, nMember);

        if (!VerifyIntVal(lMemberAmount))
        {
            OTAPI_Wrap::Output(0, "Error retrieving minimum transfer amount from index " + to_string(nMember) + " (" + strMemberType + ") on basket currency: " + strBasketType + "\n");
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        lAttemptedTransfer = (nTransferMultiple * lMemberAmount);

        // This will only display accounts registered on strServer of asset type strMemberType.
        //
        stat_basket_accounts(strServer, strNym, true, strMemberType);

        OTAPI_Wrap::Output(0, "There are " + to_string(nMemberCount - nMember) + " accounts remaining to be selected.\n\n");
        OTAPI_Wrap::Output(0, "Currently we need to select an account with the asset type:\n" + strMemberType + " (" + strMemberTypeName + ")\n");
        OTAPI_Wrap::Output(0, "Above are all the accounts in the wallet, for the relevant server and nym, of that asset type.\n");

        if (bExchangingIn) { OTAPI_Wrap::Output(0, "\nKeep in mind, with a transfer multiple of " + to_string(nTransferMultiple) + " and a minimum transfer amount of " + to_string(lMemberAmount) + "\n(for this sub-currency), you must therefore select an account with a minimum\nbalance of: " + to_string(lAttemptedTransfer) + "\n"); }

        OTAPI_Wrap::Output(0, "\nPlease PASTE an account ID from the above list: ");
        string strSubAccount = OT_CLI_ReadLine();

        if (!VerifyStringVal(strSubAccount))
        {
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        string strSubAssetID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strSubAccount);

        if (!VerifyStringVal(strSubAssetID))
        {
            OTAPI_Wrap::Output(0, "Error retrieving asset type ID from pasted account: " + strSubAccount + "\n");
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        if (strMemberType != strSubAssetID)
        {
            OTAPI_Wrap::Output(0, "Failure: The selected account has the wrong asset type: " + strSubAssetID + "\n");
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        lBalance = OTAPI_Wrap::GetAccountWallet_Balance(strSubAccount);

        if (!VerifyIntVal(lBalance))
        {
            OTAPI_Wrap::Output(0, "Strange, error while retrieving balance for sub-account: " + strSubAccount + "\n");
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        if (bExchangingIn && (lAttemptedTransfer > lBalance))
        {
            OTAPI_Wrap::Output(0, "\nWith a minimum transfer amount of " + to_string(lMemberAmount) + " for this sub-currency, a transfer multiple of " + to_string(nTransferMultiple) + " will exchange " + to_string(lAttemptedTransfer) + " units out of the basket currency.\n\nUnfortunately, you only have a " + to_string(lBalance) + " balance in your selected account. (Failure.)\n");
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        string strTempBasket = OTAPI_Wrap::AddBasketExchangeItem(strServer, strNym, strBasket, strSubAssetID, strSubAccount);

        if (!VerifyStringVal(strTempBasket))
        {
            OTAPI_Wrap::Output(0, "Failed while adding this sub-account to the exchange request!\n");
            OTAPI_Wrap::Msg_HarvestTransactionNumbers(strBasket, strNym, false, false, false, false, false);
            return -1;
        }

        strBasket = strTempBasket;

        OTAPI_Wrap::Output(0, "\n\n");
    } // for

    // Send the exchange transaction...
    //
    string strResponse = madeEasy.exchange_basket_currency(strServer, strNym, strBasketType, strBasket, strAcct, bExchangingIn);
    string strAttempt = "exchange_basket";
    // ***************************************************************

    // Interpret the server reply...

    int32_t nInterpretReply = InterpretTransactionMsgReply(strServer, strNym, strAcct, strAttempt, strResponse);

    if (1 == nInterpretReply)
    {
        // Download all the intermediary files (account balance, inbox, outbox, etc)
        // since they have probably changed from this operation.
        //
        bool bRetrieved = madeEasy.retrieve_account(strServer, strNym, strAcct, true); //bForceDownload defaults to false.

        OTAPI_Wrap::Output(0, "Server response (" + strAttempt + "): SUCCESS exchanging basket!\n");
        OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");
    }

    // ***************************************************************
    //
    // Return status to caller.
    //
    return nInterpretReply;
}

OT_COMMAND_OT int32_t main_exchange_basket()
{
    string strUsage = "Usage:   opentxs exchange --myacct BASKET_ACCT_ID\n\nThis command exchanges in or out of a basket currency.\nYou must already have an asset account which has a basket currency as its asset type.\nYou must also have accounts for all the subcurrencies in that basket.\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strAcctType = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);
        string strServer = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);
        string strNym = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

        if (!VerifyStringVal(strAcctType))
        {
            OTAPI_Wrap::Output(0, "Error while trying to retrieve asset type for account: " + MyAcct + "\n");
        }
        else if (!VerifyStringVal(strServer))
        {
            OTAPI_Wrap::Output(0, "Error while trying to retrieve server ID for account: " + MyAcct + "\n");
        }
        else if (!VerifyStringVal(strNym))
        {
            OTAPI_Wrap::Output(0, "Error while trying to retrieve Nym ID for account: " + MyAcct + "\n");
        }

        else if (VerifyExists("MyPurse", false) && (MyPurse != strAcctType))
        {
            OTAPI_Wrap::Output(0, "MyAcct has a different asset type than the one specified at the command line.\nPlease re-try, and add: --mypurse " + strAcctType + "\n");
        }
        else if (VerifyExists("Server", false) && (Server != strServer))
        {
            OTAPI_Wrap::Output(0, "MyAcct has a different server ID than the one specified at the command line.\nPlease re-try, and add: --server " + strServer + "\n");
        }
        else if (VerifyExists("MyNym", false) && (MyNym != strNym))
        {
            OTAPI_Wrap::Output(0, "MyAcct has a different owner Nym ID than the one specified at the command line.\nPlease re-try, and add: --mynym " + strNym + "\n");
        }

        else if (!OTAPI_Wrap::IsBasketCurrency(strAcctType))
        {
            OTAPI_Wrap::Output(0, "\nMyAcct is NOT a basket currency! Its asset type is: " + strAcctType + "\nHere is a list of the basket currencies in your wallet:\n");

            details_show_basket();

            OTAPI_Wrap::Output(0, "\nHere is a list of the accounts whose asset type IS a basket currency:\n");

            stat_basket_accounts();

            OTAPI_Wrap::Output(0, "\nMyAcct is not a basket currency!\nPlease use --myacct to specify an account whose asset type IS a basket currency.\n");
        }

        else
        {
            return details_exchange_basket(strServer, strNym, MyAcct, strAcctType);
        }
    }
    else
    {
        OTAPI_Wrap::Output(0, "You must provide an account ID, and that account must have a basket\ncurrency for its asset type. Use --myacct and choose from these basket accounts:\n");

        stat_basket_accounts();
    }

    return -1;
}

OT_COMMAND_OT int32_t stat_basket_accounts()
{
    string strServer = "";
    string strNym = "";
    return stat_basket_accounts(strServer, strNym);
}

OT_COMMAND_OT int32_t stat_basket_accounts(const string & strServer, const string & strNym)
{
    bool bFilter = false; //unused in this case
    string strBasketType = "";

    return stat_basket_accounts(strServer, strNym, bFilter, strBasketType); // This will ONLY show accounts that are basket currencies.
}

// Used by exchange_basket for displaying certain types of accounts.
//
// if strBasketType doesn't exist, it will ONLY show accounts that are basket currencies.
// if strBasketType exists, and bFilter is TRUE, it will ONLY show accounts of that type.
// if strBasketType exists, and bFilter is FALSE, it will only show accounts that are NOT of that type.
//
// Also: if strServer exists, the accounts are filtered by that server.
// Also: if strNym exists, the accounts are filtered by that Nym.
//
OT_COMMAND_OT int32_t stat_basket_accounts(const string & strServer, const string & strNym, const bool bFilter, const string & strBasketType)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    print("------------------------------------------------------------------");
    print(" ** ACCOUNTS :\n");

    int32_t nAccountCount = OTAPI_Wrap::GetAccountCount();

    for (int32_t i = 0; i < nAccountCount; ++i)
    {
        string strID = OTAPI_Wrap::GetAccountWallet_ID(i);
        string strAssetID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strID);
        string strAcctServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strID);
        string strAcctNymID = OTAPI_Wrap::GetAccountWallet_NymID(strID);

        if (!VerifyStringVal(strServer) || (VerifyStringVal(strServer) && (strServer == strAcctServerID)))
        {
            if (!VerifyStringVal(strNym) || (VerifyStringVal(strNym) && (strNym == strAcctNymID)))
            {
                if ((!VerifyStringVal(strBasketType) && OTAPI_Wrap::IsBasketCurrency(strAssetID)) || // Only show basket accounts.
                    (VerifyStringVal(strBasketType) && bFilter && (strBasketType == strAssetID)) || // Only show accounts of type strBasketType
                    (VerifyStringVal(strBasketType) && !bFilter && (strBasketType != strAssetID)))   // Only show accounts NOT of type strBasketType
                {
                    if ((i > 0) && (i != (nAccountCount))) { print("-------------------------------------"); }

                    string strStatAcct = madeEasy.stat_asset_account(strID);
                    bool bSuccess = VerifyStringVal(strStatAcct);
                    if (bSuccess)
                    {
                        print(strStatAcct);
                    }
                    else
                    {
                        print("Error trying to stat an account: " + strID);
                    }
                    // stderr
                    print("");
                }
            }
        }
    }
    print("------------------------------------------------------------------");

    return 1;
}


// ALSO TODO:  Modified cancelCronItem so you can pass an instrument.
// So even for non-cron items, you should still be able to cancel them.
// (aka cancel the transaction numbers on it.) This is for when you change
// your mind on an outgoing instrument, and you want it cancelled before the
// recipient can process it.
// Outgoing cheque, outgoing payment plan, outgoing smart contract, etc.
//

// AND WHAT ABOUT incoming cheques? I can already discard it, but that leaves
// the sender with it still sitting in his outpayment box, until it expires.
// I'd rather notify him. He should get a failure/rejection notice so that his
// client can also harvest whatever numbers it needs to harvest.


// TODO:  details_cancel_outgoing and details_discard_incoming both need to be updated
// so that they involve a server message. This way the other parties can be notified of
// the cancellation / discarding.
//


OT_COMMAND_OT int32_t details_discard_incoming(const string & strServer, const string & strMyNym, const string & strIndices)
{
    if (!VerifyStringVal(strIndices)) { return -1; }

    int32_t nSuccess = 1;

    string strInbox = OTAPI_Wrap::LoadPaymentInbox(strServer, strMyNym); // Returns NULL, or an inbox.

    if (!VerifyStringVal(strInbox))
    {
        OTAPI_Wrap::Output(0, "\n\n details_discard_incoming:  OT_API_LoadPaymentInbox failed.\n\n");
        return -1;
    }

    int32_t nInboxCount = OTAPI_Wrap::Ledger_GetCount(strServer, strMyNym, strMyNym, strInbox);

    if (!VerifyIntVal(nInboxCount))
    {
        OTAPI_Wrap::Output(0, "details_discard_incoming: Unable to retrieve size of payments inbox ledger. (Failure.)\n");
        return -1;
    }

    if (nInboxCount > 0)
    {

        int32_t nIndicesCount = VerifyStringVal(strIndices) ? OTAPI_Wrap::NumList_Count(strIndices) : 0;

        // Either we loop through all the instruments and accept them all, or
        // we loop through all the instruments and accept the specified indices.
        //
        // (But either way, we loop through all the instruments.)
        //
        for (int32_t nInboxIndex = (nInboxCount - 1); nInboxIndex >= 0; --nInboxIndex) // Loop from back to front, so if any are removed, the indices remain accurate subsequently.
        {
            bool bContinue = false;

            // - If "all" was passed, we process the item.
            // - If indices are specified, but the current index is not on
            //   that list, then continue...
            //
            if (!("all" == strIndices) && ((nIndicesCount > 0) && !OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nInboxIndex))))
            {
                //              continue  // apparently not supported by the language.
                bContinue = true;
            }

            // If it IS "all" OR, if there are indices and the current index was found in them.
            //
            if (!bContinue)
            {
                // removes payment instrument (from payments in or out box)
                bool bRecorded = OTAPI_Wrap::RecordPayment(strServer, strMyNym,
                    true, // true == payments inbox. false == payments outbox.
                    nInboxIndex, false);  //bSaveCopy = false, since we're discarding it.
                string strRecorded = bRecorded ? "Success" : "Failure";
                OTAPI_Wrap::Output(0, "\n" + strRecorded + " discarding instrument from payments inbox at index: " + to_string(nInboxIndex) + ".\n\n NOTE: Now the sender has to leave it in his outbox until it expires or he cancels it on his end.\n");
                if (!bRecorded) { nSuccess = -1; }
            } //if (!bContinue)

        } // for

    } // if (nCount > 0)
    else { return 0; } // 1 means we successfully did something. 0 means the payments inbox was empty.

    return nSuccess;
}

OT_COMMAND_OT int32_t main_discard_incoming()
{
    string strUsage = "Usage:   opentxs discard --mynym NYM_ID --server SERVER_ID --args \"index|indices INDICES_GO_HERE\"\n\nThis command discards an incoming instrument from the payments inbox.\n(Usually used for discarding an invoice, for when you don't want to pay it.)\nYou can also use 'all' for the index, for it to process ALL instruments.\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym") && VerifyExists("Server"))
    {
        string strIndex = "";
        string strIndices = "";
        string strFinalIndex = "";
        bool bUseStdin = false;

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            strIndex = OT_CLI_GetValueByKey(Args, "index");
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.

            if (VerifyStringVal(strIndex))
            {
                strFinalIndex = strIndex;
            }
            else if (VerifyStringVal(strIndices))
            {
                strFinalIndex = strIndices;
            }
            else
            {
                bUseStdin = true;
            }
        }
        else { bUseStdin = true; }

        if (bUseStdin)
        {
            main_show_payments_inbox();

            OTAPI_Wrap::Output(0, "\nPlease enter the index (in your payments inbox)\nof the instrument you are discarding: ");
            strIndex = OT_CLI_ReadLine();

            if (VerifyStringVal(strIndex))
            {
                strFinalIndex = strIndex;
            }
            else { return -1; }
        }

        return details_discard_incoming(Server, MyNym, strFinalIndex);
    }

    return -1;
}

/*
std::string GetNym_OutpaymentsContentsByIndex(const std::string & NYM_ID, const int32_t & nIndex); // returns the message itself
std::string GetNym_OutpaymentsRecipientIDByIndex(const std::string & NYM_ID, const int32_t & nIndex); // returns the NymID of the recipient.
std::string GetNym_OutpaymentsServerIDByIndex(const std::string & NYM_ID, const int32_t & nIndex); // returns the ServerID where the message came from.
bool Nym_RemoveOutpaymentsByIndex(const std::string & NYM_ID, const int32_t & nIndex); // (1 or 0.)
bool Nym_VerifyOutpaymentsByIndex(const std::string & NYM_ID, const int32_t & nIndex); // true if signature verifies. (Sender Nym MUST be in my wallet for this to work.)

const char * OTAPI_Wrap::Instrmnt_GetAmount(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetTransNum(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetValidFrom(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetValidTo(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetMemo(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetType(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetServerID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetAssetID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetSenderUserID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetSenderAcctID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetRecipientUserID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetRecipientAcctID(const char * THE_INSTRUMENT);
*/

OT_COMMAND_OT int32_t details_cancel_outgoing(const string & strMyNym, const string & strMyAcct, const string & strIndices)
{
    int32_t nIndicesCount = OTAPI_Wrap::NumList_Count(strIndices);
    int32_t nCount = OTAPI_Wrap::GetNym_OutpaymentsCount(strMyNym);
    int32_t nSuccess = 1;

    //    OTAPI_Wrap::Output(0, "\n\nNOTE: You can't just discard a sent cheque from your outpayment box. Why not?\nJust because you remove your record of the outgoing cheque, doesn't mean you didn't already send it. (The recipient still received it, and still has it, whether you remove it from your outbox or not.) If you really want to cancel the cheque, then you need to do it in such a way that it will fail-as-cancelled when the recipient tries to deposit it. Otherwise, he would get that money whether you kept your own outgoing record or not. Therefore TODO: SOME server message must be performed here, which actually cancels the transaction number itself that appears on the cheque. This is the only way to insure that the cheque can't be used by the recipient (and even this will only work if you beat him to the punch -- otherwise if he deposits it before you cancel it, then it's already too late and he has the money.) THIS is why RecordPayment, regarding outpayments, only works on expired instruments -- because if it's not expired, you don't just want to remove your record of it. You want to cancel the transaction number itself -- and that requires server communication.\n\n");


    if (!VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "Error retrieving outpayments count for Nym: " + strMyNym + "\n");
        return -1;
    }

    if (nCount == 0)
    {
        OTAPI_Wrap::Output(0, "(Outpayment box is empty.)\n");
        nSuccess = 0;
    }
    else
    {
        for (int32_t nIndex = (nCount - 1); nIndex >= 0; --nIndex)
        {
            //          bool bRemoved = OTAPI_Wrap::Nym_RemoveOutpaymentsByIndex(strMyNym, nIndex); // (1 or 0.)

            //          string strRecorded = bRecorded ? "Success" : "Failure"
            //          OTAPI_Wrap::Output(0,  strRecorded + " discarding instrument from outpayment box at index: " + to_string(nIndex) + ".\n");

            //          if (!bRemoved)
            //          { nSuccess = -1; }

            bool bContinue = false;

            // - If "all" was passed, we process the item.
            // - If indices are specified, but the current index is not on
            //   that list, then continue...
            //
            if (!("all" == strIndices) && (VerifyIntVal(nIndicesCount) && (nIndicesCount > 0) && !OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex))))
            {
                //              continue  // apparently not supported by the language.
                bContinue = true;
            }

            string strServer = "";
            // If it IS "all," OR, if there are indices and the current index was found in them.
            //
            if (!bContinue)
            {
                strServer = OTAPI_Wrap::GetNym_OutpaymentsServerIDByIndex(strMyNym, nIndex);
                if (!VerifyStringVal(strServer))
                {
                    OTAPI_Wrap::Output(0, "ERROR: Failed retrieving server ID from outpayment at index: " + to_string(nIndex) + "\n");
                }

                else
                {
                    string strPaymentContents = OTAPI_Wrap::GetNym_OutpaymentsContentsByIndex(strMyNym, nIndex);

                    if (VerifyStringVal(strPaymentContents))
                    {
                        //                        string strPaymentAssetID   = OTAPI_Wrap::Instrmnt_GetAssetID (strPaymentContents)
                        string strPaymentType = OTAPI_Wrap::Instrmnt_GetType(strPaymentContents);

                        // Done: Put the code here where we message the server to cancel all relevant transaction
                        // numbers for the instrument. If it's a cheque, there's only one number. But if it's a smart
                        // contract, there could be many numbers. Seems like best thing is to just activate it, but
                        // have a "rejected" flag which causes the activation to fail. (That way, all the other parties
                        // will be properly notified, which the server already does.) We don't even need to remove it
                        // from the outpayment box, because the failure notification from the server will already cause
                        // the OTClient to remove it from the outpayment box.
                        //
                        // Ah-ha! ANY outgoing payment plan or smart contract is necessarily incomplete: it's outgoing
                        // because it was sent to the next party so he could sign it, too, and probably activate it.
                        // Presumably he has not done so yet (if I am 'beating him to the punch' by cancelling it before
                        // he can activate it) and therefore the plan or smart contract still is missing at least one
                        // signer, so it is GUARANTEED to fail verification if I try to activate it myself. (Good.)
                        //
                        // This means I can just take whatever instrument appears outgoing, and try to activate it myself.
                        // It will definitely fail activation, and then the failure notice will already be sent from that,
                        // to all the parties, and they can harvest back their numbers automatically as necessary.
                        //
                        // The one problem is, though this works for payment plans and smart contracts, it will not work
                        // for cheques. The cheque is made out to someone else, and he is the one normally who needs to
                        // deposit it. Plus, I can't deposit a cheque into the same account it's drawn on.
                        //
                        // UPDATE: Now when a cheque is deposited into the same account it was drawn on, that will be
                        // interpreted by the server as a request to CANCEL the cheque.
                        //


                        if ("SMARTCONTRACT" == strPaymentType)
                        {
                            // Just take the smart contract from the outpayment box, and try to
                            // activate it. It WILL fail, and then the failure message will be
                            // propagated to all the other parties to the contract. (Which will
                            // result in its automatic removal from the outpayment box.)
                            //
                            if (!VerifyStringVal(strMyAcct))
                            {
                                OTAPI_Wrap::Output(0, "You must provide an account owned by this Nym, which will be used for the cancellation. Try adding --myacct ACCT_ID\nNOTE: in the future we should just look up one of the accounts from the smart contract itself, since the current Nym has already confirmed the contract. But for now I'm just collecting the acct ID at the command line, since it's faster.\n");
                            }
                            else
                            {
                                MadeEasy madeEasy;
                                string strResponse = madeEasy.activate_smart_contract(strServer, strMyNym, strMyAcct, "acct_agent_name", strPaymentContents);

                                OTAPI_Wrap::Output(0, "Okay I just tried to activate the smart contract. (As a way of cancelling it.)\nSo while we expect this 'activation' to fail, it should have the desired effect of cancelling the smart contract and sending failure notices to all the parties.\n");

                                if (VerifyStringVal(strResponse))
                                {
                                    OTAPI_Wrap::Output(0, "\n Here's the server reply: \n" + strResponse + "\n");

                                    int32_t nTransCancelled = OTAPI_Wrap::Message_IsTransactionCanceled(strServer, strMyNym, strMyAcct, strResponse);

                                    if (VerifyIntVal(nTransCancelled) && (1 == nTransCancelled))
                                    {
                                        OTAPI_Wrap::Output(0, "\n Success canceling!\n");
                                    }
                                    else
                                    {
                                        OTAPI_Wrap::Output(0, "\n Error canceling!\n");
                                        nSuccess = -1;
                                    }
                                }
                                else
                                {
                                    OTAPI_Wrap::Output(0, "Strange, tried to cancel, but received a NULL server reply.\n");
                                }
                            }
                        }


                        else if ("PAYMENT PLAN" == strPaymentType)
                        {
                            // Just take the payment plan from the outpayment box, and try to
                            // activate it. It WILL fail, and then the failure message will be
                            // propagated to the other party to the contract. (Which will
                            // result in its automatic removal from the outpayment box.)

                            MadeEasy madeEasy;
                            string strResponse = madeEasy.cancel_payment_plan(strServer, strMyNym, strPaymentContents);

                            OTAPI_Wrap::Output(0, "Okay I just tried to activate the payment plan. (As a way of cancelling it.)\nSo while we expect this 'activation' to fail, it should have the desired effect of cancelling the payment plan and sending failure notices to all the parties.\n");

                            if (VerifyStringVal(strResponse))
                            {
                                OTAPI_Wrap::Output(0, "\n Here's the server reply: \n" + strResponse + "\n");

                                int32_t nTransCancelled = OTAPI_Wrap::Message_IsTransactionCanceled(strServer, strMyNym, strMyAcct, strResponse);

                                if (VerifyIntVal(nTransCancelled) && (1 == nTransCancelled))
                                {
                                    OTAPI_Wrap::Output(0, "\n Success canceling!\n");
                                }
                                else
                                {
                                    OTAPI_Wrap::Output(0, "\n Error canceling!\n");
                                    nSuccess = -1;
                                }
                            }
                            else
                            {
                                OTAPI_Wrap::Output(0, "Strange, tried to cancel, but received a NULL server reply.\n");
                            }
                        }


                        else if ("PURSE" == strPaymentType)
                        {
                            // This is a tricky one -- why would anyone EVER want to discard outgoing cash?
                            // Normally your incentive would be to do the opposite: Keep a copy of all outgoing
                            // cash until the copy itself expires (when the cash expires.) This way it's always
                            // recoverable in the event of a "worst case" situation.
                            //
                            // So what do we do in this case? Nevertheless, the user has explicitly just instructed
                            // the client to DISCARD OUTGOING CASH.
                            //
                            // Perhaps we should just ask the user to CONFIRM that he wants to erase the cash,
                            // and make SURE that he understands the consequences of that choice.

                            //                                OTAPI_Wrap::Output(0, "Any outgoing cash will already be automatically moved to the record box once it expires. No need to move it by hand.\nAre you SURE you want to move it now? [y/N] ");
                            //                                string strYes = OT_CLI_ReadLine()
                            //
                            //                                if (VerifyStringVal(strYes) && (("y" == strYes) || ("Y" == strYes)))
                            {
                                // removes payment instrument (from payments in or out box)
                                bool bRecorded = OTAPI_Wrap::RecordPayment(strServer, strMyNym,
                                false, // true == payments inbox. false == payments outbox.
                                nIndex,
                                false); // bSaveCopy = false.
                                if (!bRecorded) { nSuccess = -1; }
                                else { OTAPI_Wrap::Output(0, "Discarded cash purse:\n\n" + strPaymentContents + "\n"); }
                                string strRecorded = bRecorded ? "Success" : "Failure";
                                OTAPI_Wrap::Output(0, strRecorded + " discarding cash purse from outpayment box at index: " + to_string(nIndex) + ".\n\n");
                            }

                        }


                        else  // CHEQUE VOUCHER INVOICE
                        {
                            int32_t nDepositCheque = -1;
                            bool bIsVoucher = ("VOUCHER" == strPaymentType);

                            // Get the nym and account IDs from the cheque itself.
                            //
                            string strSenderAcctID = (bIsVoucher ? OTAPI_Wrap::Instrmnt_GetRemitterAcctID(strPaymentContents) : OTAPI_Wrap::Instrmnt_GetSenderAcctID(strPaymentContents));
                            string strSenderUserID = (bIsVoucher ? OTAPI_Wrap::Instrmnt_GetRemitterUserID(strPaymentContents) : OTAPI_Wrap::Instrmnt_GetSenderUserID(strPaymentContents));

                            if (!VerifyStringVal(strSenderAcctID))
                            {
                                OTAPI_Wrap::Output(0, "Failure trying to retrieve asset account ID from instrument.\n");
                            }
                            else if (!VerifyStringVal(strSenderUserID))
                            {
                                OTAPI_Wrap::Output(0, "Failure trying to retrieve Sender Nym ID from instrument.\n");
                            }
                            else if (!(strSenderUserID == strMyNym))
                            {
                                OTAPI_Wrap::Output(0, "Failure, very strange: Sender Nym ID on the instrument doesn't match the Nym ID.\n");
                            }
                            else
                            {
                                nDepositCheque = details_deposit_cheque(strServer, strSenderAcctID, strSenderUserID, strPaymentContents, strPaymentType);

                                OTAPI_Wrap::Output(0, "\n" + string((1 == nDepositCheque) ? "Success" : "Failure") + " canceling cheque of type: " + strPaymentType + "\n");
                            }
                        }


                    }

                }
            } //if (!bContinue)

        } // for (backwards through outpayments box.)
    }
    return nSuccess;
}


OT_COMMAND_OT int32_t main_cancel_outgoing()
{
    string strUsage = "Usage:   opentxs cancel --mynym NYM_ID --args \"index INDEX_GOES_HERE\"\n\nThis command cancels an outgoing instrument from the outpayment box.\n(Usually used for cancelling a cheque, payment plan, or smart contract.)\nThis, of course, will fail on the server side, if the recipient has already deposited the cheque.\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym"))
    {
        string strIndex = "";
        string strIndices = "";
        string strFinalIndex = "";
        bool bUseStdin = false;

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            strIndex = OT_CLI_GetValueByKey(Args, "index");
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.

            if (VerifyStringVal(strIndex))
            {
                strFinalIndex = strIndex;
            }
            else if (VerifyStringVal(strIndices))
            {
                strFinalIndex = strIndices;
            }
            else
            {
                bUseStdin = true;
            }
        }
        else { bUseStdin = true; }

        if (bUseStdin)
        {
            int32_t nCount = OTAPI_Wrap::GetNym_OutpaymentsCount(MyNym);

            for (int32_t nPayments = 0; nPayments < nCount; ++nPayments)
            {
                show_outpayment(MyNym, nPayments, false); // bShowInFull=false
            }

            OTAPI_Wrap::Output(0, "\nPlease enter the index (in your outpayment box)\nof the instrument you are cancelling: ");
            strIndex = OT_CLI_ReadLine();

            if (VerifyStringVal(strIndex))
            {
                strFinalIndex = strIndex;
            }
            else { return -1; }
        }

        string strMyAcct = "";
        if (VerifyExists("MyAcct", false)) // Used in the case of smart contracts.
        {
            strMyAcct = MyAcct;
        }

        return details_cancel_outgoing(MyNym, strMyAcct, strFinalIndex);
    }

    return -1;
}


/*
We might also need something like: main_show_cron_items
(Because we can't trigger a clause on a running smart contract,
unless we are able to list the running smart contracts and thus
ascertain the transaction number of the one whose clause we wish
to trigger.)
*/

OT_COMMAND_OT int32_t details_trigger_clause(const string & strServerID, const string & strMyNymID, const string & strTransNum, const string & strClause, const string & strParam)
{
    MadeEasy madeEasy;
    string strResponse = madeEasy.trigger_clause(strServerID, strMyNymID, strTransNum, strClause, strParam);
    int32_t nMessageSuccess = VerifyMessageSuccess(strResponse);

    if (!VerifyIntVal(nMessageSuccess) || (1 != nMessageSuccess))
    {
        OTAPI_Wrap::Output(0, "For whatever reason, our attempt to trigger the clause has failed.\n");
    }
    else
    {
        OTAPI_Wrap::Output(0, "Success!\n");
    }

    return nMessageSuccess;
}


//def main_trigger_clause()
//{; }


OT_COMMAND_OT int32_t main_trigger_clause()
{
    string strUsage = "USAGE STRING GOES HERE";
    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        // At this point we need to collect some other data:
        // First, we need the transaction number for the smart contract.
        // Second, we need the name of the clause we will be triggering.
        // Third we need (optionally) any string parameter that the user
        // may wish to pass into the clause when it gets triggered.
        //

        string strTransNum = "";
        string strClause = "";
        string strParam = "";

        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "index 1"
            //
            string strTempTransNum = OT_CLI_GetValueByKey(Args, "id");
            string strTempClause = OT_CLI_GetValueByKey(Args, "clause");
            string strTempParam = OT_CLI_GetValueByKey(Args, "param");

            // TRANSACTION ID
            //
            if (!VerifyStringVal(strTempTransNum))
            {
                OTAPI_Wrap::Output(0, "Please enter the transaction ID for the running smart contract: ");
                string strInputTransNum = OT_CLI_ReadLine();

                if (VerifyStringVal(strInputTransNum))
                {
                    strTransNum = strInputTransNum;
                }
            }
            else
            {
                strTransNum = strTempTransNum;
            }

            // CLAUSE NAME
            //
            if (!VerifyStringVal(strTempClause))
            {
                OTAPI_Wrap::Output(0, "Please enter the name of the clause you wish to trigger: ");
                string strInputClause = OT_CLI_ReadLine();

                if (VerifyStringVal(strInputClause))
                {
                    strClause = strInputClause;
                }
            }
            else
            {
                strClause = strTempClause;
            }

            // OPTIONAL PARAMETER
            //
            if (!VerifyStringVal(strTempParam))
            {
                OTAPI_Wrap::Output(0, "You can pass an optional parameter string (to pass to the clause itself)\nfollowed by a ~ by itself on a blank line. (Just use ~ to leave it blank.)\n\n");
                string strInputParam = OT_CLI_ReadUntilEOF();

                if (VerifyStringVal(strInputParam))
                {
                    strParam = strInputParam;
                }
            }
            else
            {
                strParam = strTempParam;
            }

        } // VerifyExists("Args")

        if (VerifyStringVal(strTransNum) && VerifyStringVal(strClause))
        {
            return details_trigger_clause(Server, MyNym, strTransNum, strClause, strParam);
        }

    }
    return -1;
}


OT_COMMAND_OT string find_revokedID_for_subcred(const string & strMyNymID, const string & strInputID)
{
    int32_t nCredCount = OTAPI_Wrap::GetNym_RevokedCredCount(strMyNymID);

    if (!VerifyIntVal(nCredCount))
    {
        return "";
    }

    else if (nCredCount >= 1)
    {
        for (int32_t nCurrent = 0; nCurrent < nCredCount; ++nCurrent)
        {
            string strCredID = OTAPI_Wrap::GetNym_RevokedCredID(strMyNymID, nCurrent);

            int32_t nSubCredCount = OTAPI_Wrap::GetNym_SubcredentialCount(strMyNymID, strCredID);

            if (VerifyIntVal(nSubCredCount) && (nSubCredCount >= 1))
            {
                for (int32_t nCurrentSubCred = 0; nCurrentSubCred < nSubCredCount; ++nCurrentSubCred)
                {
                    string strSubCredID = OTAPI_Wrap::GetNym_SubCredentialID(strMyNymID, strCredID, nCurrentSubCred);

                    if (strInputID == strSubCredID)
                    {
                        return strCredID; // Returns the revoked master credential ID associated with the subcred passed in.
                    }
                } // loop sub-credentials.
            }
        } // loop credentials

    }
    return "";
}


OT_COMMAND_OT string find_masterID_for_subcred(const string & strMyNymID, const string & strInputID)
{
    int32_t nCredCount = OTAPI_Wrap::GetNym_CredentialCount(strMyNymID);

    if (!VerifyIntVal(nCredCount))
    {
        return "";
    }

    else if (nCredCount >= 1)
    {
        for (int32_t nCurrent = 0; nCurrent < nCredCount; ++nCurrent)
        {
            string strCredID = OTAPI_Wrap::GetNym_CredentialID(strMyNymID, nCurrent);

            int32_t nSubCredCount = OTAPI_Wrap::GetNym_SubcredentialCount(strMyNymID, strCredID);

            if (VerifyIntVal(nSubCredCount) && (nSubCredCount >= 1))
            {
                for (int32_t nCurrentSubCred = 0; nCurrentSubCred < nSubCredCount; ++nCurrentSubCred)
                {
                    string strSubCredID = OTAPI_Wrap::GetNym_SubCredentialID(strMyNymID, strCredID, nCurrentSubCred);

                    if (strInputID == strSubCredID)
                    {
                        return strCredID; // Returns the master credential ID associated with the subcred passed in.
                    }
                } // loop sub-credentials.
            }
        } // loop credentials

    }
    return "";
}


// Takes a Nym ID and a credential ID and displays the contents
// for the credential.
// The credential might be a master credential, or a subcredential.
// It also might be a revoked credential.
// Handle all cases.
//
OT_COMMAND_OT bool details_show_credential(const string & strMyNymID, const string & strCredID)
{
    string strCredContents = OTAPI_Wrap::GetNym_CredentialContents(strMyNymID, strCredID);

    if (VerifyStringVal(strCredContents))
    {
        OTAPI_Wrap::Output(0, "Master Credential contents:\n");
        print(strCredContents);
        return true;
    }

    strCredContents = OTAPI_Wrap::GetNym_RevokedCredContents(strMyNymID, strCredID);

    if (VerifyStringVal(strCredContents))
    {
        OTAPI_Wrap::Output(0, "Revoked Credential contents:\n");
        print(strCredContents);
        return true;
    }

    // It MUST be a subcredential by this point, either for a master
    // or revoked master credential.
    //
    bool bIsRevoked = false;
    string strMasterID = find_masterID_for_subcred(strMyNymID, strCredID);

    if (!VerifyStringVal(strMasterID))
    {
        strMasterID = find_revokedID_for_subcred(strMyNymID, strCredID);
        bIsRevoked = true;
    }

    if (!VerifyStringVal(strMasterID))
    {
        OTAPI_Wrap::Output(0, "Sorry, unable to find any credentials associated with that ID.\n");
    }
    else
    {
        strCredContents = OTAPI_Wrap::GetNym_SubCredentialContents(strMyNymID, strMasterID, strCredID);

        if (!VerifyStringVal(strCredContents))
        {
            OTAPI_Wrap::Output(0, "Error retrieving sub-credential contents.\n");
            return false;
        }

        if (bIsRevoked)
        {
            OTAPI_Wrap::Output(0, "Revoked Subcredential contents:\n");
        }
        else
        {
            OTAPI_Wrap::Output(0, "Subcredential contents:\n");
        }
        print(strCredContents); // Great success!
        OTAPI_Wrap::Output(0, "\n");
        return true;
    }
    return false;
}


OT_COMMAND_OT int32_t main_show_credential()
{
    string strUsage = "Usage:   opentxs showcred --mynym NYM_ID --args \"id CREDENTIAL_ID\"\n\nThis command displays the contents of a given credential (for a given Nym.)\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym"))
    {
        string strCredID = "";

        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "index 1"
            //
            string strTempCredID = OT_CLI_GetValueByKey(Args, "id");

            if (!VerifyStringVal(strTempCredID))
            {
                OTAPI_Wrap::Output(0, "Please enter the ID for the credential: ");
                string strInput = OT_CLI_ReadLine();

                if (VerifyStringVal(strInput))
                {
                    strCredID = strInput;
                }
            }
            else
            {
                strCredID = strTempCredID;
            }
        } // VerifyExists("Args")

        if (VerifyStringVal(strCredID) && details_show_credential(MyNym, strCredID))
        {
            return 1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t details_show_credentials(const string & strMyNymID)
{
    int32_t nReturnVal = -1;

    int32_t nCredCount = OTAPI_Wrap::GetNym_CredentialCount(strMyNymID);

    if (!VerifyIntVal(nCredCount))
    {
        return -1;
    }

    if (nCredCount >= 1)
    {
        nReturnVal = 1;

        OTAPI_Wrap::Output(0, "Idx     Credential ID\n---------------------------\n");

        for (int32_t nCurrent = 0; nCurrent < nCredCount; ++nCurrent)
        {
            string strCredID = OTAPI_Wrap::GetNym_CredentialID(strMyNymID, nCurrent);
            print(to_string(nCurrent) + ":      " + strCredID);

            int32_t nSubCredCount = OTAPI_Wrap::GetNym_SubcredentialCount(strMyNymID, strCredID);

            if (VerifyIntVal(nSubCredCount) && (nSubCredCount >= 1))
            {

                OTAPI_Wrap::Output(0, "        ---------------------------\n        Idx     Subcredential ID\n        ---------------------------\n");

                for (int32_t nCurrentSubCred = 0; nCurrentSubCred < nSubCredCount; ++nCurrentSubCred)
                {
                    string strSubCredID = OTAPI_Wrap::GetNym_SubCredentialID(strMyNymID, strCredID, nCurrentSubCred);
                    print("        " + to_string(nCurrentSubCred) + ":      " + strSubCredID);
                }
            }
        } // credentials

        OTAPI_Wrap::Output(0, "\n");
    }

    else { nReturnVal = 0; }

    // Next: REVOKED credentials.

    nCredCount = OTAPI_Wrap::GetNym_RevokedCredCount(strMyNymID);

    if (!VerifyIntVal(nCredCount))
    {
        return -1;
    }

    if (nCredCount >= 1)
    {
        nReturnVal = 1;

        OTAPI_Wrap::Output(0, "Idx     Revoked Credential ID\n---------------------------\n");

        for (int32_t nCurrent = 0; nCurrent < nCredCount; ++nCurrent)
        {
            string strCredID = OTAPI_Wrap::GetNym_RevokedCredID(strMyNymID, nCurrent);
            print(to_string(nCurrent) + ":      " + strCredID);

            int32_t nSubCredCount = OTAPI_Wrap::GetNym_SubcredentialCount(strMyNymID, strCredID);

            if (VerifyIntVal(nSubCredCount) && (nSubCredCount >= 1))
            {

                OTAPI_Wrap::Output(0, "        ---------------------------\n        Idx     Revoked Subcredential ID\n        ---------------------------\n");

                for (int32_t nCurrentSubCred = 0; nCurrentSubCred < nSubCredCount; ++nCurrentSubCred)
                {
                    string strSubCredID = OTAPI_Wrap::GetNym_SubCredentialID(strMyNymID, strCredID, nCurrentSubCred);
                    print("        " + to_string(nCurrentSubCred) + ":      " + strSubCredID);
                }
            }
        } // credentials

        OTAPI_Wrap::Output(0, "\n");
    }

    return nReturnVal;
}


OT_COMMAND_OT int32_t main_show_credentials()
{
    string strUsage = "Usage:   opentxs credentials --mynym NYM_ID\n\nThis command displays the list of credentials for a given Nym.\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym"))
    {
        return details_show_credentials(MyNym);
    }

    return -1;
}


OT_COMMAND_OT bool stat_partyagent(const string & strSmartContract, const string & strPartyName, const string & strAgentName, const int32_t nIndex)
{
    string strDisplayIndex = "*";

    if (VerifyIntVal(nIndex))
    {
        strDisplayIndex = to_string(nIndex);
    }

    string strAgentID = OTAPI_Wrap::Party_GetAgentID(strSmartContract, strPartyName, strAgentName);

    if (VerifyStringVal(strAgentID))
    {
        print("--------------------\n " + strDisplayIndex + " : Agent '" + strAgentName + "' (party '" + strPartyName + "') has NymID: " + strAgentID + " ('" + OTAPI_Wrap::GetNym_Name(strAgentID) + "')");
    }
    else
    {
        print(" " + strDisplayIndex + " : Agent '" + strAgentName + "' (party '" + strPartyName + "') has no NymID assigned (yet.)");
    }

    return true;
}

OT_COMMAND_OT bool stat_partyagent_index(const string & strSmartContract, const string & strPartyName, const int32_t nCurrentAgent)
{
    string strAgentName = OTAPI_Wrap::Party_GetAgentNameByIndex(strSmartContract, strPartyName, nCurrentAgent);

    if (!VerifyStringVal(strAgentName))
    {
        OTAPI_Wrap::Output(0, "Error: Failed retrieving Agent Name from party '" + strPartyName + "' at agent index: " + to_string(nCurrentAgent) + "\n");
        return false;
    }
    return stat_partyagent(strSmartContract, strPartyName, strAgentName, nCurrentAgent);
}

OT_COMMAND_OT bool stat_partyagents(const string & strSmartContract, const string & strPartyName, const int32_t nDepth)
{
    int32_t nAgentCount = OTAPI_Wrap::Party_GetAgentCount(strSmartContract, strPartyName);

    if (!VerifyIntVal(nAgentCount) || (nAgentCount < 0))
    {
        OTAPI_Wrap::Output(0, "Error: Party '" + strPartyName + "' has bad value for number of authorized agents.\n");
        return false;
    }

    if (nDepth > 0)
    {
        // Iterate the agents for this party.
        //
        for (int32_t nCurrentAgent = 0; nCurrentAgent < nAgentCount; ++nCurrentAgent)
        {
            if (!stat_partyagent_index(strSmartContract, strPartyName, nCurrentAgent)) { return false; }
        }
    }
    else
    {
        print("Party '" + strPartyName + "' has " + to_string(nAgentCount) + ((1 == nAgentCount) ? " agent." : " agents."));
    }

    return true;
}


OT_COMMAND_OT bool stat_partyaccount(const string & strSmartContract, const string & strPartyName, const string & strAcctName, const int32_t nCurrentAccount)
{
    string strAcctAssetID = OTAPI_Wrap::Party_GetAcctAssetID(strSmartContract, strPartyName, strAcctName);
    string strAcctID = OTAPI_Wrap::Party_GetAcctID(strSmartContract, strPartyName, strAcctName);
    string strAcctAgentName = OTAPI_Wrap::Party_GetAcctAgentName(strSmartContract, strPartyName, strAcctName);

    if (VerifyStringVal(strAcctAssetID))
    {
        print("-------------------\nAccount '" + strAcctName + "' (index " + to_string(nCurrentAccount) + " on Party '" + strPartyName + "') has asset type: " + strAcctAssetID + " (" + OTAPI_Wrap::GetAssetType_Name(strAcctAssetID) + ")");
    }
    //  else
    //  {
    //      print("Account '"+strAcctName+"' (party '"+strPartyName+"') has no asset type (yet.)")
    //; }

    if (VerifyStringVal(strAcctID))
    {
        print("Account '" + strAcctName + "' (party '" + strPartyName + "') is confirmed as Account ID: " + strAcctID + " (" + OTAPI_Wrap::GetAccountWallet_Name(strAcctID) + ")");
    }
    //  else
    //  {
    //      print("Account '"+strAcctName+"' (party '"+strPartyName+"') has no Account ID (yet.)")
    //; }

    if (VerifyStringVal(strAcctAgentName))
    {
        print("Account '" + strAcctName + "' (party '" + strPartyName + "') is managed by agent: " + strAcctAgentName);
    }
    //  else
    //  {
    //      print("Account '"+strAcctName+"' (party '"+strPartyName+"') has no managing agent (yet.)")
    //; }
    return true;
}

OT_COMMAND_OT bool stat_partyaccount_index(const string & strSmartContract, const string & strPartyName, const int32_t nCurrentAccount)
{
    string strAcctName = OTAPI_Wrap::Party_GetAcctNameByIndex(strSmartContract, strPartyName, nCurrentAccount);

    if (!VerifyStringVal(strAcctName))
    {
        OTAPI_Wrap::Output(0, "Error: Failed retrieving Asset Account Name from party '" + strPartyName + "' at account index: " + to_string(nCurrentAccount) + "\n");
        return false;
    }
    return stat_partyaccount(strSmartContract, strPartyName, strAcctName, nCurrentAccount);
}


OT_COMMAND_OT bool stat_partyaccounts(const string & strSmartContract, const string & strPartyName, const int32_t nDepth)
{
    int32_t nAccountCount = OTAPI_Wrap::Party_GetAcctCount(strSmartContract, strPartyName);

    if (!VerifyIntVal(nAccountCount) || (nAccountCount < 0))
    {
        OTAPI_Wrap::Output(0, "Error: Party '" + strPartyName + "' has bad value for number of asset accounts.\n");
        return false;
    }

    if (nDepth > 0)
    {
        // Iterate the asset accounts for this party.
        //
        for (int32_t nCurrentAccount = 0; nCurrentAccount < nAccountCount; ++nCurrentAccount)
        {
            if (!stat_partyaccount_index(strSmartContract, strPartyName, nCurrentAccount)) { return false; }
        }
    }
    else
    {
        print("Party '" + strPartyName + "' has " + to_string(nAccountCount) + ((1 == nAccountCount) ? " asset account." : " asset accounts."));
    }

    return true;
}


OT_COMMAND_OT bool show_unconfirmed_parties(const string & strSmartContract)
{
    int32_t nPartyCount = 0;
    return show_unconfirmed_parties(strSmartContract, nPartyCount);
}


OT_COMMAND_OT bool show_unconfirmed_parties(const string & strSmartContract, int32_t & nPartyCount)
{
    if (!VerifyIntVal(nPartyCount) || (0 == nPartyCount))
    {
        nPartyCount = OTAPI_Wrap::Smart_GetPartyCount(strSmartContract);
        if (!VerifyIntVal(nPartyCount) || (nPartyCount < 0))
        {
            OTAPI_Wrap::Output(0, "Failure: There are apparently no PARTIES to this smart contract.\n");
            return false;
        }
    }

    // See if the smart contract is already confirmed by all parties.
    //
    if (OTAPI_Wrap::Smart_AreAllPartiesConfirmed(strSmartContract))
    {
        OTAPI_Wrap::Output(0, "Looks like all the parties on this contract are already confirmed.\n(Perhaps you want to 'activate' it instead.)\n");
        return false;
    }

    int32_t nUnconfirmedPartyCount = 0;

    for (int32_t nCurrentParty = 0; nCurrentParty < nPartyCount; ++nCurrentParty)
    {
        string strPartyName = OTAPI_Wrap::Smart_GetPartyByIndex(strSmartContract, nCurrentParty);

        if (!VerifyStringVal(strPartyName))
        {
            OTAPI_Wrap::Output(0, "Error: Unable to retrieve smart contract party's name at index: " + to_string(nCurrentParty) + "\n");
            return false;
        }

        bool bIsPartyConfirmed = OTAPI_Wrap::Smart_IsPartyConfirmed(strSmartContract, strPartyName);
        if (!bIsPartyConfirmed)
        {
            string strIndex = to_string(nCurrentParty);
            OTAPI_Wrap::Output(0, strIndex + " : Unconfirmed party: " + strPartyName + "\n");
            ++nUnconfirmedPartyCount;
        }
    } // for

    if (nUnconfirmedPartyCount <= 0)
    {
        OTAPI_Wrap::Output(0, "SHOULD NEVER HAPPEN: OT_API_Smart_AreAllPartiesConfirmed was already verified as false, above.\nSo then why am I at the bottom of this loop and I haven't found any unconfirmed parties?\n");
        return false;
    }

    return true;
}


// The merchant (sender of proposal / payee of proposal) proposes the payment plan
// to the customer (recipient of proposal / payer of proposal.) So this function is
// called by the merchant.
//
OT_COMMAND_OT int32_t details_propose_plan(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const string & strHisNymID, const string & strHisAcctID, const string & strDates, const string & strConsideration, const string & strInitialPayment, const string & strPaymentPlan, const string & strExpiry)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    if (!VerifyStringVal(strConsideration))
    {
        OTAPI_Wrap::Output(0, "Sorry, but you must describe the consideration to create a recurring payment plan.\n");
        return -1;
    }

    // Make sure strMyNymID aka recipient of money (aka sender of payment plan instrument)
    // has enough transaction numbers to propose the plan in the first place.
    //
    if (!madeEasy.insure_enough_nums(2, strServerID, strMyNymID)) // strMyNymID is Merchant.
    {
        return -1;
    }

    // OTAPI_Wrap::EasyProposePlan is a version of ProposePaymentPlan that compresses it into a
    // fewer number of arguments. (Then it expands them and calls ProposePaymentPlan.)
    // Basically this version has ALL the same parameters, but it stuffs two or three at a time into
    // a single parameter, as a comma-separated list in string form.
    // See details for each parameter, in the comment below.
    //
    string strPlan = OTAPI_Wrap::EasyProposePlan(strServerID, strDates, strHisAcctID, strHisNymID, strConsideration, strMyAcctID, strMyNymID, strInitialPayment, strPaymentPlan, strExpiry);

    // std::string EasyProposePlan(
    //    const std::string & SERVER_ID,
    //    // ----------------------------------------
    //    const std::string & DATE_RANGE,           // "from,to"  Default 'from' (0 or "") == NOW,
    //    // ---------------------------------------- // and default 'to' (0 or "") == no expiry / cancel anytime
    //    const std::string & SENDER_ACCT_ID,     // strHisAcctID. Mandatory parameters.
    //    const std::string & SENDER_USER_ID,     // strHisNymID. Both sender and recipient must sign before submitting.
    //    // ----------------------------------------
    //    const std::string & PLAN_CONSIDERATION, // Like a memo.
    //    // ----------------------------------------
    //    const std::string & RECIPIENT_ACCT_ID, // strMyAcctID. NOT optional.
    //    const std::string & RECIPIENT_USER_ID, // strMyNymID. Both sender and recipient must sign before submitting.
    //    // -------------------------------
    //    const std::string & INITIAL_PAYMENT, // "amount,delay"  Default 'amount' (0 or "") == no initial payment.
    //    // ------------------------------- // Default 'delay' (0 or NULL) is seconds from creation date.
    //    const std::string & PAYMENT_PLAN,   // "amount,delay,period" 'amount' is a recurring payment.
    //    // -------------------------------  // 'delay' and 'period' cause 30 days if you pass 0 or "".
    //    const std::string & PLAN_EXPIRY // "length,number" 'length' is maximum lifetime in seconds.
    //    );                              // 'number' is maximum number of payments in seconds. 0 or "" is unlimited (for both.)


    if (VerifyStringVal(strPlan))
    {
        // The "propose" step (performed by the merchant) includes the merchant's confirmation / signing.
        // (So there's no need for the merchant to additionally "confirm" the plan before sending it -- he
        // already has done that by this point, just as part of the proposal itself.)

        // Send the payment plan to the payer (the customer). If it fails, harvest the transaction numbers
        // back from the payment plan. Return 1 if success.

        string strResponse = madeEasy.send_user_payment(strServerID, strMyNymID, strHisNymID, strPlan);
        int32_t nMessageSuccess = VerifyMessageSuccess(strResponse);

        if (!VerifyIntVal(nMessageSuccess) || (1 != nMessageSuccess))
        {
            OTAPI_Wrap::Output(0, "For whatever reason, our attempt to send the payment plan on to the next user has failed.\n");
            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strPlan, strMyNymID,
                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a payment plan, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and thus we're harvesting ALL numbers. Period.)
            OTAPI_Wrap::Output(0, "details_propose: OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
            return -1;
        }
        // else success
        return nMessageSuccess;
    }

    return -1;
}


OT_COMMAND_OT int32_t main_propose_plan() // payment plan -- called by recipient. (Who generates the proposal.)
{
    string strUsage1 = "Usage: opentxs propose   (For a merchant to propose a payment plan to a customer.)\nMandatory: --server SERVER_ID --mynym PAYEE_NYM_ID --hisnym PAYER_NYM_ID\nMandatory: --myacct PAYEE_ACCT_ID --hisacct PAYER_NYM_ID\nAdditional arguments:\n Date Range: --args \" date_range \\\"from,to\\\" \"\nFROM should be in seconds from Jan 1970, and TO is added to that number.\nDefault FROM is the current time, and default TO is 'no expiry.'\n";
    string strUsage2 = concat(strUsage1, "Also: --args \" consideration \\\"like a memo\\\" \" \n");
    string strUsage3 = concat(strUsage2, "Also: --args \" initial_payment \\\"amount,delay\\\" \" \nDefault 'amount' (0 or \"\") == no initial payment. Default 'delay' (0 or \"\") is seconds from creation date.\n");
    string strUsage4 = concat(strUsage3, "Also: --args \" payment_plan \\\"amount,delay,period\\\" \" \n'amount' is a recurring payment. 'delay' and 'period' cause 30 days if you pass 0 or \"\".\n'delay' and 'period' are both measured in seconds. Period is time between\neach payment. Delay is time until first payment.\n");
    string strUsage = concat(strUsage4, "Also: --args \" plan_expiry \\\"length,number\\\" \" \n'length' is maximum lifetime in seconds. 'number' is maximum number of payments. 0 or \"\" is unlimited (for both.)\n\n");

    OTAPI_Wrap::Output(0, strUsage);
    // **************************************************************
    // recipient nym        // recipient acct        // sender nym             // sender acct
    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("MyAcct") && VerifyExists("HisNym") && VerifyExists("HisAcct"))
    {
        string strDates = "";
        string strConsideration = "";
        string strInitialPayment = "";
        string strPaymentPlan = "";
        string strExpiry = "";

        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "index 1"
            //
            string strTempDates = OT_CLI_GetValueByKey(Args, "date_range"); // "from,to"  Default 'from' (0 or "") == NOW (otherwise pass the time in seconds), and default 'to' (0 or "") == no expiry / cancel anytime (otherwise pass this time in seconds as well.)
            string strTempConsideration = OT_CLI_GetValueByKey(Args, "consideration"); // Like a memo.
            string strTempInitialPayment = OT_CLI_GetValueByKey(Args, "initial_payment"); // "amount,delay"  Default 'amount' (0 or "") == no initial payment. Default 'delay' (0 or NULL) is seconds from creation date.
            string strTempPaymentPlan = OT_CLI_GetValueByKey(Args, "payment_plan"); // "amount,delay,period" 'amount' is a recurring payment. 'delay' and 'period' cause 30 days if you pass 0 or "".
            string strTempExpiry = OT_CLI_GetValueByKey(Args, "plan_expiry"); // "length,number" 'length' is maximum lifetime in seconds. 'number' is maximum number of payments. 0 or "" is unlimited (for both.)

            if (VerifyStringVal(strTempDates)) { strDates = strTempDates; }
            if (VerifyStringVal(strTempConsideration)) { strConsideration = strTempConsideration; }
            if (VerifyStringVal(strTempInitialPayment)) { strInitialPayment = strTempInitialPayment; }
            if (VerifyStringVal(strTempPaymentPlan)) { strPaymentPlan = strTempPaymentPlan; }
            if (VerifyStringVal(strTempExpiry)) { strExpiry = strTempExpiry; }
        }
        OTAPI_Wrap::Output(0, "\n"); // stderr
        // ***************************************************************

        if (!VerifyStringVal(strConsideration))
        {
            OTAPI_Wrap::Output(0, "\nDescribe the product or service being received in return for the\nrecurring payments, followed by a ~ by itself on a blank line:\n\n");

            strConsideration = OT_CLI_ReadUntilEOF();

            if (!VerifyStringVal(strConsideration))
            {
                return -1;
            }
        }

        // ***************************************************************
        OTAPI_Wrap::Output(0, "date_range (from,to): " + strDates + "\n"); // stderr
        OTAPI_Wrap::Output(0, "consideration: " + strConsideration + "\n"); // stderr
        OTAPI_Wrap::Output(0, "initial_payment (amount,delay): " + strInitialPayment + "\n"); // stderr
        OTAPI_Wrap::Output(0, "payment_plan (amount,delay,period): " + strPaymentPlan + "\n"); // stderr
        OTAPI_Wrap::Output(0, "plan_expiry (length,number): " + strExpiry + "\n"); // stderr

        return details_propose_plan(Server, MyNym, MyAcct, HisNym, HisAcct, strDates, strConsideration, strInitialPayment, strPaymentPlan, strExpiry);
    }

    return -1;
}


// NOTE: if nIndex is NOT -1, then it's in the payments inbox for Server and MyNym, and we
// need to go ahead and
// the serverID must be found on the instrument, or must be provided as Server, or we must ask
// the user to enter it.
//
OT_COMMAND_OT int32_t details_confirm_plan(const string & strPlan, const int32_t nIndex)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strLocation = "details_confirm_plan";

    //    std::string ConfirmPaymentPlan(
    //       const std::string & SERVER_ID,
    //       const std::string & SENDER_USER_ID,
    //       const std::string & SENDER_ACCT_ID,
    //       const std::string & RECIPIENT_USER_ID,
    //       const std::string & PAYMENT_PLAN);

    string strServerID = OTAPI_Wrap::Instrmnt_GetServerID(strPlan);
    string strSenderUserID = OTAPI_Wrap::Instrmnt_GetSenderUserID(strPlan);
    string strSenderAcctID = OTAPI_Wrap::Instrmnt_GetSenderAcctID(strPlan);
    string strRecipientUserID = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strPlan);

    if (VerifyStringVal(strServerID) && VerifyStringVal(strSenderUserID) && VerifyStringVal(strSenderAcctID) && VerifyStringVal(strRecipientUserID) && VerifyStringVal(strPlan))
    {
        //      OTAPI_Wrap::Output(0, "Here's the payment plan, FYI:\n\n" + strPlan + "\n");

        // Make sure strSenderUserID aka sender of money (aka recipient of payment plan
        // instrument in his inbox, which if confirmed will have him sending money...)
        // has enough transaction numbers to confirm the plan.
        //
        if (!madeEasy.insure_enough_nums(2, strServerID, strSenderUserID)) // strSenderUserID is Customer.
        {
            return -1;
        }

        string strConfirmed = OTAPI_Wrap::ConfirmPaymentPlan(strServerID, strSenderUserID, strSenderAcctID, strRecipientUserID, strPlan);

        if (VerifyStringVal(strConfirmed))
        {
            //          OTAPI_Wrap::Output(0, "Here's the CONFIRMED payment plan, FYI:\n\n" + strConfirmed + "\n");

            // Below this point, inside this block, if we fail, then we need to harvest the transaction
            // numbers back from the payment plan that we confirmed (strConfirmed.)
            //
            string strResponse = madeEasy.deposit_payment_plan(strServerID, strSenderUserID, strConfirmed);
            string strAttempt = "deposit_payment_plan";
            // ***************************************************************
            int32_t nMessageSuccess = VerifyMessageSuccess(strResponse);

            // These are cases where the transaction never even got to TRY to run, since the message itself
            // failed inside the server before it even got that far.
            //
            if (-1 == nMessageSuccess)
            {
                // In this case, the server never even SAW the transaction, because its enveloping message already
                // failed before we even got that far. So we can harvest, as though it was never attempted...
                //
                OTAPI_Wrap::Output(0, "Message error: " + strAttempt + ".\n");
                int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strConfirmed, strSenderUserID,
                    false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                return -1;
            }
            else if (0 == nMessageSuccess)
            {
                OTAPI_Wrap::Output(0, "Server reply (" + strAttempt + "): Message failure.\n");
                int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strConfirmed, strSenderUserID,
                    false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                return 0;
            }
            // (else 1: message was processed successfully -- though not necessarily the transaction inside it.)

            // BELOW THIS POINT, the transaction has definitely processed. It may have succeeded or failed,
            // but either way, we don't need to harvest any numbers, since OT will internally handle those
            // when it processes the server's reply to the transaction attempt.
            //
            int32_t nInterpretReply = InterpretTransactionMsgReply(strServerID, strSenderUserID, strSenderAcctID, strAttempt, strResponse);

            if (1 == nInterpretReply) // Success.
            {
                // Download all the intermediary files (account balance, inbox, outbox, etc)
                // since they have probably changed from this operation.
                //
                bool bRetrieved = madeEasy.retrieve_account(strServerID, strSenderUserID, strSenderAcctID, true); //bForceDownload defaults to false.

                OTAPI_Wrap::Output(0, "\nServer response (" + strAttempt + "): SUCCESS activating payment plan!\n");
                OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");
            }
            //
            // Return status to caller.
            //
            return nInterpretReply;
        }
    }
    return -1;
}


// NOTE: if nIndex is -1, then it's assumed the instrument was PASTED in, and therefore
// the serverID must be found on the instrument, or must be provided as Server, or we must ask
// the user to enter it. Then the Nym [and potentially AcctID] must be ascertained by walking
// the user through the instrument, and by making him choose a Nym and Acct(s) for the party
// he's confirming as.
//
// But if an index is provided, then it's ASSUMED the index goes to the payments inbox, and
// that therefore Server and MyNym must have been provided at the command line already, or
// otherwise that index could not logically have been matched up to the proper box.
//
// If SOME parties have already confirmed the contract before you, then it SHOULD already have
// a serverID attached to it. If a Server is also provided at the command line, then the two must
// match, since the ID cannot be changed after that point.
//


OT_COMMAND_OT int32_t details_confirm_smart_contract(string & strSmartContract, const int32_t nIndex)
{
    string strLocation = "details_confirm_smart_contract";


    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    int32_t nPartyCount = OTAPI_Wrap::Smart_GetPartyCount(strSmartContract);

    if (!VerifyIntVal(nPartyCount) || (nPartyCount <= 0))
    {
        OTAPI_Wrap::Output(0, "Failed trying to confirm a smart contract: there are apparently no PARTIES to this contract!\n");
        return -1;
    }

    // We don't need MyAcct except when actually ACTIVATING the smart contract on the server.
    // This variable might get set later to MyAcct, if it matches one of the accounts being
    // confirmed. (Meaning if this variable is set by the time we reach the bottom, then we
    // can use it for activation, if/when needed.)
    //
    string strMyAcctID = "";
    string strMyAcctAgentName = "";

    string strServerID = "";
    string strNymID = "";

    map<string, string> map_ID; // We'll store the account IDs here, for each PartyAcct
    map<string, string> map_agent; // We'll store the agent names here, for each PartyAcct

    // By this point we know it's a smart contract, and there is at least
    // one party that is still unconfirmed on this contract.
    // Therefore let's loop through the parties and display the
    // unconfirmed ones.
    //
    if (show_unconfirmed_parties(strSmartContract, nPartyCount))
    {

        // By this point I know that nUnconfirmedPartyCount is larger than 0.
        // Therefore we displayed the unconfirmed ones...
        // Let's ask the user to choose one to confirm as....
        //
        OTAPI_Wrap::Output(0, "\n\nWhich party are you? Enter the number, from the list above: ");

        string strPartyIndex = OT_CLI_ReadLine();

        if (VerifyStringVal(strPartyIndex))
        {
            int32_t nCurrentParty = to_int(strPartyIndex);

            if (VerifyIntVal(nCurrentParty) && (nCurrentParty >= 0) && (nCurrentParty < nPartyCount))
            {
                string strPartyName = OTAPI_Wrap::Smart_GetPartyByIndex(strSmartContract, nCurrentParty);

                if (!VerifyStringVal(strPartyName))
                {
                    OTAPI_Wrap::Output(0, "Error: Unable to retrieve smart contract party's name at index: " + to_string(nCurrentParty) + "\n");
                    return -1;
                }

                if (OTAPI_Wrap::Smart_IsPartyConfirmed(strSmartContract, strPartyName))
                {
                    OTAPI_Wrap::Output(0, "Failure: the party at that index is _already_ confirmed.\n");
                    return -1;
                }

                // At this point we know it's a valid index for an unconfirmed party.
                // And we know that strPartyName is the party's name.
                //
                // So how many accounts does strPartyName have? We must confirm those, too.
                //
                int32_t nAccountCount = OTAPI_Wrap::Party_GetAcctCount(strSmartContract, strPartyName);

                if (!VerifyIntVal(nAccountCount) || (nAccountCount < 0))
                {
                    OTAPI_Wrap::Output(0, "Error: Party '" + strPartyName + "' has a bad value for number of asset accounts.\n");
                    return -1;
                }

                // Confirm the accounts.
                //
                if (nAccountCount > 0)
                {
                    // In the loop, if we have to devise the serverID, we store it in this var so we don't devise twice.
                    string strFoundServerID = "";
                    string strFoundMyNymID = "";
                    int32_t nCurrentAcctCount = nAccountCount;

                    while (nCurrentAcctCount > 0)
                    {
                        OTAPI_Wrap::Output(0, "\n");
                        stat_partyaccounts(strSmartContract, strPartyName, 2); //nDepth=2

                        OTAPI_Wrap::Output(0, "\n There are " + to_string(nCurrentAcctCount) + " asset accounts remaining to be confirmed.\nEnter the index for an UNconfirmed account: ");

                        string strAcctIndex = OT_CLI_ReadLine();

                        if (!VerifyStringVal(strAcctIndex))
                        {
                            return -1;
                        }

                        int32_t nAcctIndex = to_int(strAcctIndex);

                        if (!VerifyIntVal(nAcctIndex) || (nAcctIndex < 0))
                        {
                            OTAPI_Wrap::Output(0, "Error: Bad Index: " + strAcctIndex + "\n");
                            return -1;
                        }

                        string strAcctName = OTAPI_Wrap::Party_GetAcctNameByIndex(strSmartContract, strPartyName, nAcctIndex);

                        if (!VerifyStringVal(strAcctName))
                        {
                            OTAPI_Wrap::Output(0, "Error: Unable to retrieve account name at index " + strAcctIndex + " for Party: " + strPartyName + "\n");
                            return -1;
                        }

                        bool bAlreadyThere = false;

                        for (map<string, string>::iterator x = map_ID.begin(); x != map_ID.end(); x++)
                        {
                            if (x->first == strAcctName) { bAlreadyThere = true; }
                        }

                        string strAcctID = OTAPI_Wrap::Party_GetAcctID(strSmartContract, strPartyName, strAcctName);

                        if (bAlreadyThere || VerifyStringVal(strAcctID))  // This account is ALREADY confirmed! It has an account ID already.
                        {
                            OTAPI_Wrap::Output(0, "\nSorry, but the account at index " + strAcctIndex + " is already confirmed with account ID: " + strAcctID + " \nYou are just going to have to pick a different account.\n");
                        }
                        else // The account is NOT already confirmed (so we can confirm it, once we select the Acct ID to use.)
                        {

                            string strServerOnContract = OTAPI_Wrap::Instrmnt_GetServerID(strSmartContract);
                            bool bServerOnContract = VerifyStringVal(strServerOnContract);

                            // Now we need to ascertain the server and Nym ID...

                            if (-1 != nIndex) // The instrument was selected from the payments inbox at a given index.
                            {
                                strServerID = Server;  // These match up to the payments inbox that was used.
                                strNymID = MyNym;

                                // If there's a server listed on the contract (there may not be, if this is the FIRST
                                // confirmation) AND if that Server ID doesn't match the one passed in on the command line...
                                //
                                if (bServerOnContract && (strServerID != strServerOnContract))
                                {
                                    string strServerName = OTAPI_Wrap::GetServer_Name(strServerOnContract);
                                    if (!VerifyStringVal(strServerName)) { strServerName = ""; }
                                    OTAPI_Wrap::Output(0, "The server ID on the smart contract, " + strServerOnContract + " (" + strServerName + ") doesn't match the server selected at the command line with the --server option.\n");
                                    return -1;
                                }
                            }
                            else // the instrument was pasted in.
                            {
                                if (bServerOnContract)
                                {
                                    strServerID = strServerOnContract;
                                }
                                else if (VerifyExists("Server", false))
                                {
                                    strServerID = Server;
                                }
                                else if (VerifyStringVal(strFoundServerID)) // We might have already figured it out. (The block after this one should only happen once, if at all.)
                                {
                                    strServerID = strFoundServerID;
                                }
                                else // There's no server on the contract, AND there's no server chosen at the command line.
                                {
                                    int32_t nServerCount = OTAPI_Wrap::GetServerCount();

                                    if (nServerCount < 1)
                                    {
                                        OTAPI_Wrap::Output(0, "Sorry, there aren't any server contracts in this wallet. Try 'opentxs addserver'\n");
                                        return -1;
                                    }

                                    stat_servers();

                                    OTAPI_Wrap::Output(0, "Paste a server ID: ");

                                    string strServerIDInput = OT_CLI_ReadLine();

                                    if (!VerifyStringVal(strServerIDInput))
                                    {
                                        return -1;
                                    }

                                    strServerID = strServerIDInput;
                                    strFoundServerID = strServerIDInput; // So we're not forced to select the server EVERY iteration...
                                }

                                if (VerifyExists("MyNym", false))
                                {
                                    strNymID = MyNym;
                                }
                                else if (VerifyStringVal(strFoundMyNymID))
                                {
                                    strNymID = strFoundMyNymID;
                                }
                                else
                                {
                                    int32_t nNymCount = OTAPI_Wrap::GetNymCount();

                                    if (nNymCount < 1)
                                    {
                                        OTAPI_Wrap::Output(0, "There are apparently no Nyms in this wallet. Try 'opentxs newnym'\n");
                                        return -1;
                                    }
                                    while (true) // Choose a Nym.
                                    {
                                        print("------------------------------------------------------------------");
                                        print(" ** PSEUDONYMS (filtered by serverID: " + strServerID + "): " + "\n");

                                        bool bFoundANym = false;

                                        for (int32_t i = 0; i < nNymCount; ++i)
                                        {
                                            string strIndex = to_string(i);
                                            string strLoopNymID = OTAPI_Wrap::GetNym_ID(i);

                                            if (OTAPI_Wrap::IsNym_RegisteredAtServer(strLoopNymID, strServerID))
                                            {
                                                bFoundANym = true;
                                                string strName = OTAPI_Wrap::GetNym_Name(strLoopNymID);
                                                OTAPI_Wrap::Output(0, strIndex + ": " + strLoopNymID + " ---  " + strName + "\n");
                                            }
                                        }

                                        if (!bFoundANym)
                                        {
                                            OTAPI_Wrap::Output(0, "Unfortunately, didn't find ANY Nyms registered at server: " + strServerID + "\n");
                                            return -1;
                                        }

                                        OTAPI_Wrap::Output(0, "\n Select a Nym by index: ");

                                        string strNymIndex = OT_CLI_ReadLine();

                                        if (!VerifyStringVal(strNymIndex))
                                        {
                                            return -1;
                                        }

                                        int32_t nNymIndex = to_int(strNymIndex);
                                        if (!VerifyIntVal(nNymIndex) || (nNymIndex < 0))
                                        {
                                            OTAPI_Wrap::Output(0, "Bad index: " + strNymIndex + "\n");
                                            return -1;
                                        }

                                        string strTempNymID = OTAPI_Wrap::GetNym_ID(nNymIndex);

                                        if (!VerifyStringVal(strTempNymID))
                                        {
                                            OTAPI_Wrap::Output(0, "Error retrieving NymID from wallet at index: " + strNymIndex + "\n");
                                            return -1;
                                        }

                                        if (OTAPI_Wrap::IsNym_RegisteredAtServer(strTempNymID, strServerID))
                                        {
                                            strNymID = strTempNymID;
                                            strFoundMyNymID = strTempNymID;
                                            break;
                                        }
                                        else
                                        {
                                            OTAPI_Wrap::Output(0, "Sorry, that Nym isn't registered at server: " + strServerID + "\nPlease choose another Nym\n");
                                        }
                                    } // while (selecting a Nym)
                                } // Determining NymID
                            } // else instrument was pasted in.


                            // By this point, we definitely have strServerID and strNymID

                            // Loop through all the accounts for that Server/Nym, display them, allow the user to
                            // choose one and then store it in a list somewhere for the actual confirmation.
                            // (Which we will do only after ALL accounts have been selected.) We will also make sure
                            // to prevent from selecting an account that already appears on that list.
                            //
                            // Also, when we actually add an Acct ID to the list, we need to decrement nCurrentAcctCount,
                            // so that we are finished once all the accounts from the smart contract template have had
                            // actual acct IDs selected for each.
                            //
                            string strTemplateAssetID = OTAPI_Wrap::Party_GetAcctAssetID(strSmartContract, strPartyName, strAcctName);
                            bool bFoundTemplateAssetID = VerifyStringVal(strTemplateAssetID);

                            bool bFoundAccounts = false;
                            int32_t nCountAcctsWallet = OTAPI_Wrap::GetAccountCount();

                            OTAPI_Wrap::Output(0, "\nAccounts by index (filtered by serverID and nymID):\n\n");

                            for (int32_t i = 0; i < nCountAcctsWallet; ++i)
                            {
                                string strWalletAcctID = OTAPI_Wrap::GetAccountWallet_ID(i);

                                if (!VerifyStringVal(strWalletAcctID))
                                {
                                    OTAPI_Wrap::Output(0, "Error reading account ID based on index: " + to_string(i) + "\n");
                                    return -1;
                                }

                                string strAcctServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strWalletAcctID);
                                string strAcctNymID = OTAPI_Wrap::GetAccountWallet_NymID(strWalletAcctID);
                                string strAcctAssetID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strWalletAcctID);

                                bool bAlreadyOnTheMap = false;


                                for (map<string, string>::iterator x = map_ID.begin(); x != map_ID.end(); x++)
                                {
                                    if (x->second == strWalletAcctID) { bAlreadyOnTheMap = true; }
                                }

                                if ((strServerID == strAcctServerID) && (strNymID == strAcctNymID))
                                {
                                    // If the smart contract doesn't specify the asset type ID of the account, or if
                                    // it DOES specify, AND they match, then it's a viable choice. Display it.
                                    //
                                    if (!bFoundTemplateAssetID || (bFoundTemplateAssetID && (strTemplateAssetID == strAcctAssetID)))
                                    {

                                        if (!bAlreadyOnTheMap)  // DO NOT display any accounts that have already been selected! (Search the temp map where we've been stashing them.)
                                        {
                                            bFoundAccounts = true;
                                            string strAccountName = OTAPI_Wrap::GetAccountWallet_Name(strWalletAcctID);
                                            if (!VerifyStringVal(strAccountName)) { strAccountName = ""; }
                                            OTAPI_Wrap::Output(0, to_string(i) + " : " + strWalletAcctID + " (" + strAccountName + ")\n");
                                        }
                                    }
                                }
                            } // for

                            if (!bFoundAccounts)
                            {
                                OTAPI_Wrap::Output(0, "Unfortunately, looks like there are no accounts matching the specified Nym (" + strNymID + ") and Server (" + strServerID + ")\nTry:  opentxs newacct --mynym " + strNymID + " --server " + strServerID + " \n");
                                return -1;
                            }

                            OTAPI_Wrap::Output(0, "\nChoose an account by index (for '" + strAcctName + "'): ");

                            string strSelectedAcctIndex = OT_CLI_ReadLine();

                            if (!VerifyStringVal(strSelectedAcctIndex))
                            {
                                return -1;
                            }

                            int32_t nSelectedAcctIndex = to_int(strSelectedAcctIndex);

                            if (!VerifyIntVal(nSelectedAcctIndex) || (nSelectedAcctIndex < 0) || (nSelectedAcctIndex >= nCountAcctsWallet))
                            {
                                OTAPI_Wrap::Output(0, "Bad index: " + strSelectedAcctIndex + "\n");
                                return -1;
                            }

                            string strWalletAcctID = OTAPI_Wrap::GetAccountWallet_ID(nSelectedAcctIndex);

                            if (!VerifyStringVal(strWalletAcctID))
                            {
                                OTAPI_Wrap::Output(0, "Error reading account ID based on index: " + to_string(nSelectedAcctIndex) + "\n");
                                return -1;
                            }

                            string strAcctServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strWalletAcctID);
                            string strAcctNymID = OTAPI_Wrap::GetAccountWallet_NymID(strWalletAcctID);
                            string strAcctAssetID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strWalletAcctID);

                            if ((strServerID == strAcctServerID) && (strNymID == strAcctNymID))
                            {
                                // If the smart contract doesn't specify the asset type ID of the account, or if
                                // it DOES specify, AND they match, then it's a viable choice. Allow it.
                                //
                                if (!bFoundTemplateAssetID || (bFoundTemplateAssetID && (strTemplateAssetID == strAcctAssetID)))
                                {

                                    bool bAlreadyOnIt = false;

                                    for (map<string, string>::iterator x = map_ID.begin(); x != map_ID.end(); x++)
                                    {
                                        if (x->second == strWalletAcctID) { bAlreadyOnIt = true; }
                                    }

                                    if (bAlreadyOnIt)  // make sure it's not already on the map of selected accounts.
                                    {
                                        OTAPI_Wrap::Output(0, "Sorry, you already selected this account. Choose another.\n");
                                    }
                                    else
                                    {
                                        // strWalletAcctID has been selected for strPartyName's account, strAcctName.
                                        // Add these to a map or whatever, to save them until this loop is complete.
                                        //

                                        string strAgentName = OTAPI_Wrap::Party_GetAcctAgentName(strSmartContract, strPartyName, strAcctName);

                                        if (!VerifyStringVal(strAgentName))
                                        {
                                            OTAPI_Wrap::Output(0, "\n");

                                            if (stat_partyagents(strSmartContract, strPartyName, 3))
                                            {
                                                OTAPI_Wrap::Output(0, "\n (This choice is arbitrary, but you must pick one.)\nEnter the index for an agent, to have authority over that account: ");

                                                string strAgentIndex = OT_CLI_ReadLine();

                                                if (!VerifyStringVal(strAgentIndex))
                                                {
                                                    return -1;
                                                }

                                                int32_t nAgentIndex = to_int(strAgentIndex);

                                                if (!VerifyIntVal(nAgentIndex) || (nAgentIndex < 0))
                                                {
                                                    OTAPI_Wrap::Output(0, "Error: Bad Index: " + strAgentIndex + "\n");
                                                    return -1;
                                                }

                                                strAgentName = OTAPI_Wrap::Party_GetAgentNameByIndex(strSmartContract, strPartyName, nAgentIndex);

                                                if (!VerifyStringVal(strAgentName))
                                                {
                                                    OTAPI_Wrap::Output(0, "Error: Unable to retrieve agent name at index " + strAgentIndex + " for Party: " + strPartyName + "\n");
                                                    return -1;
                                                }

                                            }
                                            else
                                            {
                                                OTAPI_Wrap::Output(0, "Failed finding the agent's name for party: " + strPartyName + " Account: " + strAcctName + " \n And then failed finding any agents on this smart contract at ALL.\n");
                                                return -1;
                                            }
                                        }

                                        map_ID[strAcctName] = strWalletAcctID;
                                        map_agent[strAcctName] = strAgentName;

                                        nCurrentAcctCount -= 1;

                                    }
                                }
                            }
                        } // else the account is NOT already confirmed (so we can confirm it.)
                    } // while (nCurrentAcctCount > 0)


                    for (map<string, string>::iterator x = map_ID.begin(); x != map_ID.end(); x++)
                    {
                        int32_t numCountNeeded = OTAPI_Wrap::SmartContract_CountNumsNeeded(strSmartContract, map_agent[x->first]) + 1;

                        if (!madeEasy.insure_enough_nums(numCountNeeded, strServerID, strNymID)) // Someday there might be a different NymID based on which agent it is...
                        {
                            OTAPI_Wrap::Output(0, "\n** Sorry -- Nym (" + strNymID + ") doesn't have enough transaction numbers to confirm this smart contract. Come back when you have more.\n");
                            return -1;
                        }
                    }

                    // CONFIRM THE ACCOUNTS HERE
                    //
                    // By this point we KNOW we have enough transaction numbers
                    //
                    // Note: Any failure below this point needs to harvest back ALL transaction numbers.
                    // Because we haven't even TRIED to activate it, therefore ALL numbers on the contract
                    // are still good (even the opening number.)
                    //
                    // Whereas after a failed activation, we'd need to harvest only the closing numbers, and
                    // not the opening numbers. But in here, this is confirmation, not activation.
                    //
                    for (map<string, string>::iterator x = map_ID.begin(); x != map_ID.end(); x++)
                    {
                        // Here we check to see if MyAcct exists -- if so we compare it to the current acctID
                        // and if they match, we set strMyAcctID. Later on, if/when activating, we can just use
                        // strMyAcctID to activate. (Otherwise we will have to pick one from the confirmed accounts.)
                        //
                        if (!VerifyStringVal(strMyAcctID) && VerifyExists("MyAcct", false) && (MyAcct == x->second))
                        {
                            strMyAcctID = MyAcct; // Now we can use it later, for activation.
                            strMyAcctAgentName = map_agent[x->first];
                        }

                        // CONFIRM A THEORETICAL ACCT BY GIVING IT A REAL ACCT ID.
                        string strTempSmart = OTAPI_Wrap::SmartContract_ConfirmAccount(strSmartContract, strNymID, strPartyName,

                            x->first,             // Acct name.
                            map_agent[x->first], // The agent name for this asset account.
                            x->second);           // AcctID for the asset account. (For acct_name).
                        if (VerifyStringVal(strTempSmart))
                        {
                            strSmartContract = strTempSmart;
                        }
                        else
                        {
                            OTAPI_Wrap::Output(0, "Failure while calling OT_API_SmartContract_ConfirmAccount. Acct Name: " + x->first + "  Agent Name: " + map_agent[x->first] + "  Acct ID: " + x->second + " \n");
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }
                    }

                } // if (nCurrentAcctCount > 0)

                // CONFIRM THE NYM HERE.
                //
                // NOTE: confirming the Party will drop a copy into the outpayments box.
                // After that, if you are not the last party, you will send it on to
                // the next party. This will also drop it into the outpayments box, but
                // when that happens, it will automatically first remove the prior
                // one that had been dropped. This way there is only one copy in
                // the outbox, not two.
                //
                // If you ARE the last party, then we will activate it here, and
                // when the server reply is received, it will be removed from the
                // outbox and moved to the record box.
                //
                // Also, whether it succeeds or fails activation, either way, a notice
                // will be dropped to all the parties, informing them of this fact.
                // The activating party will ignore this, since he already processes
                // the server reply directly when he receives it. (And there's a copy of
                // that in his nymbox to make SURE he receives it, so he DEFINITELY
                // received it already.)
                // But each of the other parties will then move the notice from their
                // outbox to their record box. (And harvest the transaction numbers
                // accordingly.)
                // A party can "reject" a smart contract by activating it without signing
                // it. That way it will fail activation, and all the other parties will get
                // the failure notice, and harvest their numbers back as appropriate. But if
                // he is "rude" and simply discards the contract WITHOUT rejecting it, then
                // they will never get the failure notice. However, they will also never
                // get the activation notice, since it was never activated in that case, and
                // thus they will be safe to harvest their numbers back when it expires.
                // (A well-designed wallet will do this automatically.)
                //

                string strTempSmart = OTAPI_Wrap::SmartContract_ConfirmParty(strSmartContract, strPartyName, strNymID);

                if (VerifyStringVal(strTempSmart))
                {
                    strSmartContract = strTempSmart;
                }
                else
                {
                    OTAPI_Wrap::Output(0, "Failure while calling OT_API_SmartContract_ConfirmParty. Party Name: " + strPartyName + "  NymID: " + strNymID + "\n");
                    int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                        false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                    OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                    return -1;
                }

                // If you are the last party to sign, then ACTIVATE THE SMART CONTRACT.

                // NOTE: No matter which party you are (perhaps you are the middle one), when you confirm
                // the contract, you will send it on to the NEXT UNCONFIRMED ONE. This means you don't know
                // which party it will be, since all the unconfirmed parties have no NymID (yet.) Rather,
                // it's YOUR problem to provide the NymID you're sending the contract on to. And then it's HIS
                // problem to decide which party he will sign on as. (Unless you are the LAST PARTY to confirm,
                // in which case YOU are the activator.)
                //
                if (OTAPI_Wrap::Smart_AreAllPartiesConfirmed(strSmartContract))
                {
                    // The logic: If all the parties are confirmed, then just activate the thing. I must be the activator.
                    // We need the ACCT_ID that we're using to activate it with, and we need the AGENT NAME for that account.
                    // strMyAcctID and strMyAcctAgentName might ALREADY be set -- otherwise we need to set those.
                    //
                    if (!VerifyStringVal(strMyAcctID) || !VerifyStringVal(strMyAcctAgentName)) // Both will be valid or invalid, if one is. (But we check anyway.)
                    {
                        // We can't just use ANY account ID, but we must use one that is listed as one of the accounts for
                        // the party activating the contract. So we have to display those accounts, and the user must choose
                        // which one it's going to be. From there we can get the account ID and the agent name and call
                        // activate_smart_contract.
                        //
                        stat_partyaccounts(strSmartContract, strPartyName, 2); //nDepth=2

                        OTAPI_Wrap::Output(0, "\n\n Enter the index for the account you'll use to ACTIVATE the smart contract: ");

                        string strAcctIndex = OT_CLI_ReadLine();

                        if (!VerifyStringVal(strAcctIndex))
                        {
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }

                        int32_t nAcctIndex = to_int(strAcctIndex);

                        if (!VerifyIntVal(nAcctIndex) || (nAcctIndex < 0) || (nAcctIndex >= nAccountCount))
                        {
                            OTAPI_Wrap::Output(0, "Error: Bad Index: " + strAcctIndex + " (Acceptable values are 0 through " + to_string(nAccountCount - 1) + ")\n");
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }

                        string strAcctName = OTAPI_Wrap::Party_GetAcctNameByIndex(strSmartContract, strPartyName, nAcctIndex);

                        if (!VerifyStringVal(strAcctName))
                        {
                            OTAPI_Wrap::Output(0, "Error: Unable to retrieve account name at index " + strAcctIndex + " for Party: " + strPartyName + "\n");
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }

                        string strAcctID = OTAPI_Wrap::Party_GetAcctID(strSmartContract, strPartyName, strAcctName);

                        if (!VerifyStringVal(strAcctID))
                        {
                            OTAPI_Wrap::Output(0, "Strange: the account at index " + strAcctIndex + " is not yet confirmed with any account ID. (Failure.)\n");
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }
                        strMyAcctID = strAcctID; // <============

                        string strAcctAgentName = OTAPI_Wrap::Party_GetAcctAgentName(strSmartContract, strPartyName, strAcctName);

                        if (!VerifyStringVal(strAcctAgentName))
                        {
                            OTAPI_Wrap::Output(0, "Strange: the account named: '" + strAcctName + "' doesn't seem to have any agent confirmed to it. (Failure.)\n");
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }
                        strMyAcctAgentName = strAcctAgentName;  // <============

                    } // strMyAcctID wasn't set already, so the above block sets it.

                    // NOTE: Above, you see us harvesting the transaction numbers if any error occurs, since we haven't even tried
                    // to send the instrument yet.
                    //
                    // But in this next section, we only want to do that if the transaction was definitely not processed by the server.
                    // (Whether that processing succeeded or failed being a separate question.)
                    //
                    string strResponse = madeEasy.activate_smart_contract(strServerID, strNymID, strMyAcctID, strMyAcctAgentName, strSmartContract);
                    string strAttempt = "activate_smart_contract";
                    // ***************************************************************
                    int32_t nMessageSuccess = VerifyMessageSuccess(strResponse);

                    if (-1 == nMessageSuccess)
                    {
                        // In this case, the server never even SAW the transaction, because its enveloping message already
                        // failed before we even got that far. So we can harvest, as though it was never attempted...
                        //
                        OTAPI_Wrap::Output(0, "Message error: " + strAttempt + ".\n");
                        int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                            false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                        OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                        return -1;
                    }
                    else if (0 == nMessageSuccess)
                    {
                        OTAPI_Wrap::Output(0, "Server reply (" + strAttempt + "): Message failure.\n");
                        int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                            false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                        OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                        return 0;
                    }
                    // (else 1: message was processed successfully -- though not necessarily the transaction inside it.)

                    // BELOW THIS POINT, the transaction has definitely processed. It may have succeeded or failed,
                    // but either way, we don't need to harvest any numbers, since OT will internally handle those
                    // when it processes the server's reply to the transaction attempt.
                    //
                    int32_t nInterpretReply = InterpretTransactionMsgReply(strServerID, strNymID, strMyAcctID, strAttempt, strResponse);

                    if (1 == nInterpretReply) // Success.
                    {
                        // Download all the intermediary files (account balance, inbox, outbox, etc)
                        // since they have probably changed from this operation.
                        //
                        bool bRetrieved = madeEasy.retrieve_account(strServerID, strNymID, strMyAcctID, true); //bForceDownload defaults to false.

                        OTAPI_Wrap::Output(0, "\nServer response (" + strAttempt + "): SUCCESS activating smart contract!\n");
                        OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");
                    }
                    //
                    // Return status to caller.
                    //
                    return nInterpretReply;
                } // if (all parties are confirmed)
                // ***************************************************************
                else // SEND INSTRUMENT TO NEXT PARTY.
                {
                    // But if all the parties are NOT confirmed, then we need to send it to the next guy. In that case:
                    // If HisNym is provided, and it's different than strNymID, then use it. He's the next receipient.
                    // If HisNym is NOT provided, then display the list of NymIDs, and allow the user to paste one. We can
                    // probably select him based on abbreviated ID or Name as well (I think there's an API call for that...)
                    //
                    string strHisNymID = "";

                    if (VerifyExists("HisNym", false))
                    {
                        strHisNymID = HisNym;
                    }

                    // If strHisNymID doesn't exist, or it's the same as strNymID, then ask the user to select
                    // a NymID for the recipient.
                    //
                    if (!VerifyStringVal(strHisNymID) || (strHisNymID == strNymID))
                    {
                        stat_nyms(); // Display the NymIDs

                        OTAPI_Wrap::Output(0, "\nOnce you confirm this contract, then we need to send it on to the\nnext party so he can confirm it, too.\n\nPlease PASTE a recipient Nym ID (the next party): ");
                        string strRecipientNymID = OT_CLI_ReadLine();
                        if (!VerifyStringVal(strRecipientNymID))
                        {
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }

                        string strHisNymParam = strRecipientNymID;

                        // IF we are able to resolve the HisNymId from a partial, then we
                        // replace the partial with the full version.
                        // (Otherwise we assume it's already a full ID and we don't mess with it.)
                        //
                        string strHisNymFromPartial = OTAPI_Wrap::Wallet_GetNymIDFromPartial(strRecipientNymID);

                        if (VerifyStringVal(strHisNymFromPartial))
                        {
                            strHisNymParam = strHisNymFromPartial;
                        }

                        strHisNymID = strHisNymParam;

                        if (strHisNymID == strNymID)
                        {
                            OTAPI_Wrap::Output(0, "\nSorry, but YOU cannot simultaneously be the SENDER _and_ the RECIPIENT. Choose another nym for one or the other.\n");
                            int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                                false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                            OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                            return -1;
                        }
                    }

                    // Send it to the next user!
                    //
                    string strResponse = madeEasy.send_user_payment(strServerID, strNymID, strHisNymID, strSmartContract);

                    int32_t nMessageSuccess = VerifyMessageSuccess(strResponse);

                    if (!VerifyIntVal(nMessageSuccess) || (1 != nMessageSuccess))
                    {
                        OTAPI_Wrap::Output(0, "\nFor whatever reason, our attempt to send the instrument on to the next user has failed.\n");
                        int32_t nHarvested = OTAPI_Wrap::Msg_HarvestTransactionNumbers(strSmartContract, strNymID,
                            false, false, false, false, false); // NOTE: all the 'false's here are unused in this case. (Since we're passing a smart contract, instead of a message, it means we are harvesting before the message even had a CHANCE to get sent. Meaning we didn't even TRY to send it, and we're harvesting ALL numbers. Period.)
                        OTAPI_Wrap::Output(0, strLocation + ": OT_API_Msg_HarvestTransactionNumbers: " + to_string(nHarvested) + "\n");
                    }
                    else // Success. (Remove the payment instrument we just successfully sent, from our payments inbox.)
                    {
                        // In the case of smart contracts, it might be sent on to a chain of 2 or 3 users,
                        // before finally being activated by the last one in the chain. All of the users in
                        // the chain (except the first one) will thus have a copy of the smart contract in
                        // their payments inbox AND outbox.
                        //
                        // But once the smart contract has successfully been sent on to the next user, and
                        // thus a copy of it is in my outbox already, then there is definitely no reason for
                        // a copy of it to stay in my inbox as well. Might as well remove that copy.
                        //
                        // We can't really expect to remove the payments inbox copy inside OT itself, when we
                        // receive the server's atSendUserInstrument reply message, without opening up the
                        // (encrypted) contents. (Although that would actually be ideal, since it would cover
                        // all cases included dropped messages...) But we CAN easily remove it RIGHT HERE.
                        // Perhaps in the future I WILL move this code to the atSendUserInstrument reply processing,
                        // but that will require it to be encrypted to my own key as well as the recipient's,
                        // which we already do for sending cash, but which we up until now have not done for
                        // the other instruments. So perhaps we'll start doing that sometime in the future, and
                        // then move this code.
                        //
                        // In the meantime, this is good enough.
                        //

                        OTAPI_Wrap::Output(0, "Success sending the agreement on to the next party.\n");

                        if (-1 != nIndex) // If the instrument was in the payments inbox (versus just being pasted in.)
                        {
                            OTAPI_Wrap::RecordPayment(strServerID, strNymID, true, // true == payments inbox. false == outpayments box.
                                nIndex, false); //bSaveCopy = false (it's already in my payments outbox, no need to save inbox copy too)
                        }
                    }
                    return nMessageSuccess;

                }
            }
        }
    } // ---------------------------------------
    // else there aren't any unconfirmed parties, and it already displayed an error message related to that.

    return -1;
}


OT_COMMAND_OT int32_t main_confirm() // smart contract and payment plan
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;
    // **************************************************************
    int32_t nIndex = -1;

    if (VerifyExists("Args", false))
    {
        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "index 1"
        //
        string strIndex = OT_CLI_GetValueByKey(Args, "index"); // any integer value

        if (VerifyStringVal(strIndex))
        {
            int32_t nTempIndex = to_int(strIndex);

            if (VerifyIntVal(nTempIndex) && (nTempIndex >= 0))
            {
                nIndex = nTempIndex;
            }
        }
    }
    OTAPI_Wrap::Output(0, "\n\n"); // stderr
    // ***************************************************************
    string strInstrument = "";

    if (-1 == nIndex) // No index provided, so they need to paste the smart contract...
    {
        if (VerifyExists("Server", false) && VerifyExists("MyNym", false))
        {
            main_show_payments_inbox();

            OTAPI_Wrap::Output(0, "If this is in reference to a smart contract or payment plan in your payments\ninbox, please enter the index to confirm it (or just hit enter, to paste a contract): ");
            string strIndex = OT_CLI_ReadLine();

            if (VerifyStringVal(strIndex))
            {
                int32_t nTempIndex = to_int(strIndex);

                if (VerifyIntVal(nTempIndex) && (nTempIndex >= 0))
                {
                    nIndex = nTempIndex;

                    strInstrument = madeEasy.get_payment_instrument(Server, MyNym, nIndex);

                    if (!VerifyStringVal(strInstrument))
                    {
                        OTAPI_Wrap::Output(0, "\n Unable to get instrument from payments inbox, based on index: " + to_string(nIndex) + ".\n");
                        return -1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                OTAPI_Wrap::Output(0, "\nPlease paste the smart contract or payment plan,\nfollowed by a ~ by itself on a blank line:\n\n");

                strInstrument = OT_CLI_ReadUntilEOF();

                if (!VerifyStringVal(strInstrument))
                {
                    return -1;
                }
            }
        }
        else
        {
            OTAPI_Wrap::Output(0, "\nPlease paste the smart contract or payment plan,\nfollowed by a ~ by itself on a blank line:\n\n");

            strInstrument = OT_CLI_ReadUntilEOF();

            if (!VerifyStringVal(strInstrument))
            {
                return -1;
            }
        }
    }

    else // nIndex is NOT -1 (an index was specified.)
    {
        if (VerifyExists("Server") && VerifyExists("MyNym"))
        {
            strInstrument = madeEasy.get_payment_instrument(Server, MyNym, nIndex);

            if (!VerifyStringVal(strInstrument))
            {
                OTAPI_Wrap::Output(0, "\n Unable to get instrument from payments inbox, based on index: " + to_string(nIndex) + ".\n");
                return -1;
            }
        }
        else
        {
            OTAPI_Wrap::Output(0, "Since you specified an index, make sure to also specify --server and --mynym,\nso you use that index on the right payments inbox.\n");
            return -1; // VerifyExists logs already.
        }
    }

    string strInstrumentType = OTAPI_Wrap::Instrmnt_GetType(strInstrument);

    if (!VerifyStringVal(strInstrumentType))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine instrument type. Expected SMART CONTRACT or PAYMENT PLAN.\n");
        return -1;
    }

    // Is the instrument yet valid, or is it expired?
    // Handle both those cases here...
    time_t tFrom = OTAPI_Wrap::Instrmnt_GetValidFrom(strInstrument);
    time_t tTo = OTAPI_Wrap::Instrmnt_GetValidTo(strInstrument);
    time_t tTime = OTAPI_Wrap::GetTime();

    if (tTime < tFrom)
    {
        if (-1 == nIndex) { OTAPI_Wrap::Output(0, "The instrument is not yet within its valid date range. (Skipping.)\n"); }
        else { OTAPI_Wrap::Output(0, "The instrument at index " + to_string(nIndex) + " is not yet within its valid date range. (Skipping.)\n"); }
        return 0;
    }
    if ((tTo > 0) && (tTime > tTo))
    {
        if (-1 == nIndex)
        {
            OTAPI_Wrap::Output(0, "The instrument is expired. (Harvesting the transaction numbers.)\n");
            if (OTAPI_Wrap::Msg_HarvestTransactionNumbers(strInstrument, MyNym, false, false, false, false, false))
            {
                return 0;
            }
        }
        else // there's an index.
        {
            OTAPI_Wrap::Output(0, "The instrument at index " + to_string(nIndex) + " is expired. (Moving it to the record box.)\n");

            // Since this instrument is expired, remove it from the payments inbox, and move to record box.


            // Note: this harvests.
            if (OTAPI_Wrap::RecordPayment(Server, MyNym, true, // bIsInbox=true
                nIndex, true)) // bSaveCopy=true. (Will be saved in expired box, since it's expired.)
            {
                return 0;
            }
        } // there's an index.
        return -1;
    }

    if ("SMARTCONTRACT" == strInstrumentType)
    {
        // Success! (It's a smart contract for sure.)
        //
        // BY this point, we know that strInstrument contains a string.
        // We also know that it came from the payments inbox at nIndex, or
        // that it was pasted in and nIndex is -1. We also know that if nIndex
        // is NOT -1, that means Server and MyNym are set, because that's the
        // box we must have gotten the smart contract out of (because someone
        // else sent it to us for confirmation...)
        //
        return details_confirm_smart_contract(strInstrument, nIndex);

    }
    else if ("PAYMENT PLAN" == strInstrumentType)
    {
        // Success! (It's a payment plan for sure.)
        //
        return details_confirm_plan(strInstrument, nIndex);
    }
    else  // CHEQUE VOUCHER INVOICE PURSE
    {
        OTAPI_Wrap::Output(0, "\nFailure: Instrument is not a smart contract or payment plan, but rather a: " + strInstrumentType + "\n");
        return -1;
    }

    return -1;
}


OT_COMMAND_OT int32_t main_encode()
{
    OTAPI_Wrap::Output(0, "Please enter multiple lines of input to be encoded, followed by an EOF or a ~ by itself on a blank line:\n\n");

    // The reason we accept the tilde ~ on a blank line by itself, is because
    // the EOF, while it works, causes us not to be able to read any more input
    // from stdin. Stdin is considered "closed" for the duration of the run.
    // So the tilde allows us to read multiple times without closing stdin.

    string strInput = OT_CLI_ReadUntilEOF();

    OTAPI_Wrap::Output(0, "\n\n--------------------------------------\n You entered:\n" + strInput + "\n\n");

    string strOutput = OTAPI_Wrap::Encode(strInput, true);  // bLineBreaks=true

    // stderr
    OTAPI_Wrap::Output(0, "-------------------------------------- \n Encoded:\n\n");

    // stdout
    if (VerifyStringVal(strOutput))
    {
        print(strOutput);
        // stderr
        OTAPI_Wrap::Output(0, "\n\n");
        return 1;
    }

    // stderr
    OTAPI_Wrap::Output(0, "\n\n");

    return -1;
}


OT_COMMAND_OT int32_t main_decode()
{
    OTAPI_Wrap::Output(0, "Please enter multiple lines of OT-armored text to be decoded, followed by an EOF or a ~ by itself on a blank line:\n\n");

    // The reason we accept the tilde ~ on a blank line by itself, is because
    // the EOF, while it works, causes us not to be able to read any more input
    // from stdin. Stdin is considered "closed" for the duration of the run.
    // So the tilde allows us to read multiple times without closing stdin.

    string strInput = OT_CLI_ReadUntilEOF();

    OTAPI_Wrap::Output(0, "\n\n--------------------------------------\n You entered:\n" + strInput + "\n\n");

    string strOutput = OTAPI_Wrap::Decode(strInput, true);  // bLineBreaks=true

    // stderr
    OTAPI_Wrap::Output(0, "--------------------------------------\n Decoded:\n\n");

    // stdout
    if (VerifyStringVal(strOutput))
    {
        print(strOutput);
        // stderr
        OTAPI_Wrap::Output(0, "\n\n");
        return 1;
    }

    // stderr
    OTAPI_Wrap::Output(0, "\n\n");

    return -1;
}


OT_COMMAND_OT int32_t main_encrypt()
{
    if (VerifyExists("HisNym"))
    {

        OTAPI_Wrap::Output(0, "Please enter multiple lines of input to be encrypted,\nfollowed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strInput = OT_CLI_ReadUntilEOF();

        OTAPI_Wrap::Output(0, "\n\n--------------------------------------\n You entered:\n" + strInput + "\n\n");

        string strOutput = OTAPI_Wrap::Encrypt(HisNym, strInput);  // bLineBreaks=true

        // stdout
        if (VerifyStringVal(strOutput))
        {
            // stderr
            OTAPI_Wrap::Output(0, "-------------------------------------- \n Encrypted:\n\n");

            print(strOutput);
            // stderr
            OTAPI_Wrap::Output(0, "\n\n");
            return 1;
        }
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t main_decrypt()
{
    if (VerifyExists("MyNym"))
    {

        OTAPI_Wrap::Output(0, "Please enter multiple lines of input to be decrypted, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strInput = OT_CLI_ReadUntilEOF();

        OTAPI_Wrap::Output(0, "\n\n--------------------------------------\n You entered:\n" + strInput + "\n\n");

        string strOutput = OTAPI_Wrap::Decrypt(MyNym, strInput);  // bLineBreaks=true

        // stdout
        if (VerifyStringVal(strOutput))
        {
            // stderr
            OTAPI_Wrap::Output(0, "-------------------------------------- \n Decrypted:\n\n");

            print(strOutput);
            // stderr
            OTAPI_Wrap::Output(0, "\n\n");
            return 1;
        }
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t main_password_encrypt()
{
    OTAPI_Wrap::Output(0, "Please enter a symmetric key, followed by a ~ by itself on a blank line:\n\n");

    // The reason we accept the tilde ~ on a blank line by itself, is because
    // the EOF, while it works, causes us not to be able to read any more input
    // from stdin. Stdin is considered "closed" for the duration of the run.
    // So the tilde allows us to read multiple times without closing stdin.

    string strKey = OT_CLI_ReadUntilEOF();

    OTAPI_Wrap::Output(0, "Please enter the plaintext, followed by a ~ by itself on a blank line:\n\n");

    string strPlaintext = OT_CLI_ReadUntilEOF();

    if (VerifyStringVal(strKey) && VerifyStringVal(strPlaintext))
    {
        string strCiphertext = OTAPI_Wrap::SymmetricEncrypt(strKey, strPlaintext);

        // stdout
        if (VerifyStringVal(strCiphertext))
        {
            // stderr
            OTAPI_Wrap::Output(0, "-------------------------------------- \n strCiphertext:\n\n");

            print(strCiphertext);
            // stderr
            OTAPI_Wrap::Output(0, "\n\n");
            return 1;
        }
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t main_password_decrypt()
{
    OTAPI_Wrap::Output(0, "Please enter a symmetric key, followed by a ~ by itself on a blank line:\n\n");

    // The reason we accept the tilde ~ on a blank line by itself, is because
    // the EOF, while it works, causes us not to be able to read any more input
    // from stdin. Stdin is considered "closed" for the duration of the run.
    // So the tilde allows us to read multiple times without closing stdin.

    string strKey = OT_CLI_ReadUntilEOF();

    OTAPI_Wrap::Output(0, "Please enter the symmetrically-encrypted ciphertext, followed by a ~ by itself on a blank line:\n\n");

    string strCiphertext = OT_CLI_ReadUntilEOF();

    if (VerifyStringVal(strKey) && VerifyStringVal(strCiphertext))
    {
        string strPlaintext = OTAPI_Wrap::SymmetricDecrypt(strKey, strCiphertext);

        // stdout
        if (VerifyStringVal(strPlaintext))
        {
            // stderr
            OTAPI_Wrap::Output(0, "-------------------------------------- \n Plaintext:\n\n");

            print(strPlaintext);
            // stderr
            OTAPI_Wrap::Output(0, "\n\n");
            return 1;
        }
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT bool details_import_nym(const string & strNymImportFile, string & strOutNymID)
{
    strOutNymID = OTAPI_Wrap::Wallet_ImportNym(strNymImportFile);

    bool bVerified = VerifyStringVal(strOutNymID);

    return bVerified;
}


OT_COMMAND_OT int32_t main_import_nym()
{
    string strUsage = "\n\n USAGE: importnym\n";

    OTAPI_Wrap::Output(0, strUsage);


    OTAPI_Wrap::Output(0, "Paste your exported Nym here (for import), followed by a ~ by itself on a blank line: \n");

    string strNymFile = OT_CLI_ReadUntilEOF();

    if (!VerifyStringVal(strNymFile))
    {
        return -1;
    }

    string strOutNymID;
    bool bDone = details_import_nym(strNymFile, strOutNymID);

    if (!bDone)
    {
        OTAPI_Wrap::Output(0, "\n\n FAILED trying to import Nym.\n");
        return -1;
    }
    else
    {
        OTAPI_Wrap::Output(0, "\n\n SUCCESS importing Nym: " + strOutNymID + "\n\n");
        return 1;
    }

    return -1;
}


OT_COMMAND_OT string details_export_nym(const string & strNymID)
{
    string strExportedNym = OTAPI_Wrap::Wallet_ExportNym(strNymID);

    return strExportedNym;
}

OT_COMMAND_OT int32_t main_export_nym()
{
    string strUsage = "\n\n USAGE: exportnym --mynym NYM_ID\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym"))
    {
        string strExportedNym = details_export_nym(MyNym);

        if (!VerifyStringVal(strExportedNym))
        {
            OTAPI_Wrap::Output(0, "\n\n FAILED trying to export Nym: " + MyNym + "\n");
            return -1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\n SUCCESS exporting Nym: " + MyNym + "\n\n"); //stderr
            print(strExportedNym); // stdout
            OTAPI_Wrap::Output(0, "\n"); //stderr
            return 1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t main_change_passphrase()
{
    if (OTAPI_Wrap::Wallet_ChangePassphrase())
    {
        return 1;
    }

    return -1;
}


//
// SEND TRANSFER (From one asset account to another.)
//


OT_COMMAND_OT int32_t details_send_transfer(const string & strMyAcctID, const string & strHisAcctID, const string & strAmount, const string & strNote)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // Look up the NymID based on strMyAcctID
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(strMyAcctID);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find NymID (for sender) based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
        return -1;
    }
    if (VerifyExists("MyNym", false) && !(MyNym == strMyNymID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: MyNym was provided (" + MyNym + "), but didn't match the Nym who owns MyAcct. To override, use: --mynym " + strMyNymID + "\n\n");
        return -1;
    }

    // Look up the ServerID based on strMyAcctID
    //
    string strMyServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strMyAcctID);

    if (!VerifyStringVal(strMyServerID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find ServerID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Server based on the account.\n\n");
        return -1;
    }
    if (VerifyExists("Server", false) && !(Server == strMyServerID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Server was provided (" + Server + "), but didn't match the Server where MyAcct is based. To override, use: --server " + strMyServerID + "\n\n");
        return -1;
    }

    // NEXT, we get the Server based on HIS account.
    //
    // That way, we can make sure both accounts are on the same server, before
    // we go riding off into the sunset sending transfer requests to the server.
    //
    string strHisServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strHisAcctID);

    if (!VerifyStringVal(strHisServerID))
    {
        OTAPI_Wrap::Output(0, "HisAcct is not in the wallet, so I'm assuming it's on the same server as MyAcct. (Proceeding.)\n");

        strHisServerID = strMyServerID;
    }

    if (!(strMyServerID == strHisServerID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: HisAcct is not on the same server as MyAcct (he's on " + strHisServerID + " but MyAcct is on " + strMyServerID + "). You must choose either a different sender account (using --myacct ACCT_ID) or a different recipient account (using --hisacct ACCT_ID)\n\n");
        return -1;
    }
    // ***************************************************************

    string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strMyAcctID);

    // HERE, WE SEND THE TRANSFER REQUEST TO THE SERVER
    //
    int64_t lAmount = OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount);
    //  int64_t lAmount = to_long(strAmount)
    string strResponse = madeEasy.send_transfer(strMyServerID, strMyNymID, strMyAcctID, strHisAcctID, lAmount, strNote);
    string strAttempt = "send_transfer";
    /*
    int32_t notarizeTransfer(   const std::string SERVER_ID,
    const std::string USER_ID,
    const std::string ACCT_FROM,
    const std::string ACCT_TO,
    const std::string AMOUNT,
    const std::string NOTE);
    */
    // ***************************************************************

    // HERE, WE INTERPRET THE SERVER REPLY, WHETHER SUCCESS, FAIL, OR ERROR...

    int32_t nInterpretReply = InterpretTransactionMsgReply(strMyServerID, strMyNymID, strMyAcctID, strAttempt, strResponse);

    if (1 == nInterpretReply)
    {
        // Download all the intermediary files (account balance, inbox, outbox, etc)
        // since they have probably changed from this operation.
        //
        bool bRetrieved = madeEasy.retrieve_account(strMyServerID, strMyNymID, strMyAcctID, true); //bForceDownload defaults to false.

        OTAPI_Wrap::Output(0, "Server response (" + strAttempt + "): SUCCESS sending transfer!\n");
        OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");
    }

    // ***************************************************************
    //
    // Return status to caller.
    //
    return nInterpretReply;
}


// HERE, WE GET ALL THE ARGUMENTS TOGETHER,
// and then call the above function.
//
OT_COMMAND_OT int32_t main_transfer()
{
    string strUsage1 = concat("\n\n  USAGE: transfer --myacct YOUR_ASSET_ACCT --hisacct RECIPIENT_ASSET_ACCT\n\n",
        "Also NECESSARY: --args \"amount PUT_AMOUNT_HERE\"\n");
    string strUsage = concat(strUsage1,
        "And OPTIONALLY: --args \"memo \\\"Just a memo for the transfer.\\\"\"\n\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("MyAcct") && VerifyExists("HisAcct"))
    {
        // strAmount and strNote...
        //
        string strAmount = "0"; // must be >= 1
        string strNote = ""; // can be blank

        string strDefaultAmount = "10"; // must be >= 1
        string strDefaultNote = "(blank memo field)"; // can be blank

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "amount 1"
            // EXAMPLE:  --args "amount 15 note \"Just a memo for the transfer.\""
            //
            string strNewAmount = OT_CLI_GetValueByKey(Args, "amount"); // any integer value
            string strNewNote = OT_CLI_GetValueByKey(Args, "memo");     // optional memo field


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewAmount))
            {
                strAmount = strNewAmount;
            }
            if (VerifyStringVal(strNewNote))
            {
                strNote = strNewNote;
            }
        }


        string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);

        // If the transfer parameters aren't provided, then we
        // ask the user to supply them at the command line.
        //
        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
            //      if (!VerifyStringVal(strAmount) || (to_int(strAmount) < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the amount[" + strDefaultAmount + "]: ");
            strAmount = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strNote))
        {
            OTAPI_Wrap::Output(0, "Optionally, enter a memo on a single line[" + strDefaultNote + "]: ");
            strNote = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
            //      if (!VerifyStringVal(strAmount) || (to_int(strAmount) < 1))
        {
            strAmount = strDefaultAmount;
        }
        if (!VerifyStringVal(strNote))
        {
            strNote = strDefaultNote;
        }


        return details_send_transfer(MyAcct, HisAcct, strAmount, strNote);
    }

    return -1;
}


// SET NAME!!


OT_COMMAND_OT int32_t main_edit_nym()
{
    string strUsage = concat("\n\n USAGE: editnym --mynym YOUR_NYM_ID\n",
        "Also optionally:         --args \"label \\\"PUT LABEL HERE\\\"\"\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("MyNym"))
    {
        string strLabel = "";

        string strDefaultLabel = "(blank label)"; // can be blank

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "label \"FT's test Nym\""
            //
            string strNewLabel = OT_CLI_GetValueByKey(Args, "label");  // optional label field

            // Set the value based on the custom argument.
            //
            if (VerifyStringVal(strNewLabel))
            {
                strLabel = strNewLabel;
            }
        }

        // If the label isn't provided, then we ask the
        // user to supply it at the command line.
        //
        if (!VerifyStringVal(strLabel))
        {
            OTAPI_Wrap::Output(0, "Enter MyNym's new label [" + strDefaultLabel + "]: ");
            strLabel = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strLabel))
        {
            strLabel = strDefaultLabel;
        }


        bool bSet = OTAPI_Wrap::SetNym_Name(MyNym, MyNym, strLabel);

        if (!bSet)
        {
            OTAPI_Wrap::Output(0, "\n\n FAILED trying to set MyNym's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "MyNym ID: " + MyNym + "\n\n");
            return -1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\n SUCCESS setting MyNym's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "MyNym ID: " + MyNym + "\n\n");
            return 1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t main_edit_account()
{
    string strUsage = concat("\n\n USAGE: editacct --myacct YOUR_ACCT_ID\n",
        "Also optionally:          --args \"label \\\"PUT LABEL HERE\\\"\"\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("MyAcct"))
    {

        // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
        //
        string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

        if (!VerifyStringVal(strMyNymID))
        {
            OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
            return -1;
        }
        if (VerifyExists("MyNym") && !(MyNym == strMyNymID))
        {
            OTAPI_Wrap::Output(0, "\n\nFailure: MyNym was provided, but didn't match the Nym who owns MyAcct. To override, use: --mynym " + strMyNymID + "\n\n");
            return -1;
        }
        // ***************************************************************
        //
        string strLabel = "";

        string strDefaultLabel = "(blank label)"; // can be blank

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "label \"FT's issuer account\""
            //
            string strNewLabel = OT_CLI_GetValueByKey(Args, "label");  // optional label field

            // Set the value based on the custom argument.
            //
            if (VerifyStringVal(strNewLabel))
            {
                strLabel = strNewLabel;
            }
        }

        // If the label isn't provided, then we ask the
        // user to supply it at the command line.
        //
        if (!VerifyStringVal(strLabel))
        {
            OTAPI_Wrap::Output(0, "Enter MyAcct's new label [" + strDefaultLabel + "]: ");
            strLabel = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strLabel))
        {
            strLabel = strDefaultLabel;
        }


        bool bSet = OTAPI_Wrap::SetAccountWallet_Name(MyAcct, strMyNymID, strLabel);

        if (!bSet)
        {
            OTAPI_Wrap::Output(0, "\n\n FAILED trying to set MyAcct's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "MyAcct ID: " + MyAcct + "\n");
            OTAPI_Wrap::Output(0, " MyNym ID: " + strMyNymID + "\n\n");
            return -1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\n SUCCESS setting MyAcct's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "MyAcct ID: " + MyAcct + "\n");
            OTAPI_Wrap::Output(0, " MyNym ID: " + strMyNymID + "\n\n");
            return 1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t main_edit_asset()
{
    string strUsage = concat("\n\n USAGE: editasset --mypurse ASSET_TYPE_ID\n",
        "Also optionally:           --args \"label \\\"PUT LABEL HERE\\\"\"\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("MyPurse"))
    {
        string strLabel = "";

        string strDefaultLabel = "(blank label)"; // can be blank

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "label \"Silver Grams\""
            //
            string strNewLabel = OT_CLI_GetValueByKey(Args, "label");  // optional label field

            // Set the value based on the custom argument.
            //
            if (VerifyStringVal(strNewLabel))
            {
                strLabel = strNewLabel;
            }
        }

        // If the label isn't provided, then we ask the
        // user to supply it at the command line.
        //
        if (!VerifyStringVal(strLabel))
        {
            OTAPI_Wrap::Output(0, "Enter MyPurse's new label [" + strDefaultLabel + "]: ");
            strLabel = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strLabel))
        {
            strLabel = strDefaultLabel;
        }


        bool bSet = OTAPI_Wrap::SetAssetType_Name(MyPurse, strLabel);

        if (!bSet)
        {
            OTAPI_Wrap::Output(0, "\n\n FAILED trying to set MyPurse's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "MyPurse (AssetTypeID): " + MyPurse + "\n\n");
            return -1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\n SUCCESS setting MyPurse's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "MyPurse (AssetTypeID): " + MyPurse + "\n\n");
            return 1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t main_edit_server()
{
    string strUsage = concat("\n\n USAGE: editserver --server SERVER_ID\n",
        "Also optionally:            --args \"label \\\"PUT LABEL HERE\\\"\"\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server"))
    {
        string strLabel = "";

        string strDefaultLabel = "(blank label)"; // can be blank

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "label \"localhost server\""
            //
            string strNewLabel = OT_CLI_GetValueByKey(Args, "label");  // optional label field

            // Set the value based on the custom argument.
            //
            if (VerifyStringVal(strNewLabel))
            {
                strLabel = strNewLabel;
            }
        }

        // If the label isn't provided, then we ask the
        // user to supply it at the command line.
        //
        if (!VerifyStringVal(strLabel))
        {
            OTAPI_Wrap::Output(0, "Enter Server's new label [" + strDefaultLabel + "]: ");
            strLabel = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strLabel))
        {
            strLabel = strDefaultLabel;
        }


        bool bSet = OTAPI_Wrap::SetServer_Name(Server, strLabel);

        if (!bSet)
        {
            OTAPI_Wrap::Output(0, "\n\n FAILED trying to set Server's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "Server ID: " + Server + "\n\n");
            return -1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\n SUCCESS setting Server's label to: " + strLabel + "\n");
            OTAPI_Wrap::Output(0, "Server ID: " + Server + "\n\n");
            return 1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t main_sendmsg()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // Just to show how easy it is, let's try a "send_user_message" message.
    //
    string strUsage = "\n\n FYI, USAGE: sendmsg --mynym <YOUR_NYM_ID> --hisnym <RECIPIENT_NYM_ID>\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("HisNym"))
    {
        OTAPI_Wrap::Output(0, "Please enter your message on multiple lines, optionally beginning with a \"Subject: \" line.\n");
        OTAPI_Wrap::Output(0, "Use Ctrl-C to cancel, otherwise finish your message with an EOF or a ~ by itself on a blank line:\n\n");

        string strMessage = OT_CLI_ReadUntilEOF();

        // Send the request.
        //
        string strResponse = madeEasy.send_user_msg(Server, MyNym, HisNym, strMessage);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!
        //
        // Instead, simply check for success or failure:
        //
        if (1 != VerifyMessageSuccess(strResponse))
        {
            OTAPI_Wrap::Output(0, "send_user_msg: Failed.\n");
        }
        else
        {
            OTAPI_Wrap::Output(0, "Success in send_user_msg! Server response:\n\n");
            print(strResponse);
            OTAPI_Wrap::Output(0, "\nSuccess in send_user_msg.\n\n");
            return 1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t details_write_cheque(string & strCheque, const bool bIsInvoice) // strCheque is output.
{
    Utility MsgUtil;

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    if (VerifyExists("MyAcct"))
    {

        // Look up the NymID based on MyAcct
        //
        string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

        if (!VerifyStringVal(strMyNymID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find NymID (for sender) based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
            return -1;
        }
        if (VerifyExists("MyNym", false) && !(MyNym == strMyNymID))
        {
            OTAPI_Wrap::Output(0, "\n\nFailure: MyNym was provided (" + MyNym + "), but didn't match the Nym who owns MyAcct. To override, use: --mynym " + strMyNymID + "\n\n");
            return -1;
        }

        // Look up the ServerID based on MyAcct
        //
        string strMyServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);

        if (!VerifyStringVal(strMyServerID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find ServerID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Server based on the account.\n\n");
            return -1;
        }
        if (VerifyExists("Server", false) && !(Server == strMyServerID))
        {
            OTAPI_Wrap::Output(0, "\n\nFailure: Server was provided (" + Server + "), but didn't match the Server where MyAcct is based. To override, use: --server " + strMyServerID + "\n\n");
            return -1;
        }
        // ***************************************************************
        //
        // When we pass in HisNym at the command line, using this option:  --hisnym HIS_NYM_ID
        // then OT internally TRIES to look it up on the wallet (and someday on the address
        // book as well) in abbreviated or name form, in order to substitute it with the ACTUAL
        // full NymID, before passing it into the script where we are now. If nothing is found,
        // then it just passes through the ID so we have a chance to download the pubkey and
        // verify that it actually exists.
        //
        // Therefore, if the full "HisNym" ID hasn't ALREADY been found by now, that means we
        // already couldn't find it via abbreviation or name, and therefore we will HAVE to download
        // it from the server since we don't have it already. (And therefore we will NEED to know the
        // FULL ID, since we cannot download a pubkey from a server based on a partial ID.)
        //
        // The point is that when we get here, there's no need to worry about searching for a partial
        // or abbreviated version, and no need to ask load_or_retrieve_pubkey to somehow translate HisNym
        // to a full ID. That would have already happened by now, if one were available. So at this point
        // we basically have to assume the user passed the full and correct ID, and if it's not in the
        // wallet already, then load_or_retrieve_pubkey can go ahead and try to download it as if it is
        // the full and correct ID. If it fails, it fails.
        //
        string strRecipientPubkey = "";
        string strHisNymID = "";

        if (VerifyExists("HisNym", false))
        {
            strRecipientPubkey = madeEasy.load_or_retrieve_encrypt_key(strMyServerID, strMyNymID, HisNym);
            // Note: even thogh send_user_payment already calls load_or_retrieve_pubkey, we do it
            // here anyway, BEFORE trying to write the cheque. (No point writing a cheque to HisNym until
            // we're sure it's real...)
            //
            if (!VerifyStringVal(strRecipientPubkey))
            {
                OTAPI_Wrap::Output(0, "\n\nFailure: Unable to load or download pubkey for HisNym based on given value (" + HisNym + "). To override, use: --hisnym HIS_NYM_ID\n\n");
                return -1;
            }

            strHisNymID = HisNym;
        }

        // Make sure we have at least one transaction number (to write the cheque...)
        //
        if (!madeEasy.insure_enough_nums(10, strMyServerID, strMyNymID))
        {
            return -1;
        }

        // - At this point we have MyAcct writing a cheque to HisNym.
        // - We have strMyServerID and strMyNymID and we know they match MyAcct.
        // (And we know they match --server and --mynym as well, otherwise the
        // user would have been be forced to override at the command line before
        // allowing him to continue.)
        // - We know that HisNym is a valid enough ID that we were able to load
        // his public key, or download it and THEN load it up. By this point it was
        // successful either way.
        // - We know that the Nym has at least 1 valid transaction number, with
        // which to write the cheque. (If he didn't, we would have downloaded it in
        // the above block.)
        // - Therefore let's collect all the other cheque-related data, and write
        // the actual cheque, and return it to the caller.

        string strDefaultAmount = "1"; // smallest possible amount.
        string strDefaultMemo = "(memo field)";
        int32_t nDefaultLength = 2592000;   // 30 days

        string strAmount = "0";
        string strMemo = ""; // empty
        int32_t nLength = 0;


        string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);

        if (VerifyExists("Args"))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "amount 100 memo \"my share for the BBQ\""
            //
            string strNewAmount = OT_CLI_GetValueByKey(Args, "amount");
            string strNewMemo = OT_CLI_GetValueByKey(Args, "memo");
            string strNewLength = OT_CLI_GetValueByKey(Args, "validfor");

            if (VerifyStringVal(strNewMemo))
            {
                strMemo = strNewMemo;
            }

            if (VerifyStringVal(strNewAmount) && (OTAPI_Wrap::StringToAmount(strAssetTypeID, strNewAmount) > 0))
                //          if (VerifyStringVal(strNewAmount) && (to_int(strNewAmount) > 0))
            {
                strAmount = strNewAmount;
            }

            if (VerifyStringVal(strNewLength) && (to_int(strNewLength) > 0))
            {
                nLength = to_int(strNewLength);
            }
        }


        // If the transfer parameters aren't provided, then we
        // ask the user to supply them at the command line.
        //
        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the amount[" + strDefaultAmount + "]: ");
            strAmount = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strMemo))
        {
            OTAPI_Wrap::Output(0, "Optionally, enter a note on a single line[" + strDefaultMemo + "]: ");
            strMemo = OT_CLI_ReadLine();
        }
        if (!VerifyIntVal(nLength) || (nLength < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the 'valid for' time period, in seconds (default is 30 days.) [" + to_string(nDefaultLength) + "]: ");
            string strTemp = OT_CLI_ReadLine();

            if (VerifyStringVal(strTemp) && (to_int(strTemp) > 0))
            {
                nLength = to_int(strTemp);
            }
        }

        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
        {
            strAmount = strDefaultAmount;
        }

        if (!VerifyStringVal(strMemo))
        {
            strMemo = strDefaultMemo;
        }

        if (!VerifyIntVal(nLength) || (nLength < 1))
        {
            nLength = nDefaultLength;
        }


        // Todo: use Args feature here to allow an option to override nLength.
        // If it's not used, go with the default of 30 days (above.)

        string strLength = to_string(nLength);

        time_t tFrom = OTAPI_Wrap::GetTime();
        int64_t tLength = to_long(strLength);
        time_t tTo = tFrom + tLength;

        if (bIsInvoice)
        {
            int64_t lTempAmount = (int64_t(-1) * OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount));
            strAmount = OTAPI_Wrap::FormatAmount(strAssetTypeID, lTempAmount);
        }

        int64_t lAmount = OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount);

        strCheque = OTAPI_Wrap::WriteCheque(strMyServerID,
            lAmount,
            tFrom,
            tTo,
            MyAcct,
            strMyNymID,
            strMemo,
            strHisNymID);

        // Record it in the records?
        // Update: We wouldn't record that here. Instead, OTAPI_Wrap::WriteCheque should drop a notice
        // into the payments outbox, the same as it does when you "sendcheque" (after all, the same
        // resolution would be expected once it is cashed.)

        return 1;
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t main_write_cheque()
{
    string strUsage1 = "Usage:  writecheque  --myacct <MY_ACCT_ID> --hisnym <HIS_NYM_ID>\n";
    string strUsage2 = "This command WRITES but DOES NOT SEND the cheque. (Use sendcheque for that.)\n\n";
    string strUsage = concat(strUsage1 + "Optionally: --args \"memo \\\"one-line memo allowed here.\\\" amount AMOUNT\"\n",
        "Additionally: --args \"validfor IN_SECONDS\" \n" + strUsage2);

    OTAPI_Wrap::Output(0, strUsage);

    string strCheque = "";
    int32_t nReturnVal = details_write_cheque(strCheque, false); //bIsInvoice=false

    if ((1 == nReturnVal) && VerifyStringVal(strCheque))
    {
        // stderr
        OTAPI_Wrap::Output(0, "\n-------------------------------------------\n the cheque:\n\n");
        // stdout
        print(strCheque);
        // stderr
        OTAPI_Wrap::Output(0, "\n");
    }

    return nReturnVal;
}


OT_COMMAND_OT int32_t main_write_invoice()
{
    string strUsage1 = "Usage:  writeinvoice  --myacct <MY_ACCT_ID> --hisnym <HIS_NYM_ID>\n";
    string strUsage2 = "This command WRITES but DOES NOT SEND the invoice. (Use sendinvoice for that.)\n";
    string strUsage = concat(strUsage1 + "Optionally: --args \"memo \\\"one-line memo allowed here.\\\" amount AMOUNT\"\n",
        "Additionally: --args \"validfor IN_SECONDS\" \n" + strUsage2);
    OTAPI_Wrap::Output(0, strUsage);

    string strCheque = "";
    int32_t nReturnVal = details_write_cheque(strCheque, true); //bIsInvoice=true

    if ((1 == nReturnVal) && VerifyStringVal(strCheque))
    {
        // stderr
        OTAPI_Wrap::Output(0, "\n-------------------------------------------\n the invoice:\n\n");
        // stdout
        print(strCheque);
        // stderr
        OTAPI_Wrap::Output(0, "\n");
    }

    return nReturnVal;
}


OT_COMMAND_OT int32_t main_sendcash()
{

    string strUsage1 = "Usage:  sendcash  --[myacct|mypurse] <ID> --hisnym <RECIPIENT_NYM_ID>\nFor mypurse, the server and nym are also required: --server <SERVER_ID> --mynym <NYM_ID> \n";
    string strUsage2 = concat(strUsage1, "Optionally: --args \"passwd true\"  (To send a password-protected purse.)\n");
    string strUsage3 = concat(strUsage2, "Optionally: --args \"memo \\\"one-line memo allowed here.\\\" amount AMOUNT\"\n");
    string strUsage = concat(strUsage3, "This command sends cash to the recipient, from your purse if specified, and withdrawing first from your account, if necessary.\n\n");

    OTAPI_Wrap::Output(0, strUsage);

    string strServerID = "";
    string strMyAcctID = "";
    string strMyNymID = "";
    string strAssetTypeID = "";

    bool bServerExists = VerifyExists("Server", false);
    bool bMyPurseExists = VerifyExists("MyPurse", false);
    bool bMyAcctExists = VerifyExists("MyAcct", false);
    bool bMyNymExists = VerifyExists("MyNym", false);

    if (!bMyPurseExists && !bMyAcctExists)
    {
        OTAPI_Wrap::Output(0, "\n You must provide EITHER --myacct <ACCT_ID> OR --mypurse <ASSET_TYPE_ID>\nFor mypurse, the server and nym are also required: --server <SERVER_ID> --mynym <NYM_ID> \n");
        return -1;
    }

    if (bMyPurseExists)
    {
        strAssetTypeID = MyPurse;

        if (bServerExists && bMyNymExists)
        {
            strServerID = Server;
            strMyNymID = MyNym;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n MyPurse was specified, but you must also specify a server and nym:  --server <SERVER_ID> --mynym <NYM_ID>\nMaybe we can find them using MyAcct...\n");
        }
    }
    // NOTE: If MyNym and Server are not provided here, but MyAcct IS, the nym and server can still be derived from MyAcct.
    // The purse will still be used, but only if it has the same asset type ID as MyAcct does. (Meaning there was no point,
    // then, in specifying the purse at all, since all the info was derived from the account in that case.)

    if (bMyAcctExists)
    {
        string strAcctServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);
        string strAcctAssetID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);
        string strAcctNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

        if (!VerifyStringVal(strAcctServerID))
        {
            OTAPI_Wrap::Output(0, "\n Failed trying to retrieve ServerID based on MyAcct: " + MyAcct + "\n");
            return -1;
        }

        if (!VerifyStringVal(strAcctAssetID))
        {
            OTAPI_Wrap::Output(0, "\n Failed trying to retrieve AssetTypeID based on MyAcct: " + MyAcct + "\n");
            return -1;
        }

        if (!VerifyStringVal(strAcctNymID))
        {
            OTAPI_Wrap::Output(0, "\n Failed trying to retrieve NymID based on MyAcct: " + MyAcct + "\n");
            return -1;
        }

        if (VerifyStringVal(strServerID) && (strAcctServerID != strServerID))
        {
            OTAPI_Wrap::Output(0, "\n Server ID provided on the command line doesn't match the Server ID for MyAcct. Expected: " + strAcctServerID + "\n Try adding: --server " + strAcctServerID + "\n");
            return -1;
        }

        if (VerifyStringVal(strAssetTypeID) && (strAcctAssetID != strAssetTypeID))
        {
            OTAPI_Wrap::Output(0, "\n Asset Type ID provided on the command line doesn't match the Asset Type ID of MyAcct. Expected: " + strAcctAssetID + "\n Try adding: --mypurse " + strAcctAssetID + "\n");
            return -1;
        }

        if (VerifyStringVal(strMyNymID) && (strAcctNymID != strMyNymID))
        {
            OTAPI_Wrap::Output(0, "\n Nym ID provided on the command line doesn't match the Nym ID for MyAcct. Expected: " + strAcctNymID + "\n Try adding: --mynym " + strAcctNymID + "\n");
            return -1;
        }

        strServerID = strAcctServerID;
        strAssetTypeID = strAcctAssetID;
        strMyNymID = strAcctNymID;
        strMyAcctID = MyAcct;

    }

    // Since MyPurse might have been specified with NO server or Nym, and with MyAcct NOT specified,
    // we could potentially end up down here without a server or Nym still. This is only possible because
    // we allow the purse to fall through, in case those values are picked up from the account instead.
    // But by this point, we have to MAKE SURE we have a server and Nym. So let's do that now:
    //

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "\n Failed: Missing Server ID. Try adding: --server <SERVER_ID>\n");
        return -1;
    }

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "\n Failed: Missing MyNym ID. Try adding: --mynym <NYM_ID>\n");
        return -1;
    }

    // Below this point, we KNOW there's EITHER a purse OR account (or both.)
    // We know if there is only a purse specified, that it properly also has
    // a serverID and nymID. (MyPurse itself being the asset type ID.)
    //
    // We know that if a purse AND account are both specified, that they have
    // matching asset types, AND matching server and nym IDs. You might think
    // there'd be no point in doing that, since you could just not specify the
    // purse at all, and only specify the account. And you'd be right! Either way,
    // we'll try to pay it first out of the cash purse, and only withdraw from
    // the account if we're unable to pay it solely through the purse first.
    //
    // We know that strServerID is correct, strAssetTypeID is correct, and strMyNymID
    // is correct, whether we're using an account or a purse. And we know that if
    // we're using an account, we know that strMyAcctID is correct as well.
    //
    // Below this point we can just try to pay it from the purse, and if unable to,
    // try to get the remaining funds from the account, IF that's available.
    //
    int32_t nReturnVal = -1;

    if (VerifyExists("HisNym"))
    {

        // strAmount
        //
        string strAmount = "0"; // must be >= 1
        string strMemo = ""; // can be blank

        string strDefaultAmount = "1"; // must be >= 1
        string strDefaultMemo = "(blank memo field)"; // can be blank

        string strIndices = ""; // If indices are not specified, we derive them from the amount. Otherwise we go with the selected indices.
        bool bPasswordProtected = false;

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false)) // displayErrorMsg=false
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "amount 1"
            //
            // EXAMPLE:  --args "indices \"all\" "
            //
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.

            string strPasswordProtected = OT_CLI_GetValueByKey(Args, "passwd");

            string strNewAmount = OT_CLI_GetValueByKey(Args, "amount"); // any integer value
            string strNewMemo = OT_CLI_GetValueByKey(Args, "memo"); // optional memo field

            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewAmount))
            {
                strAmount = strNewAmount;
            }
            if (VerifyStringVal(strNewMemo))
            {
                strMemo = strNewMemo;
            }
            if (VerifyStringVal(strPasswordProtected) && ("true" == strPasswordProtected))
            {
                bPasswordProtected = true;
            }
        }

        // If the withdrawal parameters aren't provided, then we
        // ask the user to supply them at the command line.
        //
        if ((!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1)) && !VerifyStringVal(strIndices)) // If no indices are selected, then we NEED to know the amount...
        {
            OTAPI_Wrap::Output(0, "Enter the amount[" + strDefaultAmount + "]: ");
            strAmount = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
        {
            strAmount = strDefaultAmount;
        }

        if (!VerifyStringVal(strMemo))
        {
            OTAPI_Wrap::Output(0, "Optionally, enter a memo on a single line[" + strDefaultMemo + "]: ");
            strMemo = OT_CLI_ReadLine();
        }

        string strResponse = "";

        nReturnVal = details_send_cash(strResponse, strServerID, strAssetTypeID, strMyNymID, strMyAcctID, HisNym, strMemo, strAmount, strIndices, bPasswordProtected); // <=======

        if (1 != nReturnVal)
        {
            OTAPI_Wrap::Output(0, "main_sendcash: Failed in details_send_cash.\n");
        }
        else
        {
            OTAPI_Wrap::Output(0, "Success in sendcash! Server response:\n\n");
            print(strResponse);
            OTAPI_Wrap::Output(0, "(Success in sendcash)\n");
        }
    }

    return nReturnVal;
}


OT_COMMAND_OT int32_t main_sendcheque()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage1 = "Usage:  sendcheque  --myacct <MY_ACCT_ID> --hisnym <RECIPIENT_NYM_ID>\n";
    string strUsage2 = "This command WRITES AND SENDS the cheque.\n(Use 'writecheque', not 'sendcheque', if you don't want it to be immediately SENT.)\n";
    string strUsage = concat(strUsage1 + "Optionally: --args \"memo \\\"one-line memo allowed here.\\\" amount AMOUNT\"\n",
        "Additionally: --args \"validfor IN_SECONDS\" \n" + strUsage2);

    OTAPI_Wrap::Output(0, strUsage);

    string strCheque = "";
    int32_t nReturnVal = details_write_cheque(strCheque, false); //bIsInvoice=false

    if ((1 == nReturnVal) && VerifyStringVal(strCheque))
    {
        // stderr
        OTAPI_Wrap::Output(0, "\n-------------------------------------------\n the cheque:\n\n");
        // stdout
        print(strCheque);
        // stderr
        OTAPI_Wrap::Output(0, "\n");

        // TODO: Store a copy in outpayments box (OR VERIFY THAT IT'S ALREADY BEING DONE, WHICH I BELIEVE THAT IT IS.)

        string strServerID = OTAPI_Wrap::Instrmnt_GetServerID(strCheque);
        string strSenderNymID = OTAPI_Wrap::Instrmnt_GetSenderUserID(strCheque);
        string strRecipientNymID = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strCheque);

        if (!VerifyStringVal(strServerID))
        {
            OTAPI_Wrap::Output(0, "Unable to retrieve a Server ID from this cheque! Very strange. (Failure.)\n");
            return -1;
        }
        if (!VerifyStringVal(strSenderNymID))
        {
            OTAPI_Wrap::Output(0, "Unable to retrieve a Sender Nym ID from this cheque! Very strange. (Failure.)\n");
            return -1;
        }
        if (!VerifyStringVal(strRecipientNymID))
        {
            OTAPI_Wrap::Output(0, concat("Unable to retrieve a Recipient Nym ID from this cheque! Very strange. (Failure.)\n",
                "(Although it's fine to WRITE a cheque with no recipient, still need the ID to SEND one.)\n"));
            return -1;
        }


        string strResponse = madeEasy.send_user_payment(strServerID, strSenderNymID, strRecipientNymID, strCheque);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!
        //
        // Instead, simply check for success or failure:
        //
        nReturnVal = VerifyMessageSuccess(strResponse);

        if (1 != nReturnVal)
        {
            OTAPI_Wrap::Output(0, "sendcheque: Failed.\n");

            if (VerifyStringVal(strResponse))
            {
                OTAPI_Wrap::Msg_HarvestTransactionNumbers(strResponse, strSenderNymID, false, false, false, false, false);
            }
        }
        else
        {
            OTAPI_Wrap::Output(0, "Success in sendcheque! Server response:\n\n");
            print(strResponse);
            OTAPI_Wrap::Output(0, "(Success in sendcheque)\n");
            return 1;
        }
    }

    return nReturnVal;
}


OT_COMMAND_OT int32_t main_sendinvoice()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage1 = "Usage:  sendinvoice  --myacct <MY_ACCT_ID> --hisnym <RECIPIENT_NYM_ID>\n";
    string strUsage2 = "This command WRITES AND SENDS the invoice. (Use 'writeinvoice', not 'sendinvoice',\nif you don't want it to be immediately SENT.)\n";
    string strUsage = concat(strUsage1 + "Optionally: --args \"memo \\\"one-line memo allowed here.\\\" amount AMOUNT\"\n",
        "Additionally: --args \"validfor IN_SECONDS\" \n" + strUsage2);

    OTAPI_Wrap::Output(0, strUsage);

    string strCheque = "";
    int32_t nReturnVal = details_write_cheque(strCheque, true); //bIsInvoice=true

    if ((1 == nReturnVal) && VerifyStringVal(strCheque))
    {
        // stderr
        OTAPI_Wrap::Output(0, "\n-------------------------------------------\n the invoice:\n\n");
        // stdout
        print(strCheque);
        // stderr
        OTAPI_Wrap::Output(0, "\n");

        // TODO: Store a copy in outpayments box (OR VERIFY THAT IT'S ALREADY BEING DONE, WHICH I BELIEVE THAT IT IS.)

        string strServerID = OTAPI_Wrap::Instrmnt_GetServerID(strCheque);
        string strSenderNymID = OTAPI_Wrap::Instrmnt_GetSenderUserID(strCheque);
        string strRecipientNymID = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strCheque);

        if (!VerifyStringVal(strServerID))
        {
            OTAPI_Wrap::Output(0, "Unable to retrieve a Server ID from this invoice! Very strange. (Failure.)\n");
            return -1;
        }
        if (!VerifyStringVal(strSenderNymID))
        {
            OTAPI_Wrap::Output(0, "Unable to retrieve a Sender Nym ID from this invoice! Very strange. (Failure.)\n");
            return -1;
        }
        if (!VerifyStringVal(strRecipientNymID))
        {
            OTAPI_Wrap::Output(0, concat("Unable to retrieve a Recipient Nym ID (Endorsee) from this invoice! Very strange. (Failure.)\n",
                "(Although it's fine to WRITE a invoice with no endorsee, still need the ID to SEND it.)\n"));
            return -1;
        }

        string strResponse = madeEasy.send_user_payment(strServerID, strSenderNymID, strRecipientNymID, strCheque);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!
        //
        // Instead, simply check for success or failure:
        //
        nReturnVal = VerifyMessageSuccess(strResponse);

        if (1 != nReturnVal)
        {
            OTAPI_Wrap::Output(0, "sendinvoice: Failed.\n");
        }
        else
        {
            OTAPI_Wrap::Output(0, "Success in sendinvoice! Server response:\n\n");
            print(strResponse);
            OTAPI_Wrap::Output(0, "(Success in sendinvoice)\n");
            return 1;
        }
    }

    return nReturnVal;
}


OT_COMMAND_OT int32_t details_create_offer(const string & strScale, const string & strMinIncrement, const string & strQuantity, const string & strPrice, const bool bSelling, const string & strLifespan)
{
    // NOTE: The top half of this function has nothing to do with placing a new offer.
    // Instead, as a convenience for knotwork, it first checks to see if there are any
    // existing offers within certain parameters based on this new one, and removes them
    // if so. Only then, after that is done, does it actually place the new offer.
    // (Meaning: most of the code you see here at first is not actually necessary for
    // placing offers, but was done at the request of a server operator.)
    //
    string strLocation = "details_create_offer";

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);
    string strMyNymID2 = OTAPI_Wrap::GetAccountWallet_NymID(HisAcct);

    if (!VerifyStringVal(strMyNymID) || !VerifyStringVal(strMyNymID2) || (strMyNymID != strMyNymID2))
    {
        OTAPI_Wrap::Output(0, "You must supply myacct as your asset account, and hisacct as your currency account.\n");
        OTAPI_Wrap::Output(0, "Also, both accounts must be owned by the same Nym (you.)\n\n");
        return -1;
    }

    string strMyServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);
    string strMyServerID2 = OTAPI_Wrap::GetAccountWallet_ServerID(HisAcct);

    if (!VerifyStringVal(strMyServerID) || !VerifyStringVal(strMyServerID2) || (strMyServerID != strMyServerID2))
    {
        OTAPI_Wrap::Output(0, "Both accounts must be on the same server.\n");
        return -1;
    }
    // Below this point we're safe to use Server.


    // We're about to load up the Nym's market offers so we can see if there are
    // any we should cancel before placing this new offer.
    //
    // Therefore, I'm going to download the Nym's market offers before loading them
    // up, in case we don't even have the current list of them.

    details_get_nym_market_offers(strMyServerID, strMyNymID);

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

    This is done here:
    */

    OTDB::OfferListNym & offerList = *loadNymOffers(strMyServerID, strMyNymID);

    if (!VerifyStorable(&offerList, "OTDB::OfferListNym"))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Unable to load up a (nym) offerList from local storage. Probably doesn't exist.\n");
    }

    else
    {
        // LOOP THROUGH THE OFFERS and sort them into a map_of_maps, key is: scale-assetID-currencyID
        // the value for each key is a sub-map, with the key: transaction ID and value: the offer data itself.
        //
        int32_t nCount = offerList.GetOfferDataNymCount(); // size_t
        int32_t nTemp = nCount; // so it's created as size_t

        if (VerifyIntVal(nCount) && (nCount > 0))
        {
            MapOfMaps * map_of_maps = convert_offerlist_to_maps(offerList);

            if (!VerifyType(map_of_maps, "Map"))
            {
                OTAPI_Wrap::Output(0, strLocation + ": Unable to convert offer list to map of offers. Perhaps it's empty?\n");
            }
            else
            {
                // find_strange_offers is called for each offer, for this nym,
                // as it iterates through the maps. When it's done, extra_vals.the_vector
                // will contain a vector of all the transaction numbers for offers that we
                // should cancel, before placing the new offer. (Such as an offer to sell for
                // 30 clams when our new offer buys for 40...)
                //
                the_lambda_struct extra_vals;

                extra_vals.the_asset_acct = MyAcct;
                extra_vals.the_currency_acct = HisAcct;
                extra_vals.the_scale = strScale;
                extra_vals.the_price = strPrice;
                extra_vals.bSelling = bSelling;

                int32_t nIterated = iterate_nymoffers_maps(*map_of_maps, find_strange_offers, extra_vals);

                if (-1 == nIterated)
                {
                    OTAPI_Wrap::Output(0, strLocation + ": Error trying to iterate nym's offers.\n");
                    return -1;
                }

                // Okay -- if there are any offers we need to cancel, extra_vals.the_vector now contains
                // the transaction number for each one. Let's remove them from the market before
                // starting up the new offer...
                //

                if (extra_vals.the_vector.size() > 0)
                {
                    OTAPI_Wrap::Output(0, strLocation + ": FYI, about to cancel at least one market offer, before placing the new one, due to price inconsistencies between the two...\n");
                }

                for (int32_t i = 0; i < extra_vals.the_vector.size(); i++)
                {
                    OTAPI_Wrap::Output(0, strLocation + ": Canceling market offer with transaction number: " + extra_vals.the_vector[i] + "\n");

                    details_kill_offer(strMyServerID, strMyNymID, MyAcct, extra_vals.the_vector[i]);
                }
                extra_vals.the_vector.clear();
            }
        }
        else
        {
            OTAPI_Wrap::Output(0, strLocation + ": FYI, there don't seem to be any existing offers for this nym, so I won't be erasing any older ones.\n");
        }
    }
    // ********************************************************************

    // OKAY! Now that we've cleaned out any undesirable offers, let's place the
    // the offer itself!


    //
    // Send the "create offer" transaction.
    //
    string strResponse = madeEasy.create_market_offer(MyAcct, HisAcct, strScale, strMinIncrement, strQuantity, strPrice, bSelling, strLifespan, "", "0"); // lifespan of "0" results in "86400" == 1 day. Last two params are stop sign and stop price.
    string strAttempt = "create_market_offer";

    // NOTICE: No need here to deal with retries, timeouts, request number,
    // syncing transaction number, download / process nymbox, etc! It's all
    // handled at a lower level!  Instead, simply check for success or failure:

    // ***************************************************************

    int32_t nInterpretReply = InterpretTransactionMsgReply(strMyServerID, strMyNymID, MyAcct, strAttempt, strResponse);

    if (1 == nInterpretReply)
    {
        OTAPI_Wrap::Output(0, "Server response (" + strAttempt + "): SUCCESS placing market offer!\n\n");
    }

    return nInterpretReply;
}


OT_COMMAND_OT int32_t main_create_offer()
{
    string strUsage = concat("\n\n USAGE: newoffer --myacct <YOUR_ASSET_ACCT> --hisacct <YOUR_CURRENCY_ACCT>\n\n",
        " Optional: --args \"type <bid|ask> scale 1 quantity 100 price 101\"\n Optional: --args \"lifespan 86400\"   (in seconds: 86400 is 1 day--the default.)\n\nWARNING: a price of 0 is a market order, which means 'purchase/sell at ANY price'\n\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("MyAcct") && VerifyExists("HisAcct"))
    {
        string strScale = "0"; // must be 1, 10, 100, etc
        string strMinIncrement = "0"; // must be 1, 2, 3, etc
        string strQuantity = "0"; // must be >= 1
        string strPrice = "0"; // must be >= 0
        string strType = ""; // must be bid or ask
        string strLifespan = "0";

        string strDefaultScale = "1"; // must be 1, 10, 100, etc
        string strDefaultMinIncrement = "1"; // must be 1, 2, 3, etc
        string strDefaultQuantity = "100"; // must be >= 1
        string strDefaultPrice = "101"; // must be >= 1
        string strDefaultType = "bid"; // must be bid or ask
        string strDefaultLifespan = "86400"; // even if we put "0" here, OT would internally default this to 86400.

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args"))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "type bid scale 1 quantity 100 price 101"
            // EXAMPLE:  --args "type ask scale 1 quantity 100 price 101"
            //
            string strNewScale = OT_CLI_GetValueByKey(Args, "scale"); // 1, 10, 100, 1000, etc
            string strNewMinInc = OT_CLI_GetValueByKey(Args, "min_inc"); // 1, 2, 3, 4, etc. Usually 1.
            string strNewQuantity = OT_CLI_GetValueByKey(Args, "quantity"); // quantity for sale/purchase.
            string strNewPrice = OT_CLI_GetValueByKey(Args, "price"); // per scale
            string strNewType = OT_CLI_GetValueByKey(Args, "type"); // bid / ask
            string strNewLifespan = OT_CLI_GetValueByKey(Args, "lifespan"); // "0" defaults to "86400" which is 1 day.


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewScale))
            {
                strScale = strNewScale;
            }
            if (VerifyStringVal(strNewMinInc))
            {
                strMinIncrement = strNewMinInc;
            }
            if (VerifyStringVal(strNewQuantity))
            {
                strQuantity = strNewQuantity;
            }
            if (VerifyStringVal(strNewPrice))
            {
                strPrice = strNewPrice;
            }
            if (VerifyStringVal(strNewType))
            {
                strType = strNewType;
            }
            if (VerifyStringVal(strNewLifespan))
            {
                strLifespan = strNewLifespan;
            }
        }

        // If the offer parameters aren't satisfied yet, then
        // ask the user to supply them at the command line.
        //
        if (!VerifyStringVal(strScale) || (to_int(strScale) < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the market scale (1, 10, 100, etc)[" + strDefaultScale + "]: ");
            strScale = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strMinIncrement) || (to_int(strMinIncrement) < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the minimum increment[" + strDefaultMinIncrement + "]: ");
            strMinIncrement = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strQuantity) || (to_int(strQuantity) < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the quantity being purchased/sold[" + strDefaultQuantity + "]: ");
            strQuantity = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strPrice) || (to_int(strPrice) < 0))
        {
            OTAPI_Wrap::Output(0, "Enter the price per scale[" + strDefaultPrice + "]: ");
            strPrice = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strType) || ((strType != "bid") && (strType != "ask")))
        {
            OTAPI_Wrap::Output(0, "Enter the order type (bid/ask) [" + strDefaultType + "]: ");
            strType = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strLifespan) || (to_int(strLifespan) < 1))
        {
            OTAPI_Wrap::Output(0, "(1 hour == 3600, 1 day == 86400)\n Enter the lifespan of the offer, in seconds[" + strDefaultLifespan + "]: ");
            strLifespan = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strScale) || (to_int(strScale) < 1))
        {
            strScale = strDefaultScale;
        }
        if (!VerifyStringVal(strMinIncrement) || (to_int(strMinIncrement) < 1))
        {
            strMinIncrement = strDefaultMinIncrement;
        }
        if (!VerifyStringVal(strQuantity) || (to_int(strQuantity) < 1))
        {
            strQuantity = strDefaultQuantity;
        }
        if (!VerifyStringVal(strPrice) || (to_int(strPrice) < 1))
        {
            strPrice = strDefaultPrice;
        }
        if (!VerifyStringVal(strType) || ((strType != "bid") && (strType != "ask")))
        {
            strType = strDefaultType;
        }
        if (!VerifyStringVal(strLifespan) || (to_int(strLifespan) < 1))
        {
            strLifespan = strDefaultLifespan;
        }

        //
        // false == buying    bid
        // true  == selling   ask
        //
        bool bType = ((strType == "bid") ? false : true);

        return details_create_offer(strScale, strMinIncrement, strQuantity, strPrice, bType, strLifespan);
    }

    return -1;
}


OT_COMMAND_OT int32_t main_create_server_contract()
{
    if (VerifyExists("MyNym"))
    {
        OTAPI_Wrap::Output(0, "Please enter the XML contents for the contract, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strXML = OT_CLI_ReadUntilEOF();

        if (VerifyStringVal(strXML))
        {
            string strContractID = OTAPI_Wrap::CreateServerContract(MyNym, strXML);

            if (VerifyStringVal(strContractID))
            {
                // stderr
                OTAPI_Wrap::Output(0, "-------------------------------------------\nNew server ID: " + strContractID + "\n\n");

                string strContract = OTAPI_Wrap::GetServer_Contract(strContractID);

                if (VerifyStringVal(strContract))
                {
                    // stderr
                    OTAPI_Wrap::Output(0, "-------------------------------------------\nNew server contract:\n\n");

                    // stdout
                    print(strContract);

                    OTAPI_Wrap::Output(0, "\n\n");

                    return 1;
                }
            }
        }
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t main_create_asset_contract()
{
    // bool OTContract::CreateContract(OTString & strContract, OTPseudonym & theSigner)

    if (VerifyExists("MyNym"))
    {
        OTAPI_Wrap::Output(0, "Please enter the XML contents for the contract, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strXML = OT_CLI_ReadUntilEOF();

        if (VerifyStringVal(strXML))
        {
            string strContractID = OTAPI_Wrap::CreateAssetContract(MyNym, strXML);

            if (VerifyStringVal(strContractID))
            {
                // stderr
                OTAPI_Wrap::Output(0, "-------------------------------------------\nNew asset ID: " + strContractID + "\n\n");

                string strContract = OTAPI_Wrap::GetAssetType_Contract(strContractID);

                if (VerifyStringVal(strContract))
                {
                    // stderr
                    OTAPI_Wrap::Output(0, "-------------------------------------------\nNew asset contract:\n\n");

                    // stdout
                    print(strContract);

                    OTAPI_Wrap::Output(0, "\n\n");

                    return 1;
                }
            }
        }
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t main_create_acct()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    // Just to show how easy it is now, let's try a "create_asset_acct" message.
    // (It sends a NymID to the server, and downloads that Nym's public key.)

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("MyPurse"))
    {
        if (!OTAPI_Wrap::IsNym_RegisteredAtServer(MyNym, Server))
        {
            // If the Nym's not registered at the server, then register him first.
            main_register_nym();
        }

        // Send the request.
        //
        string strResponse = madeEasy.create_asset_acct(Server, MyNym, MyPurse); // Send the 'create_asset_acct' message to the server.

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:

        // -1 error, 0 failure, 1 success.
        //
        if (1 != VerifyMessageSuccess(strResponse))
        {
            OTAPI_Wrap::Output(0, "\n\ncreate_asset_acct: Failed.\n\n");
            return -1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "Success in create_asset_acct! Server response:\n\n"); // stderr
            print(strResponse); // stdout
            OTAPI_Wrap::Output(0, "\n (Success in create_asset_acct)\n\n"); //stderr
            return 1;
        }
    }

    // Done!
    return -1;
}


OT_COMMAND_OT int32_t main_add_signature()
{
    // SignContract erases all signatures and affixes a new one alone.
    // But AddSignature, on the other hand, leaves all signatures in place, and simply adds yours to the list.

    if (VerifyExists("MyNym"))
    {

        OTAPI_Wrap::Output(0, "Please enter an already-signed contract you wish to add your signature to, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strInput = OT_CLI_ReadUntilEOF();

        OTAPI_Wrap::Output(0, "\n\n You entered:\n" + strInput + "\n\n");

        string strOutput = OTAPI_Wrap::AddSignature(MyNym, strInput);

        // stderr
        OTAPI_Wrap::Output(0, "-------------------------------------------\nSigned:\n\n");

        // stdout
        print(strOutput);

        // stderr
        OTAPI_Wrap::Output(0, "\n\n");

        return 1;
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t main_sign_contract()
{
    // SignContract erases all signatures and affixes a new one alone.
    // But AddSignature, on the other hand, leaves all signatures in place, and simply adds yours to the list.

    string strUsage = concat("\n\n FYI, USAGE: sign \n",
        " Optionally, you may specify a contract type:  sign --args \"type LEDGER\"\nIn that example, the output would start with the bookend: -----BEGIN OT SIGNED LEDGER-----\n(You don't need to specify the type if the bookend is already present on the input string.)\n\n");

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym"))
    {
        OTAPI_Wrap::Output(0, "Please enter a contract to be signed, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strInput = OT_CLI_ReadUntilEOF();

        OTAPI_Wrap::Output(0, "\n\n You entered:\n" + strInput + "\n\n");

        string strOutput = OTAPI_Wrap::SignContract(MyNym, strInput);

        if (!VerifyStringVal(strOutput))
        {
            // Maybe we need to flat sign (maybe it wasn't already a signed contract...)
            //
            string strContractType;

            if (VerifyExists("Args"))
            {
                strContractType = OT_CLI_GetValueByKey(Args, "type");
            }

            if (VerifyStringVal(strContractType))
            {
                OTAPI_Wrap::Output(0, "A properly-formed-and-signed contract was not provided, but a 'type' was... so we'll try flatsigning the input text...\n\n");
                strOutput = OTAPI_Wrap::FlatSign(MyNym, strInput, strContractType);
            }
            else
            {
                OTAPI_Wrap::Output(0, "A properly-formed-and-signed contract was not provided, and neither was a 'type' in order to form one. (Failure.)\n");
                OTAPI_Wrap::Output(0, strUsage);
                return -1;
            }
        }


        int32_t nReturnVal = -1;

        if (VerifyStringVal(strOutput))
        {
            // stderr
            OTAPI_Wrap::Output(0, "-------------------------------------------\nSigned:\n\n");

            // stdout
            print(strOutput);

            nReturnVal = 1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\nSorry, but OT was unable to sign. Oh well.");
        }

        // stderr
        OTAPI_Wrap::Output(0, "\n\n");

        return nReturnVal;
    }

    // "return value"
    return -1;
}


OT_COMMAND_OT int32_t details_kill_offer(const string & strServerID, const string & strNymID, const string & strAcctID, const string & strTransNum)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    // Just to show how easy it is now, let's try a "kill_market_offer" message.
    // (It kills a market offer.)

    if (VerifyStringVal(strServerID) && VerifyStringVal(strNymID) && VerifyStringVal(strAcctID) && VerifyStringVal(strTransNum))
    {
        // Send the transaction.
        //
        string strResponse = madeEasy.kill_market_offer(strServerID, strNymID, strAcctID, strTransNum);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:

        if (1 != VerifyMessageSuccess(strResponse))
        {
            OTAPI_Wrap::Output(0, "\n\n killoffer: Failed.\n");
        }
        else if (1 != VerifyMsgBalanceAgrmntSuccess(strServerID, strNymID, strAcctID, strResponse))
        {
            OTAPI_Wrap::Output(0, "\n\n killoffer: Balance agreement failed.\n");
        }
        else if (1 != VerifyMsgTrnxSuccess(strServerID, strNymID, strAcctID, strResponse))
        {
            OTAPI_Wrap::Output(0, "\n\n killoffer: Balance agreement succeeded, but transaction failed.\n");
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\nSuccess in killoffer! Server response:\n\n");
            print(strResponse); // stdout
            OTAPI_Wrap::Output(0, "\n"); // stderr
            return 1;
        }
    }

    // Done!
    return -1;
}


OT_COMMAND_OT int32_t main_kill_offer()
{


    string strUsage = "\n\n FYI, used for killing an active market offer.\nUSAGE: killoffer --args \"transnum <transaction_number>\"\n\n";

    // Just to show how easy it is now, let's try a "kill_market_offer" message.
    // (It kills a market offer.)

    if (!VerifyExists("Server") || !VerifyExists("MyNym") || !VerifyExists("MyAcct") || !VerifyExists("Args"))
    {
        OTAPI_Wrap::Output(0, strUsage);
    }
    else
    {
        string strTransactionNum = OT_CLI_GetValueByKey(Args, "transnum");

        if (!VerifyStringVal(strTransactionNum))
        {
            OTAPI_Wrap::Output(0, "\n\n\nYou need to provide a transaction number...\n\n");
            OTAPI_Wrap::Output(0, strUsage);
        }
        else
        {
            return details_kill_offer(Server, MyNym, MyAcct, strTransactionNum);
        }
    }

    // Done!
    return -1;
}


OT_COMMAND_OT int32_t main_kill_plan()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    // string OT_CLI_GetValueByKey(Args, str_key)

    string strUsage = "\n\n FYI, used for stopping an active payment plan.\nUSAGE: killplan --args \"transnum <transaction_number>\"\n\n";

    // Just to show how easy it is now, let's try a "kill_payment_plan" message.
    // It kills an active (already running) payment plan.

    if (!VerifyExists("Server") || !VerifyExists("MyNym") || !VerifyExists("MyAcct") || !VerifyExists("Args"))
    {
        OTAPI_Wrap::Output(0, strUsage);
    }
    else
    {
        string strTransactionNum = OT_CLI_GetValueByKey(Args, "transnum");

        if (!VerifyStringVal(strTransactionNum))
        {
            OTAPI_Wrap::Output(0, "\n\n\nYou need to provide a transaction number...\n\n");
            OTAPI_Wrap::Output(0, strUsage);
        }
        else
        {
            // Send the transaction.
            //
            string strResponse = madeEasy.kill_payment_plan(Server, MyNym, MyAcct, strTransactionNum);

            // NOTICE: No need here to deal with retries, timeouts, request number,
            // syncing transaction number, download / process nymbox, etc! It's all
            // handled at a lower level!  Instead, simply check for success or failure:

            if (1 != VerifyMessageSuccess(strResponse))
            {
                OTAPI_Wrap::Output(0, "\n\nkill_payment_plan: Failed.\n");
            }
            else if (1 != VerifyMsgBalanceAgrmntSuccess(Server, MyNym, MyAcct, strResponse))
            {
                OTAPI_Wrap::Output(0, "\n\nkill_payment_plan: Balance agreement failed.\n");
            }
            else if (1 != VerifyMsgTrnxSuccess(Server, MyNym, MyAcct, strResponse))
            {
                OTAPI_Wrap::Output(0, "\n\nkill_payment_plan: Balance agreement succeeded, but transaction failed.\n");
            }
            else
            {
                OTAPI_Wrap::Output(0, "\n\nSuccess in kill_payment_plan! Server response:\n\n");
                print(strResponse); // stdout
                OTAPI_Wrap::Output(0, "\n\n"); // stderr
                return 1;
            }
        }
    }

    // Done!
    return -1;
}


OT_COMMAND_OT int32_t main_verify_signature()
{
    if (VerifyExists("HisNym"))
    {
        OTAPI_Wrap::Output(0, "Please enter a contract you wish to verify with HisNym, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strInput = OT_CLI_ReadUntilEOF();

        OTAPI_Wrap::Output(0, "\n\n--------------------------------------\n You entered:\n" + strInput + "\n\n");

        bool bSuccess = false;

        bSuccess = OTAPI_Wrap::VerifySignature(HisNym, strInput);

        if (bSuccess)
        {
            print("\n\n *** Verified! ***\n\n");
            return 1;
        }
        else
        {
            print("Failed!\n\n");
        }
    }

    // return value;
    return -1;
}


OT_COMMAND_OT int32_t stat_nyms()
{
    print("------------------------------------------------------------------");
    print(" ** PSEUDONYMS: \n");

    int32_t nNymCount = OTAPI_Wrap::GetNymCount();

    for (int32_t i = 0; i < nNymCount; ++i)
    {
        string strIndex = to_string(i);
        string strID = OTAPI_Wrap::GetNym_ID(i);
        string strName = OTAPI_Wrap::GetNym_Name(strID);

        print(strIndex + ": " + strID + " ---  " + strName);
    }

    return 1;
}

OT_COMMAND_OT int32_t stat_servers()
{
    print("------------------------------------------------------------------");
    print(" ** SERVERS: \n");
    int32_t nServerCount = OTAPI_Wrap::GetServerCount();

    for (int32_t i = 0; i < nServerCount; ++i)
    {
        string strIndex = to_string(i);
        string strID = OTAPI_Wrap::GetServer_ID(i);
        string strName = OTAPI_Wrap::GetServer_Name(strID);

        print(strIndex + ": " + strID + " ---  " + strName);
    }

    return 1;
}


OT_COMMAND_OT int32_t stat_assets()
{
    print("------------------------------------------------------------------");
    print(" ** ASSET TYPES: \n");
    int32_t nAssetTypeCount = OTAPI_Wrap::GetAssetTypeCount();

    for (int32_t i = 0; i < nAssetTypeCount; ++i)
    {
        string strID = OTAPI_Wrap::GetAssetType_ID(i);
        string strName = OTAPI_Wrap::GetAssetType_Name(strID);

        print(strID + " ---  " + strName);
    }

    return 1;
}


OT_COMMAND_OT int32_t stat_accounts()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    print("------------------------------------------------------------------");
    print(" ** ACCOUNTS: \n");

    int32_t nAccountCount = OTAPI_Wrap::GetAccountCount();

    for (int32_t i = 0; i < nAccountCount; ++i)
    {
        if ((i > 0) && (i != (nAccountCount))) { print("-------------------------------------"); }
        string strID = OTAPI_Wrap::GetAccountWallet_ID(i);
        string strStatAcct = madeEasy.stat_asset_account(strID);
        bool bSuccess = VerifyStringVal(strStatAcct);
        if (bSuccess)
        {
            print(strStatAcct);
        }
        else
        {
            print("Error trying to stat an asset account: " + strID);
        }
        // stderr
        print("");
    }
    print("------------------------------------------------------------------");

    return 1;
}

OT_COMMAND_OT int32_t main_stat()
{
    print("");

    stat_nyms();
    stat_servers();
    stat_assets();
    stat_accounts();

    return 1;
}


OT_COMMAND_OT int32_t details_stat_account(const string & strID)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // stderr
    OTAPI_Wrap::Output(0, "\n\n------------------------------------------------------------------\n");

    string strStatAcct = madeEasy.stat_asset_account(strID);

    bool bSuccess = VerifyStringVal(strStatAcct);
    int32_t nSuccess = (bSuccess ? 1 : -1);

    if (bSuccess)
    {
        print(strStatAcct);
    }
    else
    {
        print("Error trying to stat an asset account: " + strID + "\n");
    }
    // stderr
    OTAPI_Wrap::Output(0, "\n");

    return nSuccess;
}


OT_COMMAND_OT int32_t main_stat_acct()
{
    if (VerifyExists("MyAcct"))
    {
        return details_stat_account(MyAcct);
    }
    return -1;
}


OT_COMMAND_OT int32_t details_account_balance(const string & strID)
{
    string strName = OTAPI_Wrap::GetAccountWallet_Name(strID);
    string strAssetID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strID);
    int64_t lBalance = OTAPI_Wrap::GetAccountWallet_Balance(strID);

    OTAPI_Wrap::Output(0, "\n    Balance: "); //stderr
    print(OTAPI_Wrap::FormatAmount(strAssetID, lBalance)); // stdout
    OTAPI_Wrap::Output(0, strID + "   (" + strName + ")\n\n"); //stderr

    return 1;
}

OT_COMMAND_OT int32_t main_balance()
{
    if (VerifyExists("MyAcct"))
    {
        return details_account_balance(MyAcct);
    }
    return -1;
}


OT_COMMAND_OT int32_t details_nym_stat(const string & strID)
{
    //  string strName    = OTAPI_Wrap::GetNym_Name(strID)
    string strStats = OTAPI_Wrap::GetNym_Stats(strID);

    print(strStats); // stdout

    return 1;
}


OT_COMMAND_OT int32_t main_nym_stat()
{
    if (VerifyExists("MyNym"))
    {
        return details_nym_stat(MyNym);
    }
    return -1;
}


OT_COMMAND_OT int32_t main_show_mint()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // SHOW MINT
    //
    // (Load a public mint from local storage and display it on the screen.
    // If necessary, download it from the server.)
    //

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("MyPurse"))
    {
        // Just to show how easy it is now, let's load up a mint and display it.
        // If this function is unable to load it, it will download the mint from
        // the server.
        //
        string strMint = madeEasy.load_or_retrieve_mint(Server, MyNym, MyPurse); // <=====

        // NOTICE -- there's no need here to deal with retries, timeouts, request number, synching
        // transaction number, download / process nymbox, etc! It's all handled interally.
        //
        // Simply "verify" the return value:
        //
        if (!VerifyStringVal(strMint))
        {
            OTAPI_Wrap::Output(0, "\n\n load_or_retrieve_mint: Failed.\n\n");
            return -1;
        }
        else // Success!
        {
            OTAPI_Wrap::Output(0, "\n\n"); // stderr
            print(strMint); // stdout
            OTAPI_Wrap::Output(0, "\n\n"); // stderr
            return 1;
        }
    }

    // Done!
    return -1;
}


// Creates a new Pseudonym and adds it to the wallet.
// (And sets the display name for the new Nym, in the wallet.)
// Prints the new NymID to stdout.
//
// Returns 1 for success, 0 for failure.
//
OT_COMMAND_OT int32_t details_create_nym(const int32_t nKeybits, const string & strName, const string & strSourceForNymID, const string & strAltLocation)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strNymID = madeEasy.create_pseudonym(nKeybits, strSourceForNymID, strAltLocation); // returns new Nym ID

    if (!VerifyStringVal(strNymID))
    {
        OTAPI_Wrap::Output(0, "details_create_nym: Failed in OT_ME::create_pseudonym(keybits == " + to_string(nKeybits) + ")\n");
        return -1;
    }
    OTAPI_Wrap::Output(0, "Success creating! " + to_string(nKeybits) + " keybits, new ID: "); // stderr
    print(strNymID); // stdout
    OTAPI_Wrap::Output(0, "\n"); //stderr

    bool bSetName = OTAPI_Wrap::SetNym_Name(strNymID, // subject
        strNymID, // signer
        strName);
    if (!bSetName)
    {
        OTAPI_Wrap::Output(0, "Failed in OT_API_SetNym_Name(name == " + strName + ")\n");
        return -1;
    }

    OTAPI_Wrap::Output(0, "Success setting name to: " + strName + "\n\n"); // stderr
    return 1;
}


OT_COMMAND_OT int32_t main_create_nym()
{
    string strUsage1 = "\nUsage:    newnym --args \"keybits 1024 name \\\"Bob's New Nym\\\"\"  \n";
    string strUsage2 = "Optional: newnym --args \"source \\\"http://test.com/credential_IDs\\\" \"  \n";
    string strUsage = strUsage1 + strUsage2 + "FYI, a source can be a URL, a Bitcoin address, a Namecoin address, a public key,\nor the unique DN info from a traditionally-issued cert. Hashing the source should\n produce the NymID. Also, the source should always (somehow) validate the\ncredential IDs, if they are to be trusted for their purported Nym.\nAnother optional parameter is 'altlocation' which, in the case of DN info as a source, would be the \ndownload location where a Cert should be found with that DN info, or a PKI where the Cert can be found.\n\nNOTE: If you leave the source BLANK, then OT will just generate a public key to serve as the source. The\npublic key will be hashed to form the NymID, and all credentials for that Nym will need to be signed by\nthe corresponding private key. That's the only way they can be 'verified by their source.'\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    int32_t nKeybits = 1024;
    string strName = "New Nym";
    string strSourceForNymID = ""; // Leave this blank to use a key-based Nym. Otherwise provide a source to hash (to form the NymID. All credentials must somehow verify through this source.)
    string strAltLocation = "";

    if (VerifyExists("Args", false))
    {
        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        //
        // EXAMPLE:  --args "keybits 1024"
        //
        string strKeybits = OT_CLI_GetValueByKey(Args, "keybits");
        string strNewName = OT_CLI_GetValueByKey(Args, "name");
        string strNewSource = OT_CLI_GetValueByKey(Args, "source");
        string strNewLocation = OT_CLI_GetValueByKey(Args, "location");

        if (VerifyStringVal(strKeybits) && (to_int(strKeybits) > 0))
        {
            nKeybits = to_int(strKeybits);
        }

        if (VerifyStringVal(strNewName))
        {
            strName = strNewName;
        }

        if (VerifyStringVal(strNewSource))
        {
            strSourceForNymID = strNewSource;
        }

        if (VerifyStringVal(strNewLocation))
        {
            strAltLocation = strNewLocation;
        }
    }


    return details_create_nym(nKeybits, strName, strSourceForNymID, strAltLocation);
}


/*
call OTAPI_Wrap::LoadInbox() to load the inbox ledger from local storage.

During this time, your user has the opportunity to peruse the inbox, and to decide which transactions therein he wishes to accept or reject. Usually the inbox is display on the screen, then the user selects various items to accept or reject, and then the user clicks “Process Inbox” and then you do this:
Then call OTAPI_Wrap::Ledger_CreateResponse() in order to create a ‘response’ ledger for that inbox, which will be sent to the server to signal your responses to the various inbox transactions.
Then call OTAPI_Wrap::Ledger_GetCount() (pass it the inbox) to find out how many transactions are inside of it. Use that count to LOOP through them…
Use OTAPI_Wrap::Ledger_GetTransactionByIndex() to grab each transaction as you iterate through the inbox. (There are various introspection functions you can use in the API here if you wish to display the inbox items on the screen for the user…)
Next call OTAPI_Wrap::Transaction_CreateResponse() for each transaction in the inbox, to create a response to it, accepting or rejecting it. This function creates the response and adds it to the response ledger.
Next, call OTAPI_Wrap::Ledger_FinalizeResponse() which will create a Balance Agreement for the ledger.
Finally, call OTAPI_Wrap::processInbox() to send your message to the server and process the various items.

If the message was successful, then use OTAPI_Wrap::Message_GetBalanceAgreementSuccess() and OTAPI_Wrap::Message_GetTransactionSuccess() as described above in the deposit cash instructions.
*/


// Done:  add options here for accept transfers, accept receipts, and accept all.
// Done:  Then basically make a version for the payments inbox for accept payments, accept invoices, and accept all.
//
// (Accepting payments can basically be automated, but accepting invoices requires user permission.)
//
// Therefore add:
//   acceptmoney    -- This accepts all incoming transfers and incoming payments
//                     (Not receipts or invoices) for any designated accounts and nyms.
//   acceptreceipts -- Accepts all inbox receipts (not transfers.)
//   acceptinvoices -- Accepts all invoices (not payments.)
//   acceptall      -- All of the above.
//
// Todo: Make the above functions also work with specific indices (vs "all")
//


//
// PROCESS INBOX, ACCEPTING ALL ITEMS WITHIN...
//
// Load an asset account's inbox from local storage and iterate through
// the items inside, and fire off a server message accepting them all.
//
// nItemType  == 0 for all, 1 for transfers only, 2 for receipts only.
// strIndices == "" for "all indices"
//
OT_COMMAND_OT int32_t accept_inbox_items(const string & strMyAcctID, const int32_t nItemType, const string & strIndices)
{
    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;
    Utility MsgUtil;

    // Look up the Nym ID based on the Account ID.
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(strMyAcctID);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on the specified account ( " + strMyAcctID + " ).\n");
        return -1;
    }

    if (VerifyExists("MyNym", false) && (MyNym != strMyNymID))
    {
        OTAPI_Wrap::Output(0, "Try again: MyNym is specified, but it's not the owner of the specified account ( " + strMyAcctID + " ).\n");
        OTAPI_Wrap::Output(0, "To override with the nym for this account, add: --mynym " + strMyNymID + " \n\n");
        return -1;
    }

    // Look up the Server ID based on the Account ID.
    //
    string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strMyAcctID);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find Server ID based on the specified account ( " + strMyAcctID + " ).\n");
        return -1;
    }

    if (VerifyExists("Server", false) && (Server != strServerID))
    {
        OTAPI_Wrap::Output(0, "Try again: Server is specified, but it's not the server for the specified account ( " + strMyAcctID + " ).\n");
        OTAPI_Wrap::Output(0, "To override with the server for this account, add: --server " + strServerID + " \n\n");
        return -1;
    }

    // returns bool.
    //
    // User may have already chosen indices (passed in) so we don't want to
    // re-download the inbox unless we HAVE to. But if the hash has changed, that's
    // one clear-cut case where we _do_ have to. Otherwise our balance agreement
    // will fail anyway. So hopefully we can let OT "be smart about it" here instead
    // of just forcing it to download every time even when unnecessary.
    //
    if (!MsgUtil.getIntermediaryFiles(strServerID, strMyNymID, strMyAcctID)) // boolean bForceDownload=false
    {
        OTAPI_Wrap::Output(0, "Unable to download necessary intermediary files for this inbox/account. (Failure.)\n");
        return -1;
    }


    // Make sure we have at least one transaction number (to process the inbox with.)
    //
    // NOTE: Normally we don't have to do this, because the high-level API is smart
    // enough, when sending server transaction requests, to grab new transaction numbers
    // if it is running low.
    // But in this case, we need the numbers available BEFORE sending the transaction
    // request, because the call to OTAPI_Wrap::Ledger_CreateResponse is where the number
    // is first needed, and that call is made long before the server transaction request
    // is actually sent.
    //
    if (!madeEasy.insure_enough_nums(10, strServerID, strMyNymID))
    {
        return -1;
    }

    string strInbox = OTAPI_Wrap::LoadInbox(strServerID, strMyNymID, strMyAcctID); // Returns NULL, or an inbox.

    if (!VerifyStringVal(strInbox))
    {
        OTAPI_Wrap::Output(0, "\n\n OT_API_LoadInbox: Failed.\n\n");
        return -1;
    }
    else // Success!
    {
        OTAPI_Wrap::Output(0, "\n\n"); // stderr
        //  print(strInbox)          // stdout

        int32_t nCount = OTAPI_Wrap::Ledger_GetCount(strServerID, strMyNymID, strMyAcctID, strInbox);

        if (VerifyIntVal(nCount) && (nCount > 0))
        {
            // NOTE!!! DO **NOT** create the response ledger until the FIRST iteration of the below loop that actually
            // creates a transaction response! If that "first iteration" never comes (due to receipts being skipped, etc)
            // then OTAPI_Wrap::Transaction_CreateResponse will never get called, and therefore Ledger_CreateResponse should
            // also not be called, either. (Nor should OTAPI_Wrap::Ledger_FinalizeResponse, etc.)
            //
            string strResponseLEDGER = "";

            int32_t nIndicesCount = VerifyStringVal(strIndices) ? OTAPI_Wrap::NumList_Count(strIndices) : 0;

            for (int32_t nIndex = 0; nIndex < nCount; ++nIndex)
            {
                bool bContinue = false;  // I'm hacking my own "continue" since the language doesn't support it....

                string strTrans = OTAPI_Wrap::Ledger_GetTransactionByIndex(strServerID, strMyNymID, strMyAcctID, strInbox, nIndex);

                // nItemType  == 0 for all, 1 for transfers only, 2 for receipts only.
                // strIndices == "" for "all indices"
                //
                if (nItemType > 0) // 0 means "all", so we don't have to skip anything based on type, if it's 0.
                {
                    string strTransType = OTAPI_Wrap::Transaction_GetType(strServerID, strMyNymID, strMyAcctID, strTrans);

                    // incoming transfer
                    if (("pending" == strTransType) && (1 != nItemType))
                    {
                        // if it IS an incoming transfer, but we're doing receipts, then skip it.
                        //                      continue // language doesn't support this
                        bContinue = true;
                    }
                    // receipt
                    else if (!bContinue && ("pending" != strTransType) && (2 != nItemType))
                    {
                        // if it is NOT an incoming transfer, then it's a receipt. If we're not doing receipts, then skip it.
                        //                      continue // language doesn't support this
                        bContinue = true;
                    }
                }

                if (!bContinue)
                {

                    // - If NO indices are specified, process them ALL.
                    //
                    // - If indices are specified, but the current index is not on
                    //   that list, then continue...
                    //
                    if ((nIndicesCount > 0) && !OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex)))
                    {
                        //                      continue  // language doesn't support continue.
                        bContinue = true;
                    }

                    else if (!bContinue)
                    {
                        // By this point we know we actually have to call OTAPI_Wrap::Transaction_CreateResponse
                        // Therefore, if OTAPI_Wrap::Ledger_CreateResponse has not yet been called (which it won't
                        // have been, the first time we hit this in this loop), then we call it here this one
                        // time, to get things started...
                        //
                        if (!VerifyStringVal(strResponseLEDGER))
                        {
                            strResponseLEDGER = OTAPI_Wrap::Ledger_CreateResponse(strServerID, strMyNymID, strMyAcctID, strInbox);

                            if (!VerifyStringVal(strResponseLEDGER))
                            {
                                OTAPI_Wrap::Output(0, "\n\nFailure: OT_API_Ledger_CreateResponse returned NULL.\n");
                                return -1;
                            }
                        }

                        // By this point, we know the ledger response exists, and we know we have to create
                        // a transaction response to go inside of it, so let's do that next...
                        //
                        string strNEW_ResponseLEDGER = OTAPI_Wrap::Transaction_CreateResponse(strServerID, strMyNymID, strMyAcctID, strResponseLEDGER, strTrans, true); // accept = true (versus rejecting a pending transfer, for example.)

                        if (!VerifyStringVal(strNEW_ResponseLEDGER))
                        {
                            OTAPI_Wrap::Output(0, "\n\nFailure: OT_API_Transaction_CreateResponse returned NULL.\n");
                            return -1;
                        }
                        strResponseLEDGER = strNEW_ResponseLEDGER;
                    }
                }
            } // for

            if (!VerifyStringVal(strResponseLEDGER))
            {
                // This means there were receipts in the box, but they were skipped.
                // And after the skipping was done, there were no receipts left.
                // So we can't just say "the box is empty" because it's not. But nevertheless,
                // we aren't actually processing any of them, so we return 0 AS IF the box
                // had been empty. (Because this is not an error condition. Just a "no op".)
                //
                return 0;
            }

            // Below this point, we know strResponseLEDGER needs to be sent,
            // so let's finalize it.
            //
            string strFinalizedResponse = OTAPI_Wrap::Ledger_FinalizeResponse(strServerID, strMyNymID, strMyAcctID, strResponseLEDGER);

            if (!VerifyStringVal(strFinalizedResponse))
            {
                OTAPI_Wrap::Output(0, "\n\nFailure: OT_API_Ledger_FinalizeResponse returned NULL.\n");
                return -1;
            }
            // ***************************************************************

            // Server communications are handled here...
            //
            string strResponse = madeEasy.process_inbox(strServerID, strMyNymID, strMyAcctID, strFinalizedResponse);
            string strAttempt = "process_inbox";

            // ***************************************************************

            int32_t nInterpretReply = InterpretTransactionMsgReply(strServerID, strMyNymID, strMyAcctID, strAttempt, strResponse);

            if (1 == nInterpretReply)
            {
                // Download all the intermediary files (account balance, inbox, outbox, etc)
                // since they have probably changed from this operation.
                //
                bool bRetrieved = madeEasy.retrieve_account(strServerID, strMyNymID, strMyAcctID, true); //bForceDownload defaults to false.

                OTAPI_Wrap::Output(0, "\n\nServer response (" + strAttempt + "): SUCCESS processing/accepting inbox.\n");
                OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");
            }

            // ***************************************************************
            //
            // Success!
            //
            return nInterpretReply;

        } // VerifyIntVal (nCount) && nCount > 0

        OTAPI_Wrap::Output(0, "The asset account inbox is empty.\n\n");
    }

    return 0;
}


OT_COMMAND_OT int32_t main_accept_receipts()
{
    string strUsage1 = "\nUsage:  acceptreceipts --myacct FOR_ACCT --args \"indices 3,6,8\"  \n (Sample indices are shown.)\n";
    string strUsage2 = "If indices are not specified for myacct's inbox, then OT will\n";
    string strUsage = strUsage1 + strUsage2 + "accept ALL receipts (but no pending transfers) in that box.\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strIndices = "";

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.
        }

        return accept_inbox_items(MyAcct, 2, strIndices);
    }

    return -1;
}


OT_COMMAND_OT int32_t main_accept_inbox()
{
    string strUsage1 = "\nUsage:  acceptinbox --myacct FOR_ACCT --args \"indices 3,6,8\"  \n (Sample indices are shown.)\n";
    string strUsage2 = "If indices are not specified for myacct's inbox, then OT will\n";
    string strUsage = strUsage1 + strUsage2 + "accept ALL transfers and receipts in that box.\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strIndices = "";

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.
        }

        return accept_inbox_items(MyAcct, 0, strIndices);
    }

    return -1;
}


OT_COMMAND_OT int32_t main_accept_transfers()
{
    string strUsage1 = "\nUsage:  accepttransfers --myacct FOR_ACCT --args \"indices 3,6,8\"  \n (Sample indices are shown.)\n";
    string strUsage2 = "If indices are not specified for myacct's inbox, then OT will\n";
    string strUsage = strUsage1 + strUsage2 + "accept ALL transfers (but no receipts) in that box.\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strIndices = "";

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.
        }

        return accept_inbox_items(MyAcct, 1, strIndices);
    }

    return -1;
}


// Accept incoming payments and transfers. (NOT receipts or invoices.)
//
OT_COMMAND_OT int32_t main_accept_money()
{
    string strUsage = "\nUsage:  acceptmoney --myacct INTO_ACCT\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strIndices = "";

        int32_t nAcceptedTransfers = accept_inbox_items(MyAcct, 1, strIndices); // accepts transfers only, leaves receipts.

        int32_t nAcceptedPurses = accept_from_paymentbox(MyAcct, strIndices, "PURSE");
        // Voucher is already interpreted as a form of cheque, so this is redundant.
        //      int32_t nAcceptedVouchers = accept_from_paymentbox(MyAcct, strIndices, "VOUCHER")
        int32_t nAcceptedCheques = accept_from_paymentbox(MyAcct, strIndices, "CHEQUE");

        // If all five calls succeed, then the total here is 5.
        // So we return success as well (1).
        //
        if ((nAcceptedTransfers > -1) || (nAcceptedPurses > -1) || (nAcceptedCheques > -1))
        {
            return 1;
        }
    }

    return -1;
}


// Accept all incoming transfers, receipts, payments, and invoices.
//
OT_COMMAND_OT int32_t main_accept_all()
{
    string strUsage = "\nUsage:  acceptall --myacct INTO_ACCT\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strIndices = "";

        //  Incoming transfers and receipts (asset account inbox.)
        //
        int32_t nAcceptedInbox = accept_inbox_items(MyAcct, 0, strIndices); // accepts transfers AND receipts.

        // Incoming payments -- cheques, purses, vouchers (payments inbox for nym)
        //
        int32_t nAcceptedPurses = accept_from_paymentbox(MyAcct, strIndices, "PURSE");
        // Voucher is already interpreted as a form of cheque, so this is redundant.
        //      int32_t nAcceptedVouchers = accept_from_paymentbox(MyAcct, strIndices, "VOUCHER")
        int32_t nAcceptedCheques = accept_from_paymentbox(MyAcct, strIndices, "CHEQUE");

        // Invoices LAST (so the MOST money is in the account before it starts paying out.)
        //
        int32_t nAcceptedInvoices = accept_from_paymentbox(MyAcct, strIndices, "INVOICE");

        // If all four calls succeed, then the total here is 4.
        // So we return success as well (1).
        //
        if (4 == (nAcceptedInbox + nAcceptedPurses + nAcceptedCheques + nAcceptedInvoices))
        {
            return 1;
        }
    }

    return -1;
}


// returns the server response string (or null.)
// Use VerifyStringVal and/or VerifyMessageSuccess on it, for more info.
//
OT_COMMAND_OT string details_check_user(const string & strServerID, const string & strMyNymID, const string & strHisNymID)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    // Just to show how easy it is now, let's try a "check_user" message.
    // (It sends a NymID to the server, and downloads that Nym's public key.)

    string strServerParam = strServerID;
    string strMyNymParam = strMyNymID;
    string strHisNymParam = strHisNymID;

    string strResponse;

    // NOTE: If this were Server, MyNym, and HisNym, then we'd have already
    // translated the partials to read IDs (in OT itself) but we don't have that
    // guarantee in this function. Maybe strServerID was passed in from user input
    // directly, while inside another script. Partial IDs should still work, right?
    // So here, we translate them just in case.
    //
    if (VerifyStringVal(strServerID) && VerifyStringVal(strMyNymID) && VerifyStringVal(strHisNymID))
    {
        // IF we are able to resolve the HisNymId from a partial, then we
        // replace the partial with the full version.
        // (Otherwise we assume it's already a full ID and we don't mess with it.)
        //
        string strServerFromPartial = OTAPI_Wrap::Wallet_GetServerIDFromPartial(strServerID);

        if (VerifyStringVal(strServerFromPartial))
        {
            strServerParam = strServerFromPartial;
        }

        string strHisNymFromPartial = OTAPI_Wrap::Wallet_GetNymIDFromPartial(strHisNymID);

        if (VerifyStringVal(strHisNymFromPartial))
        {
            strHisNymParam = strHisNymFromPartial;
        }

        string strMyNymFromPartial = OTAPI_Wrap::Wallet_GetNymIDFromPartial(strMyNymID);

        if (VerifyStringVal(strMyNymFromPartial))
        {
            strMyNymParam = strMyNymFromPartial;
        }

        // Send the request.
        //
        strResponse = madeEasy.check_user(strServerParam, strMyNymParam, strHisNymParam); // Send the 'check_user' message to the server.
    }
    else
    {
        OTAPI_Wrap::Output(0, "\n details_check_user: Bad input... strServerID, strMyNymID, or strHisNymID \n");
    }

    // Done
    return strResponse;
}


OT_COMMAND_OT int32_t main_check_user()
{
    string strUsage = "Usage:   opentxs checknym --mynym MY_NYM_ID --hisnym HIS_NYM_ID \n Downloads the public key for HisNym.\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("HisNym") && VerifyExists("Args"))
    {
        //        string strHisNym = OT_CLI_GetValueByKey( Args, "hisnym" )
        //
        //        if (!VerifyStringVal(strHisNym))
        //        {
        //            OTAPI_Wrap::Output(0, "\n\n Missing:  --args \"hisnym HIS_NYM_ID_GOES_HERE\"\n\n");
        //            return -1;
        //; }

        // Send the request.
        //
        string strResponse = details_check_user(Server, MyNym, HisNym);


        // -1 is error,
        //  0 is reply received: failure
        //  1 is reply received: success
        //
        if (1 == VerifyMessageSuccess(strResponse))
        {
            OTAPI_Wrap::Output(0, "\n\nSuccess in checknym! Server response:\n\n");
            print(strResponse); // stdout
            OTAPI_Wrap::Output(0, "\n\n"); //stderr
            return 1;
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\n checknym: Failed.\n\n");
        }
    }

    // Done
    return -1;
}


OT_COMMAND_OT int32_t download_acct_files()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
        return -1;
    }


    // Download all the intermediary files (account balance, inbox, outbox, etc)
    // since they have probably changed from this operation.
    //
    bool bRetrieved = madeEasy.retrieve_account(Server, strMyNymID, MyAcct, true); //bForceDownload defaults to false.

    OTAPI_Wrap::Output(0, "\n\n" + string(bRetrieved ? "SUCCESS" : "FAILED") + " retrieving intermediary files for account: " + MyAcct + "\n\n");

    return bRetrieved ? 1 : -1;
}


OT_COMMAND_OT int32_t main_dl_acct_files()
{
    string strUsage = "\n\n Usage:  refreshacct --server SERVER_ID --myacct YOUR_ACCT_ID\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyAcct"))
    {
        return download_acct_files();
    }

    return -1;
}


OT_COMMAND_OT int32_t main_refresh_all()
{
    string strUsage = "Usage:  refresh --server SERVER_ID --mynym YOUR_NYM_ID --myacct YOUR_ACCT_ID\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("MyAcct"))
    {
        int32_t nSuccess = main_refresh_nym();   // <=======

        if (-1 == nSuccess)
        {
            return -1;
        }

        return main_dl_acct_files();  // <=======
    }

    return -1;
}


OT_COMMAND_OT int32_t details_download_contract(const string & strServerID, const string & strNymID, const string & strContractID)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    // Download all the intermediary files (account balance, inbox, outbox, etc)
    // since they have probably changed from this operation.
    //
    string strRetrieved = madeEasy.retrieve_contract(strServerID, strNymID, strContractID);
    int32_t nRetrieved = VerifyMessageSuccess(strRetrieved);

    string strSuccess = "ERROR";

    if (1 == nRetrieved)
    {
        strSuccess = "SUCCESS";
    }
    else if (0 == nRetrieved)
    {
        strSuccess = "FAILED";
    }

    OTAPI_Wrap::Output(0, "\n\n " + strSuccess + " retrieving contract: " + strContractID + "\n\n");

    return (1 == nRetrieved) ? 1 : -1;
}


OT_COMMAND_OT int32_t main_download_contract()
{
    string strUsage = concat("\n\nUsage:  getcontract --server SERVER_ID --mynym YOUR_NYM_ID \n",
        "                    --args \"contract_id CONTRACT_ID_HERE\"\n\n");
    OTAPI_Wrap::Output(0, strUsage);

    string strContractID = "";

    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args"))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "contract_id CvHGtfOOKzQKL5hFL7J4iF5yAodVKhS1rxPzME5R9XA"
            //
            string strNewContractID = OT_CLI_GetValueByKey(Args, "contract_id");


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewContractID))
            {
                strContractID = strNewContractID;
            }
            else
            {
                OTAPI_Wrap::Output(0, "\n\nMissing --args \"contract_id CONTRACT_ID_HERE\"\n\n");
                return -1;
            }

            return details_download_contract(Server, MyNym, strContractID);
        }

    }

    return -1;
}


OT_COMMAND_OT int32_t main_verify_last_receipt()
{

    // Instantiate the "OT Made Easy" object.
    //

    MadeEasy madeEasy;

    // SHOW INBOX
    //
    // Load an asset account's inbox from local storage and display it on the screen.
    //

    if (VerifyExists("Server") && VerifyExists("MyAcct"))
    {

        // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
        //
        string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

        if (!VerifyStringVal(strMyNymID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
            return -1;
        }
        // ***************************************************************

        bool bSuccess = OTAPI_Wrap::VerifyAccountReceipt(Server, strMyNymID, MyAcct);

        if (!bSuccess)
        {
            OTAPI_Wrap::Output(0, "\n\n OT_API_VerifyAccountReceipt: Failed. Try using refreshacct and then try verifying again.\n\n");
            return -1;
        }
        else // Success!
        {
            OTAPI_Wrap::Output(0, "\n\nVerify receipt:  success!\n\n"); // stderr
            return 1;
        }
    }

    // Done!
    return -1;
}


OT_COMMAND_OT int32_t main_register_nym()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage = concat("\n\nUsage: register_nym.ot --server SERVER_ID --mynym NYM_ID\n\n",
        "(If you don't have a NymID, then use create_nym.ot first.)\n\n");

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        string strResponse = madeEasy.register_nym(Server, MyNym); // This also does getRequest internally, if success.
        int32_t nSuccess = VerifyMessageSuccess(strResponse);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:
        //
        // -1 is error,
        //  0 is reply received: failure
        //  1 is reply received: success
        //
        switch (nSuccess)
        {
        case 1:
            OTAPI_Wrap::Output(0, "\n\n Server response:\n\n");
            print(strResponse); // stdout
            OTAPI_Wrap::Output(0, "\n\n SUCCESS in register_nym!\n(Also, success syncronizing the request number.)\n\n");
            break;
        case 0:
            OTAPI_Wrap::Output(0, "\n\n FAILURE in register_nym! Server response:\n\n");
            print(strResponse); // stdout
            break;
        default:
            OTAPI_Wrap::Output(0, "\n\nError in register_nym!\n");

            if (VerifyStringVal(strResponse))
            {
                OTAPI_Wrap::Output(0, "Server response:\n\n");
                print(strResponse); // stdout
            }
            break;
        }
        OTAPI_Wrap::Output(0, "\n\n"); //stderr

        return nSuccess;
    }

    return -1;
}


OT_COMMAND_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID, const bool bForceDownload)
{
    bool bWasMsgSent = false;

    return details_refresh_nym(strServerID, strMyNymID, bWasMsgSent, bForceDownload);
}


OT_COMMAND_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID, bool & bWasMsgSent, const bool bForceDownload)
{
    MadeEasy madeEasy;

    int32_t nGetAndProcessNymbox = madeEasy.retrieve_nym(strServerID, strMyNymID, bWasMsgSent, bForceDownload);

    // NOTICE: No need here to deal with retries, timeouts, request number,
    // syncing transaction number, download / process nymbox, etc! It's all
    // handled at a lower level!  Instead, simply check for success or failure:
    //
    // -1 is error,
    //  0 is reply received: failure
    //  1 is reply received: success
    //
    bool bReturnVal = false;

    switch (nGetAndProcessNymbox)
    {
    case 1:
        OTAPI_Wrap::Output(0, "\n\n SUCCESS in refresh nym!\n");
        bReturnVal = true;
        break;
    case 0:
        if (bWasMsgSent) // the message was sent, and the server replied "failure".
        {
            OTAPI_Wrap::Output(0, "\n\n FAILURE in refresh nym!\n");
        }
        else // the message wasn't sent; the 0 in this case means "nymbox was empty."
        {
            OTAPI_Wrap::Output(0, "\n\n Success in refresh nym! (Skipped processing Nymbox, since it's empty.)\n");
            bReturnVal = true;
        }
        break;
    default:
        OTAPI_Wrap::Output(0, "\n\nError in refresh nym! nGetAndProcessNymbox: " + to_string(nGetAndProcessNymbox) + "\n");
        break;
    }

    return bReturnVal;
}

OT_COMMAND_OT bool details_refresh_nym(const string & strServerID, const string & strMyNymID)
{
    bool bForceDownload = true;

    return details_refresh_nym(strServerID, strMyNymID, bForceDownload);
}


OT_COMMAND_OT int32_t main_refresh_nym()
{
    string strUsage = concat("\n\nUsage: refreshnym --server SERVER_ID --mynym NYM_ID\n\n",
        "(If you don't have a NymID, then use the newnym command first.)\n\n");
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        bool bReturnVal = details_refresh_nym(Server, MyNym);

        OTAPI_Wrap::Output(0, "\n"); //stderr

        if (bReturnVal)
        {
            return 1;
        }
    }

    return -1;
}


// GET BOX RECEIPT          Note: from ot_made_easy.ot
// Note: nBoxType is 0 for Nymbox, 1 for Inbox, and 2 for Outbox.
// Also, if nBoxType is 0 (nymbox) then you have to pass the NymID in the ACCT_ID
// argument, as well as the NYM_ID argument (you have to pass it twice...)
// Otherwise for inbox/outbox, pass the actual ACCT_ID there as normal.
//
//def OT_ME::get_box_receipt(SERVER_ID, NYM_ID, ACCT_ID, nBoxType, STR_TRANS_NUM)
//{
//    var ot_Msg := OTAPI_Func()
//    // -------------------------
//    var theRequest := OTAPI_Func(ot_Msg.GET_BOX_RECEIPT, SERVER_ID, NYM_ID, ACCT_ID, nBoxType, STR_TRANS_NUM)
//    string strResponse = theRequest.SendRequest(theRequest, "GET_BOX_RECEIPT")
//
//    return strResponse;
//; }


OT_COMMAND_OT int32_t details_download_box_receipt(const string & strID, const int32_t nBoxType)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    string strMyNymID = MyNym;
    string strAcctID;

    // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
    //
    if (0 == nBoxType)  // It's a Nymbox he's after. (Use NymID for the AcctID, in this case.)
    {
        strAcctID = MyNym;
    }
    else // it's an inbox or outbox (needs an acct ID.)
    {
        if (!VerifyExists("MyAcct", false))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find MyAcct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
            return -1;
        }
        else
        {
            strAcctID = MyAcct;

            // (After this point, MyNym contains the NymID, and strMyNymID contains
            // the NymID that corresponds to MyAcct -- they may not necessarily be
            // the same Nym...)
            //
            strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(strAcctID);

            if (!VerifyStringVal(strMyNymID))
            {
                OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
                OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
                return -1;
            }

            if (strMyNymID != MyNym)
            {
                OTAPI_Wrap::Output(0, "Failure: Found a NymID based on myacct, but MyNym is not the same ID.\n");
                OTAPI_Wrap::Output(0, "To avoid any confusion, please be explicit with Nym ID:   --mynym NYM_ID \n\n");
                return -1;
            }
        }
    }
    // ***************************************************************

    // HERE, WE SEND THE 'GET BOX RECEIPT' REQUEST TO THE SERVER
    //
    string strResponse = madeEasy.get_box_receipt(Server, strMyNymID, strAcctID, nBoxType, strID);
    //  string strAttempt = "get_box_receipt"; // unused here.

    // ***************************************************************
    // NOTICE: No need here to deal with retries, timeouts, request number,
    // syncing transaction number, download / process nymbox, etc! It's all
    // handled at a lower level!
    //
    // Instead, simply check for success or failure:
    //
    int32_t nInterpretReply = VerifyMessageSuccess(strResponse);

    if (!VerifyIntVal(nInterpretReply) || (1 != nInterpretReply))
    {
        OTAPI_Wrap::Output(0, "get_box_receipt: Failed. nInterpretReply is: " + to_string(nInterpretReply) + "\n");
        OTAPI_Wrap::Output(0, "get_box_receipt: Perhaps that receipt is no longer in the box?\n");
    }
    else
    {
        OTAPI_Wrap::Output(0, "Success in get_box_receipt! Server response:\n\n");
        print(strResponse);
        OTAPI_Wrap::Output(0, "\n\n");
        return 1;
    }
    // ***************************************************************
    //
    // Return status to caller.
    //
    return nInterpretReply;
}


OT_COMMAND_OT int32_t main_get_box_receipt()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage = concat("\n\nUsage: getboxreceipt --server SERVER_ID --mynym NYM_ID\n\n",
        "Also:    --args \"box_type BOX_TYPE_ID_HERE id TRANSACTION_ID_HERE\"\nBox types are 0 (Nymbox), 1 (Inbox), 2 (Outbox)\n\n");

    OTAPI_Wrap::Output(0, strUsage);

    string strID;
    int32_t nBoxType = 1;  // Inbox by default.

    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args"))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "box_type 0 id 98"
            //
            string strNewID = OT_CLI_GetValueByKey(Args, "id");
            string strNewType = OT_CLI_GetValueByKey(Args, "box_type");


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewID))
            {
                strID = strNewID;
            }
            else
            {
                OTAPI_Wrap::Output(0, "\n\nMissing --args \"id TRANSACTION_ID_HERE\"\n\n");
                return -1;
            }
            // **************************************************************
            //
            if (VerifyStringVal(strNewType))
            {
                nBoxType = to_int(strNewType);
            }

            if (!VerifyIntVal(nBoxType) || (nBoxType < 0) || (nBoxType > 2))
            {
                OTAPI_Wrap::Output(0, "\n\n box_type cannot be <0 or >2. Try:  --args \"box_type 1\"\nBox types are 0 (Nymbox), 1 (Inbox), 2 (Outbox)\n\n");
                return -1;
            }

            // If Inbox or Outbox, make sure we have an acct...
            //
            if ((nBoxType != 0) && !VerifyExists("MyAcct", false))
            {
                OTAPI_Wrap::Output(0, "\n\n For inbox (1) or outbox (2) box types, need an account ID.\nMissing: --myacct ACCT_ID_HERE \n\n");
                return -1;
            }


            return details_download_box_receipt(strID, nBoxType);
        }

    }

    return -1;
}


//
// WITHDRAW CASH
//
// (from asset account on server to cash purse on client.)
//
OT_COMMAND_OT int32_t details_withdraw_cash(const string & strMyAcctID, const int64_t lAmount)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(strMyAcctID);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
        return -1;
    }

    // MAKE SURE WE HAVE THE RIGHT ASSET CONTRACT
    //
    string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strMyAcctID);

    if (!VerifyStringVal(strAssetTypeID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find Asset Type ID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the asset type based on the account.\n\n");
        return -1;
    }

    string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strMyAcctID);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "Unable to find the server ID based on the account. Strange! Perhaps specify a different account? Use:  --myacct ACCT_ID \n");
        return -1;
    }

    if ((VerifyExists("Server", false) && !(strServerID == Server)))
    {
        OTAPI_Wrap::Output(0, "This account is on server ( " + strServerID + " -- the server is deduced based on the account), but the default server is ( " + Server + " ). To override it, use:  --server " + strServerID + " \n");
        return -1;
    }

    string assetContract = OTAPI_Wrap::LoadAssetContract(strAssetTypeID);

    if (!VerifyStringVal(assetContract))
    {
        string strResponse = madeEasy.retrieve_contract(strServerID, strMyNymID, strAssetTypeID);

        if (1 != VerifyMessageSuccess(strResponse))
        {
            OTAPI_Wrap::Output(0, "details_withdraw_cash: Unable to retrieve contract for IDs: \n");
            OTAPI_Wrap::Output(0, "  Server ID: " + strServerID + "\n");
            OTAPI_Wrap::Output(0, "   Asset ID: " + strAssetTypeID + "\n");
            return -1;
        }

        assetContract = OTAPI_Wrap::LoadAssetContract(strAssetTypeID);

        if (!VerifyStringVal(assetContract))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to load Asset contract even after retrieving it.\n");
            return -1;
        }
    }
    // By this point, we KNOW the appropriate asset contract is available.

    //
    // HERE, WE MAKE SURE WE HAVE THE PROPER MINT...
    //
    string strMint = madeEasy.load_or_retrieve_mint(strServerID, strMyNymID, strAssetTypeID);

    if (!VerifyStringVal(strMint))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to load or retrieve necessary mint file for withdrawal.\n");
        return -1;
    }
    // By this point, we know we can successfully load both:
    // 1. the proper asset contract.
    // 2. the proper (unexpired) mint file.
    // ***************************************************************
    // HERE, WE SEND THE WITHDRAWAL REQUEST TO THE SERVER
    //

    string strResponse = madeEasy.withdraw_cash(strServerID, strMyNymID, strMyAcctID, lAmount);
    string strAttempt = "withdraw_cash";
    // ***************************************************************

    // HERE, WE INTERPRET THE SERVER REPLY, WHETHER SUCCESS, FAIL, OR ERROR...

    //VerifyMsgTrnxSuccess
    int32_t nInterpretReply = InterpretTransactionMsgReply(strServerID, strMyNymID, strMyAcctID, strAttempt, strResponse);

    if (1 == nInterpretReply)
    {
        // Download all the intermediary files (account balance, inbox, outbox, etc)
        // since they have probably changed from this operation.
        //
        bool bRetrieved = madeEasy.retrieve_account(strServerID, strMyNymID, strMyAcctID); //bForceDownload defaults to false.

        OTAPI_Wrap::Output(0, "\n\nServer response (" + strAttempt + "): SUCCESS withdrawing cash! (From account on server to local purse.) \n");
        OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");
    }

    // ***************************************************************
    //
    // Return status to caller.
    //
    return nInterpretReply;
}


// HERE, WE GET ALL THE ARGUMENTS TOGETHER,
// and then call the above function.
//
OT_COMMAND_OT int32_t main_withdraw_cash()
{
    string strUsage = concat("\n\n  USAGE: withdraw --myacct YOUR_ASSET_ACCT \n",
        "You can provide an amount:  --args \"amount PUT_AMOUNT_HERE\"\n\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("MyAcct"))
    {

        // strAmount
        //
        string strAmount = "0"; // must be >= 1

        string strDefaultAmount = "1"; // must be >= 1

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false)) // displayErrorMsg=false
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "amount 1"
            //
            string strNewAmount = OT_CLI_GetValueByKey(Args, "amount"); // any integer value


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewAmount))
            {
                strAmount = strNewAmount;
            }
        }


        string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);

        // If the withdrawal parameters aren't provided, then we
        // ask the user to supply them at the command line.
        //
        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the amount[" + strDefaultAmount + "]: ");
            strAmount = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
        {
            strAmount = strDefaultAmount;
        }

        int64_t lAmount = OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount);

        return details_withdraw_cash(MyAcct, lAmount);   // <========================
    }

    return -1;
}


/*
pScript->chai.add(fun(&OTAPI_Wrap::Wallet_GetNymIDFromPartial),     "OT_API_Wallet_GetNymIDFromPartial")
pScript->chai.add(fun(&OTAPI_Wrap::Wallet_GetServerIDFromPartial),  "OT_API_Wallet_GetServerIDFromPartial")
pScript->chai.add(fun(&OTAPI_Wrap::Wallet_GetAssetIDFromPartial),   "OT_API_Wallet_GetAssetIDFromPartial")
pScript->chai.add(fun(&OTAPI_Wrap::Wallet_GetAccountIDFromPartial), "OT_API_Wallet_GetAccountIDFromPartial")

*/


//
// WITHDRAW VOUCHER
//
//(From asset account into instrument form,
// like a cashier's cheque.)
//


OT_COMMAND_OT int32_t details_withdraw_voucher(string & strOutput)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // HERE, WE LOOK UP THE NYM ID
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
        return -1;
    }

    // HERE, WE LOOK UP THE SERVER ID
    //
    string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find the server ID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the server ID based on the account.\n\n");
        return -1;
    }

    string strHisNymID;

    if (VerifyExists("HisNym")) // This ID is already validated in the C++ code (in this case.)
    {
        strHisNymID = HisNym;

        string strRecipientPubkey = madeEasy.load_or_retrieve_encrypt_key(strServerID, strMyNymID, strHisNymID);

        if (!VerifyStringVal(strRecipientPubkey))
        {
            OTAPI_Wrap::Output(0, "\n\nFailure: Unable to load or download pubkey for HisNym based on given value (" + strHisNymID + "). To override, use: --hisnym HIS_NYM_ID\n\n");
            return -1;
        }

    }
    else
    {
        OTAPI_Wrap::Output(0, "Optionally, enter recipient NymID (abbreviations accepted): ");

        string strHisPartialNymID = OT_CLI_ReadLine();

        if (VerifyStringVal(strHisPartialNymID)) // If the user typed something...
        {
            strHisNymID = OTAPI_Wrap::Wallet_GetNymIDFromPartial(strHisPartialNymID); // Try to find the associated ID...

            if (!VerifyStringVal(strHisNymID)) // But if it returned NULL, failure (return.)
            {
                OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find HisNym (Recipient) in your wallet. Use: --hisnym NYM_ID\n");
                return -1;
            }
        }

        else // The user just hit "enter" so we'll default the recipient Nym to the user himself.
        {
            strHisNymID = strMyNymID;
        }

    }

    // ***************************************************************
    //
    // strAmount and strMemo...
    //
    string strAmount = "0"; // must ultimately be >= 1
    string strMemo = ""; // can be blank

    string strDefaultAmount = "1"; // must be >= 1
    string strDefaultMemo = "(blank memo field)"; // can be blank

    // If custom arguments have been passed on the command line,
    // then grab them and use them instead of asking the user to enter them
    // at the command line.
    //
    string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);

    if (VerifyExists("Args", false))
    {
        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "amount 1"
        // EXAMPLE:  --args "amount 15 memo \"Just a memo for the voucher cheque.\""
        //
        string strNewAmount = OT_CLI_GetValueByKey(Args, "amount"); // any integer value
        string strNewMemo = OT_CLI_GetValueByKey(Args, "memo");     // optional memo field


        // Set the values based on the custom arguments, for those found.
        //
        if (VerifyStringVal(strNewAmount))
        {
            strAmount = strNewAmount;
        }
        if (VerifyStringVal(strNewMemo))
        {
            strMemo = strNewMemo;
        }
    }

    // If the transfer parameters aren't provided, then we
    // ask the user to supply them at the command line.
    //
    if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
    {
        OTAPI_Wrap::Output(0, "Enter the amount[" + strDefaultAmount + "]: ");
        strAmount = OT_CLI_ReadLine();
    }
    if (!VerifyStringVal(strMemo))
    {
        OTAPI_Wrap::Output(0, "Optionally, enter a memo on a single line[" + strDefaultMemo + "]: ");
        strMemo = OT_CLI_ReadLine();
    }

    if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
    {
        strAmount = strDefaultAmount;
    }
    if (!VerifyStringVal(strMemo))
    {
        strMemo = strDefaultMemo;
    }

    // ***************************************************************

    // HERE, WE SEND THE VOUCHER WITHDRAWAL REQUEST TO THE SERVER
    //
    int64_t lAmount = OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount);
    string strResponse = madeEasy.withdraw_voucher(strServerID, strMyNymID, MyAcct, strHisNymID, strMemo, lAmount);
    string strAttempt = "withdraw_voucher";
    //  static int32_t withdrawVoucher(const std::string SERVER_ID,
    //                             const std::string USER_ID,
    //                             const std::string ACCT_ID,
    //                             const std::string RECIPIENT_USER_ID,
    //                             const std::string CHEQUE_MEMO,
    //                             const std::string AMOUNT)
    // ***************************************************************
    //
    // HERE, WE INTERPRET THE SERVER REPLY, WHETHER SUCCESS, FAIL, OR ERROR...

    int32_t nInterpretReply = InterpretTransactionMsgReply(strServerID, strMyNymID, MyAcct, strAttempt, strResponse);

    if (1 == nInterpretReply) // Success!
    {

        string strLedger = OTAPI_Wrap::Message_GetLedger(strResponse);

        if (!VerifyStringVal(strLedger))
        {
            OTAPI_Wrap::Output(0, "\n\n details_withdraw_voucher: Error: strLedger is null, returned by OT_API_Message_GetLedger.\n");
            return -1;
        }

        string strTransReply = OTAPI_Wrap::Ledger_GetTransactionByIndex(strServerID, strMyNymID, MyAcct, strLedger, 0); // index 0.

        if (!VerifyStringVal(strTransReply))
        {
            OTAPI_Wrap::Output(0, concat("details_withdraw_voucher: Error: strTransReply is unexpectedly null, returned by ",
                "OT_API_Ledger_GetTransactionByIndex, argument passed, index 0 and ledger:\n\n") + strLedger + "\n\n");
            return -1;
        }


        strOutput = OTAPI_Wrap::Transaction_GetVoucher(strServerID, strMyNymID, MyAcct, strTransReply);

        if (!VerifyStringVal(strOutput))
        {
            OTAPI_Wrap::Output(0, concat("details_withdraw_voucher: Error: Voucher is unexpectedly null, returned by ",
                "OT_API_Transaction_GetVoucher with strTransReply set to:\n\n") + strTransReply + "\n\n");
            return -1;
        }
        else
        {
            // Save a copy in my own outpayments box. I don't want to lose this voucher since it uses
            // one of my own transaction numbers. (If I later send the voucher to someone, OT is smart
            // enough to remove the first copy from outpayments, when adding the second copy.)
            //
            // Notice how I can send an instrument to myself. This doesn't actually send anything --
            // it just puts a copy into my outpayments box for safe-keeping.
            //
            madeEasy.send_user_payment(strServerID, strMyNymID, strMyNymID, strOutput);
        }

        // Download all the intermediary files (account balance, inbox, outbox, etc)
        // since they have probably changed from this operation.
        //
        bool bRetrieved = madeEasy.retrieve_account(strServerID, strMyNymID, MyAcct, true); //bForceDownload defaults to false.
        OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");

        OTAPI_Wrap::Output(0, "details_withdraw_voucher: Voucher returned by OT_API_Transaction_GetVoucher:\n\n"); // stderr
        print(strOutput); // stdout
        OTAPI_Wrap::Output(0, "\n\n"); // stderr.

        OTAPI_Wrap::Output(0, "\n\nServer response (" + strAttempt + "): SUCCESS withdrawing voucher (cashier's cheque)!\n");

        return 1;
    }

    // ***************************************************************
    //
    // Return status to caller.
    //
    return nInterpretReply;
}


//  static int32_t withdrawVoucher(const std::string SERVER_ID,
//                             const std::string USER_ID,
//                             const std::string ACCT_ID,
//                             const std::string RECIPIENT_USER_ID,
//                             const std::string CHEQUE_MEMO,
//                             const std::string AMOUNT)

// HERE, WE GET ALL THE ARGUMENTS TOGETHER,
// and then call the above function.
//
OT_COMMAND_OT int32_t main_withdraw_voucher()
{
    string strUsage1 = concat("\n\n  USAGE: buyvoucher --myacct YOUR_ASSET_ACCT --hisnym RECIPIENT_NYM_ID\n\n",
        "Also NECESSARY: --args \"amount PUT_AMOUNT_HERE\"\n");
    string strUsage = concat(strUsage1,
        "And OPTIONALLY: --args \"memo \\\"Just a memo for the voucher cheque.\\\"\"\n\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("MyAcct"))
    {
        string strVoucher = "";
        return details_withdraw_voucher(strVoucher);
    }

    return -1;
}


OT_COMMAND_OT int32_t main_sendvoucher()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage1 = "Usage:  sendvoucher  --myacct MY_ASSET_ACCT --hisnym RECIPIENT_NYM_ID\n";
    string strUsage2 = "Server is deduced from MyAcct. This command withdraws AND SENDS the\nvoucher. (Use 'buyvoucher', not 'sendvoucher', if you don't want it to be immediately SENT.)\n";
    string strUsage = concat(strUsage1 + "Optionally: --args \"memo \\\"one-line memo allowed here.\\\" amount AMOUNT\"\n", strUsage2);

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strCheque = "";
        int32_t nReturnVal = details_withdraw_voucher(strCheque);

        //
        if ((1 == nReturnVal) && VerifyStringVal(strCheque))
        {
            // stderr
            OTAPI_Wrap::Output(0, "\n-------------------------------------------\n the voucher:\n\n");
            // stdout
            print(strCheque);
            // stderr
            OTAPI_Wrap::Output(0, "\n");

            // TODO: Store a copy in outpayments box (OR VERIFY THAT IT'S ALREADY BEING DONE, WHICH I BELIEVE THAT IT IS.)

            string strServerID = OTAPI_Wrap::Instrmnt_GetServerID(strCheque);
            string strSenderNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);
            string strRecipientNymID = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strCheque);

            if (!VerifyStringVal(strServerID))
            {
                OTAPI_Wrap::Output(0, "Unable to retrieve a Server ID from this voucher! Very strange. (Failure.)\n");
                return -1;
            }
            if (!VerifyStringVal(strSenderNymID))
            {
                OTAPI_Wrap::Output(0, "Unable to retrieve a Sender Nym ID from this voucher! Very strange. (Failure.)\n");
                return -1;
            }
            if (!VerifyStringVal(strRecipientNymID))
            {
                OTAPI_Wrap::Output(0, concat("Unable to retrieve a Recipient Nym ID from this voucher! Very strange. (Failure.)\n(Although ",
                    "it's fine to WITHDRAW a voucher with no recipient, still need the recipient ID to SEND one.)\n"));
                return -1;
            }

            string strResponse = madeEasy.send_user_payment(strServerID, strSenderNymID, strRecipientNymID, strCheque);

            // NOTICE: No need here to deal with retries, timeouts, request number,
            // syncing transaction number, download / process nymbox, etc! It's all
            // handled at a lower level!
            //
            // Instead, simply check for success or failure:
            //
            nReturnVal = VerifyMessageSuccess(strResponse);

            if (1 != nReturnVal)
            {
                OTAPI_Wrap::Output(0, "sendvoucher: Failed.\n");
            }
            else
            {
                OTAPI_Wrap::Output(0, "Success in sendvoucher! Server response:\n\n");
                print(strResponse);
                OTAPI_Wrap::Output(0, "(Success in sendvoucher)\n");
                return 1;
            }
        }

        return nReturnVal;
    }

    return -1;
}


OT_COMMAND_OT OTDB::MarketList * loadMarketList(const string & serverID)
{
    if (!OTDB::Exists("markets", serverID, "market_data.bin", ""))
    {
        OTAPI_Wrap::Output(0, "The market list file doesn't exist.\n");
        return NULL;
    }

    OTAPI_Wrap::Output(1, "Markets file exists...Querying list of markets...\n");

    OTDB::Storable * storable = OTDB::QueryObject(OTDB::STORED_OBJ_MARKET_LIST, "markets", serverID, "market_data.bin", "");
    if (!VerifyStorable(storable, "OTDB::Storable"))
    {
        OTAPI_Wrap::Output(0, "Failed to verify storable object. Probably doesn't exist.\n");
        return NULL;
    }

    OTAPI_Wrap::Output(1, "QueryObject worked. Now dynamic casting from storable to marketlist...\n");

    OTDB::MarketList * marketList = dynamic_cast<OTDB::MarketList *>(storable);
    if (!VerifyStorable(marketList, "OTDB::MarketList"))
    {
        OTAPI_Wrap::Output(0, "Unable to dynamic cast a storable to a marketlist.\n");
        return NULL;
    }

    return marketList;  // success.

    // This WAS a "load or create" sort of function, but I commented out the "create" part because
    // you will literally NEVER need to create this list.
    //
    //    else
    //    {
    //        OTAPI_Wrap::Output(0, "Didn't exist. Creating market list object...\n");
    //        storable := OTDB::CreateObject(STORED_OBJ_MARKET_LIST)
    //
    //        if (!VerifyStorable(storable))
    //        {
    //            OTAPI_Wrap::Output(0, "Failed trying to create market list object!\n");
    //            return storable  // containing null or undef
    //; }
    //
    //        OTAPI_Wrap::Output(0, "CreateObject worked. Now dynamic casting from storable to marketlist...\n");
    //        marketList := OTDB::CAST_MARKET_LIST(storable)
    //
    //        if (!VerifyStorable(marketList))
    //        {
    //            OTAPI_Wrap::Output(0, "Failed to dynamic cast from storable to marketlist.\n");
    //; }
    //; }
}


OT_COMMAND_OT int32_t main_show_market_list()
{
    if (VerifyExists("Server"))
    {
        OTDB::MarketList & marketList = *loadMarketList(Server);

        if (!VerifyStorable(&marketList, "OTDB::MarketList"))
        {
            OTAPI_Wrap::Output(0, "Unable to load up marketlist from local storage.\n");
            return -1;
        }

        // LOOP THROUGH THE MARKETS AND PRINT THEM OUT.

        int32_t nCount = marketList.GetMarketDataCount();
        int32_t nTemp = nCount;  // this way, nTemp is initialized as a size_t.

        if (!VerifyIntVal(nCount))
        {
            OTAPI_Wrap::Output(0, "Loaded the market list, but GetMarketDataCount returns an invalid result. (Failure.)\n");
        }
        else if (!(nCount > 0))
        {
            OTAPI_Wrap::Output(0, "Loaded the market list, but GetMarketDataCount says there aren't any markets in the list. (Returning.)\n");
        }
        else
        {
            //          print("\nIndex\tScale\tMarket\tAsset\tCurrency")
            OTAPI_Wrap::Output(0, "\nIndex\tScale\tMarket\t\t\t\t\t\tAsset\t\t\t\t\t\tCurrency\n");

            for (int32_t nIndex = 0; nIndex < nCount; ++nIndex)
            {
                OTDB::MarketData & marketData = *marketList.GetMarketData(nIndex);
                if (!VerifyStorable(&marketData, "OTDB::MarketData"))
                {
                    OTAPI_Wrap::Output(0, "Unable to reference marketData on marketList, at index: " + to_string(nIndex) + "\n");
                    return -1;
                }

                // OUTPUT THE MARKET DATA...
                //
                print(to_string(nIndex) + "\t" + marketData.scale + "\tM " + marketData.market_id + "\tA " + marketData.asset_type_id + "\tC " + marketData.currency_type_id);
            }
        }

        return 1;
    }

    return -1;
}


OT_COMMAND_OT int32_t main_get_market_list()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage = "\n\n USAGE: getmarketlist --server SERVER_ID --mynym YOUR_NYM_ID\n\n";

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {

        // Send the request.
        //
        string strResponse = madeEasy.get_market_list(Server, MyNym);
        string strAttempt = "get_market_list";

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:

        // ***************************************************************

        int32_t nInterpretReply = VerifyMessageSuccess(strResponse);

        if (1 == nInterpretReply)
        {
            OTAPI_Wrap::Output(0, "Server response (" + strAttempt + "): SUCCESS getting market list.\n\n");

            main_show_market_list(); // if it was successful, then we display the list on the screen.
        }

        return nInterpretReply;
    }

    return -1;
}


OT_COMMAND_OT OTDB::OfferListMarket * loadMarketOffers(const string & serverID, const string & marketID)
{
    OTDB::OfferListMarket * offerList = NULL;
    OTDB::Storable * storable = NULL;

    if (OTDB::Exists("markets", serverID, "offers", marketID + ".bin"))
    {
        OTAPI_Wrap::Output(1, "Offers file exists... Querying file for market offers...\n");
        storable = OTDB::QueryObject(OTDB::STORED_OBJ_OFFER_LIST_MARKET, "markets", serverID, "offers", marketID + ".bin");

        if (!VerifyStorable(storable, "OTDB::Storable"))
        {
            OTAPI_Wrap::Output(0, "Unable to verify storable object. Probably doesn't exist.\n");
            return NULL; // containing null or undef
        }

        OTAPI_Wrap::Output(1, "QueryObject worked. Now dynamic casting from storable to a (market) offerList...\n");
        offerList = dynamic_cast<OTDB::OfferListMarket *>(storable);

        if (!VerifyStorable(offerList, "OTDB::OfferListMarket"))
        {
            OTAPI_Wrap::Output(0, "Unable to dynamic cast a storable to a (market) offerList.\n");
            return NULL; // containing null or undef
        }
    }

    return offerList;  // possibly containing the offerList (if success), or possibly containing a null/undef value (if failure.)
}


OT_COMMAND_OT int32_t details_show_market_offers(const string & strServerID, const string & strMarketID)
{
    OTDB::OfferListMarket & offerList = *loadMarketOffers(strServerID, strMarketID);

    if (!VerifyStorable(&offerList, "OTDB::OfferListMarket"))
    {
        OTAPI_Wrap::Output(0, "Unable to load up a (market) offerList from local storage.\n");
        return -1;
    }

    // LOOP THROUGH THE BIDS AND PRINT THEM OUT.
    int32_t nBidCount = offerList.GetBidDataCount();  // size_t
    int32_t nTemp = nBidCount; // just so it's created as size_t

    if (VerifyIntVal(nBidCount) && (nBidCount > 0))
    {
        OTAPI_Wrap::Output(0, "\n** BIDS **\n\nIndex\tTrans#\tPrice\tAvailable\n");

        for (int32_t nIndex = 0; nIndex < nBidCount; ++nIndex)
        {
            OTDB::BidData & offerData = *offerList.GetBidData(nIndex);
            if (!VerifyStorable(&offerData, "OTDB::BidData"))
            {
                OTAPI_Wrap::Output(0, "Unable to reference bidData on offerList, at index: " + to_string(nIndex) + "\n");
                return -1;
            }

            // OUTPUT THE BID OFFER DATA...
            //
            print(to_string(nIndex) + "\t" + offerData.transaction_id + "\t" + offerData.price_per_scale + "\t" + offerData.available_assets);
        }
    }

    // LOOP THROUGH THE ASKS AND PRINT THEM OUT.
    int32_t nAskCount = offerList.GetAskDataCount();

    if (VerifyIntVal(nAskCount) && (nAskCount > 0))
    {
        OTAPI_Wrap::Output(0, "\n** ASKS **\n\nIndex\tTrans#\tPrice\tAvailable\n");

        for (int32_t nIndex = 0; nIndex < nAskCount; ++nIndex)
        {
            nTemp = nIndex;
            OTDB::AskData & offerData = *offerList.GetAskData(nTemp);

            if (!VerifyStorable(&offerData, "OTDB::AskData"))
            {
                OTAPI_Wrap::Output(0, "Unable to reference askData on offerList, at index: " + to_string(nIndex) + "\n");
                return -1;
            }

            // OUTPUT THE ASK OFFER DATA...
            //
            print(to_string(nIndex) + "\t" + offerData.transaction_id + "\t" + offerData.price_per_scale + "\t" + offerData.available_assets);
        }
    }

    return 1;
}


OT_COMMAND_OT int32_t impl_show_market_offers(string & strMarket)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage1 = "\n\n USAGE: showoffers --server SERVER_ID --mynym YOUR_NYM_ID\n";
    string strUsage = concat(strUsage1, "Also: --args \"market MARKET_ID\"\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server"))
    {

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (!VerifyStringVal(strMarket) && VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "market MARKET_ID"
            //
            string strNewMarket = OT_CLI_GetValueByKey(Args, "market"); // the market ID

            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewMarket))
            {
                strMarket = strNewMarket;
            }
        }

        // If the transfer parameters aren't provided, then we
        // ask the user to supply them at the command line.
        //
        if (!VerifyStringVal(strMarket))
        {
            main_show_market_list();

            OTAPI_Wrap::Output(0, "\nEnter the market ID: ");
            strMarket = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strMarket))
        {
            return -1;
        }


        return details_show_market_offers(Server, strMarket);
    }

    return -1;
}


OT_COMMAND_OT int32_t main_show_market_offers()
{
    string strMarket;

    return impl_show_market_offers(strMarket);
}


OT_COMMAND_OT int32_t main_get_market_offers()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage1 = "\n\n USAGE: getoffers --server SERVER_ID --mynym YOUR_NYM_ID\n";
    string strUsage = concat(strUsage1, "Also: --args \"market MARKET_ID depth MAX_DEPTH\"\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        string strMarket = ""; // must ultimately be an ID.
        string strDepth = ""; // can be blank

        string strDefaultDepth = "50"; // can be blank

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "market MARKET_ID depth 50"
            //
            string strNewMarket = OT_CLI_GetValueByKey(Args, "market"); // the market ID
            string strNewDepth = OT_CLI_GetValueByKey(Args, "depth");    // how many offers should we retrieve?


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewMarket))
            {
                strMarket = strNewMarket;
            }
            if (VerifyStringVal(strNewDepth))
            {
                strDepth = strNewDepth;
            }
        }

        // If the transfer parameters aren't provided, then we
        // ask the user to supply them at the command line.
        //
        if (!VerifyStringVal(strMarket))
        {
            main_show_market_list();

            OTAPI_Wrap::Output(0, "\nEnter the market ID: ");
            strMarket = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strDepth))
        {
            OTAPI_Wrap::Output(0, "Optionally, enter a max depth on a single line[" + strDepth + "]: ");
            strDepth = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strMarket))
        {
            return -1;
        }
        if (!VerifyStringVal(strDepth))
        {
            strDepth = strDefaultDepth;
        }

        // Send the request.
        //
        int64_t lDepth = to_long(strDepth);
        string strResponse = madeEasy.get_market_offers(Server, MyNym, strMarket, lDepth);
        string strAttempt = "get_market_offers";

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:

        // ***************************************************************

        int32_t nInterpretReply = VerifyMessageSuccess(strResponse);

        if (1 == nInterpretReply)
        {
            OTAPI_Wrap::Output(0, "Server response (" + strAttempt + "): SUCCESS getting market offers.\n\n");

            impl_show_market_offers(strMarket); // if it was successful, then we display the list on the screen.
        }

        return nInterpretReply;
    }

    return -1;
}


OT_COMMAND_OT int32_t main_adjust_usage_credits()
{
    //  def OT_ME::adjust_usage_credits(SERVER_ID, USER_NYM_ID, TARGET_NYM_ID, ADJUSTMENT)

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage1 = concat("\n\n  Options: --server SERVER_ID --mynym NYM_ID\n",
        "           --hisnym SUBJECT_NYM_ID\n\n");

    string strUsage = concat(strUsage1 + "To adjust (change) a Nym's usage credits: --args \"adjust POSITIVE_OR_NEGATIVE_VALUE\" \n (Used for giving or taking away usage credits.)\n",
        "For example, --args \"adjust 10000\"   or:  --args \"adjust -100\" \n\nFYI, this command also retrieves the current usage credits,\nand any Nym can use it on himself, read-only.\n\n");

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("HisNym"))
    {
        string strAdjustment = "0";

        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "adjust 1"
            //
            string strNewAdjust = OT_CLI_GetValueByKey(Args, "adjust"); // any positive or negative integer value, or zero.


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewAdjust))
            {
                strAdjustment = strNewAdjust;
            }
        }

        string strResponse = madeEasy.adjust_usage_credits(Server, MyNym, HisNym, strAdjustment);
        int32_t nStatus = VerifyMessageSuccess(strResponse);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:
        //
        // -1 is error,
        //  0 is reply received: failure
        //  1 is reply received: success
        //
        switch (nStatus)
        {
        case 1:
        {
                  OTAPI_Wrap::Output(0, "\n\n Server response:\n\n");
                  print(strResponse); // stdout

                  // IF THE_MESSAGE is of command type @usageCredits, and IF it was a SUCCESS,
                  // then this function returns the usage credits BALANCE (it's a long int, but
                  // passed as a string). If you adjusted the balance using the usageCredits
                  // command (THE_MESSAGE being the server's reply to that) then you will see
                  // the balance AFTER the adjustment. (The current "Usage Credits" balance.)
                  //
                  int64_t lNewUsageBalance = OTAPI_Wrap::Message_GetUsageCredits(strResponse);
                  string strNewUsageBalance = VerifyIntVal(lNewUsageBalance) ? to_string(lNewUsageBalance) : "";

                  if (!VerifyStringVal(strNewUsageBalance))
                  {
                      strNewUsageBalance = "(Error while calling API to retrieve usage credits from server reply.)";
                  }
                  else if (int64_t(-2) == lNewUsageBalance)
                  {
                      strNewUsageBalance = "Error code -2, while attempting to retrieve usage credits from this server reply.";
                  }
                  else if (int64_t(-1) == lNewUsageBalance)
                  {
                      strNewUsageBalance = concat("Either Nym has unlimited usage credits, or server has its usage credit enforcement turned off.\n",
                          "(Either way, Nym is good to go, since -1 was returned as his 'credits balance'.)");
                  }
                  else if (int64_t(0) == lNewUsageBalance)
                  {
                      strNewUsageBalance = concat("Nym appears to have exhausted his supply of usage credits.\n",
                          "(0 was returned as his 'credits balance'.)");
                  }
                  else
                  {
                      strNewUsageBalance = concat("Nym currently has " + to_string(lNewUsageBalance), " usage credits.");
                  }

                  string strOutput = concat("\n\n adjust_usage_credits -- reply: " + strNewUsageBalance,
                      "\n\n(FYI, this server message is the only and proper way to query for your own current usage credits balance, or also to set someone else's.)\n\n");
                  OTAPI_Wrap::Output(0, strOutput);

                  break;
        }
        case 0:
            OTAPI_Wrap::Output(0, "\n\nServer response:\n\n");
            print(strResponse); // stdout
            OTAPI_Wrap::Output(0, "\n\n FAILURE in adjust_usage_credits!\n\n");
            break;
        default:
            if (VerifyStringVal(strResponse))
            {
                OTAPI_Wrap::Output(0, "Server response:\n\n");
                print(strResponse); // stdout
            }
            OTAPI_Wrap::Output(0, "\n\nError in adjust_usage_credits! nStatus is: " + to_string(nStatus) + "\n");
            break;
        }

        OTAPI_Wrap::Output(0, "\n\n"); //stderr

        return (0 == nStatus) ? -1 : nStatus;
    }

    return -1;
}


/*
//      pScript->chai.add(fun(&OTDB::OfferDataNym::gui_label),          "gui_label");
pScript->chai.add(fun(&OTDB::OfferDataNym::valid_from),         "valid_from");
pScript->chai.add(fun(&OTDB::OfferDataNym::valid_to),           "valid_to");
pScript->chai.add(fun(&OTDB::OfferDataNym::server_id),          "server_id");
pScript->chai.add(fun(&OTDB::OfferDataNym::asset_type_id),      "asset_type_id");
pScript->chai.add(fun(&OTDB::OfferDataNym::asset_acct_id),      "asset_acct_id");
pScript->chai.add(fun(&OTDB::OfferDataNym::currency_type_id),   "currency_type_id");
pScript->chai.add(fun(&OTDB::OfferDataNym::currency_acct_id),   "currency_acct_id");
pScript->chai.add(fun(&OTDB::OfferDataNym::selling),            "selling");
pScript->chai.add(fun(&OTDB::OfferDataNym::scale),              "scale");
pScript->chai.add(fun(&OTDB::OfferDataNym::price_per_scale),    "price_per_scale");
pScript->chai.add(fun(&OTDB::OfferDataNym::transaction_id),     "transaction_id");
pScript->chai.add(fun(&OTDB::OfferDataNym::total_assets),       "total_assets");
pScript->chai.add(fun(&OTDB::OfferDataNym::finished_so_far),    "finished_so_far");
pScript->chai.add(fun(&OTDB::OfferDataNym::minimum_increment),  "minimum_increment");
pScript->chai.add(fun(&OTDB::OfferDataNym::stop_sign),          "stop_sign");
pScript->chai.add(fun(&OTDB::OfferDataNym::stop_price),         "stop_price");

OT_CHAI_CONTAINER(OfferListNym, OfferDataNym);
*/


OT_COMMAND_OT int32_t details_show_nym_offers(const string & strServerID, const string & strNymID)
{
    string strLocation = "details_show_nym_offers";

    OTDB::OfferListNym & offerList = *loadNymOffers(strServerID, strNymID);

    if (!VerifyStorable(&offerList, "OTDB::OfferListNym"))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Unable to load up a (nym) offerList from local storage. Probably doesn't exist.\n");
        return -1;
    }

    // LOOP THROUGH THE OFFERS and sort them into a map_of_maps, key is: scale-assetID-currencyID
    // the value for each key is a sub-map, with the key: transaction ID and value: the offer data itself.
    //
    int32_t nCount = offerList.GetOfferDataNymCount(); // size_t
    int32_t nTemp = nCount; // so it's created as size_t

    if (VerifyIntVal(nCount) && (nCount > 0))
    {
        MapOfMaps & map_of_maps = *convert_offerlist_to_maps(offerList);

        if (!VerifyType(&map_of_maps, "Map"))
        {
            OTAPI_Wrap::Output(0, strLocation + ": Unable to convert offer list to map of offers. Perhaps it's empty?\n");
            return -1;
        }

        // output_nymoffer_data is called for each offer, for this nym,
        // as it iterates through the maps.
        //
        // iterate_nymoffers_maps takes a final parameter extra_vals (not seen here)
        // Other sections in the code which use iterate_nymoffers_maps might pass a value
        // here, or expect one to be returned through the same mechansim.
        //
        int32_t nIterated = iterate_nymoffers_maps(map_of_maps, output_nymoffer_data); // low level. map_of_maps must be good. (assumed.)

        if (-1 == nIterated)
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error trying to iterate nym's offers.\n");
            return -1;
        }
    }

    return 1;
}


OT_COMMAND_OT int32_t main_show_nym_offers()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strUsage = "\n\n USAGE: showmyoffers --server SERVER_ID --mynym YOUR_NYM_ID\n\n";

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        return details_show_nym_offers(Server, MyNym);
    }

    return -1;
}


OT_COMMAND_OT string details_get_nym_market_offers(const string & strServerID, const string & strNymID)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strResponse;

    if (VerifyStringVal(strServerID) && VerifyStringVal(strNymID))
    {
        // Send the request.
        //
        strResponse = madeEasy.get_nym_market_offers(strServerID, strNymID);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:
    }

    return strResponse;
}


OT_COMMAND_OT int32_t main_get_nym_market_offers()
{

    string strUsage = "\n\n USAGE: getmyoffers --server SERVER_ID --mynym YOUR_NYM_ID\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {

        // Send the request.
        //
        string strResponse = details_get_nym_market_offers(Server, MyNym);
        string strAttempt = "get_nym_market_offers";

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:

        // ***************************************************************

        int32_t nInterpretReply = VerifyMessageSuccess(strResponse);

        if (1 == nInterpretReply)
        {
            OTAPI_Wrap::Output(0, "Server response (" + strAttempt + "): SUCCESS getting nym's market offers.\n\n");

            main_show_nym_offers(); // if it was successful, then we display the list on the screen.
        }

        return nInterpretReply;
    }

    return -1;
}


//
// PAY DIVIDEND
//
// Just like withdraw voucher...except instead of withdrawing a single voucher to yourself,
// it removes the total dividend payout from your account, and then divides it up amongst the
// shareholders, sending them EACH a voucher cheque in the amount of strAmount * number of shares owned.
//
OT_COMMAND_OT int32_t details_pay_dividend(const string & strAmount, const string & strMemo)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find Payer NymID based on myacct. Use: --myacct DIVIDEND_SOURCE_ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account (that the dividends will be paid out of) must be yours. OT will find the Nym based on that account.\n\n");
        return -1;
    }


    string strHisPurse;

    if (VerifyExists("HisPurse")) // This ID is already validated in the C++ code (in this case.)
    {
        strHisPurse = HisPurse;
    }
    else
    {
        while (true)
        {
            OTAPI_Wrap::Output(0, "Enter the SHARES asset type ID (Nym must also be the issuer for these shares): ");
            string strHisPartialPurseID = OT_CLI_ReadLine();

            if (VerifyStringVal(strHisPartialPurseID)) // If the user typed something...
            {
                strHisPurse = OTAPI_Wrap::Wallet_GetAssetIDFromPartial(strHisPartialPurseID); // Try to find the associated ID...

                if (!VerifyStringVal(strHisPurse)) // But if it returned NULL, failure (return.)
                {
                    OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find SHARES_ASSET_TYPE_ID in your wallet. Use: --hispurse SHARES_ASSET_TYPE_ID\n");
                    return -1;
                }
                break;
            }
        }
    }

    // ***************************************************************

    // HERE, WE SEND THE PAY DIVIDEND REQUEST TO THE SERVER
    //

    string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);

    int64_t lAmount = OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount);
    string strResponse = madeEasy.pay_dividend(Server, strMyNymID, MyAcct, strHisPurse, strMemo, lAmount);
    string strAttempt = "pay_dividend";

    //static int32_t payDividend(const std::string SERVER_ID,
    //                       const std::string ISSUER_USER_ID,
    //                       const std::string DIVIDEND_FROM_ACCT_ID,
    //                       const std::string SHARES_ASSET_TYPE_ID,
    //                       const std::string DIVIDEND_MEMO,
    //                       const std::string AMOUNT_PER_SHARE);
    // ***************************************************************

    // HERE, WE INTERPRET THE SERVER REPLY, WHETHER SUCCESS, FAIL, OR ERROR...

    int32_t nInterpretReply = InterpretTransactionMsgReply(Server, strMyNymID, MyAcct, strAttempt, strResponse);

    if (1 == nInterpretReply) // Success!
    {

        // Download all the intermediary files (account balance, inbox, outbox, etc)
        // since they have probably changed from this operation.
        //
        bool bRetrieved = madeEasy.retrieve_account(Server, strMyNymID, MyAcct, true); //bForceDownload defaults to false.
        OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");

        OTAPI_Wrap::Output(0, "\n\nServer response (" + strAttempt + "): SUCCESS paying out dividends.\n");
    }

    return nInterpretReply;
}


//static int32_t payDividend(const std::string SERVER_ID,
//                       const std::string ISSUER_USER_ID,
//                       const std::string DIVIDEND_FROM_ACCT_ID,
//                       const std::string SHARES_ASSET_TYPE_ID,
//                       const std::string DIVIDEND_MEMO,
//                       const std::string AMOUNT_PER_SHARE);

// HERE, WE GET ALL THE ARGUMENTS TOGETHER,
// and then call the above function.
//
OT_COMMAND_OT int32_t main_pay_dividend()
{
    string strUsage1 = concat("\n\n  USAGE: paydividend --server SERVER_ID --mynym SHARES_ISSUER_NYM_ID\n",
        "             --myacct DIVIDEND_SOURCE_ACCT_ID --hispurse SHARES_ASSET_TYPE_ID\n\n");

    string strUsage = concat(strUsage1 + "Also necessary: --args \"amount PAYOUT_AMOUNT_PER_SHARE\"\n",
        "And OPTIONALLY: --args \"memo \\\"Just a memo for the dividend payment.\\\"\"\n\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server") && VerifyExists("MyAcct"))
    {
        // strAmount and strNote...
        //
        string strAmount = "0"; // must ultimately be >= 1  (Payout per share.)
        string strNote = ""; // can be blank

        string strDefaultAmount = "1"; // must be >= 1
        string strDefaultNote = "(blank memo field)"; // can be blank

        // If custom arguments have been passed on the command line,
        // then grab them and use them instead of asking the user to enter them
        // at the command line.
        //
        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "amount 1"
            // EXAMPLE:  --args "amount 15 memo \"Just a memo for the dividend payout.\""
            //
            string strNewAmount = OT_CLI_GetValueByKey(Args, "amount"); // any integer value
            string strNewNote = OT_CLI_GetValueByKey(Args, "memo");     // optional memo field


            // Set the values based on the custom arguments, for those found.
            //
            if (VerifyStringVal(strNewAmount))
            {
                strAmount = strNewAmount;
            }
            if (VerifyStringVal(strNewNote))
            {
                strNote = strNewNote;
            }
        }


        string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(MyAcct);

        // If the transfer parameters aren't provided, then we
        // ask the user to supply them at the command line.
        //
        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
        {
            OTAPI_Wrap::Output(0, "Enter the 'Payout Amount Per-Share'[" + strDefaultAmount + "]: ");
            strAmount = OT_CLI_ReadLine();
        }
        if (!VerifyStringVal(strNote))
        {
            OTAPI_Wrap::Output(0, "Optionally, enter a memo on a single line[" + strDefaultNote + "]: ");
            strNote = OT_CLI_ReadLine();
        }

        if (!VerifyStringVal(strAmount) || (OTAPI_Wrap::StringToAmount(strAssetTypeID, strAmount) < 1))
        {
            strAmount = strDefaultAmount;
        }
        if (!VerifyStringVal(strNote))
        {
            strNote = strDefaultNote;
        }


        return details_pay_dividend(strAmount, strNote);
    }

    return -1;
}


OT_COMMAND_OT int32_t main_show_purse()
{
    string strUsage = "\n\n  USAGE: showpurse --mypurse ASSET_TYPE_ID --mynym YOUR_NYM_ID --server SERVER_ID \n\n";
    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("MyPurse"))
    {

        string strPurse = OTAPI_Wrap::LoadPurse(Server, MyPurse, MyNym); // returns NULL, or a purse.

        if (!VerifyStringVal(strPurse))
        {
            OTAPI_Wrap::Output(0, "\n main_show_purse: Unable to load purse. Does it even exist?\n");
        }
        else
        {
            int64_t lAmount = OTAPI_Wrap::Purse_GetTotalValue(Server, MyPurse, strPurse);

            print("\n\nTOTAL VALUE: " + OTAPI_Wrap::FormatAmount(MyPurse, lAmount));


            // Loop through purse contents and display tokens.
            int32_t nCount = OTAPI_Wrap::Purse_Count(Server, MyPurse, strPurse);

            if (!VerifyIntVal(nCount) || (nCount < 0))
            {
                OTAPI_Wrap::Output(0, "\n main_show_purse: Error: Unexpected bad value returned from OT_API_Purse_Count.\n\n");
                return -1;
            }


            if (nCount > 0)
            {
                print("Token count: " + to_string(nCount) + "\n");
                print("Index\tValue\tSeries\tValidFrom\tValidTo\t\tStatus");

                int32_t nIndex = -1;

                while (nCount > 0)
                {
                    --nCount;
                    ++nIndex;  // on first iteration, this is now 0.

                    string strToken = OTAPI_Wrap::Purse_Peek(Server, MyPurse, MyNym, strPurse);

                    if (!VerifyStringVal(strToken))
                    {
                        OTAPI_Wrap::Output(0, "main_show_purse: Error: OT_API_Purse_Peek unexpectedly returned NULL instead of token.\n");
                        return -1;
                    }


                    string strNewPurse = OTAPI_Wrap::Purse_Pop(Server, MyPurse, MyNym, strPurse);

                    if (!VerifyStringVal(strNewPurse))
                    {
                        OTAPI_Wrap::Output(0, "main_show_purse: Error: OT_API_Purse_Pop unexpectedly returned NULL instead of updated purse.\n");
                        return -1;
                    }

                    strPurse = strNewPurse;

                    int64_t lDenomination = OTAPI_Wrap::Token_GetDenomination(Server, MyPurse, strToken);
                    int32_t nSeries = OTAPI_Wrap::Token_GetSeries(Server, MyPurse, strToken);
                    time_t tValidFrom = OTAPI_Wrap::Token_GetValidFrom(Server, MyPurse, strToken);
                    time_t tValidTo = OTAPI_Wrap::Token_GetValidTo(Server, MyPurse, strToken);
                    time_t lTime = OTAPI_Wrap::GetTime();

                    if (0 > lDenomination)
                    {
                        OTAPI_Wrap::Output(0, "Error while showing purse: bad lDenomination.\n");
                        return -1;
                    }
                    if (!VerifyIntVal(nSeries))
                    {
                        OTAPI_Wrap::Output(0, "Error while showing purse: bad nSeries.\n");
                        return -1;
                    }
                    if (!VerifyIntVal(tValidFrom))
                    {
                        OTAPI_Wrap::Output(0, "Error while showing purse: bad tValidFrom.\n");
                        return -1;
                    }
                    if (!VerifyIntVal(tValidTo))
                    {
                        OTAPI_Wrap::Output(0, "Error while showing purse: bad tValidTo.\n");
                        return -1;
                    }
                    if (0 > lTime)
                    {
                        OTAPI_Wrap::Output(0, "Error while showing purse: bad strTime.\n");
                        return -1;
                    }

                    // Output the token...

                    string strStatus = (lTime > tValidTo) ? "expired" : "valid";

                    print(to_string(nIndex) + "\t" + to_string(lDenomination) + "\t" + to_string(nSeries) + "\t" + to_string(tValidFrom) + "\t" + to_string(tValidTo) + "\t" + strStatus);

                } // while
            } // if nCount > 0

            return 1;

        } // valid purse string was loaded.

    }

    return -1;
}


//
//
// THESE FUNCTIONS were added for the PAYMENTS screen. (They are fairly new.)
//
// Basically there was a need to have DIFFERENT instruments, but to be able to
// treat them as though they are a single type.
//
// In keeping with that, the below functions will work with disparate types.
// You can pass [ CHEQUES / VOUCHERS / INVOICES ] and PAYMENT PLANS, and
// SMART CONTRACTS, and PURSEs into these functions, and they should be able
// to handle any of those types.
//
//
//const char * OTAPI_Wrap::Instrmnt_GetAmount(const char * SERVER_ID, const char * THE_INSTRUMENT);
//const char * OTAPI_Wrap::Instrmnt_GetTransNum(const char * SERVER_ID, const char * THE_INSTRUMENT);
//
//const char * OTAPI_Wrap::Instrmnt_GetValidFrom(const char * SERVER_ID, const char * THE_INSTRUMENT);
//const char * OTAPI_Wrap::Instrmnt_GetValidTo(const char * SERVER_ID, const char * THE_INSTRUMENT);
//
//const char * OTAPI_Wrap::Instrmnt_GetMemo(const char * SERVER_ID, const char * THE_INSTRUMENT);
//
//const char * OTAPI_Wrap::Instrmnt_GetAssetID(const char * SERVER_ID, const char * THE_INSTRUMENT);
//
//const char * OTAPI_Wrap::Instrmnt_GetSenderUserID(const char * SERVER_ID, const char * THE_INSTRUMENT);
//const char * OTAPI_Wrap::Instrmnt_GetSenderAcctID(const char * SERVER_ID, const char * THE_INSTRUMENT);
//const char * OTAPI_Wrap::Instrmnt_GetRecipientUserID(const char * SERVER_ID, const char * THE_INSTRUMENT);
//const char * OTAPI_Wrap::Instrmnt_GetRecipientAcctID(const char * SERVER_ID, const char * THE_INSTRUMENT);
//

OT_COMMAND_OT int32_t details_deposit_cheque(const string & strServerID, const string & strMyAcct, const string & strMyNymID, const string & strInstrument, const string & strType)
{
    string strAssetTypeID = OTAPI_Wrap::Instrmnt_GetAssetID(strInstrument);

    if (!VerifyStringVal(strAssetTypeID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find Asset Type ID on the instrument.\n\n");
        return -1;
    }

    string strAssetTypeAcct = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strMyAcct);

    if (strAssetTypeID != strAssetTypeAcct)
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Asset Type ID on the instrument ( " + strAssetTypeID + " ) doesn't match the one on the MyAcct ( " + strAssetTypeAcct + " )\n\n");
        return -1;
    }

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // ***************************************************************

    // HERE, WE SEND THE DEPOSIT CHEQUE REQUEST TO THE SERVER
    //
    string strResponse = madeEasy.deposit_cheque(strServerID, strMyNymID, strMyAcct, strInstrument);
    string strAttempt = "deposit_cheque";

    // ***************************************************************

    // HERE, WE INTERPRET THE SERVER REPLY, WHETHER SUCCESS, FAIL, OR ERROR...

    int32_t nInterpretReply = InterpretTransactionMsgReply(strServerID, strMyNymID, strMyAcct, strAttempt, strResponse);

    if (1 == nInterpretReply)
    {
        // Download all the intermediary files (account balance, inbox, outbox, etc)
        // since they have probably changed from this operation.
        //
        bool bRetrieved = madeEasy.retrieve_account(strServerID, strMyNymID, strMyAcct, true); //bForceDownload defaults to false.

        OTAPI_Wrap::Output(0, "Server response (" + strAttempt + "): SUCCESS!\n");
        OTAPI_Wrap::Output(0, string(bRetrieved ? "Success" : "Failed") + " retrieving intermediary files for account.\n");
    }

    // ***************************************************************
    //
    // Return status to caller.
    //
    return nInterpretReply;


}


OT_COMMAND_OT int32_t details_deposit_purse(const string & strServerID, const string & strMyAcct, const string & strFromNymID, const string & strInstrument, const string & strIndices)
{
    string strTHE_Instrument = "";

    if (VerifyStringVal(strInstrument))
    {
        strTHE_Instrument = strInstrument;
    }

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;
    string strLocation = "details_deposit_purse";

    // HERE, WE LOOK UP THE asset type ID, BASED ON THE ACCOUNT ID.
    //
    string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strMyAcct);

    if (!VerifyStringVal(strAssetTypeID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find Asset Type ID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the asset type based on the account.\n\n");
        return -1;
    }

    if (VerifyExists("MyPurse", false) && (MyPurse != strAssetTypeID))
    {
        OTAPI_Wrap::Output(0, "Warning: Depositing to MyAcct, which is NOT the same asset type as the MyPurse asset type specified.\n");
    }


    bool bLoadedPurse = false;

    // If strInstrument wasn't passed, that means we're supposed to load
    // the purse ourselves, from local storage.
    //
    if (!VerifyStringVal(strTHE_Instrument))
    {
        // LOAD PURSE

        strTHE_Instrument = OTAPI_Wrap::LoadPurse(strServerID, strAssetTypeID, strFromNymID); // returns NULL, or a purse.

        if (!VerifyStringVal(strTHE_Instrument))
        {
            OTAPI_Wrap::Output(0, "\n " + strLocation + ": Unable to load purse from local storage. Does it even exist?\n");
            return -1;
        }

        bLoadedPurse = true;
    }

    // Below this point, we know that strTHE_Instrument contains either the purse as it was passed in
    // to us, or it contains the purse as we loaded it from local storage.
    // If it WAS from local storage, then there's a chance that strIndices contains "all" or "4, 6, 2" etc.
    // If that's the case, then we need to iterate through the purse, and add the denoted token IDs to
    // a vector (selectedTokens) and pass it into depositCashPurse.
    //


    vector<string> vecSelectedTokenIDs;

    // If we loaded the purse (vs the user pasting one in...)
    // then the user might have wanted to deposit only selected indices,
    // rather than ALL the tokens in that purse.
    // So we'll loop through the purse and add any relevant IDs to the
    // "selected" list, since the actual Token IDs must be passed.
    //
    if (bLoadedPurse)
    {

        // Loop through purse contents...
        //
        int32_t nCount = OTAPI_Wrap::Purse_Count(strServerID, strAssetTypeID, strTHE_Instrument);

        if (!VerifyIntVal(nCount) || (nCount < 0))
        {
            OTAPI_Wrap::Output(0, "\n " + strLocation + ": Error: Unexpected bad value returned from OT_API_Purse_Count.\n\n");
            return -1;
        }

        if (nCount < 1)
        {
            OTAPI_Wrap::Output(0, "\n " + strLocation + ": The purse is empty, so you can't deposit it.\n\n");
            return -1;
        }

        else //nCount >= 1
        {
            // Make a copy of the purse passed in, so we can iterate it and find the
            // appropriate Token IDs...

            string strPurse = strTHE_Instrument;

            if (VerifyStringVal(strIndices))
            {
                int32_t nIndex = -1;

                while (nCount > 0)
                {
                    --nCount;
                    ++nIndex;  // on first iteration, this is now 0.

                    //                  string strOwner = bPasswordProtected ? "" : strFromNymID

                    // NOTE: Owner can ONLY be strFromNymID in here, since bLoadedPurse
                    // is only true in the case where we LOADED the purse from local storage.
                    // (Therefore this DEFINITELY is not a password-protected purse.)
                    //
                    string strToken = OTAPI_Wrap::Purse_Peek(strServerID, strAssetTypeID,
                        strFromNymID,
                        strPurse);

                    if (!VerifyStringVal(strToken))
                    {
                        OTAPI_Wrap::Output(0, strLocation + ": Error: OT_API_Purse_Peek unexpectedly returned NULL instead of token.\n");
                        return -1;
                    }

                    string strNewPurse = OTAPI_Wrap::Purse_Pop(strServerID, strAssetTypeID,
                        strFromNymID,
                        strPurse);

                    if (!VerifyStringVal(strNewPurse))
                    {
                        OTAPI_Wrap::Output(0, strLocation + ": Error: OT_API_Purse_Pop unexpectedly returned NULL instead of updated purse.\n");
                        return -1;
                    }

                    strPurse = strNewPurse;

                    string strTokenID = OTAPI_Wrap::Token_GetID(strServerID, strAssetTypeID, strToken);

                    if (!VerifyStringVal(strTokenID))
                    {
                        OTAPI_Wrap::Output(0, strLocation + ": Error while depositing purse: bad strTokenID.\n");
                        return -1;
                    }

                    if (!("all" == strIndices) && OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex))) // empty vector should be interpreted already as "all"
                    {
                        vecSelectedTokenIDs.push_back(strTokenID);
                    }

                } // while
            } // if strIndices
        } // if nCount > 0
    }// if (bLoadedPurse)


    int32_t nResult = depositCashPurse(strServerID, strAssetTypeID, strFromNymID, strTHE_Instrument, vecSelectedTokenIDs, strMyAcct, bLoadedPurse);

    return nResult;

}


//case (this.DEPOSIT_CASH)
//{ nRetVal = OTAPI_Wrap::notarizeDeposit(this.serverID, this.nymID, this.accountID, this.strData);  break; }
//case (this.DEPOSIT_CHEQUE)
//{ nRetVal = OTAPI_Wrap::depositCheque(this.serverID, this.nymID, this.accountID, this.strData);  break; }
//case (this.DEPOSIT_PAYMENT_PLAN)
//{ nRetVal = OTAPI_Wrap::depositPaymentPlan(this.serverID, this.nymID, this.strData);  break; }


OT_COMMAND_OT int32_t details_deposit(const string & strServerID, const string & strMyAcctID)
{
    string strInstrument = "";


    // HERE, WE LOOK UP THE recipient NYM ID, BASED ON THE ACCOUNT ID.
    //
    string strToNymID = OTAPI_Wrap::GetAccountWallet_NymID(strMyAcctID);

    if (!VerifyStringVal(strToNymID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to find depositor NymID based on account ( " + strMyAcctID + " ).\nUse: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
        return -1;
    }

    //
    string strIndices = "";

    if (VerifyExists("Args", false))
    {
        // You have the OPTION to pass in indices for tokens in your purse, and deposit
        // will automatically assume "deposit cash" and deposit those tokens.
        // You can also specify to deposit ALL tokens in your cash purse.
        // Without this extra argument, OT will ask you to paste an instrument,
        // and then will dynamically determine its contract type.
        //

        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "indices 4,6,9"
        // EXAMPLE:  --args "indices all"
        //
        strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.
    }

    //
    if (VerifyStringVal(strIndices)) // He wants to deposit some or all of his local purse.
    {
        // Only in the case of cash, it's possible you have some cash in Nym A's purse, but
        // you want to deposit it into Nym B's account. So we have a "to" Nym and a "from" Nym
        // even though they will often be the same.
        //
        string strFromNymID = "";

        if (VerifyExists("MyNym", false))
        {
            strFromNymID = MyNym;
        }
        else
        {
            strFromNymID = strToNymID;
        }

        // In this case, strInstrument is blank.
        // That's how the callee knows that we're working with the local purse.
        // Then strIndices tells him either to use "all" tokens in that purse, or
        // the selected indices.
        //
        return details_deposit_purse(strServerID, strMyAcctID, strFromNymID, strInstrument, strIndices);
    }

    else // he wants to paste an instrument.
    {
        //
        OTAPI_Wrap::Output(0, "You can deposit a PURSE (containing cash tokens) or a CHEQUE / VOUCHER. \n");
        OTAPI_Wrap::Output(0, "Paste your financial instrument here, followed by a ~ by itself on a blank line: \n");

        strInstrument = OT_CLI_ReadUntilEOF();

        if (!VerifyStringVal(strInstrument))
        {
            return -1;
        }


        //      const char * OTPayment::_TypeStrings[] =
        //      {
        //          // ------------------
        //          // OTCheque is derived from OTTrackable, which is derived from OTInstrument, which is
        //          // derived from OTScriptable, which is derived from OTContract.
        //          // ------------------
        //          "CHEQUE",         // A cheque drawn on a user's account.
        //          "VOUCHER",        // A cheque drawn on a server account (cashier's cheque aka banker's cheque)
        //          "INVOICE",        // A cheque with a negative amount. (Depositing this causes a payment out, instead of a deposit in.)
        //          // ------------------
        //          "PAYMENT_PLAN",   // An OTCronItem-derived OTPaymentPlan, related to a recurring payment plan.
        //          "SMART_CONTRACT", // An OTCronItem-derived OTSmartContract, related to a smart contract.
        //          // ------------------
        //          "PURSE",          // An OTContract-derived OTPurse containing a list of cash OTTokens.
        //          // ------------------
        //          "ERROR_STATE"
        //; };


        string strType = OTAPI_Wrap::Instrmnt_GetType(strInstrument);

        if (!VerifyStringVal(strType))
        {
            OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine instrument type. Expected CHEQUE, VOUCHER, INVOICE, or (cash) PURSE.\n");
            return -1;
        }


        if ("CHEQUE" == strType)
        {
            return details_deposit_cheque(strServerID, strMyAcctID, strToNymID, strInstrument, strType);
        }
        else if ("VOUCHER" == strType)
        {
            return details_deposit_cheque(strServerID, strMyAcctID, strToNymID, strInstrument, strType);
        }
        else if ("INVOICE" == strType)
        {
            return details_deposit_cheque(strServerID, strMyAcctID, strToNymID, strInstrument, strType);
        }
        else if ("PURSE" == strType)
        {
            return details_deposit_purse(strServerID, strMyAcctID, strToNymID, strInstrument, ""); // strIndices is left blank in this case
        }
        else
        {
            OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine instrument type. Expected CHEQUE, VOUCHER, INVOICE, or (cash) PURSE.\n");
            return -1;
        }
    }

    return -1;
}


OT_COMMAND_OT int32_t main_deposit()
{
    string strUsage1 = "\n\n  USAGE: deposit --myacct YOUR_ACCT_ID  \n(OT will ask you to paste the instrument.)\n";
    string strUsage2 = concat(strUsage1, "Optionally:    --mynym YOUR_NYM_ID \n");
    string strUsage3 = concat(strUsage2, "Optionally:    --args \"indices 4,6,9\"\n");
    string strUsage4 = concat(strUsage3, "Optionally:    --args \"indices all\"  (To deposit ALL cash tokens in your purse.)\n");
    string strUsage = concat(strUsage4, "Server and NymID are usually determined based on MyAcct.\n If you supply optional indices, they must correspond to tokens in your cash purse.\n\n");

    OTAPI_Wrap::Output(0, strUsage);


    // A bit complicated:
    //
    // If I specify MyPurse and MyAcct, then they MUST have the same asset type.
    //
    // If I specify MyNym and MyPurse, that is where we will look for the purse.
    //
    // If I specify MyAcct, and it's owned by a different Nym than MyNym, then the cash
    // tokens will be reassigned from MyNym to MyAcct's Nym, before depositing.
    // Basically ALWAYS look up MyAcct's owner, and set HIM as the recipient Nym.
    // (But still use MyNym, independently, to find the purse being deposited.)
    //
    // Must ALWAYS specify MyAcct because otherwise, where are you depositing to?
    //
    // If MyNym isn't available, should use MyAcct's Nym.
    //
    // Shouldn't need to specify MyPurse, since we can ONLY deposit into MyAcct of
    // the same type as MyAcct. Thus we should ignore any other asset types or purses
    // since they couldn't possibly be deposited into MyAcct anyway.
    //

    if (VerifyExists("MyAcct"))
    {

        // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
        //
        string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);

        if (!VerifyStringVal(strServerID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find Server ID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Server based on the account.\n\n");
            return -1;
        }

        if (VerifyExists("Server", false) && !(Server == strServerID))
        {
            OTAPI_Wrap::Output(0, "This account is on server ( " + strServerID + " -- the server is deduced based on the account), but the default server is ( " + Server + " ). To override it, use:  --server " + strServerID + " \n");
            return -1;
        }

        return details_deposit(strServerID, MyAcct);
    }

    return -1;
}


/*

const char * OTAPI_Wrap::Instrmnt_GetAmount(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetTransNum(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetValidFrom(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetValidTo(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetMemo(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetType(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetServerID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetAssetID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetSenderUserID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetSenderAcctID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetRecipientUserID(const char * THE_INSTRUMENT);
const char * OTAPI_Wrap::Instrmnt_GetRecipientAcctID(const char * THE_INSTRUMENT);


pScript->chai.add(fun(&OTAPI_Wrap::CreatePurse), "OT_API_CreatePurse");
pScript->chai.add(fun(&OTAPI_Wrap::CreatePurse_Passphrase), "OT_API_CreatePurse_Passphrase");
pScript->chai.add(fun(&OTAPI_Wrap::SavePurse), "OT_API_SavePurse");
pScript->chai.add(fun(&OTAPI_Wrap::Purse_GetTotalValue), "OT_API_Purse_GetTotalValue");
pScript->chai.add(fun(&OTAPI_Wrap::Purse_Count), "OT_API_Purse_Count");
pScript->chai.add(fun(&OTAPI_Wrap::Purse_Peek), "OT_API_Purse_Peek");
pScript->chai.add(fun(&OTAPI_Wrap::Purse_Pop), "OT_API_Purse_Pop");
pScript->chai.add(fun(&OTAPI_Wrap::Purse_Push), "OT_API_Purse_Push");
pScript->chai.add(fun(&OTAPI_Wrap::Wallet_ImportPurse), "OT_API_Wallet_ImportPurse");
pScript->chai.add(fun(&OTAPI_Wrap::exchangePurse), "OT_API_exchangePurse");
pScript->chai.add(fun(&OTAPI_Wrap::Token_ChangeOwner), "OT_API_Token_ChangeOwner");
pScript->chai.add(fun(&OTAPI_Wrap::Purse_HasPassword), "OT_API_Purse_HasPassword");

*/


OT_COMMAND_OT int32_t details_import_purse(const string & strInstrument, const bool bHasPassword, const string & strPurseOwner)
{
    if (!VerifyStringVal(strInstrument))
    {
        return -1;
    }

    string strServerID = OTAPI_Wrap::Instrmnt_GetServerID(strInstrument);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine server ID from purse.\n");
        return -1;
    }

    string strAssetID = OTAPI_Wrap::Instrmnt_GetAssetID(strInstrument);

    if (!VerifyStringVal(strAssetID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine asset type ID from purse.\n");
        return -1;
    }

    bool bActuallyHasPassword = OTAPI_Wrap::Purse_HasPassword(strServerID, strInstrument);

    if (bHasPassword != bActuallyHasPassword)
    {
        OTAPI_Wrap::Output(0, "The actual purse's opinion of whether or not it has a password, doesn't match the caller's opinion.\n");
        return -1;
    }

    bool bImported = OTAPI_Wrap::Wallet_ImportPurse(strServerID, strAssetID, strPurseOwner, strInstrument);

    if (bImported)
    {
        OTAPI_Wrap::Output(0, "\n\n Success importing purse!\nServer: " + strServerID + "\nAsset Type: " + strAssetID + "\nNym: " + strPurseOwner + "\n\n");
        return 1;
    }

    return -1;
}


OT_COMMAND_OT int32_t details_import_cash(const string & strInstrument)
{
    if (!VerifyStringVal(strInstrument))
    {
        return -1;
    }

    string strType = OTAPI_Wrap::Instrmnt_GetType(strInstrument);

    if (!VerifyStringVal(strType))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine instrument type. Expected (cash) PURSE.\n");
        return -1;
    }

    string strServerID = OTAPI_Wrap::Instrmnt_GetServerID(strInstrument);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine server ID from purse.\n");
        return -1;
    }

    if ("PURSE" == strType)
    {
    }
    // Todo: case "TOKEN"
    //
    // NOTE: This is commented out because since it is guessing the NymID as MyNym,
    // then it will just create a purse for MyNym and import it into that purse, and
    // then later when doing a deposit, THAT's when it tries to DECRYPT that token
    // and re-encrypt it to the SERVER's nym... and that's when we might find out that
    // it never was encrypted to MyNym in the first place -- we had just assumed it
    // was here, when we did the import. Until I can look at that in more detail, it
    // will remain commented out.
    else
    {
        //            // This version supports cash tokens (instead of purse...)
        //            bool bImportedToken = importCashPurse(strServerID, MyNym, strAssetID, userInput, isPurse)
        //
        //            if (bImportedToken)
        //            {
        //                OTAPI_Wrap::Output(0, "\n\n Success importing cash token!\nServer: "+strServerID+"\nAsset Type: "+strAssetID+"\nNym: "+MyNym+"\n\n");
        //                return 1;
        //; }

        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine instrument type. Expected (cash) PURSE.\n");
        return -1;
    }

    // This tells us if the purse is password-protected. (Versus being owned
    // by a Nym.)
    bool bHasPassword = OTAPI_Wrap::Purse_HasPassword(strServerID, strInstrument);

    // Even if the Purse is owned by a Nym, that Nym's ID may not necessarily
    // be present on the purse itself (it's optional to list it there.)
    // OTAPI_Wrap::Instrmnt_GetRecipientUserID tells us WHAT the recipient User ID
    // is, IF it's on the purse. (But does NOT tell us WHETHER there is a
    // recipient. The above function is for that.)
    //
    string strPurseOwner = "";

    if (!bHasPassword)
    {
        strPurseOwner = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strInstrument); // TRY and get the Nym ID (it may have been left blank.)
    }

    // Whether the purse was password-protected (and thus had no Nym ID)
    // or whether it does have a Nym ID (but it wasn't listed on the purse)
    // Then either way, in those cases strPurseOwner will still be NULL.
    //
    // (The third case is that the purse is Nym protected and the ID WAS available,
    // in which case we'll skip this block, since we already have it.)
    //
    // But even in the case where there's no Nym at all (password protected)
    // we STILL need to pass a Signer Nym ID into OTAPI_Wrap::Wallet_ImportPurse.
    // So if it's still NULL here, then we use --mynym to make the call.
    // And also, even in the case where there IS a Nym but it's not listed,
    // we must assume the USER knows the appropriate NymID, even if it's not
    // listed on the purse itself. And in that case as well, the user can
    // simply specify the Nym using --mynym.
    //
    // Bottom line: by this point, if it's still not set, then we just use
    // MyNym, and if THAT's not set, then we return failure.
    //
    if (!VerifyStringVal(strPurseOwner))
    {
        OTAPI_Wrap::Output(0, "\n\n The NymID isn't evident from the purse itself... (listing it is optional.)\nThe purse may have no Nym at all--it may instead be password-protected.) Either way, a signer nym is still necessary, even for password-protected purses.\n\n Trying MyNym...\n");

        if (!VerifyExists("MyNym"))
        {
            return -1;
        }

        strPurseOwner = MyNym;
    }

    return details_import_purse(strInstrument, bHasPassword, strPurseOwner);
}


OT_COMMAND_OT int32_t main_import_cash()
{
    string strUsage1 = "\n\n  USAGE: importcash   (OT will ask you to paste the instrument.)\n";
    string strUsage2 = concat(strUsage1, "Optionally: importcash --mynym YOUR_NYM_ID\n\n");
    string strUsage3 = concat(strUsage2, "Asset (Purse) ID and ServerID are both deduced from the cash purse that you're importing.\n");
    string strUsage = concat(strUsage3, "NymID is also deduced, if necessary. (Otherwise, specify using --mynym.)\n\n");

    OTAPI_Wrap::Output(0, strUsage);

    OTAPI_Wrap::Output(0, "You can import a PURSE (containing cash tokens.)\n");
    OTAPI_Wrap::Output(0, "Paste your financial instrument here, followed by a ~ by itself on a blank line: \n");

    string strInstrument = OT_CLI_ReadUntilEOF();

    if (!VerifyStringVal(strInstrument))
    {
        return -1;
    }

    return details_import_cash(strInstrument);
}


// MyPurse and HisPurse will call the script even when not found, giving the script
// the opportunity to download the appropriate asset contract from the server, if
// necessary.
//
// Similarly, HisAcct works without being expected to be found in the wallet (since
// maybe it's HIS account and thus it's not IN your wallet...)
//
// Similarly, HisNym will call the script even when not found, giving the script the
// opportunity to download the appropriate pubkey ("check_user" aka "checknym") and
// continue operating.
//
// All of the above, plus Server, ALREADY attempt a partial match search. Therefore,
// it's not necessary to perform ANOTHER partial match, when the value comes from
// --server, --mynym, --hisnym, --mypurse, --hispurse, --myacct, or --hisacct.
//
// You only need to do partial matches when you get values from ELSEWHERE, such as
// from custom arguments, or user-pasted input.
//
// Therefore, add a function for downloading a Nym's pubkey if not already in the wallet,
// and one that downloads an asset contract if not already in the wallet


OT_COMMAND_OT string details_export_cash(const string & strServerID, const string & strFromNymID, const string & strAssetTypeID, string & strHisNymID, const string & strIndices, const bool bPasswordProtected, string & strRetainedCopy)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strLocation = "\n details_export_cash";

    // The first three arguments are for loading up the purse we're exporting FROM.
    //
    // Then strHisNymID is for the Nym we're exporting TO (if bPasswordProtected is false.)
    //
    // Then strIndices contains the indices for the tokens to export.
    //
    // Then bPasswordProtected tells us whether to export to strHisNymID,
    // or to create a password-protected purse and export to that instead.
    // (In which case, the purse itself becomes the "owner" and can be passed
    // wherever we would normally pass a NymID as a purse owner.)
    //
    // if bPasswordProtected is false, then strHisNymID needs to contain the recipient Nym.
    // This will contain MyNym by default, if --hisnym wasn't used at the command line.
    //

    string strContract = madeEasy.load_or_retrieve_contract(strServerID, strFromNymID, strAssetTypeID);

    if (!VerifyStringVal(strContract))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Unable to load asset contract: " + strAssetTypeID + "\n");
        return "";
    }

    bool bLoadedPurse = false;

    string strInstrument = OTAPI_Wrap::LoadPurse(strServerID, strAssetTypeID, strFromNymID); // returns NULL, or a purse.

    if (!VerifyStringVal(strInstrument))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Unable to load purse from local storage. Does it even exist?\n");
        return "";
    }

    bLoadedPurse = true;

    // Below this point, we know that strInstrument contains the purse as we loaded it from local storage.
    // If it WAS from local storage, then there's a chance that strIndices contains "4, 6, 2" etc.
    // If that's the case, then we need to iterate through the purse, and add the denoted token IDs to
    // a vector (selectedTokens) and pass it into exportCashPurse.


    vector<string> vecSelectedTokenIDs;

    // the user might have wanted to export only selected indices,
    // rather than ALL the tokens in the purse.
    // So we'll loop through the purse and add any relevant IDs to the
    // "selected" list, since the actual Token IDs must be passed.
    //
    if (bLoadedPurse)
    {

        // Loop through purse contents...
        //
        int32_t nCount = OTAPI_Wrap::Purse_Count(strServerID, strAssetTypeID, strInstrument);

        if (!VerifyIntVal(nCount) || (nCount < 0))
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error: Unexpected bad value returned from OT_API_Purse_Count.\n\n");
            return "";
        }

        if (nCount < 1)
        {
            OTAPI_Wrap::Output(0, strLocation + ": The purse is empty, so you can't export it.\n\n");
            return "";
        }

        else //nCount >= 1
        {
            // Make a COPY of the purse for this loop, so we can iterate it and find the
            // appropriate Token IDs...

            string strPurse = strInstrument;

            if (VerifyStringVal(strIndices)) // if strIndices is empty, then we send vecSelectedTokenIDs empty as well (which means, "do them all.")
            {
                int32_t nIndex = -1;

                while (nCount > 0)
                {
                    --nCount;
                    ++nIndex;  // on first iteration, this is now 0.

                    string strToken = OTAPI_Wrap::Purse_Peek(strServerID, strAssetTypeID, strFromNymID, strPurse);

                    if (!VerifyStringVal(strToken))
                    {
                        OTAPI_Wrap::Output(0, strLocation + ": Error: OT_API_Purse_Peek unexpectedly returned NULL instead of token.\n");
                        return "";
                    }

                    string strNewPurse = OTAPI_Wrap::Purse_Pop(strServerID, strAssetTypeID, strFromNymID, strPurse);

                    if (!VerifyStringVal(strNewPurse))
                    {
                        OTAPI_Wrap::Output(0, strLocation + ": Error: OT_API_Purse_Pop unexpectedly returned NULL instead of updated purse.\n");
                        return "";
                    }

                    strPurse = strNewPurse;

                    string strTokenID = OTAPI_Wrap::Token_GetID(strServerID, strAssetTypeID, strToken);

                    if (!VerifyStringVal(strTokenID))
                    {
                        OTAPI_Wrap::Output(0, strLocation + ": Error while exporting purse: bad strTokenID.\n");
                        return "";
                    }

                    //                  bool NumList_VerifyQuery(const std::string str_NumList, const std::string str_Numbers)

                    // If there are no indices, then do them all. (Thus push this one,
                    // as we push every one.)
                    // OR, If there are indices, and the current index is FOUND on the
                    // vector of indices, then we push this one (since it was selected.)
                    //
                    if (!("all" == strIndices) && OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex))) // empty vector should be interpreted already as "all"
                    {
                        vecSelectedTokenIDs.push_back(strTokenID);
                    }

                } // while
            } // if strIndices

            string strExportedCashPurse = exportCashPurse(strServerID, strAssetTypeID, strFromNymID, strInstrument, vecSelectedTokenIDs, strHisNymID, bPasswordProtected, strRetainedCopy);

            return strExportedCashPurse;

        } // if nCount > 0

    }// if (bLoadedPurse)

    return "";
}


OT_COMMAND_OT int32_t main_export_cash()
{
    string strUsage1 = "\n\n  USAGE: exportcash --mypurse ASSET_TYPE_ID --mynym YOUR_NYM_ID --hisnym RECIPIENT_NYM_ID --server SERVER_ID\n";
    string strUsage2 = concat(strUsage1, "Optionally:    --args \"indices 4,6,9\"\n");
    string strUsage3 = concat(strUsage2, "Optionally:    --args \"passwd true\"  (To create a password-protected purse.)\n\n");
    string strUsage4 = concat(strUsage3, "(If you create a password-protected purse, then HisNym will be ignored and can be left out.)\n");
    string strUsage = concat(strUsage4, "If you supply optional indices, they must correspond to tokens in your cash purse.\n\n");

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("MyPurse"))
    {
        string strIndices = "";
        bool bPasswordProtected = false;

        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            // EXAMPLE:  --args "indices \"all\" "
            //
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.

            string strPasswordProtected = OT_CLI_GetValueByKey(Args, "passwd");

            if (VerifyStringVal(strPasswordProtected) && ("true" == strPasswordProtected))
            {
                bPasswordProtected = true;
            }
        }

        string strHisNym = MyNym;  // default export is to your own Nym.

        if (!bPasswordProtected && VerifyExists("HisNym", false))
        {
            OTAPI_Wrap::Output(0, "HisNym was provided at the command line.\nDo you wish to export this cash to HisNym instead of MyNym?\n\n");
            OTAPI_Wrap::Output(0, "HisNym is: " + HisNym + "\n MyNym is: " + MyNym + "\n\n Type yes to use HisNym, or no to use MyNym.[no]: ");

            string strAnswer = OT_CLI_ReadLine();

            if (VerifyStringVal(strAnswer) && (("y" == strAnswer) || ("yes" == strAnswer)))
            {
                strHisNym = HisNym;
            }
        }

        string strServerID = Server;  // so it makes a copy. (Partial ID processing will alter the variable internally here, and that will fail with Server since it's a global constant.)
        string strMyNymID = MyNym;   // Same reason.
        string strMyPurse = MyPurse; // Same reason.
        string strRetainedCopy = ""; // A copy of the exported purse, except this copy is encrypted to the SENDER's key. (In case he needs to recover it from his outpayments.)

        string strExportedPurse = details_export_cash(strServerID, strMyNymID, strMyPurse, strHisNym, strIndices, bPasswordProtected, strRetainedCopy);

        if (VerifyStringVal(strExportedPurse))
        {
            print("\n" + strExportedPurse + "\n"); // stdout
            OTAPI_Wrap::Output(0, "Success exporting cash purse!\n\n"); // stderr
            return 1; // Success!
        }
    }

    return -1;
}


// Pass in the exact indices, or an amount, and this function will return true;
// or false.
//
// If you pass the indices, this function returns true if those exact indices
// exist. In that case, this function will also set lAmount to the total.
//
// If, instead, you pass lAmount and a blank indices, this function will try to
// determine the indices that would create lAmount, if they were selected. If it
// returns true, strIndices, will contain the result, at the end of it all.
//
OT_COMMAND_OT bool purse_get_indices_or_amount(const string & strServerID, const string & strAssetTypeID, const string & strMyNymID, int64_t & lAmount, string & strIndices) // If strIndices is input, lAmount is output. (And vice-versa.)
{

    string strLocation = "\n purse_get_indices_or_amount";

    string strLoopIndices = "";
    int64_t lLoopAmount = lAmount; // so they are the same data type.
    int64_t lAmountRemaining = lAmount; // so they are the same data type.
    lLoopAmount = 0; // to initialize it back to 0.

    // lLoopAmount is where we will start at 0, and keep the running total of the value for the selected indices, as we loop.
    // lAmountRemaining is where we will start at lAmount, and then SUBTRACT the value of each selected index, as we loop.
    // If we are trying to determine the indices based on lAmount, we'll SEE if the current index is less-than-or-equal-to
    // lAmountRemaining, and if so, we'll concat that index to our output and subtract the denomination of the token at the
    // current index from lAmountRemaining.
    // If bFindAmountFromIndices is true then lAmount is already 0 and then lAmountRemaining is already 0 as well.

    bool bFindIndicesFromAmount = false;
    bool bFindAmountFromIndices = false;

    if (VerifyStringVal(strIndices) && (0 == lAmount))
    {
        // all good.
        bFindAmountFromIndices = true;
    }
    else if (!VerifyStringVal(strIndices) && (0 != lAmount))
    {
        // all good.
        bFindIndicesFromAmount = true;
    }
    else
    {
        OTAPI_Wrap::Output(0, strLocation + ": Can only pass indices, OR amount to this function, but not both (the other becomes output.)\n");
        return false;
    }

    OTAPI_Wrap::Output(0, "strServerID: " + strServerID + "\n");
    OTAPI_Wrap::Output(0, "strAssetTypeID: " + strAssetTypeID + "\n");
    OTAPI_Wrap::Output(0, "strMyNymID: " + strMyNymID + "\n");

    string strLocalPurse = OTAPI_Wrap::LoadPurse(strServerID, strAssetTypeID, strMyNymID);

    bool bLoadedPurse = VerifyStringVal(strLocalPurse);
    if (!bLoadedPurse)
    {
        OTAPI_Wrap::Output(0, strLocation + ": Unable to load local purse. Does it even exist?\n");
        return false;
    }
    else
    {

        // Loop through purse contents...
        //
        int32_t nCount = OTAPI_Wrap::Purse_Count(strServerID, strAssetTypeID, strLocalPurse);

        if (!VerifyIntVal(nCount) || (nCount < 0))
        {
            OTAPI_Wrap::Output(0, strLocation + ": Error: Unexpected bad value returned from OT_API_Purse_Count.\n\n");
            return false;
        }

        if (nCount < 1)
        {
            OTAPI_Wrap::Output(0, strLocation + ": The purse is empty.\n\n");
            return false;
        }

        else //nCount >= 1
        {
            // Make a copy of the purse passed in, so we can iterate it and find the
            // appropriate Token IDs...

            string strPurse = strLocalPurse;

            int32_t nIndex = -1;

            while (nCount > 0)
            {
                --nCount;
                ++nIndex;  // on first iteration, this is now 0.


                //                  string strOwner = bPasswordProtected ? "" : strMyNymID

                // NOTE: Owner can ONLY be strMyNymID in here, since bLoadedPurse
                // is only true in the case where we LOADED the purse from local storage.
                // (Therefore this DEFINITELY is not a password-protected purse.)
                //
                string strToken = OTAPI_Wrap::Purse_Peek(strServerID, strAssetTypeID,
                    strMyNymID,
                    strPurse);

                if (!VerifyStringVal(strToken))
                {
                    OTAPI_Wrap::Output(0, strLocation + ": Error: OT_API_Purse_Peek unexpectedly returned NULL instead of token.\n");
                    return false;
                }

                string strNewPurse = OTAPI_Wrap::Purse_Pop(strServerID, strAssetTypeID,
                    strMyNymID,
                    strPurse);

                if (!VerifyStringVal(strNewPurse))
                {
                    OTAPI_Wrap::Output(0, strLocation + ": Error: OT_API_Purse_Pop unexpectedly returned NULL instead of updated purse.\n");
                    return false;
                }

                strPurse = strNewPurse;

                string strTokenID = OTAPI_Wrap::Token_GetID(strServerID, strAssetTypeID, strToken);
                if (!VerifyStringVal(strTokenID))
                {
                    OTAPI_Wrap::Output(0, strLocation + ": Error: bad strTokenID.\n");
                    return false;
                }
                int64_t lDenomination = OTAPI_Wrap::Token_GetDenomination(strServerID, strAssetTypeID, strToken);
                if (0 > lDenomination)
                {
                    OTAPI_Wrap::Output(0, "Error while showing purse: bad lDenomination.\n");
                    return false;
                }
                int32_t nSeries = OTAPI_Wrap::Token_GetSeries(strServerID, strAssetTypeID, strToken);
                if (!VerifyIntVal(nSeries))
                {
                    OTAPI_Wrap::Output(0, "Error while showing purse: bad nSeries.\n");
                    return false;
                }
                time_t tValidFrom = OTAPI_Wrap::Token_GetValidFrom(strServerID, strAssetTypeID, strToken);
                if (!VerifyIntVal(tValidFrom))
                {
                    OTAPI_Wrap::Output(0, "Error while showing purse: bad tValidFrom.\n");
                    return false;
                }
                time_t tValidTo = OTAPI_Wrap::Token_GetValidTo(strServerID, strAssetTypeID, strToken);
                if (!VerifyIntVal(tValidTo))
                {
                    OTAPI_Wrap::Output(0, "Error while showing purse: bad tValidTo.\n");
                    return false;
                }
                time_t lTime = OTAPI_Wrap::GetTime();
                if (0 > lTime)
                {
                    OTAPI_Wrap::Output(0, "Error while showing purse: bad lTime.\n");
                    return false;
                }
                string strStatus = (lTime > tValidTo) ? "expired" : "valid";

                // ------------------------------------------
                // lLoopAmount is where we will start at 0, and keep the running total of the value for the selected indices, as we loop.
                // lAmountRemaining is where we will start at lAmount, and then SUBTRACT the value of each selected index, as we loop.
                // If we are trying to determine the indices based on lAmount, we'll SEE if value at the current index is less-than-or-equal-to
                // lAmountRemaining, and if so, we'll concat that index to our output and subtract the denomination of the token at the
                // current index from lAmountRemaining.
                // If bFindAmountFromIndices is true then lAmount is already 0 and then lAmountRemaining is already 0 as well.

                // TODO:  This would work better if the tokens were sorted. In the future, pull the tokens onto a map or something,
                // and then SORT IT based on denomination of token. THEN go through the tokens from largest to smallest and do what we're
                // doing here in this loop. And then it will work perfectly everytime. Todo.  This version will work okay, but there will be
                // times it fails and ends up withdrawing cash when it didn't really need to. TOdo.

                if (lTime > tValidTo)
                {
                    OTAPI_Wrap::Output(0, strLocation + ": Skipping: Token is " + strStatus + ".\n");
                }

                else if (bFindAmountFromIndices)
                {
                    if (VerifyStringVal(strIndices) && (("all" == strIndices) || OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex))))
                    {
                        string strTempIndices = OTAPI_Wrap::NumList_Add(strLoopIndices, to_string(nIndex));
                        strLoopIndices = strTempIndices;
                        lLoopAmount += lDenomination;
                    }
                }
                else if (bFindIndicesFromAmount)
                {
                    if (VerifyIntVal(lAmount) && (lAmountRemaining > 0) && (lDenomination <= lAmountRemaining))
                    {
                        string strTempIndices = OTAPI_Wrap::NumList_Add(strLoopIndices, to_string(nIndex));
                        strLoopIndices = strTempIndices;
                        lLoopAmount += lDenomination;
                        lAmountRemaining -= lDenomination;

                        if (0 == lAmountRemaining)
                        {
                            break;
                        }
                    }
                }

            } // while
        } // if nCount > 0
    }// if (bLoadedPurse)

    if (bFindAmountFromIndices)
    {
        lAmount = lLoopAmount;
        return true;
    }
    else if (bFindIndicesFromAmount)
    {
        strIndices = strLoopIndices;
        lAmount = lAmountRemaining;  // So the caller, if this fails, sees how much he still needs to withdraw.

        if (0 == lAmountRemaining)
        {
            return true;
        }

        strIndices = ""; // Since we're about to return false, and since we were finding the indices, we set them back to "" again.
    }

    return false;
}


OT_COMMAND_OT bool withdraw_and_send_cash(const string & strMyAcctID, string & strHisNymID, const string & strMemo, const string & strAmount)
{
    string strLocation = "withdraw_and_send_cash";

    if (!VerifyStringVal(strMyAcctID) || !VerifyStringVal(strHisNymID) || !VerifyStringVal(strAmount))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Failure: Missing one of: strMyAcctID (" + strMyAcctID + "), strHisNymID (" + strHisNymID + "), or strAmount (" + strAmount + ")\n");
        return false;
    }

    // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(strMyAcctID);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Failure: Unable to find NymID based on strMyAcctID (" + strMyAcctID + ").\n");
        return false;
    }

    // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
    //
    string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strMyAcctID);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Failure: Unable to find Server ID based on strMyAcctID (" + strMyAcctID + ").\n");
        return false;
    }

    string strAssetTypeID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strMyAcctID);

    if (!VerifyStringVal(strAssetTypeID))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Failure: Unable to find Asset Type ID based on strMyAcctID (" + strMyAcctID + ").\n");
        return false;
    }

    int64_t lAmount = int64_t(0);

    if (VerifyStringVal(strAmount))
    {
        lAmount = to_long(strAmount);
    }

    if (!VerifyIntVal(lAmount) || (lAmount <= 0))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Invalid value: strAmount (" + strAmount + ")\n");
        return false;
    }

    string strTempMemo = "";
    string strResponse = "";
    string strIndices = "";
    bool bPasswordProtected = false;

    if (VerifyStringVal(strMemo))
    {
        strTempMemo = strMemo;
    }

    if (1 == details_send_cash(strResponse, strServerID, strAssetTypeID, strMyNymID, strMyAcctID, strHisNymID, strTempMemo, strAmount, strIndices, bPasswordProtected))
    {
        return true;
    }

    return false;
}

OT_COMMAND_OT int32_t details_send_cash(string & strResponse, const string & strServerID, const string & strAssetTypeID, const string & strMyNymID, const string & strMyAcctID, string & strHisNymID, const string & strMemo, const string & strAmount, string & strIndices, const bool bPasswordProtected)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    string strLocation = "\n details_send_cash";

    int64_t lStartAmount = int64_t(0);

    if (VerifyStringVal(strAmount))
    {
        lStartAmount = to_long(strAmount);
    }

    int64_t lAmount = lStartAmount;

    // What we want to do from here is, see if we can send the cash purely using cash we already
    // have in the local purse.
    // If so, we just package it up and send it off using send_user_payment.
    //
    // But if we do NOT have the proper cash tokens in the local purse to send, then we need to
    // withdraw enough tokens until we do, and then try sending again.
    //

    bool bAmountFromIndices = VerifyStringVal(strIndices);
    bool bIndicesFromAmount = VerifyIntVal(lAmount);

    bool bGotData = purse_get_indices_or_amount(strServerID, strAssetTypeID, strMyNymID, lAmount, strIndices); // If strIndices is input, lAmount is output. (And vice-versa.)

    if (!bGotData)  // NOT ENOUGH CASH FOUND IN EXISTING PURSE TO MATCH THE AMOUNT (or indices were specified and not found.)
    {
        if (bAmountFromIndices)
        {
            // If we were starting out with indices, and those indices failed to be found, then there's
            // nothing more we can do. They aren't there.
            //
            OTAPI_Wrap::Output(0, strLocation + ": Sorry, those indices weren't found: " + strIndices + "\nPerhaps try: 'opentxs showpurse'\n");
            return -1;
        }

        // By this point, it means we started with the amount, and tried to use it to find the
        // appropriate indices -- and they weren't there. This means we need to withdraw more cash
        // from the server before we can send it, since we don't have enough in our purse already.
        //
        int32_t nWithdraw = details_withdraw_cash(strMyAcctID, lAmount); // By this point lAmount is only the remaining amount that wasn't found in the purse already.

        if (1 != nWithdraw)
        {
            OTAPI_Wrap::Output(0, strLocation + ": Tried to withdraw cash, but failed.\n");
            return -1;
        }

        // Okay we performed the withdrawal, so now let's see again if we can extract the proper
        // cash tokens from the local purse. We'll load it up again...
        //
        lAmount = lStartAmount;

        bGotData = purse_get_indices_or_amount(strServerID, strAssetTypeID, strMyNymID, lAmount, strIndices); // If strIndices is input, lAmount is output. (And vice-versa.)

        if (!bGotData)
        {
            OTAPI_Wrap::Output(0, strLocation + ": Unable to get enough cash into the local purse to send, EVEN after performing a cash withdrawal. (Failure.)\n strIndices: " + strIndices + " lAmount: " + OTAPI_Wrap::FormatAmount(strAssetTypeID, lAmount) + "\n");
            return -1;
        }
    }

    // By this point, bGotData is definitely true, meaning there are already enough cash tokens in the purse
    // to send, or there are now since performing a withdrawal. Either way, we should be good to go...

    // Returns the exported cash purse, with strRetainedCopy containing the sender's version of that.
    //
    string strRetainedCopy = "";
    string strExportedCashPurse = details_export_cash(strServerID, strMyNymID, strAssetTypeID, strHisNymID, strIndices, bPasswordProtected, strRetainedCopy);
    int32_t nReturnVal = -1;

    if (VerifyStringVal(strExportedCashPurse))
    {
        strResponse = madeEasy.send_user_cash(strServerID, strMyNymID, strHisNymID, strExportedCashPurse, strRetainedCopy); // <==================

        nReturnVal = VerifyMessageSuccess(strResponse);

        if (1 != nReturnVal)
        {
            // It failed sending the cash to the recipient Nym.
            // Re-import strRetainedCopy back into the sender's cash purse.
            //
            bool bImported = OTAPI_Wrap::Wallet_ImportPurse(strServerID, strAssetTypeID, strMyNymID, strRetainedCopy);

            if (bImported)
            {
                OTAPI_Wrap::Output(0, "\n\nFailed sending cash, but at least: success re-importing purse.\nServer: " + strServerID + "\nAsset Type: " + strAssetTypeID + "\nNym: " + strMyNymID + "\n\n");
            }
            else
            {
                OTAPI_Wrap::Output(0, "\n\n Failed sending cash AND failed re-importing purse.\nServer: " + strServerID + "\nAsset Type: " + strAssetTypeID + "\nNym: " + strMyNymID + "\n\nPurse (SAVE THIS SOMEWHERE!):\n\n" + strRetainedCopy + "\n");
            }
        }
    }


    return nReturnVal;
}


OT_COMMAND_OT int32_t main_new_symmetric_key()
{
    string strKey = OTAPI_Wrap::CreateSymmetricKey();

    if (VerifyStringVal(strKey))
    {
        // stderr
        OTAPI_Wrap::Output(0, "\n");

        // stdout
        print(strKey);

        // stderr
        OTAPI_Wrap::Output(0, "\n");

        return 1;
    }

    // "return value"
    return -1;
}


// For a certain index in the payments inbox, this function will deposit the cheque, or
// deposit the purse, or pay the invoice, etc (whatever is at that index.)
// Use a strPaymentType of "ANY" to handle any payment type. Otherwise, pass the payment
// type itself to only succeed for that type. (If only paying invoices, then only handle it
// if it's actually an invoice.)
//
OT_COMMAND_OT int32_t handle_payment_index(const string & strMyAcctID, const int32_t nIndex) // (If nIndex is -1, then it will ask user to paste an invoice.)
{
    string strPaymentType = "ANY";
    return handle_payment_index(strMyAcctID, nIndex, strPaymentType);
}

OT_COMMAND_OT int32_t handle_payment_index(const string & strMyAcctID, const int32_t nIndex, const string & strPaymentType) // (If nIndex is -1, then it will ask user to paste an invoice.)
{
    string strInbox = "";
    return handle_payment_index(strMyAcctID, nIndex, strPaymentType, strInbox);
}

//case ("CHEQUE")
//case ("VOUCHER")
//case ("INVOICE")
//case ("PURSE")
//
// If one of the above types is passed in, then the payment will only be handled if the type matches.
//
// But if "ANY" is passed in, then the payment will be handled for any of them.
//

OT_COMMAND_OT int32_t handle_payment_index(const string & strMyAcctID, const int32_t nIndex, const string & strPaymentType, const string & strInbox) // (If nIndex is -1, then it will ask user to paste an invoice.)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    //
    if (!VerifyStringVal(strMyAcctID) || !VerifyIntVal(nIndex))
    {
        OTAPI_Wrap::Output(0, "Failure: Either strMyAcctID not a valid string, or nIndex not a valid int.\n");
        return -1;
    }

    // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(strMyAcctID);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
        return -1;
    }

    // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
    //
    string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strMyAcctID);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find Server ID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Server based on the account.\n\n");
        return -1;
    }
    // ***************************************************************
    string strInstrument = "";

    if (-1 == nIndex) // paste an instrument
    {
        OTAPI_Wrap::Output(0, "Please paste the instrument, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.
        //
        strInstrument = OT_CLI_ReadUntilEOF();

        if (!VerifyStringVal(strInstrument))
        {
            OTAPI_Wrap::Output(0, "\n\n Sorry, You must paste the instrument, in order to process it. Or, specify an index in the\npayments inbox using the option:  --args \"index INDEX_OF_INVOICE\".\n\n");
            return -1;
        }
    }

    else // Use an instrument from the payments inbox, since a valid index was provided.
    {
        strInstrument = madeEasy.get_payment_instrument(strServerID, strMyNymID, nIndex, strInbox); // strInbox is optional and avoids having to load it multiple times. This function will just load it itself, if it has to.

        if (!VerifyStringVal(strInstrument))
        {
            OTAPI_Wrap::Output(0, "\n\n Unable to get payment instrument based on index: " + to_string(nIndex) + ".\n\n");
            return -1;
        }
    }
    // ***************************************************************
    // By this point, strInstrument is a valid string (whether we got it from the payments inbox,
    // or whether we got it from stdin.)
    //
    string strType = OTAPI_Wrap::Instrmnt_GetType(strInstrument);

    if (!VerifyStringVal(strType))
    {
        OTAPI_Wrap::Output(0, "\n\nFailure: Unable to determine strInstrument's type. Expected CHEQUE, VOUCHER, INVOICE, or (cash) PURSE.\n");
        return -1;
    }

    string strIndexErrorMsg = "";

    if (-1 != nIndex)
    {
        strIndexErrorMsg = "at index " + to_string(nIndex) + " ";
    }

    // If there's a payment type,
    // and it's not "ANY", and it's the wrong type,
    // then skip this one.
    //
    if (VerifyStringVal(strPaymentType) && (strPaymentType != "ANY") && (strPaymentType != strType))
    {
        if ((("CHEQUE" == strPaymentType) && ("VOUCHER" == strType)) || (("VOUCHER" == strPaymentType) && ("CHEQUE" == strType)))
        {
            // in this case we allow it to drop through.
        }
        else
        {
            OTAPI_Wrap::Output(0, "The instrument " + strIndexErrorMsg + "is not a " + strPaymentType + ". (It's a " + strType + ". Skipping.)\n");
            return -1;
        }
    }

    // Note: I USED to check the ASSET TYPE ID here, but then I removed it, since
    // details_deposit_cheque() already verifies that (so I don't need to do it twice.)
    //
    //  string strInstrumentAssetType  = OTAPI_Wrap::Instrmnt_GetAssetID(strInstrument)
    //  string strAccountAssetID       = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strMyAcctID)
    //
    //  if (strInstrumentAssetType != strAccountAssetID)
    //  {
    //      OTAPI_Wrap::Output(0, "The instrument's asset type ("+strInstrumentAssetType+") doesn't match the account's asset type ("+strAccountAssetID+").\nTry specifying a different account using --myacct ACCT_ID\n");
    //      return -1;
    //; }

    // By this point, we know the invoice has the right asset type for the account
    // we're trying to use (to pay it from.)
    //
    // But we need to make sure the invoice is made out to strMyNymID (or to no one.)
    // Because if it IS endorsed to a Nym, and strMyNymID is NOT that nym, then the
    // transaction will fail. So let's check, before we bother sending it...
    //
    string strRecipientUserID = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strInstrument);

    // Not all instruments have a specified recipient. But if they do, let's make
    // sure the Nym matches.
    //
    if (VerifyStringVal(strRecipientUserID) && (strRecipientUserID != strMyNymID))
    {
        OTAPI_Wrap::Output(0, "The instrument " + strIndexErrorMsg + "is endorsed to a specific recipient (" + strRecipientUserID + ") and that doesn't match the account's owner Nym (" + strMyNymID + "). (Skipping.)\nTry specifying a different account, using --myacct ACCT_ID \n");
        return -1;
    }

    // At this point I know the invoice isn't made out to anyone, or if it is, it's properly
    // made out to the owner of the account which I'm trying to use to pay the invoice from.
    // So let's pay it!  P.S. strRecipientUserID might be NULL, but strMyNymID is guaranteed
    // to be good.

    //  string strPayeeUserID    = OTAPI_Wrap::Instrmnt_GetSenderUserID    (strInstrument)
    //  string strPayeeAcctID    = OTAPI_Wrap::Instrmnt_GetSenderAcctID    (strInstrument)

    //
    string strInstrumentAssetType = OTAPI_Wrap::Instrmnt_GetAssetID(strInstrument);
    string strAccountAssetID = OTAPI_Wrap::GetAccountWallet_AssetTypeID(strMyAcctID);

    if (VerifyStringVal(strInstrumentAssetType) && (strAccountAssetID != strInstrumentAssetType))
    {
        OTAPI_Wrap::Output(0, "The instrument at index " + to_string(nIndex) + " has a different asset type than the selected account. (Skipping.)\nTry specifying a different account, using --myacct ACCT_ID \n");
        return -1;
    }

    time_t tFrom = OTAPI_Wrap::Instrmnt_GetValidFrom(strInstrument);
    time_t tTo = OTAPI_Wrap::Instrmnt_GetValidTo(strInstrument);
    time_t tTime = OTAPI_Wrap::GetTime();

    if (tTime < tFrom)
    {
        OTAPI_Wrap::Output(0, "The instrument at index " + to_string(nIndex) + " is not yet within its valid date range. (Skipping.)\n");
        return -1;
    }
    if ((tTo > 0) && (tTime > tTo))
    {
        OTAPI_Wrap::Output(0, "The instrument at index " + to_string(nIndex) + " is expired. (Moving it to the record box.)\n");

        // Since this instrument is expired, remove it from the payments inbox, and move to record box.

        // Note: this harvests
        if ((nIndex >= 0) && OTAPI_Wrap::RecordPayment(strServerID, strMyNymID, true, // bIsInbox = true;
            nIndex, true)) // bSaveCopy = true. (Since it's expired, it'll go into the expired box.)
        {
            return 0;
        }

        return -1;
    }

    // TODO, IMPORTANT: After the below deposits are completed successfully, the wallet
    // will receive a "successful deposit" server reply. When that happens, OT (internally)
    // needs to go and see if the deposited item was a payment in the payments inbox. If so,
    // it should REMOVE it from that box and move it to the record box.
    //
    // That's why you don't see me messing with the payments inbox even when these are successful.
    // They DO need to be removed from the payments inbox, but just not here in the script. (Rather,
    // internally by OT itself.)
    //
    if ("CHEQUE" == strType)
    {
        return details_deposit_cheque(strServerID, strMyAcctID, strMyNymID, strInstrument, strType);
    }
    else if ("VOUCHER" == strType)
    {
        return details_deposit_cheque(strServerID, strMyAcctID, strMyNymID, strInstrument, strType);
    }
    else if ("INVOICE" == strType)
    {
        return details_deposit_cheque(strServerID, strMyAcctID, strMyNymID, strInstrument, strType);
    }
    else if ("PURSE" == strType)
    {
        int32_t nDepositPurse = details_deposit_purse(strServerID, strMyAcctID, strMyNymID, strInstrument, ""); // strIndices is left blank in this case

        // if nIndex !=  -1, go ahead and call RecordPayment on the purse at that index, to
        // remove it from payments inbox and move it to the recordbox.
        //
        if ((nIndex != -1) && (1 == nDepositPurse))
        {
            int32_t nRecorded = OTAPI_Wrap::RecordPayment(strServerID, strMyNymID, true, //bIsInbox=true
                nIndex, true); // bSaveCopy=true.
        }

        return nDepositPurse;
    }
    else
    {
        OTAPI_Wrap::Output(0, "\nSkipping this instrument: Expected CHEQUE, VOUCHER, INVOICE, or (cash) PURSE.\n");
    }

    return -1;
}


/*
EXPORT static std::string NumList_Add (const std::string & strNumList, const std::string & strNumbers);
EXPORT static std::string NumList_Remove (const std::string & strNumList, const std::string & strNumbers);
EXPORT static bool NumList_VerifyQuery(const std::string & strNumList, const std::string & strNumbers); // returns OT_BOOL
EXPORT static bool NumList_VerifyAll (const std::string & strNumList, const std::string & strNumbers); // returns OT_BOOL
EXPORT static int32_t NumList_Count (const std::string & strNumList);
*/

// COULD have been named "details_accept_specific_instruments_of_specific_types_from_the_payment_inbox."

OT_COMMAND_OT int32_t accept_from_paymentbox(const string & strMyAcctID, const string & strIndices)
{
    string strPaymentType = "ANY";
    return accept_from_paymentbox(strMyAcctID, strIndices, strPaymentType);
}

// COULD have been named "details_accept_specific_instruments_of_specific_types_from_the_payment_inbox."
OT_COMMAND_OT int32_t accept_from_paymentbox(const string & strMyAcctID, const string & strIndices, const string & strPaymentType)
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    //
    if (!VerifyStringVal(strMyAcctID))
    {
        OTAPI_Wrap::Output(0, "Failure: strMyAcctID not a valid string.\n");
        return -1;
    }

    // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
    //
    string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(strMyAcctID);

    if (!VerifyStringVal(strMyNymID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
        return -1;
    }

    // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
    //
    string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(strMyAcctID);

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, "Failure: Unable to find Server ID based on myacct. Use: --myacct ACCT_ID\n");
        OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Server based on the account.\n\n");
        return -1;
    }
    // ******************************************************************
    //
    string strInbox = OTAPI_Wrap::LoadPaymentInbox(strServerID, strMyNymID); // Returns NULL, or an inbox.

    if (!VerifyStringVal(strInbox))
    {
        OTAPI_Wrap::Output(0, "\n\n accept_from_paymentbox:  OT_API_LoadPaymentInbox Failed.\n\n");
        return -1;
    }

    int32_t nCount = OTAPI_Wrap::Ledger_GetCount(strServerID, strMyNymID, strMyNymID, strInbox);

    if (!VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "Unable to retrieve size of payments inbox ledger. (Failure.)\n");
        return -1;
    }

    int32_t nIndicesCount = VerifyStringVal(strIndices) ? OTAPI_Wrap::NumList_Count(strIndices) : 0;

    // Either we loop through all the instruments and accept them all, or
    // we loop through all the instruments and accept the specified indices.
    //
    // (But either way, we loop through all the instruments.)
    //
    for (int32_t nIndex = (nCount - 1); nIndex >= 0; --nIndex) // Loop from back to front, so if any are removed, the indices remain accurate subsequently.
    {
        bool bContinue = false;

        // - If indices are specified, but the current index is not on
        //   that list, then continue...
        //
        // - If NO indices are specified, accept all the ones matching MyAcct's asset type.
        //
        if ((nIndicesCount > 0) && !OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex)))
        {
            //          continue  // apparently not supported by the language.
            bContinue = true;
        }

        else if (!bContinue)
        {
            int32_t nHandled = handle_payment_index(strMyAcctID, nIndex, strPaymentType, strInbox);
        }
    }

    return 1;
}

OT_COMMAND_OT int32_t details_accept_invoices(const string & strMyAcctID) // Use this function when you want to loop through all accounts and accept all invoices for them.
{
    string strIndices = "";
    return details_accept_invoices(strMyAcctID, strIndices);
}

OT_COMMAND_OT int32_t details_accept_invoices(const string & strMyAcctID, const string & strIndices)
{
    return accept_from_paymentbox(strMyAcctID, strIndices, "INVOICE");
}


OT_COMMAND_OT int32_t main_accept_invoices()
{
    string strUsage1 = "\nUsage:  acceptinvoices --myacct FROM_ACCT --args \"indices 3,6,8\"  \n (Sample indices are shown.)\n";
    string strUsage2 = "The invoice and myacct must both have same asset type. If indices\nare not specified for the payments inbox, ";
    string strUsage = strUsage1 + strUsage2 + "then OT will pay ALL invoices in it\nthat have the same asset type as MyAcct.\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strIndices = "";

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.
        }

        return details_accept_invoices(MyAcct, strIndices);
    }

    return -1;
}


// Accepts all incoming "payments" from the payments inbox. (NOT Invoices.)
//
OT_COMMAND_OT int32_t details_accept_payments(const string & strMyAcctID)
{
    string strIndices = "";
    return details_accept_payments(strMyAcctID, strIndices);
}

OT_COMMAND_OT int32_t details_accept_payments(const string & strMyAcctID, const string & strIndices)
{

    int32_t nAcceptedPurses = accept_from_paymentbox(strMyAcctID, strIndices, "PURSE");
    // Voucher is already interpreted as a form of cheque, so this is redundant.
    //
    //  int32_t nAcceptedVouchers = accept_from_paymentbox(strMyAcctID, strIndices, "VOUCHER")
    int32_t nAcceptedCheques = accept_from_paymentbox(strMyAcctID, strIndices, "CHEQUE");

    // Note: NOT invoices.

    // If all two calls succeed, then the total here is 2.
    // So we return success as well (1).
    //
    if ((nAcceptedPurses > -1) || (nAcceptedCheques > -1))
    {
        return 1;
    }

    return -1;

}


OT_COMMAND_OT int32_t main_accept_payments()
{
    string strUsage1 = "\nUsage:  acceptpayments --myacct INTO_ACCT --args \"indices 3,6,8\"  \n (Sample indices are shown.)\n";
    string strUsage2 = "The payment instrument and myacct must both have same asset type. If indices\nare not specified for the payments inbox, ";
    string strUsage = strUsage1 + strUsage2 + "then OT will accept ALL payment\ninstruments in it that have the same asset type as MyAcct.\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {
        string strIndices = "";

        if (VerifyExists("Args", false))
        {
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "indices 4,6,9"
            //
            strIndices = OT_CLI_GetValueByKey(Args, "indices"); // OTNumList will be used for this value.
        }

        return details_accept_payments(MyAcct, strIndices);
    }

    return -1;
}


// Pay an invoice
//
OT_COMMAND_OT int32_t main_payinvoice()
{
    string strUsage1 = "\nUsage:  payinvoice --myacct FROM_ACCT --args \"index INVOICE_INDEX\" \n";
    string strUsage2 = "The invoice and myacct must both have same asset type. If an index is not\n";
    string strUsage = strUsage1 + strUsage2 + "specified for the payments inbox, then OT will ask you to paste an invoice.\n\n";

    OTAPI_Wrap::Output(0, strUsage);

    //
    if (!VerifyExists("MyAcct"))
    {
        return -1;
    }
    // ***************************************************************
    int32_t nIndex = -1;

    if (VerifyExists("Args"))
    {
        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "index 1"
        //
        string strIndex = OT_CLI_GetValueByKey(Args, "index"); // any integer value

        if (VerifyStringVal(strIndex))
        {
            int32_t nTempIndex = to_int(strIndex);

            if (VerifyIntVal(nTempIndex) && (nTempIndex >= 0))
            {
                nIndex = nTempIndex;
            }
        }
    }
    OTAPI_Wrap::Output(0, "\n\n"); // stderr
    // ***************************************************************
    //
    int32_t nPaidInvoice = handle_payment_index(MyAcct, nIndex, "INVOICE");

    if (1 == nPaidInvoice) // Success!  (Therefore, remove from payments inbox, and move to record box.)
    {
        // Should I bother moving the invoice from the payments inbox to the record box?
        //
        // Update: Okay for now, I'm using an API call here (RecordPayment) which moves the invoice.
        // HOWEVER, in the long term, we don't want to do it here. Rather, we want to do it inside OT while
        // it's processesing the server reply for your cheque (invoice) deposit. For example what if there's
        // a network problem and we don't process that reply here now? There'll still be a copy of the reply
        // in the Nymbox and it will still get processed at a future time... and THAT's when we need to move
        // the record, not here. (But this is what we'll do for now.)
        //
        // OTAPI_Wrap::RecordPayment(const OTIdentifier & SERVER_ID,
        //                              const OTIdentifier & USER_ID,
        //                              bool bIsInbox, // true == payments inbox. false == payments outbox.
        //                              int32_t  nIndex)   // removes payment instrument (from payments in or out box) and moves to record box.
        //        if (!OTAPI_Wrap::RecordPayment(strServerID, strMyNymID, ))   {; }
        //

        // UPDATE:
        /*
        - In my Payments Inbox, there could be a cheque or invoice. Either way, when I deposit the cheque or
        pay the invoice, the chequeReceipt goes back to the signer's asset account's inbox.
        - When he accepts the chequeReceipt (during a processInbox) and WHEN HE GETS THE "SUCCESS" REPLY to that
        processInbox, is when the chequeReceipt should be moved from his inbox to his record box. It MUST be
        done then, inside OT, because the next time he downloads the inbox from the server, that chequeReceipt
        won't be in there anymore! It'll be too late to pass it on to the records.
        - Whereas I, being the recipient of his cheque, had it in my **payments inbox,** and thus upon receipt
        of a successful server-reply to my deposit transaction, need to move it from my payments inbox to my
        record box. (The record box will eventually be a callback so that client software can take over that
        functionality, which is outside the scope of OT. The actual CALL to store in the record box, however
        should occur inside OT.)
        - For now, I'm using the below API call, so it's available inside the scripts. This is "good enough"
        for now, just to get the payments inbox/outbox working for the scripts. But in the long term, I'll need
        to add the hooks directly into OT as described just above. (It'll be necessary in order to get the record
        box working.)
        - Since I'm only worried about Payments Inbox for now, and since I'll be calling the below function
        directly from inside the scripts, how will this work? Incoming cheque or invoice will be in the payments
        inbox, and will need to be moved to recordBox (below call) when the script receives a success reply to
        the depositing/paying of that cheque/invoice.
        - Whereas outoing cheque/invoice is in the Outpayments box, (fundamentally more similar to the outmail
        box than to the payments inbox.) If the cheque/invoice is cashed/paid by the endorsee, **I** will receive
        the chequeReceipt, in MY asset account inbox, and when I accept it during a processInbox transaction,
        the SUCCESS REPLY from the server for that processInbox is where I should actually process that chequeReceipt
        and, if it appears in the outpayments box, move it at that time to the record box. The problem is, I can NOT
        do this much inside the script. To do this part, I thus HAVE to go into OT itself as I just described.
        - Fuck!
        - Therefore I might as well comment this out, since this simply isn't going to work.

        - Updated plan:
        1. DONE: Inside OT, when processing successful server reply to processInbox request, if a chequeReceipt
        was processed out successfully, and if that chequeReceipt is found inside the outpayments, then
        move it at that time to the record box.
        2. DONE: Inside OT, when processing successful server reply to depositCheque request, if that cheque is
        found inside the Payments Inbox, move it to the record box.
        3. As for cash:
        If I SENT cash, it will be in my outpayments box. But that's wrong. Because I can
        never see if the guy cashed it or not. Therefore it should go straight to the record box, when
        sent. AND it needs to be encrypted to MY key, not his -- so need to generate BOTH versions, when
        exporting the purse to him in the FIRST PLACE. Then my version goes straight into my record box and
        I can delete it at my leisure. (If he comes running the next day saying "I lost it!!" I can still
        recover it. But once he deposits it, then the cash will be no good and I might as well archive it
        or destroy it, or whatever I choose to do with my personal records.)
        If I RECEIVED cash, it will be in my payments inbox, and then when I deposit it, and when I process
        the SUCCESSFUL server REPLY to my depositCash request, it should be moved to my record Box.
        4. How about vouchers? If I deposit a voucher, then the "original sender" should get some sort of
        notice. This means attaching his ID to the voucher--which should be optional--and then dropping an
        "FYI" notice to him when it gets deposited. It can't be a normal chequeReceipt because that's used
        to verify the balance agreement against a balance change, whereas a "voucher receipt" wouldn't represent
        a balance change at all, since the balance was already changed when you originally bought the voucher.
        Instead it would probably be send to your Nymbox but it COULD NOT BE PROVEN that it was, since OT currently
        can't prove NOTICE!!

        All of the above needs to happen inside OT, since there are many plances where it's the only appropriate
        place to take the necessary action. (Script cannot.)
        */

        print("\n Success paying invoice!\n\n");

        return 1;
    }


    return -1;
}


// Show an individual payment in detail.
//
OT_COMMAND_OT int32_t main_show_payment()
{
    string strUsage = "\nUsage:  showpayment --args \"index PAYMENT_INDEX showmemo true|false\"\n Default index is 0. Default showmemo is false.\n";

    OTAPI_Wrap::Output(0, strUsage);

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // SHOW a payment from the PAYMENTS INBOX
    //
    // Load an asset account's payments inbox from local storage and display it on the screen.
    //

    if (VerifyExists("Server") && VerifyExists("MyNym") && VerifyExists("Args"))
    {

        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "index 1"
        //
        string strIndex = OT_CLI_GetValueByKey(Args, "index"); // any integer value
        string strShowLargeMemo = OT_CLI_GetValueByKey(Args, "showmemo"); // any integer value
        int32_t nIndex = 0;
        bool bShowLargeMemo = false;  // Memos aren't normally shown if they contain a newline. But you can force them to show anyway.

        // Set the values based on the custom arguments, for those found.
        //
        if (VerifyStringVal(strShowLargeMemo) && ("true" == strShowLargeMemo))
        {
            bShowLargeMemo = true; // now we'll show the memo even if it spans multiple lines.
        }

        if (VerifyStringVal(strIndex))
        {
            int32_t nTempIndex = to_int(strIndex);

            if (VerifyIntVal(nTempIndex) && (nTempIndex >= 0))
            {
                nIndex = nTempIndex;
            }
        }
        // ***************************************************************

        string strInbox = OTAPI_Wrap::LoadPaymentInbox(Server, MyNym); // Returns NULL, or an inbox.

        if (!VerifyStringVal(strInbox))
        {
            OTAPI_Wrap::Output(0, "\n\n OT_API_LoadPaymentInbox: Failed.\n\n");
            return -1;
        }
        else // Success!
        {
            OTAPI_Wrap::Output(0, "\n\n"); // stderr
            //          print(strInbox)          // stdout

            int32_t nCount = OTAPI_Wrap::Ledger_GetCount(Server, MyNym, MyNym, strInbox);

            if (VerifyIntVal(nCount))
            {
                if (nIndex > (nCount - 1))
                {
                    OTAPI_Wrap::Output(0, "Index out of bounds. (There are " + to_string(nCount) + " indices, starting at 0.\n");
                    return -1;
                }

                OTAPI_Wrap::Output(0, "Ind  Amt   Type       Txn#   Memo\n");
                OTAPI_Wrap::Output(0, "---------------------------------\n");

                string strInstrument = OTAPI_Wrap::Ledger_GetInstrument(Server, MyNym, MyNym, strInbox, nIndex);

                if (!VerifyStringVal(strInstrument))
                {
                    OTAPI_Wrap::Output(0, "Failed trying to get payment instrument from payments box.\n");
                    return -1;
                }

                string strTrans = OTAPI_Wrap::Ledger_GetTransactionByIndex(Server, MyNym, MyNym, strInbox, nIndex);
                int64_t lTransNumber = OTAPI_Wrap::Ledger_GetTransactionIDByIndex(Server, MyNym, MyNym, strInbox, nIndex);

                int64_t lRefNum = OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(Server, MyNym, MyNym, strTrans);

                int64_t lAmount = OTAPI_Wrap::Instrmnt_GetAmount(strInstrument);
                string strType = OTAPI_Wrap::Instrmnt_GetType(strInstrument);
                string strAssetType = OTAPI_Wrap::Instrmnt_GetAssetID(strInstrument);  // todo: output this.
                string strMemo = OTAPI_Wrap::Instrmnt_GetMemo(strInstrument);
                string strSenderUserID = OTAPI_Wrap::Instrmnt_GetSenderUserID(strInstrument);
                string strSenderAcctID = OTAPI_Wrap::Instrmnt_GetSenderAcctID(strInstrument);
                string strRemitterUserID = OTAPI_Wrap::Instrmnt_GetRemitterUserID(strInstrument);
                string strRemitterAcctID = OTAPI_Wrap::Instrmnt_GetRemitterAcctID(strInstrument);
                string strRecipientUserID = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strInstrument);
                string strRecipientAcctID = OTAPI_Wrap::Instrmnt_GetRecipientAcctID(strInstrument);

                string strUserID = VerifyStringVal(strRemitterUserID) ? strRemitterUserID : strSenderUserID;
                string strAcctID = VerifyStringVal(strRemitterAcctID) ? strRemitterAcctID : strSenderAcctID;

                bool bUserIDExists = VerifyStringVal(strUserID);
                bool bAcctIDExists = VerifyStringVal(strAcctID);
                bool bAssetIDExists = VerifyStringVal(strAssetType);
                bool bMemoExists = VerifyStringVal(strMemo);

                bool bHasAmount = VerifyIntVal(lAmount);


                if (bMemoExists && (strMemo.find("\n") != string::npos) && !bShowLargeMemo)
                {
                    strMemo = "<too large to display here>";
                }
                else if (bMemoExists)
                {
                    string strTempMemo = "\"" + strMemo + "\"";
                    strMemo = strTempMemo;
                }

                string strNewlineSeparator = "";

                if (bUserIDExists || bAcctIDExists)
                {
                    strNewlineSeparator = "\n";
                }

                string strSeparator = (!bUserIDExists && !bAcctIDExists && !bAssetIDExists) ? "" : strNewlineSeparator;

                // Set up some symbols to appear or not,
                // based on whether there is something to show.
                //
                string strUserDenoter = (bUserIDExists ? "U:" : "");
                string strUserDenoter2 = (bUserIDExists ? " - " : "");
                string strAcctDenoter = (bAcctIDExists ? "A:" : "");
                string strAcctDenoter2 = (bAcctIDExists ? " - " : "");
                string strAssetDenoter = (bAssetIDExists ? "T:" : "");
                string strAssetDenoter2 = (bAssetIDExists ? " - " : "");

                // If we have the user/acct/asset ID, then get the associated name (if that exists.)
                //
                string strUserName = (bUserIDExists ? ("\"" + OTAPI_Wrap::GetNym_Name(strUserID) + "\"") : "");
                string strAcctName = (bAcctIDExists ? ("\"" + OTAPI_Wrap::GetAccountWallet_Name(strAcctID) + "\"") : "");
                string strAssetName = (bAssetIDExists ? ("\"" + OTAPI_Wrap::GetAssetType_Name(strAssetType) + "\"") : "");

                // Just making sure here that if the string wasn't there, that it's set to
                // a proper empty string, instead of a null or a "not a value" value.
                //
                if (!VerifyStringVal(strUserName))      { strUserName = ""; strUserDenoter2 = ""; }
                if (!VerifyStringVal(strAcctName))      { strAcctName = ""; strAcctDenoter2 = ""; }
                if (!VerifyStringVal(strAssetName))     { strAssetName = ""; strAssetDenoter2 = ""; }

                if ("\"\"" == strUserName)              { strUserName = ""; strUserDenoter2 = ""; }
                if ("\"\"" == strAcctName)              { strAcctName = ""; strAcctDenoter2 = ""; }
                if ("\"\"" == strAssetName)             { strAssetName = ""; strAssetDenoter2 = ""; }

                string strOut1 = to_string(nIndex) + "    ";

                string strOut2 = "      ";

                if (bAssetIDExists && bHasAmount)
                {
                    strOut2 = OTAPI_Wrap::FormatAmount(strAssetType, lAmount) + (OTAPI_Wrap::FormatAmount(strAssetType, lAmount).size() < 3 ? "    " : "   ");
                }

                string strOut3 = strType;
                string strOut4 = strType.size() > 10 ? " " : "    ";
                string strOut5 = to_string(lTransNumber) + (to_string(lTransNumber).size() < 2 ? "    " : "   ");
                string strOut6 = (bMemoExists ? (strMemo) : "") + "\n";
                string strOut7 = strUserDenoter + strUserID + strUserDenoter2 + strUserName + strSeparator;
                string strOut8 = strAcctDenoter + strAcctID + strAcctDenoter2 + strAcctName + strSeparator;
                string strOut9 = strAssetDenoter + strAssetType + strAssetDenoter2 + strAssetName;

                print(strOut1 + strOut2 + strOut3 + strOut4 + strOut5 + strOut6 + strOut7 + strOut8 + strOut9);

                print("Instrument:\n" + strInstrument);

            } // VerifyIntVal (nCount)

            //          OTAPI_Wrap::Output(0, "\n\n") // stderr
            return 1;
        }
    }
    return -1;
}


OT_COMMAND_OT int32_t main_show_incoming()
{
    int32_t nShowPayments = -1;
    int32_t nShowInbox = -1;

    if (VerifyExists("MyAcct", false))
    {
        nShowInbox = main_show_inbox();
    }
    else
    {
        OTAPI_Wrap::Output(0, "Try adding --myacct ASSET_ACCT_ID   (to see the asset account's inbox.)\n");
    }

    if (VerifyExists("Server", false) && VerifyExists("MyNym", false))
    {
        nShowPayments = main_show_payments_inbox();
    }
    else
    {
        OTAPI_Wrap::Output(0, "Try adding --mynym NYM_ID  and  --server SERVER_ID\n(to see the payments inbox for that Server and Nym.)\n");
    }

    if ((nShowInbox > -1) || (nShowPayments > -1))
    {
        return 1;
    }

    return -1;
}


OT_COMMAND_OT int32_t main_show_outgoing()
{
    int32_t nShowPayments = -1;
    int32_t nShowOutbox = -1;

    if (VerifyExists("MyAcct", false))
    {
        nShowOutbox = main_show_outbox();
    }
    else
    {
        OTAPI_Wrap::Output(0, "Try adding --myacct ASSET_ACCT_ID   (to see the asset account's outbox.)\n");
    }

    if (VerifyExists("MyNym", false))
    {
        nShowPayments = main_show_outpayment();
    }
    else
    {
        OTAPI_Wrap::Output(0, "Try adding --mynym NYM_ID (to see the outpayment box for that Nym.)\n");
    }

    if ((nShowOutbox > -1) || (nShowPayments > -1))
    {
        return 1;
    }

    return -1;
}


OT_COMMAND_OT int32_t main_show_payments_inbox()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;

    // SHOW PAYMENTS INBOX
    //
    // Load an asset account's payments inbox from local storage and display it on the screen.
    //

    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        // ***************************************************************

        string strInbox = OTAPI_Wrap::LoadPaymentInbox(Server, MyNym); // Returns NULL, or an inbox.

        if (!VerifyStringVal(strInbox))
        {
            OTAPI_Wrap::Output(0, "\n Unable to load the payments inbox (probably doesn't exist yet.)\n(Nym/Server: " + MyNym + " / " + Server + " )\n\n");
            return -1;
        }
        else // Success!
        {
            OTAPI_Wrap::Output(0, "\n"); // stderr
            //          print(strInbox)          // stdout

            int32_t nCount = OTAPI_Wrap::Ledger_GetCount(Server, MyNym, MyNym, strInbox);

            if (VerifyIntVal(nCount))
            {
                if (nCount > 0)
                {
                    OTAPI_Wrap::Output(0, "Show payments inbox (Nym/Server)\n( " + MyNym + " / " + Server + " )\n");
                    OTAPI_Wrap::Output(0, "Idx  Amt   Type      Txn#  Asset_Type\n");
                    OTAPI_Wrap::Output(0, "---------------------------------------\n");

                    for (int32_t nIndex = 0; nIndex < nCount; ++nIndex)
                    {
                        string strInstrument = OTAPI_Wrap::Ledger_GetInstrument(Server, MyNym, MyNym, strInbox, nIndex);

                        if (!VerifyStringVal(strInstrument))
                        {
                            OTAPI_Wrap::Output(0, "Failed trying to get payment instrument from payments box.\n");
                            return -1;
                        }

                        string strTrans = OTAPI_Wrap::Ledger_GetTransactionByIndex(Server, MyNym, MyNym, strInbox, nIndex);
                        int64_t lTransNumber = OTAPI_Wrap::Ledger_GetTransactionIDByIndex(Server, MyNym, MyNym, strInbox, nIndex);

                        string strTransID = VerifyIntVal(lTransNumber) ? to_string(lTransNumber) : "UNKNOWN_TRANS_NUM";

                        int64_t lRefNum = OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(Server, MyNym, MyNym, strTrans);
                        //                      string strAmount          = OTAPI_Wrap::Transaction_GetAmount(Server, MyNym, MyNym, strTrans)
                        //                      string strType            = OTAPI_Wrap::Transaction_GetType(Server, MyNym, MyNym, strTrans)
                        //                      string strSenderUserID    = OTAPI_Wrap::Transaction_GetSenderUserID(Server, MyNym, MyNym, strTrans)
                        //                      string strSenderAcctID    = OTAPI_Wrap::Transaction_GetSenderAcctID(Server, MyNym, MyNym, strTrans)
                        //                      string strRecipientUserID = OTAPI_Wrap::Transaction_GetRecipientUserID(Server, MyNym, MyNym, strTrans)
                        //                      string strRecipientAcctID = OTAPI_Wrap::Transaction_GetRecipientAcctID(Server, MyNym, MyNym, strTrans)

                        //                      string strRefNum          = OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(Server, MyNym, MyNym, strTrans)
                        int64_t lAmount = OTAPI_Wrap::Instrmnt_GetAmount(strInstrument);
                        string strType = OTAPI_Wrap::Instrmnt_GetType(strInstrument);
                        string strAssetType = OTAPI_Wrap::Instrmnt_GetAssetID(strInstrument);  // todo: output this.
                        string strSenderUserID = OTAPI_Wrap::Instrmnt_GetSenderUserID(strInstrument);
                        string strSenderAcctID = OTAPI_Wrap::Instrmnt_GetSenderAcctID(strInstrument);
                        string strRecipientUserID = OTAPI_Wrap::Instrmnt_GetRecipientUserID(strInstrument);
                        string strRecipientAcctID = OTAPI_Wrap::Instrmnt_GetRecipientAcctID(strInstrument);

                        string strUserID = VerifyStringVal(strSenderUserID) ? strSenderUserID : strRecipientUserID;
                        string strAcctID = VerifyStringVal(strSenderAcctID) ? strSenderAcctID : strRecipientAcctID;

                        bool bHasAmount = VerifyIntVal(lAmount);
                        bool bHasAsset = VerifyStringVal(strAssetType);

                        string strAmount = (bHasAmount && bHasAsset) ? OTAPI_Wrap::FormatAmount(strAssetType, lAmount) : "UNKNOWN_AMOUNT";

                        bool bUserIDExists = VerifyStringVal(strUserID);
                        bool bAcctIDExists = VerifyStringVal(strAcctID);
                        bool bAssetIDExists = VerifyStringVal(strAssetType);

                        string strAssetDenoter = (bAssetIDExists ? " - " : "");

                        string strAssetName = (bAssetIDExists ? ("\"" + OTAPI_Wrap::GetAssetType_Name(strAssetType) + "\"") : "");
                        if (!VerifyStringVal(strAssetName))     { strAssetName = ""; strAssetDenoter = ""; }

                        string strOut1 = to_string(nIndex) + "    ";
                        string strOut2 = strAmount + (strAmount.size() < 3 ? "    " : "   ");
                        string strOut3 = strType;
                        string strOut4 = strType.size() > 10 ? " " : "    ";
                        string strOut5 = strTransID + (strTransID.size() < 2 ? "    " : "   ");
                        string strOut6 = strAssetType + strAssetDenoter + strAssetName;

                        print(strOut1 + strOut2 + strOut3 + strOut4 + strOut5 + strOut6);
                    } // for

                    OTAPI_Wrap::Output(0, "\n For the above, try: acceptpayments, acceptinvoices, acceptmoney, or acceptall.\n EXCEPT for smart contracts and payment plans -- for those, use: opentxs confirm\n\n");
                } // if nCount > 0
                else
                {
                    OTAPI_Wrap::Output(0, "\n Payments inbox is empty (Nym/Server: " + MyNym + " / " + Server + " )\n");
                }
            } // VerifyIntVal (nCount)

            return 1;
        }
    }
    return -1;
}


// Don't use this unless you really only need one record.
// Instead, use the function below it. (Otherwise you'll be
// loading the record box from storage for EACH record, instead
// of loading it once for ALL the records in your loop.)
//
OT_COMMAND_OT int32_t details_show_record(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const int32_t nIndex)
{
    string strRecordBox = OTAPI_Wrap::LoadRecordBox(strServerID, strMyNymID, strMyAcctID); // Returns NULL, or a record box.

    if (!VerifyStringVal(strRecordBox))
    {
        OTAPI_Wrap::Output(0, "\n\n details_show_record: OT_API_LoadRecordBox: Failed.\n\n");
        return false;
    }

    // Success!
    return details_show_record(strServerID, strMyNymID, strMyAcctID, nIndex, strRecordBox);
}


OT_COMMAND_OT int32_t details_show_record(const string & strServerID, const string & strMyNymID, const string & strMyAcctID, const int32_t nIndex, const string & strRecordBox)
{
    if (!VerifyStringVal(strRecordBox))
    {
        OTAPI_Wrap::Output(0, "\n\n details_show_record: strRecordBox is empty.\n(Need to load it first before calling this function.)\n\n");
        return false;
    }

    // Success!
    //
    string strTrans = OTAPI_Wrap::Ledger_GetTransactionByIndex(strServerID, strMyNymID, strMyAcctID, strRecordBox, nIndex);
    int64_t lTransID = OTAPI_Wrap::Ledger_GetTransactionIDByIndex(strServerID, strMyNymID, strMyAcctID, strRecordBox, nIndex);
    int64_t lRefNum = OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(strServerID, strMyNymID, strMyAcctID, strTrans);
    int64_t lAmount = OTAPI_Wrap::Transaction_GetAmount(strServerID, strMyNymID, strMyAcctID, strTrans);
    string strType = OTAPI_Wrap::Transaction_GetType(strServerID, strMyNymID, strMyAcctID, strTrans);
    string strSenderUserID = OTAPI_Wrap::Transaction_GetSenderUserID(strServerID, strMyNymID, strMyAcctID, strTrans);
    string strSenderAcctID = OTAPI_Wrap::Transaction_GetSenderAcctID(strServerID, strMyNymID, strMyAcctID, strTrans);
    string strRecipientUserID = OTAPI_Wrap::Transaction_GetRecipientUserID(strServerID, strMyNymID, strMyAcctID, strTrans);
    string strRecipientAcctID = OTAPI_Wrap::Transaction_GetRecipientAcctID(strServerID, strMyNymID, strMyAcctID, strTrans);

    string strUserID = VerifyStringVal(strSenderUserID) ? strSenderUserID : strRecipientUserID;
    string strAcctID = VerifyStringVal(strSenderAcctID) ? strSenderAcctID : strRecipientAcctID;

    bool bUserIDExists = VerifyStringVal(strUserID);
    bool bAcctIDExists = VerifyStringVal(strAcctID);

    string strNewlineSeparator = "";

    if (bUserIDExists || bAcctIDExists)
    {
        strNewlineSeparator = "\n                                 |";
    }

    string strSeparator = (!bUserIDExists && !bAcctIDExists) ? "" : strNewlineSeparator;

    string strUserDenoter = (bUserIDExists ? "U:" : "");
    string strAcctDenoter = (bAcctIDExists ? "A:" : "");

    string strAssetTypeID = bAcctIDExists ? OTAPI_Wrap::GetAccountWallet_AssetTypeID(strAcctID) : "";

    bool bHasAmount = VerifyIntVal(lAmount);
    bool bHasAsset = VerifyStringVal(strAssetTypeID);

    string strAmount = bHasAmount ? (bHasAsset ? OTAPI_Wrap::FormatAmount(strAssetTypeID, lAmount) : to_string(lAmount)) : "UNKNOWN_AMOUNT";

    OTAPI_Wrap::Output(0, to_string(nIndex) + "    ");
    OTAPI_Wrap::Output(0, strAmount + (strAmount.size() < 3 ? "    " : "   "));
    OTAPI_Wrap::Output(0, strType);
    OTAPI_Wrap::Output(0, strType.size() > 10 ? " " : "    ");
    OTAPI_Wrap::Output(0, to_string(lTransID) + (to_string(lTransID).size() < 2 ? "    " : "   "));
    OTAPI_Wrap::Output(0, to_string(lRefNum) + (to_string(lRefNum).size() > 2 ? "  " : " ") + "|");
    OTAPI_Wrap::Output(0, strUserDenoter + strUserID + strSeparator + strAcctDenoter + strAcctID + "\n");

    return true;
}


OT_COMMAND_OT int32_t details_show_records(const string & strServerID, const string & strMyNymID, const string & strMyAcctID)
{
    string strRecordBox = OTAPI_Wrap::LoadRecordBox(strServerID, strMyNymID, strMyAcctID); // Returns NULL, or a record box.

    if (!VerifyStringVal(strRecordBox))
    {
        OTAPI_Wrap::Output(0, "\n\n details_show_records: OT_API_LoadRecordBox: Failed.\n\n");
        return -1;
    }
    // Success!
    OTAPI_Wrap::Output(0, "\n\n"); // stderr
    //  print(strRecordBox)      // stdout

    int32_t nCount = OTAPI_Wrap::Ledger_GetCount(strServerID, strMyNymID, strMyAcctID, strRecordBox);

    if (VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "SHOW RECORDS: \n\n");
        OTAPI_Wrap::Output(0, "Idx  Amt  Type        Txn# InRef#|User / Acct\n");
        OTAPI_Wrap::Output(0, "---------------------------------|(from or to)\n");

        for (int32_t nIndex = 0; nIndex < nCount; ++nIndex)
        {
            if (!details_show_record(strServerID, strMyNymID, strMyAcctID, nIndex, strRecordBox))
            {
                OTAPI_Wrap::Output(0, "details_show_records: Error calling details_show_record.\n");
                return -1;
            }
        } // for
    } // VerifyIntVal (nCount)

    return 1;
}


OT_COMMAND_OT int32_t main_show_records()
{
    string strLocation = "main_show_records";

    // SHOW RECORD BOX
    //
    // Load an asset account's record box from local storage and display it on the screen.
    //
    bool bNymExists = VerifyExists("MyNym", false);
    bool bAcctExists = VerifyExists("MyAcct", false);
    bool bBothExist = (bNymExists &&  bAcctExists);
    bool bShowNymOnly = (bNymExists && !bAcctExists);

    //
    string strMyNymID = "";

    if (bShowNymOnly)
    {
        strMyNymID = MyNym;
    }
    else if (bAcctExists)
    {
        strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);
    }
    else
    {
        OTAPI_Wrap::Output(0, strLocation + ": This should never happen. (1)\n");
        return -1;
    }

    if (!VerifyStringVal(strMyNymID))
    {
        // if bShowNymOnly is true, then we KNOW MyNym is the Nym, and we ALREADY know he's
        // good, since we called VerifyExists at the top of this function. (MyNym, unlike HisNym,
        // is verified against the wallet, so we KNOW it's there.)
        // Therefore, if strMyNymID doesn't contain a proper string, then we KNOW bShowNymOnly
        // must have been false, and that OTAPI_Wrap::GetAccountWallet_NymID(MyAcct) was the call that
        // failed. Thus, the error message is appropriate to the latter case and not the former.
        //
        OTAPI_Wrap::Output(0, strLocation + ": Unable to find NymID based on myacct. Try a different account or nym, using --myacct ACCT_ID or --mynym NYM_ID\n");
        return -1;
    }
    if (bBothExist && !(strMyNymID == MyNym))
    {
        OTAPI_Wrap::Output(0, strLocation + ": MyNym (" + MyNym + ") is not the same nym who owns MyAcct.\nTo override using MyAcct's owner nym, add:  --mynym (" + strMyNymID + ")\n");
        return -1;
    }

    // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
    //
    string strServerID = "";

    if (bAcctExists)
    {
        strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);
    }
    else if (VerifyExists("Server", false))
    {
        strServerID = Server;
    }
    else
    {
        OTAPI_Wrap::Output(0, strLocation + ": Server was not specified, and either MyAcct wasn't specified either, or if it was, I was unable to find any ServerID associated with MyAcct.\nTry a different account or different server, using --myacct ACCT_ID or --server SERVER_ID \n\n");
        return -1;
    }

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Unable to find Server ID.\nTry: --server SERVER_ID\nYou might also try: --myacct ACCT_ID  (It will find the server ID based on the account.)\n");
        return -1;
    }
    // ***************************************************************
    //
    // REMEMBER, recordbox for MyAcct contains the old inbox receipts.
    // Whereas recordbox for MyNym contains the old payments (in and out.)
    // In the case of the latter, the NYM must be passed as the ACCT...
    //
    // Meaning: there are TWO record boxes. So must there thus be two commands
    // for viewing them? Or do we combine them somehow?
    ///
    // ===> I say combine them, since they are for viewing only (nothing is actually done
    // with the records -- they're just there for the actual client to take and store
    // however it wishes.)
    //
    OTAPI_Wrap::Output(0, "\n\nNote: OT is completely done with these records. A proper GUI will sweep them out\nperiodically and archive them somewhere, or just erase them. All you can do at the\ncommand line (using this tool) is view them, or erase them using: opentxs clearrecords \n\n");
    OTAPI_Wrap::Output(0, "\nArchived Nym-related records (" + strMyNymID + "): \n");
    int32_t nNymRecords = details_show_records(strServerID, strMyNymID, strMyNymID);
    OTAPI_Wrap::Output(0, "--------------------------------------------------------------\n");

    int32_t nAcctRecords = 1;

    if (bAcctExists)
    {
        OTAPI_Wrap::Output(0, "\nArchived Account-related records (" + MyAcct + "): \n");
        nAcctRecords = details_show_records(strServerID, strMyNymID, MyAcct);
    }

    if (2 == (nNymRecords + nAcctRecords))
    {
        return 1; // success.
    }

    return -1;
}


OT_COMMAND_OT int32_t details_clear_records(const string & strServerID, const string & strMyNymID, const string & strMyAcctID)
{
    bool bTrue = true;
    bool bCleared = OTAPI_Wrap::ClearRecord(strServerID, strMyNymID, strMyAcctID, 0, bTrue); // nIndex=0 (ignored when clearing all), ClearAll = true.

    return bCleared ? 1 : -1;
}


OT_COMMAND_OT int32_t main_clear_records()
{
    string strLocation = "main_clear_records";

    OTAPI_Wrap::Output(0, " Usage:      opentxs clearrecords\n\n");


    // CLEAR RECORD BOX
    //
    // Load an asset account's record box from local storage and display it on the screen.
    //
    bool bNymExists = VerifyExists("MyNym", false);
    bool bAcctExists = VerifyExists("MyAcct", false);
    bool bBothExist = (bNymExists &&  bAcctExists);
    bool bShowNymOnly = (bNymExists && !bAcctExists);

    //
    string strMyNymID = "";

    if (bShowNymOnly)
    {
        strMyNymID = MyNym;
    }
    else if (bAcctExists)
    {
        strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);
    }
    else
    {
        OTAPI_Wrap::Output(0, strLocation + ": This should never happen. (1)\n");
        return -1;
    }

    if (!VerifyStringVal(strMyNymID))
    {
        // if bShowNymOnly is true, then we KNOW MyNym is the Nym, and we ALREADY know he's
        // good, since we called VerifyExists at the top of this function. (MyNym, unlike HisNym,
        // is verified against the wallet, so we KNOW it's there.)
        // Therefore, if strMyNymID doesn't contain a proper string, then we KNOW bShowNymOnly
        // must have been false, and that OTAPI_Wrap::GetAccountWallet_NymID(MyAcct) was the call that
        // failed. Thus, the error message is appropriate to the latter case and not the former.
        //
        OTAPI_Wrap::Output(0, strLocation + ": Unable to find NymID based on myacct. Try a different account or nym, using --myacct ACCT_ID or --mynym NYM_ID\n");
        return -1;
    }
    if (bBothExist && !(strMyNymID == MyNym))
    {
        OTAPI_Wrap::Output(0, strLocation + ": MyNym (" + MyNym + ") is not the same nym who owns MyAcct.\nTo override using MyAcct's owner nym, add:  --mynym (" + strMyNymID + ")\n");
        return -1;
    }

    // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
    //
    string strServerID = "";

    if (bAcctExists)
    {
        strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);
    }
    else if (VerifyExists("Server", false))
    {
        strServerID = Server;
    }
    else
    {
        OTAPI_Wrap::Output(0, strLocation + ": Server was not specified, and either MyAcct wasn't specified either, or if it was, I was unable to find any ServerID associated with MyAcct.\nTry a different account or different server, using --myacct ACCT_ID or --server SERVER_ID \n\n");
        return -1;
    }

    if (!VerifyStringVal(strServerID))
    {
        OTAPI_Wrap::Output(0, strLocation + ": Unable to find Server ID.\nTry: --server SERVER_ID\nYou might also try: --myacct ACCT_ID  (It will find the server ID based on the account.)\n");
        return -1;
    }
    // ***************************************************************
    //
    // REMEMBER, recordbox for MyAcct contains the old inbox receipts.
    // Whereas recordbox for MyNym contains the old payments (in and out.)
    // In the case of the latter, the NYM must be passed as the ACCT...
    //
    // Meaning: there are TWO record boxes.
    //
    OTAPI_Wrap::Output(0, "\n Clearing archived Nym-related records (" + strMyNymID + ")... \n");
    int32_t nNymRecords = details_clear_records(strServerID, strMyNymID, strMyNymID);
    OTAPI_Wrap::Output(0, "--------------------------------------------------------------\n");
    OTAPI_Wrap::Output(0, "\nClearing archived Account-related records (" + MyAcct + ")... \n");
    int32_t nAcctRecords = details_clear_records(strServerID, strMyNymID, MyAcct);

    if (2 == (nNymRecords + nAcctRecords))
    {
        return 1; // success.
    }

    return -1;
}


OT_COMMAND_OT int32_t details_clear_expired(const string & strServerID, const string & strMyNymID)
{
    bool bTrue = true;
    bool bCleared = OTAPI_Wrap::ClearExpired(strServerID, strMyNymID, 0, bTrue); // nIndex=0 (ignored when clearing all), ClearAll = true.

    return bCleared ? 1 : -1;
}


OT_COMMAND_OT int32_t main_clear_expired()
{
    OTAPI_Wrap::Output(0, " Usage:      opentxs clearexpired\n\n");

    // CLEAR EXPIRED BOX
    //
    if (VerifyExists("MyNym") && VerifyExists("Server"))
    {
        string strMyNymID = MyNym;
        string strServerID = Server;

        //
        // expiredBox for MyNym contains the old payments (in and out.)
        //
        OTAPI_Wrap::Output(0, "\n Clearing archived Nym-related expired records (" + strMyNymID + ")... \n");

        return details_clear_expired(strServerID, strMyNymID);
    }

    return -1;
}


// Don't use this unless you really only need one expired record.
// Instead, use the function below it. (Otherwise you'll be
// loading the expired box from storage for EACH record, instead
// of loading it once for ALL the expired records in your loop.)
//
OT_COMMAND_OT int32_t details_show_expired(const string & strServerID, const string & strMyNymID, const int32_t nIndex)
{
    string strExpiredBox = OTAPI_Wrap::LoadExpiredBox(strServerID, strMyNymID); // Returns NULL, or an expired box.

    if (!VerifyStringVal(strExpiredBox))
    {
        OTAPI_Wrap::Output(0, "\n\n details_show_expired: OT_API_LoadExpiredBox: Failed.\n\n");
        return false;
    }

    // Success!
    return details_show_expired(strServerID, strMyNymID, nIndex, strExpiredBox);
}


// TODO: This is based on details_show_record which assumes it can contain asset inbox records as well
// as payment inbox records. But in fact, the expired box can ONLY contain payment records, not asset
// account records. So at some point, we will want to update this function to use the Instrument calls
// instead of the typical transaction calls, since that is more appropriate in this case. In fact we
// will also want to update details_show_record to do the same thing, in cases where the nymID and
// the account ID are the same.
//
OT_COMMAND_OT int32_t details_show_expired(const string & strServerID, const string & strMyNymID, const int32_t nIndex, const string & strExpiredBox)
{
    if (!VerifyStringVal(strExpiredBox))
    {
        OTAPI_Wrap::Output(0, "\n\n details_show_expired: strExpiredBox is empty.\n(Need to load it first before calling this function.)\n\n");
        return false;
    }

    // Success!
    //
    string strTrans = OTAPI_Wrap::Ledger_GetTransactionByIndex(strServerID, strMyNymID, strMyNymID, strExpiredBox, nIndex);
    int64_t lTransID = OTAPI_Wrap::Ledger_GetTransactionIDByIndex(strServerID, strMyNymID, strMyNymID, strExpiredBox, nIndex);
    int64_t lRefNum = OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(strServerID, strMyNymID, strMyNymID, strTrans);
    int64_t lAmount = OTAPI_Wrap::Transaction_GetAmount(strServerID, strMyNymID, strMyNymID, strTrans);
    string strType = OTAPI_Wrap::Transaction_GetType(strServerID, strMyNymID, strMyNymID, strTrans);
    string strSenderUserID = OTAPI_Wrap::Transaction_GetSenderUserID(strServerID, strMyNymID, strMyNymID, strTrans);
    string strSenderAcctID = OTAPI_Wrap::Transaction_GetSenderAcctID(strServerID, strMyNymID, strMyNymID, strTrans);
    string strRecipientUserID = OTAPI_Wrap::Transaction_GetRecipientUserID(strServerID, strMyNymID, strMyNymID, strTrans);
    string strRecipientAcctID = OTAPI_Wrap::Transaction_GetRecipientAcctID(strServerID, strMyNymID, strMyNymID, strTrans);

    string strUserID = VerifyStringVal(strSenderUserID) ? strSenderUserID : strRecipientUserID;
    string strAcctID = VerifyStringVal(strSenderAcctID) ? strSenderAcctID : strRecipientAcctID;

    bool bUserIDExists = VerifyStringVal(strUserID);
    bool bAcctIDExists = VerifyStringVal(strAcctID);

    string strNewlineSeparator = "";

    if (bUserIDExists || bAcctIDExists)
    {
        strNewlineSeparator = "\n                                 |";
    }

    string strSeparator = (!bUserIDExists && !bAcctIDExists) ? "" : strNewlineSeparator;

    string strUserDenoter = (bUserIDExists ? "U:" : "");
    string strAcctDenoter = (bAcctIDExists ? "A:" : "");

    string strAssetTypeID = bAcctIDExists ? OTAPI_Wrap::GetAccountWallet_AssetTypeID(strAcctID) : "";

    string strAmount = VerifyIntVal(lAmount) ? (VerifyStringVal(strAssetTypeID) ? OTAPI_Wrap::FormatAmount(strAssetTypeID, lAmount) : to_string(lAmount)) : "UNKNOWN_AMOUNT";

    OTAPI_Wrap::Output(0, to_string(nIndex) + "    ");
    OTAPI_Wrap::Output(0, strAmount + (strAmount.size() < 3 ? "    " : "   "));
    OTAPI_Wrap::Output(0, strType);
    OTAPI_Wrap::Output(0, strType.size() > 10 ? " " : "    ");
    OTAPI_Wrap::Output(0, to_string(lTransID) + (to_string(lTransID).size() < 2 ? "    " : "   "));
    OTAPI_Wrap::Output(0, to_string(lRefNum) + (to_string(lRefNum).size() > 2 ? "  " : " ") + "|");
    OTAPI_Wrap::Output(0, strUserDenoter + strUserID + strSeparator + strAcctDenoter + strAcctID + "\n");

    return true;
}


OT_COMMAND_OT int32_t details_show_expired_records(const string & strServerID, const string & strMyNymID)
{
    string strExpiredBox = OTAPI_Wrap::LoadExpiredBox(strServerID, strMyNymID); // Returns NULL, or an expired box.

    if (!VerifyStringVal(strExpiredBox))
    {
        OTAPI_Wrap::Output(0, "\n\n details_show_expired_records: OT_API_LoadExpiredBox: Failed.\n\n");
        return -1;
    }
    // Success!
    OTAPI_Wrap::Output(0, "\n\n"); // stderr
    //  print(strExpiredBox)      // stdout

    int32_t nCount = OTAPI_Wrap::Ledger_GetCount(strServerID, strMyNymID, strMyNymID, strExpiredBox);

    if (VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "SHOW EXPIRED RECORDS: \n\n");
        OTAPI_Wrap::Output(0, "Idx  Amt  Type        Txn# InRef#|User / Acct\n");
        OTAPI_Wrap::Output(0, "---------------------------------|(from or to)\n");

        for (int32_t nIndex = 0; nIndex < nCount; ++nIndex)
        {
            if (!details_show_expired(strServerID, strMyNymID, nIndex, strExpiredBox))
            {
                OTAPI_Wrap::Output(0, "details_show_expired_records: Error calling details_show_expired.\n");
                return -1;
            }
        } // for
    } // VerifyIntVal (nCount)

    return 1;
}


OT_COMMAND_OT int32_t main_show_expired()
{
    string strLocation = "main_show_expired";

    // SHOW EXPIRED RECORD BOX
    //
    if (VerifyExists("MyNym") && VerifyExists("Server"))
    {
        string strMyNymID = MyNym;
        string strServerID = Server;

        // expiredbox for MyNym contains the old payments (in and out.)

        OTAPI_Wrap::Output(0, "\n\nNote: OT is completely done with these expired records. A proper GUI will sweep them out\nperiodically and archive them somewhere, or just erase them. All you can do at the\ncommand line (using this tool) is view them, or erase them using: opentxs clearexpired \n\n");
        OTAPI_Wrap::Output(0, "\nArchived Nym-related expired records (" + strMyNymID + "): \n");

        return details_show_expired_records(strServerID, strMyNymID);
    }

    return -1;
}


OT_COMMAND_OT int32_t main_show_inbox()
{

    // SHOW INBOX
    //
    // Load an asset account's inbox from local storage and display it on the screen.
    //

    if (VerifyExists("MyAcct"))
    {

        // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
        //
        string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

        if (!VerifyStringVal(strMyNymID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
            return -1;
        }

        // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
        //
        string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);

        if (!VerifyStringVal(strServerID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find Server ID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Server based on the account.\n\n");
            return -1;
        }
        // ***************************************************************

        string strInbox = OTAPI_Wrap::LoadInbox(strServerID, strMyNymID, MyAcct); // Returns NULL, or an inbox.

        if (!VerifyStringVal(strInbox))
        {
            OTAPI_Wrap::Output(0, "\n Unable to load asset account inbox. ( " + MyAcct + " )\n Perhaps it doesn't exist yet?\n\n");
            return -1;
        }
        else // Success!
        {
            OTAPI_Wrap::Output(0, "\n"); // stderr
            //          print(strInbox)          // stdout

            int32_t nCount = OTAPI_Wrap::Ledger_GetCount(strServerID, strMyNymID, MyAcct, strInbox);

            if (VerifyIntVal(nCount))
            {
                if (nCount > 0)
                {
                    OTAPI_Wrap::Output(0, "Show inbox for an asset account  (" + MyAcct + "): \n");
                    OTAPI_Wrap::Output(0, "Idx  Amt  Type        Txn# InRef#|User / Acct\n");
                    OTAPI_Wrap::Output(0, "---------------------------------|(from or to)\n");

                    for (int32_t nIndex = 0; nIndex < nCount; ++nIndex)
                    {
                        string strTrans = OTAPI_Wrap::Ledger_GetTransactionByIndex(strServerID, strMyNymID, MyAcct, strInbox, nIndex);
                        int64_t lTransID = OTAPI_Wrap::Ledger_GetTransactionIDByIndex(strServerID, strMyNymID, MyAcct, strInbox, nIndex);
                        int64_t lRefNum = OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(strServerID, strMyNymID, MyAcct, strTrans);
                        int64_t lAmount = OTAPI_Wrap::Transaction_GetAmount(strServerID, strMyNymID, MyAcct, strTrans);
                        string strType = OTAPI_Wrap::Transaction_GetType(strServerID, strMyNymID, MyAcct, strTrans);
                        string strSenderUserID = OTAPI_Wrap::Transaction_GetSenderUserID(strServerID, strMyNymID, MyAcct, strTrans);
                        string strSenderAcctID = OTAPI_Wrap::Transaction_GetSenderAcctID(strServerID, strMyNymID, MyAcct, strTrans);
                        string strRecipientUserID = OTAPI_Wrap::Transaction_GetRecipientUserID(strServerID, strMyNymID, MyAcct, strTrans);
                        string strRecipientAcctID = OTAPI_Wrap::Transaction_GetRecipientAcctID(strServerID, strMyNymID, MyAcct, strTrans);

                        string strUserID = VerifyStringVal(strSenderUserID) ? strSenderUserID : strRecipientUserID;
                        string strAcctID = VerifyStringVal(strSenderAcctID) ? strSenderAcctID : strRecipientAcctID;

                        bool bUserIDExists = VerifyStringVal(strUserID);
                        bool bAcctIDExists = VerifyStringVal(strAcctID);

                        string strNewlineSeparator = "";

                        if (bUserIDExists || bAcctIDExists)
                        {
                            strNewlineSeparator = "\n                                 |";
                        }

                        string strSeparator = (!bUserIDExists && !bAcctIDExists) ? "" : strNewlineSeparator;

                        string strUserDenoter = (bUserIDExists ? "U:" : "");
                        string strAcctDenoter = (bAcctIDExists ? "A:" : "");

                        string strAssetTypeID = bAcctIDExists ? OTAPI_Wrap::GetAccountWallet_AssetTypeID(strAcctID) : "";

                        string strAmount = VerifyIntVal(lAmount) ? (VerifyStringVal(strAssetTypeID) ? OTAPI_Wrap::FormatAmount(strAssetTypeID, lAmount) : to_string(lAmount)) : "UNKNOWN_AMOUNT";

                        OTAPI_Wrap::Output(0, to_string(nIndex) + "    ");
                        OTAPI_Wrap::Output(0, strAmount + (strAmount.size() < 3 ? "    " : "   "));
                        OTAPI_Wrap::Output(0, strType);
                        OTAPI_Wrap::Output(0, strType.size() > 10 ? " " : "    ");
                        OTAPI_Wrap::Output(0, to_string(lTransID) + (to_string(lTransID).size() < 2 ? "    " : "   "));
                        OTAPI_Wrap::Output(0, to_string(lRefNum) + (to_string(lRefNum).size() > 2 ? "  " : " ") + "|");
                        OTAPI_Wrap::Output(0, strUserDenoter + strUserID + strSeparator + strAcctDenoter + strAcctID + "\n");
                    } // for

                    OTAPI_Wrap::Output(0, "\n For the above, try: accepttransfers, acceptreceipts, acceptinbox, acceptmoney, or acceptall.\n");
                }
                else
                {
                    OTAPI_Wrap::Output(0, "\n Asset account inbox ( " + MyAcct + " ) is empty.\n");
                }

            } // VerifyIntVal (nCount)

            return 1;
        }
    }
    return -1;
}


OT_COMMAND_OT int32_t main_show_outbox()
{

    // SHOW OUTPUT
    //
    // Load an asset account's outbox from local storage and display it on the screen.
    //
    string strUsage = "-----------------------------------------------\nUSAGE:   outbox --myacct MY_ACCT_ID\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyAcct"))
    {

        // HERE, WE LOOK UP THE NYM ID, BASED ON THE ACCOUNT ID.
        //
        string strMyNymID = OTAPI_Wrap::GetAccountWallet_NymID(MyAcct);

        if (!VerifyStringVal(strMyNymID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find NymID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Nym based on the account.\n\n");
            return -1;
        }

        // HERE, WE LOOK UP THE SERVER ID, BASED ON THE ACCOUNT ID.
        //
        string strServerID = OTAPI_Wrap::GetAccountWallet_ServerID(MyAcct);

        if (!VerifyStringVal(strServerID))
        {
            OTAPI_Wrap::Output(0, "Failure: Unable to find Server ID based on myacct. Use: --myacct ACCT_ID\n");
            OTAPI_Wrap::Output(0, "The designated asset account must be yours. OT will find the Server based on the account.\n\n");
            return -1;
        }
        // ***************************************************************

        string strOutbox = OTAPI_Wrap::LoadOutbox(strServerID, strMyNymID, MyAcct); // Returns NULL, or an outbox.

        if (!VerifyStringVal(strOutbox))
        {
            OTAPI_Wrap::Output(0, "\n\n OT_API_LoadOutbox: Failed.\n\n");
            return -1;
        }
        else // Success!
        {
            OTAPI_Wrap::Output(0, "\n"); // stderr
            //          print(strOutbox)         // stdout

            int32_t nCount = OTAPI_Wrap::Ledger_GetCount(strServerID, strMyNymID, MyAcct, strOutbox);

            if (VerifyIntVal(nCount))
            {
                OTAPI_Wrap::Output(0, "===> SHOW OUTBOX: \n");

                if (nCount <= 0)
                {
                    OTAPI_Wrap::Output(0, "\nAsset account outbox is empty for account: " + MyAcct + "\n\n--------------------------------------------\n");
                }
                else
                {
                    OTAPI_Wrap::Output(0, "\nIdx  Amt  Type        Txn# InRef#|User / Acct\n");
                    OTAPI_Wrap::Output(0, "---------------------------------|(from or to)\n");

                    for (int32_t nIndex = 0; nIndex < nCount; ++nIndex)
                    {
                        string strTrans = OTAPI_Wrap::Ledger_GetTransactionByIndex(strServerID, strMyNymID, MyAcct, strOutbox, nIndex);
                        int64_t lTransID = OTAPI_Wrap::Ledger_GetTransactionIDByIndex(strServerID, strMyNymID, MyAcct, strOutbox, nIndex);
                        int64_t lRefNum = OTAPI_Wrap::Transaction_GetDisplayReferenceToNum(strServerID, strMyNymID, MyAcct, strTrans);
                        int64_t lAmount = OTAPI_Wrap::Transaction_GetAmount(strServerID, strMyNymID, MyAcct, strTrans);
                        string strType = OTAPI_Wrap::Transaction_GetType(strServerID, strMyNymID, MyAcct, strTrans);
                        string strSenderUserID = OTAPI_Wrap::Transaction_GetSenderUserID(strServerID, strMyNymID, MyAcct, strTrans);
                        string strSenderAcctID = OTAPI_Wrap::Transaction_GetSenderAcctID(strServerID, strMyNymID, MyAcct, strTrans);
                        string strRecipientUserID = OTAPI_Wrap::Transaction_GetRecipientUserID(strServerID, strMyNymID, MyAcct, strTrans);
                        string strRecipientAcctID = OTAPI_Wrap::Transaction_GetRecipientAcctID(strServerID, strMyNymID, MyAcct, strTrans);

                        string strUserID = strRecipientUserID;
                        string strAcctID = strRecipientAcctID;

                        bool bUserIDExists = VerifyStringVal(strUserID);
                        bool bAcctIDExists = VerifyStringVal(strAcctID);

                        string strNewlineSeparator = "";

                        if (bUserIDExists || bAcctIDExists)
                        {
                            strNewlineSeparator = "\n                                 |";
                        }

                        string strSeparator = (!bUserIDExists && !bAcctIDExists) ? "" : strNewlineSeparator;

                        string strUserDenoter = (bUserIDExists ? "U:" : "");
                        string strAcctDenoter = (bAcctIDExists ? "A:" : "");

                        string strAssetTypeID = bAcctIDExists ? OTAPI_Wrap::GetAccountWallet_AssetTypeID(strAcctID) : "";

                        string strAmount = VerifyIntVal(lAmount) ? (VerifyStringVal(strAssetTypeID) ? OTAPI_Wrap::FormatAmount(strAssetTypeID, lAmount) : to_string(lAmount)) : "UNKNOWN_AMOUNT";

                        OTAPI_Wrap::Output(0, to_string(nIndex) + "    ");
                        OTAPI_Wrap::Output(0, strAmount + (strAmount.size() < 3 ? "    " : "   "));
                        OTAPI_Wrap::Output(0, strType);
                        OTAPI_Wrap::Output(0, strType.size() > 10 ? " " : "    ");
                        OTAPI_Wrap::Output(0, to_string(lTransID) + (to_string(lTransID).size() < 2 ? "    " : "   "));
                        OTAPI_Wrap::Output(0, to_string(lRefNum) + (to_string(lRefNum).size() > 2 ? "  " : " ") + "|");
                        OTAPI_Wrap::Output(0, strUserDenoter + strUserID + strSeparator + strAcctDenoter + strAcctID + "\n");
                    } // for
                }
            } // VerifyIntVal (nCount)

            return 1;
        }
    }
    return -1;
}


OT_COMMAND_OT int32_t show_mail_message(const string & strMyNymID, const int32_t nIndex, const bool bShowContents)
{
    bool bMailVerified = OTAPI_Wrap::Nym_VerifyMailByIndex(strMyNymID, nIndex);

    if (!VerifyBoolVal(bMailVerified))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_Nym_VerifyMailByIndex at Index: " + to_string(nIndex) + "\n");
        return false;
    }

    if (!bMailVerified) // 1 meaning OT_TRUE.
    {
        print("UNVERIFIED mail! At index: " + to_string(nIndex));
        //      return false;
    }

    else
    {
        print("------------------------------\nVerified mail at index: " + to_string(nIndex));
    }

    string strMailServerID = OTAPI_Wrap::GetNym_MailServerIDByIndex(strMyNymID, nIndex);
    string strMailSenderID = OTAPI_Wrap::GetNym_MailSenderIDByIndex(strMyNymID, nIndex);
    string strMailContents = OTAPI_Wrap::GetNym_MailContentsByIndex(strMyNymID, nIndex);

    if (VerifyStringVal(strMailSenderID))
    {
        string strName = OTAPI_Wrap::GetNym_Name(strMailSenderID);
        if (!VerifyStringVal(strName)) { strName = ""; }
        print("Mail from: " + strMailSenderID + " \"" + strName + "\" ");
    }
    if (VerifyStringVal(strMailServerID))
    {
        string strName = OTAPI_Wrap::GetServer_Name(strMailServerID);
        if (!VerifyStringVal(strName)) { strName = ""; }
        print("Server ID: " + strMailServerID + " \"" + strName + "\" ");
    }
    if (bShowContents && VerifyStringVal(strMailContents))
    {
        print("Contents:\n" + strMailContents + "\n");
    }

    return true;
}


OT_COMMAND_OT int32_t details_del_mail(const string & strMyNymID, const string & strIndices)
{

    int32_t nCount = OTAPI_Wrap::GetNym_MailCount(strMyNymID);

    if (!VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_GetNym_MailCount for Nym: " + strMyNymID + "\n");
        return -1;
    }

    if (0 == nCount)
    {
        OTAPI_Wrap::Output(0, "\n(Mail is empty.)\n\n");
        return 0;
    }

    bool bIndices = VerifyStringVal(strIndices);
    bool bDeleteAll = false;

    if (bIndices && ("all" == strIndices))
    {
        bDeleteAll = true;
    }

    int32_t nIndicesCount = (bIndices && !bDeleteAll) ? OTAPI_Wrap::NumList_Count(strIndices) : 0;

    // If we're not deleting ALL, then we must be deleting SPECIFC indices.
    // But no specific indices were supplied!
    // Therefore, error.
    //
    if (!bDeleteAll && (nIndicesCount < 1))
    {
        OTAPI_Wrap::Output(0, "Problem: You're apparently not deleting \"all\" indices, but neither have you selected SPECIFIC indices.\n Try adding: --args \"indices 4,6,7\" (for deleting the messages at indices 4, 6, and 7, for example.)\n\n");
        return -1;
    }

    int32_t nReturnVal = 1;

    for (int32_t nIndex = (nCount - 1); nIndex >= 0; --nIndex)
    {

        // If we're not deleting "all" (i.e. we're deleting specific indices)...
        // and the current index doesn't appear on that specified list, then continue...
        //
        if (!bDeleteAll && !OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex)))
        {
            // We skip any indices that the user isn't trying to delete.
            //          continue   // apparently not supported by the language.
        }

        // Let's try to remove it...
        //
        else if (OTAPI_Wrap::Nym_RemoveMailByIndex(strMyNymID, nIndex))
        {
            OTAPI_Wrap::Output(0, "Deleted mail at index " + to_string(nIndex) + " for nym: " + strMyNymID + " \n");
        }
        else
        {
            OTAPI_Wrap::Output(0, "Error while trying to delete mail at index " + to_string(nIndex) + " for nym: " + strMyNymID + " \n");
            nReturnVal = -1;
        }
    } // for

    return nReturnVal;
}


OT_COMMAND_OT int32_t main_del_mail()
{
    string strUsage = "USAGE:   delmail --mynym MY_NYM_ID --args \"index 5\"  (To delete message 5.)\n Also, try: --args \"indices all\" (for all messages)\n As well as: --args \"indices 3,5,6\" (for messages 3, 5, and 6)\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym"))
    {
        string strIndices = "";

        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "index 5 "
            //

            string strIndex = OT_CLI_GetValueByKey(Args, "index");

            if (VerifyStringVal(strIndex))
            {
                strIndices = strIndex;
            }

            string strTempIndices = OT_CLI_GetValueByKey(Args, "indices");

            if (VerifyStringVal(strTempIndices))
            {
                strIndices = strTempIndices;
            }
        }

        int32_t nDetails = details_del_mail(MyNym, strIndices);
        return nDetails;
    }

    return -1;
}


OT_COMMAND_OT int32_t main_show_mail()
{
    string strUsage = "USAGE:   mail --mynym MY_NYM_ID   (To list all the mail messages for mynym.)\n Also:   mail --args \"index 5\"  (To examine a specific message.)\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (!VerifyExists("MyNym"))
    {
        return -1;
    }

    int32_t nCount = OTAPI_Wrap::GetNym_MailCount(MyNym);

    if (!VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_GetNym_MailCount for Nym: " + MyNym + "\n");
        return -1;
    }

    if (0 == nCount)
    {
        OTAPI_Wrap::Output(0, "\n(Mail is empty.)\n\n");
        return 0;
    }

    string strIndex = "";
    int32_t nIndex = -1;

    if (VerifyExists("Args", false))
    {
        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "index 5 "
        //
        strIndex = OT_CLI_GetValueByKey(Args, "index");

        if (VerifyStringVal(strIndex))
        {
            nIndex = to_int(strIndex);
        }
    }

    //
    int32_t nReturnVal = 1;

    if (nIndex > -1)
    {
        nReturnVal = show_mail_message(MyNym, nIndex, true) ? 1 : -1;
    }
    else
    {
        OTAPI_Wrap::Output(0, "\n Mail contents:\n\n");

        for (nIndex = 0; nIndex < nCount; ++nIndex)
        {
            if (!show_mail_message(MyNym, nIndex, false))
            {
                OTAPI_Wrap::Output(0, "show_mail_message returned false. I'll finish out the loop, but that's weird.\n");
                nReturnVal = -1;
            }
        }
    }
    return nReturnVal;
}

//pScript->chai.add(fun(&OTAPI_Wrap::Nym_RemoveMailByIndex), "OT_API_Nym_RemoveMailByIndex");


OT_COMMAND_OT int32_t show_outmail_message(const string & strMyNymID, const int32_t nIndex, const bool bShowContents)
{
    bool bMailVerified = OTAPI_Wrap::Nym_VerifyOutmailByIndex(strMyNymID, nIndex);

    if (!VerifyBoolVal(bMailVerified))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_Nym_VerifyOutmailByIndex at Index: " + to_string(nIndex) + "\n");
        return false;
    }

    if (!bMailVerified) // 1 meaning OT_TRUE.
    {
        print("UNVERIFIED sent (outgoing) mail! At index: " + to_string(nIndex) + "\n");
        //      return false;
    }

    else
    {
        print("--------------------------------------------------------\nVerified outmail at index: " + to_string(nIndex));
    }

    string strMailServerID = OTAPI_Wrap::GetNym_OutmailServerIDByIndex(strMyNymID, nIndex);
    string strMailRecipientID = OTAPI_Wrap::GetNym_OutmailRecipientIDByIndex(strMyNymID, nIndex);
    string strMailContents = OTAPI_Wrap::GetNym_OutmailContentsByIndex(strMyNymID, nIndex);

    if (VerifyStringVal(strMailRecipientID))
    {
        print("Mail was sent to: " + strMailRecipientID);
    }
    if (VerifyStringVal(strMailServerID))
    {
        print("At server ID: " + strMailServerID);
    }
    if (bShowContents && VerifyStringVal(strMailContents))
    {
        print("Contents:\n" + strMailContents + "\n");
    }
    return true;
}


OT_COMMAND_OT int32_t main_show_outmail()
{
    string strUsage = "USAGE:   outmail --mynym MY_NYM_ID   (To list all the sent mail messages for mynym.)\n Also:   outmail --args \"index 5\"  (To examine a specific message.)\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (!VerifyExists("MyNym"))
    {
        return -1;
    }

    int32_t nCount = OTAPI_Wrap::GetNym_OutmailCount(MyNym);

    if (!VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_GetNym_OutmailCount for Nym: " + MyNym + "\n");
        return -1;
    }

    if (0 == nCount)
    {
        OTAPI_Wrap::Output(0, "\n(Outmail box is empty.)\n\n");
        return 0;
    }

    string strIndex = "";
    int32_t nIndex = -1;

    if (VerifyExists("Args", false))
    {
        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "index 5 "
        //
        strIndex = OT_CLI_GetValueByKey(Args, "index");

        if (VerifyStringVal(strIndex))
        {
            nIndex = to_int(strIndex);
        }
    }

    int32_t nReturnVal = 1;

    if (nIndex > -1)
    {
        nReturnVal = show_outmail_message(MyNym, nIndex, true) ? 1 : -1;
    }
    else
    {
        for (nIndex = 0; nIndex < nCount; ++nIndex)
        {
            if (!show_outmail_message(MyNym, nIndex, false))
            {
                OTAPI_Wrap::Output(0, "show_outmail_message returned false. I'll finish out the loop, but that's weird.\n");
                nReturnVal = -1;
            }
        }
    }

    return nReturnVal;
}


OT_COMMAND_OT int32_t details_del_outmail(const string & strMyNymID, const string & strIndices)
{

    int32_t nCount = OTAPI_Wrap::GetNym_OutmailCount(strMyNymID);

    if (!VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_GetNym_OutmailCount for Nym: " + strMyNymID + "\n");
        return -1;
    }

    if (0 == nCount)
    {
        OTAPI_Wrap::Output(0, "\n(Outgoing mail is empty.)\n\n");
        return 0;
    }

    bool bIndices = VerifyStringVal(strIndices);
    bool bDeleteAll = false;

    if (bIndices && ("all" == strIndices))
    {
        bDeleteAll = true;
    }

    int32_t nIndicesCount = (bIndices && !bDeleteAll) ? OTAPI_Wrap::NumList_Count(strIndices) : 0;

    // If we're not deleting ALL, then we must be deleting SPECIFC indices.
    // But no specific indices were supplied!
    // Therefore, error.
    //
    if (!bDeleteAll && (nIndicesCount < 1))
    {
        OTAPI_Wrap::Output(0, "Problem: You're apparently not deleting \"all\" indices, but neither have you selected SPECIFIC indices.\n Try adding: --args \"indices 4,6,7\" (for deleting the outgoing messages at indices 4, 6, and 7, for example.)\n\n");
        return -1;
    }

    int32_t nReturnVal = 1;

    for (int32_t nIndex = (nCount - 1); nIndex >= 0; --nIndex)
    {

        // If we're not deleting "all" (i.e. we're deleting specific indices)...
        // and the current index doesn't appear on that specified list, then continue...
        //
        if (!bDeleteAll && !OTAPI_Wrap::NumList_VerifyQuery(strIndices, to_string(nIndex)))
        {
            // We skip any indices that the user isn't trying to delete.
            //          continue // apparently not supported by the language.
        }

        // Let's try to remove it...
        //
        else if (OTAPI_Wrap::Nym_RemoveOutmailByIndex(strMyNymID, nIndex))
        {
            OTAPI_Wrap::Output(0, "Deleted outgoing mail at index " + to_string(nIndex) + " for nym: " + strMyNymID + " \n");
        }
        else
        {
            OTAPI_Wrap::Output(0, "Error while trying to delete outgoing mail at index " + to_string(nIndex) + " for nym: " + strMyNymID + " \n");
            nReturnVal = -1;
        }
    } // for

    return nReturnVal;
}


OT_COMMAND_OT int32_t main_del_outmail()
{
    string strUsage = "USAGE:   deloutmail --mynym MY_NYM_ID --args \"index 5\"  (To delete outmail message 5.)\n Also, try: --args \"indices all\" (for all outgoing messages)\n As well as: --args \"indices 3,5,6\" (for outgoing messages 3, 5, and 6)\n\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (VerifyExists("MyNym"))
    {
        string strIndices = "";

        if (VerifyExists("Args", false))
        {
            // std::string OT_CLI_GetValueByKey(const std::string str_Args,
            //                                  const std::string str_key)
            //
            // OPTION:   --args "key value key value"
            // EXAMPLE:  --args "index 5 "
            //

            string strIndex = OT_CLI_GetValueByKey(Args, "index");

            if (VerifyStringVal(strIndex))
            {
                strIndices = strIndex;
            }

            string strTempIndices = OT_CLI_GetValueByKey(Args, "indices");

            if (VerifyStringVal(strTempIndices))
            {
                strIndices = strTempIndices;
            }
        }

        int32_t nDetails = details_del_outmail(MyNym, strIndices);
        return nDetails;
    }

    return -1;
}


OT_COMMAND_OT bool show_outpayment(const string & strMyNym, const int32_t nIndex, const bool bShowInFull)
{
    bool bMailVerified = OTAPI_Wrap::Nym_VerifyOutpaymentsByIndex(strMyNym, nIndex);

    if (!VerifyBoolVal(bMailVerified))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_Nym_VerifyOutpaymentsByIndex at Index: " + to_string(nIndex) + "\n");
        return false;
    }

    if (!bMailVerified) // 1 meaning OT_TRUE.
    {
        print("UNVERIFIED sent (outgoing) payment! At index: " + to_string(nIndex));
        //      return false;
    }

    else
    {
        print("\n----------------------------------------------\n(index " + to_string(nIndex) + ")");
    }

    string strMailServerID = OTAPI_Wrap::GetNym_OutpaymentsServerIDByIndex(strMyNym, nIndex);
    string strMailRecipientID = OTAPI_Wrap::GetNym_OutpaymentsRecipientIDByIndex(strMyNym, nIndex);
    string strMailContents = OTAPI_Wrap::GetNym_OutpaymentsContentsByIndex(strMyNym, nIndex);

    if (VerifyStringVal(strMailContents))
    {
        int64_t lPaymentAmount = OTAPI_Wrap::Instrmnt_GetAmount(strMailContents);
        string strPaymentAmount = "UNKNOWN_PAYMENT_AMOUNT";

        if (VerifyIntVal(lPaymentAmount))
        {
            strPaymentAmount = to_string(lPaymentAmount);
        }

        string strPaymentAssetID = OTAPI_Wrap::Instrmnt_GetAssetID(strMailContents);
        string strPaymentType = OTAPI_Wrap::Instrmnt_GetType(strMailContents);

        string strFormatted = "";
        string strAssetTypeName = "";

        string strRecipientString = "";
        string strServerString = "";

        if (VerifyStringVal(strMailRecipientID))
        {
            string strName = OTAPI_Wrap::GetNym_Name(strMailRecipientID);
            if (!VerifyStringVal(strName)) { strName = ""; }
            strRecipientString = "Payment sent to: " + strMailRecipientID + " \"" + strName + "\" ";
        }
        if (VerifyStringVal(strMailServerID))
        {
            string strName = OTAPI_Wrap::GetServer_Name(strMailServerID);
            if (!VerifyStringVal(strName)) { strName = ""; }
            strServerString = "   At server ID: " + strMailServerID + " \"" + strName + "\" ";
        }

        if (VerifyStringVal(strPaymentAssetID))
        {
            strAssetTypeName = OTAPI_Wrap::GetAssetType_Name(strPaymentAssetID);
            if (!VerifyStringVal(strAssetTypeName)) { strAssetTypeName = ""; }
        }
        else
        {
            strPaymentAssetID = "UNKNOWN_ASSET_ID";
        }

        if (VerifyIntVal(lPaymentAmount))
        {
            if (!VerifyStringVal(strPaymentType)) { strPaymentType = "UNKNOWN_PAYMENT_TYPE"; }
            string strTempFormat;
            if ((lPaymentAmount > -1))
            {
                strTempFormat = OTAPI_Wrap::FormatAmount(strPaymentAssetID, lPaymentAmount);
            }
            if (!VerifyStringVal(strTempFormat))  { strTempFormat = strPaymentAmount; }

            strFormatted = "( " + strPaymentType + ": " + strTempFormat + " )";
        }

        print("         Amount: " + strPaymentAmount + "  " + strFormatted);
        print(strRecipientString);
        print("  Of asset type: " + strPaymentAssetID + " \"" + strAssetTypeName + "\" ");
        print(strServerString);

        if (bShowInFull)
        {
            print("     Instrument: \n" + strMailContents + "\n");
        }
    }
    else
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_GetNym_OutpaymentsContentsByIndex at Index: " + to_string(nIndex) + "\n");
        return false;
    }

    return true;
}

OT_COMMAND_OT bool show_outpayment(const string & strMyNym, const int32_t nIndex)
{
    bool bShowInFull = true;

    return show_outpayment(strMyNym, nIndex, bShowInFull);
}


OT_COMMAND_OT int32_t main_show_outpayment()
{
    string strUsage = "USAGE:   outpayment --mynym MY_NYM_ID --args \"index 5\"   (for example)\nIf no index is specified, all outgoing payments are listed.\n";
    OTAPI_Wrap::Output(0, strUsage);

    if (!VerifyExists("MyNym"))
    {
        return -1;
    }

    string strIndex = "";
    int32_t nIndex = -1;

    if (VerifyExists("Args", false))
    {
        // std::string OT_CLI_GetValueByKey(const std::string str_Args,
        //                                  const std::string str_key)
        //
        // OPTION:   --args "key value key value"
        // EXAMPLE:  --args "index 5 "
        //
        strIndex = OT_CLI_GetValueByKey(Args, "index"); // OTNumList will be used for this value.

        if (VerifyStringVal(strIndex))
        {
            nIndex = to_int(strIndex);
        }
    }

    //
    int32_t nCount = OTAPI_Wrap::GetNym_OutpaymentsCount(MyNym);

    if (!VerifyIntVal(nCount))
    {
        OTAPI_Wrap::Output(0, "Error: bad result from OT_API_GetNym_OutpaymentsCount for Nym: " + MyNym + "\n");
        return -1;
    }

    if (0 == nCount)
    {
        OTAPI_Wrap::Output(0, "\nSent (outgoing) payments box is empty.\n\n");
        return 0;
    }

    if (!(nIndex < nCount))
    {
        OTAPI_Wrap::Output(0, "\nIndex (" + strIndex + ") out of bounds. (Acceptable range is 0 to " + to_string(nCount - 1) + ".)\n\n");
        return 0;
    }

    int32_t nReturnVal = 1;

    if (nIndex > -1)
    {
        if (!show_outpayment(MyNym, nIndex, true))  { nReturnVal = -1; }
    }
    else
    {
        OTAPI_Wrap::Output(0, "\n\n===> SHOW OUTGOING PAYMENTS:\n");

        for (nIndex = 0; nIndex < nCount; ++nIndex)
        {
            if (!show_outpayment(MyNym, nIndex, false))  { nReturnVal = -1; }
        }
    }
    return nReturnVal;
}


OT_COMMAND_OT int32_t main_add_server()
{
    OTAPI_Wrap::Output(0, "Please paste a server contract, followed by an EOF or a ~ by itself on a blank line:\n\n");

    // The reason we accept the tilde ~ on a blank line by itself, is because
    // the EOF, while it works, causes us not to be able to read any more input
    // from stdin. Stdin is considered "closed" for the duration of the run.
    // So the tilde allows us to read multiple times without closing stdin.

    string strContract = OT_CLI_ReadUntilEOF();

    if (!VerifyStringVal(strContract))
    {
        OTAPI_Wrap::Output(0, "\n\n Sorry, You must input a server contract, in order to add it to your wallet.\n\n");
        return -1;
    }


    int32_t nAdded = OTAPI_Wrap::AddServerContract(strContract);

    if (1 != nAdded)
    {
        OTAPI_Wrap::Output(0, "\n\n Sorry, failed. Are you sure that was a server contract?\n\n");
        return -1;
    }

    OTAPI_Wrap::Output(0, "\n\n Success adding server contract to your wallet.\n\n");
    return 1;
}


OT_COMMAND_OT int32_t main_add_asset()
{
    OTAPI_Wrap::Output(0, "Please paste a currency contract, followed by an EOF or a ~ by itself on a blank line:\n\n");

    // The reason we accept the tilde ~ on a blank line by itself, is because
    // the EOF, while it works, causes us not to be able to read any more input
    // from stdin. Stdin is considered "closed" for the duration of the run.
    // So the tilde allows us to read multiple times without closing stdin.

    string strContract = OT_CLI_ReadUntilEOF();

    if (!VerifyStringVal(strContract))
    {
        OTAPI_Wrap::Output(0, "\n\n Sorry, You must input a currency contract, in order to add it to your wallet.\n\n");
        return -1;
    }


    int32_t nAdded = OTAPI_Wrap::AddAssetContract(strContract);

    if (1 != nAdded)
    {
        OTAPI_Wrap::Output(0, "\n\n Sorry, failed. Are you sure that was an asset contract?\n\n");
        return -1;
    }

    OTAPI_Wrap::Output(0, "\n\n Success adding asset contract to your wallet.\n\n");
    return 1;
}


OT_COMMAND_OT int32_t main_issue_asset()
{

    // Instantiate the "OT Made Easy" object.
    //
    MadeEasy madeEasy;


    string strUsage = concat("\n\nUsage: opentxs issueasset --server SERVER_ID --mynym NYM_ID\n\n",
        "       (NYM_ID must already be the 'contract' key on the new contract.)\n       See 'opentxs newasset' before running this script.\n\n");

    OTAPI_Wrap::Output(0, strUsage);


    if (VerifyExists("Server") && VerifyExists("MyNym"))
    {
        OTAPI_Wrap::Output(0, "Please paste a currency contract, followed by an EOF or a ~ by itself on a blank line:\n\n");

        // The reason we accept the tilde ~ on a blank line by itself, is because
        // the EOF, while it works, causes us not to be able to read any more input
        // from stdin. Stdin is considered "closed" for the duration of the run.
        // So the tilde allows us to read multiple times without closing stdin.

        string strContract = OT_CLI_ReadUntilEOF();

        if (!VerifyStringVal(strContract))
        {
            OTAPI_Wrap::Output(0, "\n\n Sorry, You must input a currency contract, in order to issue it on an OT server.\n\n");
            return -1;
        }

        if (!OTAPI_Wrap::IsNym_RegisteredAtServer(MyNym, Server))
        {
            // If the Nym's not registered at the server, then register him first.
            main_register_nym();
        }

        string strResponse = madeEasy.issue_asset_type(Server, MyNym, strContract);
        int32_t nStatus = VerifyMessageSuccess(strResponse);

        // NOTICE: No need here to deal with retries, timeouts, request number,
        // syncing transaction number, download / process nymbox, etc! It's all
        // handled at a lower level!  Instead, simply check for success or failure:
        //
        // -1 is error,
        //  0 is reply received: failure
        //  1 is reply received: success
        //
        switch (nStatus)
        {
        case 1:
            OTAPI_Wrap::Output(0, "\n\n SUCCESS in issue_asset! Server response:\n\n");
            print(strResponse); // stdout
            break;
        case 0:
            OTAPI_Wrap::Output(0, "\n\n FAILURE in issue_asset! Server response:\n\n");
            print(strResponse); // stdout
            break;
        default:
            OTAPI_Wrap::Output(0, "\n\nError in issue_asset! nStatus is: " + to_string(nStatus) + "\n");

            if (VerifyStringVal(strResponse))
            {
                OTAPI_Wrap::Output(0, "Server response:\n\n");
                print(strResponse); // stdout
            }
            break;
        }
        OTAPI_Wrap::Output(0, "\n\n"); //stderr

        return (0 == nStatus) ? -1 : nStatus;
    }

    return -1;
}
