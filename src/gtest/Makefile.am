lib_LTLIBRARIES             =   libgtest.la

########################## STANDARD FOLDERS #########################

opentxs_incdir              =   $(top_srcdir)/include
opentxs_srcdir              =   $(top_srcdir)/src

gmock_incdir                =   $(opentxs_incdir)/gmock
gmock_srcdir                =   $(opentxs_srcdir)/gmock
gtest_incdir                =   $(opentxs_incdir)/gtest
gtest_srcdir                =   $(opentxs_srcdir)/gtest
ot_incdir                   =   $(opentxs_incdir)/otd
ot_srcdir                   =   $(opentxs_srcdir)/otd
otapi_incdir                =   $(opentxs_incdir)/otapi
otapi_srcdir                =   $(opentxs_srcdir)/otapi
otapitest_incdir            =   $(opentxs_incdir)/otapitest
otapitest_srcdir            =   $(opentxs_srcdir)/otapitest
otlib_incdir                =   $(opentxs_incdir)/otlib
otlib_srcdir                =   $(opentxs_srcdir)/otlib
otmint_incdir               =   $(opentxs_incdir)/otmint
otmint_srcdir               =   $(opentxs_srcdir)/otmint
otserver_incdir             =   $(opentxs_incdir)/ots
otserver_srcdir             =   $(opentxs_srcdir)/ots

swig_dir                    =   $(top_srcdir)/swig

common_includes             =   -I$(otapi_incdir) \
                                -I$(otlib_incdir) \
                                -I$(opentxs_incdir)

common_libraries            =   $(otapi_srcdir)/libotapi.la \
                                $(otlib_srcdir)/libotlib.la
                                        
######################## BUILD COMMANDS #############################

libgtest_la_SOURCES         =   $(gtestlib_sources) $(gtestlib_headers)

libgtest_la_CXXFLAGS        =   $(AM_CXXFLAGS) \
                                -I$(gtest_incdir) \
                                -I$(opentxs_incdir)

libgtest_la_LDFLAGS         =   --no-undefined -g

######################## DEPENDENCIES ###############################

gtestlib_sources            =   gtest.cc \
                                gtest-death-test.cc \
                                gtest-filepath.cc \
                                gtest-port.cc \
                                gtest-printers.cc \
                                gtest-test-part.cc \
                                gtest-typed-test.cc               

gtestlib_headers            =   stdafx.h

