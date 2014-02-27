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

void OtMeExtra::exec(const string & script)
{
	ExecuteScript_ReturnVoid(script, __FUNCTION__);
}

int OtMeExtra::execInt(const string & script)
{
	return ExecuteScript_ReturnInt(script, __FUNCTION__);
}

string OtMeExtra::execStr(const string & script)
{
	return ExecuteScript_ReturnString(script, __FUNCTION__);
}
