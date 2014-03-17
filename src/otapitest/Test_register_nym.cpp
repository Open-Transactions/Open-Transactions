#include "stdafx.hpp"


TEST_MULTI(register_nym)
{
	//FIX does REQUEST_NUMBER spill out of this call?
	EXPECT_MULTI_REQUEST(MESSAGE_DATA, createUserAccount(SERVER_ID, NYM_ID));

	const char * result = "";
	if (index >= 0)
	{
		EXPECT_MULTI_RETURN(OT_FALSE, OT_TRUE, Message_GetSuccess(MESSAGE_DATA));
		//FIX there is no failure logic, so it will actually return this MESSAGE_DATA upon failure

		result = MESSAGE_DATA;
		if (index >= 0)
		{
			index--;
			result = "";
			EXPECT_CALL_FUNC(index >= 0 ? REQUEST_NUMBER : OT_ERROR, getRequest(SERVER_ID, NYM_ID));
			if (index >= 0)
			{
				EXPECT_CALL_VOID(Sleep(50));
				EXPECT_CALL_RETURN(MESSAGE_DATA2, PopMessageBuffer(REQUEST_NUMBER, SERVER_ID, NYM_ID));
				EXPECT_MULTI_RETURN(OT_FALSE, OT_TRUE, Message_GetSuccess(MESSAGE_DATA2));
				result = index >= 0 ? MESSAGE_DATA : "";
			}
		}
	}

	ASSERT_EQ(result, me.register_nym(SERVER_ID, NYM_ID));
}
