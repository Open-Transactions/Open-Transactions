lib_LTLIBRARIES         =       libgtest.la

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

libgtest_la_SOURCES	=	$(gtestlib_sources) $(gtestlib_headers)

libgtest_la_CXXFLAGS	=	$(common_includes)

libgtest_la_LDFLAGS	=	--no-undefined -g

####################################################################

gtestlib_sources     =		$(gtest_source_dir)/gtest.cc	\
				$(gtest_source_dir)/gtest-death-test.cc	\
                                $(gtest_source_dir)/gtest-filepath.cc	\
                                $(gtest_source_dir)/gtest-port.cc	\
                                $(gtest_source_dir)/gtest-printers.cc	\
                                $(gtest_source_dir)/gtest-test-part.cc	\
                                $(gtest_source_dir)/gtest-typed-test.cc	\
                                $(top_srcdir)/project/gtest/stdafx.cpp				

gtestlib_headers	=	$(top_srcdir)/project/gtest/stdafx.h

