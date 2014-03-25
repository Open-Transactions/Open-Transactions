SUBDIRS                     =   otlib otapi

bin_PROGRAMS                =   ot otserver createmint

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


#### Createmint  (includes files from OT Server)

createmint_SOURCES          =   $(createmint_sources) $(otserver_sources) $(otserver_headers)

createmint_CXXFLAGS         =   $(AM_CXXFLAGS) \
                                -I$(otserver_incdir) \
                                $(common_includes)

createmint_DEPENDENCIES     =   $(common_libraries)

createmint_LDADD            =   $(common_libraries) $(DEPS_LIBS)


#### OT

ot_SOURCES                  =   $(ot_sources) $(ot_headers)

ot_CXXFLAGS                 =   $(AM_CXXFLAGS) $(common_includes)

ot_DEPENDENCIES             =   $(common_libraries)

ot_LDADD                    =   $(ot_DEPENDENCIES) $(DEPS_LIBS)


#### OT Server

otserver_SOURCES            =   $(otserver_sources) $(otserver_headers)

otserver_CXXFLAGS           =   $(AM_CXXFLAGS) \
                                -I$(otserver_incdir) \
                                $(common_includes)

otserver_DEPENDENCIES       =   $(common_libraries)

otserver_LDADD              =   $(otserver_DEPENDENCIES) $(DEPS_LIBS)


#### Transport ZMQ 'option'

if TRANSPORT_ZMQ
createmint_CXXFLAGS        +=   -DOT_ZMQ_MODE
ot_CXXFLAGS                +=   -DOT_ZMQ_MODE
otserver_SOURCES           +=   ots/xmlrpcxx_server.cpp
otserver_CXXFLAGS          +=   -DOT_ZMQ_MODE
endif

######################## DEPENDENCIES ###############################

#### CreateMint

createmint_sources          =   $(otmint_srcdir)/main.cpp


#### OT

ot_sources                  =   $(ot_srcdir)/main.cpp

ot_headers                  =   $(otapi_incdir)/main.hpp             \
                                $(otapi_incdir)/OpenTransactions.hpp \
                                $(otapi_incdir)/OTAPI.hpp            \
                                $(otapi_incdir)/OT_ME.hpp            \
                                $(otapi_incdir)/ot_switch_me.hpp   \
                                $(otapi_incdir)/OTClient.hpp         \
                                $(otapi_incdir)/OTServerConnection.hpp


#### OT Server

otserver_sources            =   $(otserver_srcdir)/OTClientConnection.cpp  \
                                $(otserver_srcdir)/OTServer.cpp

otserver_headers            =   $(otserver_incdir)/main.hpp   \
                                $(otserver_incdir)/OTClientConnection.hpp \
                                $(otserver_incdir)/OTServer.hpp
