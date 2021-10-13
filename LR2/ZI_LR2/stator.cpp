#include "stator.h"
#include <iostream>
#include <fstream>

Stator::Stator()
{
    generatePairs();
    savePairs();
}

int Stator::find(int letter)
{
    for (int i = 0; i < PAIRS_SIZE; i++)
    {
        if (pairs[i][0] == letter)
            return pairs[i][1];
    }
    return -1;
}

void Stator::generatePairs()
{
    vector<int> pairsLeft(PAIRS_HALF_SIZE);
    vector<int> pairsRight(PAIRS_HALF_SIZE);

    for(int i = 0; i < PAIRS_HALF_SIZE; i++)
    {
        pairsLeft[i] = i;
        pairsRight[i] = i + PAIRS_HALF_SIZE;
    }

    srand(unsigned(time(0)));

    random_shuffle(pairsLeft.begin(), pairsLeft.end());
    random_shuffle(pairsRight.begin(), pairsRight.end());

    pairs = vector<vector<int>>(PAIRS_SIZE);
    for (int i = 0; i < PAIRS_SIZE; i++)
        pairs[i] = {0, 0};

    for (int i = 0; i < PAIRS_HALF_SIZE; i++)
    {
        pairs[i][0] = pairsLeft[i];
        pairs[i][1] = pairsRight[i];
    }

    for (int i = PAIRS_HALF_SIZE; i < PAIRS_SIZE; i++)
    {
        pairs[i][0] = pairsRight[i - PAIRS_HALF_SIZE];
        pairs[i][1] = pairsLeft[i - PAIRS_HALF_SIZE];
    }
}

int Stator::checkPairs(vector<int>& pairsLeft, vector<int>& pairsRight)
{
    int checked = 1;
    for (int i = 0; i < PAIRS_SIZE; i++)
    {
        if (pairsLeft[i] == pairsRight[i])
        {
            checked = 0;
            break;
        }
    }

    return checked;
}

void Stator::savePairs()
{
    ofstream file("stator.txt");
    for (int i = 0; i < PAIRS_SIZE; i++)
    {
        file << pairs[i][0] << "    " << pairs[i][1] << endl;
    }
    file.close();
}
