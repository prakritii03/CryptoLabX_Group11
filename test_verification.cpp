#include <iostream>
#include <string>

#include "attacks/verification.h"

using namespace std;

int main()
{
    string plaintext = "HELLO WORLD";
    string ciphertext = "IFMMP XPSME";

    char cipherToPlain[26];
    char plainToCipher[26];

    for (int i = 0; i < 26; i++)
    {
        cipherToPlain[i] = 'A' + i;
    }

    for (int i = 0; i < 26; i++)
    {
        plainToCipher[i] = '?';
    }

    for (int i = 0; i < 26; i++)
    {
        int cipherIndex = (i + 1) % 26;

        cipherToPlain[cipherIndex] =
            'A' + i;
    }

    verify_solution(
        ciphertext,
        plaintext,
        cipherToPlain
    );

    return 0;
}
