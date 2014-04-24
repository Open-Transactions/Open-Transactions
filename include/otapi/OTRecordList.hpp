//
//  OTRecordList.h
//  OTClient module
//
//  Created by Chris Odom on 4/28/13.
//  Copyright (c) 2013 Monetas. All rights reserved.
//

#ifndef __OTClient__OTRecordList__
#define __OTClient__OTRecordList__

#include "OTCommon.hpp"

#include "OTRecord.hpp"

#include _CINTTYPES
#include _MEMORY

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>


// For address book lookups. Your client app inherits this and provides
// addr storage/lookup through this simple interface. OTRecordList then
// calls it.
//
class OTNameLookup
{
public:
EXPORT          OTNameLookup() { }
EXPORT virtual ~OTNameLookup();

EXPORT virtual std::string GetNymName(const std::string & str_id, // NymID
                                      const std::string * p_server_id=NULL) const;

EXPORT virtual std::string GetAcctName(const std::string & str_id, // AcctID
                                       const std::string * p_nym_id=NULL,
                                       const std::string * p_server_id=NULL,
                                       const std::string * p_asset_id=NULL) const;
};

// ------------------------------------------------

// Client app makes an instance of its own subclass of OTNameLookup.
// Client app also makes an instance of OTLookupCaller (below.)
// Client app then gives the caller a pointer to the namelookup.
// Client app then passes the caller to OT via OT_API_Set_AddrBookCallback.
// OTRecord and OTRecordList then call the caller.
//
class OTLookupCaller
{
protected:
	OTNameLookup * _callback;
    
public:
EXPORT   OTLookupCaller() : _callback(NULL) { }
EXPORT	~OTLookupCaller();

EXPORT	void delCallback();
EXPORT	void setCallback(OTNameLookup *cb);
EXPORT	bool isCallbackSet() const;

EXPORT	std::string GetNymName(const std::string & str_id, // NymID
                               const std::string * p_server_id=NULL) const;

EXPORT	std::string GetAcctName(const std::string & str_id, // AcctID
                                const std::string * p_nym_id=NULL,
                                const std::string * p_server_id=NULL,
                                const std::string * p_asset_id=NULL) const;
};


// ------------------------------------------------


EXPORT bool OT_API_Set_AddrBookCallback(OTLookupCaller & theCaller); // OTLookupCaller must have OTNameLookup attached already.

/*
 class OTNameLookupIPhone : public OTNameLookup
 {
 public:
    virtual std::string GetNymName(const std::string & str_id) const;
    virtual std::string GetAcctName(const std::string & str_id) const;
 };
 */

typedef _WeakPtr<OTRecord>       weak_ptr_OTRecord;
typedef _SharedPtr<OTRecord>     shared_ptr_OTRecord;


typedef std::vector<shared_ptr_OTRecord>      vec_OTRecordList;
// -------------------------------------------------------------
typedef std::list<std::string>                 list_of_strings;
// -------------------------------------------------------------
typedef std::map<std::string, std::string>     map_of_strings;


class OTRecordList
{
    OTNameLookup           *  m_pLookup;
    // ------------------------------------------------
    // Defaults to false. If you set it true, it will run a lot faster. (And give you less data.)
    bool                      m_bRunFast;
    // ------------------------------------------------
    bool                      m_bAutoAcceptCheques;   // Cheques and vouchers, NOT invoices.
    bool                      m_bAutoAcceptReceipts;
    bool                      m_bAutoAcceptTransfers;
    bool                      m_bAutoAcceptCash;
    // ------------------------------------------------
    static std::string        s_strTextTo;   // "To: "
    static std::string        s_strTextFrom; // "From: "
    // ------------------------------------------------
    list_of_strings           m_servers;
     map_of_strings           m_assets;  // <asset_type_id, asset_name>
    list_of_strings           m_accounts;
    list_of_strings           m_nyms;
    // ------------------------------------------------
    vec_OTRecordList          m_contents;
    // ------------------------------------------------
    static const std::string  s_blank;
    static const std::string  s_message_type;
    // ********************************************
public: // ADDRESS BOOK CALLBACK
    
	   static bool setAddrBookCaller(OTLookupCaller & theCaller);
	   static OTLookupCaller * getAddrBookCaller();

protected: // ADDRESS BOOK CALLBACK
	   static OTLookupCaller * s_pCaller;
// ********************************************
public:
        OTRecordList(OTNameLookup & theLookup);
EXPORT ~OTRecordList();
    // ------------------------------------------------
EXPORT static const char * textTo  ()  { return s_strTextTo  .c_str(); }
EXPORT static const char * textFrom()  { return s_strTextFrom.c_str(); }

EXPORT static void setTextTo  (const std::string text)  { s_strTextTo   = text; }
EXPORT static void setTextFrom(const std::string text)  { s_strTextFrom = text; }
// ------------------------------------------------
EXPORT    void SetFastMode() { m_bRunFast = true; }
    // ------------------------------------------------
    // SETUP:
    
EXPORT    void SetServerID(const std::string str_id); // Set the default server here.
EXPORT    void AddServerID(const std::string str_id); // Unless you have many servers, then use this.
EXPORT    void ClearServers(); // Also clears m_contents
    
EXPORT    void SetAssetID(const std::string str_id);  // Etc.
EXPORT    void AddAssetID(const std::string str_id);
EXPORT    void ClearAssets(); // Also clears m_contents
    
EXPORT    void SetNymID(const std::string str_id);
EXPORT    void AddNymID(const std::string str_id);
EXPORT    void ClearNyms(); // Also clears m_contents
    
EXPORT    void SetAccountID(const std::string str_id);
EXPORT    void AddAccountID(const std::string str_id);
EXPORT    void ClearAccounts(); // Also clears m_contents
    
    // ------------------------------------------------
EXPORT    void AcceptChequesAutomatically  (bool bVal=true);
EXPORT    void AcceptReceiptsAutomatically (bool bVal=true);
EXPORT    void AcceptTransfersAutomatically(bool bVal=true);
EXPORT    void AcceptCashAutomatically     (bool bVal=true);
    
EXPORT    bool DoesAcceptChequesAutomatically  ();
EXPORT    bool DoesAcceptReceiptsAutomatically ();
EXPORT    bool DoesAcceptTransfersAutomatically();
EXPORT    bool DoesAcceptCashAutomatically     ();
    
EXPORT    bool PerformAutoAccept(); // Before populating, process out any items we're supposed to accept automatically.
    // ------------------------------------------------
    // POPULATE:
    
EXPORT    bool Populate();      // Populates m_contents from OT API. Calls ClearContents().
EXPORT    void ClearContents(); // Clears m_contents (NOT nyms, accounts, servers, or asset types.)
    // ------------------------------------------------
    // RETRIEVE:
    //
EXPORT    int32_t              size();
EXPORT    _SharedPtr<OTRecord> GetRecord(int32_t nIndex);
EXPORT    bool                 RemoveRecord(int32_t nIndex);
    // ------------------------------------------------
};

/*
 
 // TO USE:
 
 OTRecordList blah;
 
 blah.SetServerID("id goes here");
 blah.SetAssetID("id goes here");
 blah.SetNymID("id goes here");
 blah.SetAccountID("id goes here");
 
 blah.Populate();
 
 // THEN:
 
 int               nSize  = blah.size();
 int               nIndex = [0 .. nSize-1]
 weak_ptr_OTRecord record = blah.GetRecord(nIndex);
 
 
 // ACCESSING THE RECORD:
 
 shared_ptr_OTRecord pRecord(record);
 
 if (!sp)
 {
 // It's NULL -- this means OTRecordList got re-populated.
 // (Which means the list control on the UI needs to get
 // re-populated with fresh pointers.)
 }
 else // Pointer is good
 {
 pRecord->GetName();  // Etc.
 }
 
 
 // THEN LATER:
 
 blah.Populate();
 
 Etc.
 
 */

#endif /* defined(__OTClient__OTRecordList__) */












