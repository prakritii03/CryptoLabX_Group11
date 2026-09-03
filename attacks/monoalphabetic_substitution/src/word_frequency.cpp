#include "word_frequency.h"

#include <iostream>
#include <map>
#include <cctype>

using namespace std;

void word_frequency_analysis(const string& ciphertext)
{
    map<string, int> wordCount;

    string currentWord = "";

    for (size_t i = 0; i <= ciphertext.length(); i++)
    {
        char ch;

        if (i < ciphertext.length())
        {
            ch = ciphertext[i];
        }
        else
        {
            // Force the last word to be processed
            ch = ' ';
        }

        if (isalpha(static_cast<unsigned char>(ch)))
        {
            currentWord +=
                toupper(static_cast<unsigned char>(ch));
        }
        else
        {
            if (!currentWord.empty())
            {
                wordCount[currentWord]++;
                currentWord = "";
            }
        }
    }

    cout << "        WORD FREQUENCY ANALYSIS\n";

    cout << "\nONE-LETTER WORDS\n";
    cout << "----------------\n";

    for (auto item : wordCount)
    {
        if (item.first.length() == 1)
        {
            cout << item.first
                 << " -> "
                 << item.second
                 << " occurrence(s)\n";
        }
    }

    cout << "\nTWO-LETTER WORDS\n";

    for (auto item : wordCount)
    {
        if (item.first.length() == 2)
        {
            cout << item.first
                 << " -> "
                 << item.second
                 << " occurrence(s)\n";
        }
    }

    cout << "\nTHREE-LETTER WORDS\n";

    for (auto item : wordCount)
    {
        if (item.first.length() == 3)
        {
            cout << item.first
                 << " -> "
                 << item.second
                 << " occurrence(s)\n";
        }
    }

    cout << "\nREPEATED WORDS\n";

    for (auto item : wordCount)
    {
        if (item.second > 1)
        {
            cout << item.first
                 << " -> "
                 << item.second
                 << " occurrences\n";
        }
    }
}