//
// Created by 98314 on 2026/5/5.
//

#include "RSA.h"
#include <random>
#include <chrono>
#include <iostream>
using namespace std;
RSA::RSA() {
    this->arg_n = 0;
    this->arg_e = 0;
    this->arg_d = 0;
    gen_Key();
}

ull RSA::exGcd(const ull &a, const ull &b, ull &x, ull &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ull x_1, y_1;

    ull g = exGcd(b, a % b, x_1, y_1);

    x = y_1;
    y = x_1 - (a / b) * y_1;

    return g;
}

ull RSA::getMulInverse(const ull &e, const ull &z) {
    ull x = 0, y=0;
    exGcd(e, z, x, y);
    return (x % z + z) % z;
}

ull RSA::quickMulMod(const ull &a, const ull &b, const ull &c) {
    ull res = 0;
    ull a_temp = a % c;
    ull b_temp = b;
    while (b_temp > 0) {
        if (b_temp & 0x01) {
            res = (res + a_temp) % c;
        }
        a_temp = (a_temp * 2) % c;
        b_temp >>= 1;
    }
    return (res % c + c) % c;
}

ull RSA::quickPowMod(const ull &a, const ull &b, const ull &c) {
    ull res = 1;
    ull a_temp = a % c;
    ull b_temp = b;
    while (b_temp > 0) {
        if (b_temp & 0x01) {
            res = quickMulMod(res, a_temp, c);
        }
        a_temp = quickMulMod(a_temp, a_temp, c);
        b_temp >>= 1;
    }
    return (res % c + c) % c;
}

bool RSA::MiullerRabbin(const ull &p, const ull &a) {
    ull d = p - 1;
    ull r = 0;
    while ((d & 0x01) == 0) {
        d >>= 1;
        r++;
    }
    ull k = quickPowMod(a, d, p);
    if (k == 1) {
        return true;
    }
    for (int i = 0; i < r; i++) {
        if (k == p - 1) {
            return true;
        }
        k = quickPowMod(k, 2, p);
    }
    return false;
}

bool RSA::isPrime(const ull &n) {
    if (n < 3) {
        return n == 2;
    }
    if (n % 2 == 0) {
        return false;
    }
    bool prime_Flag = true;
    for (ull Jim_Sinclair[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}; ull a: Jim_Sinclair) {
        prime_Flag &= MiullerRabbin(n, a);
        if (!prime_Flag) {
            return false;
        }
    }
    return true;
}

ull RSA::getPrimeNum() {
    std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        ull random = generator();
        if (isPrime(random)) {
            return random;
        }
    }
}

void RSA::gen_Key() {
    std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());
    const ull p = getPrimeNum();
    const ull q = getPrimeNum();
    this->arg_n = p * q;
    const ull Euler_z = (p - 1) * (q - 1);
    ull x=0, y=0;
    std::uniform_int_distribution<ull> distribution(0, Euler_z);
    do {
        this->arg_e = distribution(generator);
        this->arg_d = getMulInverse(this->arg_e, Euler_z);
        cout<<"x"<<endl;
    } while (exGcd(this->arg_e, Euler_z, x, y) != 1 || quickMulMod(this->arg_e, this->arg_d, Euler_z)!=1);
    cout<<quickMulMod(this->arg_e, this->arg_d, Euler_z)<<endl;;
}

pair<ull, ull> RSA::getPublicKey() {
    return {this->arg_e, this->arg_n};
}

pair<ull, ull> RSA::getPrivateKey() {
    return {this->arg_d, this->arg_n};
}

void RSA::en_RSA(const string& plainText, vector<ull>& cipherText, const pair<ull, ull>& privateKey){
    for (const char str : plainText){
        cipherText.push_back(quickPowMod(str, privateKey.first, privateKey.second));
    }
}

void RSA::de_RSA(const vector<ull>& cipherText, string& de_plainText, const pair<ull, ull>& publicKey){
    for (ull str : cipherText){
        const ull de_str = quickPowMod(str, publicKey.first, publicKey.second);
        de_plainText += static_cast<char>(de_str);
    }
}
