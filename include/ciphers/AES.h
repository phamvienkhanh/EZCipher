#ifndef _CIPHERS_AES_H_
#define _CIPHERS_AES_H_

#include "precompile.h"

#include <openssl/evp.h>

#include "ciphers/defs.h"

namespace Ciphers 
{

class AES
{

public:
    struct InitParam {
        KeySize keySize;
        Mode mode;
        QByteArray key;
        QByteArray iv;
        bool isEnc = true;
    };

public:
    bool init(const InitParam& param);
    QByteArray update(const QByteArray& data);
    QByteArray final();

private:
    const EVP_CIPHER* getCipher(KeySize keySize, Mode mode);
    Error validateParam(const InitParam& param);

public:
    AES();
    ~AES();

private:
    EVP_CIPHER_CTX* _ctx = nullptr;
};

}

#endif