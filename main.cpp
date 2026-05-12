#include <fstream>
#include "RSA.h"
#include <iostream>
#include <sstream>

using namespace std;
void savePublicKey(const pair<ull, ull> &publicKey, const string &publicKeyFileName) {
    ofstream fileName(publicKeyFileName);
    if (!fileName) {
        cout << "Error: Can't open file " << publicKeyFileName << endl;
        exit(0);
    }
    fileName << publicKey.first << endl;
    fileName << publicKey.second << endl;
    fileName.close();
}
void savePrivateKey(const pair<ull, ull> &privateKey, const string &privateKeyFileName) {
    ofstream fileName(privateKeyFileName);
    if (!fileName) {
        cout << "Error: Can't open file" << privateKeyFileName << endl;
        exit(0);
    }
    fileName << privateKey.first << endl;
    fileName << privateKey.second << endl;
    fileName.close();
}
void en_RSA(const string &plaintextFileName, const string &privateKeyFileName, const string &ciphertextFileName) {
    ifstream privateFile(privateKeyFileName);
    ifstream plainFile(plaintextFileName);
    ofstream cipherFile(ciphertextFileName);
    if (!privateFile) {
        cout << "Error: Can't open file " << privateKeyFileName << endl;
        exit(0);
    }
    if (!plainFile) {
        cout << "Error: Can't open file " << plaintextFileName << endl;
    }
    if (!cipherFile) {
        cout << "Error: Can't open file " << ciphertextFileName << endl;
    }

    pair<ull, ull> privateKey;
    privateFile>>privateKey.first;
    privateFile>>privateKey.second;
    privateFile.close();

    for (string line; getline(plainFile, line);) {
        vector<ull> cipherText;
        RSA::en_RSA(line, cipherText, privateKey);
        for (ull c:cipherText) {
            cipherFile << c << " ";
        }
        cipherFile<<endl;
    }

    plainFile.close();
    cipherFile.close();
}
void de_RSA(const string &ciphertextFileName, const string &publicKeyFileName, const string &de_plaintextFileName) {
    ifstream cipherFile(ciphertextFileName);
    ifstream publicFile(publicKeyFileName);
    ofstream de_plainFile(de_plaintextFileName);
    if (!cipherFile) {
        cout << "Error: Can't open file " << ciphertextFileName << endl;
        exit(0);
    }
    if (!publicFile) {
        cout << "Error: Can't open file " << publicKeyFileName << endl;
        exit(0);
    }
    if (!de_plainFile) {
        cout << "Error: Can't open file " << de_plaintextFileName << endl;
        exit(0);
    }

    pair<ull, ull> publicKey;
    publicFile>>publicKey.first;
    publicFile>>publicKey.second;
    publicFile.close();

    for (string line; getline(cipherFile, line); ) {
        vector<ull> ciphertext;
        stringstream sstr(line);
        for (ull s; sstr >> s; ) {
            ciphertext.push_back(s);
        }
        string de_plaintext;
        RSA::de_RSA(ciphertext, de_plaintext, publicKey);
        de_plainFile << de_plaintext << endl;
    }

    cipherFile.close();
    de_plainFile.close();
}
int main() {
    string publicKeyFileName("../data/publicKey.txt");
    string privateKeyFileName("../data/privateKey.txt");
    string plaintextFileName("../data/plaintext.txt");
    string ciphertextFileName("../data/ciphertext.txt");
    string de_plaintextFileName("../data/de_plaintext.txt");

    RSA rsa;

    const pair<ull, ull> publicKey = rsa.getPublicKey();
    const pair<ull, ull> privateKey = rsa.getPrivateKey();

    savePublicKey(publicKey, publicKeyFileName);
    savePrivateKey(privateKey, privateKeyFileName);

    en_RSA(plaintextFileName, privateKeyFileName, ciphertextFileName);
    de_RSA(ciphertextFileName, publicKeyFileName, de_plaintextFileName);

    return 0;
}
