#include "ciphers/AES.h"

#include <openssl/aes.h>

namespace Ciphers
{

AES::AES()
{

}

AES::~AES()
{

}

Error AES::validateParam(const InitParam& param)
{
    if(param.iv.size() != AES_BLOCK_SIZE) {
        return Error::InvalidIvSize;
    }

    if(param.key.size() != param.key.size()) {
        return Error::InvalidKeySize;
    }

    return Error::None;
}

const EVP_CIPHER* AES::getCipher(KeySize keySize, Mode mode)
{
    return EVP_aes_256_cbc();
}

bool AES::init(const InitParam& param)
{
    if(_ctx) {
        EVP_CIPHER_CTX_free(_ctx);
        _ctx = nullptr;
    }

    _ctx = EVP_CIPHER_CTX_new();
    if(!_ctx) {
        return false;
    }

    int rs = 0;
    auto* cipher = getCipher(param.keySize, param.mode);
    rs = EVP_CipherInit(_ctx, cipher, (unsigned char*)param.key.data(),
                        (unsigned char*)param.iv.data(), param.isEnc);
    if(rs != 1) {
        return false;
    }

    return true;
}

QByteArray AES::update(const QByteArray& data)
{
    QByteArray out;
    if(_ctx) {
        int inSize = data.size();
        byte* outBuff = new byte[inSize+AES_BLOCK_SIZE];
        int outLen = 0;
        int rs = EVP_CipherUpdate(_ctx, outBuff, &outLen, (byte*)data.data(), inSize);
        if(rs) {
            out = QByteArray((char*)outBuff, outLen);
            delete[] outBuff;
        }
    }

    return out;
}

QByteArray AES::final()
{
    QByteArray out;
    if(_ctx) {
        byte* outBuff = new byte[AES_BLOCK_SIZE];
        int outLen = 0;
        int rs = EVP_CipherFinal(_ctx, outBuff, &outLen);
        if(rs) {
            out = QByteArray((char*)outBuff, outLen);
            delete[] outBuff;
        }
    }

    return out;
}

}