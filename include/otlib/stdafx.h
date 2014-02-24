// OTLIB
// Open Transactions Pre-Compiled Headers File

#pragma once

#ifdef _MSC_VER
//#include <ot_msvc.h>
#else
#include <ot_config.h>
#endif

#include <ExportWrapper.h>
#include <WinsockWrapper.h>

// NOTE: Turns out moneypunct kind of sucks.
// As a result, for internationalization purposes,
// these values have to be set here before compilation.
//
#define OT_THOUSANDS_SEP ","
#define OT_DECIMAL_POINT "."


