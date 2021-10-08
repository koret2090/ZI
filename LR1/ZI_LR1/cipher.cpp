#include "cipher.h"

using namespace std;

Cipher::Cipher()
{

}

char Cipher::codeSymbol = 'T';

string Cipher::encode(string str)
{
    string codedStr = "";
    int len = str.length();

    for (int i = 0; i < len; i++)
    {
        codedStr += str[i] ^ codeSymbol;
    }

    return codedStr;
}
