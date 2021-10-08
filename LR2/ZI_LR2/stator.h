#ifndef STATOR_H
#define STATOR_H

#include <vector>

using namespace std;

class Stator
{
public:
    Stator();

    vector<vector<int>> pairs;
    int find(int letter);
};

#endif // STATOR_H
