noinst_LTLIBRARIES      =   libotext.la

## For now we build locally and statically link to this library as a convenience library

otext_headers_dir       =   $(top_srcdir)/include/otlib

libotext_la_SOURCES     =   $(otext_sources) $(otext_headers)

libotext_la_CXXFLAGS    =   $(AM_CXXFLAGS) -I$(otext_headers_dir)

libotext_la_LDFLAGS     =   -static --no-undefined

otext_sources           =   mkcert.cpp \
                            anyoption.cpp \
                            tinythread.cpp \
                            Timer.cpp

otext_headers           =   $(otext_headers_dir)/anyoption.hpp \
                            $(otext_headers_dir)/tinythread.hpp \
                            $(otext_headers_dir)/Timer.hpp

pkginclude_HEADERS      =   $(otext_headers)
