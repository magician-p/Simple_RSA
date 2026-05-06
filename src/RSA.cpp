//
// Created by 98314 on 2026/5/5.
//

#include "RSA.h"
#include <random>
#include <chrono>
#include <iostream>

RSA::RSA() {
    //this->gen_Key();
}
ll RSA::exGcd(const ll &a, const ll &b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exGcd(b, a % b, x, y);

    long long temp = y;
    y = x - (a / b) * y;
    x = temp;

    return g;
}
ll RSA::exGcd(const ll &a, const ll &b) {
    if (b == 0) {
        return a;
    }
    ll g = exGcd(b, a % b);
    return g;
}
ll RSA::getMulInverse(const ll &e, const ll &z) {
    ll x = 0;
    ll y = 0;
    exGcd(e, z, x, y);
    x = (x % z + z) % z;
    return x;
}

ll RSA::quickMulMod(const ll &a, const ll &b, const ll &c) {
    ll res = 0;
    ll a_temp = a % c;
    ll b_temp = b;
    while (b_temp > 0) {
        if (b_temp & 0x01) {
            res = (res + a_temp) % c;
        }
        a_temp = (a_temp * 2) % c;
        b_temp >>= 1;
    }
    return (res%c+c)%c;
}

ll RSA::quickPowMod(const ll &a, const ll &b, const ll &c) {
    ll res = 1;
    ll a_temp = a % c;
    std::cout<<"a%c:"<<a_temp<< std::endl;
    ll b_temp = b;
    while (b_temp > 0) {
        if (b_temp & 0x01) {
            res = quickMulMod(res, a_temp, c);
        }
        a_temp = quickMulMod(a_temp, a_temp, c);
        b_temp >>= 1;
    }
    return (res%c+c)%c;
}

bool RSA::MillerRabbin(const ll &p, const ll &a) {
    ll d = p - 1;
    ll r = 0;
    while ((d & 0x01) == 0) {
        d >>= 1;
        r++;
    }
    std::cout<<"p:"<<p<< std::endl;
    std::cout<<"a:"<<a<< std::endl;
    std::cout<<"d:"<<d<< std::endl;
    ll k = quickPowMod(a, d, p);
    std::cout<<"k:"<<k<< std::endl;
    if (k == 1) {
        return true;
    }
    for (int i = 0; i < r; i++) {
        std::cout<<"i:"<<i<< std::endl;
        std::cout<<"k:"<<k<< std::endl;
        if (k == p - 1) {
            return true;
        }
        k = quickPowMod(k, 2, p);
    }
    return false;
}

bool RSA::isPrime(const unsigned long long &n) {
    if (n < 3) {
        return n == 2;
    }
    if (n % 2 == 0) {
        return false;
    }
    bool prime_Flag = true;
    for (ll Jim_Sinclair[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}; ll a : Jim_Sinclair) {
        prime_Flag &= MillerRabbin(n, a);
        std::cout<<"Flag:"<<prime_Flag<< std::endl;
        if (!prime_Flag) {
            return false;
        }
    }
    return true;
}
ll RSA::getPrimeNum() {
    std::mt19937_64 generator(std::chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        ll random = generator();
        if (isPrime(random)) {
            return random;
        }
    }
}
void RSA::gen_Key() {
    std::mt19937_64 generator(std::chrono::steady_clock::now().time_since_epoch().count());
    const ll p = getPrimeNum();
    const ll q = getPrimeNum();
    this->agr_n = p * q;
    const ll Euler_z = (p - 1) * (q - 1);
    std::uniform_int_distribution<ll> distribution(0, Euler_z);
    do {
        this->arg_e = distribution(generator);
    }while (exGcd(this->arg_e, Euler_z)!=1);
    this->arg_d = getMulInverse(this->arg_e, Euler_z);
}
