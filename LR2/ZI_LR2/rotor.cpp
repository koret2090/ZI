#include "rotor.h"
#include <iostream>

Rotor::Rotor()
{
    pairs = {{1,3},{5,20},{17,2},{2,15},{14,18},{8,1},
            {12,13},{18,10},{9,5},{13,24},{3,19},{23,6},{6,17},{16,12},
            {25,21},{15,26},{4,8},{10,25},{21,9},{26,14},{22,11},{19,16},
            {11,23},{24,7},{7,4},{20,22}};

    codePos = 0;
    decodePos = 0;
}

int Rotor::encode(int letter, int direction)
{
    codePos++; // имитируем сдвиг ротора на 1 позицию

    if (codePos > 26) // имитируем зацикливание
        codePos -= 26;

    // определим, какая буква (точнее ее порядковый номер) нам нужна.
    // Для этого сложим порядковый номер вводимой буквы и стартовую позицию.
    int search = cykleSearch(letter + codePos);
    cout << "CHECK1: " << search << endl;
    int result;

    for(int i = 0; i < 26; i++)
    {
        if (pairs[i][alterDirection(direction)] == search)
            result = pairs[i][direction];
    }
    cout << "CHECK2: " << result << endl;
    return result;
}


int Rotor::decode(int letter, int direction)
{
    decodePos++; // имитируем сдвиг ротора на 1 позицию

    if (decodePos > 26) // имитируем зацикливание
        decodePos -= 26;

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
            result = pairs[i][direction] - pos; //возвращаем с вычетом стартовой позиции
            while (result <= 0)
                result += 26;
        }
    }

    return result;
}

int Rotor::alterDirection(int direction)
{
    return (direction == 0) ? 1 : 0;
}

int Rotor::cykleSearch(int search)
{
    while (search > 26)
        search -= 26;
    return search;
}
