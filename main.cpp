#include <iomanip>
#include "RSA.h"
#include <iostream>

using namespace std;

int main() {
    RSA rsa;
    const pair<ull, ull> publicKey = rsa.getPublicKey();
    const pair<ull, ull> privateKey = rsa.getPrivateKey();
    cout << "Public Key: " << publicKey.first << " " << publicKey.second << endl;
    cout << "Private Key: " << privateKey.first << " " << privateKey.second << endl;
    vector<ull> cipherText;
    const string plainText("wang hao");
    cout << "Plaintext: " << plainText << endl;
    RSA::en_RSA(plainText, cipherText, privateKey);
    cout << "Ciphertext: ";
    for (auto i : cipherText) cout << i << " ";
    cout<<endl;
    string de_plaintext;
    RSA::de_RSA(cipherText, de_plaintext, publicKey);
    cout << "De_plaintext: " << de_plaintext << endl;
    return 0;
}
