bin_PROGRAMS                =   otapitest
lib_LTLIBRARIES             =   libotapitest.la

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

libotapitest_la_SOURCES     =   $(otapitest_sources) $(otapitest_headers)

libotapitest_la_CXXFLAGS    =   $(AM_CXXFLAGS) \
                                -I$(otapitest_incdir) \
                                $(common_includes)

libotapitest_la_LDFLAGS     =   --no-undefined -g

if TRANSPORT_ZMQ
libotapitest_la_CXXFLAGS   +=   -DOT_ZMQ_MODE
endif

libotapitest_la_DEPENDENCIES=   $(common_libraries) \
                                $(gmock_srcdir)/libgmock.la \
                                $(gtest_srcdir)/libgtest.la

libotapitest_la_LIBADD      =   $(libotapitest_la_DEPENDENCIES) \
                                $(DEPS_LIBS)

otapitest_SOURCES           =   otapitest.cpp $(otapitest_headers)

otapitest_CXXFLAGS          =   $(libotapitest_la_CXXFLAGS)

otapitest_DEPENDENCIES      =   libotapitest.la

otapitest_LDADD             =   $(otapitest_DEPENDENCIES) $(libotapitest_la_LIBADD)

otapitest_LDFLAGS           =   -g

######################## DEPENDENCIES ###############################

otapitest_sources           =   AllRequests.cpp \
                                AllTransactions.cpp \
                                OtMeExtra.cpp \
                                OtMeTest.cpp \
                                Test_accept_from_paymentbox.cpp \
                                Test_accept_inbox_items.cpp \
                                Test_cancel_outgoing_payments.cpp \
                                Test_create_pseudonym.cpp \
                                Test_deposit_cash.cpp \
                                Test_deposit_local_purse.cpp \
                                Test_details_deposit_cheque.cpp \
                                Test_details_export_cash.cpp \
                                Test_discard_incoming_payments.cpp \
                                Test_export_cash.cpp \
                                Test_get_payment_instrument.cpp \
                                Test_handle_payment_index.cpp \
                                Test_insure_enough_nums.cpp \
                                Test_load_or_retrieve_contract.cpp \
                                Test_load_or_retrieve_encrypt_key.cpp \
                                Test_load_or_retrieve_mint.cpp \
                                Test_load_or_retrieve_signing_key.cpp \
                                Test_ot_utility.cpp \
                                Test_ot_utility_ReceiveReplyLowLevel.cpp \
                                Test_ot_utility_getAndProcessNymbox_4.cpp \
                                Test_ot_utility_getNymbox.cpp \
                                Test_ot_utility_getNymboxLowLevel.cpp \
                                Test_ot_utility_getRequestNumber.cpp \
                                Test_ot_utility_getTransactionNumLowLevel.cpp \
                                Test_ot_utility_getTransactionNumbers.cpp \
                                Test_ot_utility_processNymbox.cpp \
                                Test_ot_utility_receiveReplySuccessLowLevel.cpp \
                                Test_register_nym.cpp \
                                Test_retrieve_account.cpp \
                                Test_retrieve_nym.cpp \
                                Test_stat_asset_account.cpp \
                                Test_withdraw_and_send_cash.cpp

otapitest_headers           =   stdafx.h \
                                $(otapitest_incdir)/OtMeExtra.hpp \
                                $(otapitest_incdir)/OtMeTest.hpp
