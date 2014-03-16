#include "stdafx.h"


TEST_MOCK(load_public_signing_key_UserPubkey)
{
	//NOTE: we invert the negative/positive pathways here,
	//      since the function will 'bomb out' whenever it finds a public key

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadPubkey_Signing(NYM_ID));

	EXPECT_MOCK_STR(PUBLIC_KEY, "", LoadUserPubkey_Signing(NYM_ID));

	ASSERT_MOCK_EQ(PUBLIC_KEY, "", me.load_public_signing_key(NYM_ID));
}
