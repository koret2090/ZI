#ifndef ROTOR_H
#define ROTOR_H

#include <vector>

using namespace std;

class Rotor
{
public:
    Rotor();

    vector<vector<int>> pairs;
    int encode(int letter, int direction);
    int decode(int letter, int direction);

    int codePos;
    int decodePos;

private:
    int alterDirection(int direction);
    int cykleSearch(int search);
};

#endif // ROTOR_H
