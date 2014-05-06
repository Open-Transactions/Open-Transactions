noinst_PROGRAMS = unittests_otlib

AM_CXXFLAGS = -I$(top_builddir)/include

unittests_otlib_SOURCES = main.cpp Test_OTData.cpp
unittests_otlib_LDADD = -L$(top_builddir)/src -L$(top_builddir)/src/gtest -lot -lgtest

TESTS = $(noinst_PROGRAMS)
