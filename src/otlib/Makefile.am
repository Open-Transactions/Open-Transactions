lib_LTLIBRARIES             =   libotlib.la

SUBDIRS                     =   bigint irrxml lucre otext otprotob

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
                                libotlib.la
                                        
######################## BUILD COMMANDS #############################

libotlib_la_SOURCES         =   $(otlib_sources) $(otlib_headers)

libotlib_la_CXXFLAGS        =   $(AM_CXXFLAGS) $(common_includes)

libotlib_la_DEPENDENCIES    =   bigint/libbigint.la \
                                irrxml/libirrxml.la \
                                lucre/liblucre.la \
                                otext/libotext.la \
                                otprotob/libotprotob.la

libotlib_la_LIBADD          =   $(libotlib_la_DEPENDENCIES) \
                                $(DEPS_LIBS)

libotlib_la_LDFLAGS         =   -g --no-undefined


#### KEYRING Options

if KEYRING_WINDOWS
libotlib_la_CXXFLAGS       +=   -DOT_KEYRING_WINDOWS
endif

if KEYRING_MAC
libotlib_la_CXXFLAGS       +=   -DOT_KEYRING_MAC
endif

if KEYRING_GNOME
libotlib_la_CXXFLAGS       +=   -DOT_KEYRING_GNOME
endif

if KEYRING_KWALLET
libotlib_la_CXXFLAGS       +=   -DOT_KEYRING_KWALLET
endif

######################## DEPENDENCIES ###############################


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

otlib_headers               =   $(otlib_incdir)/constants.h \
                                $(otlib_incdir)/fast_mutex.h \
                                $(otlib_incdir)/WinsockWrapper.h \
                                $(otlib_incdir)/tinythread.h \
                                $(otlib_incdir)/Timer.h \
                                $(otlib_headers_ext)

otlib_headers_ext           =   $(otlib_incdir)/anyoption.hpp \
                                $(otlib_incdir)/Bitcoin.pb.h \
                                $(otlib_incdir)/ExportWrapper.h \
                                $(otlib_incdir)/Generics.pb.h \
                                $(otlib_incdir)/Markets.pb.h \
                                $(otlib_incdir)/MemoryWrapper.hpp \
                                $(otlib_incdir)/Moneychanger.pb.h \
                                $(otlib_incdir)/OTAccount.hpp \
                                $(otlib_incdir)/OTAgreement.hpp \
                                $(otlib_incdir)/OTASCIIArmor.hpp \
                                $(otlib_incdir)/OTAssert.hpp \
                                $(otlib_incdir)/OTAssetContract.hpp \
                                $(otlib_incdir)/OTAsymmetricKey.hpp \
                                $(otlib_incdir)/OTBasket.hpp \
                                $(otlib_incdir)/OTBylaw.hpp \
                                $(otlib_incdir)/OTCachedKey.hpp \
                                $(otlib_incdir)/OTCheque.hpp \
                                $(otlib_incdir)/OTContract.hpp \
                                $(otlib_incdir)/OTCredential.hpp \
                                $(otlib_incdir)/OTCron.hpp \
                                $(otlib_incdir)/OTCronItem.hpp \
                                $(otlib_incdir)/OTCrypto.hpp \
                                $(otlib_incdir)/OTData.hpp \
                                $(otlib_incdir)/OTDataCheck.hpp \
                                $(otlib_incdir)/OTDigitalCash.hpp \
                                $(otlib_incdir)/OTEnvelope.hpp \
                                $(otlib_incdir)/OTglobal.h \
                                $(otlib_incdir)/OTIdentifier.hpp \
                                $(otlib_incdir)/OTInstrument.hpp \
                                $(otlib_incdir)/OTItem.hpp \
                                $(otlib_incdir)/OTKeyring.hpp \
                                $(otlib_incdir)/OTLedger.hpp \
                                $(otlib_incdir)/OTLib.hpp \
                                $(otlib_incdir)/OTLibPriv.hpp \
                                $(otlib_incdir)/OTLog.hpp \
                                $(otlib_incdir)/OTMarket.hpp \
                                $(otlib_incdir)/OTMessage.hpp \
                                $(otlib_incdir)/OTMessageBuffer.hpp \
                                $(otlib_incdir)/OTMint.hpp \
                                $(otlib_incdir)/OTOffer.hpp \
                                $(otlib_incdir)/OTPassword.hpp \
                                $(otlib_incdir)/OTPaths.hpp \
                                $(otlib_incdir)/OTPayload.hpp \
                                $(otlib_incdir)/OTPayment.hpp \
                                $(otlib_incdir)/OTPaymentPlan.hpp \
                                $(otlib_incdir)/OTPseudonym.hpp \
                                $(otlib_incdir)/OTPurse.hpp \
                                $(otlib_incdir)/OTScript.hpp \
                                $(otlib_incdir)/OTScriptable.hpp \
                                $(otlib_incdir)/OTServerContract.hpp \
                                $(otlib_incdir)/OTSettings.hpp \
                                $(otlib_incdir)/OTSignature.hpp \
                                $(otlib_incdir)/OTSignedFile.hpp \
                                $(otlib_incdir)/OTSmartContract.hpp \
                                $(otlib_incdir)/OTStorage.hpp \
                                $(otlib_incdir)/OTString.hpp \
                                $(otlib_incdir)/OTStringXML.hpp \
                                $(otlib_incdir)/OTSymmetricKey.hpp \
                                $(otlib_incdir)/OTToken.hpp \
                                $(otlib_incdir)/OTTrackable.hpp \
                                $(otlib_incdir)/OTTrade.hpp \
                                $(otlib_incdir)/OTTransaction.hpp \
                                $(otlib_incdir)/OTTransactionType.hpp \
                                $(otlib_incdir)/OTWallet.hpp \
                                $(otlib_incdir)/stacktrace.h \
                                $(otlib_incdir)/stdafx.h \
                                $(otlib_incdir)/stdafx.hpp

####   Containers

containers_incdir           =   $(opentxs_incdir)/containers

containers_headers          =   $(containers_incdir)/containers.hpp \
                                $(containers_incdir)/containers_fixes.hpp \
                                $(containers_incdir)/copy_functors.hpp \
                                $(containers_incdir)/digraph.hpp \
                                $(containers_incdir)/digraph.tpp \
                                $(containers_incdir)/exceptions.hpp \
                                $(containers_incdir)/foursome.hpp \
                                $(containers_incdir)/foursome.tpp \
                                $(containers_incdir)/hash.hpp \
                                $(containers_incdir)/hash.tpp \
                                $(containers_incdir)/matrix.hpp \
                                $(containers_incdir)/matrix.tpp \
                                $(containers_incdir)/ntree.hpp \
                                $(containers_incdir)/ntree.tpp \
                                $(containers_incdir)/safe_iterator.hpp \
                                $(containers_incdir)/safe_iterator.tpp \
                                $(containers_incdir)/simple_ptr.hpp \
                                $(containers_incdir)/simple_ptr.tpp \
                                $(containers_incdir)/smart_ptr.hpp \
                                $(containers_incdir)/smart_ptr.tpp \
                                $(containers_incdir)/triple.hpp \
                                $(containers_incdir)/triple.tpp

####    Global Headers for dist.

pkginclude_HEADERS          =   $(otlib_headers_ext)

## Extra to package containers headers

pkginclude_containersdir    =   $(pkgincludedir)/containers
pkginclude_containers_HEADERS   =   $(containers_headers)

## Extra to package simpleini headers

simpleini_headers_dir       =   $(top_srcdir)/include/simpleini

simpleini_headers           =   $(simpleini_headers_dir)/ConvertUTF.h \
                                $(simpleini_headers_dir)/SimpleIni.hpp
    
pkginclude_simpleinidir     =   $(pkgincludedir)/simpleini
pkginclude_simpleini_HEADERS    =   $(simpleini_headers)
