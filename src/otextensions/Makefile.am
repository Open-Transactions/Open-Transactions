######################################
## Open Transactions Libs extensions #
######################################

lib_LTLIBRARIES = libotextensions.la

### Common variables, flags ###

opentxs_include_dir	=	$(top_srcdir)/include

otlib_build_dir		=	$(top_builddir)/src/otlib

common_includes		=	$(AM_CXXFLAGS)          		\
				-I$(opentxs_include_dir)		\
				-I$(opentxs_include_dir)/otlib		\
				-I$(opentxs_include_dir)/otextensions	\
				-I$(top_srcdir)/deps/include/simpleini	\
				-I$(top_srcdir)/deps/include/misc	\
				-I$(top_srcdir)/deps/include


########################

libotextensions_la_SOURCES	=	$(otextensions_sources) $(otextensions_headers)

libotextensions_la_CXXFLAGS		=	$(common_includes)

libotextensions_la_LIBADD		=	$(otlib_build_dir)/libot.la $(DEPS_LIBS)
libotextensions_la_DEPENDENCIES		=	$(otlib_build_dir)/libot.la

libotextensions_la_LDFLAGS		=	--no-undefined


#### Transport ZMQ 'option'

if TRANSPORT_ZMQ2
libotextensions_la_CXXFLAGS		+=	-DOT_ZMQ_MODE
endif

if TRANSPORT_ZMQ4

libotextensions_la_LIBADD		+=	$(top_builddir)/deps/src/zmq/libzmq.la

libotextensions_la_DEPENDENCIES		+=	$(top_builddir)/deps/src/zmq/libzmq.la

endif


####  otextensions

otextensions_sources_dir	= 	$(top_srcdir)/src/otextensions

otextensions_sources		=	OTSocket.cpp


otextensions_headers_dir	=	$(opentxs_include_dir)/otextensions

otextensions_headers		=	$(otextensions_headers_dir)/OTSocket.hpp

####	Global headers for dist.

pkginclude_HEADERS		=	$(otextensions_headers)
