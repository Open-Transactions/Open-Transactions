lib_LTLIBRARIES             =   libgtest.la

########################## STANDARD FOLDERS #########################

opentxs_incdir              =   $(top_srcdir)/include
opentxs_srcdir              =   $(top_srcdir)/src

gmock_incdir                =   $(opentxs_incdir)/gmock
gmock_srcdir                =   $(opentxs_srcdir)/gmock
gtest_incdir                =   $(opentxs_incdir)/gtest
gtest_srcdir                =   $(opentxs_srcdir)/gtest
ot_incdir                   =   $(opentxs_incdir)/ot
ot_srcdir                   =   $(opentxs_srcdir)/ot
otapi_incdir                =   $(opentxs_incdir)/otapi
otapi_srcdir                =   $(opentxs_srcdir)/otapi
otapitest_incdir            =   $(opentxs_incdir)/otapitest
otapitest_srcdir            =   $(opentxs_srcdir)/otapitest
otlib_incdir                =   $(opentxs_incdir)/otlib
otlib_srcdir                =   $(opentxs_srcdir)/otlib
otmint_incdir               =   $(opentxs_incdir)/otmint
otmint_srcdir               =   $(opentxs_srcdir)/otmint
otserver_incdir             =   $(opentxs_incdir)/otserver
otserver_srcdir             =   $(opentxs_srcdir)/otserver

swig_dir                    =   $(top_srcdir)/swig

common_includes             =   -I$(otapi_incdir) \
                                -I$(otlib_incdir) \
                                -I$(opentxs_incdir)

common_libraries            =   $(otapi_srcdir)/libotapi.la \
                                $(otlib_incdir)/libotlib.la
                                        
######################## BUILD COMMANDS #############################

libgtest_la_SOURCES         =   $(gtestlib_sources) $(gtestlib_headers)

libgtest_la_CXXFLAGS        =   $(AM_CXXFLAGS) \
                                -I$(top_srcdir)/project/gtest \
                                -I$(opentxs_incdir)

libgtest_la_LDFLAGS         =   --no-undefined -g

######################## DEPENDENCIES ###############################

gtestlib_sources            =   $(gtest_srcdir)/gtest.cc \
                                $(gtest_srcdir)/gtest-death-test.cc \
                                $(gtest_srcdir)/gtest-filepath.cc \
                                $(gtest_srcdir)/gtest-port.cc \
                                $(gtest_srcdir)/gtest-printers.cc \
                                $(gtest_srcdir)/gtest-test-part.cc \
                                $(gtest_srcdir)/gtest-typed-test.cc               

gtestlib_headers            =   $(top_srcdir)/project/gtest/stdafx.h

