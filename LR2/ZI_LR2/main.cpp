#include <iostream>

#include "rotor.h"
#include "rotor2.h"
#include "rotor3.h"
#include "stator.h"
#include <cctype>

#define TO_LEFT 0
#define TO_RIGHT 1

using namespace std;

char encodeByRotors(char letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
char decodeByRotors(char letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);

int main()
{
    cout << "Hello World!" << endl;

    Rotor rotor1 = Rotor();
    Rotor2 rotor2 = Rotor2();
    Rotor3 rotor3 = Rotor3();
    Stator stator = Stator();

    char letter = 'Z';

    char resLetter = encodeByRotors(letter, rotor1, rotor2, rotor3, stator);

    cout << "CODED: " << resLetter << endl;

    resLetter = decodeByRotors(resLetter, rotor1, rotor2, rotor3, stator);
    cout << "DECODED: " << resLetter << endl;

    return 0;
}


char encodeByRotors(char letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    int number = toupper(letter) - 64;

    int firstRtl = rotor1.encode(number, TO_LEFT);
    int secondRtl = rotor2.encode(firstRtl, TO_LEFT);
    int thirdRtl = rotor3.encode(secondRtl, TO_LEFT);

    int statorRtl = stator.find(thirdRtl);
    cout << statorRtl << endl;

    int thirdLtr = rotor3.encode(statorRtl, TO_RIGHT);
    int secondLtr = rotor2.encode(thirdLtr, TO_RIGHT);
    int result = rotor1.encode(secondLtr, TO_RIGHT);

    char resLetter = result + 64;

    return resLetter;
}

char decodeByRotors(char letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    int number = toupper(letter) - 64;

    int firstRtl = rotor1.decode(number, TO_LEFT);
    int secondRtl = rotor2.decode(firstRtl, TO_LEFT);
    int thirdRtl = rotor3.decode(secondRtl, TO_LEFT);

    int statorRtl = stator.find(thirdRtl);
    cout << statorRtl << endl;

    int thirdLtr = rotor3.decode(statorRtl, TO_RIGHT);
    int secondLtr = rotor2.decode(thirdLtr, TO_RIGHT);
    int result = rotor1.decode(secondLtr, TO_RIGHT);

    char resLetter = result + 64;

    return resLetter;
}
