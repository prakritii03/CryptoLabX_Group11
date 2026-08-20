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
    string text;
    int key;
    int choice;

    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore();

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    key = key % 26;

    if (choice == 1)
        cout << "Result: " << encryptText(text, key) << endl;
    else if (choice == 2)
        cout << "Result: " << decryptText(text, key) << endl;
    else
        cout << "Invalid choice\n";

    return 0;
}
