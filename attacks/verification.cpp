#include "verification.h"

#include <iostream>

using namespace std;

bool isLetterVerification(char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

char toUpperVerification(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }

    return c;
}

bool build_encryption_key(
    char cipherToPlain[26],
    char plainToCipher[26]
)
{
    for (int i = 0; i < 26; i++)
    {
        plainToCipher[i] = '?';
    }

    for (int i = 0; i < 26; i++)
    {
        if (cipherToPlain[i] == '?')
        {
            return false;
        }

        int plainIndex =
            cipherToPlain[i] - 'A';

        if (plainToCipher[plainIndex] != '?')
        {
            return false;
        }

        plainToCipher[plainIndex] =
            'A' + i;
    }

    return true;
}

string re_encrypt(
    const string& plaintext,
    char plainToCipher[26]
)
{
    string ciphertext;

    for (char ch : plaintext)
    {
        if (isLetterVerification(ch))
        {
            char upper =
                toUpperVerification(ch);

            int index =
                upper - 'A';

            if (plainToCipher[index] == '?')
            {
                ciphertext += '_';
            }
            else
            {
                ciphertext +=
                    plainToCipher[index];
            }
        }
        else
        {
            ciphertext += ch;
        }
    }

    return ciphertext;
}

bool verify_solution(
    const string& ciphertext,
    const string& plaintext,
    char cipherToPlain[26]
)
{
    char plainToCipher[26];

    cout << "\n========================================\n";
    cout << "SOLUTION VERIFICATION\n";
    cout << "========================================\n";

    if (!build_encryption_key(
            cipherToPlain,
            plainToCipher
        ))
    {
        cout << "\nVerification cannot be completed.\n";
        cout << "Substitution key is incomplete or invalid.\n";

        return false;
    }

    string reencrypted =
        re_encrypt(
            plaintext,
            plainToCipher
        );

    cout << "\nOriginal Ciphertext:\n";
    cout << ciphertext << '\n';

    cout << "\nRe-encrypted Ciphertext:\n";
    cout << reencrypted << '\n';

    if (ciphertext == reencrypted)
    {
        cout << "\nVERIFICATION SUCCESSFUL\n";
        cout << "Recovered plaintext and substitution key are correct.\n";

        return true;
    }

    cout << "\nVERIFICATION FAILED\n";
    cout << "Re-encrypted text does not match original ciphertext.\n";

    return false;
}
