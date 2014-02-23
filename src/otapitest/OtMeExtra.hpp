#ifndef _H_OT_ME_EXTRA

#include "stdafx.h"


using namespace std;


class OtMeExtra : public OT_ME
{
private:

public:

	OtMeExtra();
	~OtMeExtra();

	//void AddVariable(OTVariable & var);

	int details_deposit_cheque(const char * serverId, const char * accountId, const char * nymId, const char * paymentData, const char * paymentType);
	string details_export_cash(const char * serverId, const char * nymFromId, const char *assetId, const char *nymToId, const char *indices, bool password, string & retainedCopy);
	int handle_payment_index(const char * accountId, int32_t paymentIndex, const char * paymentType, const char * inboxData);
};

#endif // _H_OT_ME_EXTRA
