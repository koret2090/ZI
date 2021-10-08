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
    // считываем лицензию
    char pathName[PATH_MAX];
    getcwd(pathName, PATH_MAX);

    char fileName[PATH_MAX] = "/.license";
    strcat(pathName, fileName);
    ifstream file(pathName);

    // проверка на наличие файла с лицензией
    if (!file.is_open())
    {
        cout << "There is no license!" << endl;
        return 0;
    }

    string licenseUuid;
    file >> licenseUuid;

    if (licenseUuid == Cipher::encode(getUuid()))
    {
        cout << "Thanks for the purchasing of our product!" << endl;
    }
    else
    {
        cout << "Not permitted!" << endl;
    }
    file.close();

    return 0;
}
