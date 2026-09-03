#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <string>

bool build_encryption_key(
    char cipherToPlain[26],
    char plainToCipher[26]
);

std::string re_encrypt(
    const std::string& plaintext,
    char plainToCipher[26]
);

bool verify_solution(
    const std::string& ciphertext,
    const std::string& plaintext,
    char cipherToPlain[26]
);

#endif
