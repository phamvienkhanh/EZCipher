#ifndef _CIPHERS_DEFS_H_
#define _CIPHERS_DEFS_H_

namespace Ciphers {

using byte = unsigned char;

enum KeySize {
    _128 = 128,
    _256 = 256,
};

enum Mode {
    ECB,
    CBC,
};

enum Error {
    None,
    InvalidIvSize,
    InvalidKeySize,
};

namespace Modes
{
    static const char* ECB = "ECB";
    static const char* CBC = "CBC";
    static const char* GCM = "GCM";
}

namespace KeySizes
{
    static const char* _128 = "128";
    static const char* _256 = "256";
}

}

#endif