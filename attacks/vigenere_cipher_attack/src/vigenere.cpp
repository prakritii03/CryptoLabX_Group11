#include "vigenere.h"
#include "frequency.h"

#include <iostream>

using namespace std;

string find_key(
    const vector<string>& groups
)
{
    string key;

    for (const string& group : groups)
    {
        int shift = find_shift(group);

        key += static_cast<char>('A' + shift);
    }

    return key;
}

string vigenere_decrypt(
    const string& ciphertext,
    const string& key
)
{
    string plaintext;

    if (key.empty())
        return plaintext;

    for (size_t i = 0; i < ciphertext.length(); i++)
    {
        int c = ciphertext[i] - 'A';
        int k = key[i % key.length()] - 'A';

        int p = (c - k + 26) % 26;

        plaintext += static_cast<char>('A' + p);
    }

    return plaintext;
}

string vigenere_encrypt(
    const string& plaintext,
    const string& key
)
{
    string ciphertext;

    if (key.empty())
        return ciphertext;

    for (size_t i = 0; i < plaintext.length(); i++)
    {
        int p = plaintext[i] - 'A';
        int k = key[i % key.length()] - 'A';

        int c = (p + k) % 26;

        ciphertext += static_cast<char>('A' + c);
    }

    return ciphertext;
}

bool verify(
    const string& originalCiphertext,
    const string& regeneratedCiphertext
)
{
    return originalCiphertext == regeneratedCiphertext;
}
