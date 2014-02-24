#ifndef _EXPORT_WRAPPER_H_
#define _EXPORT_WRAPPER_H_

#ifdef _WIN32

// DLL Export/Import for Win32
#ifdef EXPORT
#undef EXPORT
#endif

#ifndef NOEXPORT
#ifdef _WINDLL
#ifdef IMPORT
  #define EXPORT __declspec(dllimport)
#else
  #define EXPORT __declspec(dllexport)
#endif
#else
  #define EXPORT
#endif
#endif

#endif
#endif