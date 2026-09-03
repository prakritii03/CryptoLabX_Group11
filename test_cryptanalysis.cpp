#include <iostream>
#include <string>

#include "attacks/cryptanalysis.h"

using namespace std;

int main()
{
    string ciphertext = "KHOOR ZRUOG";

    char cipherToPlain[26];

    for (int i = 0; i < 26; i++)
    {
        cipherToPlain[i] = '?';
    }

    iterative_cryptanalysis(
        ciphertext,
        cipherToPlain
    );

    return 0;
}
