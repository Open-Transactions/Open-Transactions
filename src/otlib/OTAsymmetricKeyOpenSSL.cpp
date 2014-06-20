/************************************************************
 *    
 *  OTAsymmetricKeyOpenSSL.cpp
 *  
 */

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA1
 
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net
 *
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT (PGP Key in license file):
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- otlib.........A class library.......LICENSE:...LAGPLv3
 *   -- otapi.........A client API..........LICENSE:...LAGPLv3
 *   -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
 *   -- otserver......Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (bitcointrader4@gmail.com).
 *  The open-source community has since actively contributed.
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT API, then you
 *   don't have to open-source your code--only your changes to
 *   Open-Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open-Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open-Transactions terms remain respected, with regard to
 *   the Open-Transactions code itself.
 *
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   See Lucre on Github:  https://github.com/benlaurie/lucre
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.
 
 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.9 (Darwin)
 
 iQIcBAEBAgAGBQJRSsfJAAoJEAMIAO35UbuOQT8P/RJbka8etf7wbxdHQNAY+2cC
 vDf8J3X8VI+pwMqv6wgTVy17venMZJa4I4ikXD/MRyWV1XbTG0mBXk/7AZk7Rexk
 KTvL/U1kWiez6+8XXLye+k2JNM6v7eej8xMrqEcO0ZArh/DsLoIn1y8p8qjBI7+m
 aE7lhstDiD0z8mwRRLKFLN2IH5rAFaZZUvj5ERJaoYUKdn4c+RcQVei2YOl4T0FU
 LWND3YLoH8naqJXkaOKEN4UfJINCwxhe5Ke9wyfLWLUO7NamRkWD2T7CJ0xocnD1
 sjAzlVGNgaFDRflfIF4QhBx1Ddl6wwhJfw+d08bjqblSq8aXDkmFA7HeunSFKkdn
 oIEOEgyj+veuOMRJC5pnBJ9vV+7qRdDKQWaCKotynt4sWJDGQ9kWGWm74SsNaduN
 TPMyr9kNmGsfR69Q2Zq/FLcLX/j8ESxU+HYUB4vaARw2xEOu2xwDDv6jt0j3Vqsg
 x7rWv4S/Eh18FDNDkVRChiNoOIilLYLL6c38uMf1pnItBuxP3uhgY6COm59kVaRh
 nyGTYCDYD2TK+fI9o89F1297uDCwEJ62U0Q7iTDp5QuXCoxkPfv8/kX6lS6T3y9G
 M9mqIoLbIQ1EDntFv7/t6fUTS2+46uCrdZWbQ5RjYXdrzjij02nDmJAm2BngnZvd
 kamH0Y/n11lCvo1oQxM+
 =uSzz
 -----END PGP SIGNATURE-----
 **************************************************************/

#include "stdafx.hpp"

#include "OTAsymmetricKeyOpenSSL.hpp"

#include "OTASCIIArmor.hpp"
#include "OTLog.hpp"
#include "OTPassword.hpp"
#include "OTPasswordData.hpp"
#include "OTPayload.hpp"

#if defined (OT_CRYPTO_USING_OPENSSL)
#include "OTAsymmetricKey_OpenSSLPrivdp.hpp"
#include "OpenSSL_BIO.hpp"
#endif


#if defined (OT_CRYPTO_USING_OPENSSL)

OTAsymmetricKey_OpenSSL::OTAsymmetricKey_OpenSSL() : OTAsymmetricKey(), dp(new OTAsymmetricKey_OpenSSLPrivdp())
{
    dp->backlink = this;

    dp->m_pX509  = NULL;
    dp->m_pKey   = NULL;
}


OTAsymmetricKey_OpenSSL::~OTAsymmetricKey_OpenSSL()
{
    Release_AsymmetricKey_OpenSSL();
    // -------------------------
    ReleaseKeyLowLevel_Hook();
    // -------------------------
    if (NULL != dp->m_pX509)  // Todo: figure out if I should put a copy of this into ReleaseKeyLowLevel_Hook as we are with m_pKey.
        X509_free(dp->m_pX509); // FYI: the reason it's not there already is because the original need was for wiping m_pKey when a private key timed out.
    dp->m_pX509 = NULL;         // ReleaseKeyLowLevel is used all over OTAsymmetricKey.cpp for the purpose of wiping that private key. The same need didn't exist with the x509 so it was never coded that way. As long as it's cleaned up here in the destructor, seems good enough?
    //-------------------------
    // YOU MIGHT ASK... Why is m_pKey cleaned up here in the destructor, and ALSO in ReleaseKeyLowLevel_Hook ?
    // The answer is because if we call ReleaseKeyLowLevel_Hook from OTAsymmetricKey's destructor (down that chain)
    // then it will fail at runtime, since it is a pure virtual method. Since we still want the ABILITY to use ReleaseKeyLowLevel_Hook
    // (For cases where the destructor is not being used) and since we still want it to ALSO work when destructing, the
    // easiest/quickest/simplest way is to put the code into OTAsymmetricKey_OpenSSL's destructor directly, as well
    // as OTAsymmetricKey_OpenSSL's override of ReleaseKeyLowLevel_Hook. Then go into OTAsymmetricKey's destructor and
    // make sure the full call path through there doesn't involve any virtual functions.
}


//virtual
void OTAsymmetricKey_OpenSSL::Release()
{
    Release_AsymmetricKey_OpenSSL(); // My own cleanup is performed here.
    
    // Next give the base class a chance to do the same...
	ot_super::Release(); // since I've overridden the base class, I call it now...
}


void OTAsymmetricKey_OpenSSL::Release_AsymmetricKey_OpenSSL()
{
    // Release any dynamically allocated members here. (Normally.)
}


void OTAsymmetricKey_OpenSSL::ReleaseKeyLowLevel_Hook()
{
    // Release the instantiated OpenSSL key (unsafe to store in this form.)
    //
    if (NULL != dp->m_pKey)
        EVP_PKEY_free (dp->m_pKey);
    dp->m_pKey = NULL;
}


// Load the private key from a .pem formatted cert string
//
bool OTAsymmetricKey_OpenSSL::LoadPrivateKeyFromCertString(const OTString & strCert, // Contains certificate and private key.
                                                           bool bEscaped/*=true*/, // "escaped" means pre-pended with "- " as in:   - -----BEGIN CER....
                                                           const OTString * pstrReason/*=NULL*/,  // This reason is what displays on the passphrase dialog.
                                                           OTPassword     * pImportPassword/*=NULL*/) // Used when importing an exported Nym into a wallet.
{   
	Release();
	// --------------------------------------------------------------------	
	m_bIsPublicKey	= false;
	m_bIsPrivateKey	= true;
	// --------------------------------------------------------------------
	//
	if (!strCert.Exists())
	{
		OTLog::vError("%s: Error: Cert input is nonexistent!\n", __FUNCTION__);
		return false;
	}
	// --------------------------------------------------------------------
    // Read private key
    //
	OTString strWithBookends;
	OTLog::vOutput(3,  "%s: FYI, Reading private key from x509 stored in bookended string...\n", __FUNCTION__); 

	if (bEscaped)
	{
		OTASCIIArmor theArmor;
        
		// I only have a CERTIFICATE 'if' here, not a PUBLIC KEY 'if'.
		// That's because this function is called "LoadPublicKeyFrom*CERT*String"
		// If you want to load a public key from a public key string, then call the
		// other function that does that.
		if (theArmor.LoadFromString(const_cast<OTString &>(strCert), true, // passing bEscaped in as true explicitly here.
                                    "-----BEGIN ENCRYPTED PRIVATE")) // It will start loading from THIS substring...
			strWithBookends.Format("-----BEGIN ENCRYPTED PRIVATE KEY-----\n%s-----END ENCRYPTED PRIVATE KEY-----\n", 
								   theArmor.Get());
		else 
		{
			OTLog::vError("%s: Error extracting ASCII-Armored text from Cert String.\n", __FUNCTION__);
			return false;
		}
	}
	else // It's not escaped already, so no need to remove the escaping, in this case.
    {
		strWithBookends = strCert;
	}
    // *****************************************************
    
	// Create a new memory buffer on the OpenSSL side.
    //
//	OpenSSL_BIO bio = BIO_new(BIO_s_mem());
//  OpenSSL_BIO bio = BIO_new_mem_buf(static_cast<void*>(const_cast<char*>(strWithBookends.Get())), strWithBookends.GetLength() /*+1*/); 
    OpenSSL_BIO bio = BIO_new_mem_buf(static_cast<void*>(const_cast<char*>(strWithBookends.Get())), -1); 
	OT_ASSERT_MSG(NULL != bio, "OTAsymmetricKey_OpenSSL::LoadPrivateKeyFromCertString: Assert: NULL != bio \n");


	// --------------------------------------------------------------------
	{
		// TODO security: Need to replace PEM_read_bio_PrivateKey().
		/*
         The old PrivateKey write routines are retained for compatibility.
		 New applications should write private keys using the PEM_write_bio_PKCS8PrivateKey() or PEM_write_PKCS8PrivateKey() 
		 routines because they are more secure (they use an iteration count of 2048 whereas the traditional routines use a
		 count of 1) unless compatibility with older versions of OpenSSL is important.
		 NOTE: The PrivateKey read routines can be used in all applications because they handle all formats transparently.
		 */
        OTPasswordData thePWData((NULL == pstrReason) ? 
                                 (NULL == pImportPassword ? "Enter the master passphrase. (LoadPrivateKeyFromCertString)" : "Enter the passphrase for this exported nym.") :
                                 pstrReason->Get());

        EVP_PKEY * pkey = NULL;
        
        if (NULL == pImportPassword) // pImportPassword is NULL? Do it normally then.
        {
//          OTLog::vOutput(0, "%s: READING using WALLET password.\n", __FUNCTION__);
            pkey = PEM_read_bio_PrivateKey( bio, NULL, OTAsymmetricKey::GetPasswordCallback(), &thePWData );
        }
        else // Otherwise, use pImportPassword instead of the normal OTCachedKey system.
        {
//          OTLog::vOutput(0, "%s: READING using EXPORT password.\n", __FUNCTION__);
            pkey = PEM_read_bio_PrivateKey( bio, NULL, 0, const_cast<void*>(reinterpret_cast<const void*>(pImportPassword->getPassword())) );
        }
        // ------------------------------------------------------
//      if (strWithBookends.GetLength() > 0)
//          OPENSSL_cleanse(bio, strWithBookends.GetLength());
		// ------------------------------------------------------
		
		if (NULL == pkey) 
		{ 
			OTLog::vError("%s: (pImportPassword size: %d) Error reading private key from string.\n\n",
						  __FUNCTION__,
                          NULL == pImportPassword ? 0 : pImportPassword->getPasswordSize());
//			OTLog::vError("%s: (pImportPassword is %s, size: %d) Error reading private key from string:\n%s\n\n",
//						  __FUNCTION__, NULL == pImportPassword ? "NULL" : pImportPassword->getPassword(),
//                          NULL == pImportPassword ? 0 : pImportPassword->getPasswordSize(),
//                          strWithBookends.Get()
//                          );
			return false;
		}
		else 
		{
            // Note: no need to start m_timer here since SetKeyAsCopyOf already calls ArmorPrivateKey, which does that.
            //
            this->dp->SetKeyAsCopyOf(*pkey, true, &thePWData, pImportPassword); // bIsPrivateKey=false by default, but true here.
            EVP_PKEY_free(pkey);
            pkey = NULL;
			OTLog::vOutput(3, "%s: Successfully loaded private key, FYI.\n", __FUNCTION__);
			return true;
		}
	}
}


// Load the public key from a x509 stored in a bookended string
// If the string is escaped (- ----BEGIN is prefixed with dash space: "- ") then make
// sure to pass true.  (Keys that appear inside contracts are escaped after signing.)
// This function will remove the escapes.
//
bool OTAsymmetricKey_OpenSSL::LoadPublicKeyFromCertString(const OTString   & strCert, bool bEscaped/*=true*/,
                                                          const OTString   * pstrReason/*=NULL*/,
                                                                OTPassword * pImportPassword/*=NULL*/)
{
	Release();
    // ------------------------------
	m_bIsPublicKey	= true;
	m_bIsPrivateKey	= false;
	
	bool bReturnValue = false;
    // ------------------------------
	// Read public key
	OTLog::vOutput(3,  "%s: Reading public key from x509 stored in bookended string...\n", __FUNCTION__);

	OTString   strWithBookends;
	
	if (bEscaped)
	{
		OTASCIIArmor	theArmor;

		// I only have a CERTIFICATE 'if' here, not a PUBLIC KEY 'if'.
		// That's because this function is called "LoadPublicKeyFrom*CERT*String"
		// If you want to load a public key from a public key string, then call the
		// other function that does that.
        //
		if (theArmor.LoadFromString(const_cast<OTString &>(strCert), true, // passing bEscaped in as true explicitly here.
                                    "-----BEGIN CERTIFICATE")) // Overrides "-----BEGIN" 
			strWithBookends.Format("-----BEGIN CERTIFICATE-----\n%s-----END CERTIFICATE-----\n", 
								   theArmor.Get());
		else 
		{
			OTLog::vError("%s: Error extracting ASCII-Armored text from Cert String.\n", __FUNCTION__);
			return false;
		}
	}
	else // It's not escaped already, so no need to remove the escaping, in this case.
    {
		strWithBookends = strCert;
	}
    // -------------------------------------------------
	// took out the +1 on the length since null terminater only
	// needed in string form, not binary form as OpenSSL treats it.
    //
	OpenSSL_BIO keyBio = BIO_new_mem_buf(static_cast<void*>(const_cast<char*>(strWithBookends.Get())), -1); 
//	OpenSSL_BIO keyBio = BIO_new_mem_buf(static_cast<void*>(const_cast<char*>(strWithBookends.Get())), strWithBookends.GetLength() /*+1*/); 
//	OpenSSL_BIO keyBio = BIO_new_mem_buf((void*)strCert.Get(), strCert.GetLength() /*+1*/);
	OT_ASSERT(NULL != keyBio);
	// --------------------------------------------------
    OTPasswordData thePWData(NULL == pImportPassword ? "Enter your wallet master passphrase. (LoadPublicKeyFromCertString)" :
                             // pImportPassword exists:
                             (NULL == pstrReason ? "Enter the passphrase for your exported Nym. (LoadPublicKeyFromCertString)" : pstrReason->Get()));
	// --------------------------------------------------
	X509 * x509 = NULL;
    
    if (NULL == pImportPassword)
        x509 = PEM_read_bio_X509(keyBio, NULL, OTAsymmetricKey::GetPasswordCallback(), &thePWData);
    else
        x509 = PEM_read_bio_X509(keyBio, NULL, 0, const_cast<void*>(reinterpret_cast<const void*>(pImportPassword->getPassword())));
		
	// TODO security: At some point need to switch to using X509_AUX functions.
	// The current x509 functions will read a trust certificate but discard the trust structure.
	// The X509_AUX functions will process the trust structure.
    // UPDATE: Possibly the trust structure sucks. Need to consult experts. (CA system is a farce.)
    //
	if (NULL != x509)
	{
        EVP_PKEY * pkey = X509_get_pubkey(x509);
        // ------------------------
		if (pkey == NULL)
		{
			OTLog::vError("%s: Error reading public key from x509.\n", __FUNCTION__);
		}
		else
		{
            this->dp->SetKeyAsCopyOf(*pkey,      false, // bIsPrivateKey=false. PUBLIC KEY.
                                 &thePWData, pImportPassword); // pImportPassword is sometimes NULL here.
            
            EVP_PKEY_free(pkey);
            pkey = NULL;
			OTLog::vOutput(3, "%s: Successfully extracted a public key from an x509 certificate.\n", __FUNCTION__); 
			bReturnValue = true; 
		}
	}
	else
	{ 
		OTLog::vError("%s: Error reading x509 out of certificate.\n", __FUNCTION__); 
	}
    // ---------------------------------------------------------
    // For now we save the x509, and free it in the destructor, since we may
    // need it in the meantime, to convert the Nym to the new master key and
    // re-save. (Don't want to have to load the x509 AGAIN just to re-save it...)
    //
    if (bReturnValue)
    {
        dp->SetX509(x509);
    }
    else
    {
        if (NULL != x509) 
            X509_free(x509);
        x509 = NULL;
        dp->SetX509(NULL);
    }

	return bReturnValue;
}


// Used when importing / exporting Nym to/from the wallet.
//
bool OTAsymmetricKey_OpenSSL::ReEncryptPrivateKey(OTPassword & theExportPassword, bool bImporting)
{
    OT_ASSERT(m_p_ascKey != NULL);
    OT_ASSERT(IsPrivate());
    // ------------------------------
    bool bReturnVal = false;
    // ------------------------------
    const EVP_CIPHER * pCipher = EVP_des_ede3_cbc(); // todo should this algorithm be hardcoded?
    // ------------------------------
	EVP_PKEY * pClearKey = NULL;
	OTPayload theData;  // after base64-decoding the ascii-armored string, the (encrypted) binary will be stored here.
	// --------------------------------------
	// This line base64 decodes the ascii-armored string into binary object theData...
    //
	m_p_ascKey->GetData(theData); // theData now contains binary data, the encrypted private key itself, no longer in text-armoring.
    
    if (theData.GetSize() > 0)
    {
        // --------------------------------------
        // Copy the encrypted binary private key data into an OpenSSL memory BIO...
        //
        OpenSSL_BIO keyBio = BIO_new_mem_buf(static_cast<char*>(const_cast<void*>(theData.GetPayloadPointer())),
                                       theData.GetSize()); // theData will zeroMemory upon destruction.
        OT_ASSERT_MSG(NULL != keyBio, "OTAsymmetricKey_OpenSSL::ReEncryptPrivateKey: Assert: NULL != keyBio \n");
        // --------------------------------------
        // Here's thePWData we use if we didn't have anything else:
        //
        OTPasswordData thePWData(bImporting ? "(Importing) Enter the exported Nym's passphrase." : "(Exporting) Enter your wallet's master passphrase.");
        
        // --------------------------------------
        // If we're importing, that means we're currently stored as an EXPORTED NYM (i.e. with its own
        // password, independent of the wallet.) So we use theExportedPassword.
        //
        if (bImporting)
        {
//          OTLog::vOutput(0, "RE-ENCRYPT PRIVATE KEY -- READING using special EXPORT password: %s\n", theExportPassword.getPassword());
            pClearKey = PEM_read_bio_PrivateKey( keyBio, NULL, 0, const_cast<void*>(reinterpret_cast<const void*>(theExportPassword.getPassword())) );
        }
        // --------------------------------------
        // Else if we're exporting, that means we're currently stored in the wallet (i.e. using the wallet's
        // cached master key.) So we use the normal password callback.
        //
        else
        {
//          OTLog::vOutput(0, "RE-ENCRYPT PRIVATE KEY -- READING using WALLET password.\n");
            pClearKey = PEM_read_bio_PrivateKey( keyBio, NULL, OTAsymmetricKey::GetPasswordCallback(), &thePWData );
        }
        // --------------------------------------
        if (NULL != pClearKey)
        {
//          OTLog::vOutput(4, "%s: Success reading private key from ASCII-armored data:\n\n%s\n\n",
//                         __FUNCTION__, m_p_ascKey->Get());
            OTLog::vOutput(4, "%s: Success reading private key from ASCII-armored data.\n",
                           __FUNCTION__);
            // --------------------------------------
            // Okay, we have loaded up the private key, now let's save it back to m_p_ascKey
            // using the new passphrase.
            //
            OpenSSL_BIO bmem = BIO_new(BIO_s_mem());
            OT_ASSERT(NULL != bmem);
            
            int64_t lSize = 0;
            // ----------------------------------------
            // write a private key to that buffer, from pClearKey
            //            
            int32_t nWriteBio = 0;
            
            // If we're importing, that means we just loaded up the (previously) exported Nym
            // using theExportedPassphrase, so now we need to save it back again using the
            // normal password callback (for importing it to the wallet.)
            //
            if (bImporting)
            {
//              OTLog::vOutput(0, "RE-ENCRYPT PRIVATE KEY -- WRITING using WALLET password.\n");
                nWriteBio = PEM_write_bio_PrivateKey(bmem, pClearKey, pCipher,
                                                     NULL, 0, OTAsymmetricKey::GetPasswordCallback(), &thePWData);
            }
            // ----------------------------------------
            // Else if we're exporting, that means we just loaded up the Nym from the wallet
            // using the normal password callback, and now we need to save it back again using
            // theExportedPassphrase (for exporting it outside of the wallet.)
            //
            else
            {
//              OTLog::vOutput(0, "RE-ENCRYPT PRIVATE KEY -- WRITING using special EXPORT password: %s  Size: %d\n", theExportPassword.getPassword(),
//                             theExportPassword.getPasswordSize());
                nWriteBio = PEM_write_bio_PrivateKey(bmem, pClearKey, pCipher,
                                                     NULL, 0, 0, const_cast<void*>(reinterpret_cast<const void*>(theExportPassword.getPassword())));
            }
            // ----------------------------------------
            EVP_PKEY_free(pClearKey);
            // ----------------------------------------
            if (0 == nWriteBio)
                OTLog::vError("%s: Failed writing EVP_PKEY to memory buffer.\n", __FUNCTION__);
            else
            {
                // --------------------
                OTLog::vOutput(5, "%s: Success writing EVP_PKEY to memory buffer.\n", __FUNCTION__);
                
                OTPayload theNewData;
                char * pChar = NULL;
                
                // After the below call, pChar will point to the memory buffer where the private key supposedly is,
                // and lSize will contain the size of that memory.
                //
                lSize = BIO_get_mem_data(bmem, &pChar);
                uint32_t  nSize = static_cast<uint32_t>(lSize);
                
                if (nSize > 0)
                {
                    // Set the buffer size in our own memory.
                    theNewData.SetPayloadSize(nSize);
                    
//                  void * pv =
                    OTPassword::safe_memcpy((static_cast<char*>(const_cast<void*>(theNewData.GetPayloadPointer()))), // destination
                                            theNewData.GetSize(),    // size of destination buffer.
                                            pChar,                // source
                                            nSize);               // length of source.
                                         // bool bZeroSource=false); // if true, sets the source buffer to zero after copying is done.
                    // ------------------------------------------------
                    // This base64 encodes the private key data, which
                    // is already encrypted to its passphase as well.
                    //
                    m_p_ascKey->SetData(theNewData); // <======== Success!
                    bReturnVal = true;
                }
                else
                    OTLog::vError("%s: Failed copying private key into memory.\n", __FUNCTION__);
            } // (nWriteBio != 0)
            // --------------------------------------
        }
        else
            OTLog::vError("%s: Failed loading actual private key from BIO containing ASCII-armored data:\n\n%s\n\n",
                          __FUNCTION__, m_p_ascKey->Get());
    }
    else
        OTLog::vError("%s: Failed reading private key from ASCII-armored data.\n\n",
                      __FUNCTION__);
//      OTLog::vError("%s: Failed reading private key from ASCII-armored data:\n\n%s\n\n",
//                    __FUNCTION__, m_p_ascKey->Get());
    // --------------------------------------
    return bReturnVal;
}


//virtual
bool OTAsymmetricKey_OpenSSL::SaveCertToString(OTString & strOutput, const OTString * pstrReason/*=NULL*/, OTPassword * pImportPassword/*=NULL*/)
{
    X509 * x509 = dp->GetX509();
    
    if (NULL == x509)
    {
        OTLog::vError("%s: Error: Unexpected NULL x509. (Returning false.)\n", __FUNCTION__);
        return false;
    }
    // ---------------------------------------    
    OpenSSL_BIO bio_out_x509 = BIO_new(BIO_s_mem()); // we now have auto-cleanup
    // ---------------------------------------
	PEM_write_bio_X509(bio_out_x509, x509);
    // ---------------------------------------
    bool bSuccess = false;
    
	uint8_t buffer_x509[8192] = ""; // todo hardcoded
	OTString      strx509;
	int32_t           len = 0;
	
    // todo hardcoded 4080 (see array above.)
    //
	if (0 < (len = BIO_read(bio_out_x509, buffer_x509, 8100))) // returns number of bytes successfully read.
	{
		buffer_x509[len] = '\0';
		strx509.Set((const char*)buffer_x509); // todo cast

		EVP_PKEY  * pPublicKey = X509_get_pubkey(x509); 
		if (NULL != pPublicKey)
        {
            OTPasswordData thePWData(NULL == pstrReason ? "OTAsymmetricKey_OpenSSL::SaveCertToString" : pstrReason->Get());
            
            this->dp->SetKeyAsCopyOf(*pPublicKey, false, &thePWData, pImportPassword); // bool bIsPrivateKey=false;
            EVP_PKEY_free(pPublicKey);
            pPublicKey = NULL;
        }
		// else?
        
        bSuccess = true;
	}
	// ---------------------------------------
	//
	if (bSuccess)
        strOutput = strx509;
	
	return bSuccess;    
}


//virtual
bool OTAsymmetricKey_OpenSSL::SavePrivateKeyToString(OTString & strOutput, const OTString * pstrReason/*=NULL*/, OTPassword * pImportPassword/*=NULL*/)
{
    const EVP_CIPHER * pCipher = EVP_des_ede3_cbc(); // todo security (revisit this mode...)
    // ---------------------------------------
    if (!IsPrivate())
    {
		OTLog::vError("%s: Error: !IsPrivate() (This function should only be called on a private key.)\n", __FUNCTION__);
		return false;
    }
    // ------------------------------
    EVP_PKEY  * pPrivateKey = dp->GetKeyLowLevel();
    if (NULL == pPrivateKey)
    {
        OTLog::vError("%s: Error: Unexpected NULL pPrivateKey. (Returning false.)\n", __FUNCTION__);
        return false;
    }
    // ---------------------------------------
    OpenSSL_BIO bio_out_pri  = BIO_new(BIO_s_mem()); bio_out_pri.setFreeOnly(); // only BIO_free(), not BIO_free_all();

    // ---------------------------------------
    OTPasswordData thePWData((NULL != pstrReason) ? pstrReason->Get() : 
                             "OTAsymmetricKey_OpenSSL::SavePrivateKeyToString is calling PEM_write_bio_PrivateKey...");
    
    if (NULL == pImportPassword)
        PEM_write_bio_PrivateKey(bio_out_pri,
                                 pPrivateKey,
                                 pCipher,
                                 NULL, 0, OTAsymmetricKey::GetPasswordCallback(), &thePWData);
    else
        PEM_write_bio_PrivateKey(bio_out_pri,
                                 pPrivateKey,
                                 pCipher,
                                 NULL, 0, 0, const_cast<void*>(reinterpret_cast<const void*>(pImportPassword->getPassword())));
    // ---------------------------------------
    bool bSuccess = false;
    
	int32_t           len = 0;
	uint8_t buffer_pri [4096] = ""; // todo hardcoded
	
    // todo hardcoded 4080 (see array above.)
    if (0 < (len = BIO_read(bio_out_pri, buffer_pri, 4080))) // returns number of bytes successfully read.
    {
        buffer_pri[len] = '\0';
        strOutput.Set((const char *)buffer_pri); // so I can write this string to file in a sec... todo cast
        bSuccess = true;
    }
    else OTLog::vError("%s: Error: key length is not 1 or more!", __FUNCTION__);
	// ---------------------------------------
	return bSuccess;    
}


/*
 * An implementation of convertion from PGP public key format to OpenSSL equivalent
 * Support of RSA, DSA and Elgamal public keys
 *
 * Copyright (c) 2010 Mounir IDRASSI <mounir.idrassi@idrix.fr>. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 */

typedef struct
{
	BIGNUM* p;
	BIGNUM* g;
	BIGNUM* pub_key;
	BIGNUM* priv_key;
}  ELGAMAL;

typedef struct
{
	RSA* pRsa;
	DSA* pDsa;
	ELGAMAL* pElgamal;
}  PgpKeys;


PgpKeys ExportRsaKey(uint8_t *pbData, int32_t dataLength)
{
	PgpKeys pgpKeys;
	int32_t i;
	
	OT_ASSERT(NULL != pbData);
	
	memset(&pgpKeys, 0, sizeof(pgpKeys));
	for (i = 0; i < dataLength; )
	{
		int32_t packetLength;
		uint8_t packetTag = pbData[i++];
		if ((packetTag & 0x80) == 0) 
			break;
		if ((packetTag & 0x40))
		{
			packetTag &= 0x3F;
			packetLength = pbData[i++];
			if( (packetLength >191) && (packetLength <224)) 
				packetLength = ((packetLength-192) << 8) + pbData[i++];
			else if( (packetLength > 223) && (packetLength < 255))
				packetLength = (1 << (packetLength & 0x1f)); 
			else if(packetLength == 255) 
			{
				packetLength = (pbData[i]<<24) + (pbData[i+1]<<16) + (pbData[i+2]<<8) + pbData[i+3];
				i+=4;
			}
		}
		else
		{
			packetLength = packetTag & 3;
			packetTag = (packetTag >> 2) & 15;
			if(packetLength == 0) 
				packetLength = pbData[i++];
			else if(packetLength == 1) 
			{
				packetLength = (pbData[i]<<8) + pbData[i+1];
				i+=2;
			}
			else if(packetLength == 2) 
			{
				packetLength = (pbData[i]<<24) + (pbData[i+1]<<16) + (pbData[i+2]<<8) + pbData[i+3];
				i+=4;
			}
			else 
				packetLength = dataLength - 1;
		}
		
		if( (packetTag==6) || (packetTag==14) )  //  a public key
		{
			int32_t algorithm;
			int32_t version = pbData[i++];
			
			// skip time over 4 bytes
			i += 4;
			
			if( (version==2) || (version==3) )
			{
				// skip validity over 2 bytes
				i += 2;
			}
			
			algorithm = pbData[i++];
			
			if( (algorithm == 1) || (algorithm == 2) || (algorithm == 3) ) // an RSA key
			{
				int32_t modulusLength, exponentLength;
				RSA* pKey = RSA_new();
				
				// Get the modulus
				modulusLength = ((pbData[i]*256 + pbData[i+1]+7)/8);
				pKey->n = BN_bin2bn (pbData + i + 2, modulusLength, NULL);
				i += modulusLength + 2;
				
				// Get the exponent
				exponentLength = (pbData[i]*256 + pbData[i+1]+7)/8;
				pKey->e = BN_bin2bn(pbData + i + 2, exponentLength, NULL);
				i += exponentLength + 2;
				
				pgpKeys.pRsa = pKey;
				
				continue;
			}
			else if (algorithm == 17) // a DSA key
			{
				int32_t pLen, qLen, gLen, yLen;
				DSA* pKey = DSA_new();
				
				// Get Prime P
				pLen = ((pbData[i]*256 + pbData[i+1]+7)/8);
				pKey->p = BN_bin2bn(pbData + i + 2, pLen, NULL);
				i += pLen + 2;
				
				// Get Prime Q
				qLen = ((pbData[i]*256 + pbData[i+1]+7)/8);
				pKey->q = BN_bin2bn(pbData + i + 2, qLen, NULL);
				i += qLen + 2;
				
				// Get Prime G
				gLen = ((pbData[i]*256 + pbData[i+1]+7)/8);
				pKey->g = BN_bin2bn(pbData + i + 2, gLen, NULL);
				i += gLen + 2;
				
				// Get Prime Y
				yLen = ((pbData[i]*256 + pbData[i+1]+7)/8);
				pKey->pub_key = BN_bin2bn(pbData + i + 2, yLen, NULL);
				i += yLen + 2;
				
				pgpKeys.pDsa = pKey;
				
				continue;
			}
			else if ((algorithm == 16) || (algorithm == 20)) // Elgamal key (not supported by OpenSSL
			{
				int32_t pLen, gLen, yLen;
				ELGAMAL* pKey = (ELGAMAL*) malloc(sizeof(ELGAMAL));
				if (NULL == pKey) {OTLog::vError("%s: Error: pKey is NULL!", __FUNCTION__); OT_FAIL; }
				
				// Get Prime P
				pLen = ((pbData[i]*256 + pbData[i+1]+7)/8);

				pKey->p = BN_bin2bn(pbData + i + 2, pLen, NULL);

				i += pLen + 2;
				
				// Get Prime G
				gLen = ((pbData[i]*256 + pbData[i+1]+7)/8);
				pKey->g = BN_bin2bn(pbData + i + 2, gLen, NULL);
				i += gLen + 2;
				
				// Get Prime Y
				yLen = ((pbData[i]*256 + pbData[i+1]+7)/8);       
				pKey->pub_key = BN_bin2bn(pbData + i + 2, yLen, NULL);
				i += yLen + 2;
				
				pgpKeys.pElgamal = pKey;
				
				continue;
			}
			else
			{
				i -= 6;
				if (version == 2 || version == 3)
					i -= 2;
			}
		}
		
		i += packetLength;	
	}
	
	return pgpKeys;
}


// Decodes a PGP public key from ASCII armor into an actual key pointer
// and sets that as the keypointer on this object.
// This function expects the bookends to be GONE already
// It just wants the base64 encoded data which is why we have ascii-armor
// object coming in instead of a string.
bool OTAsymmetricKey_OpenSSL::LoadPublicKeyFromPGPKey(const OTASCIIArmor & strKey)
{	
    Release();
    // ---------------------
    
	m_bIsPublicKey	= true;
	m_bIsPrivateKey	= false;
	
	/*
	 * An implementation of convertion from PGP public key format to OpenSSL equivalent
	 * Support of RSA, DSA and Elgamal public keys
	 *
	 * Copyright (c) 2010 Mounir IDRASSI <mounir.idrassi@idrix.fr>. All rights reserved.
	 *
	 * This program is distributed in the hope that it will be useful, 
	 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
	 * or FITNESS FOR A PARTICULAR PURPOSE.
	 * 
	 */
	int32_t iRet =-1, len;
	uint8_t buffer[520]; // Making it a bit bigger than 512 for safety reasons.
	BUF_MEM *bptr;
	PgpKeys pgpKeys;
	
	OpenSSL_BIO b64 = BIO_new(BIO_f_base64());
	OpenSSL_BIO bio = BIO_new_mem_buf((void*)strKey.Get(), -1);
	OpenSSL_BIO bio_out = BIO_new(BIO_s_mem());
    OpenSSL_BIO bioJoin = BIO_push(b64, bio); b64.release(); bio.release();

	while((len = BIO_read(bioJoin, buffer, 512)) > 0)
		BIO_write(bio_out, buffer, len);

    BIO_get_mem_ptr(bio_out, &bptr); bio_out.setFreeOnly();
	
	pgpKeys = ExportRsaKey((uint8_t*)bptr->data, static_cast<int32_t> (bptr->length));
	
	if(!pgpKeys.pRsa)
	{  
		OTLog::Output(5,  "\nNo RSA public key found.\n\n"); 
	}
	else
	{
		char* szModulusHex = BN_bn2hex(pgpKeys.pRsa->n);
		char* szExponentHex = BN_bn2hex(pgpKeys.pRsa->e);
		OTLog::vOutput(5, "RSA public key found : \n  Modulus (%d bits)\n", BN_num_bits(pgpKeys.pRsa->n));
		OTLog::vOutput(5, "  Exponent : 0x%s\n\n", szExponentHex);
		OTLog::vOutput(5, "RSA public key found : \nModulus (%d bits) : 0x%s\n", BN_num_bits(pgpKeys.pRsa->n), szModulusHex);
		OTLog::vOutput(5, "Exponent : 0x%s\n\n", szExponentHex);
		
		CRYPTO_free(szModulusHex);
		CRYPTO_free(szExponentHex);
	}
	
	if(!pgpKeys.pDsa)
	{  
		OTLog::Output(5, "No DSA public key found.\n\n"); 
	}
	else
	{
		char* szPHex = BN_bn2hex(pgpKeys.pDsa->p);
		char* szQHex = BN_bn2hex(pgpKeys.pDsa->q);
		char* szGHex = BN_bn2hex(pgpKeys.pDsa->g);
		char* szYHex = BN_bn2hex(pgpKeys.pDsa->pub_key);
		OTLog::vOutput(5, "DSA public key found : \n  p (%d bits)\n", BN_num_bits(pgpKeys.pDsa->p));
		OTLog::vOutput(5, "  q (%d bits)\n", BN_num_bits(pgpKeys.pDsa->q));
		OTLog::vOutput(5, "  g (%d bits)\n", BN_num_bits(pgpKeys.pDsa->g));
		OTLog::vOutput(5, "public key (%d bits)\n\n", BN_num_bits(pgpKeys.pDsa->pub_key));
		OTLog::vOutput(5, "DSA public key found : \np (%d bits) : 0x%s\n", BN_num_bits(pgpKeys.pDsa->p), szPHex);
		OTLog::vOutput(5, "q (%d bits) : 0x%s\n", BN_num_bits(pgpKeys.pDsa->q),szQHex);
		OTLog::vOutput(5, "g (%d bits) : 0x%s\n", BN_num_bits(pgpKeys.pDsa->g),szGHex);
		OTLog::vOutput(5, "public key (%d bits) : 0x%s\n\n", BN_num_bits(pgpKeys.pDsa->pub_key),szYHex);
		
		CRYPTO_free(szPHex);
		CRYPTO_free(szQHex);
		CRYPTO_free(szGHex);
		CRYPTO_free(szYHex);
	}
	
	if(!pgpKeys.pElgamal)
	{  
		OTLog::Output(5, "No Elgamal public key found.\n\n"); 
	}
	else
	{
		char* szPHex = BN_bn2hex(pgpKeys.pElgamal->p);
		char* szGHex = BN_bn2hex(pgpKeys.pElgamal->g);
		char* szYHex = BN_bn2hex(pgpKeys.pElgamal->pub_key);
		OTLog::vOutput(5, "Elgamal public key found : \n  p (%d bits) : 0x%s\n", BN_num_bits(pgpKeys.pElgamal->p), szPHex);
		OTLog::vOutput(5, "  g (%d bits) : 0x%s\n", BN_num_bits(pgpKeys.pElgamal->g),szGHex);
		OTLog::vOutput(5, "  public key (%d bits) : 0x%s\n\n", BN_num_bits(pgpKeys.pElgamal->pub_key),szYHex);
		
		CRYPTO_free(szPHex);
		CRYPTO_free(szGHex);
		CRYPTO_free(szYHex);
	}
	
	iRet = 0;
	
	/*
	if (pgpKeys.pRsa)
		RSA_free(pgpKeys.pRsa);
	if (pgpKeys.pDsa)
		DSA_free(pgpKeys.pDsa);
	if (pgpKeys.pElgamal)
		free(pgpKeys.pElgamal);
	*/
	
    // -------------------------------------------------------

	bool		bReturnValue	= false;
	EVP_PKEY *	pkey			= EVP_PKEY_new();
	OT_ASSERT(NULL != pkey);
	
	if (pgpKeys.pRsa)
	{
		if (EVP_PKEY_assign_RSA(pkey, pgpKeys.pRsa))
		{
			bReturnValue	= true;
            // todo: make sure the lack of RSA_free here is not a memory leak.            
			OTLog::Output(4, "Successfully extracted RSA public key from PGP public key block.\n");
		}
		else
		{
			RSA_free(pgpKeys.pRsa);
			OTLog::Output(0, "Extracted RSA public key from PGP public key block, but unable to convert to EVP_PKEY.\n");
		}

		pgpKeys.pRsa = NULL;
	}
	else if (pgpKeys.pDsa)
	{
		if (EVP_PKEY_assign_DSA(pkey, pgpKeys.pDsa))
		{
			bReturnValue	= true;
            // todo: make sure the lack of DSA_free here is not a memory leak.
			OTLog::Output(4, "Successfully extracted DSA public key from PGP public key block.\n");
		}
		else
		{
			DSA_free(pgpKeys.pDsa);
			OTLog::Output(0, "Extracted DSA public key from PGP public key block, but unable to convert to EVP_PKEY.\n");
		}
		
		pgpKeys.pDsa = NULL;
	}
	else if (pgpKeys.pElgamal)
	{
		OTLog::Output(0, "Extracted ElGamal Key from PGP public key block, but currently do not support it (sorry))\n");
        //
		// int32_t EVP_PKEY_assign_EC_KEY(EVP_PKEY *pkey,EC_KEY *key); // Here is the assign function for El Gamal 
		// (assuming that "EC" stands for eliptical curve... kind of hard to tell with the OpenSSL docs...)
        //
		free(pgpKeys.pElgamal); 
		pgpKeys.pElgamal = NULL;
	}
    // -------------------------------------------------------
    // FT: Adding some fixes here...
    //
    if (bReturnValue)
    {
        dp->SetKeyAsCopyOf(*pkey, false); // bIsPrivateKey=false. PUBLIC KEY.
        EVP_PKEY_free(pkey); // We have our own copy already. It's set NULL just below...
    }
    else if (NULL != pkey) // we failed, but pkey is NOT null (need to free it.)
    {
        EVP_PKEY_free(pkey); // Set NULL just below...
    }
    // ---------------------------
	pkey = NULL; // This is either stored on m_pKey, or deleted. I'm setting pointer to NULL here just for completeness.
		
	return bReturnValue;
    
	//	EVP_cleanup(); // removes digests from the table
	//	ERR_free_strings(); // removes error strings.
}


#elif defined (OT_CRYPTO_USING_GPG)


#else


#endif