#ifndef CRYPTANALYSIS_H
#define CRYPTANALYSIS_H

#include <string>

void iterative_cryptanalysis(
    const std::string& ciphertext,
    char cipherToPlain[26]
);

void recover_plaintext(
    const std::string& ciphertext,
    char cipherToPlain[26]
);

void recover_substitution_key(
    char cipherToPlain[26]
);

#endif
