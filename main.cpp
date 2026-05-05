#include "RSA.h"
#include <iostream>
using namespace std;
int main() {
    RSA rsa;
    //cout<<rsa.quickPowMod(325,3,13)<<endl;
    rsa.isPrime(13);
    return 0;
}