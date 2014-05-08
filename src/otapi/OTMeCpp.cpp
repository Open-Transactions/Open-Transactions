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

#include "OTMeCpp.hpp"

#include <ot_commands_ot.hpp>
#include <ot_made_easy_ot.hpp>
#include <ot_otapi_ot.hpp>


OTMeCpp::OTMeCpp()
{
}


OTMeCpp::~OTMeCpp()
{
}


bool OTMeCpp::make_sure_enough_trans_nums(const int32_t nNumberNeeded,
    const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    return MadeEasy::insure_enough_nums(nNumberNeeded, SERVER_ID, NYM_ID);
}


std::string OTMeCpp::register_nym(const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    return MadeEasy::register_nym(SERVER_ID, NYM_ID);
}


std::string OTMeCpp::check_user(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & TARGET_NYM_ID)
{
    return MadeEasy::check_user(SERVER_ID, NYM_ID, TARGET_NYM_ID);
}


std::string OTMeCpp::create_pseudonym(const int32_t nKeybits,
    const std::string & NYM_ID_SOURCE,
    const std::string & ALT_LOCATION)
{
    return MadeEasy::create_pseudonym(nKeybits, NYM_ID_SOURCE, ALT_LOCATION);
}


std::string OTMeCpp::issue_asset_type(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & THE_CONTRACT)
{
    return MadeEasy::issue_asset_type(SERVER_ID, NYM_ID, THE_CONTRACT);
}


std::string OTMeCpp::issue_basket_currency(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & THE_BASKET)
{
    return MadeEasy::issue_basket_currency(SERVER_ID, NYM_ID, THE_BASKET);
}


std::string OTMeCpp::exchange_basket_currency(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_TYPE_ID,
    const std::string & THE_BASKET,
    const std::string & ACCOUNT_ID,
    const bool IN_OR_OUT)
{
    return MadeEasy::exchange_basket_currency(SERVER_ID, NYM_ID, ASSET_TYPE_ID, THE_BASKET, ACCOUNT_ID, IN_OR_OUT);
}


std::string OTMeCpp::retrieve_contract(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & CONTRACT_ID)
{
    return MadeEasy::retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID);
}


std::string OTMeCpp::load_or_retrieve_contract(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & CONTRACT_ID)
{
    return MadeEasy::load_or_retrieve_contract(SERVER_ID, NYM_ID, CONTRACT_ID);
}


std::string OTMeCpp::create_asset_acct(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_TYPE_ID)
{
    return MadeEasy::create_asset_acct(SERVER_ID, NYM_ID, ASSET_TYPE_ID);
}


std::string OTMeCpp::stat_asset_account(const std::string & ACCOUNT_ID)
{
    return MadeEasy::stat_asset_account(ACCOUNT_ID);
}


bool OTMeCpp::retrieve_account(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCOUNT_ID,
    const bool bForceDownload)
{
    return MadeEasy::retrieve_account(SERVER_ID, NYM_ID, ACCOUNT_ID, bForceDownload);
}


bool OTMeCpp::retrieve_nym(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const bool bForceDownload)
{
    bool bWasSent = false;
    return OT_Command::details_refresh_nym(SERVER_ID, NYM_ID, bWasSent, bForceDownload);
}


std::string OTMeCpp::send_transfer(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_FROM,
    const std::string & ACCT_TO,
    const int64_t AMOUNT,
    const std::string & NOTE)
{
    return MadeEasy::send_transfer(SERVER_ID, NYM_ID, ACCT_FROM, ACCT_TO, AMOUNT, NOTE);
}


std::string OTMeCpp::process_inbox(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCOUNT_ID,
    const std::string & RESPONSE_LEDGER)
{
    return MadeEasy::process_inbox(SERVER_ID, NYM_ID, ACCOUNT_ID, RESPONSE_LEDGER);
}


bool OTMeCpp::accept_inbox_items(const std::string & ACCOUNT_ID,
    int32_t nItemType,
    const std::string & INDICES)
{
    return OT_Command::accept_inbox_items(ACCOUNT_ID, nItemType, INDICES) == 1;
}


bool OTMeCpp::discard_incoming_payments(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & INDICES)
{
    return OT_Command::details_discard_incoming(SERVER_ID, NYM_ID, INDICES) == 1;
}


bool OTMeCpp::cancel_outgoing_payments(const std::string & NYM_ID,
    const std::string & ACCOUNT_ID,
    const std::string & INDICES)
{
    return OT_Command::details_cancel_outgoing(NYM_ID, ACCOUNT_ID, INDICES) == 1;
}


int32_t OTMeCpp::accept_from_paymentbox(const std::string & ACCOUNT_ID,
    const std::string & INDICES,
    const std::string & PAYMENT_TYPE)
{
    return OT_Command::accept_from_paymentbox(ACCOUNT_ID, INDICES, PAYMENT_TYPE);
}


std::string OTMeCpp::load_public_encryption_key(const std::string & NYM_ID)
{
    return MadeEasy::load_public_encryption_key(NYM_ID);
}


std::string OTMeCpp::load_public_signing_key(const std::string & NYM_ID)
{
    return MadeEasy::load_public_signing_key(NYM_ID);
}


std::string OTMeCpp::load_or_retrieve_encrypt_key(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & TARGET_NYM_ID)
{
    return MadeEasy::load_or_retrieve_encrypt_key(SERVER_ID, NYM_ID, TARGET_NYM_ID);
}


std::string OTMeCpp::load_or_retrieve_signing_key(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & TARGET_NYM_ID)
{
    return MadeEasy::load_or_retrieve_signing_key(SERVER_ID, NYM_ID, TARGET_NYM_ID);
}


std::string OTMeCpp::send_user_msg_pubkey(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & RECIPIENT_PUBKEY,
    const std::string & THE_MESSAGE)
{
    return MadeEasy::send_user_msg_pubkey(SERVER_ID, NYM_ID, RECIPIENT_NYM_ID, RECIPIENT_PUBKEY, THE_MESSAGE);
}


std::string OTMeCpp::send_user_pmnt_pubkey(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & RECIPIENT_PUBKEY,
    const std::string & THE_INSTRUMENT)
{
    return MadeEasy::send_user_pmnt_pubkey(SERVER_ID, NYM_ID, RECIPIENT_NYM_ID, RECIPIENT_PUBKEY, THE_INSTRUMENT);
}


std::string OTMeCpp::send_user_cash_pubkey(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & RECIPIENT_PUBKEY,
    const std::string & THE_INSTRUMENT,
    const std::string & INSTRUMENT_FOR_SENDER)
{
    return MadeEasy::send_user_cash_pubkey(SERVER_ID, NYM_ID, RECIPIENT_NYM_ID, RECIPIENT_PUBKEY, THE_INSTRUMENT, INSTRUMENT_FOR_SENDER);
}


std::string OTMeCpp::send_user_msg(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & THE_MESSAGE)
{
    return MadeEasy::send_user_msg(SERVER_ID, NYM_ID, RECIPIENT_NYM_ID, THE_MESSAGE);
}


std::string OTMeCpp::send_user_payment(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & THE_PAYMENT)
{
    return MadeEasy::send_user_payment(SERVER_ID, NYM_ID, RECIPIENT_NYM_ID, THE_PAYMENT);
}


std::string OTMeCpp::send_user_cash(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & THE_PAYMENT,
    const std::string & SENDERS_COPY)
{
    return MadeEasy::send_user_cash(SERVER_ID, NYM_ID, RECIPIENT_NYM_ID, THE_PAYMENT, SENDERS_COPY);
}


bool OTMeCpp::withdraw_and_send_cash(const std::string & ACCT_ID,
    const std::string & RECIPIENT_NYM_ID,
    const std::string & MEMO,
    const int64_t AMOUNT)
{
    std::string recipient_nym_id = RECIPIENT_NYM_ID;

    return OT_Command::withdraw_and_send_cash(ACCT_ID, recipient_nym_id, MEMO, ::to_string(AMOUNT));
}


std::string OTMeCpp::get_payment_instrument(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const int32_t nIndex,
    const std::string & PRELOADED_INBOX)
{
    return MadeEasy::get_payment_instrument(SERVER_ID, NYM_ID, nIndex, PRELOADED_INBOX);
}


std::string OTMeCpp::get_box_receipt(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const int32_t nBoxType,
    const int64_t TRANS_NUM)
{
    return MadeEasy::get_box_receipt(SERVER_ID, NYM_ID, ACCT_ID, nBoxType, ::to_string(TRANS_NUM));
}


std::string OTMeCpp::retrieve_mint(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_ID)
{
    return MadeEasy::retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID);
}


std::string OTMeCpp::load_or_retrieve_mint(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_ID)
{
    return MadeEasy::load_or_retrieve_mint(SERVER_ID, NYM_ID, ASSET_ID);
}


std::string OTMeCpp::query_asset_types(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ENCODED_MAP)
{
    return MadeEasy::query_asset_types(SERVER_ID, NYM_ID, ENCODED_MAP);
}


std::string OTMeCpp::create_market_offer(const std::string & ASSET_ACCT_ID,
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
    return MadeEasy::create_market_offer(ASSET_ACCT_ID, CURRENCY_ACCT_ID,
        ::to_string(scale), ::to_string(minIncrement), ::to_string(quantity), ::to_string(price),
        bSelling, ::to_string(lLifespanInSeconds), STOP_SIGN, ::to_string(ACTIVATION_PRICE));
}


std::string OTMeCpp::kill_market_offer(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ASSET_ACCT_ID,
    const int64_t TRANS_NUM)
{
    return MadeEasy::kill_market_offer(SERVER_ID, NYM_ID, ASSET_ACCT_ID, ::to_string(TRANS_NUM));
}


std::string OTMeCpp::kill_payment_plan(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const int64_t TRANS_NUM)
{
    return MadeEasy::kill_payment_plan(SERVER_ID, NYM_ID, ACCT_ID, ::to_string(TRANS_NUM));
}


std::string OTMeCpp::cancel_payment_plan(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & THE_PAYMENT_PLAN)
{
    return MadeEasy::cancel_payment_plan(SERVER_ID, NYM_ID, THE_PAYMENT_PLAN);
}


std::string OTMeCpp::activate_smart_contract(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & AGENT_NAME,
    const std::string & THE_SMART_CONTRACT)
{
    return MadeEasy::activate_smart_contract(SERVER_ID, NYM_ID, ACCT_ID, AGENT_NAME, THE_SMART_CONTRACT);
}


std::string OTMeCpp::trigger_clause(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const int64_t TRANS_NUM,
    const std::string & CLAUSE_NAME,
    const std::string & STR_PARAM)
{
    return MadeEasy::trigger_clause(SERVER_ID, NYM_ID, ::to_string(TRANS_NUM), CLAUSE_NAME, STR_PARAM);
}


std::string OTMeCpp::withdraw_cash(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const int64_t AMOUNT)
{
    return MadeEasy::withdraw_cash(SERVER_ID, NYM_ID, ACCT_ID, AMOUNT);
}


int32_t OTMeCpp::easy_withdraw_cash(const std::string & ACCT_ID,
    const int64_t AMOUNT)
{
    return OT_Command::details_withdraw_cash(ACCT_ID, AMOUNT);
}


std::string OTMeCpp::export_cash(const std::string & SERVER_ID,
    const std::string & FROM_NYM_ID,
    const std::string & ASSET_TYPE_ID,
    const std::string & TO_NYM_ID,
    const std::string & STR_INDICES,
    bool bPasswordProtected,
    std::string & STR_RETAINED_COPY)
{
    std::string to_nym_id = TO_NYM_ID;
    return OT_Command::details_export_cash(SERVER_ID, FROM_NYM_ID, ASSET_TYPE_ID, to_nym_id, STR_INDICES, bPasswordProtected, STR_RETAINED_COPY);
}


std::string OTMeCpp::withdraw_voucher(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & RECIP_NYM_ID,
    const std::string & STR_MEMO,
    const int64_t AMOUNT)
{
    return MadeEasy::withdraw_voucher(SERVER_ID, NYM_ID, ACCT_ID, RECIP_NYM_ID, STR_MEMO, AMOUNT);
}


std::string OTMeCpp::pay_dividend(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & SOURCE_ACCT_ID,
    const std::string & SHARES_ASSET_ID,
    const std::string & STR_MEMO,
    const int64_t AMOUNT_PER_SHARE)
{
    return MadeEasy::pay_dividend(SERVER_ID, NYM_ID, SOURCE_ACCT_ID, SHARES_ASSET_ID, STR_MEMO, AMOUNT_PER_SHARE);
}


std::string OTMeCpp::deposit_cheque(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & STR_CHEQUE)
{
    return MadeEasy::deposit_cheque(SERVER_ID, NYM_ID, ACCT_ID, STR_CHEQUE);
}


int32_t OTMeCpp::deposit_cash(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & STR_PURSE)
{
    return OT_Command::details_deposit_purse(SERVER_ID, ACCT_ID, NYM_ID, STR_PURSE, "");
}


int32_t OTMeCpp::deposit_local_purse(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & ACCT_ID,
    const std::string & STR_INDICES)
{
    return OT_Command::details_deposit_purse(SERVER_ID, ACCT_ID, NYM_ID, "", STR_INDICES);
}


std::string OTMeCpp::get_market_list(const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    return MadeEasy::get_market_list(SERVER_ID, NYM_ID);
}


std::string OTMeCpp::get_market_offers(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & MARKET_ID,
    const int64_t MAX_DEPTH)
{
    return MadeEasy::get_market_offers(SERVER_ID, NYM_ID, MARKET_ID, MAX_DEPTH);
}


std::string OTMeCpp::get_nym_market_offers(const std::string & SERVER_ID,
    const std::string & NYM_ID)
{
    return MadeEasy::get_nym_market_offers(SERVER_ID, NYM_ID);
}


std::string OTMeCpp::get_market_recent_trades(const std::string & SERVER_ID,
    const std::string & NYM_ID,
    const std::string & MARKET_ID)
{
    return MadeEasy::get_market_recent_trades(SERVER_ID, NYM_ID, MARKET_ID);
}


std::string OTMeCpp::adjust_usage_credits(const std::string & SERVER_ID,
    const std::string & USER_NYM_ID,
    const std::string & TARGET_NYM_ID,
    const std::string & ADJUSTMENT)
{
    return MadeEasy::adjust_usage_credits(SERVER_ID, USER_NYM_ID, TARGET_NYM_ID, ADJUSTMENT);
}
