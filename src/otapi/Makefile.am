lib_LTLIBRARIES                 =   libotapi.la

########################## STANDARD FOLDERS #########################

opentxs_incdir                  =   $(top_srcdir)/include
opentxs_srcdir                  =   $(top_srcdir)/src

gmock_incdir                    =   $(opentxs_incdir)/gmock
gmock_srcdir                    =   $(opentxs_srcdir)/gmock
gtest_incdir                    =   $(opentxs_incdir)/gtest
gtest_srcdir                    =   $(opentxs_srcdir)/gtest
ot_incdir                       =   $(opentxs_incdir)/otd
ot_srcdir                       =   $(opentxs_srcdir)/otd
otapi_incdir                    =   $(opentxs_incdir)/otapi
otapi_srcdir                    =   $(opentxs_srcdir)/otapi
otapitest_incdir                =   $(opentxs_incdir)/otapitest
otapitest_srcdir                =   $(opentxs_srcdir)/otapitest
otlib_incdir                    =   $(opentxs_incdir)/otlib
otlib_srcdir                    =   $(opentxs_srcdir)/otlib
otmint_incdir                   =   $(opentxs_incdir)/otmint
otmint_srcdir                   =   $(opentxs_srcdir)/otmint
otserver_incdir                 =   $(opentxs_incdir)/ots
otserver_srcdir                 =   $(opentxs_srcdir)/ots

swig_dir                        =   $(top_srcdir)/swig

common_includes                 =   -I$(otapi_incdir) \
                                    -I$(otlib_incdir) \
                                    -I$(opentxs_incdir)

common_libraries                =   $(otapi_srcdir)/libotapi.la \
                                    $(otlib_srcdir)/libotlib.la
                                        
######################## BUILD COMMANDS #############################

libotapi_la_SOURCES             =   $(otapi_sources) $(otapi_headers)

libotapi_la_CXXFLAGS            =   $(AM_CXXFLAGS) $(common_includes)

if TRANSPORT_ZMQ
libotapi_la_CXXFLAGS           +=   -DOT_ZMQ_MODE
endif

libotapi_la_LDFLAGS             =   --no-undefined -g

libotapi_la_DEPENDENCIES        =   $(otlib_srcdir)/libotlib.la

libotapi_la_LIBADD              =   $(libotapi_la_DEPENDENCIES) $(DEPS_LIBS)

######################## EXTRA BUILD COMMANDS #############################

#### OT API JAVA

if WANT_JAVA
lib_LTLIBRARIES                +=   libotapi-java.la
endif

libotapi_java_la_SOURCES        =   $(swig_dir)/otapi/OTAPI-java.cxx \
                                    $(swig_dir)/otapi/OTAPI-java.hpp

libotapi_java_la_CXXFLAGS       =   $(AM_CXXFLAGS) $(common_includes) $(JNI_CPPFLAGS)

libotapi_java_la_DEPENDENCIES   =   $(common_libraries) 
libotapi_java_la_LIBADD         =   $(libotapi_java_la_DEPENDENCIES) $(DEPS_LIBS)
libotapi_java_la_LDFLAGS        =   --no-undefined

if TRANSPORT_ZMQ
libotapi_java_la_CXXFLAGS      +=   -DOT_ZMQ_MODE
endif

#### OT API PERL5

if WANT_PERL5
lib_LTLIBRARIES                +=   libotapi-perl5.la
endif

libotapi_perl5_la_SOURCES       =   $(swig_dir)/otapi/OTAPI-perl5.cxx
libotapi_perl5_la_CXXFLAGS      =   $(AM_CXXFLAGS) $(common_includes) \
                                    -I$(PERL_EXT_INC) \
                                    $(PERL_EXT_CPPFLAGS)
libotapi_perl5_la_DEPENDENCIES  =   $(common_libraries) 
libotapi_perl5_la_LIBADD        =   $(libotapi_perl5_la_DEPENDENCIES) $(DEPS_LIBS)
libotapi_perl5_la_LDFLAGS       =   $(PERL_EXT_LDFLAGS) --no-undefined

if TRANSPORT_ZMQ
libotapi_perl5_la_CXXFLAGS     +=   -DOT_ZMQ_MODE
endif

#### OT API PHP

if WANT_PHP
lib_LTLIBRARIES                +=   libotapi-php.la
endif

libotapi_php_la_SOURCES         =   $(swig_dir)/otapi/OTAPI-php.cpp \
                                    $(swig_dir)/otapi/OTAPI-php.hpp
libotapi_php_la_CXXFLAGS        =   $(AM_CXXFLAGS) $(common_includes) \
                                    -I$(swig_dir)/glue/php \
                                    $(PHP_INCLUDES)
libotapi_php_la_DEPENDENCIES    =   $(common_libraries) 
libotapi_php_la_LIBADD          =   $(libotapi_php_la_DEPENDENCIES)  $(DEPS_LIBS)
libotapi_php_la_LDFLAGS         =   $(PHP_LDFLAGS) --no-undefined

if TRANSPORT_ZMQ
libotapi_php_la_CXXFLAGS       +=   -DOT_ZMQ_MODE
endif

#### OT API PYTHON

if WANT_PYTHON
lib_LTLIBRARIES                +=   _otapi.la
endif

_otapi_la_SOURCES               =   $(swig_dir)/otapi/OTAPI-python.cxx \
                                    $(swig_dir)/otapi/OTAPI-python.hpp

_otapi_la_CXXFLAGS              =   $(AM_CXXFLAGS) $(common_includes) \
                                    $(PYTHON_CPPFLAGS) \
                                    $(PYTHON_EXTRA_LIBS)
_otapi_la_DEPENDENCIES          =   $(common_libraries) 
_otapi_la_LIBADD                =   $(_otapi_la_DEPENDENCIES)  $(DEPS_LIBS)
_otapi_la_LDFLAGS               =   --no-undefined \
                                    -module -avoid-version \
                                    $(PYTHON_LDFLAGS) \
                                    $(PYTHON_EXTRA_LDFLAGS)

if TRANSPORT_ZMQ
_otapi_la_CXXFLAGS             +=   -DOT_ZMQ_MODE
endif

#### OT API RUBY

if WANT_RUBY
lib_LTLIBRARIES                +=   libotapi-ruby.la
endif

libotapi_ruby_la_SOURCES        =   $(swig_dir)/otapi/OTAPI-ruby. \
                                    $(swig_dir)/otapi/OTAPI-ruby.hpp
libotapi_ruby_la_CXXFLAGS       =   $(AM_CXXFLAGS) $(common_includes) \
                                    $(RUBY_CPPFLAGS) \
                                    $(RUBY_EXTRA_LIBS)
libotapi_ruby_la_DEPENDENCIES   =   $(common_libraries) 
libotapi_ruby_la_LIBADD         =   $(libotapi_ruby_la_DEPENDENCIES)  $(DEPS_LIBS)
libotapi_ruby_la_LDFLAGS        =   $(RUBY_LDFLAGS) --no-undefined

if TRANSPORT_ZMQ
libotapi_ruby_la_CXXFLAGS      +=   -DOT_ZMQ_MODE
endif

#### OT API TCL

if WANT_TCL
lib_LTLIBRARIES                +=   libotapi-tcl.la
endif

libotapi_tcl_la_SOURCES         =   $(swig_dir)/otapi/OTAPI-tcl.cxx
libotapi_tcl_la_CXXFLAGS        =   $(AM_CXXFLAGS) $(common_includes)
libotapi_tcl_la_DEPENDENCIES    =   $(common_libraries) 
libotapi_tcl_la_LIBADD          =   $(libotapi_tcl_la_DEPENDENCIES)  $(DEPS_LIBS)
libotapi_tcl_la_LDFLAGS         =   --no-undefined

if TRANSPORT_ZMQ
libotapi_tcl_la_CXXFLAGS       +=   -DOT_ZMQ_MODE
endif

#### OT API CSHARP

if WANT_CSHARP
lib_LTLIBRARIES                +=   libotapi-csharp.la
endif

libotapi_csharp_la_SOURCES      =   $(swig_dir)/otapi/OTAPI-csharp.cxx \
                                    $(swig_dir)/otapi/OTAPI-csharp.hpp
libotapi_csharp_la_CXXFLAGS     =   $(AM_CXXFLAGS) $(common_includes)
libotapi_csharp_la_DEPENDENCIES =   $(common_libraries) 
libotapi_csharp_la_LIBADD       =   $(libotapi_csharp_la_DEPENDENCIES)  $(DEPS_LIBS)
libotapi_csharp_la_LDFLAGS      =   --no-undefined

if TRANSPORT_ZMQ
libotapi_csharp_la_CXXFLAGS    +=   -DOT_ZMQ_MODE
endif

#### OT API D

if WANT_D
lib_LTLIBRARIES                +=   libotapi-d.la
endif

libotapi_d_la_SOURCES           =   $(swig_dir)/otapi/OTAPI-d.cxx \
                                    $(swig_dir)/otapi/OTAPI-d.hpp
libotapi_d_la_CXXFLAGS          =   $(AM_CXXFLAGS) $(common_includes)
libotapi_d_la_DEPENDENCIES      =   $(common_libraries) 
libotapi_d_la_LIBADD            =   $(libotapi_d_la_DEPENDENCIES)  $(DEPS_LIBS)
libotapi_d_la_LDFLAGS           =   --no-undefined

if TRANSPORT_ZMQ
libotapi_d_la_CXXFLAGS         +=   -DOT_ZMQ_MODE
endif

#### OT API GO

if WANT_GO
lib_LTLIBRARIES                +=   libotapi-go.la
endif

libotapi_go_la_SOURCES          =   $(swig_dir)/otapi/OTAPI-go.cxx \
                                    $(swig_dir)/otapi/OTAPI-go.hpp
libotapi_go_la_CXXFLAGS         =   $(AM_CXXFLAGS) $(common_includes)
libotapi_go_la_DEPENDENCIES     =   $(common_libraries) 
libotapi_go_la_LIBADD           =   $(libotapi_go_la_DEPENDENCIES)  $(DEPS_LIBS)
libotapi_go_la_LDFLAGS          =   --no-undefined

if TRANSPORT_ZMQ
libotapi_go_la_CXXFLAGS        +=   -DOT_ZMQ_MODE
endif

######################## DEPENDENCIES ###############################

otapi_sources                   =   OpenTransactions.cpp \
                                    ot_commands_ot.cpp \
                                    ot_made_easy_ot.cpp \
                                    OT_ME.cpp \
                                    OT_ME_NEW.cpp \
                                    ot_opentxs_ot.cpp \
                                    ot_otapi_ot.cpp \
                                    ot_utility_ot.cpp \
                                    OTAPI.cpp \
                                    OTAPI_Basic.cpp \
                                    OTAPI_Exec.cpp \
                                    OTClient.cpp \
                                    OTMadeEasy.cpp \
                                    OTServerConnection.cpp

otapi_headers                   =   $(otapi_incdir)/main.hpp \
                                    $(otapi_incdir)/ot_commands_ot.hpp \
                                    $(otapi_incdir)/ot_made_easy_ot.hpp \
                                    $(otapi_incdir)/ot_me_switch.hpp \
                                    $(otapi_incdir)/ot_otapi_ot.hpp \
                                    $(otapi_incdir)/ot_utility_ot.hpp \
                                    $(otapi_incdir)/OTClient.hpp \
                                    $(otapi_incdir)/OTServerConnection.hpp \
                                    $(otapi_headers_ext)

otapi_headers_ext               =   $(otapi_incdir)/OpenTransactions.hpp \
                                    $(otapi_incdir)/OT_ME.hpp \
                                    $(otapi_incdir)/OTAPI.hpp \
                                    $(otapi_incdir)/OTAPI_Basic.hpp \
                                    $(otapi_incdir)/OTAPI_Exec.hpp \
                                    $(otapi_incdir)/OTMadeEasy.hpp

pkginclude_HEADERS              =   $(otapi_headers_ext)
