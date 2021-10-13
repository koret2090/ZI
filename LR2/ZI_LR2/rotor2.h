#ifndef ROTOR2_H
#define ROTOR2_H

#include <vector>
#include "generator.h"

using namespace std;

class Rotor2
{
public:
    Rotor2();

    vector<vector<int>> pairs;
    int encode(int letter, int direction);
    int decode(int letter, int direction);

    int codePos;
    int decodePos;

private:
    int alterDirection(int direction);
    int cykleSearch(int search);
    int cycleIteration(int iter);

    void generatePairs();
    int checkPairs(vector<int>& pairsLeft, vector<int>& pairsRight);
    void savePairs();
};


#endif // ROTOR2_H
