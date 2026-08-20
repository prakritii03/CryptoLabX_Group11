#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <cctype>
using namespace std;

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

unordered_set<string> loadDictionary(string filename) {
    unordered_set<string> dictionary;
    ifstream file(filename);
    string word;

    while (file >> word) {
        for (char &ch : word)
            ch = toupper(ch);

        dictionary.insert(word);
    }

    return dictionary;
}

int scoreText(string text, unordered_set<string> &dictionary) {
    stringstream ss(text);
    string word;
    int score = 0;

    while (ss >> word) {
        string cleaned = "";

        for (char ch : word) {
            if (isalpha(ch))
                cleaned += toupper(ch);
        }

        if (dictionary.count(cleaned))
            score++;
    }

    return score;
}

int main() {
    string ciphertext;

    cout << "Enter ciphertext: ";
    getline(cin, ciphertext);

    auto dictionary = loadDictionary(
        "attacks/shift_cipher_attack/dictionary/english_words.txt"
    );

    int bestKey = 0;
    int bestScore = -1;
    string bestText = "";

    for (int key = 0; key < 26; key++) {
        string plaintext = decryptText(ciphertext, key);
        int score = scoreText(plaintext, dictionary);

        cout << "Key " << key
             << " | Score: " << score
             << " | " << plaintext << endl;

        if (score > bestScore) {
            bestScore = score;
            bestKey = key;
            bestText = plaintext;
        }
    }

    cout << "\nPredicted Key: " << bestKey << endl;
    cout << "Predicted Plaintext: " << bestText << endl;
    cout << "Dictionary Score: " << bestScore << endl;

    return 0;
}
