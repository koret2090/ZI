#include "aes.h"
#include <QFile>
#include <QDataStream>
#include <QString>

#include <iostream>
#include <QDebug>

using namespace std;
void menu();

int main()
{
    menu();
    //AES aes = AES("3rbek1hPYKLJuMVd");
    //aes.Encode("aes.txt", "aesEncoded.txt");
    //aes.Decode("aesEncoded.txt", "aesDecoded.txt");

    return 0;
}


void menu()
{
    int choice = -1;
    AES aes = AES("3rbek1hPYKLJuMVd");
    while(choice)
    {
        cout << "Menu: " << endl
             << "1 - Enter the key" << endl
             << "2 - Encode file" << endl
             << "3 - Decode file" << endl
             << "0 - Exit" << endl
             << "Your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter the key: ";
            char key[17];
            cin >> key;
            aes = AES(key);
        }
        else if (choice == 2)
        {
            cout << "Input filename for Encoding: ";
            string aesFile;
            cin >> aesFile;

            //if (aesFile == " ")
            //    aesFile = "aes.txt";

            cout << "Input filename for Saving: ";
            string aesFileEncode;
            cin >> aesFileEncode;

            //if (aesFileEncode == " ")
            //    aesFileEncode = "aesEncoded.txt";

            aes.Encode(aesFile, aesFileEncode);
        }
        else if (choice == 3)
        {
            cout << "Input filename for Decoding: ";
            string aesFileEncode;
            cin >> aesFileEncode;

            //if (aesFileEncode == " ")
            //    aesFileEncode = "aesEncoded.txt";

            cout << "Input filename for Saving: ";
            string aesFileDecode;
            cin >> aesFileDecode;

            //if (aesFileDecode == " ")
            //    aesFileDecode = "aesDecoded.txt";

            aes.Decode(aesFileEncode, aesFileDecode);
        }
    }
}
