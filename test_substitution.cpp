#include <iostream>
#include <string>

#include "attacks/substitution.h"

using namespace std;

int main()
{
    string ciphertext =
        "KHOOR ZRUOG";

    char cipherToPlain[26];

    for (int i = 0; i < 26; i++)
    {
        cipherToPlain[i] = '?';
    }

    cipherToPlain['K' - 'A'] = 'H';
    cipherToPlain['H' - 'A'] = 'E';
    cipherToPlain['O' - 'A'] = 'L';
    cipherToPlain['R' - 'A'] = 'O';

    display_partial_plaintext(
        ciphertext,
        cipherToPlain
    );

    return 0;
}
