#include "encryption.h"
#include <cctype>

using namespace std;

string encryptText(const string& plaintext, const string& key)
{
    string ciphertext = "";

    for (char ch : plaintext)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            ciphertext += key[ch - 'A'];
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            char encrypted = key[ch - 'a'];
            ciphertext += tolower(
                static_cast<unsigned char>(encrypted)
            );
        }
        else
        {
            // Keep spaces, numbers and punctuation unchanged
            ciphertext += ch;
        }
    }

    return ciphertext;
}