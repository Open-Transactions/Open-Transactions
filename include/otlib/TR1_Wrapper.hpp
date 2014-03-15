#ifndef __TR1_WRAPPER_HPP__
#define __TR1_WRAPPER_HPP__

#ifdef _MSC_VER
//#include "ot_msvc.h"
#else
#include "ot_config.h"
#endif

//  C++ Defines.
#ifdef OT_USE_TR1
#undef OT_USE_TR1
#endif
#if !defined(_MSC_VER) && defined(OPENTXS_CXX03_TR1)
#define OT_USE_TR1
#endif

#ifndef OT_USE_TR1
#define _CINTTYPES <cinttypes>
#define _MEMORY <memory>
#else
#define _CINTTYPES <tr1/cinttypes>
#define _MEMORY <tr1/memory>
#endif

#ifndef OT_USE_TR1
#define _SharedPtr std::shared_ptr
#define _WeakPtr std::weak_ptr
#else
#define _SharedPtr std::tr1::shared_ptr
#define _WeakPtr std::tr1::weak_ptr
#endif





#endif //__TR1_WRAPPER_HPP__

