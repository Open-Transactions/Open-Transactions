#ifndef __MEMORY_WRAPPER_HPP__
#define __MEMORY_WRAPPER_HPP__

#ifdef _MSC_VER
//#include <ot_msvc.h>
#else
#include <ot_config.h>
#endif

//  C++ Defines.
#ifdef OT_USE_TR1
#undef OT_USE_TR1
#endif
#if !defined(_MSC_VER) && defined(OPENTXS_CXX03_TR1)
#define OT_USE_TR1
#endif

#ifndef OT_USE_TR1
#include <cinttypes>
#include <memory>
#else
#include <tr1/cinttypes>
#include <tr1/memory>
#endif

#endif

