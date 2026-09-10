#include "preprocessing.h"
#include <cctype>

std::string clean_ciphertext(const std::string& ciphertext)
{
    std::string cleaned;

    for (char ch : ciphertext)
    {
        if (std::isalpha(static_cast<unsigned char>(ch)))
        {
            cleaned += static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );
        }
    }

    return cleaned;
}