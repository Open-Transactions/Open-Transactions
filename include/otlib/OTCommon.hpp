#ifndef __OT_COMMON_HPP__
#define __OT_COMMON_HPP__

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#include "ExportWrapper.h"
#include "WinsockWrapper.h"
#include "TR1_Wrapper.hpp"
#include _CINTTYPES
#include _MEMORY


#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include <string>
#include <cstdlib>

// forward decleration.  (need to match what is in the irr source code). Cam.
namespace irr{
	namespace io{
		template<class char_type, class super_class>
		class IIrrXMLReader;
		class IFileReadCallBack;
		class IXMLBase;

		typedef IIrrXMLReader<char, IXMLBase> IrrXMLReader;
	}
}


#define OT_TIME_YEAR_IN_SECONDS          OTTimeGetTimeFromSeconds(31536000)  // 60 * 60 * 24 * 365
#define OT_TIME_SIX_MONTHS_IN_SECONDS    OTTimeGetTimeFromSeconds(15552000)  // 60 * 60 * 24 * 180
#define OT_TIME_THREE_MONTHS_IN_SECONDS  OTTimeGetTimeFromSeconds( 7776000)  // 60 * 60 * 24 * 90
#define OT_TIME_MONTH_IN_SECONDS         OTTimeGetTimeFromSeconds( 2592000)  // 60 * 60 * 24 * 30
#define OT_TIME_DAY_IN_SECONDS           OTTimeGetTimeFromSeconds(   86400)  // 60 * 60 * 24
#define OT_TIME_HOUR_IN_SECONDS          OTTimeGetTimeFromSeconds(    3600)  // 60 * 60
#define OT_TIME_MINUTE_IN_SECONDS        OTTimeGetTimeFromSeconds(      60)  // 60

#define OT_TIME_ZERO                     OTTimeGetTimeFromSeconds((int64_t)0)


//#define FORCE_COMPILE_ERRORS_TO_FIND_USAGE  // uncomment this line to find non-localized time64_t usage
#ifdef FORCE_COMPILE_ERRORS_TO_FIND_USAGE
class time64_t
{
public:
    int operator < (const time64_t & rhs) const;
    int operator > (const time64_t & rhs) const;
    int operator <= (const time64_t & rhs) const;
    int operator >= (const time64_t & rhs) const;
    int operator == (const time64_t & rhs) const;
    int operator != (const time64_t & rhs) const;

};
std::stringstream & operator << (const std::stringstream & str, const time64_t & t);

EXPORT time64_t OTTimeGetCurrentTime(); // { return time(NULL); }
EXPORT time64_t OTTimeGetTimeFromSeconds(int64_t seconds); // { return seconds; }
EXPORT time64_t OTTimeGetTimeFromSeconds(const char * pSeconds); // { return std::stol(pSeconds); }
EXPORT int64_t  OTTimeGetSecondsFromTime(time64_t time); // { return time; }
EXPORT int64_t  OTTimeGetTimeInterval(time64_t lhs, time64_t rhs); // { return lhs - rhs; }
EXPORT time64_t OTTimeAddTimeInterval(time64_t lhs, int64_t rhs); // { return lhs + rhs; }
#else
typedef int64_t time64_t;

inline time64_t OTTimeGetCurrentTime() { return time(NULL); }
inline time64_t OTTimeGetTimeFromSeconds(int64_t seconds) { return seconds; }
#if defined(OT_USE_CXX11) && !defined(ANDROID)
inline time64_t OTTimeGetTimeFromSeconds(const char * pSeconds) { return std::stol(pSeconds); }
#else
inline time64_t OTTimeGetTimeFromSeconds(const char * pSeconds) { return std::atol(pSeconds); }
#endif
inline int64_t  OTTimeGetSecondsFromTime(time64_t time) { return time; }
inline int64_t  OTTimeGetTimeInterval(time64_t lhs, time64_t rhs) { return lhs - rhs; }
inline time64_t OTTimeAddTimeInterval(time64_t lhs, int64_t rhs) { return lhs + rhs; }
#endif


#endif // __OT_COMMON_HPP__
