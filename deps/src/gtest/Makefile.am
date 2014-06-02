lib_LTLIBRARIES             =   libgtest.la

########################## STANDARD FOLDERS #########################

opentxs_incdir              =   $(top_srcdir)/include
opentxs_srcdir              =   $(top_srcdir)/src

gmock_incdir                =   $(top_srcdir)/deps/include/gmock
gmock_srcdir                =   $(top_srcdir)/deps/src/gmock
gtest_incdir                =   $(top_srcdir)/deps/include/gtest
gtest_srcdir                =   $(top_srcdir)/deps/src/gtest
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

common_includes             =   $(AM_CXXFLAGS)			\
				-I$(top_builddir)/include/otlib	\
				-I$(otapi_incdir)		\
                                -I$(otlib_incdir)		\
                                -I$(opentxs_incdir)		\
                                -I$(top_srcdir)/deps/include

common_libraries            =   $(otapi_srcdir)/libotapi.la \
                                $(otlib_srcdir)/libotlib.la
                                        
######################## BUILD COMMANDS #############################

libgtest_la_SOURCES         =   $(gtestlib_sources) $(gtestlib_headers)

libgtest_la_CXXFLAGS        =   $(common_includes) -I$(gtest_incdir)

libgtest_la_LDFLAGS         =   --no-undefined -g

######################## DEPENDENCIES ###############################

gtestlib_sources            =   gtest.cc		\
                                gtest-death-test.cc	\
                                gtest-filepath.cc	\
                                gtest-port.cc		\
                                gtest-printers.cc	\
                                gtest-test-part.cc	\
                                gtest-typed-test.cc               

gtestlib_headers	=	$(gtest_incdir)/gtest-death-test.h	\
				$(gtest_incdir)/gtest.h			\
				$(gtest_incdir)/gtest-message.h		\
				$(gtest_incdir)/gtest-param-test.h	\
				$(gtest_incdir)/gtest_pred_impl.h	\
				$(gtest_incdir)/gtest-printers.h	\
				$(gtest_incdir)/gtest_prod.h		\
				$(gtest_incdir)/gtest-spi.h		\
				$(gtest_incdir)/gtest-test-part.h	\
				$(gtest_incdir)/gtest-typed-test.h	\
				$(gtest_incdir)/internal/gtest-death-test-internal.h	\
				$(gtest_incdir)/internal/gtest-filepath.h		\
				$(gtest_incdir)/internal/gtest-param-util.h		\
				$(gtest_incdir)/internal/gtest-type-util.h		\
				$(gtest_incdir)/internal/gtest-internal.h		\
				$(gtest_incdir)/internal/gtest-port.h			\
				$(gtest_incdir)/internal/gtest-linked_ptr.h		\
				$(gtest_incdir)/internal/gtest-string.h			\
				$(gtest_incdir)/internal/gtest-param-util-generated.h	\
				$(gtest_incdir)/internal/gtest-tuple.h			\
				$(gtest_incdir)/src/gtest-internal-inl.h

