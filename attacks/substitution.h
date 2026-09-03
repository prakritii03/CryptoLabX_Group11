#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include <string>

std::string apply_substitution(
    const std::string& ciphertext,
    char cipherToPlain[26]
);

void display_partial_plaintext(
    const std::string& ciphertext,
    char cipherToPlain[26]
);

#endif
