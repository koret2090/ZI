#include "checking.h"

string getUuid()
{
    // текущий путь
    char pathName[PATH_MAX];
    getcwd(pathName, PATH_MAX);

    // добавляем лицензию к пути
    char fileName[PATH_MAX] = "/.license";
    strcat(pathName, fileName);

    char command[PATH_MAX] = "wmic csproduct get uuid > ";
    strcat(command, pathName);
    system(command);

    ifstream fileRead(pathName);

    string uuid;
    getline(fileRead, uuid);
    getline(fileRead, uuid);

    fileRead.close();

    return uuid;
}
