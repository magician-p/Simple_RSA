#include "RSA.h"
#include <iostream>
using namespace std;
int main() {
    RSA rsa;
    //cout<<rsa.quickPowMod(325,3,13)<<endl;
    cout<<rsa.quickMulMod(324,5,13)<<endl;
    //rsa.isPrime(13);
    return 0;
}