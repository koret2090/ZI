#include "rotor3.h"
#include <iostream>

Rotor3::Rotor3()
{
    pairs = {{24,19},{19,20},{5,13},{6,7},{2,5},{15,25},{8,17},
            {9,4},{20,10},{12,11},{25,23},{11,6},{18,8},{23,2},
            {21,16},{16,26},{26,1},{7,21},{3,3},{4,12},{14,15},
            {22,9},{17,24},{13,22},{1,14},{10,18}};

    codePos = 0;
    decodePos = 0;
}

int Rotor3::encode(int letter, int direction)
{
    codePos++; // имитируем сдвиг ротора на 1 позицию

    int search = cykleSearch(letter + cycleIteration(codePos));
    int result;

    for(int i = 0; i < 26; i++)
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
    for(int i = 0; i < 26; i++)
    {
        if (pairs[i][alterDirection(direction)] == letter)
        {
            result = pairs[i][direction] - cycleIteration(pos); //возвращаем с вычетом стартовой позиции
            //result %= 26;
            while (result <= 0)
                result = result + 26;
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
    while (search > 26)
        search -= 26;
    return search;
}

int Rotor3::cycleIteration(int iter)
{
    if (iter / 676 > 1) // 676 = 26 * 26
    {
        while (iter > 676)
        {
            iter /= 676;
        }
    }
    else
    {
        iter = 0;
    }

    return iter;
}
