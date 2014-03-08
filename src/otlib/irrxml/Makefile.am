noinst_LTLIBRARIES = libirrxml.la

## For now we build locally and statically link to this library as a convenience library



libirrxml_la_SOURCES	=	$(irrxml_sources) $(irrxml_headers)
libirrxml_la_CXXFLAGS	=	$(AM_CXXFLAGS) -I$(irrxml_headers_dir)
libirrxml_la_LDFLAGS	=	-static

irrxml_sources		=	irrXML.cpp

irrxml_headers_dir	=	$(top_srcdir)/include/irrxml

irrxml_headers		=	$(irrxml_headers_dir)/CXMLReaderImpl.hpp	\
				$(irrxml_headers_dir)/fast_atof.hpp		\
				$(irrxml_headers_dir)/heapsort.hpp		\
				$(irrxml_headers_dir)/irrArray.hpp		\
				$(irrxml_headers_dir)/irrString.hpp		\
				$(irrxml_headers_dir)/irrTypes.hpp		\
				$(irrxml_headers_dir)/irrXML.hpp


pkginclude_irrxmldir	=	$(pkgincludedir)/irrxml

pkginclude_irrxml_HEADERS	=	$(irrxml_headers)
