lib_LTLIBRARIES             =   libgmock.la

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

libgmock_la_SOURCES         =   $(gmocklib_sources) $(gmocklib_headers)

libgmock_la_CXXFLAGS        =   $(AM_CXXFLAGS) \
                                -I$(gmock_incdir) \
                                -I$(opentxs_incdir)

libgmock_la_LDFLAGS         =   --no-undefined -g

######################## DEPENDENCIES ###############################

gmocklib_sources            =   gmock.cc \
                                gmock-cardinalities.cc \
                                gmock-internal-utils.cc \
                                gmock-matchers.cc \
                                gmock-spec-builders.cc                

gmocklib_headers            =   stdafx.h