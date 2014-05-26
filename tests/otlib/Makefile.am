noinst_PROGRAMS = unittests_otlib

common_includes         =	$(AM_CXXFLAGS)			\
				-I$(top_builddir)/include	\
				-I$(top_srcdir)/include

unittests_otlib_SOURCES		= main.cpp Test_OTData.cpp

unittests_otlib_CXXFLAGS	= $(common_includes)

unittests_otlib_LDFLAGS		= -L$(top_builddir)/src/otlib -L$(top_builddir)/src/gtest

unittests_otlib_LDADD		= $(top_builddir)/src/otlib/libot.la $(top_builddir)/src/gtest/libgtest.la

TESTS				= $(noinst_PROGRAMS)
