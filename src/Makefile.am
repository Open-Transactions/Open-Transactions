
AUTOMAKE_OPTIONS	=	subdir-objects

SUBDIRS                 =	otlib otextensions otapi

opentxs_include_dir     =	$(top_srcdir)/include
opentxs_source_dir      =	$(top_srcdir)/src

common_includes         =	$(AM_CXXFLAGS)		 		\
				-I$(top_srcdir)/deps/include/misc	\
				-I$(top_srcdir)/deps/include		\
				-I$(opentxs_include_dir)		\
				-I$(opentxs_include_dir)/otlib

## Open Transactions Bin Build  ##

bin_PROGRAMS            =   ot opentxs otserver createmint

#### OT

ot_SOURCES              =  $(ot_sources) $(otapi_headers)

ot_CXXFLAGS             =  $(common_includes) -I$(otapi_headers_dir)

ot_LDADD                =  otapi/libotapi.la otlib/libot.la $(DEPS_LIBS)
ot_DEPENDENCIES         =  otapi/libotapi.la otlib/libot.la

#### OPENTXS

opentxs_SOURCES         =  $(opentxs_sources) $(otapi_headers)

opentxs_CXXFLAGS        =  $(common_includes) -I$(otapi_headers_dir)

opentxs_LDADD           =  otapi/libotapi.la otextensions/libotextensions.la otlib/libot.la $(DEPS_LIBS)
opentxs_DEPENDENCIES    =  otapi/libotapi.la otextensions/libotextensions.la otlib/libot.la

#### OT Server

otserver_SOURCES        =   $(otserver_common) $(otserver_sources) $(otserver_headers)

otserver_CXXFLAGS       =   $(common_includes) -I$(otserver_headers_dir) -I$(opentxs_include_dir)/otextensions

otserver_LDADD          =   otextensions/libotextensions.la otlib/libot.la $(DEPS_LIBS)
otserver_DEPENDENCIES   =   otextensions/libotextensions.la otlib/libot.la


#### Createmint  (includes files from OT Server)

createmint_SOURCES      =   $(createmint_sources) $(otserver_common) $(otserver_headers)

createmint_CXXFLAGS     =   $(common_includes) -I$(otserver_headers_dir)

createmint_LDADD        =   otlib/libot.la $(DEPS_LIBS)
createmint_DEPENDENCIES =   otlib/libot.la


#### OT

ot_sources              =   otd/main.cpp

opentxs_sources         =   otc/main.cpp

otapi_headers_dir       =   $(opentxs_include_dir)/otapi

otapi_headers           =   $(otapi_headers_dir)/main.hpp		\
                            $(otapi_headers_dir)/OpenTransactions.hpp	\
                            $(otapi_headers_dir)/OTAPI.hpp		\
                            $(otapi_headers_dir)/OT_ME.hpp		\
                            $(otapi_headers_dir)/OTClient.hpp		\
                            $(otapi_headers_dir)/OTServerConnection.hpp	\
                            $(otapi_headers_dir)/ot_otapi_ot.hpp

#### OT Server

otserver_common         =   ots/OTClientConnection.cpp	\
                            ots/OTServer.cpp

otserver_sources        =   ots/xmlrpcxx_server.cpp

otserver_headers_dir    =   $(opentxs_include_dir)/ots

otserver_headers        =   $(otserver_headers_dir)/main.hpp			\
                            $(otserver_headers_dir)/OTClientConnection.hpp	\
                            $(otserver_headers_dir)/OTServer.hpp
                            
if KEYRING_FLATFILE

otserver_CXXFLAGS       += -DOT_KEYRING_FLATFILE

endif
                            

#### OT Create Mint

createmint_sources      =   otmint/main.cpp
