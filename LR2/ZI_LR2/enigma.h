#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>

#include "rotor.h"
#include "rotor2.h"
#include "rotor3.h"
#include "stator.h"
#include <cctype>
#include <fstream>
#include <windows.h>

#define BUF_SIZE 256
#define TO_LEFT 0
#define TO_RIGHT 1

int encodeByRotors(int letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
int decodeByRotors(int letter, Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
void encodeFile(const char* fileFrom, const char* fileTo, \
                Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
void decodeFile(const char* fileFrom, const char* fileTo, \
                Rotor& rotor1, Rotor2& rotor2, Rotor3& rotor3, Stator& stator);
#endif // ENIGMA_H
