#include "rotor.h"

Rotor::Rotor()
{
    //generatePairs();
    loadPairs();
    codePos = 0;
    decodePos = 0;

    savePairs();
}

int Rotor::encode(int letter, int direction)
{
    codePos++; // имитируем сдвиг ротора на 1 позицию

    if (codePos >= PAIRS_SIZE) // имитируем зацикливание
        codePos -= PAIRS_SIZE;

    // определим, какая буква (точнее ее порядковый номер) нам нужна.
    // Для этого сложим порядковый номер вводимой буквы и стартовую позицию.
    int search = cykleSearch(letter + codePos);
    int result;

    for(int i = 0; i < PAIRS_SIZE; i++)
    {
        if (pairs[i][alterDirection(direction)] == search)
            result = pairs[i][direction];
    }
    return result;
}


int Rotor::decode(int letter, int direction)
{
    decodePos++; // имитируем сдвиг ротора на 1 позицию

    if (decodePos >= PAIRS_SIZE) // имитируем зацикливание
        decodePos -= PAIRS_SIZE;

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
            result = pairs[i][direction] - pos; //возвращаем с вычетом стартовой позиции
            while (result < 0)
                result += PAIRS_SIZE;
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
    while (search >= PAIRS_SIZE)
        search -= PAIRS_SIZE;
    return search;
}

void Rotor::generatePairs()
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

int Rotor::checkPairs(vector<int>& pairsLeft, vector<int>& pairsRight)
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

void Rotor::savePairs()
{
    ofstream file("rotor1.txt");
    for (int i = 0; i < PAIRS_SIZE; i++)
    {
        file << pairs[i][0] << " " << pairs[i][1] << endl;
    }
    file.close();
}

void Rotor::loadPairs()
{
    pairs = vector<vector<int>>(PAIRS_SIZE);
    for (int i = 0; i < PAIRS_SIZE; i++)
        pairs[i] = {0, 0};

    ifstream file("rotor1.txt");
    for (int i = 0; i < PAIRS_SIZE; i++)
    {
        file >> pairs[i][0];
        file >> pairs[i][1];
    }
    file.close();
}
