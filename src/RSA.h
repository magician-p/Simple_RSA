//
// Created by 98314 on 2026/5/5.
//

#ifndef RSA_H
#define RSA_H
#include <vector>
#include <string>
using std::vector;
using std::pair;
using std::string;

typedef unsigned long long ll;

class RSA {
public:
    RSA();

    pair<ll, ll> getPublicKey();

    pair<ll, ll> getPrivateKey();

    void en_RSA(const string &plainText, vector<ll> &cipherText, const pair<ll, ll> &privateKey);

    void de_RSA(const vector<ll> &cipherText, string &de_plainText, const pair<ll, ll> &publicKey);

private:
    static ll getPrimeNum();

    ll getMulInverse(const ll &e, const ll &z);

    ll exGcd(const ll &a, const ll &b, ll &x, ll &y);

    ll exGcd(const ll &a, const ll &b);

    static ll quickMulMod(const ll &a, const ll &b, const ll &c);

    static ll quickPowMod(const ll &a, const ll &b, const ll &c);

    static bool MillerRabbin(const ll &p, const ll &a);

    static bool isPrime(const ll &n);

    void gen_Key();

    ll arg_n;
    ll arg_e;
    ll arg_d;
};


#endif //RSA_H
