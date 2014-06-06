/*************************************************************
*
*  main.cpp  (Uses ZMQ for transport.)
*
*/

/************************************************************
-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA1

*                 OPEN TRANSACTIONS
*
*       Financial Cryptography and Digital Cash
*       Library, Protocol, API, str_Server, CLI, GUI
*
*       -- Anonymous Numbered Accounts.
*       -- Untraceable Digital Cash.
*       -- Triple-Signed Receipts.
*       -- Cheques, Vouchers, Transfers, Inboxes.
*       -- Basket Currencies, Markets, Payment Plans.
*       -- Signed, XML, Ricardian-style Contracts.
*       -- Scripted smart contracts.
*
*  Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
*
*  EMAIL:
*  FellowTraveler@rayservers.net
*
*  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
*
*  KEY FINGERPRINT (PGP Key in license file):
*  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
*
*  OFFICIAL PROJECT WIKI(s):
*  https://github.com/FellowTraveler/Moneychanger
*  https://github.com/FellowTraveler/Open-Transactions/wiki
*
*  WEBSITE:
*  http://www.OpenTransactions.org/
*
*  Components and licensing:
*   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
*   -- otlib.........A class library.......LICENSE:...LAGPLv3
*   -- otapi.........A client API..........LICENSE:...LAGPLv3
*   -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
*   -- otserver......str_Server Application....LICENSE:....AGPLv3
*  Github.com/FellowTraveler/Open-Transactions/wiki/Components
*
*  All of the above OT components were designed and written by
*  Fellow Traveler, with the exception of Moneychanger, which
*  was contracted out to Vicky C (bitcointrader4@gmail.com).
*  The open-source community has since actively contributed.
*
*  -----------------------------------------------------
*
*   LICENSE:
*   This program is free software: you can redistribute it
*   and/or modify it under the terms of the GNU Affero
*   General Public License as published by the Free Software
*   Foundation, either version 3 of the License, or (at your
*   option) any later version.
*
*   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
*   section 7: (This paragraph applies only to the LAGPLv3
*   components listed above.) If you modify this Program, or
*   any covered work, by linking or combining it with other
*   code, such other code is not for that reason alone subject
*   to any of the requirements of the GNU Affero GPL version 3.
*   (==> This means if you are only using the OT API, then you
*   don't have to open-source your code--only your changes to
*   Open-Transactions itself must be open source. Similar to
*   LGPLv3, except it applies to software-as-a-service, not
*   just to distributing binaries.)
*
*   Extra WAIVER for OpenSSL, Lucre, and all other libraries
*   used by Open Transactions: This program is released under
*   the AGPL with the additional exemption that compiling,
*   linking, and/or using OpenSSL is allowed. The same is true
*   for any other open source libraries included in this
*   project: complete waiver from the AGPL is hereby granted to
*   compile, link, and/or use them with Open-Transactions,
*   according to their own terms, as long as the rest of the
*   Open-Transactions terms remain respected, with regard to
*   the Open-Transactions code itself.
*
*   Lucre License:
*   This code is also "dual-license", meaning that Ben Lau-
*   rie's license must also be included and respected, since
*   the code for Lucre is also included with Open Transactions.
*   See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
*   The Laurie requirements are light, but if there is any
*   problem with his license, simply remove the Lucre code.
*   Although there are no other blind token algorithms in Open
*   Transactions (yet. credlib is coming), the other functions
*   will continue to operate.
*   See Lucre on Github:  https://github.com/benlaurie/lucre
*   -----------------------------------------------------
*   You should have received a copy of the GNU Affero General
*   Public License along with this program.  If not, see:
*   http://www.gnu.org/licenses/
*
*   If you would like to use this software outside of the free
*   software license, please contact FellowTraveler.
*   (Unfortunately many will run anonymously and untraceably,
*   so who could really stop them?)
*
*   DISCLAIMER:
*   This program is distributed in the hope that it will be
*   useful, but WITHOUT ANY WARRANTY; without even the implied
*   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
*   PURPOSE.  See the GNU Affero General Public License for
*   more details.

-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1.4.9 (Darwin)

iQIcBAEBAgAGBQJRSsfJAAoJEAMIAO35UbuOQT8P/RJbka8etf7wbxdHQNAY+2cC
vDf8J3X8VI+pwMqv6wgTVy17venMZJa4I4ikXD/MRyWV1XbTG0mBXk/7AZk7Rexk
KTvL/U1kWiez6+8XXLye+k2JNM6v7eej8xMrqEcO0ZArh/DsLoIn1y8p8qjBI7+m
aE7lhstDiD0z8mwRRLKFLN2IH5rAFaZZUvj5ERJaoYUKdn4c+RcQVei2YOl4T0FU
LWND3YLoH8naqJXkaOKEN4UfJINCwxhe5Ke9wyfLWLUO7NamRkWD2T7CJ0xocnD1
sjAzlVGNgaFDRflfIF4QhBx1Ddl6wwhJfw+d08bjqblSq8aXDkmFA7HeunSFKkdn
oIEOEgyj+veuOMRJC5pnBJ9vV+7qRdDKQWaCKotynt4sWJDGQ9kWGWm74SsNaduN
TPMyr9kNmGsfR69Q2Zq/FLcLX/j8ESxU+HYUB4vaARw2xEOu2xwDDv6jt0j3Vqsg
x7rWv4S/Eh18FDNDkVRChiNoOIilLYLL6c38uMf1pnItBuxP3uhgY6COm59kVaRh
nyGTYCDYD2TK+fI9o89F1297uDCwEJ62U0Q7iTDp5QuXCoxkPfv8/kX6lS6T3y9G
M9mqIoLbIQ1EDntFv7/t6fUTS2+46uCrdZWbQ5RjYXdrzjij02nDmJAm2BngnZvd
kamH0Y/n11lCvo1oQxM+
=uSzz
-----END PGP SIGNATURE-----
**************************************************************/

#include <stdafx.hpp>

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <map>
#include <vector>

#include <anyoption.hpp>

#include <OpenTransactions.hpp>
#include <OT_ME.hpp>
#include <OTClient.hpp>

#include <OTAccount.hpp>
#include <OTAssetContract.hpp>
#include <OTLog.hpp>
#include <OTPaths.hpp>
#include <OTPseudonym.hpp>
#include <OTServerContract.hpp>
#include <OTVariable.hpp>
#include <OTWallet.hpp>

#include "ot_otapi_ot.hpp"


#define OT_OPTIONS_FILE_DEFAULT	"command-line-ot.opt"


static string str_Args;
static string str_HisAcct;
static string str_HisNym;
static string str_HisPurse;
static string str_MyAcct;
static string str_MyNym;
static string str_MyPurse;
static string str_Server;


// trim from start
static inline std::string &ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}


// trim from end
static inline std::string &rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}


// trim from both ends
static inline std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}


void HandleCommandLineArguments(int argc, char* argv[], AnyOption & opt)
{
    OTString strConfigPath(OTPaths::AppDataFolder());
    bool bConfigPathFound = strConfigPath.Exists() && 3 < strConfigPath.GetLength();
    OT_ASSERT_MSG(bConfigPathFound, "RegisterAPIWithScript: Must set Config Path first!\n");
    OTLog::vOutput(1, "Using configuration path:  %s\n", strConfigPath.Get());

    opt.addUsage("");
    opt.addUsage(" Opentxs CLI Usage:  ");
    opt.addUsage("");

    opt.setCommandFlag("echocommand");
    opt.setCommandFlag("echoexpand");
    opt.setCommandFlag("errorlist");
    opt.setCommandFlag("noprompt");
    opt.setCommandFlag("test");

    opt.setCommandOption("args");
    opt.setCommandOption("myacct");
    opt.setCommandOption("mynym");
    opt.setCommandOption("mypurse");
    opt.setCommandOption("hisacct");
    opt.setCommandOption("hisnym");
    opt.setCommandOption("hispurse");
    opt.setCommandOption("server");

    // RESOURCE FILE ONLY
    /* for options that will be checked only from the option/resource file */
    opt.setFileOption("defaultserver"); /* an option (takes an argument), supporting only long form */
    opt.setFileOption("defaultmyacct"); /* an option (takes an argument), supporting only long form */
    opt.setFileOption("defaultmynym"); /* an option (takes an argument), supporting only long form */
    opt.setFileOption("defaultmypurse"); /* an option (takes an argument), supporting only long form */
    opt.setFileOption("defaulthisacct"); /* an option (takes an argument), supporting only long form */
    opt.setFileOption("defaulthisnym"); /* an option (takes an argument), supporting only long form */
    opt.setFileOption("defaulthispurse"); /* an option (takes an argument), supporting only long form */

    /* PROCESS THE COMMANDLINE AND RESOURCE FILE */

    /* read options from a option/resource file with ':' separated options or flags, one per line */

    OTString strOptionsFile(OT_OPTIONS_FILE_DEFAULT), strIniFileExact;
    bool bBuildFullPathSuccess = OTPaths::RelativeToCanonical(strIniFileExact, strConfigPath, strOptionsFile);
    OT_ASSERT_MSG(bBuildFullPathSuccess, "Unalbe to set Full Path");

    opt.processFile(strIniFileExact.Get());
    opt.processCommandArgs(argc, argv);
}


const char * GetOption(AnyOption & opt, const char * pDefaultName, const char * pOptionName)
{
    // can we get the default value from the command line?
    const char * pValue = opt.getValue(pOptionName);
    if (NULL != pValue)
    {
        OTLog::vOutput(1, "Option  %s: %s\n", pOptionName, pValue);
        return pValue;
    }

    // can we get the default value from the options file?
    pValue = opt.getValue(pDefaultName);
    if (NULL != pValue)
    {
        OTLog::vOutput(1, "Default %s: %s\n", pOptionName, pValue);
        return pValue;
    }

    // clear option value
    return "";
}


OTVariable * SetGlobalVariable(OT_ME & madeEasy, const string & name, const string & value)
{
    if (value.size() == 0)
    {
        OTLog::vOutput(2, "Variable %s isn't set\n", name.c_str());
        return NULL;
    }

    OTLog::vOutput(1, "Variable %s has value: %s\n", name.c_str(), value.c_str());

    OTVariable * pVar = new OTVariable(name, value, OTVariable::Var_Constant);
    OT_ASSERT(NULL != pVar);
    madeEasy.AddVariable(name, *pVar);
    return pVar;
}


int ProcessCommand(OT_ME & madeEasy, AnyOption & opt)
{
    // process command line values such as account ID, Nym ID, etc.
    // Also available as defaults in a config file in the ~/.ot folder
    str_Args = GetOption(opt, "defaultargs", "args");
    str_HisAcct = GetOption(opt, "defaulthisacct", "hisacct");
    str_HisNym = GetOption(opt, "defaulthisnym", "hisnym");
    str_HisPurse = GetOption(opt, "defaulthispurse", "hispurse");
    str_MyAcct = GetOption(opt, "defaultmyacct", "myacct");
    str_MyNym = GetOption(opt, "defaultmynym", "mynym");
    str_MyPurse = GetOption(opt, "defaultmypurse", "mypurse");
    str_Server = GetOption(opt, "defaultserver", "server");

    OTWallet * pWallet = OTAPI_Wrap::OTAPI()->GetWallet();
    OT_ASSERT_MSG(NULL != pWallet, "The wallet object is still NULL, somehow. Please load it.\n");

    OTServerContract * pServerContract = NULL;
    if (str_Server.size() > 0)
    {
        pServerContract = pWallet->GetServerContract(str_Server);
        if (NULL == pServerContract)
        {
            pServerContract = pWallet->GetServerContractPartialMatch(str_Server);
            if (NULL == pServerContract)
            {
                OTLog::Output(0, "Unable to find a server contract. Please use the option:  --server SERVER_ID\n"
                    "(Where SERVER_ID is the server ID. Partial matches are accepted if the contract is already in the wallet.)\n"
                    "Also, see default values located in ~/.ot/comand-line-ot.opt \n");
            }
        }
        if (NULL != pServerContract)
        {
            OTString strTemp;
            pServerContract->GetIdentifier(strTemp);
            str_Server = strTemp.Get();
            OTLog::vOutput(0, "Using as server: %s\n", str_Server.c_str());
        }
    }
    if (NULL == pServerContract)
    {
        OTLog::Output(0, "Unable to find a server contract to use. Please use the option: --server SERVER_ID\n"
            "(Where SERVER_ID is the str_Server's ID. Partial matches ARE accepted.)\n");
    }

    OTPseudonym * pMyNym = NULL;
    if (str_MyNym.size() > 0)
    {
        pMyNym = pWallet->GetNymByID(str_MyNym);
        if (NULL == pMyNym)
        {
            pMyNym = pWallet->GetNymByIDPartialMatch(str_MyNym);
            if (NULL == pMyNym)
            {
                OTLog::Output(0, "==> Unable to find My Nym. Please use the option:   --mynym USER_ID\n"
                    "(Where USER_ID is the Nym's ID. Partial matches are accepted if the nym is already in the wallet.)\n"
                    "Also, see default values located in ~/.ot/comand-line-ot.opt \n");
            }
        }
        if (NULL != pMyNym)
        {
            OTString strTemp;
            pMyNym->GetIdentifier(strTemp);
            str_MyNym = strTemp.Get();
            OTLog::vOutput(0, "Using as mynym: %s\n", str_MyNym.c_str());
        }
    }
    if (NULL == pMyNym)
    {
        OTLog::Output(0, "Unable to find My Nym. Please use the option:   --mynym USER_ID\n"
            "(Where USER_ID is the Nym's ID. Partial matches and names are accepted.)\n");
    }

    OTAccount * pMyAccount = NULL;
    if (str_MyAcct.size() > 0)
    {
        pMyAccount = pWallet->GetAccount(str_MyAcct);
        if (NULL == pMyAccount)
        {
            pMyAccount = pWallet->GetAccountPartialMatch(str_MyAcct);
            if (NULL == pMyAccount)
            {
                OTLog::vOutput(0, "Aborting: Unable to find specified myacct: %s\n", str_MyAcct.c_str());
                return 0;
            }
        }
        if (NULL != pMyAccount)
        {
            OTString strTemp;
            pMyAccount->GetPurportedAccountID().GetString(strTemp);
            str_MyAcct = strTemp.Get();
            OTLog::vOutput(0, "Using as myacct: %s\n", str_MyAcct.c_str());
        }
    }

    OTPseudonym * pHisNym = NULL;
    if (str_HisNym.size() > 0)
    {
        pHisNym = pWallet->GetNymByID(str_HisNym);
        if (NULL == pHisNym)
        {
            pHisNym = pWallet->GetNymByIDPartialMatch(str_HisNym);
        }
        if (NULL != pHisNym)
        {
            OTString strTemp;
            pHisNym->GetIdentifier(strTemp);
            str_HisNym = strTemp.Get();
            OTLog::vOutput(0, "Using as hisnym: %s\n", str_HisNym.c_str());
        }
    }

    OTAccount * pHisAccount = NULL;
    if (str_HisAcct.size() > 0)
    {
        pHisAccount = pWallet->GetAccount(str_HisAcct);
        if (NULL == pHisAccount)
        {
            pHisAccount = pWallet->GetAccountPartialMatch(str_HisAcct);
        }
        if (NULL != pHisAccount)
        {
            OTString strTemp;
            pHisAccount->GetPurportedAccountID().GetString(strTemp);
            str_HisAcct = strTemp.Get();
            OTLog::vOutput(0, "Using as hisacct: %s\n", str_HisAcct.c_str());
        }
    }

    OTIdentifier thePurseAssetTypeID;
    OTAssetContract * pMyAssetContract = NULL;
    if (str_MyPurse.size() > 0)
    {
        pMyAssetContract = pWallet->GetAssetContract(str_MyPurse);
        if (NULL == pMyAssetContract)
        {
            pMyAssetContract = pWallet->GetAssetContractPartialMatch(str_MyPurse);
        }
        if (NULL != pMyAssetContract)
        {
            pMyAssetContract->GetIdentifier(thePurseAssetTypeID);
            OTString strTemp;
            pMyAssetContract->GetIdentifier(strTemp);
            str_MyPurse = strTemp.Get();
            OTLog::vOutput(0, "Using as mypurse: %s\n", str_MyPurse.c_str());
        }
    }
    else
    {
        // if no purse (asset type) ID was provided, but MyAccount WAS provided, then
        // use the asset type for the account instead.
        if (NULL != pMyAccount)
        {
            thePurseAssetTypeID = pMyAccount->GetAssetTypeID();
            if (!thePurseAssetTypeID.IsEmpty())
            {
                OTString strTemp(thePurseAssetTypeID);
                str_MyPurse = strTemp.Get();
                OTLog::vOutput(0, "Using as mypurse: %s\n", str_MyPurse.c_str());
            }
        }
    }

    OTIdentifier hisPurseAssetTypeID;
    OTAssetContract * pHisAssetContract = NULL;
    if (str_HisPurse.size() > 0)
    {
        pHisAssetContract = pWallet->GetAssetContract(str_HisPurse);
        if (NULL == pHisAssetContract)
        {
            pHisAssetContract = pWallet->GetAssetContractPartialMatch(str_HisPurse);
        }
        if (NULL != pHisAssetContract)
        {
            pHisAssetContract->GetIdentifier(hisPurseAssetTypeID);
            OTString strTemp;
            pHisAssetContract->GetIdentifier(strTemp);
            str_HisPurse = strTemp.Get();
            OTLog::vOutput(0, "Using as hispurse: %s\n", str_HisPurse.c_str());
        }
    }
    else
    {
        // If no "HisPurse" was provided, but str_HisAcct WAS, then we use the
        // asset type of str_HisAcct as str_HisPurse.
        if (NULL != pHisAccount)
        {
            hisPurseAssetTypeID = pHisAccount->GetAssetTypeID();
        }
    }

    if (!hisPurseAssetTypeID.IsEmpty())
    {
        OTString strTempAssetType(hisPurseAssetTypeID);
        str_HisPurse = strTempAssetType.Get();
        OTLog::vOutput(0, "Using as hispurse: %s\n", str_HisPurse.c_str());
    }

    OTLog::Output(0, "\n");

    if (NULL != pServerContract && NULL != pMyNym)
    {
        OTAPI_Wrap::OTAPI()->GetClient()->SetFocusToServerAndNym(*pServerContract, *pMyNym, OTAPI_Wrap::OTAPI()->GetTransportCallback());
    }

    if (str_Args.size() > 0)
    {
        str_Args += " ";
    }
    str_Args += "ot_cli_command ";

    if (opt.getArgc() == 1)
    {
        str_Args += opt.getArgv(0);;
    }
    else
    {
        OTLog::vOutput(0, "Expecting a single opentxs command:\n\n");
        str_Args += "list";
    }

    OTCleanup<OTVariable> angelArgs(SetGlobalVariable(madeEasy, "Args", str_Args));
    OTCleanup<OTVariable> angelMyAcct(SetGlobalVariable(madeEasy, "MyAcct", str_MyAcct));
    OTCleanup<OTVariable> angelMyNym(SetGlobalVariable(madeEasy, "MyNym", str_MyNym));
    OTCleanup<OTVariable> angelMyPurse(SetGlobalVariable(madeEasy, "MyPurse", str_MyPurse));
    OTCleanup<OTVariable> angelHisAcct(SetGlobalVariable(madeEasy, "HisAcct", str_HisAcct));
    OTCleanup<OTVariable> angelHisNym(SetGlobalVariable(madeEasy, "HisNym", str_HisNym));
    OTCleanup<OTVariable> angelHisPurse(SetGlobalVariable(madeEasy, "HisPurse", str_HisPurse));
    OTCleanup<OTVariable> angelServer(SetGlobalVariable(madeEasy, "Server", str_Server));

    madeEasy.opentxs_copy_variables();

    OTLog::Output(1, "Script output:\n\n");

    int result = madeEasy.opentxs_main_loop();
    return opt.getArgc() == 1 ? result : -2;
}


int main(int argc, char* argv[])
{
    class __OTclient_RAII
    {
    public:
        __OTclient_RAII()
        {
             OTAPI_Wrap::AppInit(); 
        }
        ~__OTclient_RAII()
        {
            OTAPI_Wrap::AppCleanup();
        }
    };

    //
    // This makes SURE that AppCleanup() gets called before main() exits (without any
    // twisted logic being necessary below, for that to happen.)
    //
    __OTclient_RAII the_client_cleanup;

    //

    if (NULL == OTAPI_Wrap::OTAPI()) return -1;  // error out if we don't have the API.

    // COMMAND-LINE OPTIONS (and default values from files.)
    //

    OTAPI_Wrap::OTAPI()->LoadWallet();

    std::map<string, string> macros;
    std::vector<int> errorLineNumbers;
    std::vector<string> errorCommands;

    OT_ME madeEasy;

    AnyOption opt;
    HandleCommandLineArguments(argc, argv, opt);

    if (opt.getArgc() != 0)
    {
        return ProcessCommand(madeEasy, opt);
    }

    int lineNumber = 0;
    bool bEchoCommand = opt.getFlag("echocommand") || opt.getFlag("test");
    bool bEchoExpand = opt.getFlag("echoexpand") || opt.getFlag("test");
    bool bNoPrompt = opt.getFlag("noprompt") || opt.getFlag("test");
    int processed = 0;
    int failed = 0;
    while (true)
    {
        // get next command line from input stream
        if (!bNoPrompt)
        {
            std::cout << "\nopentxs> ";
        }
        string cmd;
        getline(std::cin, cmd);

        // end of file stops processing commands
        if (std::cin.eof())
        {
            break;
        }

        lineNumber++;

        // quit/exit the command loop?
        cmd = trim(cmd);
        if (bEchoCommand)
        {
            std::cout << cmd << std::endl;
        }

        if (cmd == "quit" || cmd == "exit")
        {
            break;
        }

        // empty lines and lines starting with a hash character are seen as comments
        if (cmd.size() == 0 || cmd[0] == '#')
        {
            continue;
        }

        string originalCmd = cmd;

        // lines starting with a dollar sign character denote the definition of a macro of the form:
        // $macroName = macroValue
        // whitespace around the equal sign is optional
        // <macroName> can be any combination of A-Z, a-z, 0-9, or _
        // <macroValue> is anything after the equal sign and whitespace-trimmed
        // note that <macroValue> can be an empty string
        // note that the dollar sign itself is part of the immediately following macro name
        // note that a macro value stays valid for the entire lifetime of the command loop
        // note that macro expansion is done on the command line before processing the line
        //      this means that a macro is allowed to contain command line escape characters
        // note that macro expansion is recursive until no expansions are found any more
        //      this means that a macro is allowed to contain other macros
        if (cmd[0] == '$')
        {
            // determine the macro name
            size_t nameLength = 1;
            while (nameLength < cmd.length() && (std::isalnum(cmd[nameLength]) || cmd[nameLength] == '_'))
            {
                nameLength++;
            }
            string macroName = cmd.substr(0, nameLength);

            // skip whitespace
            size_t i = nameLength;
            while (i < cmd.length() && std::isspace(cmd[i]))
            {
                i++;
            }

            if (i == cmd.length() || cmd[i] != '=')
            {
                OTLog::vOutput(0, "\n\n***ERROR***\n"
                    "Expected macro definition of the form: $macroName = macroValue\n"
                    "Command was: %s", cmd.c_str());
                continue;
            }

            // remainder of line after trimming whitespace is macro value
            string macroValue = cmd.substr(i + 1);
            macros[macroName] = trim(macroValue);
            continue;
        }

        // now replace any macro in the command line with its value
        // unknown macro names will cause an error message instead of command execution
        // note that all macro names are 'maximum munch'
        int expansions = 0;
        for (size_t macro = cmd.find_first_of("$"); macro != string::npos; macro = cmd.find_first_of("$", macro + 1))
        {
            // first see if this is an escaped literal
            if (macro > 0 && cmd[macro - 1] == '\\')
            {
                continue;
            }

            // gather rest of macro name 'maximum munch'
            size_t macroEnd = macro + 1;
            while (macroEnd < cmd.length() && (std::isalnum(cmd[macroEnd]) || cmd[macroEnd] == '_'))
            {
                macroEnd++;
            }
            
            // has this macro been defined?
            string macroName = cmd.substr(macro, macroEnd - macro);
            std::map<string, string>::iterator found = macros.find(macroName);
            if (found == macros.end())
            {
                OTLog::vOutput(0, "\n\n***ERROR***\n"
                    "Macro expansion failed.\n"
                    "Unknown macro: %s\n"
                    "Command was: %s", macroName.c_str(), cmd.c_str());
                expansions = 100;
                break;
            }

            string & macroValue = found->second;

            // limit to 100 expansions to avoid endless recusion loop
            expansions++;
            if (expansions > 100)
            {
                OTLog::vOutput(0, "\n\n***ERROR***\n"
                    "Macro expansion failed.\n"
                    "Too many expansions at macro: %s\n"
                    "Command was: %s", macroName.c_str(), cmd.c_str());
                break;
            }

            // limit to 10000 characters to avoid crazy recursive expansions
            if (cmd.length() + macroValue.length() > 10000)
            {
                OTLog::vOutput(0, "\n\n***ERROR***\n"
                    "Macro expansion failed.\n"
                    "Command length exceeded at macro: %s\n"
                    "Macro value is: %s\n"
                    "Command was: %s", macroName.c_str(), macroValue.c_str(), cmd.c_str());
                expansions = 100;
                break;
            }

            // expand the command line
            cmd = cmd.substr(0, macro) + macroValue + cmd.substr(macroEnd);
        }

        if (bEchoExpand && cmd != originalCmd)
        {
            std::cout << cmd << std::endl;
        }

        // skip command when anything during macro expansion failed
        if (expansions > 99)
        {
            continue;
        }

        // '!' indicates that we expect this command to fail
        //     which is very useful for running a test script
        bool bExpectFailure = cmd[0] == '!';

        // Parse command string into its separate parts so it can be passed as an argc/argv combo
        // Whitespace separates args as usual.
        // To include whitespace in an arg surround the entire arg with double quotes
        // An unterminated double-quoted arg will auto-terminate at end of line
        // All characters are taken literal except for: double quote, dollar sign, and backslash
        // To take any character literal, precede it with a backslash
        std::vector<string> arguments;

        // add original command name
        arguments.push_back(argv[0]);

        // set up buffer that will receive the separate arguments
        char * pBuf = new char[cmd.length() + 1];
        char * pArg = pBuf;

        // start at actual command
        size_t i = bExpectFailure ? 1 : 0;
        while (i < cmd.length())
        {
            // skip any whitespace
            while (i < cmd.length() && std::isspace(cmd[i]))
            {
                i++;
            }
            if (i == cmd.length())
            {
                // it was trailing whitespace; we're done
                break;
            }

            // remember where we start this new argument in the buffer
            char * pStart = pArg;

            // unquoted argument?
            if (cmd[i] != '"')
            {
                // take everything until end of line or next whitespace
                while (i < cmd.length() && !std::isspace(cmd[i]))
                {
                    // unescaped literal character?
                    if (cmd[i] != '\\')
                    {
                        // yep, add to buffer and go for next
                        *pArg++ = cmd[i++];
                        continue;
                    }

                    // take next character literal unless it was the end of line
                    // in which case we simply add the backslash as a literal character
                    *pArg++ = i < cmd.length() ? cmd[i++] : '\\';
                }

                // end of argument reached, terminate an add to arguments array
                *pArg++ = '\0';
                arguments.push_back(pStart);

                // look for next argument
                continue;
            }

            // double quoted argument, skip the quote
            i++;

            // take everything until end of line or next double quote
            while (i < cmd.length() && cmd[i] != '"')
            {
                // unescaped literal character?
                if (cmd[i] != '\\')
                {
                    // yep, add to buffer and go for next
                    *pArg++ = cmd[i++];
                    continue;
                }

                // take next character literal unless it was the end of line
                // in which case we simply add the backslash as a literal character
                *pArg++ = i < cmd.length() ? cmd[i++] : '\\';
            }

            // end of argument reached, terminate an add to arguments array
            *pArg++ = '\0';
            arguments.push_back(pStart);

            // skip terminating double quote or end of line
            i++;
        }

        //set up a new argc/argv combo
        int newArgc = arguments.size();
        char ** newArgv = new char *[newArgc];
        for (int i = 0; i < newArgc; i++)
        {
            newArgv[i] = const_cast<char *>(arguments[i].c_str());
        }

        // preprocess the command line
        AnyOption opt;
        HandleCommandLineArguments(newArgc, newArgv, opt);

        bool bFailedCommand = 0 != ProcessCommand(madeEasy, opt);
        if (bExpectFailure)
        {
            if (!bFailedCommand)
            {
                failed++;
                OTLog::vOutput(0, "\n\n***ERROR***\nExpected command to fail.\nSucceeding command was: %s", cmd.c_str());
                errorLineNumbers.push_back(lineNumber);
                errorCommands.push_back(originalCmd);
            }
        }
        else
        {
            if (bFailedCommand)
            {
                failed++;
                OTLog::vOutput(0, "\n\n***ERROR***\nFailed command was: %s", cmd.c_str());
                errorLineNumbers.push_back(lineNumber);
                errorCommands.push_back(originalCmd);
            }
        }

        delete [] newArgv;
        delete [] pBuf;

        OTLog::Output(0, "\n\n");
        processed++;
    }

    std::cout << "\n\n" << processed << " commands were processed.\n" << failed << " commands failed.\n" << std::endl;

    if (opt.getFlag("errorList") || opt.getFlag("test"))
    {
        for (size_t i = 0; i < errorLineNumbers.size(); i++)
        {
            std::cout << "\nFailed line " << errorLineNumbers[i] << ": " << errorCommands[i] << "." << std::endl;
        }
    }

    return 0;
}
