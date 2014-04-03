/* Certificate creation. Demonstrates some certificate related
* operations.
*/

#include <stdafx.hpp>

#include "OTString.hpp"

// -----------------------------------------------

// -----------------------------------------------

// -----------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>

#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>

#ifdef ANDROID
#include <openssl/bn.h>
#endif

#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif

#ifdef __cplusplus
}
#endif

// -----------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif


int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days);
int add_ext(X509 *cert, int nid, char *value);


/*
int main(int argc, char **argv)
        {
        BIO *bio_err;
        X509 *x509=NULL;
        EVP_PKEY *pkey=NULL;

        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

        bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);

        mkcert(&x509,&pkey,512,0,365);

        RSA_print_fp(stdout,pkey->pkey.rsa,0);
        X509_print_fp(stdout,x509);

        PEM_write_PrivateKey(stdout,pkey,EVP_des_ede3_cbc(),NULL,0,NULL, NULL);
        PEM_write_X509(stdout,x509);

        X509_free(x509);
        EVP_PKEY_free(pkey);

#ifndef OPENSSL_NO_ENGINE
        ENGINE_cleanup();
#endif
        CRYPTO_cleanup_all_ex_data();

        CRYPTO_mem_leaks(bio_err);
        return(0);
        }
 */



static void callback(int p, int n, void *arg)
        {
        char c='B';

        if (p == 0) c='.';
        if (p == 1) c='+';
        if (p == 2) c='*';
        if (p == 3) c='\n';
        fputc(c,stderr);
        }


int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days)
{
    bool bCreatedKey  = false;
    bool bCreatedX509 = false;
        // -----------------
        X509      * x    = NULL;
        EVP_PKEY  * pk   = NULL;
        RSA       * rsa  = NULL;
        X509_NAME * name = NULL;

        if ((pkeyp == NULL) || (*pkeyp == NULL))
        {
            if ((pk = EVP_PKEY_new()) == NULL)
            {
                abort();  // todo

                //return(0); undeeded after abort.
            }
            bCreatedKey = true;
        }
        else
            pk = *pkeyp;
        // -----------------------------------------
        if ((x509p == NULL) || (*x509p == NULL))
        {
            if ((x = X509_new()) == NULL)
            {
                if (bCreatedKey)
                {
                    EVP_PKEY_free(pk);
                }
                return(0);
            }

            bCreatedX509 = true;
        }
        else
            x = *x509p;
        // -----------------------------------------
//		pRsaKey = RSA_generate_key(1024, 0x010001, NULL, NULL);

#ifdef ANDROID
        rsa         = RSA_new();
        BIGNUM * e1 = BN_new();

        if ((NULL == rsa) || (NULL == e1))
            abort(); // todo

//      BN_set_word(e1, 65537);
        BN_set_word(e1, RSA_F4);

        if (!RSA_generate_key_ex(rsa, bits, e1, NULL))
            abort(); // todo

        BN_free(e1);
#else
        rsa = RSA_generate_key(bits, RSA_F4, callback, NULL);
#endif
        // -----------------------------------------
        if (!EVP_PKEY_assign_RSA(pk, rsa))
        {
            abort();  // todo
            //return(0); undeeded after abort.
        }
        // ------------------------------
        rsa = NULL;

        X509_set_version(x, 2);
        ASN1_INTEGER_set(X509_get_serialNumber(x), serial);
        X509_gmtime_adj (X509_get_notBefore(x), 0);
        X509_gmtime_adj (X509_get_notAfter (x), static_cast<long>(60*60*24*days));
        X509_set_pubkey (x, pk);

        name = X509_get_subject_name(x);

        /* This function creates and adds the entry, working out the
         * correct string type and performing checks on its length.
         * Normally we'd check the return value for errors...
         */
        X509_NAME_add_entry_by_txt(name,"C",
                                MBSTRING_ASC,
                                   (const unsigned char *)"UK",
                                   -1, -1, 0);
        X509_NAME_add_entry_by_txt(name,"CN",
                                MBSTRING_ASC,
                                   (const unsigned char *)"OpenSSL Group",
                                   -1, -1, 0);

        /* Its self signed so set the issuer name to be the same as the
         * subject.
         */
        X509_set_issuer_name(x, name);
        // ----------------------------------------------------------------------------
        /* Add various extensions: standard extensions */

        char * szConstraints  = new char[100]();
        char * szKeyUsage     = new char[100]();
        char * szSubjectKeyID = new char[100]();
        char * szCertType     = new char[100]();
        char * szComment      = new char[100]();
        // ----------------------------------------------------------------------------
        OTString::safe_strcpy(szConstraints,  "critical,CA:TRUE",             99);
        OTString::safe_strcpy(szKeyUsage,     "critical,keyCertSign,cRLSign", 99);
        OTString::safe_strcpy(szSubjectKeyID, "hash",                         99);
        OTString::safe_strcpy(szCertType,     "sslCA",                        99);
        OTString::safe_strcpy(szComment,      "example comment extension",    99);
        // ----------------------------------------------------------------------------
        add_ext(x, NID_basic_constraints,      szConstraints);
        add_ext(x, NID_key_usage,              szKeyUsage);
        add_ext(x, NID_subject_key_identifier, szSubjectKeyID);
        add_ext(x, NID_netscape_cert_type,     szCertType); // Some Netscape specific extensions
        add_ext(x, NID_netscape_comment,       szComment);  // Some Netscape specific extensions
        // ----------------------------------------------------------------------------
        delete [] szConstraints;   szConstraints  = NULL;
        delete [] szKeyUsage;      szKeyUsage     = NULL;
        delete [] szSubjectKeyID;  szSubjectKeyID = NULL;
        delete [] szCertType;      szCertType     = NULL;
        delete [] szComment;       szComment      = NULL;
        // ----------------------------------------------------------------------------

#ifdef CUSTOM_EXT
        // Maybe even add our own extension based on existing
        {
                int nid;
                nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
                X509V3_EXT_add_alias(nid, NID_netscape_comment);
                add_ext(x, nid, "example comment alias");
        }
#endif
        // ------------------------------
        if (!X509_sign(x, pk, EVP_md5()) || // TODO security:  md5 ???
            (NULL == x509p)              ||
            (NULL == pkeyp))
        {
            // ERROR
            //
            if (bCreatedX509)
                X509_free(x);

            // NOTE: not sure if x owns pk, in which case pk is already freed above.
            // Todo: find out and then determine whether or not to uncomment this.
            // (Presumably this would be a rare occurrence anyway.)
            //
//            if (bCreatedKey)
//                EVP_PKEY_free(pk);

            x  = NULL;
            pk = NULL;

            return 0;
        }
        // ------------------------------
        *x509p = x;
        *pkeyp = pk;

        return(1);
}

/* Add extension using V3 code: we can set the config file as NULL
 * because we won't reference any other sections.
 */

int add_ext(X509 *cert, int nid, char *value)
        {
        X509_EXTENSION *ex;
        X509V3_CTX ctx;
        /* This sets the 'context' of the extensions. */
        /* No configuration database */
        X509V3_set_ctx_nodb(&ctx);
        /* Issuer and subject certs: both the target since it is self signed,
         * no request and no CRL
         */
        X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
        ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);

        if (!ex)
            return 0;

        X509_add_ext(cert,ex,-1);
        X509_EXTENSION_free(ex);
        return 1;
        }

#ifdef __cplusplus
} // closing brace for extern "C"
#endif


