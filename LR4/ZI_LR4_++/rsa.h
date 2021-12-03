#ifndef RSA_H
#define RSA_H

#include <vector>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <cmath>

#define MIN_NUM 1000
#define MAX_NUM 9999

#define TO_READ "text.txt"
#define TO_ENCODE "encoded.txt"
#define TO_DECODE "decoded.txt"

typedef unsigned long long big;

using namespace std;

class RSA
{
public:
    RSA();
    vector<int> generatePrimeNumbers();
    int GCD(int num1, int num2);
    int Evklid(int a, int n);

    big GeneratePublicKey(int phi);
    big GeneratePrivateKey(int publicKey, int phi);

    big Encrypt(unsigned int m);
    big Decrypt(unsigned int c);

    big n;
    big phi;
    big publicKey;
    big privateKey;

    void EncodeFile();
    void DecodeFile();
    big modpow2(big base, big exp, big modulus);
private:
    bool isPrime(int num);
};

#endif // RSA_H
