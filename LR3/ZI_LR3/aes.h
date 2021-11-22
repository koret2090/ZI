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
    AES(char key_str[17]);
    void Encode(string aesFile, string aesFileEncode);
    void Decode(string aesFileEncoded, string aesFileDecoded);

private:
    vector<QByteArray> state;

    vector<QByteArray> SBox;
    vector<QByteArray> SBoxReversed;
    vector<QByteArray> C;
    vector<QByteArray> CReversed;
    vector<QByteArray> RCon;
    vector<QByteArray> roundKey;
    QByteArray Key;
    int Nk;
    int Nb;
    int Nr;

    vector<QByteArray> input;
    void Cipher();
    void SubBytes(vector<QByteArray>& state);
    void ShiftRows(vector<QByteArray>& state);
    void LeftShiftRow(QByteArray& row);
    void MixColumns(vector<QByteArray>& state);
    void EncodeBlock();

    void FillKey();
    void KeyExpansion();
    void AddRoundKey(vector<QByteArray> &state, vector<QByteArray> &key, int roundIter);
    void SubWord(QByteArray& word);
    void RotWord(QByteArray& word);
    QByteArray XorWord(QByteArray& word1, QByteArray& word2);



    void ByteMatrixCopy(vector<QByteArray> source, vector<QByteArray> dest);

    void InvSubBytes(vector<QByteArray>& state);
    void InvShiftRows(vector<QByteArray>& state);
    void RightShiftRow(QByteArray& row);
    void InvMixColumns(vector<QByteArray>& state);
    unsigned char gMul(unsigned char a, unsigned char b);
    void DecodeBlock();

    void InvSubWord(QByteArray &word);


};

#endif // AES_H
