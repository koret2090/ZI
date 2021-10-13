#ifndef STATOR_H
#define STATOR_H

#include <vector>
#include "generator.h"

using namespace std;

class Stator
{
public:
    Stator();

    vector<vector<int>> pairs;
    int find(int letter);

private:
    void generatePairs();
    int checkPairs(vector<int>& pairsLeft, vector<int>& pairsRight);
    void savePairs();
};

#endif // STATOR_H
