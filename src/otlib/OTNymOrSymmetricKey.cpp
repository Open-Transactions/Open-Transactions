/************************************************************
 *    
 *  OTNymOrSymmetricKey.cpp
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

#include "OTNymOrSymmetricKey.hpp"

#include "OTEnvelope.hpp"
#include "OTLog.hpp"
#include "OTPassword.hpp"
#include "OTPseudonym.hpp"
#include "OTSymmetricKey.hpp"

extern "C"
{
#if defined (OPENTXS_HAVE_NETINET_IN_H)
#include <netinet/in.h>
#endif
}


// There are certain cases where we want the option to pass a Nym OR a
// symmetric key, and the function should be able to handle either.
// This class is used to make that possible.
//
/// (This constructor is private.)
OTNym_or_SymmetricKey::OTNym_or_SymmetricKey()
: m_pNym(NULL), m_pKey(NULL), m_pPassword(NULL), m_bCleanupPassword(false), m_pstrDisplay(NULL)  {}


OTNym_or_SymmetricKey::~OTNym_or_SymmetricKey()
{
    // We don't own these objects.
    // Rather, we own a pointer to ONE of them, since we are a wrapper
    // for this one or that.
    //
    m_pNym       = NULL;
    // -------------
    m_pKey       = NULL;
    // -------------
    if (m_bCleanupPassword && (NULL != m_pPassword))
        delete m_pPassword;
    m_pPassword  = NULL; // optional
    // -------------
    
    m_pstrDisplay = NULL;
    
    // Since this is merely a wrapper class, we don't even Release() these things.
    // However, we DO have a release function, since the programmatic USER of this class
    // MAY wish to Release() whatever it is wrapping. That's his choice. But we don't call
    // it here in the destructor, because we aren't the owner.
    //
//  Release_Nym_or_SymmetricKey(); 
}


OTNym_or_SymmetricKey::OTNym_or_SymmetricKey(const OTNym_or_SymmetricKey & rhs) // same type
: m_pNym(NULL), m_pKey(NULL), m_pPassword(NULL), m_bCleanupPassword(false), m_pstrDisplay(rhs.m_pstrDisplay)
{
    // This class doesn't do any cleanup, it's just a temporary wrapper.
    // So we won't have anything get deleted twice, because this class won't
    // even delete it once.
    //
    m_pNym       = rhs.m_pNym;
    // -----------------
    m_pKey       = rhs.m_pKey;
    m_pPassword  = rhs.m_pPassword; // optional

    //m_bCleanupPassword  = rhs.m_bCleanupPassword; // optional
    //
    // This is commented out because this object keeps a POINTER to the password,
    // which is usually owned by the caller. (So we normally wouldn't delete it.)
    // But sometimes, we have to CREATE the password, in which case we store it until
    // we destruct, and then destroy it in our destructor. (Having it available in the
    // meantime to use, without having to load again.)
    // m_bCleanupPassword thus normally tells us whether the password was passed in
    // by its owner for reference purposes only, or whether we created it internally and
    // thus need to clean it up ourselves.
    // THEREFORE, here in the COPY CONSTRUCTOR, we need to keep a pointer to the password
    // from the rhs object, in case we need that password, but we cannot DESTROY that password,
    // if rhs is also destroying it! Therefore we copy the password, but we leave m_bCleanupPassword
    // as false (its default) since THIS INSTANCE definitely does not own m_pPassword.
    //
}


OTNym_or_SymmetricKey::OTNym_or_SymmetricKey(const OTPseudonym & theNym, const OTString * pstrDisplay/*=NULL*/)  // construct with nym
: m_pNym(const_cast<OTPseudonym *>(&theNym)), m_pKey(NULL), m_pPassword(NULL), m_bCleanupPassword(false), m_pstrDisplay(pstrDisplay)
{
    
}


OTNym_or_SymmetricKey::OTNym_or_SymmetricKey(const OTSymmetricKey & theKey, const OTString * pstrDisplay/*=NULL*/) // construct with key
: m_pNym(NULL), m_pKey(const_cast<OTSymmetricKey *>(&theKey)), m_pPassword(NULL), m_bCleanupPassword(false), m_pstrDisplay(pstrDisplay)
{
    
}


OTNym_or_SymmetricKey::OTNym_or_SymmetricKey(const OTSymmetricKey & theKey, const OTPassword & thePassword, // construct with key and password.
                                             const OTString * pstrDisplay/*=NULL*/) 
: m_pNym(NULL), m_pKey(const_cast<OTSymmetricKey *>(&theKey)),
  m_pPassword(const_cast<OTPassword *>(&thePassword)), m_bCleanupPassword(false), m_pstrDisplay(pstrDisplay)
{
    
}


void OTNym_or_SymmetricKey::swap(OTNym_or_SymmetricKey & other)
{
    if (&other != this)
    {
        std::swap(m_pNym,               other.m_pNym);
        std::swap(m_pKey,               other.m_pKey);
        std::swap(m_pPassword,          other.m_pPassword);
        std::swap(m_bCleanupPassword,   other.m_bCleanupPassword);
        std::swap(m_pstrDisplay,        other.m_pstrDisplay);
    }
}


OTNym_or_SymmetricKey & OTNym_or_SymmetricKey::operator = (OTNym_or_SymmetricKey other) // passed by value.
{
    // swap this with other
    this->swap(other);
    
    // by convention, always return *this
    return *this;    
}


// This is just a wrapper class.
void OTNym_or_SymmetricKey::Release() // Someday make this virtual, if we ever subclass it.
{
    OT_ASSERT((m_pNym != NULL) || (m_pKey != NULL)); // m_pPassword is optional
    
    Release_Nym_or_SymmetricKey();
    
    // no need to call ot_super::Release here, since this class has no superclass.
}


// This is just a wrapper class. (Destructor doesn't call this because we aren't the owner.)
void OTNym_or_SymmetricKey::Release_Nym_or_SymmetricKey()
{
    if (NULL != m_pNym)
    {
//      m_pNym->Release(); // no such call on OTPseudonym. (Otherwise it wouldn't be commented out.)
    }

    if (NULL != m_pKey)
        m_pKey->Release();

    if (NULL != m_pPassword)
    {
        m_pPassword->zeroMemory();
        // -------------
        if (m_bCleanupPassword) // Only in cases where *this is the actual owner of m_pPassword.
        {
            delete m_pPassword;
            m_pPassword = NULL;
        }
    }
}


bool OTNym_or_SymmetricKey::CompareID(const OTNym_or_SymmetricKey & rhs) const
{
    OTIdentifier idTHIS, idRHS;
    // --------------------------
    this->GetIdentifier(idTHIS);
    rhs.  GetIdentifier(idRHS );
    // --------------------------
    return (idTHIS == idRHS);
}


void OTNym_or_SymmetricKey::GetIdentifier(OTIdentifier & theIdentifier) const
{
    if (this->IsNym())
    {
        m_pNym->GetIdentifier(theIdentifier);
    }
    else if (this->IsKey())
    {
        m_pKey->GetIdentifier(theIdentifier);
    }
    else
    {
        OT_FAIL; // should never happen
    }
}


void OTNym_or_SymmetricKey::GetIdentifier(OTString & strIdentifier) const
{
    if (this->IsNym())
    {
        m_pNym->GetIdentifier(strIdentifier);
    }
    else if (this->IsKey())
    {
        m_pKey->GetIdentifier(strIdentifier);
    }
    else
    {
        OT_FAIL; // should never happen
    }   
}


// From OTEnvelope:
//	bool GetAsBookendedString  (      OTString     & strArmorWithBookends, bool bEscaped    = false ) const;
//	bool SetFromBookendedString(const OTString     & strArmorWithBookends, bool bEscaped    = false );

bool OTNym_or_SymmetricKey::Open_or_Decrypt(const OTEnvelope & inputEnvelope,
                                                  OTString   & strOutput,
                                            const OTString   * pstrDisplay/*=NULL*/)
{
    const char * szFunc = "OTNym_or_SymmetricKey::Open_or_Decrypt";
    // --------------------------
    bool bSuccess                  = false;
    bool bHadToInstantiatePassword = false;
    // ---------------
	// Decrypt/Open inputEnvelope into strOutput
    //    
    if (this->IsNym()) // *this is a Nym.
    {
        bSuccess = (const_cast<OTEnvelope &>(inputEnvelope)).Open(*(this->GetNym()), strOutput);
    }
    else if (this->IsKey()) // *this is a symmetric key, possibly with a password already as well.
    {
        OTPassword * pPassword = NULL;
        
        if (this->HasPassword()) // Password is already available. Let's use it.
            pPassword = this->GetPassword();
        else // NO PASSWORD already? let's collect it from the user...
        {
            const OTString strDisplay((NULL == pstrDisplay) ? szFunc : pstrDisplay->Get());
            // NOTE: m_pstrDisplay overrides this below.
            // -------------------------------------------
            // returns a text OTPassword, or NULL.
            //
            pPassword = OTSymmetricKey::GetPassphraseFromUser((NULL == m_pstrDisplay) ? &strDisplay : m_pstrDisplay);//bool bAskTwice=false
            
            if (NULL == pPassword) // Unable to retrieve passphrase from user.
            {
                OTLog::vOutput(0, "%s: Failed trying to retrieve passphrase for key. "
                               "Returning false.\n", szFunc);
                return false;
            }
            else // OTNym_or_SymmetricKey stores this, if it creates it.
                 // (And cleans it up on destruction, IF it created it.)
                 //
                bHadToInstantiatePassword = true;
        }
        // -------------------------------------------
        //
        bSuccess = (const_cast<OTEnvelope &>(inputEnvelope)).Decrypt(strOutput, *(this->GetKey()), *pPassword);
        
        // We only set this, presuming we have to at all, if it was a success.
        if (bHadToInstantiatePassword)
        {
            if (bSuccess)
            {
                m_bCleanupPassword = true;
                m_pPassword        = pPassword; // Not bothering to cleanup whatever was here before, since we only end up here if m_pPassword was set to NULL (according to above logic...)
            }
            else // We instantiated the password, but the decrypt failed. (Need to cleanup the password then.)
            {
                delete pPassword;
                pPassword = NULL;
            }
        }
    }
    // else ? should never happen.
    // -------------------------------------------
    return bSuccess;
}


bool OTNym_or_SymmetricKey::Seal_or_Encrypt(      OTEnvelope & outputEnvelope,
                                            const OTString     strInput,
                                            const OTString   * pstrDisplay/*=NULL*/)
{
    const char * szFunc = "OTNym_or_SymmetricKey::Seal_or_Encrypt";
    // --------------------------
    bool bSuccess                  = false;
    bool bHadToInstantiatePassword = false;
    // ---------------
	// Encrypt/Seal strInput into outputEnvelope
    //
    if (this->IsNym())
    {
        bSuccess = outputEnvelope.Seal(*(this->GetNym()), strInput);
    }
    // -------------------------------------------
    else if (this->IsKey())
    {
        OTPassword * pPassword = NULL;
        
        if (this->HasPassword()) // Password is already available. Let's use it.
            pPassword = this->GetPassword();
        else // no password? let's collect it from the user...
        {
            const OTString strDisplay((NULL == pstrDisplay) ? szFunc : pstrDisplay->Get());
            // NOTE: m_pstrDisplay overrides this below.
            // -------------------------------------------
            // returns a text OTPassword, or NULL.
            //
            pPassword = OTSymmetricKey::GetPassphraseFromUser((NULL == m_pstrDisplay) ? &strDisplay : m_pstrDisplay);//bool bAskTwice=false
            
            if (NULL == pPassword) // Unable to retrieve passphrase from user.
            {
                OTLog::vOutput(0, "%s: Failed trying to retrieve passphrase for key. "
                               "Returning false.\n", szFunc);
                return false;
            }
            else // OTNym_or_SymmetricKey stores this, if it creates it.
                 // (And cleans it up on destruction, IF it created it.)
                 //
                bHadToInstantiatePassword = true;
        }
        // -------------------------------------------
        //
        bSuccess = outputEnvelope.Encrypt(strInput, *(this->GetKey()), *pPassword);
        
        // We only set this, presuming we have to at all, if it was a success.
        if (bHadToInstantiatePassword)
        {
            if (bSuccess)
            {
                m_bCleanupPassword = true;
                m_pPassword        = pPassword; // Not bothering to cleanup whatever was here before, since we only end up here if m_pPassword was set to NULL (according to above logic...)
            }
            else // We instantiated the password, but the encrypt failed. (Need to cleanup the password then.)
            {
                delete pPassword;
                pPassword = NULL;
            }
        }
    }
    // else ? should never happen.
    // -----------------------------------
	return bSuccess;
}
