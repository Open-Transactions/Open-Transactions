#ifndef _H_OT_OTAPI_OT
#define _H_OT_OTAPI_OT


#include "OTCommon.hpp"

#include <string>
#include <iostream>

#ifndef OT_USE_CXX11
#include <cstdlib>
#endif

#include <OTStorage.hpp>

#include <OTAPI.hpp>
#include <OT_ME.hpp>

#define OT_OTAPI_OT


#pragma warning(disable: 4503)


using std::string;


inline string concat   (const string & str1, const string & str2) { return str1 + str2; }
inline void   print    (const string & text)   { std::cout << text << "\n"; }
inline string to_string(const bool     bValue) { return bValue ? "true" : "false"; }
// --------------------------------------------------------------
#ifdef OT_USE_CXX11
inline string  to_string(const int64_t  nValue)   { return std::to_string(nValue); }
inline int32_t to_int   (const string & strValue) { return static_cast<int32_t>(std::stoi(strValue)); }
inline int64_t to_long  (const string & strValue) { return std::stoll(strValue); }
// --------------------------------------------------------------
#else
inline string  to_string(const int64_t  nValue)   { return OTAPI_Wrap::LongToString(nValue); }
inline int32_t to_int   (const string & strValue) { return static_cast<int32_t>(std::atoi(strValue.c_str())); }
inline int64_t to_long  (const string & strValue) { return OTAPI_Wrap::StringToLong(strValue); }
#endif
// --------------------------------------------------------------

class the_lambda_struct;

typedef std::map<string, OTDB::OfferDataNym *> SubMap;
typedef std::map<string, SubMap *> MapOfMaps;
typedef int32_t (*LambdaFunc)(OTDB::OfferDataNym & offer_data, const int32_t nIndex, MapOfMaps & map_of_maps, SubMap & sub_map, the_lambda_struct & extra_vals);


EXPORT OT_OTAPI_OT MapOfMaps * convert_offerlist_to_maps(OTDB::OfferListNym & offerList);
EXPORT OT_OTAPI_OT int32_t find_strange_offers(OTDB::OfferDataNym & offer_data, const int32_t nIndex, MapOfMaps & map_of_maps, SubMap & sub_map, the_lambda_struct & extra_vals); // if 10 offers are printed for the SAME market, nIndex will be 0..9
EXPORT OT_OTAPI_OT int32_t iterate_nymoffers_maps(MapOfMaps & map_of_maps, LambdaFunc the_lambda); // low level. map_of_maps must be good. (assumed.)
EXPORT OT_OTAPI_OT int32_t iterate_nymoffers_maps(MapOfMaps & map_of_maps, LambdaFunc the_lambda, the_lambda_struct & extra_vals); // low level. map_of_maps must be good. (assumed.)
EXPORT OT_OTAPI_OT int32_t iterate_nymoffers_sub_map(MapOfMaps & map_of_maps, SubMap & sub_map, LambdaFunc the_lambda);
EXPORT OT_OTAPI_OT int32_t iterate_nymoffers_sub_map(MapOfMaps & map_of_maps, SubMap & sub_map, LambdaFunc the_lambda, the_lambda_struct & extra_vals);
EXPORT OT_OTAPI_OT OTDB::OfferListNym * loadNymOffers(const string & serverID, const string & nymID);
EXPORT OT_OTAPI_OT int32_t output_nymoffer_data(OTDB::OfferDataNym & offer_data, const int32_t nIndex, MapOfMaps & map_of_maps, SubMap & sub_map, the_lambda_struct & extra_vals); // if 10 offers are printed for the SAME market, nIndex will be 0..9


extern string Args;
extern string HisAcct;
extern string HisNym;
extern string HisPurse;
extern string MyAcct;
extern string MyNym;
extern string MyPurse;
extern string Server;


typedef enum
{
    NO_FUNC = 0,
    CREATE_USER_ACCT = 1,
    DELETE_USER_ACCT = 2,
    CHECK_USER = 3,
    SEND_USER_MESSAGE = 4,
    SEND_USER_INSTRUMENT = 5,
    ISSUE_ASSET_TYPE = 6,
    ISSUE_BASKET = 7,
    CREATE_ASSET_ACCT = 8,
    DELETE_ASSET_ACCT = 9,
    ACTIVATE_SMART_CONTRACT = 10,
    TRIGGER_CLAUSE = 11,
    PROCESS_INBOX = 12,
    EXCHANGE_BASKET = 13,
    DEPOSIT_CASH = 14,
    EXCHANGE_CASH = 15,
    DEPOSIT_CHEQUE = 16,
    WITHDRAW_VOUCHER = 17,
    PAY_DIVIDEND = 18,
    WITHDRAW_CASH = 19,
    GET_CONTRACT = 20,
    SEND_TRANSFER = 21,
    GET_MARKET_LIST = 22,
    CREATE_MARKET_OFFER = 23,
    KILL_MARKET_OFFER = 24,
    KILL_PAYMENT_PLAN = 25,
    DEPOSIT_PAYMENT_PLAN = 26,
    GET_NYM_MARKET_OFFERS = 27,
    GET_MARKET_OFFERS = 28,
    GET_MARKET_RECENT_TRADES = 29,
    GET_MINT = 30,
    QUERY_ASSET_TYPES = 31,
    GET_BOX_RECEIPT = 32,
    ADJUST_USAGE_CREDITS = 33,
} OTAPI_Func_Type;

class the_lambda_struct
{
public:
    std::vector<string> the_vector;     // used for returning a list of something.
    string the_asset_acct;              // for newoffer, we want to remove existing offers for the same accounts in certain cases.
    string the_currency_acct;           // for newoffer, we want to remove existing offers for the same accounts in certain cases.
    string the_scale;                   // for newoffer as well.
    string the_price;                   // for newoffer as well.
    bool bSelling;                      // for newoffer as well.

    the_lambda_struct();
};

class OTAPI_Func
{
public:

    OTAPI_Func_Type  funcType;
    string serverID;
    string nymID;
    string nymID2;
    string assetID;
    string assetID2;
    string accountID;
    string accountID2;
    string basket;
    string strData;
    string strData2;
    string strData3;
    string strData4;
    string strData5;
    bool bBool;
    int32_t nData;
    int64_t lData;
    time_t tData;
    int32_t nTransNumsNeeded;
    int32_t nRequestNum;

    OTAPI_Func();
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID); // 3 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_strParam); // 4 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_strParam, const int64_t p_lData); // 5 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_strParam, const string & p_strData); // 5 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_nymID2, const string & p_strData, const string & p_strData2); // 6 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_accountID, const string & p_strParam, const int64_t p_lData, const string & p_strData2); // 7 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_accountID, const string & p_strParam, const string & p_strData, const int64_t p_lData2); // 7 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_accountID, const string & p_strParam, const string & p_strData, const string & p_strData2); // 7 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & p_assetID, const string & p_basket, const string & p_accountID, const bool p_bBool, const int32_t p_nTransNumsNeeded);  // 8 args
    OTAPI_Func(const OTAPI_Func_Type theType, const string & p_serverID, const string & p_nymID, const string & assetAccountID, const string & currencyAcctID, const string & scale, const string & minIncrement, const string & quantity, const string & price, const bool bSelling); // 10 args
    ~OTAPI_Func();

    OT_OTAPI_OT void InitCustom();
    OT_OTAPI_OT int32_t Run();
    OT_OTAPI_OT string SendRequest(OTAPI_Func & theFunction, const string & IN_FUNCTION);
    OT_OTAPI_OT int32_t SendRequestLowLevel(OTAPI_Func & theFunction, const string & IN_FUNCTION);
    OT_OTAPI_OT string SendRequestOnce(OTAPI_Func & theFunction, const string & IN_FUNCTION, const bool bIsTransaction, const bool bWillRetryAfterThis, bool & bCanRetryAfterThis);
    OT_OTAPI_OT string SendTransaction(OTAPI_Func & theFunction, const string & IN_FUNCTION);
    OT_OTAPI_OT string SendTransaction(OTAPI_Func & theFunction, const string & IN_FUNCTION, const int32_t nTotalRetries);
};

#endif
