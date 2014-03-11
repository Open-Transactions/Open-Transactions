// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#ifdef _WIN32
#include <tchar.h>
#endif


// TODO: reference additional headers your program requires here

#include <ctime>
#include <cstdlib>

#include <string>
#include <iostream>
#include <fstream>

// credit:stlplus library.
#include "containers/simple_ptr.hpp"

#ifdef _WIN32
#include <WinsockWrapper.h>
#endif

#if defined (OT_ZMQ_MODE)
#include <zmq.hpp>
#endif

extern "C"
{
#ifdef _WIN32
	//#include <WinSock.h>
#else
#include <netinet/in.h>
#endif

	//#include "SSL-Example/SFSocket.h"
}

// ----------------------------------------------
#ifdef _WIN32
/*
Minimum supported client    -- Windows XP
Minimum supported server    -- Windows Server 2003
Header                      -- WinBase.h (include Windows.h)
Library                     -- Kernel32.lib
DLL                         -- Kernel32.dll
*/
//#include <windows.h>  // I'm assuming the above WinsockWrapper inclusion already covers this.
// DWORD GetCurrentProcessId(void);
#else
// getpid
#include <sys/types.h>
#include <unistd.h>
//pid_t getpid(void);
//pid_t getppid(void);
#endif
// ----------------------------------------------

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "simpleini/SimpleIni.h"

// ----------------------------

// TinyThread++
//
#include "tinythread.h"   // These are in the header already.
//#include "fast_mutex.h"

using namespace tthread;

// ----------------------------

#include "OTAPI.h"
#include "OT_ME.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "otapi/Mock_OTAPI_Exec.h"
