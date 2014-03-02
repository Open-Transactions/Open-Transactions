#include "stdafx.h"
#include "OtMeExtra.hpp"


OtMeExtra::OtMeExtra()
{
}

OtMeExtra::~OtMeExtra()
{
}
//
//void OtMeExtra::AddVariable(OTVariable & var)
//{
//	OT_ME::AddVariable(var.GetName().Get(), var);
//}

const char * OtMeExtra::boolStr(bool bValue)
{
	return bValue ? "true" : "false";
}

void OtMeExtra::exec(const string & script)
{
	ExecuteScript_ReturnVoid(script, __FUNCTION__);
}

bool OtMeExtra::execBool(const string & script)
{
	return ExecuteScript_ReturnBool(script, __FUNCTION__);
}

int OtMeExtra::execInt(const string & script)
{
	return ExecuteScript_ReturnInt(script, __FUNCTION__);
}

string OtMeExtra::execStr(const string & script)
{
	return ExecuteScript_ReturnString(script, __FUNCTION__);
}
