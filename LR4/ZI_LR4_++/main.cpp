#include "rsa.h"

int main()
{
    RSA rsa = RSA();
    rsa.EncodeFile();
    rsa.DecodeFile();

    return 0;
}
