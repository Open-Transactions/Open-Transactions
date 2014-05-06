noinst_PROGRAMS = unittests_otlib

AM_CXXFLAGS = -I$(top_builddir)/include

unittests_otlib_SOURCES = main.cpp Test_OTData.cpp
unittests_otlib_LDFLAGS = -L$(top_builddir)/src/otlib -L$(top_builddir)/src/gtest
unittests_otlib_LDADD = $(top_builddir)/src/otlib/libot.la -lgtest

TESTS = $(noinst_PROGRAMS)
