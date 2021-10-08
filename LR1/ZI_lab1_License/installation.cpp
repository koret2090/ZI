#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <fstream>
#include <direct.h>
#include "cipher.h"
#include "checking.h"

using namespace std;

int main()
{
    // текущий путь
    char pathName[PATH_MAX];
    getcwd(pathName, PATH_MAX);

    // добавляем лицензию к пути
    char fileName[PATH_MAX] = "/.license";
    strcat(pathName, fileName);

    // получение uuid и запись его в закодированном виде
    string uuid = getUuid();
    cout << "DIO:" << uuid << endl;
    ofstream file(pathName);
    file << Cipher::encode(uuid);
    file.close();

    cout << "Installed " << endl;

    return 0;
}
