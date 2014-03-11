lib_LTLIBRARIES         =       libgmock.la

opentxs_include_dir 	=	$(top_srcdir)/include
opentxs_source_dir 	=	$(top_srcdir)/src

gtest_source_dir	=	$(opentxs_source_dir)/gtest
gtest_include_dir	=	$(opentxs_include_dir)/gtest
gmock_source_dir	=	$(opentxs_source_dir)/gmock
gmock_include_dir	=	$(opentxs_include_dir)/gmock

## COMMON FLAGS ###

common_includes		=	$(AM_CXXFLAGS)				\
				-I$(top_srcdir)/project/gtest	        \
				-I$(top_srcdir)/project/gmock	        \
				-I$(gtest_include_dir)			\
				-I$(opentxs_include_dir)		\
				-DOT_PREFIX_PATH="\"${prefix}\""	\
				-DOT_VERSION="\"${VERSION}\""


#### Lib gtest build calls

libgmock_la_SOURCES	=	$(gmocklib_sources) $(gmocklib_headers)

libgmock_la_CXXFLAGS	=	$(common_includes)

libgmock_la_LDFLAGS	=	--no-undefined -g

####################################################################

gmocklib_sources     =		$(gmock_source_dir)/gmock.cc	\
				$(gmock_source_dir)/gmock-cardinalities.cc	\
                                $(gmock_source_dir)/gmock-internal-utils.cc	\
                                $(gmock_source_dir)/gmock-matchers.cc	\
                                $(gmock_source_dir)/gmock-spec-builders.cc	\
                                $(top_srcdir)/project/gtest/stdafx.cpp				

gmocklib_headers	=	$(top_srcdir)/project/gmock/stdafx.h

