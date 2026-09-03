#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

std::string encryptText(
    const std::string& plaintext,
    const std::string& key
);

#endif