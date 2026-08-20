#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

string decryptText(string text, int key) {
    string result = "";

    for (char ch : text) {
        if (ch >= 'A' && ch <= 'Z') {
            char decrypted = (ch - 'A' - key + 26) % 26 + 'A';
            result += decrypted;
        }
        else if (ch >= 'a' && ch <= 'z') {
            char decrypted = (ch - 'a' - key + 26) % 26 + 'a';
            result += decrypted;
        }
        else {
            result += ch;
        }
    }

    return result;
}

double chiSquareScore(string text) {
    int observed[26] = {0};
    int totalLetters = 0;

    for (char ch : text) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            observed[ch - 'A']++;
            totalLetters++;
        }
    }

    if (totalLetters == 0)
        return 1e9;

    double score = 0.0;

    for (int i = 0; i < 26; i++) {
        double expected = totalLetters * englishFreq[i] / 100.0;

        if (expected > 0) {
            score += pow(observed[i] - expected, 2) / expected;
        }
    }

    return score;
}

int main() {
    string ciphertext;

    cout << "Enter ciphertext: ";
    getline(cin, ciphertext);

    int bestKey = 0;
    double bestScore = 1e9;
    string bestText = "";

    cout << "\nChi-Square Analysis\n";

    for (int key = 0; key < 26; key++) {
        string plaintext = decryptText(ciphertext, key);
        double score = chiSquareScore(plaintext);

        cout << "Key " << key
             << " | Score: " << score
             << " | " << plaintext << endl;

        if (score < bestScore) {
            bestScore = score;
            bestKey = key;
            bestText = plaintext;
        }
    }

    cout << "\nPredicted Key: " << bestKey << endl;
    cout << "Predicted Plaintext: " << bestText << endl;
    cout << "Chi-Square Score: " << bestScore << endl;

    return 0;
}
