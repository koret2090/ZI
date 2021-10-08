#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include "string.h"

using namespace std;

class Cipher
{
public:
    Cipher();
    static string encode(string str);

private:
    static char codeSymbol;
};

#endif // CIPHER_H
