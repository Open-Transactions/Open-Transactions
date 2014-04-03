#include "stdafx.hpp"


TEST_MOCK(load_public_signing_key_UserPubkey)
{
	//NOTE: we invert the negative/positive pathways here,
	//      since the function will 'bomb out' whenever it finds a public key

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadPubkey_Signing(NYM_ID));

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadUserPubkey_Signing(NYM_ID));

	ASSERT_MOCK_EQ(PUBLIC_KEY, "", me.load_public_signing_key(NYM_ID));
}

TEST_MOCK(load_or_retrieve_signing_key)
{
	//NOTE: we invert the negative/positive pathways here,
	//      since the function will 'bomb out' whenever it finds a public key

	const char * expectResult = PUBLIC_KEY;
	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadPubkey_Signing(NYM_TO_ID));

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadUserPubkey_Signing(NYM_TO_ID));

	if (index >= 0)
	{
		expectResult = "";
		EXPECT_MOCK_REQUEST(MESSAGE_DATA, checkUser(SERVER_ID, NYM_ID, NYM_TO_ID));

		//FIX overkill, EXPECT_REQUEST already did this
		EXPECT_MOCK_STR(OT_FALSE, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));

		if (index >= 0)
		{
			expectResult = PUBLIC_KEY;
			EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadPubkey_Signing(NYM_TO_ID));

			EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadUserPubkey_Signing(NYM_TO_ID));
			if (index >= 0)
			{
				expectResult = "";
			}
		}
	}

	ASSERT_EQ(expectResult, me.load_or_retrieve_signing_key(SERVER_ID, NYM_ID, NYM_TO_ID));
}
