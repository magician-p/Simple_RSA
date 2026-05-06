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

typedef unsigned long long ull;

class RSA {
public:
    RSA();

    pair<ull, ull> getPublicKey();

    pair<ull, ull> getPrivateKey();

    static void en_RSA(const string &plainText, vector<ull> &cipherText, const pair<ull, ull> &privateKey);

    static void de_RSA(const vector<ull> &cipherText, string &de_plainText, const pair<ull, ull> &publicKey);

private:
    static ull getPrimeNum();

    ull getMulInverse(const ull &e, const ull &z);

    ull exGcd(const ull &a, const ull &b, ull &x, ull &y);

    static ull quickMulMod(const ull &a, const ull &b, const ull &c);

    static ull quickPowMod(const ull &a, const ull &b, const ull &c);

    static bool MiullerRabbin(const ull &p, const ull &a);

    static bool isPrime(const ull &n);

    void gen_Key();

    ull arg_n;
    ull arg_e;
    ull arg_d;
};


#endif //RSA_H
