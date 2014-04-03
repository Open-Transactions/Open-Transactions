// OTLIB
// Open Transactions Pre-Compiled Headers File

#pragma once

// Include the C one.
#include "stdafx.h"

#ifdef OT_USE_CXX11
#undef OT_USE_CXX11
#endif

#if defined(_MSC_VER)
#define OT_USE_CXX11
#elif (!defined(OPENTXS_NO_CXX11) && (__cplusplus >= 201103L))
#define OT_USE_CXX11
#endif

// ------------------------------------
#ifndef OT_USE_SCRIPT_CHAI
#define OT_USE_SCRIPT_CHAI

#ifdef OPENTXS_CHAISCRIPT_4
#else

#ifndef OPENTXS_CHAISCRIPT_5
#define OPENTXS_CHAISCRIPT_5
#endif

#endif

#endif
// ------------------------------------
#if defined(ANDROID) || defined(OT_KEYRING_IOS)

// DON'T use ChaiScript on mobile devices
#undef OT_USE_SCRIPT_CHAI

#ifdef OPENTXS_CHAISCRIPT_4
#undef OPENTXS_CHAISCRIPT_4
#endif

#ifdef OPENTXS_CHAISCRIPT_5
#undef OPENTXS_CHAISCRIPT_5
#endif

#endif
// ------------------------------------

#ifdef OT_USE_CHAI_STDLIB
#undef OT_USE_CHAI_STDLIB
#endif

#ifdef OPENTXS_CHAISCRIPT_5
#define OT_USE_CHAI_STDLIB
#endif

// ------------------------------------

#ifndef OT_CRYPTO_USING_OPENSSL
#define OT_CRYPTO_USING_OPENSSL 1
#endif

#ifndef OT_CASH_USING_LUCRE
#define OT_CASH_USING_LUCRE 1
#endif

// ------------------------------------

// for mac, this enables deprecated functions. (aka, for pthread)
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif

// define fstream while _XOPEN_SOURCE isn't defined.
//#include <fstream>

#if defined(__APPLE__) && defined(OPENTXS_XOPEN_SOURCE)
#define _XOPEN_SOURCE 500
#endif

//#include <list>
//#include <string>
//#include <map>
//#include <set>
//#include <stack>
//#include <deque>
//#include <vector>
//#include <locale>


#ifdef _WIN32
#ifndef NO_OT_PCH
//#include "OTStorage.h"
//#include "OTSmartContract.h"
#else
#undef NO_OT_PCH
#endif
#endif
