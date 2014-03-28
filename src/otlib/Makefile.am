
AUTOMAKE_OPTIONS 	=	subdir-objects

SUBDIRS 		= 	otprotob bigint irrxml lucre otext

lib_LTLIBRARIES		=	libot.la

opentxs_include_dir 	=	$(top_srcdir)/include
opentxs_source_dir 	=	$(top_srcdir)/src

## COMMON FLAGS ###

common_includes		=	$(AM_CXXFLAGS)			\
				-I$(top_builddir)/include/otlib 	\
				-I$(opentxs_include_dir)		\
				-I$(opentxs_include_dir)/otlib	\
				-I$(opentxs_include_dir)/containers	\
				-DOT_PREFIX_PATH="\"${prefix}\""	\
				-DOT_VERSION="\"${VERSION}\""


#### Lib OT build calls

libot_la_SOURCES	=	$(otlib_sources)		\
				$(otlib_headers)		\
				$(containers_headers)

libot_la_CXXFLAGS	=	$(common_includes)

libot_la_LIBADD		=	bigint/libbigint.la	\
                                irrxml/libirrxml.la \
                                lucre/liblucre.la \
				otprotob/libotprotob.la		\
                                otext/libotext.la \
                                $(DEPS_LIBS)

libot_la_DEPENDENCIES	=	bigint/libbigint.la		\
				irrxml/libirrxml.la		\
				lucre/liblucre.la		\
				otprotob/libotprotob.la		\
				otext/libotext.la

libot_la_LDFLAGS	=	--no-undefined


#### KEYRING Options

if KEYRING_WINDOWS
libot_la_CXXFLAGS		+=	-DOT_KEYRING_WINDOWS
endif

if KEYRING_MAC
libot_la_CXXFLAGS		+=	-DOT_KEYRING_MAC
endif

if KEYRING_GNOME
libot_la_CXXFLAGS		+=	-DOT_KEYRING_GNOME
endif

if KEYRING_KWALLET
libot_la_CXXFLAGS		+=	-DOT_KEYRING_KWALLET
endif

if KEYRING_FLATFILE
libot_la_CXXFLAGS       +=  -DOT_KEYRING_FLATFILE
endif

####################################################################


otlib_sources               =   OTAccount.cpp \
                                OTAgreement.cpp \
                                OTASCIIArmor.cpp \
                                OTAssert.cpp \
                                OTAssetContract.cpp \
                                OTAsymmetricKey.cpp \
                                OTBasket.cpp \
                                OTBylaw.cpp \
                                OTCachedKey.cpp \
                                OTCheque.cpp \
                                OTContract.cpp \
                                OTCredential.cpp \
                                OTCron.cpp \
                                OTCronItem.cpp \
                                OTCrypto.cpp \
                                OTData.cpp \
                                OTDataCheck.cpp \
                                OTDigitalCash.cpp \
                                OTEnvelope.cpp \
                                OTIdentifier.cpp \
                                OTInstrument.cpp \
                                OTItem.cpp \
                                OTKeyring.cpp \
                                OTLedger.cpp \
                                OTLog.cpp \
                                OTMarket.cpp \
                                OTMessage.cpp \
                                OTMessageBuffer.cpp \
                                OTMint.cpp \
                                OTOffer.cpp \
                                OTPassword.cpp \
                                OTPaths.cpp \
                                OTPayload.cpp \
                                OTPayment.cpp \
                                OTPaymentPlan.cpp \
                                OTPseudonym.cpp \
                                OTPurse.cpp \
                                OTScript.cpp \
                                OTScriptable.cpp \
                                OTServerContract.cpp \
                                OTSettings.cpp \
                                OTSignature.cpp \
                                OTSignedFile.cpp \
                                OTSmartContract.cpp \
                                OTStorage.cpp \
                                OTString.cpp \
                                OTStringXML.cpp \
                                OTSymmetricKey.cpp \
                                OTToken.cpp \
                                OTTrackable.cpp \
                                OTTrade.cpp \
                                OTTransaction.cpp \
                                OTTransactionType.cpp \
                                OTWallet.cpp


otlib_headers_dir	=	$(opentxs_include_dir)/otlib

otlib_headers		=	$(otlib_headers_dir)/constants.h		\
				$(otlib_headers_dir)/fast_mutex.h		\
				$(otlib_headers_dir)/WinsockWrapper.h		\
				$(otlib_headers_dir)/tinythread.hpp		\
				$(otlib_headers_dir)/Timer.hpp			\
				$(otlib_headers_ext)

otlib_headers_ext	=	$(top_builddir)/include/otlib/ot_config.h    \
				$(otlib_headers_dir)/ExportWrapper.h		\
				$(otlib_headers_dir)/WinsockWrapper.h		\
				$(otlib_headers_dir)/TR1_Wrapper.hpp		\
				$(otlib_headers_dir)/stacktrace.h		\
				$(otlib_headers_dir)/stdafx.h			\
				$(otlib_headers_dir)/stdafx.hpp			\
				$(otlib_headers_dir)/OTAccount.hpp		\
				$(otlib_headers_dir)/OTAgreement.hpp		\
				$(otlib_headers_dir)/OTASCIIArmor.hpp		\
				$(otlib_headers_dir)/OTAssert.hpp		\
				$(otlib_headers_dir)/OTAssetContract.hpp	\
				$(otlib_headers_dir)/OTAsymmetricKey.hpp	\
				$(otlib_headers_dir)/OTBasket.hpp		\
				$(otlib_headers_dir)/OTBylaw.hpp		\
				$(otlib_headers_dir)/OTCachedKey.hpp		\
				$(otlib_headers_dir)/OTCheque.hpp		\
				$(otlib_headers_dir)/OTContract.hpp		\
				$(otlib_headers_dir)/OTCredential.hpp		\
				$(otlib_headers_dir)/OTCron.hpp			\
				$(otlib_headers_dir)/OTCronItem.hpp		\
				$(otlib_headers_dir)/OTCrypto.hpp         	\
				$(otlib_headers_dir)/OTData.hpp			\
				$(otlib_headers_dir)/OTDataCheck.hpp		\
				$(otlib_headers_dir)/OTDigitalCash.hpp		\
				$(otlib_headers_dir)/OTEnvelope.hpp		\
				$(otlib_headers_dir)/OTKeyring.hpp		\
				$(otlib_headers_dir)/OTglobal.h			\
				$(otlib_headers_dir)/OTIdentifier.hpp		\
				$(otlib_headers_dir)/OTInstrument.hpp		\
				$(otlib_headers_dir)/OTItem.hpp			\
				$(otlib_headers_dir)/OTLedger.hpp		\
				$(otlib_headers_dir)/OTLib.hpp			\
				$(otlib_headers_dir)/OTLibPriv.hpp		\
				$(otlib_headers_dir)/OTLog.hpp			\
				$(otlib_headers_dir)/OTMarket.hpp		\
				$(otlib_headers_dir)/OTMessage.hpp		\
				$(otlib_headers_dir)/OTMessageBuffer.hpp	\
				$(otlib_headers_dir)/OTMint.hpp			\
				$(otlib_headers_dir)/OTOffer.hpp		\
				$(otlib_headers_dir)/OTPassword.hpp		\
				$(otlib_headers_dir)/OTPaths.hpp		\
				$(otlib_headers_dir)/OTPayload.hpp		\
				$(otlib_headers_dir)/OTPayment.hpp		\
				$(otlib_headers_dir)/OTPaymentPlan.hpp		\
				$(otlib_headers_dir)/OTPseudonym.hpp		\
				$(otlib_headers_dir)/OTPurse.hpp		\
				$(otlib_headers_dir)/OTScript.hpp		\
				$(otlib_headers_dir)/OTScriptable.hpp		\
				$(otlib_headers_dir)/OTServerContract.hpp	\
				$(otlib_headers_dir)/OTSettings.hpp		\
				$(otlib_headers_dir)/OTSignature.hpp		\
				$(otlib_headers_dir)/OTSignedFile.hpp		\
				$(otlib_headers_dir)/OTSmartContract.hpp	\
				$(otlib_headers_dir)/OTStorage.hpp		\
				$(otlib_headers_dir)/OTString.hpp		\
				$(otlib_headers_dir)/OTStringXML.hpp		\
				$(otlib_headers_dir)/OTSymmetricKey.hpp		\
				$(otlib_headers_dir)/OTToken.hpp		\
				$(otlib_headers_dir)/OTTrackable.hpp		\
				$(otlib_headers_dir)/OTTrade.hpp		\
				$(otlib_headers_dir)/OTTransaction.hpp		\
				$(otlib_headers_dir)/OTTransactionType.hpp	\
				$(otlib_headers_dir)/OTWallet.hpp
####   Containers

containers_headers_dir	=	$(opentxs_include_dir)/containers

containers_headers 	=	$(containers_headers_dir)/containers.hpp	\
				$(containers_headers_dir)/containers_fixes.hpp	\
				$(containers_headers_dir)/copy_functors.hpp	\
				$(containers_headers_dir)/digraph.hpp		\
				$(containers_headers_dir)/digraph.tpp		\
				$(containers_headers_dir)/exceptions.hpp	\
				$(containers_headers_dir)/foursome.hpp		\
				$(containers_headers_dir)/foursome.tpp		\
				$(containers_headers_dir)/hash.hpp		\
				$(containers_headers_dir)/hash.tpp		\
				$(containers_headers_dir)/matrix.hpp		\
				$(containers_headers_dir)/matrix.tpp		\
				$(containers_headers_dir)/ntree.hpp		\
				$(containers_headers_dir)/ntree.tpp		\
				$(containers_headers_dir)/safe_iterator.hpp	\
				$(containers_headers_dir)/safe_iterator.tpp	\
				$(containers_headers_dir)/simple_ptr.hpp	\
				$(containers_headers_dir)/simple_ptr.tpp	\
				$(containers_headers_dir)/smart_ptr.hpp		\
				$(containers_headers_dir)/smart_ptr.tpp		\
				$(containers_headers_dir)/triple.hpp		\
				$(containers_headers_dir)/triple.tpp

####	Global headers for dist.

pkginclude_HEADERS          =   $(otlib_headers_ext)

## Extra rules to handle special ot_config.h

nodist_pkginclude_HEADERS	= 	$(top_builddir)/include/otlib/ot_config.h
DISTCLEANFILES			= 	$(top_builddir)/include/otlib/ot_config.h

## Extra to package containers headers

pkginclude_containersdir    =   $(pkgincludedir)/containers
pkginclude_containers_HEADERS   =   $(containers_headers)

## Extra to package simpleini headers

simpleini_headers_dir       =   $(top_srcdir)/include/simpleini

simpleini_headers           =   $(simpleini_headers_dir)/ConvertUTF.h \
                                $(simpleini_headers_dir)/SimpleIni.hpp

pkginclude_simpleinidir     =   $(pkgincludedir)/simpleini
pkginclude_simpleini_HEADERS    =   $(simpleini_headers)

## Extra to package chai4 headers

chai4hdrs_dir		=	$(top_srcdir)/include/chai4/chaiscript

noinst_HEADERS		=	$(chai4hdrs_dir)/license.txt				\
				$(chai4hdrs_dir)/chaiscript.hpp				\
				$(chai4hdrs_dir)/chaiscript_threading.hpp		\
				$(chai4hdrs_dir)/dispatchkit/bad_boxed_cast.hpp		\
				$(chai4hdrs_dir)/dispatchkit/bind_first.hpp		\
				$(chai4hdrs_dir)/dispatchkit/bootstrap.hpp		\
				$(chai4hdrs_dir)/dispatchkit/bootstrap_stl.hpp		\
				$(chai4hdrs_dir)/dispatchkit/boxed_cast_helper.hpp	\
				$(chai4hdrs_dir)/dispatchkit/boxed_cast.hpp		\
				$(chai4hdrs_dir)/dispatchkit/boxed_number.hpp		\
				$(chai4hdrs_dir)/dispatchkit/boxed_value.hpp		\
				$(chai4hdrs_dir)/dispatchkit/dispatchkit.hpp		\
				$(chai4hdrs_dir)/dispatchkit/dynamic_cast_conversion.hpp\
				$(chai4hdrs_dir)/dispatchkit/dynamic_object.hpp		\
				$(chai4hdrs_dir)/dispatchkit/exception_specification.hpp\
				$(chai4hdrs_dir)/dispatchkit/function_call_detail.hpp	\
				$(chai4hdrs_dir)/dispatchkit/function_call.hpp		\
				$(chai4hdrs_dir)/dispatchkit/handle_return.hpp		\
				$(chai4hdrs_dir)/dispatchkit/operators.hpp		\
				$(chai4hdrs_dir)/dispatchkit/proxy_constructors.hpp	\
				$(chai4hdrs_dir)/dispatchkit/proxy_functions_detail.hpp	\
				$(chai4hdrs_dir)/dispatchkit/proxy_functions.hpp	\
				$(chai4hdrs_dir)/dispatchkit/register_function.hpp	\
				$(chai4hdrs_dir)/dispatchkit/type_info.hpp		\
				$(chai4hdrs_dir)/language/chaiscript_algebraic.hpp	\
				$(chai4hdrs_dir)/language/chaiscript_common.hpp		\
				$(chai4hdrs_dir)/language/chaiscript_engine.hpp		\
				$(chai4hdrs_dir)/language/chaiscript_eval.hpp		\
				$(chai4hdrs_dir)/language/chaiscript_parser.hpp		\
				$(chai4hdrs_dir)/language/chaiscript_prelude_docs.hpp	\
				$(chai4hdrs_dir)/language/chaiscript_prelude.hpp	\
				$(chai4hdrs_dir)/utility/utility.hpp


## Extra to package chai5 headers

chai5hdrs_dir		=	$(top_srcdir)/include/chai5/chaiscript

noinst_HEADERS		+=	$(chai5hdrs_dir)/license.txt				\
				$(chai5hdrs_dir)/chaiscript_defines.hpp			\
				$(chai5hdrs_dir)/chaiscript.hpp				\
				$(chai5hdrs_dir)/chaiscript_stdlib.hpp			\
				$(chai5hdrs_dir)/chaiscript_threading.hpp		\
				$(chai5hdrs_dir)/dispatchkit/any.hpp			\
				$(chai5hdrs_dir)/dispatchkit/bad_boxed_cast.hpp		\
				$(chai5hdrs_dir)/dispatchkit/bind_first.hpp		\
				$(chai5hdrs_dir)/dispatchkit/bootstrap.hpp		\
				$(chai5hdrs_dir)/dispatchkit/bootstrap_stl.hpp		\
				$(chai5hdrs_dir)/dispatchkit/boxed_cast_helper.hpp	\
				$(chai5hdrs_dir)/dispatchkit/boxed_cast.hpp		\
				$(chai5hdrs_dir)/dispatchkit/boxed_number.hpp		\
				$(chai5hdrs_dir)/dispatchkit/boxed_value.hpp		\
				$(chai5hdrs_dir)/dispatchkit/dispatchkit.hpp		\
				$(chai5hdrs_dir)/dispatchkit/dynamic_cast_conversion.hpp\
				$(chai5hdrs_dir)/dispatchkit/dynamic_object.hpp		\
				$(chai5hdrs_dir)/dispatchkit/exception_specification.hpp\
				$(chai5hdrs_dir)/dispatchkit/function_call_detail.hpp	\
				$(chai5hdrs_dir)/dispatchkit/function_call.hpp		\
				$(chai5hdrs_dir)/dispatchkit/handle_return.hpp		\
				$(chai5hdrs_dir)/dispatchkit/operators.hpp		\
				$(chai5hdrs_dir)/dispatchkit/proxy_constructors.hpp	\
				$(chai5hdrs_dir)/dispatchkit/proxy_functions_detail.hpp	\
				$(chai5hdrs_dir)/dispatchkit/proxy_functions.hpp	\
				$(chai5hdrs_dir)/dispatchkit/register_function.hpp	\
				$(chai5hdrs_dir)/dispatchkit/type_info.hpp		\
				$(chai5hdrs_dir)/language/chaiscript_algebraic.hpp	\
				$(chai5hdrs_dir)/language/chaiscript_common.hpp		\
				$(chai5hdrs_dir)/language/chaiscript_engine.hpp		\
				$(chai5hdrs_dir)/language/chaiscript_eval.hpp		\
				$(chai5hdrs_dir)/language/chaiscript_parser.hpp		\
				$(chai5hdrs_dir)/language/chaiscript_prelude.chai	\
				$(chai5hdrs_dir)/language/chaiscript_prelude_docs.hpp	\
				$(chai5hdrs_dir)/utility/utility.hpp
