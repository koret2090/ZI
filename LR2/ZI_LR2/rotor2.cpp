#include "rotor2.h"


Rotor2::Rotor2()
{
    pairs = {{18,8},{4,6},{13,5},{23,24},{12,25},{19,21},{2,14},
            {24,16},{3,19},{7,1},{10,23},{6,2},{20,13},{15,12},{14,10},
            {5,20},{17,3},{16,17},{9,22},{25,15},{11,18},{8,26},
            {1,7},{21,9},{22,11},{26,4}};

    codePos = 0;
    decodePos = 0;
}

int Rotor2::encode(int letter, int direction)
{
    codePos++; // имитируем сдвиг ротора на 1 позицию

    // определим, какая буква (точнее ее порядковый номер) нам нужна.
    // Для этого сложим порядковый номер вводимой буквы и стартовую позицию.

    int search = cykleSearch(letter + cycleIteration(codePos));
    int result;

    for(int i = 0; i < 26; i++)
    {
        if (pairs[i][alterDirection(direction)] == search)
            result = pairs[i][direction];
    }

    return result;
}


int Rotor2::decode(int letter, int direction)
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
            result %= 26;
        }
    }

    return result;
}

int Rotor2::alterDirection(int direction)
{
    return (direction == 0) ? 1 : 0;
}

int Rotor2::cykleSearch(int search)
{
    while (search > 26)
        search -= 26;
    return search;
}

int Rotor2::cycleIteration(int iter)
{
    while (iter > 26)
    {
        iter /= 26;
    }
    return iter;
}
