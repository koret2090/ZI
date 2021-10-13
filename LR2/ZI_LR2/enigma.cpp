#include "enigma.h"

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
    int secondRtl = rotor2.encode(firstRtl, TO_LEFT);
    int thirdRtl = rotor3.encode(secondRtl, TO_LEFT);

    int statorRtl = stator.find(thirdRtl);

    int thirdLtr = rotor3.encode(statorRtl, TO_RIGHT);
    int secondLtr = rotor2.encode(thirdLtr, TO_RIGHT);
    int result = rotor1.encode(secondLtr, TO_RIGHT);

    return result;
}

int decodeByRotors(int letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    int firstRtl = rotor1.decode(letter, TO_LEFT);
    int secondRtl = rotor2.decode(firstRtl, TO_LEFT);
    int thirdRtl = rotor3.decode(secondRtl, TO_LEFT);

    int statorRtl = stator.find(thirdRtl);

    int thirdLtr = rotor3.decode(statorRtl, TO_RIGHT);
    int secondLtr = rotor2.decode(thirdLtr, TO_RIGHT);
    int result = rotor1.decode(secondLtr, TO_RIGHT);

    return result;
}
