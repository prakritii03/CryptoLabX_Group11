#include "frequency.h"

#include <iostream>
#include <cmath>

using namespace std;

array<int, 26>
frequency_analysis(const string& group)
{
    array<int, 26> frequency{};

    for (char ch : group)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            frequency[ch - 'A']++;
        }
    }

    return frequency;
}

int find_shift(const string& group)
{
    static const double englishFrequency[26] =
    {
        0.082,
        0.015,
        0.028,
        0.043,
        0.127,
        0.022,
        0.020,
        0.061,
        0.070,
        0.0015,
        0.0077,
        0.040,
        0.024,
        0.067,
        0.075,
        0.019,
        0.00095,
        0.060,
        0.063,
        0.091,
        0.028,
        0.0098,
        0.024,
        0.0015,
        0.020,
        0.00074
    };

    if (group.empty())
        return 0;

    auto observed = frequency_analysis(group);

    int n = static_cast<int>(group.length());

    double bestScore = 1e100;
    int bestShift = 0;

    for (int shift = 0; shift < 26; shift++)
    {
        double chiSquare = 0.0;

        for (int plainLetter = 0; plainLetter < 26; plainLetter++)
        {
            int cipherLetter = (plainLetter + shift) % 26;

            double expected =
                englishFrequency[plainLetter] * n;

            double actual = observed[cipherLetter];

            if (expected > 0)
            {
                double difference = actual - expected;

                chiSquare +=
                    (difference * difference) / expected;
            }
        }

        if (chiSquare < bestScore)
        {
            bestScore = chiSquare;
            bestShift = shift;
        }
    }

    return bestShift;
}

void display_frequency_table(
    const vector<string>& groups
)
{
    cout << "\n===== FREQUENCY ANALYSIS =====\n";

    for (size_t i = 0; i < groups.size(); i++)
    {
        auto frequency = frequency_analysis(groups[i]);

        cout << "\nGroup " << i + 1 << "\n";
        cout << "Length: " << groups[i].length() << "\n";

        for (int j = 0; j < 26; j++)
        {
            cout << static_cast<char>('A' + j)
                 << " : "
                 << frequency[j]
                 << "\n";
        }

        cout << "Estimated Shift: "
             << find_shift(groups[i])
             << "\n";
    }
}
