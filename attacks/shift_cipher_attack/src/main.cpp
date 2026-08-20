#include <iostream>
#include <string>
using namespace std;

string encryptText(string text, int key) {
    string result = "";

    for (char ch : text) {
        if (ch >= 'A' && ch <= 'Z') {
            char encrypted = (ch - 'A' + key) % 26 + 'A';
            result += encrypted;
        }
        else if (ch >= 'a' && ch <= 'z') {
            char encrypted = (ch - 'a' + key) % 26 + 'a';
            result += encrypted;
        }
        else {
            result += ch;
        }
    }

    return result;
}

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

int main() {
    int choice;

    cout << "Shift Cipher\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "3. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore();

    if (choice == 1) {
        string plaintext;
        int key;

        cout << "Enter plaintext: ";
        getline(cin, plaintext);

        cout << "Enter key: ";
        cin >> key;

        key = key % 26;

        cout << "Ciphertext: " << encryptText(plaintext, key) << endl;
    }
    else if (choice == 2) {
        string ciphertext;
        int key;

        cout << "Enter ciphertext: ";
        getline(cin, ciphertext);

        cout << "Enter key: ";
        cin >> key;

        key = key % 26;

        cout << "Plaintext: " << decryptText(ciphertext, key) << endl;
    }
    else if (choice == 3) {
        cout << "Exiting...\n";
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
