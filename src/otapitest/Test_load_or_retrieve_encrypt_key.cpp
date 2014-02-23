#include "stdafx.h"
#include "OtMeTest.hpp"


TEST_MOCK(load_public_encryption_key)
{
	//NOTE: we invert the negative/positive pathways here,
	//      since the function will 'bomb out' whenever it finds a public key

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadPubkey_Encryption(NYM_ID));

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadUserPubkey_Encryption(NYM_ID));

	ASSERT_MOCK_EQ(PUBLIC_KEY, "", me.load_public_encryption_key(NYM_ID));
}

TEST_MOCK(load_or_retrieve_encrypt_key)
{
	//NOTE: we invert the negative/positive pathways here,
	//      since the function will 'bomb out' whenever it finds a public key

	const char * expectResult = PUBLIC_KEY;
	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadPubkey_Encryption(NYM_TO_ID));

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadUserPubkey_Encryption(NYM_TO_ID));

	if (index >= 0)
	{
		expectResult = "";
		EXPECT_MOCK_REQUEST(MESSAGE_DATA, checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

		//FIX overkill, EXPECT_REQUEST already did this
		EXPECT_MOCK_STR(OT_FALSE, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

		if (index >= 0)
		{
			expectResult = PUBLIC_KEY;
			EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadPubkey_Encryption(NYM_TO_ID));

			EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadUserPubkey_Encryption(NYM_TO_ID));
			if (index >= 0)
			{
				expectResult = "";
			}
		}
	}

	ASSERT_EQ(expectResult, me.load_or_retrieve_encrypt_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}


void OtMeTest::EXPECT_load_or_retrieve_encrypt_key(Mock_OTAPI_Exec & mock, int & index, const char * serverId, const char * nymId, const char * nymToId)
{
	//NOTE: this function will only follow one negative pathway
	//FIX need to fully test it separately

	// always fail initial load
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(nymToId));
	EXPECT_MOCK_RET("", LoadUserPubkey_Encryption(nymToId));

	// always succeed checkUser
	EXPECT_REQUEST(MESSAGE_DATA, checkUser(serverId, nymId, nymToId));
	EXPECT_MOCK_RET(OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

	// again, fail initial loading
	EXPECT_MOCK_RET("", LoadPubkey_Encryption(nymToId));

	// finally we can follow a negative pathway
	EXPECT_MOCK_STR("", PUBLIC_KEY, LoadUserPubkey_Encryption(nymToId));
}
