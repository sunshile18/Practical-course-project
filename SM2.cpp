#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <string>
#include<iostream>
#include<cstdlib>

using namespace std;

string sk;
string pk;


int en_sm2(string a1, unsigned char* b1, int c1, unsigned char* d1)
{
    EVP_PKEY_CTX* c = NULL;
    BIO* a = NULL;
    size_t l1;
    EVP_PKEY* b = NULL;
    char* d = NULL;
    char* e = const_cast<char*>(a1.c_str());
    if ((a = BIO_new_mem_buf(e, -1)) == NULL)
    {
        cout << "fail!" << endl;
        return NULL;
    }
    b = PEM_read_bio_PUBKEY(a, NULL, NULL, NULL);
    BIO_free_all(a);
    if ((EVP_PKEY_set_alias_type(b, EVP_PKEY_SM2)) != 1)
    {
        goto clean_up;
    }

    if (!(c = EVP_PKEY_CTX_new(b, NULL)))
    {
        goto clean_up;
    }

    if ((EVP_PKEY_encrypt_init(c)) != 1)
    {
        goto clean_up;
    }

    if ((EVP_PKEY_encrypt(c, NULL, &l1, reinterpret_cast<unsigned char*>(b1), (size_t)(c1))) != 1)
    {
        goto clean_up;
    }
    if (!(d = (char*)malloc(l1)))
    {
        goto clean_up;
    }

    if ((EVP_PKEY_encrypt(c, reinterpret_cast<unsigned char*>(d), &l1, reinterpret_cast<unsigned char*>(b1), c1)) != 1)
    {
        goto clean_up;
    }
   
    memcpy(d1, d, l1);
    return (int)(l1);

clean_up:

    if (b)
    {
        EVP_PKEY_free(b);
    }
    if (c)
    {
        EVP_PKEY_CTX_free(c);
    }

    if (b1)
    {
        free(b1);
    }

    if (d)
    {
        free(d);
    }
}

int de_sm2(string a1, unsigned char* d, int l1, unsigned char* d2)

{
    EVP_PKEY_CTX* c = NULL;
    BIO* aa = NULL;
    size_t l2 = 0;
    EVP_PKEY* bb;
    string temp;
    char* dd = NULL;
   
    //create pri key
    char* ee = const_cast<char*>(temp.c_str());
    if ((aa = BIO_new_mem_buf(ee, -1)) == NULL)
    {
        cout << "fail!" << endl;
    }
    bb = PEM_read_bio_PrivateKey(aa, NULL, NULL, NULL);
    BIO_free_all(aa);
    if (NULL == bb)
    {
        ERR_load_crypto_strings();
        char buf[512];
        ERR_error_string_n(ERR_get_error(), buf, sizeof(buf));
        cout << "fail!" << endl;
    }
    //½âÃÜ
    if ((EVP_PKEY_set_alias_type(bb, EVP_PKEY_SM2)) != 1)
    {
        cout << "fail!" << endl;
    }

    if (!(c = EVP_PKEY_CTX_new(bb, NULL)))
    {
        cout << "fail!" << endl;
    }
    if ((EVP_PKEY_decrypt_init(c)) != 1)
    {
        cout << "fail!" << endl;
    }
    if ((EVP_PKEY_decrypt(c, NULL, &l2, reinterpret_cast<unsigned char*>(d), l1)) != 1)
    {
        cout << "fail!" << endl;
        
    }
    if (!(dd = (char*)malloc(l2)))
    {
        cout << "fail!" << endl;
    }
    if ((EVP_PKEY_decrypt(c, reinterpret_cast<unsigned char*>(dd), &l2, reinterpret_cast<unsigned char*>(d), l1)) != 1)
    {
        cout << "fail!" << endl;
    }
    
    memcpy(d2, dd, l2);
    EVP_PKEY_CTX_free(c);
    free(dd);
    return l2;
}

int main(int argc, char* argv[])
{
    unsigned char s1[512], s2[512];
    int ll, l3;
    for (int i = 64; i < sk.size(); i += 64)
    {
        if (sk[i] != '\n')
        {
            sk.insert(i, "\n");
        }
        ++i;
    }
    
    for (int i = 64; i < pk.size(); i += 64)
    {
        if (pk[i] != '\n')
        {
            pk.insert(i, "\n");
        }
        ++i;
    }
    
    unsigned char ss[20] = { 0x41,0x12,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10, 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20 };

    ll = en_sm2(pk, ss, 20, s1);
    for (int i = 0; i < ll; i++)
    {
        cout << s1[i];
    }
    cout << endl;
    l3 = de_sm2(sk, s1, ll, s2);
    for (int i = 0; i < l3; i++)
    {
        cout << s2[i];
    }
    cout << endl;
    
}
