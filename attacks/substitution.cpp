#include "substitution.h"

#include <iostream>

using namespace std;

bool isLetterSubstitution(char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

char toUpperSubstitution(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }

    return c;
}

string apply_substitution(
    const string& ciphertext,
    char cipherToPlain[26]
)
{
    string result;

    for (char ch : ciphertext)
    {
        if (isLetterSubstitution(ch))
        {
            char upper =
                toUpperSubstitution(ch);

            int index =
                upper - 'A';

            if (cipherToPlain[index] == '?')
            {
                result += '_';
            }
            else
            {
                result +=
                    cipherToPlain[index];
            }
        }
        else
        {
            result += ch;
        }
    }

    return result;
}

void display_partial_plaintext(
    const string& ciphertext,
    char cipherToPlain[26]
)
{
    string partialPlaintext =
        apply_substitution(
            ciphertext,
            cipherToPlain
        );

    cout << "\n========================================\n";
    cout << "PARTIAL PLAINTEXT\n";
    cout << "========================================\n\n";

    cout << partialPlaintext << '\n';

    cout << "\nCurrent Substitutions\n";

    bool found = false;

    for (int i = 0; i < 26; i++)
    {
        if (cipherToPlain[i] != '?')
        {
            cout << (char)('A' + i)
                 << " -> "
                 << cipherToPlain[i]
                 << '\n';

            found = true;
        }
    }

    if (!found)
    {
        cout << "No substitutions applied.\n";
    }
}
