#include "cryptanalysis.h"
#include "substitution.h"

#include <iostream>

using namespace std;

bool isLetterCryptanalysis(char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

char toUpperCryptanalysis(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }

    return c;
}

bool plainLetterAlreadyUsed(
    char cipherToPlain[26],
    char plainLetter,
    int currentIndex
)
{
    for (int i = 0; i < 26; i++)
    {
        if (i != currentIndex &&
            cipherToPlain[i] == plainLetter)
        {
            return true;
        }
    }

    return false;
}

void recover_plaintext(
    const string& ciphertext,
    char cipherToPlain[26]
)
{
    string plaintext =
        apply_substitution(
            ciphertext,
            cipherToPlain
        );

    cout << "\n========================================\n";
    cout << "RECOVERED PLAINTEXT\n";
    cout << "========================================\n\n";

    cout << plaintext << '\n';
}

void recover_substitution_key(
    char cipherToPlain[26]
)
{
    cout << "\n========================================\n";
    cout << "RECOVERED SUBSTITUTION KEY\n";
    cout << "========================================\n\n";

    cout << "Cipher : ";

    for (int i = 0; i < 26; i++)
    {
        cout << (char)('A' + i);
    }

    cout << "\nPlain  : ";

    for (int i = 0; i < 26; i++)
    {
        if (cipherToPlain[i] == '?')
        {
            cout << '_';
        }
        else
        {
            cout << cipherToPlain[i];
        }
    }

    cout << "\n\nDetailed Mapping\n";

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
        cout << "No substitutions recovered.\n";
    }
}

void iterative_cryptanalysis(
    const string& ciphertext,
    char cipherToPlain[26]
)
{
    while (true)
    {
        int choice;

        cout << "\n========================================\n";
        cout << "ITERATIVE CRYPTANALYSIS\n";
        cout << "========================================\n\n";

        cout << "1. Display partial plaintext\n";
        cout << "2. Test substitution hypothesis\n";
        cout << "3. Remove substitution\n";
        cout << "4. Recover plaintext\n";
        cout << "5. Recover substitution key\n";
        cout << "6. Exit\n";

        cout << "\nEnter choice: ";

        cin >> choice;

        if (choice == 1)
        {
            display_partial_plaintext(
                ciphertext,
                cipherToPlain
            );
        }

        else if (choice == 2)
        {
            char cipherLetter;
            char plainLetter;

            cout << "Enter ciphertext letter: ";
            cin >> cipherLetter;

            cout << "Enter plaintext letter: ";
            cin >> plainLetter;

            cipherLetter =
                toUpperCryptanalysis(cipherLetter);

            plainLetter =
                toUpperCryptanalysis(plainLetter);

            if (!isLetterCryptanalysis(cipherLetter) ||
                !isLetterCryptanalysis(plainLetter))
            {
                cout << "Invalid input.\n";

                continue;
            }

            int index =
                cipherLetter - 'A';

            if (plainLetterAlreadyUsed(
                    cipherToPlain,
                    plainLetter,
                    index
                ))
            {
                cout << "Plaintext letter is already assigned.\n";

                continue;
            }

            char oldValue =
                cipherToPlain[index];

            cipherToPlain[index] =
                plainLetter;

            display_partial_plaintext(
                ciphertext,
                cipherToPlain
            );

            char decision;

            cout << "\nAccept hypothesis? (Y/N): ";

            cin >> decision;

            decision =
                toUpperCryptanalysis(decision);

            if (decision == 'Y')
            {
                cout << "Hypothesis accepted.\n";
            }
            else
            {
                cipherToPlain[index] =
                    oldValue;

                cout << "Hypothesis rejected.\n";
            }
        }

        else if (choice == 3)
        {
            char cipherLetter;

            cout << "Enter ciphertext letter: ";

            cin >> cipherLetter;

            cipherLetter =
                toUpperCryptanalysis(cipherLetter);

            if (!isLetterCryptanalysis(cipherLetter))
            {
                cout << "Invalid input.\n";

                continue;
            }

            cipherToPlain[
                cipherLetter - 'A'
            ] = '?';

            cout << "Substitution removed.\n";
        }

        else if (choice == 4)
        {
            recover_plaintext(
                ciphertext,
                cipherToPlain
            );
        }

        else if (choice == 5)
        {
            recover_substitution_key(
                cipherToPlain
            );
        }

        else if (choice == 6)
        {
            cout << "Cryptanalysis completed.\n";

            break;
        }

        else
        {
            cout << "Invalid choice.\n";
        }
    }
}
