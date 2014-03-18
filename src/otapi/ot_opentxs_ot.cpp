#include <stdafx.hpp>

#include "OTAPI.hpp"
#include "OT_ME.hpp"
#include "ot_command_ot.hpp"
#include "ot_made_easy_ot.hpp"
#include "ot_otapi_ot.hpp"
#include "ot_utility_ot.hpp"

using std::string;

#define OT_OPENTXS_OT

// ---------------------------------


typedef enum
{
    catAdmin = 1,
    catWallet = 2,
    catMisc = 3,
    catMarkets = 4,
    catAccounts = 5,
    catOtherUsers = 6,
    catInstruments = 7,
    catBaskets = 8,
    catNyms = 9,
} Category;

static string categoryName[] =
{
    "Category Error",
    "Advanced utilities",
    "The user wallet",
    "Misc",
    "Markets (bid/ask)",
    "Asset accounts",
    "Dealing with other users",
    "Financial instruments",
    "Basket currencies",
    "Pseudonyms"
};


typedef struct
{
    string command;
    int category;
} MapCategory;

MapCategory map_categories[] =
{
    { "acceptall", catAccounts },
    { "acceptinbox", catAccounts },
    { "acceptinvoices", catAccounts },
    { "acceptmoney", catAccounts },
    { "acceptpayments", catAccounts },
    { "acceptreceipts", catAccounts },
    { "accepttransfers", catAccounts },
    { "addasset", catWallet },
    { "addserver", catWallet },
    { "addsignature", catAdmin },
    { "balance", catAccounts },
    { "buyvoucher", catInstruments },
    { "cancel", catInstruments },
    { "changepw", catWallet },
    { "checknym", catOtherUsers },
    { "clearexpired", catMisc },
    { "clearrecords", catMisc },
    { "confirm", catInstruments },
    { "credentials", catNyms },
    { "decode", catAdmin },
    { "decrypt", catAdmin },
    { "delmail", catOtherUsers },
    { "deloutmail", catOtherUsers },
    { "deposit", catAccounts },
    { "discard", catInstruments },
    { "editacct", catWallet },
    { "editasset", catWallet },
    { "editnym", catWallet },
    { "editserver", catWallet },
    { "encode", catAdmin },
    { "encrypt", catAdmin },
    { "exchange", catBaskets },
    { "expired", catMisc },
    { "exportcash", catInstruments },
    { "exportnym", catWallet },
    { "getboxreceipt", catAdmin },
    { "getcontract", catAdmin },
    { "getmarkets", catMarkets },
    { "getmyoffers", catMarkets },
    { "getoffers", catMarkets },
    { "importcash", catInstruments },
    { "importnym", catWallet },
    { "inbox", catAccounts },
    { "issueasset", catAdmin },
    { "killoffer", catMarkets },
    { "killplan", catInstruments },
    { "mail", catOtherUsers },
    { "newacct", catAccounts },
    { "newasset", catAdmin },
    { "newbasket", catBaskets },
    { "newcred", catNyms },
    { "newkey", catAdmin },
    { "newnym", catNyms },
    { "newoffer", catMarkets },
    { "newserver", catAdmin },
    { "outbox", catAccounts },
    { "outmail", catOtherUsers },
    { "outpayment", catOtherUsers },
    { "pass_decrypt", catAdmin },
    { "pass_encrypt", catAdmin },
    { "paydividend", catMarkets },
    { "payinvoice", catOtherUsers },
    { "payments", catOtherUsers },
    { "propose", catInstruments },
    { "records", catMisc },
    { "refresh", catWallet },
    { "refreshacct", catAccounts },
    { "refreshnym", catNyms },
    { "register", catAdmin },
    { "revokecred", catNyms },
    { "sendcash", catOtherUsers },
    { "sendcheque", catOtherUsers },
    { "sendinvoice", catOtherUsers },
    { "sendmsg", catOtherUsers },
    { "sendvoucher", catOtherUsers },
    { "showaccounts", catWallet },
    { "showacct", catAccounts },
    { "showassets", catWallet },
    { "showbasket", catBaskets },
    { "showcred", catNyms },
    { "showincoming", catWallet },
    { "showmarkets", catMarkets },
    { "showmint", catAdmin },
    { "showmyoffers", catMarkets },
    { "shownym", catNyms },
    { "shownyms", catWallet },
    { "showoffers", catMarkets },
    { "showoutgoing", catWallet },
    { "showpayment", catOtherUsers },
    { "showpurse", catWallet },
    { "showservers", catWallet },
    { "sign", catAdmin },
    { "stat", catWallet },
    { "transfer", catAccounts },
    { "trigger", catInstruments },
    { "verifyreceipt", catAccounts },
    { "verifysig", catAdmin },
    { "withdraw", catInstruments },
    { "writecheque", catInstruments },
    { "writeinvoice", catInstruments },
    { "", 0 }
};

typedef struct
{
    string command;
    string helpText;
} MapHelp;

MapHelp map_help[] =
{
    { "acceptall", "accept all incoming transfers, receipts, payments, and invoices." },
    { "acceptinbox", "accept all incoming transfers and receipts in MyAcct's inbox." },
    { "acceptinvoices", "pay all invoices in MyNym's payments inbox." },
    { "acceptmoney", "accept all incoming transfers and payments into MyAcct." },
    { "acceptpayments", "accept all incoming payments in MyNym's payments inbox." },
    { "acceptreceipts", "accept all receipts in MyAcct's inbox." },
    { "accepttransfers", "accept all incoming transfers in MyAcct's inbox." },
    { "addasset", "paste an existing asset contract, import it into your wallet." },
    { "addserver", "paste an existing server contract, import it into your wallet." },
    { "addsignature", "add a signature to a contract without releasing others." },
    { "balance", "display balance for a specific account." },
    { "buyvoucher", "withdraw from myacct as a voucher (cashier's cheque.)" },
    { "cancel", "cancel a not-yet-cashed, outgoing instrument from outpayment box." },
    { "changepw", "change the master passphrase for the wallet." },
    { "checknym", "download a nym's public key based on his ID." },
    { "clearexpired", "clear all expired records." },
    { "clearrecords", "clear all archived records and receipts." },
    { "confirm", "confirm your agreement to a smart contract or payment plan." },
    { "credentials", "show the credentials for a specific nym." },
    { "decode", "OT-base64-decode out of armor." },
    { "decrypt", "decrypt ciphertext using nym's private key." },
    { "delmail", "delete an in-mail item." },
    { "deloutmail", "delete an out-mail item." },
    { "deposit", "deposit cash, cheque, voucher, or tokens." },
    { "discard", "discard a not-yet-cashed, incoming instrument from payments inbox." },
    { "editacct", "edit an asset account's label, as it appears in your wallet." },
    { "editasset", "edit a currency contract's label, as it appears in your wallet." },
    { "editnym", "edit the nym's label, as it appears in your wallet." },
    { "editserver", "edit a server contract's label, as it appears in your wallet." },
    { "encode", "OT-base64-encode into armor." },
    { "encrypt", "encrypt plaintext to a nym's public key." },
    { "exchange", "exchange in/out of a basket currency." },
    { "expired", "display contents of expired record box." },
    { "exportcash", "export a cash purse." },
    { "exportnym", "export an OT Nym as a single importable file." },
    { "getboxreceipt", "downloads a box receipt based on transaction ID." },
    { "getcontract", "download an asset or server contract by its ID." },
    { "getmarkets", "download the list of markets." },
    { "getmyoffers", "download mynym's list of market offers." },
    { "getoffers", "download the list of market offers." },
    { "importcash", "import a cash purse." },
    { "importnym", "import an OT Nym that was previously exported." },
    { "inbox", "display inbox of a particular account." },
    { "issueasset", "issue a currency contract onto an OT server." },
    { "killoffer", "kill an active, still-running, recurring market offer." },
    { "killplan", "kill an active, still-running, recurring payment plan." },
    { "mail", "display in-mail for a particular nym." },
    { "newacct", "create a new asset account." },
    { "newasset", "create a new asset contract." },
    { "newbasket", "create a new basket currency." },
    { "newcred", "create a new credential for a specific nym." },
    { "newkey", "create a new symmetric key." },
    { "newnym", "create a new nym." },
    { "newoffer", "create a new market offer." },
    { "newserver", "create a new server contract." },
    { "outbox", "display outbox of a particular account." },
    { "outmail", "display out-mail for a particular nym." },
    { "outpayment", "display contents of outgoing payments box." },
    { "pass_decrypt", "password-decrypt a ciphertext using a symmetric key." },
    { "pass_encrypt", "password-encrypt a plaintext using a symmetric key." },
    { "paydividend", "dividend payout, sent to all shareholders (in voucher form.)" },
    { "payinvoice", "pay an invoice." },
    { "payments", "display contents of incoming payments box." },
    { "propose", "as merchant, propose a payment plan to a customer." },
    { "records", "display contents of record box." },
    { "refresh", "performs both refreshnym and refreshacct." },
    { "refreshacct", "download latest intermediary files for myacct." },
    { "refreshnym", "download latest intermediary files for mynym." },
    { "register", "register a nym onto an OT server." },
    { "revokecred", "revoke one of a nym's credentials." },
    { "sendcash", "send cash from mypurse to recipient, withdraw if necessary." },
    { "sendcheque", "write a cheque and then send it to the recipient." },
    { "sendinvoice", "write an invoice and then send it to the recipient." },
    { "sendmsg", "send a message to another nym's in-mail." },
    { "sendvoucher", "withdraw a voucher and then send it to the recipient." },
    { "showaccounts", "show the asset accounts in the wallet." },
    { "showacct", "show account stats for a single account." },
    { "showassets", "show the currency contracts in the wallet." },
    { "showbasket", "show basket currencies available in the wallet." },
    { "showcred", "show a specific credential in detail." },
    { "showincoming", "show incoming payments for mynym+server and/or inbox for myacct." },
    { "showmarkets", "display the list of markets." },
    { "showmint", "show a mint file for specific asset ID. Download if necessary." },
    { "showmyoffers", "show mynym's offers on a particular server and market." },
    { "shownym", "show the statistics for a specific nym." },
    { "shownyms", "show the nyms in the wallet." },
    { "showoffers", "show all offers on a particular server and market." },
    { "showoutgoing", "show outgoing payments for mynym and/or outbox for myacct." },
    { "showpayment", "show the details of an incoming payment in the payments inbox." },
    { "showpurse", "show contents of cash purse." },
    { "showservers", "show the server contracts in the wallet." },
    { "sign", "sign a contract, releasing all other signatures first." },
    { "stat", "display wallet contents." },
    { "transfer", "send a transfer from myacct to hisacct." },
    { "trigger", "trigger a clause on a running smart contract." },
    { "verifyreceipt", "verify your intermediary files against the last signed receipt." },
    { "verifysig", "verify a signature on a contract." },
    { "withdraw", "withdraw cash. (From acct on server into local purse.)" },
    { "writecheque", "write a cheque and print it out to the screen." },
    { "writeinvoice", "write an invoice and print it out to the screen." },
    { "", "" }
};

typedef struct
{
    string command;
    int(*function)();
} MapFunction;

MapFunction map_functions[] =
{
    { "acceptall", main_accept_all },               // accept all incoming transfers, receipts, payments, and invoices.
    { "acceptinbox", main_accept_inbox },           // accept all incoming transfers and receipts in MyAcct's inbox.
    { "acceptinvoices", main_accept_invoices },     // pay all invoices in MyNym's payments inbox.
    { "acceptmoney", main_accept_money },           // accept all incoming transfers and payments into MyAcct.
    { "acceptpayments", main_accept_payments },     // accept all incoming payments in MyNym's payments inbox.
    { "acceptreceipts", main_accept_receipts },     // accept all receipts in MyAcct's inbox.
    { "accepttransfers", main_accept_transfers },   // accept all incoming transfers in MyAcct's inbox.
    { "addasset", main_add_asset },                 // paste an existing asset contract, import it into your wallet.
    { "addserver", main_add_server },               // paste an existing server contract, import it into your wallet.
    { "addsignature", main_add_signature },         // add a signature to a contract without releasing others.
    { "balance", main_balance },                    // display balance for a specific account.
    { "buyvoucher", main_withdraw_voucher },        // withdraw a voucher (cashier's cheque).
    { "cancel", main_cancel_outgoing },             // cancel a not-yet-cashed, outgoing instrument from outpayment box.
    { "changepw", main_change_passphrase },         // Change the master passphrase for the wallet.
    { "checknym", main_check_user },                // download a nym's public key based on his ID.
    { "clearexpired", main_clear_expired },         // clear all expired records.
    { "clearrecords", main_clear_records },         // clear all archived records and receipts.
    { "confirm", main_confirm },                    // confirm your agreement to a smart contract or payment plan.
    { "credentials", main_show_credentials },       // show the credentials for a specific nym.
    { "decode", main_decode },                      // OT-base64-decode out of armor.
    { "decrypt", main_decrypt },                    // decrypt ciphertext using nym's private key.
    { "delmail", main_del_mail },                   // delete an in-mail item
    { "deloutmail", main_del_outmail },             // delete an out-mail item
    { "deposit", main_deposit },                    // deposit cash purse, cheque, voucher, or invoice.
    { "discard", main_discard_incoming },           // discard a not-yet-cashed, incoming instrument from payments inbox.
    { "editacct", main_edit_account },              // edit an asset account's label, as it appears in your wallet.
    { "editasset", main_edit_asset },               // edit a currency contract's label, as it appears in your wallet.
    { "editnym", main_edit_nym },                   // edit the nym's label, as it appears in your wallet.
    { "editserver", main_edit_server },             // edit a server contract's label, as it appears in your wallet.
    { "encode", main_encode },                      // OT-base64-encode into armor.
    { "encrypt", main_encrypt },                    // encrypt plaintext to a nym's public key.
    { "exchange", main_exchange_basket },           // exchange in/out of a basket currency.
    { "expired", main_show_expired },               // display contents of expired box.
    { "exportcash", main_export_cash },             // Export a cash purse.
    { "exportnym", main_export_nym },               // Export an OT Nym as a single importable file.
    { "getboxreceipt", main_get_box_receipt },      // downloads a box receipt based on transaction ID.
    { "getcontract", main_download_contract },      // download an asset or server contract by its ID.
    { "getmarkets", main_get_market_list },         // download the list of markets.
    { "getmyoffers", main_get_nym_market_offers },  // download the list of market offers placed by mynym.
    { "getoffers", main_get_market_offers },        // download the list of market offers.
    { "importcash", main_import_cash },             // Import a cash purse.
    { "importnym", main_import_nym },               // Import an OT Nym that was previously exported.
    { "inbox", main_show_inbox },                   // display inbox of a particular account.
    { "issueasset", main_issue_asset },             // issue a currency contract onto an OT server.
    { "killoffer", main_kill_offer },               // kill a still-running, recurring market offer.
    { "killplan", main_kill_plan },                 // kill a still-running, recurring payment plan.
    { "mail", main_show_mail },                     // display in-mail for a particular nym.
    { "newacct", main_create_acct },                // create a new asset account.
    { "newasset", main_create_asset_contract },     // create a new asset contract.
    { "newbasket", main_new_basket },               // create a new basket currency.
    { "newcred", main_new_credential },             // create a new credential for a specific nym.
    { "newkey", main_new_symmetric_key },           // create a new symmetric key.
    { "newnym", main_create_nym },                  // create a new nym.
    { "newoffer", main_create_offer },              // create a new market offer.
    { "newserver", main_create_server_contract },   // create a new server contract.
    { "outbox", main_show_outbox },                 // display outbox of a particular account.
    { "outmail", main_show_outmail },               // display out-mail for a particular nym.
    { "outpayment", main_show_outpayment },         // display contents of outgoing payments box.
    { "pass_decrypt", main_password_decrypt },      // password-decrypt a ciphertext using a symmetric key.
    { "pass_encrypt", main_password_encrypt },      // password-encrypt a plaintext using a symmetric key.
    { "paydividend", main_pay_dividend },           // dividend payout, sent to all shareholders in voucher form.
    { "payinvoice", main_payinvoice },              // pay an invoice.
    { "payments", main_show_payments_inbox },       // display contents of incoming payments box.
    { "propose", main_propose_plan },               // as merchant, propose a payment plan to a customer.
    { "records", main_show_records },               // display contents of record box.
    { "refresh", main_refresh_all },                // "performs both refreshnym and refreshacct."
    { "refreshacct", main_dl_acct_files },          // "download latest intermediary files for myacct."
    { "refreshnym", main_refresh_nym },             // download latest intermediary files for mynym.
    { "register", main_register_nym },              // register a nym onto an OT server.
    { "revokecred", main_revoke_credential },       // revoke one of a nym's credentials.
    { "sendcash", main_sendcash },                  // send cash from mypurse to recipient, withdraw if necessary.
    { "sendcheque", main_sendcheque },              // write a cheque and then send it to the recipient.
    { "sendinvoice", main_sendinvoice },            // write an invoice and then send it to the recipient.
    { "sendmsg", main_sendmsg },                    // send a message to another nym's in-mail.
    { "sendvoucher", main_sendvoucher },            // withdraw a voucher and then send it to the recipient.
    { "showaccounts", stat_accounts },              // show the asset accounts in the wallet.
    { "showacct", main_stat_acct },                 // show account stats for a single account.
    { "showassets", stat_assets },                  // show the currency contracts in the wallet.
    { "showbasket", main_show_basket },             // show basket currencies available in the wallet.
    { "showcred", main_show_credential },           // show a specific credential in detail.
    { "showincoming", main_show_incoming },         // show incoming payments for mynym+server and/or inbox for myacct.
    { "showmarkets", main_show_market_list },       // display the list of markets.
    { "showmint", main_show_mint },                 // show a mint file for specific asset ID. Download if necessary.
    { "showmyoffers", main_show_nym_offers },       // show mynym's offers on a particular server and market.
    { "shownym", main_nym_stat },                   // show the statistics for a specific nym.
    { "shownyms", stat_nyms },                      // show the nyms in the wallet.
    { "showoffers", main_show_market_offers },      // show all offers on a particular server and market.
    { "showoutgoing", main_show_outgoing },         // show outgoing payments for mynym and/or outbox for myacct.
    { "showpayment", main_show_payment },           // show the details of a payment in the payments inbox.
    { "showpurse", main_show_purse },               // show contents of cash purse.
    { "showservers", stat_servers },                // show the server contracts in the wallet.
    { "sign", main_sign_contract },                 // sign a contract, releasing all other signatures first.
    { "stat", main_stat },                          // display wallet contents.
    { "transfer", main_transfer },                  // send a transfer from myacct to hisacct.
    { "trigger", main_trigger_clause },             // trigger a clause on a running smart contract.
    { "verifyreceipt", main_verify_last_receipt },  // verify the intermediary files against the last signed receipt.
    { "verifysig", main_verify_signature },         // verify a signature on a contract.
    { "withdraw", main_withdraw_cash },             // withdraw cash (from acct on server to local purse.)
    { "writecheque", main_write_cheque },           // write a cheque and print it out to the screen.
    { "writeinvoice", main_write_invoice },         // write an invoice and print it out to the screen.
    { "", NULL }
};



int OT_OPENTXS_OT main_not_coded_yet()
{
    print("\n\n  Congratulations, you've been selected to add that option to this script! \n It's real easy: just edit scripts/ot/ot_commands.ot, and copy some code\ninto it based on whichever sample script is appropriate.\nThen edit the opentxs script, and add your new main\nfunction to the list map_functions near the bottom. Done!\n\n");

    return 0;
}


int OT_OPENTXS_OT interpret_command(const string & strInput)
{
    if ("quit" == strInput)
    {
        return (-2);
    }

    if ("list" == strInput)
    {
        OTAPI_Wrap::Output(0, "\nCommands: \n\n");
        for (int i = 0; map_functions[i].command != ""; i++)
        {
            MapFunction & func = map_functions[i];
            OTAPI_Wrap::Output(0, func.command + (func.command.length() > 7 ? "\t" : "\t\t"));
            if (i % 4 == 3)
            {
                OTAPI_Wrap::Output(0, "\n");
            }
        }
        OTAPI_Wrap::Output(0, "\n");

        return 0;  // "success" from UNIX command line perspective.;
    }

    if ("help" == strInput)
    {
        string strAdmin = "";
        string strWallet = "";
        string strMisc = "";
        string strMarkets = "";
        string strAccounts = "";
        string strOtherUsers = "";
        string strInstruments = "";
        string strBaskets = "";
        string strNyms = "";

        OTAPI_Wrap::Output(0, "\nCommands: \n\n");
        for (int i = 0; map_functions[i].command != ""; i++)
        {
            MapFunction & func = map_functions[i];

            string line = "";
            for (int j = 0; map_help[j].command != ""; j++)
            {
                MapHelp & help = map_help[j];
                if (help.command == func.command)
                {
                    line = help.command + (help.command.length() > 7 ? "\t" : "\t\t") + help.helpText + "\n";
                    break;
                }
            }

            for (int j = 0; map_categories[j].command != ""; j++)
            {
                MapCategory & cat = map_categories[j];
                if (cat.command == func.command)
                {
                    switch (cat.category)
                    {
                    case catAdmin: strAdmin += line; break;
                    case catWallet: strWallet += line; break;
                    case catMisc: strMisc += line; break;
                    case catMarkets: strMarkets += line; break;
                    case catAccounts: strAccounts += line; break;
                    case catOtherUsers: strOtherUsers += line; break;
                    case catInstruments: strInstruments += line; break;
                    case catBaskets: strBaskets += line; break;
                    case catNyms: strNyms += line; break;
                    }
                    break;
                }
            }
        }

        OTAPI_Wrap::Output(0, "\n " + categoryName[catAdmin] + ": \\n" + strAdmin);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catWallet] + ": \\n" + strWallet);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catMisc] + ": \\n" + strMisc);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catMarkets] + ": \\n" + strMarkets);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catAccounts] + ": \\n" + strAccounts);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catOtherUsers] + ": \\n" + strOtherUsers);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catInstruments] + ": \\n" + strInstruments);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catBaskets] + ": \\n" + strBaskets);
        OTAPI_Wrap::Output(0, "\n " + categoryName[catNyms] + ": \\n" + strNyms);
        OTAPI_Wrap::Output(0, "\n");

        return 0; // "success" from UNIX command line perspective.;
    }

    // all other commands.
    for (int i = 0; map_functions[i].command != ""; i++)
    {
        MapFunction & func = map_functions[i];
        if (func.command == strInput)
        {
            if (func.function != NULL)
            {
                int nReturn = (*func.function)();
                OTAPI_Wrap::Output(2, "\n Returning error code: \"" + to_string(nReturn) + "\".\n\n");
                switch (nReturn)
                {
                case 0:
                    // This means "no error, but also didn't do anything."
                    // This is considered a form of success, so we
                    // return 0 (UNIX CLI success.)
                    //
                    return 0;
                case 1:
                    // This is an explicit success, so we
                    // return 0 (UNIX CLI success.)
                    return 0;
                case -1:
                    // This is an explicit failure, so we
                    // return -1 (UNIX failures tend to be non-zero values.)
                    return -1;
                default:
                    OTAPI_Wrap::Output(0, "\n Undefined error code: \"" + to_string(nReturn) + "\".\n\n");
                    return -1;
                }
            }
            break;
        }
    }

    OTAPI_Wrap::Output(0, "\n Undefined command: \"" + strInput + "\" -- Try 'list'.\n\n");

    return -1;
}



int OT_OPENTXS_OT OT_ME::opentxs_main_loop()
{
    OT_ME me;
    OTVariable *pVar;
    if ((pVar = me.FindVariable("Args")) != NULL) Args = pVar->GetValueString();
    if ((pVar = me.FindVariable("HisAcct")) != NULL) HisAcct = pVar->GetValueString();
    if ((pVar = me.FindVariable("HisNym")) != NULL) HisNym = pVar->GetValueString();
    if ((pVar = me.FindVariable("HisPurse")) != NULL) HisPurse = pVar->GetValueString();
    if ((pVar = me.FindVariable("MyAcct")) != NULL) MyAcct = pVar->GetValueString();
    if ((pVar = me.FindVariable("MyNym")) != NULL) MyNym = pVar->GetValueString();
    if ((pVar = me.FindVariable("MyPurse")) != NULL) MyPurse = pVar->GetValueString();
    if ((pVar = me.FindVariable("Server")) != NULL) Server = pVar->GetValueString();

    // See if the command was passed in on the command line.
    if (VerifyExists("Args", false))
    {
        OTAPI_Wrap::Output(1, "\nCommand: " + Args + "\n\n");
        string strCommand = OT_CLI_GetValueByKey(Args, "ot_cli_command");

        if (VerifyStringVal(strCommand)) // command was passed in on the command line...
        {
            return interpret_command(strCommand);
        }
    }

    // Otherwise, drop into the OT high-level prompt.
    else
    {
        OTAPI_Wrap::Output(0, ".\n..\n...\n....\n.....\n\n");

        while (true)
        {
            OTAPI_Wrap::Output(0, "opentxs> ");
            string strInput = OT_CLI_ReadLine();
            int nInterpreted = interpret_command(strInput);
            if (VerifyIntVal(nInterpreted) && ((-2) == nInterpreted))
            {
                break;
            }

            OTAPI_Wrap::Output(0, ".\n..\n...\n....\n.....\n\n");

        } // while
    }

    return 0;
}
