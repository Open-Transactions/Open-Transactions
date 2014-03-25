noinst_LTLIBRARIES      =   liblucre.la

## For now we build locally and statically link to this library as a convenience library

lucre_headers_dir       =   $(top_srcdir)/include/lucre

liblucre_la_SOURCES     =   $(lucre_sources) $(lucre_headers)

liblucre_la_CXXFLAGS    =   $(AM_CXXFLAGS) -I$(lucre_headers_dir)

liblucre_la_LDFLAGS     =   -static

lucre_sources           =   bankimp.cpp

lucre_headers           =   $(lucre_headers_dir)/bank.hpp
