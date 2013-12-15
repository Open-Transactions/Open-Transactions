// OTLIB
// Open Transactions Pre-Compiled Headers File

#pragma once

#ifdef _MSC_VER
//#include <ot_msvc.h>
#else
#include <ot_config.h>
#endif

#ifndef EXPORT
#define EXPORT
#endif
#ifndef NOEXPORT
#include <ExportWrapper.h>
#endif

#ifdef _WIN32
#include <WinsockWrapper.h>
#endif

#include <list>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <deque>
#include <vector>
#include <locale>

// NOTE: Turns out moneypunct kind of sucks.
// As a result, for internationalization purposes,
// these values have to be set here before compilation.
//
#define OT_THOUSANDS_SEP ","
#define OT_DECIMAL_POINT "."

// if we are not compiling with C++11, lets use the tr1.
#ifdef OT_USE_TR1
#undef OT_USE_TR1
#endif
#if !defined(_MSC_VER) && defined(OPENTXS_NO_CXX11)
#define OT_USE_TR1
#endif

#ifndef OT_USE_TR1
#include <memory>
#else
#include <tr1/memory>
#endif

#ifdef _WIN32
#ifndef NO_OT_PCH
#include <OTStorage.h>
#include <OTSmartContract.h>
#else
#undef NO_OT_PCH
#endif
#endif
