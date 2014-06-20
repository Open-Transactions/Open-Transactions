// OTLIB
// Open Transactions Pre-Compiled Headers File

#pragma once

// Include the C one.
#include "stdafx.h"

#ifdef OT_USE_CXX11
#undef OT_USE_CXX11
#endif

#if defined(_MSC_VER)
#define OT_USE_CXX11
#elif (!defined(OPENTXS_NO_CXX11) && (__cplusplus >= 201103L))
#define OT_USE_CXX11
#endif

// ------------------------------------
#ifndef OT_USE_SCRIPT_CHAI
#define OT_USE_SCRIPT_CHAI

#ifdef OPENTXS_CHAISCRIPT_4
#else

#ifndef OPENTXS_CHAISCRIPT_5
#define OPENTXS_CHAISCRIPT_5
#endif

#endif

#endif
// ------------------------------------
#if defined(ANDROID) || defined(OT_KEYRING_IOS)

// DON'T use ChaiScript on mobile devices
#undef OT_USE_SCRIPT_CHAI

#ifdef OPENTXS_CHAISCRIPT_4
#undef OPENTXS_CHAISCRIPT_4
#endif

#ifdef OPENTXS_CHAISCRIPT_5
#undef OPENTXS_CHAISCRIPT_5
#endif

#endif
// ------------------------------------

#ifdef OT_USE_CHAI_STDLIB
#undef OT_USE_CHAI_STDLIB
#endif

#ifdef OPENTXS_CHAISCRIPT_5
#define OT_USE_CHAI_STDLIB
#endif

// ------------------------------------

#ifndef OT_CRYPTO_USING_OPENSSL
#define OT_CRYPTO_USING_OPENSSL 1
#endif

#ifndef OT_CASH_USING_LUCRE
#define OT_CASH_USING_LUCRE 1
#endif

// ------------------------------------

// for mac, this enables deprecated functions. (aka, for pthread)
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif

// define fstream while _XOPEN_SOURCE isn't defined.
//#include <fstream>

#if defined(__APPLE__) && defined(OPENTXS_XOPEN_SOURCE)
#define _XOPEN_SOURCE 500
#endif


#ifdef _WIN32
#ifndef NO_OT_PCH

//#include "OTAccount.hpp"
//#include "OTAcctFunctor.hpp"
//#include "OTAcctList.hpp"
//#include "OTAgent.hpp"
//#include "OTAgreement.hpp"
//#include "OTAmount.hpp"
//#include "OTASCIIArmor.hpp"
//#include "OTAssert.hpp"
//#include "OTAssetContract.hpp"
//#include "OTAsymmetricKey.hpp"
//#include "OTAsymmetricKey_OpenSSLPrivdp.hpp"
//#include "OTAsymmetricKeyOpenSSL.hpp"
//#include "OTBasket.hpp"
//#include "OTBasketItem.hpp"
//#include "OTBylaw.hpp"
//#include "OTCachedKey.hpp"
//#include "OTCallback.hpp"
//#include "OTCaller.hpp"
//#include "OTCheque.hpp"
//#include "OTClause.hpp"
//#include "OTCleanup.hpp"
//#include "OTCommon.hpp"
//#include "OTContract.hpp"
//#include "OTCredential.hpp"
//#include "OTCron.hpp"
//#include "OTCronItem.hpp"
//#include "OTCrypto.hpp"         
//#include "OTDataCheck.hpp"
//#include "OTDataFolder.hpp"
//#include "OTData.hpp"
//#include "OTDigitalCash.hpp"
//#include "OTEnvelope.hpp"
//#include "OTFolders.hpp"
//#include "OTIdentifier.hpp"
//#include "OTInstrument.hpp"
//#include "OTItem.hpp"
//#include "OTKeyCredential.hpp"
//#include "OTKeypair.hpp"
//#include "OTKeyring.hpp"
//#include "OTLedger.hpp"
//#include "OTLib.hpp"
//#include "OTLibPriv.hpp"
//#include "OTLog.hpp"
//#include "OTLowLevelKeyData.hpp"
//#include "OTMarket.hpp"
//#include "OTMasterkey.hpp"
//#include "OTMessageBuffer.hpp"
//#include "OTMessage.hpp"
//#include "OTMessageOutBuffer.hpp"
//#include "OTMint.hpp"
//#include "OTMintLucre.hpp"
//#include "OTNumList.hpp"
//#include "OTNymOrSymmetricKey.hpp"
//#include "OTOffer.hpp"
//#include "OTPartyAccount.hpp"
//#include "OTParty.hpp"
//#include "OTPasswordData.hpp"
//#include "OTPassword.hpp"
//#include "OTPaths.hpp"
//#include "OTPayload.hpp"
//#include "OTPayment.hpp"
//#include "OTPaymentPlan.hpp"
//#include "OTPseudonym.hpp"
//#include "OTPurse.hpp"
//#include "OTScriptable.hpp"
//#include "OTScriptChai.hpp"
//#include "OTScript.hpp"
//#include "OTServerContract.hpp"
//#include "OTSettings.hpp"
//#include "OTStoragePB.hpp"
//#include "OTSignature.hpp"
//#include "OTSignatureMetadata.hpp"
//#include "OTSignedFile.hpp"
//#include "OTSmartContract.hpp"
//#include "OTStash.hpp"
//#include "OTStashItem.hpp"
//#include "OTSocket.hpp"
//#include "OTStorage.hpp"
//#include "OTString.hpp"
//#include "OTStringXML.hpp"
//#include "OTSubcredential.hpp"
//#include "OTSubkey.hpp"
//#include "OTSymmetricKey.hpp"
//#include "OTToken.hpp"
//#include "OTTokenLucre.hpp"
//#include "OTTrackable.hpp"
//#include "OTTrade.hpp"
//#include "OTTransaction.hpp"
//#include "OTTransactionType.hpp"
//#include "OTVariable.hpp"
//#include "OTWallet.hpp"

#else
#undef NO_OT_PCH
#endif
#endif
