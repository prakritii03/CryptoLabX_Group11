#include <iostream>
#include <fstream>
#include <string>

#include "cryptanalysis.h"
#include "substitution.h"
#include "verification.h"
using namespace std;

bool isLetter(char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

char toUpperManual(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }

    return c;
}

string readFile(const string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        return "";
    }

    string text;
    string line;

    while (getline(file, line))
    {
        text += line;
        text += '\n';
    }

    return text;
}

string getPattern(const string& word)
{
    int mapping[26];

    for (int i = 0; i < 26; i++)
    {
        mapping[i] = -1;
    }

    int nextNumber = 0;
    string pattern;

    for (char ch : word)
    {
        ch = toUpperManual(ch);

        if (!isLetter(ch))
        {
            continue;
        }

        int index = ch - 'A';

        if (mapping[index] == -1)
        {
            mapping[index] = nextNumber;
            nextNumber++;
        }

        if (!pattern.empty())
        {
            pattern += "-";
        }

        pattern += to_string(mapping[index]);
    }

    return pattern;
}

void pattern_analysis(const string& ciphertext)
{
    string words[5000];
    int wordCount = 0;
    string currentWord;

    for (int i = 0; i <= (int)ciphertext.size(); i++)
    {
        char ch = (i < (int)ciphertext.size()) ? ciphertext[i] : ' ';

        if (isLetter(ch))
        {
            currentWord += toUpperManual(ch);
        }
        else
        {
            if (!currentWord.empty())
            {
                if (wordCount < 5000)
                {
                    words[wordCount++] = currentWord;
                }

                currentWord.clear();
            }
        }
    }

    cout << "\n========================================\n";
    cout << "PATTERN ANALYSIS\n";
    cout << "========================================\n\n";

    cout << "Word\tPattern\n";

    for (int i = 0; i < wordCount; i++)
    {
        cout << words[i] << "\t" << getPattern(words[i]) << '\n';
    }

    cout << "\nRepeated Letter Patterns\n";

    bool found = false;

    for (int i = 0; i < wordCount; i++)
    {
        string pattern = getPattern(words[i]);
        bool alreadyPrinted = false;

        for (int j = 0; j < i; j++)
        {
            if (getPattern(words[j]) == pattern)
            {
                alreadyPrinted = true;
                break;
            }
        }

        if (alreadyPrinted)
        {
            continue;
        }

        int count = 0;

        for (int j = 0; j < wordCount; j++)
        {
            if (getPattern(words[j]) == pattern)
            {
                count++;
            }
        }

        if (count > 1)
        {
            cout << "\nPattern " << pattern << " : ";

            for (int j = 0; j < wordCount; j++)
            {
                if (getPattern(words[j]) == pattern)
                {
                    cout << words[j] << " ";
                }
            }

            cout << '\n';
            found = true;
        }
    }

    if (!found)
    {
        cout << "No repeated patterns found.\n";
    }
}

int main(int argc, char* argv[])
{
    string filename = "outputs/ciphertext.txt";

    if (argc > 1)
    {
        filename = argv[1];
    }

    string ciphertext = readFile(filename);

    if (ciphertext.empty())
    {
        cout << "Unable to read ciphertext file.\n";
        return 1;
    }

    cout << "\n========================================\n";
    cout << "MONOALPHABETIC CIPHER CRYPTANALYSIS\n";
    cout << "========================================\n";

    cout << "\nCiphertext:\n";
    cout << ciphertext << '\n';

    pattern_analysis(ciphertext);

    char cipherToPlain[26];

    for (int i = 0; i < 26; i++)
    {
        cipherToPlain[i] = '?';
    }

    iterative_cryptanalysis(
        ciphertext,
        cipherToPlain
    );

    string plaintext =
        apply_substitution(
            ciphertext,
            cipherToPlain
        );

    cout << "\n========================================\n";
    cout << "FINAL RESULTS\n";
    cout << "========================================\n";

    cout << "\nRecovered Plaintext:\n";
    cout << plaintext << '\n';

    recover_substitution_key(
        cipherToPlain
    );

    verify_solution(
        ciphertext,
        plaintext,
        cipherToPlain
    );

    return 0;
}
