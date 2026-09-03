#include <iostream>
#include <fstream>
#include <string>

#include "encryption.h"
#include "frequency_analysis.h"
#include "word_frequency.h"

using namespace std;

int main()
{
 
    cout << "   MONOALPHABETIC SUBSTITUTION CIPHER\n";
    // STEP 1: Read plaintext

    ifstream inputFile("../plaintext.txt");

    if (!inputFile)
    {
        cout << "Error: Could not open plaintext.txt\n";
        return 1;
    }

    string plaintext;
    string line;

    while (getline(inputFile, line))
    {
        plaintext += line;
        plaintext += '\n';
    }

    inputFile.close();

    cout << "\nPlaintext loaded successfully.\n";

    // STEP 2: Define substitution key

    string key =
        "QWERTYUIOPASDFGHJKLZXCVBNM";

    cout << "\nEncryption Key:\n";
    cout << "Plain : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    cout << "Cipher: " << key << "\n";

    // STEP 3: Encrypt plaintext

    string ciphertext =
        encryptText(plaintext, key);

    cout << "               CIPHERTEXT\n";

    cout << ciphertext << "\n";

    // STEP 4: Save ciphertext

    ofstream outputFile(
        "../outputs/ciphertext.txt"
    );

    if (!outputFile)
    {
        cout << "Error: Could not create ciphertext.txt\n";
        return 1;
    }

    outputFile << ciphertext;
    outputFile.close();

    cout << "\nCiphertext saved successfully.\n";

    // STEP 5: Frequency Analysis

    frequency_analysis(ciphertext);

    // STEP 6: Word Frequency Analysis


    word_frequency_analysis(ciphertext);

    return 0;
}