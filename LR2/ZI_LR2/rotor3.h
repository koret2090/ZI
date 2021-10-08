#ifndef ROTOR3_H
#define ROTOR3_H

#include <vector>

using namespace std;

class Rotor3
{
public:
    Rotor3();

    vector<vector<int>> pairs;
    int encode(int letter, int direction);
    int decode(int letter, int direction);

    int codePos;
    int decodePos;

private:
    int alterDirection(int direction);
    int cykleSearch(int search);
    int cycleIteration(int iter);
};

#endif // ROTOR3_H
