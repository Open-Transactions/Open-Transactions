#ifndef _H_OT_ME_EXTRA

#include "stdafx.h"


using namespace std;


class OtMeExtra : public OT_ME
{
private:

public:

	OtMeExtra();
	~OtMeExtra();

	void exec(const string & script);
	int execInt(const string & script);
	string execStr(const string & script);

	//void AddVariable(OTVariable & var);

	int details_deposit_cheque(const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType);
	string details_export_cash(const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password, string & retainedCopy);
	int handle_payment_index(const char * accountId, int32_t paymentIndex, const char * paymentType, const char * inboxData);
	int ot_utility_getNymboxLowLevel(const char * serverId, const char * nymId);
	string ot_utility_ReceiveReplyLowLevel(const char * serverId, const char * nymId, int reqNr, const char * function);
};

#endif // _H_OT_ME_EXTRA
