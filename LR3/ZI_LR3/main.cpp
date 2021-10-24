#include "aes.h"
#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QString>

#include <iostream>
#include <QDebug>


void LeftShiftRow(QByteArray& row);
void ShiftRows(vector<QByteArray>& state);
void ByteMatrixCopy(vector<QByteArray>& source, vector<QByteArray>& dest);
void MixColumns(vector<QByteArray>& state);

vector<QByteArray> C = {QByteArrayLiteral("\x02\x03\x01\x01"),
    QByteArrayLiteral("\x01\x02\x03\x01"),
    QByteArrayLiteral("\x01\x01\x02\x03"),
    QByteArrayLiteral("\x03\x01\x01\x02")};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("aes.txt");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    //out << QString("the answer is");   // serialize a string
    //QByteArray array = QByteArrayLiteral("\x41\x42\x4f\x42\xAA");
    QByteArray array;

    array[0] = 64;
    array[1] = 65;
    array[2] = 78;
    array[3] = 65;
    array[4] = 0x0A;


    file.write(array);

    //out << array;
    //qDebug("ABOBA");
    file.close();


    QFile file2("aes.txt");
    file2.open(QIODevice::ReadOnly);

    //QDataStream stream(&file2);
    QByteArray arr;
    arr = file2.read(5);
    /*
    for (int i = 0; i < arr.length(); i++)
    {
        arr[i] = arr[i] + 1;
    }
    */
    //stream >> arr;
    qDebug() << "ABIBA";
    qDebug(arr);
    file2.close();

    QByteArray byteNum;
    //byteNum[0] = 0x45;
    //byteNum[0] = arr[4];
    byteNum.append(arr[4]);
    QByteRef ref = arr[4];
    byteNum[0] = byteNum[0] * 0x02;

    unsigned int num = (unsigned int)(arr[4]);
    qDebug() << (num);
    qDebug() << "____________" << arr[4];
    bool ok;
    unsigned int num2 = byteNum.toHex().toUInt(nullptr, 16);
    qDebug() << (num2 % 16);
    qDebug() << byteNum;
    qDebug() << (byteNum.toHex().toInt(&ok,16));



    qDebug() << arr.size();


    vector<QByteArray> Check = {QByteArrayLiteral("\x01\x02\x03\x04"),
        QByteArrayLiteral("\x01\x02\x03\x04"),
        QByteArrayLiteral("\x01\x02\x03\x04"),
        QByteArrayLiteral("\x01\x02\x03\x04")};

    qDebug() << Check;

    ShiftRows(Check);
    qDebug() << Check;

    MixColumns(Check);
    qDebug() << Check;

    QByteArray Key = QByteArrayLiteral("3rbek1hPYKLJuMVd");
    Key[0] = Key[0] + 1;
    qDebug() << Key;

    return a.exec();
}

void ShiftRows(vector<QByteArray>& state)
{
    for (int i = 1; i < STATE_STR_SIZE; i++)
    {
        for (int shifts = 0; shifts < i; shifts++)
        {
            LeftShiftRow(state[i]);
        }
    }
}

void LeftShiftRow(QByteArray& row)
{
    QByteArray first;
    first.append(row[0]);
    for (int i = 0; i < row.size() - 1; i++)
    {
        row[i] = row[i + 1];
    }
    row[row.size() - 1] = first.back();
}

void MixColumns(vector<QByteArray>& state)
{
    vector<QByteArray> res = {QByteArrayLiteral("\x00\x00\x00\x00"),
                             QByteArrayLiteral("\x00\x00\x00\x00"),
                             QByteArrayLiteral("\x00\x00\x00\x00"),
                             QByteArrayLiteral("\x00\x00\x00\x00")};

    for (int i = 0; i < STATE_STR_SIZE; i++)
    {
        for (int j = 0; j < STATE_STR_SIZE; j++)
        {
            for (int k = 0; k < STATE_STR_SIZE; k++)
                res[i][j] = res[i][j] + state[i][k] * C[k][j];
        }
    }
    ByteMatrixCopy(res, state);
}

void ByteMatrixCopy(vector<QByteArray>& source, vector<QByteArray>& dest)
{
    for (int i = 0; i < source.size(); i++)
    {
        for (int j = 0; j < source.size(); j++)
        {
            dest[i][j] = source[i][j];
        }
    }
}
