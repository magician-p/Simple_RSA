#include <iomanip>
#include "RSA.h"
#include <iostream>

using namespace std;

int main() {
    RSA rsa;
    const pair<ll, ll> publicKey = rsa.getPublicKey();
    const pair<ll, ll> privateKey = rsa.getPrivateKey();
    cout << setw(13) << right << "Public Key: " << publicKey.first << " " << publicKey.second << endl;
    cout << setw(13) << right << "Private Key: " << privateKey.first << " " << privateKey.second << endl;
    vector<ll> cipherText;
    string plainText="wanghao";
    RSA::en_RSA(plainText, cipherText, privateKey);
    string de_plaintext;
    RSA::de_RSA(cipherText, de_plaintext, publicKey);
    cout << de_plaintext << endl;
    return 0;
}
