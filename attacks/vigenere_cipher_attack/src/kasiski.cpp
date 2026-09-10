#include "kasiski.h"

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

map<string, vector<int>>
find_repeated_patterns(const string& ciphertext, int minLength, int maxLength)
{
    map<string, vector<int>> patterns;

    for (int length = minLength; length <= maxLength; length++)
    {
        for (int i = 0; i + length <= static_cast<int>(ciphertext.length()); i++)
        {
            string pattern = ciphertext.substr(i, length);

            if (patterns.find(pattern) == patterns.end())
            {
                patterns[pattern] = {};
            }

            patterns[pattern].push_back(i);
        }
    }

    map<string, vector<int>> repeated;

    for (const auto& entry : patterns)
    {
        if (entry.second.size() >= 2)
        {
            repeated[entry.first] = entry.second;
        }
    }

    return repeated;
}

map<string, vector<int>>
calculate_distances(const map<string, vector<int>>& patterns)
{
    map<string, vector<int>> distances;

    for (const auto& entry : patterns)
    {
        const vector<int>& positions = entry.second;

        for (size_t i = 0; i < positions.size(); i++)
        {
            for (size_t j = i + 1; j < positions.size(); j++)
            {
                distances[entry.first].push_back(
                    positions[j] - positions[i]
                );
            }
        }
    }

    return distances;
}

map<int, int>
find_factors(const map<string, vector<int>>& distances, int maxKeyLength)
{
    map<int, int> factorFrequency;

    for (const auto& entry : distances)
    {
        for (int distance : entry.second)
        {
            for (int factor = 2; factor <= maxKeyLength; factor++)
            {
                if (distance % factor == 0)
                {
                    factorFrequency[factor]++;
                }
            }
        }
    }

    return factorFrequency;
}

vector<int>
kasiski_analysis(const string& ciphertext, int maxKeyLength)
{
    auto patterns = find_repeated_patterns(ciphertext, 3, 5);
    auto distances = calculate_distances(patterns);
    auto factors = find_factors(distances, maxKeyLength);

    vector<pair<int, int>> ranked;

    for (const auto& entry : factors)
    {
        ranked.push_back({entry.first, entry.second});
    }

    sort(
        ranked.begin(),
        ranked.end(),
        [](const pair<int, int>& a, const pair<int, int>& b)
        {
            if (a.second != b.second)
                return a.second > b.second;

            return a.first < b.first;
        }
    );

    cout << "\n===== KASISKI ANALYSIS =====\n";

    cout << "\nRepeated Patterns:\n";

    int patternCount = 0;

    for (const auto& entry : patterns)
    {
        cout << entry.first << " : ";

        for (int position : entry.second)
        {
            cout << position << " ";
        }

        cout << "\n";

        patternCount++;

        if (patternCount >= 20)
            break;
    }

    cout << "\nDistances:\n";

    int distanceCount = 0;

    for (const auto& entry : distances)
    {
        if (entry.second.empty())
            continue;

        cout << entry.first << " : ";

        for (int distance : entry.second)
        {
            cout << distance << " ";
        }

        cout << "\n";

        distanceCount++;

        if (distanceCount >= 20)
            break;
    }

    cout << "\nFactor Frequencies:\n";

    for (const auto& entry : ranked)
    {
        cout << entry.first << " -> " << entry.second << "\n";
    }

    vector<int> candidates;

    for (size_t i = 0; i < ranked.size() && i < 10; i++)
    {
        candidates.push_back(ranked[i].first);
    }

    return candidates;
}

double calculate_ic(const string& text)
{
    if (text.length() < 2)
        return 0.0;

    int frequency[26] = {0};

    for (char ch : text)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            frequency[ch - 'A']++;
        }
    }

    double numerator = 0.0;

    for (int i = 0; i < 26; i++)
    {
        numerator += frequency[i] * (frequency[i] - 1);
    }

    double denominator =
        static_cast<double>(text.length()) *
        (text.length() - 1);

    return numerator / denominator;
}

vector<string>
split_into_groups(const string& ciphertext, int keyLength)
{
    vector<string> groups(keyLength);

    for (size_t i = 0; i < ciphertext.length(); i++)
    {
        groups[i % keyLength] += ciphertext[i];
    }

    return groups;
}