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
                                $(otlib_incdir)/libotlib.la
                                        
######################## BUILD COMMANDS #############################


libotapitest_la_SOURCES     =   $(otapitest_sources) $(otapitest_headers)

libotapitest_la_CXXFLAGS    =   $(AM_CXXFLAGS) \
                                -I$(opentxs_include_dir)/otapitest \
                                $(common_includes)

libotapitest_la_DEPENDENCIES    =   $(common_libraries) \
                                    $(gmock_srcdir)/libgmock.la \
                                    $(gmock_srcdir)/libgtest.la

libotapitest_la_LIBADD      =   $(libotapitest_la_DEPENDENCIES) $(DEPS_LIBS)

libotapitest_la_LDFLAGS     =   --no-undefined -g

if TRANSPORT_ZMQ
libotapitest_la_CXXFLAGS   +=   -DOT_ZMQ_MODE
endif

######################## DEPENDENCIES ###############################

otapitest_sources           =   $(otapitest_srcdir)/AllRequests.cpp \
                                $(otapitest_srcdir)/Test_insure_enough_nums.cpp \
                                $(otapitest_srcdir)/AllTransactions.cpp \
                                $(otapitest_srcdir)/Test_load_or_retrieve_contract.cpp \
                                $(otapitest_srcdir)/Test_load_or_retrieve_encrypt_key.cpp \
                                $(otapitest_srcdir)/Test_load_or_retrieve_mint.cpp \
                                $(otapitest_srcdir)/otapitest.cpp \
                                $(otapitest_srcdir)/Test_load_or_retrieve_signing_key.cpp \
                                $(otapitest_srcdir)/OtMeExtra.cpp \
                                $(otapitest_srcdir)/Test_ot_utility.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_getAndProcessNymbox_4.cpp \
                                $(otapitest_srcdir)/OtMeTest.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_getNymbox.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_getNymboxLowLevel.cpp \
                                $(otapitest_srcdir)/Test_accept_from_paymentbox.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_getRequestNumber.cpp \
                                $(otapitest_srcdir)/Test_accept_inbox_items.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_getTransactionNumbers.cpp \
                                $(otapitest_srcdir)/Test_cancel_outgoing_payments.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_getTransactionNumLowLevel.cpp \
                                $(otapitest_srcdir)/Test_create_pseudonym.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_processNymbox.cpp \
                                $(otapitest_srcdir)/Test_deposit_cash.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_ReceiveReplyLowLevel.cpp \
                                $(otapitest_srcdir)/Test_deposit_local_purse.cpp \
                                $(otapitest_srcdir)/Test_ot_utility_receiveReplySuccessLowLevel.cpp \
                                $(otapitest_srcdir)/Test_details_deposit_cheque.cpp \
                                $(otapitest_srcdir)/Test_register_nym.cpp \
                                $(otapitest_srcdir)/Test_details_export_cash.cpp \
                                $(otapitest_srcdir)/Test_retrieve_account.cpp \
                                $(otapitest_srcdir)/Test_discard_incoming_payments.cpp \
                                $(otapitest_srcdir)/Test_retrieve_nym.cpp \
                                $(otapitest_srcdir)/Test_export_cash.cpp \
                                $(otapitest_srcdir)/Test_stat_asset_account.cpp \
                                $(otapitest_srcdir)/Test_get_payment_instrument.cpp \
                                $(otapitest_srcdir)/Test_withdraw_and_send_cash.cpp \
                                $(otapitest_srcdir)/Test_handle_payment_index.cpp

otapitest_headers           =   $(otapitest_incdir)/stdafx.h \
                                $(otapitest_incdir)/OtMeExtra.hpp \
                                $(otapitest_incdir)/OtMeTest.hpp
