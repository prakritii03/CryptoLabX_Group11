#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "preprocessing.h"
#include "kasiski.h"
#include "frequency.h"
#include "vigenere.h"

using namespace std;

string read_file(const string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "Error opening file: " << filename << "\n";
        return "";
    }

    string content;
    string line;

    while (getline(file, line))
    {
        content += line;
        content += '\n';
    }

    return content;
}

double average_ic(const vector<string>& groups)
{
    if (groups.empty())
        return 0.0;

    double total = 0.0;

    for (const string& group : groups)
    {
        total += calculate_ic(group);
    }

    return total / groups.size();
}

int choose_key_length(
    const string& ciphertext,
    const vector<int>& candidates
)
{
    if (candidates.empty())
        return 1;

    int bestLength = candidates[0];
    double bestIC = -1.0;

    cout << "\n===== IC ANALYSIS =====\n";

    for (int keyLength : candidates)
    {
        if (keyLength <= 0)
            continue;

        vector<string> groups =
            split_into_groups(ciphertext, keyLength);

        double ic = average_ic(groups);

        cout << "Key Length "
             << setw(2)
             << keyLength
             << " -> Average IC = "
             << fixed
             << setprecision(4)
             << ic
             << "\n";

        if (ic > bestIC)
        {
            bestIC = ic;
            bestLength = keyLength;
        }
    }

    return bestLength;
}

int main()
{
    cout << "========================================\n";
    cout << " VIGENERE CIPHER CRYPTANALYSIS\n";
    cout << " KASISKI + FREQUENCY ANALYSIS\n";
    cout << "========================================\n";

    cout << "\nSelect ciphertext:\n";
    cout << "1. Ciphertext 1 - Odd Group\n";
    cout << "2. Ciphertext 2 - Even Group\n";
    cout << "\nEnter choice: ";

    int choice;
    cin >> choice;

    string filename;

    if (choice == 1)
    {
        filename = "testcases/ciphertext_odd.txt";
    }
    else if (choice == 2)
    {
        filename = "testcases/ciphertext_even.txt";
    }
    else
    {
        cout << "Invalid choice.\n";
        return 1;
    }

    string originalText = read_file(filename);

    if (originalText.empty())
    {
        return 1;
    }

    string ciphertext =
        clean_ciphertext(originalText);

    cout << "\n===== PREPROCESSING =====\n";

    cout << "Original characters: "
         << originalText.length()
         << "\n";

    cout << "Clean ciphertext length: "
         << ciphertext.length()
         << "\n";

    cout << "Clean ciphertext:\n";
    cout << ciphertext << "\n";

    int maxKeyLength = 20;

    vector<int> candidates =
        kasiski_analysis(
            ciphertext,
            maxKeyLength
        );

    cout << "\nCandidate Key Lengths:\n";

    for (int candidate : candidates)
    {
        cout << candidate << " ";
    }

    cout << "\n";

    int estimatedKeyLength =
        choose_key_length(
            ciphertext,
            candidates
        );

    cout << "\n========================================\n";
    cout << "Estimated Key Length: "
         << estimatedKeyLength
         << "\n";
    cout << "========================================\n";

    vector<string> groups =
        split_into_groups(
            ciphertext,
            estimatedKeyLength
        );

    display_frequency_table(groups);

    string recoveredKey =
        find_key(groups);

    cout << "\n===== KEY RECOVERY =====\n";
    cout << "Recovered Key: "
         << recoveredKey
         << "\n";

    string plaintext =
        vigenere_decrypt(
            ciphertext,
            recoveredKey
        );

    cout << "\n===== RECOVERED PLAINTEXT =====\n";
    cout << plaintext << "\n";

    string regeneratedCiphertext =
        vigenere_encrypt(
            plaintext,
            recoveredKey
        );

    cout << "\n===== VERIFICATION =====\n";

    bool result =
        verify(
            ciphertext,
            regeneratedCiphertext
        );

    if (result)
    {
        cout << "Verification: PASS\n";
        cout << "Re-encrypted ciphertext matches "
                "the original ciphertext.\n";
    }
    else
    {
        cout << "Verification: FAIL\n";
        cout << "Re-encrypted ciphertext does not "
                "match the original ciphertext.\n";
    }

    return 0;
}