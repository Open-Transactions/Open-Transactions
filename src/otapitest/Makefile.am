###############################
## Open Transactions API Testing Libs #
###############################

## OpenTransactions test program

bin_PROGRAMS            =   otapitest

##SUBDIRS = java python perl5 php d ruby lisp ... coming soon?

lib_LTLIBRARIES = libotapitest.la

### Common variables, flags ###

opentxs_include_dir	=	$(top_srcdir)/include
opentxs_swig_dir	=	$(top_srcdir)/swig

otlib_build_dir		=	$(top_builddir)/src/otlib
otapi_build_dir		=	$(top_builddir)/src/otapi

common_includes		=	$(AM_CXXFLAGS)          	\
                -I$(top_builddir)/project/otapitest		\
				-I$(top_builddir)/include/otlib	\
								-I$(opentxs_include_dir)	\
				-I$(opentxs_include_dir)/otlib	\
				-I$(opentxs_include_dir)/otapi  \
                -I$(opentxs_include_dir)/otapitest \
				-I$(top_builddir)/include/gmock	\
				-I$(top_builddir)/include/gtest


########################

libotapitest_la_SOURCES	=	$(otapitest_sources) $(otapitest_headers)	\
					$(simpleini_headers)
otapitest_SOURCES		= 	($libotapitest_la_SOURCES)

libotapitest_la_CXXFLAGS	=	$(common_includes)
otapitest_CXXFLAGS		=       $(common_includes)

libotapitest_la_LIBADD		=	$$(libotapitest_la_DEPENDENCIES) $(DEPS_LIBS)
otapitest_LDADD			=	libotapitest.la $(libotapitest_la_LIBADD)

libotapitest_la_DEPENDENCIES	=       $(otlib_build_dir)/libot.la     \
                                        $(otapi_build_dir)/libotapi.la  \
                                        $(top_builddir)/src/gmock/libgmock.la  \
                                        $(top_builddir)/src/gtest/libgtest.la
otapitest_DEPENDENCIES		=       $(libotapitest_la_DEPENDENCIES)

libotapitest_la_LDFLAGS		=	--no-undefined -g
otapitest_LDFLAGS		= 	-g -v
if TRANSPORT_ZMQ
libotapitest_la_CXXFLAGS		+=	-DOT_ZMQ_MODE
otapitest_CXXFLAGS			+=      -DOT_ZMQ_MODE
endif

############################
#### OT TEST Library sources / headers
############################

otapitest_sources_dir	= 	$(top_srcdir)/src/otapitest

otapitest_sources	=	$(otapitest_sources_dir)/AllRequests.cpp				\
				$(otapitest_sources_dir)/Test_insure_enough_nums.cpp			\
                                $(otapitest_sources_dir)/AllTransactions.cpp				\
                                $(otapitest_sources_dir)/Test_load_or_retrieve_contract.cpp		\
                                $(otapitest_sources_dir)/Test_load_or_retrieve_encrypt_key.cpp		\
                                $(otapitest_sources_dir)/Test_load_or_retrieve_mint.cpp			\
                                $(otapitest_sources_dir)/otapitest.cpp					\
                                $(otapitest_sources_dir)/Test_load_or_retrieve_signing_key.cpp		\
                                $(otapitest_sources_dir)/OtMeExtra.cpp					\
                                $(otapitest_sources_dir)/Test_ot_utility.cpp				\
                                $(otapitest_sources_dir)/Test_ot_utility_getAndProcessNymbox_4.cpp	\
                                $(otapitest_sources_dir)/OtMeTest.cpp					\
                                $(otapitest_sources_dir)/Test_ot_utility_getNymbox.cpp			\
                                $(otapitest_sources_dir)/Test_ot_utility_getNymboxLowLevel.cpp		\
                                $(otapitest_sources_dir)/Test_accept_from_paymentbox.cpp		\
                                $(otapitest_sources_dir)/Test_ot_utility_getRequestNumber.cpp		\
                                $(otapitest_sources_dir)/Test_accept_inbox_items.cpp			\
                                $(otapitest_sources_dir)/Test_ot_utility_getTransactionNumbers.cpp	\
                                $(otapitest_sources_dir)/Test_cancel_outgoing_payments.cpp		\
                                $(otapitest_sources_dir)/Test_ot_utility_getTransactionNumLowLevel.cpp	\
                                $(otapitest_sources_dir)/Test_create_pseudonym.cpp			\
                                $(otapitest_sources_dir)/Test_ot_utility_processNymbox.cpp		\
                                $(otapitest_sources_dir)/Test_deposit_cash.cpp				\
                                $(otapitest_sources_dir)/Test_ot_utility_ReceiveReplyLowLevel.cpp	\
                                $(otapitest_sources_dir)/Test_deposit_local_purse.cpp			\
                                $(otapitest_sources_dir)/Test_ot_utility_receiveReplySuccessLowLevel.cpp \
                                $(otapitest_sources_dir)/Test_details_deposit_cheque.cpp		\
                                $(otapitest_sources_dir)/Test_register_nym.cpp				\
                                $(otapitest_sources_dir)/Test_details_export_cash.cpp			\
                                $(otapitest_sources_dir)/Test_retrieve_account.cpp			\
                                $(otapitest_sources_dir)/Test_discard_incoming_payments.cpp		\
                                $(otapitest_sources_dir)/Test_retrieve_nym.cpp				\
                                $(otapitest_sources_dir)/Test_export_cash.cpp				\
                                $(otapitest_sources_dir)/Test_stat_asset_account.cpp			\
                                $(otapitest_sources_dir)/Test_get_payment_instrument.cpp		\
                                $(otapitest_sources_dir)/Test_withdraw_and_send_cash.cpp		\
                                $(otapitest_sources_dir)/Test_handle_payment_index.cpp			\
                                $(top_builddir)/project/otapitest/stdafx.h

otapitest_headers_dir	=	$(opentxs_include_dir)/otapi

otapitest_headers	=	$(top_builddir)/project/otapitest/stdafx.h		\
				$(opentxs_include_dir)/otlib/OTPaths.h		\
				$(otapitest_sources_dir)/OtMeExtra.hpp		\
				$(otapitest_sources_dir)/OtMeTest.hpp

pkginclude_HEADERS	=	$(otapi_headers_ext)
