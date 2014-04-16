#include <stdafx.hpp>

#include <string>

#include "ot_utility_ot.hpp"
#include "ot_otapi_ot.hpp"
#include "ot_commands_ot.hpp"

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
    { "showactive", catInstruments },
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
    { "showactive", "show the active cron item IDs, or the details of one by ID." },
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
    { "acceptall", OT_Command::main_accept_all },               // accept all incoming transfers, receipts, payments, and invoices.
    { "acceptinbox", OT_Command::main_accept_inbox },           // accept all incoming transfers and receipts in MyAcct's inbox.
    { "acceptinvoices", OT_Command::main_accept_invoices },     // pay all invoices in MyNym's payments inbox.
    { "acceptmoney", OT_Command::main_accept_money },           // accept all incoming transfers and payments into MyAcct.
    { "acceptpayments", OT_Command::main_accept_payments },     // accept all incoming payments in MyNym's payments inbox.
    { "acceptreceipts", OT_Command::main_accept_receipts },     // accept all receipts in MyAcct's inbox.
    { "accepttransfers", OT_Command::main_accept_transfers },   // accept all incoming transfers in MyAcct's inbox.
    { "addasset", OT_Command::main_add_asset },                 // paste an existing asset contract, import it into your wallet.
    { "addserver", OT_Command::main_add_server },               // paste an existing server contract, import it into your wallet.
    { "addsignature", OT_Command::main_add_signature },         // add a signature to a contract without releasing others.
    { "balance", OT_Command::main_balance },                    // display balance for a specific account.
    { "buyvoucher", OT_Command::main_withdraw_voucher },        // withdraw a voucher (cashier's cheque).
    { "cancel", OT_Command::main_cancel_outgoing },             // cancel a not-yet-cashed, outgoing instrument from outpayment box.
    { "changepw", OT_Command::main_change_passphrase },         // Change the master passphrase for the wallet.
    { "checknym", OT_Command::main_check_user },                // download a nym's public key based on his ID.
    { "clearexpired", OT_Command::main_clear_expired },         // clear all expired records.
    { "clearrecords", OT_Command::main_clear_records },         // clear all archived records and receipts.
    { "confirm", OT_Command::main_confirm },                    // confirm your agreement to a smart contract or payment plan.
    { "credentials", OT_Command::main_show_credentials },       // show the credentials for a specific nym.
    { "decode", OT_Command::main_decode },                      // OT-base64-decode out of armor.
    { "decrypt", OT_Command::main_decrypt },                    // decrypt ciphertext using nym's private key.
    { "delmail", OT_Command::main_del_mail },                   // delete an in-mail item
    { "deloutmail", OT_Command::main_del_outmail },             // delete an out-mail item
    { "deposit", OT_Command::main_deposit },                    // deposit cash purse, cheque, voucher, or invoice.
    { "discard", OT_Command::main_discard_incoming },           // discard a not-yet-cashed, incoming instrument from payments inbox.
    { "editacct", OT_Command::main_edit_account },              // edit an asset account's label, as it appears in your wallet.
    { "editasset", OT_Command::main_edit_asset },               // edit a currency contract's label, as it appears in your wallet.
    { "editnym", OT_Command::main_edit_nym },                   // edit the nym's label, as it appears in your wallet.
    { "editserver", OT_Command::main_edit_server },             // edit a server contract's label, as it appears in your wallet.
    { "encode", OT_Command::main_encode },                      // OT-base64-encode into armor.
    { "encrypt", OT_Command::main_encrypt },                    // encrypt plaintext to a nym's public key.
    { "exchange", OT_Command::main_exchange_basket },           // exchange in/out of a basket currency.
    { "expired", OT_Command::main_show_expired },               // display contents of expired box.
    { "exportcash", OT_Command::main_export_cash },             // Export a cash purse.
    { "exportnym", OT_Command::main_export_nym },               // Export an OT Nym as a single importable file.
    { "getboxreceipt", OT_Command::main_get_box_receipt },      // downloads a box receipt based on transaction ID.
    { "getcontract", OT_Command::main_download_contract },      // download an asset or server contract by its ID.
    { "getmarkets", OT_Command::main_get_market_list },         // download the list of markets.
    { "getmyoffers", OT_Command::main_get_nym_market_offers },  // download the list of market offers placed by mynym.
    { "getoffers", OT_Command::main_get_market_offers },        // download the list of market offers.
    { "importcash", OT_Command::main_import_cash },             // Import a cash purse.
    { "importnym", OT_Command::main_import_nym },               // Import an OT Nym that was previously exported.
    { "inbox", OT_Command::main_show_inbox },                   // display inbox of a particular account.
    { "issueasset", OT_Command::main_issue_asset },             // issue a currency contract onto an OT server.
    { "killoffer", OT_Command::main_kill_offer },               // kill a still-running, recurring market offer.
    { "killplan", OT_Command::main_kill_plan },                 // kill a still-running, recurring payment plan.
    { "mail", OT_Command::main_show_mail },                     // display in-mail for a particular nym.
    { "newacct", OT_Command::main_create_acct },                // create a new asset account.
    { "newasset", OT_Command::main_create_asset_contract },     // create a new asset contract.
    { "newbasket", OT_Command::main_new_basket },               // create a new basket currency.
    { "newcred", OT_Command::main_new_credential },             // create a new credential for a specific nym.
    { "newkey", OT_Command::main_new_symmetric_key },           // create a new symmetric key.
    { "newnym", OT_Command::main_create_nym },                  // create a new nym.
    { "newoffer", OT_Command::main_create_offer },              // create a new market offer.
    { "newserver", OT_Command::main_create_server_contract },   // create a new server contract.
    { "outbox", OT_Command::main_show_outbox },                 // display outbox of a particular account.
    { "outmail", OT_Command::main_show_outmail },               // display out-mail for a particular nym.
    { "outpayment", OT_Command::main_show_outpayment },         // display contents of outgoing payments box.
    { "pass_decrypt", OT_Command::main_password_decrypt },      // password-decrypt a ciphertext using a symmetric key.
    { "pass_encrypt", OT_Command::main_password_encrypt },      // password-encrypt a plaintext using a symmetric key.
    { "paydividend", OT_Command::main_pay_dividend },           // dividend payout, sent to all shareholders in voucher form.
    { "payinvoice", OT_Command::main_payinvoice },              // pay an invoice.
    { "payments", OT_Command::main_show_payments_inbox },       // display contents of incoming payments box.
    { "propose", OT_Command::main_propose_plan },               // as merchant, propose a payment plan to a customer.
    { "records", OT_Command::main_show_records },               // display contents of record box.
    { "refresh", OT_Command::main_refresh_all },                // "performs both refreshnym and refreshacct."
    { "refreshacct", OT_Command::main_dl_acct_files },          // "download latest intermediary files for myacct."
    { "refreshnym", OT_Command::main_refresh_nym },             // download latest intermediary files for mynym.
    { "register", OT_Command::main_register_nym },              // register a nym onto an OT server.
    { "revokecred", OT_Command::main_revoke_credential },       // revoke one of a nym's credentials.
    { "sendcash", OT_Command::main_sendcash },                  // send cash from mypurse to recipient, withdraw if necessary.
    { "sendcheque", OT_Command::main_sendcheque },              // write a cheque and then send it to the recipient.
    { "sendinvoice", OT_Command::main_sendinvoice },            // write an invoice and then send it to the recipient.
    { "sendmsg", OT_Command::main_sendmsg },                    // send a message to another nym's in-mail.
    { "sendvoucher", OT_Command::main_sendvoucher },            // withdraw a voucher and then send it to the recipient.
    { "showaccounts", OT_Command::main_stat_accounts },         // show the asset accounts in the wallet.
    { "showacct", OT_Command::main_stat_acct },                 // show account stats for a single account.
    { "showactive", OT_Command::main_show_active },             // show the active cron item IDs, or the details of one by ID.
    { "showassets", OT_Command::main_stat_assets },             // show the currency contracts in the wallet.
    { "showbasket", OT_Command::main_show_basket },             // show basket currencies available in the wallet.
    { "showcred", OT_Command::main_show_credential },           // show a specific credential in detail.
    { "showincoming", OT_Command::main_show_incoming },         // show incoming payments for mynym+server and/or inbox for myacct.
    { "showmarkets", OT_Command::main_show_market_list },       // display the list of markets.
    { "showmint", OT_Command::main_show_mint },                 // show a mint file for specific asset ID. Download if necessary.
    { "showmyoffers", OT_Command::main_show_nym_offers },       // show mynym's offers on a particular server and market.
    { "shownym", OT_Command::main_nym_stat },                   // show the statistics for a specific nym.
    { "shownyms", OT_Command::main_stat_nyms },                 // show the nyms in the wallet.
    { "showoffers", OT_Command::main_show_market_offers },      // show all offers on a particular server and market.
    { "showoutgoing", OT_Command::main_show_outgoing },         // show outgoing payments for mynym and/or outbox for myacct.
    { "showpayment", OT_Command::main_show_payment },           // show the details of a payment in the payments inbox.
    { "showpurse", OT_Command::main_show_purse },               // show contents of cash purse.
    { "showservers", OT_Command::main_stat_servers },           // show the server contracts in the wallet.
    { "sign", OT_Command::main_sign_contract },                 // sign a contract, releasing all other signatures first.
    { "stat", OT_Command::main_stat },                          // display wallet contents.
    { "transfer", OT_Command::main_transfer },                  // send a transfer from myacct to hisacct.
    { "trigger", OT_Command::main_trigger_clause },             // trigger a clause on a running smart contract.
    { "verifyreceipt", OT_Command::main_verify_last_receipt },  // verify the intermediary files against the last signed receipt.
    { "verifysig", OT_Command::main_verify_signature },         // verify a signature on a contract.
    { "withdraw", OT_Command::main_withdraw_cash },             // withdraw cash (from acct on server to local purse.)
    { "writecheque", OT_Command::main_write_cheque },           // write a cheque and print it out to the screen.
    { "writeinvoice", OT_Command::main_write_invoice },         // write an invoice and print it out to the screen.
    { "", NULL }
};



int OT_OPENTXS_OT main_not_coded_yet()
{
    print("\n\n  Congratulations, you've been selected to add that option to this program! \n It's real easy: just edit ot_commands_ot.cpp, and copy some code\ninto it based on whichever sample script is appropriate.\nThen edit the opentxs script, and add your new main\nfunction to the list map_functions near the bottom. Done!\n\n");

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


void OT_OPENTXS_OT OT_ME::opentxs_copy_variables()
{
    OTVariable *pVar;
    Args = (pVar = FindVariable("Args")) == NULL ? "" : pVar->GetValueString();
    HisAcct = (pVar = FindVariable("HisAcct")) == NULL ? "" : pVar->GetValueString();
    HisNym = (pVar = FindVariable("HisNym")) == NULL ? "" : pVar->GetValueString();
    HisPurse = (pVar = FindVariable("HisPurse")) == NULL ? "" : pVar->GetValueString();
    MyAcct = (pVar = FindVariable("MyAcct")) == NULL ? "" : pVar->GetValueString();
    MyNym = (pVar = FindVariable("MyNym")) == NULL ? "" : pVar->GetValueString();
    MyPurse = (pVar = FindVariable("MyPurse")) == NULL ? "" : pVar->GetValueString();
    Server = (pVar = FindVariable("Server")) == NULL ? "" : pVar->GetValueString();
}


int OT_OPENTXS_OT OT_ME::opentxs_main_loop()
{
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

    // Otherwise, show list.
    return interpret_command("list");
}
