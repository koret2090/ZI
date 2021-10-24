#ifndef AES_H
#define AES_H

#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QString>

#include <iostream>

#define STATE_SIZE 16
#define STATE_STR_SIZE 4

using namespace std;

class AES
{
public:
    AES();

private:
    vector<QByteArray> SBox;
    vector<QByteArray> SBoxReversed;
    vector<QByteArray> C;
    vector<QByteArray> CReversed;
    vector<QByteArray> RCon;
    vector<QByteArray> KeySchedule;
    QByteArray Key;
    int Nk;
    int Nb;
    int Nr;



    vector<QByteArray> input;
    void Cipher();
    void AddRoundKey();
    void SubBytes(vector<QByteArray> state);
    void ShiftRows(vector<QByteArray>& state);
    void LeftShiftRow(QByteArray& row);
    void MixColumns(vector<QByteArray> state);

    void KeyExpansion();
    void SubWord(QByteArray& word);
    void RotWord(QByteArray& word);

    void ByteMatrixCopy(vector<QByteArray> source, vector<QByteArray> dest);
};

#endif // AES_H
