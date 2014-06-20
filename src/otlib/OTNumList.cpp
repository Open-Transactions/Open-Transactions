/************************************************************
 *
 *  OTNumList.cpp
 *
 *  Base class for many of the OT classes.
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

#include "OTNumList.hpp"

#include "OTLog.hpp"
#include "OTStorage.hpp"

#include <locale>


// OTNumList (helper class.)
OTNumList::OTNumList(const std::set<int64_t> & theNumbers)
{
    Add(theNumbers);
}


OTNumList::OTNumList(int64_t lInput)
{
    Add(lInput);
}


// removed, security reasons.
//OTNumList::OTNumList(const char * szNumbers)
//{
//    Add(szNumbers);
//}

OTNumList::OTNumList(const OTString & strNumbers)
{
    Add(strNumbers);
}


OTNumList::OTNumList(const std::string & strNumbers)
{
    Add(strNumbers);
}


OTNumList::OTNumList()
{

}


OTNumList::~OTNumList()
{

}


bool OTNumList::Add(const OTString & strNumbers)  // if false, means the numbers were already there. (At least one of them.)
{
    return Add(strNumbers.Get());
}


bool OTNumList::Add(const std::string & strNumbers)  // if false, means the numbers were already there. (At least one of them.)
{
    return Add(strNumbers.c_str());
}


// This function is private, so you can't use it without passing an OTString.
// (For security reasons.) It takes a comma-separated list of numbers, and adds
// them to *this.
//
bool OTNumList::Add(const char * szNumbers)       // if false, means the numbers were already there. (At least one of them.)
{
    OT_ASSERT(NULL != szNumbers); // Should never happen.

    bool    bSuccess    = true;
    int64_t    lNum        = 0;
    const
    char *  pChar       = szNumbers;
	std::locale loc;

    // Skip any whitespace.
	while (std::isspace(*pChar, loc))
        pChar++;

    // -------------------------------------
    bool bStartedANumber = false; // During the loop, set this to true when processing a digit, and set to false when anything else. That way when we go to add the number to the list, and it's "0", we'll know it's a real number we're supposed to add, and not just a default value.

    for (;;) // We already know it's not null, due to the assert. (So at least one iteration will happen.)
    {
		if (std::isdigit(*pChar, loc))
        {
            bStartedANumber = true;

            int32_t nDigit = (*pChar - '0');

            lNum *= 10;  // Move it up a decimal place.
            lNum += nDigit;
        }
        // if separator, or end of string, either way, add lNum to *this.
		else if ((',' == *pChar) || ('\0' == *pChar) || std::isspace(*pChar, loc)) // first sign of a space, and we are done with current number. (On to the next.)
        {
            if ((lNum > 0) || (bStartedANumber && (0 == lNum)))
            {
                if (false == this->Add(lNum)) // <=========
                {
                    bSuccess = false; // We still go ahead and try to add them all, and then return this sort of status when it's all done.
                }
            }
            // ------------------
            lNum = 0;   // reset for the next transaction number (in the comma-separated list.)
            bStartedANumber = false; // reset
        }
        else
        {
            OTLog::vError("OTNumList::Add: Error: Unexpected character found in erstwhile comma-separated list of longs: %c\n",
                          *pChar);
            bSuccess = false;
            break;
        }
        // ---------------------------------
        // End of the road.
        if ('\0' == *pChar)
            break;
        // -----------
        pChar++;
        // -----------
        // Skip any whitespace.
		while (std::isspace(*pChar, loc))
            pChar++;
        // -------------------------------------
    } // while

    return bSuccess;
}


bool OTNumList::Add(const int64_t & theValue)    // if false, means the value was already there.
{
    std::set<int64_t>::iterator it = m_setData.find(theValue);

    if (m_setData.end() == it) // it's not already there, so add it.
    {
        m_setData.insert(theValue);
        return true;
    }
    return false; // it was already there.
}


bool OTNumList::Peek(int64_t & lPeek) const
{
    std::set<int64_t>::iterator it = m_setData.begin();

    if (m_setData.end() != it) // it's there.
    {
        lPeek = *it;
        return true;
    }
    return false;
}


bool OTNumList::Pop()
{
    std::set<int64_t>::iterator it = m_setData.begin();

    if (m_setData.end() != it) // it's there.
    {
        m_setData.erase(it);
        return true;
    }
    return false;
}


bool OTNumList::Remove(const int64_t & theValue) // if false, means the value was NOT already there.
{
    std::set<int64_t>::iterator it = m_setData.find(theValue);

    if (m_setData.end() != it) // it's there.
    {
        m_setData.erase(it);
        return true;
    }
    return false; // it wasn't there (so how could you remove it then?)
}


bool OTNumList::Verify(const int64_t & theValue) const // returns true/false (whether value is already there.)
{
    std::set<int64_t>::iterator it = m_setData.find(theValue);

    return (m_setData.end() == it) ? false : true;
}


// True/False, based on whether values are already there.
// (ALL theNumbersmust be present.)
// So if *this contains "3,4,5,6" and rhs contains "4,5" then match is TRUE.
//
bool OTNumList::Verify(const std::set<int64_t> & theNumbers) const
{
    bool bSuccess = true;

    FOR_EACH_CONST(std::set<int64_t>, theNumbers)
    {
        const int64_t lValue = *it;

        if (!this->Verify(lValue)) // It must have NOT already been there.
            bSuccess = false;
    }

    return bSuccess;
}


/// True/False, based on whether OTNumLists MATCH in COUNT and CONTENT (NOT ORDER.)
///
bool OTNumList::Verify(const OTNumList & rhs) const
{
    // Verify they have the same number of elements.
    //
    if (this->Count() != rhs.Count())
        return false;
    // -------------------

    // Verify each value on *this is also found on rhs.
    //
    FOR_EACH(std::set<int64_t>, m_setData)
    {
        const int64_t lValue = *it;
        // ----------
        if (false == rhs.Verify(lValue))
            return false;
    }

    return true;
}


/// True/False, based on whether ANY of the numbers in rhs are found in *this.
///
bool OTNumList::VerifyAny(const OTNumList & rhs) const
{
    return rhs.VerifyAny(m_setData);
}


/// Verify whether ANY of the numbers on *this are found in setData.
///
bool OTNumList::VerifyAny(const std::set<int64_t> & setData) const
{
    FOR_EACH_CONST(std::set<int64_t>, m_setData)
    {
        const int64_t lValue = *it;
        // ----------
        std::set<int64_t>::const_iterator it_find = setData.find(lValue);

        if (it_find != setData.end()) // found a match.
            return true;
    }
    // -----------
    return false;
}


bool OTNumList::Add(const OTNumList & theNumList)    // if false, means the numbers were already there. (At least one of them.)
{
    std::set<int64_t> theOutput;
    theNumList.Output(theOutput); // returns false if the numlist was empty.

    return this->Add(theOutput);
}


bool OTNumList::Add(const std::set<int64_t> & theNumbers)    // if false, means the numbers were already there. (At least one of them.)
{
    bool bSuccess = true;

    FOR_EACH_CONST(std::set<int64_t>, theNumbers)
    {
        const int64_t lValue = *it;

        if (!this->Add(lValue)) // It must have already been there.
            bSuccess = false;
    }

    return bSuccess;
}


bool OTNumList::Remove(const std::set<int64_t> & theNumbers) // if false, means the numbers were NOT already there. (At least one of them.)
{
    bool bSuccess = true;

    FOR_EACH_CONST(std::set<int64_t>, theNumbers)
    {
        const int64_t lValue = *it;

        if (!this->Remove(lValue)) // It must have NOT already been there.
            bSuccess = false;
    }

    return bSuccess;
}


// Outputs the numlist as a set of numbers.
// (To iterate OTNumList, call this, then iterate the output.)
//
bool OTNumList::Output(std::set<int64_t> & theOutput) const // returns false if the numlist was empty.
{
    theOutput = m_setData;

    return (m_setData.size() > 0) ? true : false;
}


// Outputs the numlist as a comma-separated string (for serialization, usually.)
//
bool OTNumList::Output(OTString & strOutput) const // returns false if the numlist was empty.
{
    int32_t nIterationCount = 0;

    FOR_EACH(std::set<int64_t>, m_setData)
    {
        const int64_t lValue = *it;
        nIterationCount ++;
        // ----------

        strOutput.Concatenate("%s%lld",
                              // If first iteration, prepend a blank string (instead of a comma.)
                              // Like this:  "%lld"
                              // But for all subsequent iterations, concatenate: ",%lld"
                              (1 == nIterationCount) ? "" : ",", lValue);
    }

    return (m_setData.size() > 0) ? true : false;
}


int32_t OTNumList::Count() const
{
    return static_cast<int32_t> (m_setData.size());
}


void OTNumList::Release()
{
    m_setData.clear();
}
