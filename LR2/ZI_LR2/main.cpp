#include <iostream>

#include "rotor.h"
#include "rotor2.h"
#include "rotor3.h"
#include "stator.h"
#include <cctype>
#include <fstream>
#include <windows.h>

#define BUF_SIZE 256
#define TO_LEFT 0
#define TO_RIGHT 1

using namespace std;

int encodeByRotors(int letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
int decodeByRotors(int letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
void encodeFile(const char* fileFrom, const char* fileTo, \
                Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
void decodeFile(const char* fileFrom, const char* fileTo, \
                Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Hello World!" << endl;

    Rotor rotor1 = Rotor();
    Rotor2 rotor2 = Rotor2();
    Rotor3 rotor3 = Rotor3();
    Stator stator = Stator();

    /*
    ifstream file("enigma.txt",  ios::in | ios::binary);
    char b;

    while (file.get(b)) {
        cout << b << endl;
    }

    //file.read(&b, sizeof(char));
    //file.read(buf, 1);


    file.close();
    */

    /*
    FILE* file = fopen("enigma.txt", "rb");
    unsigned char byte;

    fread(&byte, 1,1,file);
    fclose(file);

    unsigned int num = byte;

    cout << "ORIGINAL " << byte << endl;

    char letter = 'B';
    int resLetter = encodeByRotors(num, rotor1, rotor2, rotor3, stator);

    cout << "CODED: " << resLetter << endl;

    resLetter = decodeByRotors(resLetter, rotor1, rotor2, rotor3, stator);
    cout << "DECODED: " << resLetter << endl;

    FILE* file2 = fopen("enigmaRes.txt", "wb");
    unsigned char res = (unsigned char)resLetter;
    fwrite(&res, 1, 1, file2);

    fclose(file2);
    */
    const char from[] = "enigma.txt";
    const char to[] = "enigmaRes2.txt";
    const char to2[] = "enigmaRes3.txt";

    encodeFile(from, to, rotor1, rotor2, rotor3, stator);
    decodeFile(to, to2, rotor1, rotor2, rotor3, stator);

    return 0;
}

void encodeFile(const char* fileFrom, const char* fileTo, \
                Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    FILE* fileSource = fopen(fileFrom, "rb");
    FILE* fileDest = fopen(fileTo, "wb");
    unsigned char buf[BUF_SIZE];
    unsigned char byte;

    int i = 0;
    while(fread(&byte, 1,1,fileSource) == 1)
    {
        /*
        fread(buf, sizeof(unsigned char), BUF_SIZE, fileSource);
        cout << "BOOBA " << buf << endl << endl;
        for (int i = 0; i < BUF_SIZE; i++)
        {
            buf[i] = encodeByRotors(buf[i], rotor1, rotor2, rotor3, stator);
        }
        fwrite(buf, sizeof(unsigned char), BUF_SIZE, fileSource);
        cout << "BOOBA " << buf << endl << endl;
        */
        buf[i] = encodeByRotors(byte, rotor1, rotor2, rotor3, stator);
        i++;
    }
    fwrite(buf, sizeof(unsigned char), i, fileDest);
    fclose(fileSource);
    fclose(fileDest);
}

void decodeFile(const char* fileFrom, const char* fileTo, \
                Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    FILE* fileSource = fopen(fileFrom, "rb");
    FILE* fileDest = fopen(fileTo, "wb");
    unsigned char buf[BUF_SIZE];
    unsigned char byte;

    int i = 0;
    while(fread(&byte, 1,1,fileSource) == 1)
    {
        buf[i] = decodeByRotors(byte, rotor1, rotor2, rotor3, stator);
        i++;
    }
    fwrite(buf, sizeof(unsigned char), i, fileDest);
    fclose(fileSource);
    fclose(fileDest);
}

int encodeByRotors(int letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    int number = letter;

    int firstRtl = rotor1.encode(number, TO_LEFT);
    //int secondRtl = rotor2.encode(firstRtl, TO_LEFT);
    //int thirdRtl = rotor3.encode(secondRtl, TO_LEFT);

    int statorRtl = stator.find(firstRtl);
    cout << statorRtl << endl;

    //int thirdLtr = rotor3.encode(statorRtl, TO_RIGHT);
    //int secondLtr = rotor2.encode(thirdLtr, TO_RIGHT);
    int result = rotor1.encode(statorRtl, TO_RIGHT);

    char resLetter = result;

    return result;
}

int decodeByRotors(int letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    //int number = toupper(letter) - 64;
    int number = letter;
    int firstRtl = rotor1.decode(number, TO_LEFT);
    //int secondRtl = rotor2.decode(firstRtl, TO_LEFT);
    //int thirdRtl = rotor3.decode(secondRtl, TO_LEFT);

    int statorRtl = stator.find(firstRtl);
    cout << statorRtl << endl;

    //int thirdLtr = rotor3.decode(statorRtl, TO_RIGHT);
    //int secondLtr = rotor2.decode(thirdLtr, TO_RIGHT);
    int result = rotor1.decode(statorRtl, TO_RIGHT);

    char resLetter = result;

    return result;
}
