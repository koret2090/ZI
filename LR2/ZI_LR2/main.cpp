#include "enigma.h"

using namespace std;

void menu(Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
void encodeFileMenu(Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
void decodeFileMenu(Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Rotor rotor1 = Rotor();
    Rotor2 rotor2 = Rotor2();
    Rotor3 rotor3 = Rotor3();
    Stator stator = Stator();

    /*
    const char from[] = "enigma.txt";
    const char to[] = "enigmaRes2.txt";
    const char to2[] = "enigmaRes3.txt";

    encodeFile(from, to, rotor1, rotor2, rotor3, stator);
    cout << "ROTOR " << rotor1.codePos << endl;
    decodeFile(to, to2, rotor1, rotor2, rotor3, stator);
    */

    menu(rotor1, rotor2, rotor3, stator);
    return 0;
}


void menu(Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    int choice = -1;

    while(choice != 0)
    {
        cout << "Menu" << endl
             << "1 - Encode file" << endl
             << "2 - Decode file" << endl
             << "3 - Regenerate parts pairs" << endl
             << "0 - Exit" << endl
             << "Your choice: " << endl;
        cin >> choice;

        if (choice == 1)
        {
            encodeFileMenu(rotor1, rotor2, rotor3, stator);
        }
        else if (choice == 2)
        {
            decodeFileMenu(rotor1, rotor2, rotor3, stator);
        }
        else if (choice == 0)
        {
            cout << "Rotors' shifts: " << endl
                 << "Rotor1: " << rotor1.codePos << "   "  << rotor1.decodePos << endl
                << "Rotor2: " << rotor2.codePos << "   " << rotor2.decodePos << endl
                 << "Rotor3: " << rotor3.codePos << "   "  << rotor3.decodePos << endl;
        }
    }
}

void encodeFileMenu(Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    char fileFrom[128];
    cout << "Input source file: ";
    cin >> fileFrom;

    ifstream file(fileFrom);
    if (!file.is_open())
    {
        cout << "File doesn't exist!" << endl;
        file.close();
    }
    file.close();

    char fileTo[128];
    cout << "Input destination file: ";
    cin >> fileTo;


    cout << "Input rotors' shifts: " << endl;
    cout << "Rotor1: ";
    int input = 0;
    cin >> input;
    rotor1.codePos = input;

    cout << "Rotor2: ";
    cin >> input;
    rotor2.codePos = input;

    cout << "Rotor3: ";
    cin >> input;
    rotor3.codePos = input;

    encodeFile(fileFrom, fileTo, rotor1, rotor2, rotor3, stator);
}

void decodeFileMenu(Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator)
{
    char fileFrom[128];
    cout << "Input source file: ";
    cin >> fileFrom;

    ifstream file(fileFrom);
    if (!file.is_open())
    {
        cout << "File doesn't exist!" << endl;
        file.close();
    }
    file.close();

    char fileTo[128];
    cout << "Input destination file: ";
    cin >> fileTo;


    cout << "Input rotors' shifts(0 - 255): " << endl;
    cout << "Rotor1: ";
    int input = 0;
    cin >> input;
    rotor1.codePos = input;

    cout << "Rotor2: ";
    cin >> input;
    rotor2.codePos = input;

    cout << "Rotor3: ";
    cin >> input;
    rotor3.codePos = input;

    decodeFile(fileFrom, fileTo, rotor1, rotor2, rotor3, stator);
}
