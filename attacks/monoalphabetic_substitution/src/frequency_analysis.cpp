#include "frequency_analysis.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

void frequency_analysis(const string& ciphertext)
{
    int frequency[26] = {0};
    int totalLetters = 0;

    for (char ch : ciphertext)
    {
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            ch = toupper(static_cast<unsigned char>(ch));

            frequency[ch - 'A']++;
            totalLetters++;
        }
    }

    vector<pair<char, int>> frequencies;

    for (int i = 0; i < 26; i++)
    {
        frequencies.push_back(
            {char('A' + i), frequency[i]}
        );
    }

    sort(
        frequencies.begin(),
        frequencies.end(),
        [](const pair<char, int>& a,
           const pair<char, int>& b)
        {
            return a.second > b.second;
        }
    );

    cout << "           FREQUENCY ANALYSIS\n";

    cout << left
         << setw(10) << "Letter"
         << setw(10) << "Count"
         << "Percentage\n";


    for (auto item : frequencies)
    {
        double percentage = 0.0;

        if (totalLetters > 0)
        {
            percentage =
                (static_cast<double>(item.second)
                 / totalLetters) * 100.0;
        }

        cout << left
             << setw(10) << item.first
             << setw(10) << item.second
             << fixed << setprecision(2)
             << percentage << "%\n";
    }

    cout << "\nTotal letters: "
         << totalLetters << "\n";

    cout << "\nMost frequent letters:\n";

    for (int i = 0; i < 5; i++)
    {
        cout << frequencies[i].first
             << " -> "
             << frequencies[i].second
             << " occurrences\n";
    }
}
