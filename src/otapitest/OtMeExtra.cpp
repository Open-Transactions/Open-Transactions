#include "stdafx.hpp"


OtMeExtra::OtMeExtra()
{
}

OtMeExtra::~OtMeExtra()
{
}


OtMeChai::OtMeChai()
{
}

OtMeChai::~OtMeChai()
{
}

const char * OtMeChai::boolStr(bool bValue)
{
	return bValue ? "true" : "false";
}

void OtMeChai::exec(const string & script)
{
#if USE_OLD_CODE
    ExecuteScript_ReturnVoid(script, __FUNCTION__);
#endif
}

bool OtMeChai::execBool(const string & script)
{
#if USE_OLD_CODE
    return ExecuteScript_ReturnBool(script, __FUNCTION__);
#else
    return false;
#endif
}

int OtMeChai::execInt(const string & script)
{
#if USE_OLD_CODE
    return ExecuteScript_ReturnInt(script, __FUNCTION__);
#else
    return 0;
#endif
}

string OtMeChai::execStr(const string & script)
{
#if USE_OLD_CODE
    return ExecuteScript_ReturnString(script, __FUNCTION__);
#else
    return "";
#endif
}
