noinst_LTLIBRARIES = libmisc.la

## For now we build locally and statically link to this library as a convenience library

misc_headers_dir	=	$(top_srcdir)/deps/include/misc


misc_sources		=	mkcert.cpp			\
				anyoption.cpp			\
				tinythread.cpp			\
				Timer.cpp

misc_headers		=	$(misc_headers_dir)/anyoption.hpp	\
				$(misc_headers_dir)/tinythread.hpp	\
				$(misc_headers_dir)/Timer.hpp

libmisc_la_SOURCES	=	$(misc_sources) $(misc_headers)

libmisc_la_CXXFLAGS	=	$(AM_CXXFLAGS)			\
				-I$(misc_headers_dir)		\
				-I$(top_builddir)/include/otlib	\
				-I$(top_srcdir)/include/otlib

libmisc_la_LDFLAGS	=	-static --no-undefined


pkginclude_HEADERS	=	$(misc_headers)
