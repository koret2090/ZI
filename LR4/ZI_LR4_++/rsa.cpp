#include "rsa.h"
#include "QDebug"
RSA::RSA()
{
    vector<int> nums = generatePrimeNumbers();
    int p = nums[0];
    int q = nums[1];
    n = p * q;
    phi = (p - 1) * (q - 1);

    publicKey = GeneratePublicKey(phi);
    privateKey = GeneratePrivateKey(publicKey, phi);
}


vector<int> RSA::generatePrimeNumbers()
{
    int random_number1 = MIN_NUM + rand() % MAX_NUM;

    while (!isPrime(random_number1))
    {
        random_number1 = MIN_NUM + rand() % MAX_NUM;
    }

    int random_number2 = MIN_NUM + rand() % MAX_NUM;

    while (!isPrime(random_number2) || random_number1 == random_number2)
    {
        random_number2 = MIN_NUM + rand() % MAX_NUM;
    }

    vector<int> nums = {random_number1, random_number2};
    return  nums;
}

bool RSA::isPrime(int num)
{
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int RSA::GCD(int num1, int num2)
{
    int temp;
    while (num2 != 0)
    {
        temp = num1;
        num1 = num2;
        num2 = temp % num2;
    }
    return num1;
}

int RSA::Evklid(int a, int n)
{
    int t = 0;
    int r = n; // остаток от деления
    int newt = 1;
    int newr = a;

    while (newr != 0)
    {
        int quotient = r / newr;
        int tmpt = newt;
        newt = t - quotient * newt;
        t = tmpt;

        int tmpr = newr;
        newr = r - quotient * newr;
        r = tmpr;
    }

    if (r > 1)
        return -1;
    if (t < 0)
        t = t + n;

    return t;
}

/*
big RSA::GeneratePublicKey(int phi)
{
    int key = 2;
    while (GCD(key, phi) != 1)
    {
        key++;
    }
    return key;
}
*/

big RSA::GeneratePublicKey(int phi)
{
    int nod = 0;
    int num = -1;
    while (nod != 1)
    {
        num = 2 + rand() % phi;
        nod = GCD(phi, num);
    }
    return num;
}

big RSA::GeneratePrivateKey(int publicKey, int phi)
{
    return Evklid(publicKey, phi);
}

template <typename T>
T modpow(T base, T exp, T modulus)
{
  base %= modulus;
  T result = 1;
  while (exp > 0)
  {
    if (exp & 1)
        result = (result * base) % modulus;

    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

big RSA::Encrypt(unsigned int m)
{
    return modpow<big>(m, publicKey, n);
}

big RSA::Decrypt(unsigned int c)
{
    return modpow<big>(c, privateKey, n);
}

void RSA::EncodeFile()
{
    //для считывания
    QFile file(TO_READ);
    file.open(QIODevice::ReadOnly);
    //QByteArray in;

    // для записи
    QFile fileWrite(TO_ENCODE);
    fileWrite.open(QIODevice::WriteOnly);

    while (!file.atEnd())
    {
        QByteArray byteNum;
        byteNum.append(file.read(1));
        //in = file.read(1);
        //qDebug() << byteNum;
        unsigned int num = byteNum.toHex().toUInt(nullptr, 16);
        //qDebug() << num;
        big encodedSymbol = Encrypt(num);

        QByteArray out;
        out[0] = encodedSymbol;
        //qDebug() << out;
        fileWrite.write(out);
    }
    fileWrite.close();
    file.close();
}

void RSA::DecodeFile()
{
    //для считывания
    QFile file(TO_ENCODE);
    file.open(QIODevice::ReadOnly);
    //QByteArray in;

    // для записи
    QFile fileWrite(TO_DECODE);
    fileWrite.open(QIODevice::WriteOnly);

    while (!file.atEnd())
    {
        QByteArray byteNum;
        byteNum.append(file.read(1));
        //in = file.read(1);
        qDebug() << byteNum;
        unsigned int num = byteNum.toHex().toUInt(nullptr, 16);
        qDebug() << num;
        big encodedSymbol = Decrypt(num);

        QByteArray out;
        out[0] = encodedSymbol;
        qDebug() << out;
        fileWrite.write(out);
    }
    fileWrite.close();
    file.close();
}
