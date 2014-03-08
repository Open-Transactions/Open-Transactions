#ifndef _EXPORT_WRAPPER_H_
#define _EXPORT_WRAPPER_H_
#endif // no guard.


#if defined(_WINDLL) && !defined(NOEXPORT)  && !defined(SWIG)

#ifdef EXPORT
#undef EXPORT
#endif

#ifdef IMPORT
#define EXPORT __declspec(dllimport)
#else
#define EXPORT __declspec(dllexport)
#endif

#else
#define EXPORT
#endif

