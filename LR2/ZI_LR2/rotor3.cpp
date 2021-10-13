#include "rotor3.h"
#include <iostream>

Rotor3::Rotor3()
{
    generatePairs();
    savePairs();
    codePos = 0;
    decodePos = 0;
}

int Rotor3::encode(int letter, int direction)
{
    codePos++; // имитируем сдвиг ротора на 1 позицию

    int search = cykleSearch(letter + cycleIteration(codePos));
    int result;

    for(int i = 0; i < PAIRS_SIZE; i++)
    {
        if (pairs[i][alterDirection(direction)] == search)
            result = pairs[i][direction];
    }

    return result;
}


int Rotor3::decode(int letter, int direction)
{
    decodePos++; // имитируем сдвиг ротора на 1 позицию

    int pos = decodePos; // присвоим позицию в переменную

    //при расшифровке, нам нужно учитывать направление в обратном порядке
    //Сперва нужно найти значение слева направо, затем наоборот
    if (direction == 0)
        pos++;
    else
        pos--;

    int result;
    for(int i = 0; i < PAIRS_SIZE; i++)
    {
        if (pairs[i][alterDirection(direction)] == letter)
        {
            result = pairs[i][direction] - cycleIteration(pos); //возвращаем с вычетом стартовой позиции
            //result %= PAIRS_SIZE;
            while (result <= 0)
                result = result + PAIRS_SIZE;
        }
    }

    return result;
}

int Rotor3::alterDirection(int direction)
{
    return (direction == 0) ? 1 : 0;
}

int Rotor3::cykleSearch(int search)
{
    while (search > PAIRS_SIZE)
        search -= PAIRS_SIZE;
    return search;
}

int Rotor3::cycleIteration(int iter)
{
    if (iter / (PAIRS_SIZE * PAIRS_SIZE) > 1) // 676 = PAIRS_SIZE * PAIRS_SIZE
    {
        while (iter > (PAIRS_SIZE * PAIRS_SIZE))
        {
            iter /= (PAIRS_SIZE * PAIRS_SIZE);
        }
    }
    else
    {
        iter = 0;
    }

    return iter;
}

void Rotor3::generatePairs()
{
    vector<int> pairsLeft(PAIRS_SIZE);
    vector<int> pairsRight(PAIRS_SIZE);
    for(int i = 0; i < PAIRS_SIZE; i++)
    {
        pairsLeft[i] = i;
        pairsRight[i] = i;
    }

    srand(unsigned(time(0)));

    while (!checkPairs(pairsLeft, pairsRight))
    {
        random_shuffle(pairsLeft.begin(), pairsLeft.end());
        random_shuffle(pairsRight.begin(), pairsRight.end());
    }

    pairs = vector<vector<int>>(PAIRS_SIZE);
    for (int i = 0; i < PAIRS_SIZE; i++)
        pairs[i] = {0, 0};

    for (int i = 0; i < PAIRS_SIZE; i++)
    {
        pairs[i][0] = pairsLeft[i];
        pairs[i][1] = pairsRight[i];
    }
}

int Rotor3::checkPairs(vector<int>& pairsLeft, vector<int>& pairsRight)
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

void Rotor3::savePairs()
{
    ofstream file("rotor3.txt");
    for (int i = 0; i < PAIRS_SIZE; i++)
    {
        file << pairs[i][0] << "    " << pairs[i][1] << endl;
    }
    file.close();
}
