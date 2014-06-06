/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA1

 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
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
 *   -- otserver......Server Application....LICENSE:....AGPLv3
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

#ifdef OT_USE_SCRIPT_CHAI

#include "OTMeChai.hpp"
#include "OTVariable.hpp"

#include <chaiscript/chaiscript.hpp>

#ifdef OT_USE_CHAI_STDLIB
#include <chaiscript/chaiscript_stdlib.hpp>
#endif

#include <OT_ME.hpp>


OTMeChai::OTMeChai(OT_ME * pMe)
: m_pMe(pMe)
{
}


OTMeChai::~OTMeChai()
{
}


void OTMeChai::AddVariable(OTVariable & variable)
{
    m_pMe->AddVariable(variable.GetName().Get(), variable);
}


bool OTMeChai::ExecuteScript_ReturnBool(const OTString & code, const char * pFunction)
{
    return m_pMe->ExecuteScript_ReturnBool(code.Get(), pFunction);
}


int32_t OTMeChai::ExecuteScript_ReturnInt(const OTString & code, const char * pFunction)
{
    return m_pMe->ExecuteScript_ReturnInt(code.Get(), pFunction);
}


std::string OTMeChai::ExecuteScript_ReturnString(const OTString & code, const char * pFunction)
{
    return m_pMe->ExecuteScript_ReturnString(code.Get(), pFunction);
}


void OTMeChai::ExecuteScript_ReturnVoid(const OTString & code, const char * pFunction)
{
    m_pMe->ExecuteScript_ReturnVoid(code.Get(), pFunction);
}


// Note optimization:
// Until the actual C++ high-level API is written, we'll just use this
// as a C++ wrapper to the existing high-level API written in OT Script.
// Tha way, all the other languages can wrap this using swig.
//
// Notice (for those languages) that if you make an instance of OT_ME
// and keep it around (using it for all your server calls) notice that
// it will only have to instantiate and setup the OTScript object ONCE,
// instead of having to do it for every single call.
//
// Therefore, for optimization purposes, we recommend the programmatic
// user to keep an instance of OT_ME around as long as you need to use it,
// and NOT instantiate it for every time you need to use it, as it will
// probably run noticeably faster.
//


bool OTMeChai::make_sure_enough_trans_nums(const int32_t nNumberNeeded,
    const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    OTString code;
    code.Format("{ var bResult = OT_ME_insure_enough_nums(int32_t(%" PRId32 "), \"%s\", \"%s\"); }",
        nNumberNeeded, SERVER_ID.c_str(), NYM_ID.c_str());
     return ExecuteScript_ReturnBool(code, __FUNCTION__);
}


std::string OTMeChai::register_nym(const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_register_nym(\"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::check_user(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & TARGET_NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_check_user(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), TARGET_NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::create_pseudonym(const int32_t nKeybits,
    const std::string & NYM_ID_SOURCE,
    const std::string & ALT_LOCATION)
{
    const std::string str_var_name1("varSource");
    OTVariable varSource(str_var_name1, NYM_ID_SOURCE);
    AddVariable(varSource);
    const std::string str_var_name2("varAlt");
    OTVariable varAlt(str_var_name2, ALT_LOCATION);
    AddVariable(varAlt);
    OTString code;
    code.Format("{ var strResult = OT_ME_create_pseudonym(int32_t(%"  PRId32"), %s, %s); }",
        nKeybits, str_var_name1.c_str(), str_var_name2.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::issue_asset_type(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & THE_CONTRACT)
{
    const std::string str_var_name1("varContract");
    OTVariable varTheContract(str_var_name1, THE_CONTRACT);
    AddVariable(varTheContract);
    OTString code;
    code.Format("{ var strResult = OT_ME_issue_asset_type(\"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), str_var_name1.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::issue_basket_currency(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & THE_BASKET)
{
    const std::string str_var_name1("varContract");
    OTVariable varTheContract(str_var_name1, THE_BASKET);
    AddVariable(varTheContract);
    OTString code;
    code.Format("{ var strResult = OT_ME_issue_basket_currency(\"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), str_var_name1.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::exchange_basket_currency(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_TYPE_ID,
    const std::string & THE_BASKET,
    const std::string & ACCOUNT_ID,
    const bool IN_OR_OUT)
{
    const std::string str_var_name1("varContract");
    OTVariable varTheContract(str_var_name1, THE_BASKET);
    AddVariable(varTheContract);
    OTString code;
    code.Format("{ var strResult = OT_ME_exchange_basket_currency(\"%s\", \"%s\", \"%s\", %s, \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ASSET_TYPE_ID.c_str(), str_var_name1.c_str(),
        ACCOUNT_ID.c_str(), IN_OR_OUT ? "true" : "false");
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::retrieve_contract(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & CONTRACT_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_retrieve_contract(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), CONTRACT_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::load_or_retrieve_contract(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & CONTRACT_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_load_or_retrieve_contract(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), CONTRACT_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::create_asset_acct(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_TYPE_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_create_asset_acct(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ASSET_TYPE_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::stat_asset_account(const std::string & ACCOUNT_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_stat_asset_account(\"%s\"); }",
        ACCOUNT_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


bool OTMeChai::retrieve_account( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCOUNT_ID,
    const bool bForceDownload)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_retrieve_account(\"%s\", \"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCOUNT_ID.c_str(), bForceDownload ? "true" : "false");
    return ExecuteScript_ReturnBool(code, __FUNCTION__);
}


bool OTMeChai::retrieve_nym(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const bool bForceDownload)
{
    OTString code;
    code.Format("{ var bWasSent = OTBool(false); var bResult = details_refresh_nym(\"%s\", \"%s\", bWasSent, %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), bForceDownload ? "true" : "false");
    return ExecuteScript_ReturnBool(code, __FUNCTION__);
}


std::string OTMeChai::send_transfer(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_FROM,
    const std::string & ACCT_TO,
    const int64_t AMOUNT,
    const std::string & NOTE)
{
    const std::string str_var_name1("varNote");
    OTVariable varNote(str_var_name1, NOTE);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_send_transfer(\"%s\", \"%s\", \"%s\", \"%s\", int64_t(%" PRId64"), %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCT_FROM.c_str(), ACCT_TO.c_str(),
        AMOUNT, str_var_name1.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::process_inbox(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCOUNT_ID,
    const std::string & RESPONSE_LEDGER)
{
    const std::string str_var_name("varResponse");
    OTVariable varResponse(str_var_name, RESPONSE_LEDGER);
    AddVariable(varResponse);
    OTString code;
    code.Format("{ var strResult = OT_ME_process_inbox(\"%s\", \"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCOUNT_ID.c_str(), str_var_name.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


bool OTMeChai::accept_inbox_items(const std::string & ACCOUNT_ID,
    int32_t nItemType,
    const std::string & INDICES)
{
    OTString code;
    code.Format("{ var nResult = accept_inbox_items(\"%s\", int32_t(%" PRId32"), \"%s\"); var bResult = ((1 == nResult) ? true : false); }",
        ACCOUNT_ID.c_str(), nItemType, INDICES.c_str());
    return ExecuteScript_ReturnBool(code, __FUNCTION__);
}


bool OTMeChai::discard_incoming_payments(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & INDICES)
{
    OTString code;
    code.Format("{ var nResult = details_discard_incoming(\"%s\", \"%s\", \"%s\"); var bResult = ((1 == nResult) ? true : false); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), INDICES.c_str());
    return ExecuteScript_ReturnBool(code, __FUNCTION__);
}


bool OTMeChai::cancel_outgoing_payments (const std::string & NYM_ID,
    const std::string & ACCOUNT_ID,
    const std::string & INDICES)
{
    OTString code;
    code.Format("{ var nResult = details_cancel_outgoing(\"%s\", \"%s\", \"%s\"); var bResult = ((1 == nResult) ? true : false); }",
        NYM_ID.c_str(), ACCOUNT_ID.c_str(), INDICES.c_str());
    return ExecuteScript_ReturnBool(code, __FUNCTION__);
}


int32_t OTMeChai::accept_from_paymentbox(const std::string & ACCOUNT_ID,
    const std::string & INDICES,
    const std::string & PAYMENT_TYPE)
{
    OTString code;
    code.Format("{ var nResult = accept_from_paymentbox(\"%s\", \"%s\", \"%s\"); }",
        ACCOUNT_ID.c_str(), INDICES.c_str(), PAYMENT_TYPE.c_str());
    return ExecuteScript_ReturnInt(code, __FUNCTION__);
}


std::string OTMeChai::load_public_encryption_key(const std::string & NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_load_public_encryption_key(\"%s\"); }",
        NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::load_public_signing_key(const std::string & NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_load_public_signing_key(\"%s\"); }",
        NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::load_or_retrieve_encrypt_key(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & TARGET_NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_load_or_retrieve_encrypt_key(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), TARGET_NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::load_or_retrieve_signing_key(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & TARGET_NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_load_or_retrieve_signing_key(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), TARGET_NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::send_user_msg_pubkey(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & RECIPIENT_PUBKEY,
    const std::string & THE_MESSAGE)
{
    const std::string str_var_name1("varPubkey");
    OTVariable varPubkey(str_var_name1, RECIPIENT_PUBKEY);
    AddVariable(varPubkey);
    const std::string str_var_name2("varNote");
    OTVariable varNote(str_var_name2, THE_MESSAGE);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_send_user_msg_pubkey(\"%s\", \"%s\", \"%s\", %s, %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), RECIPIENT_NYM_ID.c_str(), str_var_name1.c_str(), str_var_name2.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::send_user_pmnt_pubkey(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & RECIPIENT_PUBKEY,
    const std::string & THE_INSTRUMENT)
{
    const std::string str_var_name1("varPubkey");
    OTVariable varPubkey(str_var_name1, RECIPIENT_PUBKEY);
    AddVariable(varPubkey);
    const std::string str_var_name2("varNote");
    OTVariable varNote(str_var_name2, THE_INSTRUMENT);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_send_user_pmnt_pubkey(\"%s\", \"%s\", \"%s\", %s, %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), RECIPIENT_NYM_ID.c_str(), str_var_name1.c_str(), str_var_name2.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::send_user_cash_pubkey(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & RECIPIENT_PUBKEY,
    const std::string & THE_INSTRUMENT,
    const std::string & INSTRUMENT_FOR_SENDER)
{
    const std::string str_var_name1("varPubkey");
    OTVariable varPubkey(str_var_name1, RECIPIENT_PUBKEY);
    AddVariable(varPubkey);
    const std::string str_var_name2("varNote");
    OTVariable varNote(str_var_name2, THE_INSTRUMENT);
    AddVariable(varNote);
    const std::string str_var_name3("varSenderNote");
    OTVariable varSenderNote(str_var_name3, INSTRUMENT_FOR_SENDER);
    AddVariable(varSenderNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_send_user_cash_pubkey(\"%s\", \"%s\", \"%s\", %s, %s, %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), RECIPIENT_NYM_ID.c_str(), str_var_name1.c_str(), str_var_name2.c_str(), str_var_name3.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::send_user_msg(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & THE_MESSAGE)
{
    const std::string str_var_name("varNote");
    OTVariable varNote(str_var_name, THE_MESSAGE);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_send_user_msg(\"%s\", \"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), RECIPIENT_NYM_ID.c_str(), str_var_name.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::send_user_payment(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & THE_PAYMENT)
{
    const std::string str_var_name("varNote");
    OTVariable varNote(str_var_name, THE_PAYMENT);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_send_user_payment(\"%s\", \"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), RECIPIENT_NYM_ID.c_str(), str_var_name.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::send_user_cash(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & THE_PAYMENT,
    const std::string & SENDERS_COPY)
{
    const std::string str_var_name("varNote");
    OTVariable varNote(str_var_name, THE_PAYMENT);
    AddVariable(varNote);

    const std::string str_var_name2("varSenderNote");
    OTVariable varSenderNote(str_var_name2, SENDERS_COPY);
    AddVariable(varSenderNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_send_user_cash(\"%s\", \"%s\", \"%s\", %s, %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), RECIPIENT_NYM_ID.c_str(), str_var_name.c_str(), str_var_name2.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


bool OTMeChai::withdraw_and_send_cash(const std::string & ACCT_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & MEMO,
    const int64_t AMOUNT)
{
    const std::string str_var_name("varNote");
    OTVariable varNote(str_var_name, MEMO);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var bResult = withdraw_and_send_cash(\"%s\", \"%s\", %s, \"%" PRId64"\"); }",
        ACCT_ID.c_str(), RECIPIENT_NYM_ID.c_str(), str_var_name.c_str(), AMOUNT);
    return ExecuteScript_ReturnBool(code, __FUNCTION__);
}


std::string OTMeChai::get_payment_instrument(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const int32_t nIndex,
    const std::string & PRELOADED_INBOX)
{
    const std::string str_var_name("varBox");
    OTVariable varBox(str_var_name, PRELOADED_INBOX);
    AddVariable(varBox);
    OTString code;
    code.Format("{ var strResult = OT_ME_get_payment_instrument(\"%s\", \"%s\", int32_t(%" PRId32"), %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), nIndex, str_var_name.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::get_box_receipt(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const int32_t nBoxType,
    const int64_t TRANS_NUM)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_get_box_receipt(\"%s\", \"%s\", \"%s\", int32_t(%" PRId32"), \"%" PRId64"\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCT_ID.c_str(), nBoxType, TRANS_NUM);
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::retrieve_mint(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_retrieve_mint(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ASSET_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::load_or_retrieve_mint(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_load_or_retrieve_mint(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ASSET_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::query_asset_types(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ENCODED_MAP)
{
    const std::string str_var_name("varMap");
    OTVariable varMap(str_var_name, ENCODED_MAP);
    AddVariable(varMap);
    OTString code;
    code.Format("{ var strResult = OT_ME_query_asset_types(\"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), str_var_name.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::create_market_offer(const std::string & ASSET_ACCT_ID,
    const std::string & CURRENCY_ACCT_ID,
    const int64_t scale,
    const int64_t minIncrement,
    const int64_t quantity,
    const int64_t price,
    const bool bSelling,
    const int64_t lLifespanInSeconds,
    const std::string & STOP_SIGN,
    const int64_t ACTIVATION_PRICE)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_create_market_offer(\"%s\", \"%s\","
        " \"%" PRId64"\", \"%" PRId64"\", \"%" PRId64"\", \"%" PRId64"\", %s, \"%" PRId64"\", \"%s\", \"%" PRId64"\"); }",
        ASSET_ACCT_ID.c_str(), CURRENCY_ACCT_ID.c_str(),
        scale, minIncrement, quantity, price, bSelling ? "true" : "false", lLifespanInSeconds,
        STOP_SIGN.c_str(), ACTIVATION_PRICE
        );
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::kill_market_offer(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_ACCT_ID,
    const int64_t TRANS_NUM)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_kill_market_offer(\"%s\", \"%s\", \"%s\", \"%" PRId64"\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ASSET_ACCT_ID.c_str(), TRANS_NUM);
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::kill_payment_plan( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const int64_t TRANS_NUM)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_kill_payment_plan(\"%s\", \"%s\", \"%s\", \"%" PRId64"\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCT_ID.c_str(), TRANS_NUM);
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::cancel_payment_plan( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & THE_PAYMENT_PLAN)
{
    const std::string str_var_name("varContract");
    OTVariable varContract(str_var_name, THE_PAYMENT_PLAN);
    AddVariable(varContract);
    OTString code;
    code.Format("{ var strResult = OT_ME_cancel_payment_plan(\"%s\", \"%s\", varContract); }",
        SERVER_ID.c_str(), NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::activate_smart_contract( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & AGENT_NAME,
    const std::string & THE_SMART_CONTRACT)
{
    const std::string str_var_name("varContract");
    OTVariable varContract(str_var_name, THE_SMART_CONTRACT);
    AddVariable(varContract);
    OTString code;
    code.Format("{ var strResult = OT_ME_activate_smart_contract(\"%s\", \"%s\", \"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCT_ID.c_str(), AGENT_NAME.c_str(), str_var_name.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::trigger_clause( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const int64_t TRANS_NUM,
    const std::string & CLAUSE_NAME,
    const std::string & STR_PARAM)
{
    const std::string str_var_name("varParameter");
    OTVariable varParameter(str_var_name, STR_PARAM);
    AddVariable(varParameter);
    OTString code;
    code.Format("{ var strResult = OT_ME_trigger_clause(\"%s\", \"%s\", \"%" PRId64"\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), TRANS_NUM, CLAUSE_NAME.c_str(), str_var_name.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::withdraw_cash( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const int64_t AMOUNT)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_withdraw_cash(\"%s\", \"%s\", \"%s\", int64_t(%" PRId64")); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCT_ID.c_str(), AMOUNT);
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


int32_t OTMeChai::easy_withdraw_cash(const std::string & ACCT_ID,
    const int64_t AMOUNT)
{
    OTString code;
    code.Format("{ details_withdraw_cash(\"%s\", int64_t(%" PRId64")); }",
        ACCT_ID.c_str(), AMOUNT);
    return ExecuteScript_ReturnInt(code, __FUNCTION__);
}


std::string OTMeChai::export_cash(const std::string & SERVER_ID,
    const std::string & FROM_NYM_ID,
    const std::string & ASSET_TYPE_ID,
    const std::string & TO_NYM_ID,
    const std::string & STR_INDICES,
    bool bPasswordProtected,
    std::string & STR_RETAINED_COPY)
{
    const std::string str_var_name1("varRetained");
    OTVariable varRetained(str_var_name1, STR_RETAINED_COPY);
    AddVariable(varRetained);
    OTString code;
    code.Format("{ var strResult = details_export_cash(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %s, %s); }",
        SERVER_ID.c_str(), FROM_NYM_ID.c_str(), ASSET_TYPE_ID.c_str(), TO_NYM_ID.c_str(), STR_INDICES.c_str(),
        bPasswordProtected ? "true" : "false",
        str_var_name1.c_str()
        );
    const std::string str_result = ExecuteScript_ReturnString(code, __FUNCTION__);

    if (!str_result.empty())
        STR_RETAINED_COPY = varRetained.GetValueString();

    return str_result;
}


std::string OTMeChai::withdraw_voucher( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & RECIP_NYM_ID,
    const std::string & STR_MEMO,
    const int64_t AMOUNT)
{
    const std::string str_var_name1("varNote");
    OTVariable varNote(str_var_name1, STR_MEMO);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_withdraw_voucher(\"%s\", \"%s\", \"%s\", \"%s\", %s, int64_t(%" PRId64")); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCT_ID.c_str(), RECIP_NYM_ID.c_str(), str_var_name1.c_str(), AMOUNT);
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::pay_dividend( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & SOURCE_ACCT_ID,
    const std::string & SHARES_ASSET_ID,
    const std::string & STR_MEMO,
    const int64_t AMOUNT_PER_SHARE)
{
    const std::string str_var_name1("varNote");
    OTVariable varNote(str_var_name1, STR_MEMO);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_pay_dividend(\"%s\", \"%s\", \"%s\", \"%s\", %s, int64_t(%" PRId64")); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), SOURCE_ACCT_ID.c_str(), SHARES_ASSET_ID.c_str(), str_var_name1.c_str(), AMOUNT_PER_SHARE);
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::deposit_cheque( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & STR_CHEQUE)
{
    const std::string str_var_name1("varNote");
    OTVariable varNote(str_var_name1, STR_CHEQUE);
    AddVariable(varNote);
    OTString code;
    code.Format("{ var strResult = OT_ME_deposit_cheque(\"%s\", \"%s\", \"%s\", %s); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), ACCT_ID.c_str(), str_var_name1.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


int32_t OTMeChai::deposit_cash( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & STR_PURSE)
{
    const std::string str_var_name1("varNote");
    OTVariable varNote(str_var_name1, STR_PURSE);
    AddVariable(varNote);
    OTString code;
    code.Format("{ details_deposit_purse(\"%s\", \"%s\", \"%s\", %s, \"\"); }",
        SERVER_ID.c_str(), ACCT_ID.c_str(), NYM_ID.c_str(), str_var_name1.c_str());
    return ExecuteScript_ReturnInt(code, __FUNCTION__);
}


int32_t OTMeChai::deposit_local_purse(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & STR_INDICES)
{
    OTString code;
    code.Format("{ details_deposit_purse(\"%s\", \"%s\", \"%s\", \"\", \"%s\"); }",
        SERVER_ID.c_str(), ACCT_ID.c_str(), NYM_ID.c_str(), STR_INDICES.c_str());
    return ExecuteScript_ReturnInt(code, __FUNCTION__);
}


std::string OTMeChai::get_market_list( const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_get_market_list(\"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::get_market_offers( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & MARKET_ID,
    const int64_t MAX_DEPTH)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_get_market_offers(\"%s\", \"%s\", \"%s\", int64_t(%" PRId64")); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), MARKET_ID.c_str(), MAX_DEPTH);
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::get_nym_market_offers( const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_get_nym_market_offers(\"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::get_market_recent_trades( const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & MARKET_ID)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_get_market_recent_trades(\"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), NYM_ID.c_str(), MARKET_ID.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}


std::string OTMeChai::adjust_usage_credits( const std::string & SERVER_ID,
    const std::string & USER_NYM_ID,
    const std::string & TARGET_NYM_ID,
    const std::string & ADJUSTMENT)
{
    OTString code;
    code.Format("{ var strResult = OT_ME_adjust_usage_credits(\"%s\", \"%s\", \"%s\", \"%s\"); }",
        SERVER_ID.c_str(), USER_NYM_ID.c_str(), TARGET_NYM_ID.c_str(), ADJUSTMENT.c_str());
    return ExecuteScript_ReturnString(code, __FUNCTION__);
}

#endif // OT_USE_SCRIPT_CHAI
