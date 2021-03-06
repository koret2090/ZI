#include "aes.h"
#include <QDebug>
AES::AES(char key_str[17])
{
    SBox = {QByteArray("\x63\x7C\x77\x7B\xF2\x6B\x6F\xC5\x30\x01\x67\x2B\xFE\xD7\xAB\x76"),
           QByteArrayLiteral("\xCA\x82\xC9\x7D\xFA\x59\x47\xF0\xAD\xD4\xA2\xAF\x9C\xA4\x72\xC0"),
           QByteArrayLiteral("\xB7\xFD\x93\x26\x36\x3F\xF7\xCC\x34\xA5\xE5\xF1\x71\xD8\x31\x15"),
           QByteArrayLiteral("\x04\xC7\x23\xC3\x18\x96\x05\x9A\x07\x12\x80\xE2\xEB\x27\xB2\x75"),
           QByteArrayLiteral("\x09\x83\x2C\x1A\x1B\x6E\x5A\xA0\x52\x3B\xD6\xB3\x29\xE3\x2F\x84"),
           QByteArrayLiteral("\x53\xD1\x00\xED\x20\xFC\xB1\x5B\x6A\xCB\xBE\x39\x4A\x4C\x58\xCF"),
           QByteArrayLiteral("\xD0\xEF\xAA\xFB\x43\x4D\x33\x85\x45\xF9\x02\x7F\x50\x3C\x9F\xA8"),
           QByteArrayLiteral("\x51\xA3\x40\x8F\x92\x9D\x38\xF5\xBC\xB6\xDA\x21\x10\xFF\xF3\xD2"),
           QByteArrayLiteral("\xCD\x0C\x13\xEC\x5F\x97\x44\x17\xC4\xA7\x7E\x3D\x64\x5D\x19\x73"),
           QByteArrayLiteral("\x60\x81\x4F\xDC\x22\x2A\x90\x88\x46\xEE\xB8\x14\xDE\x5E\x0B\xDB"),
           QByteArrayLiteral("\xE0\x32\x3A\x0A\x49\x06\x24\x5C\xC2\xD3\xAC\x62\x91\x95\xE4\x79"),
           QByteArrayLiteral("\xE7\xC8\x37\x6D\x8D\xD5\x4E\xA9\x6C\x56\xF4\xEA\x65\x7A\xAE\x08"),
           QByteArrayLiteral("\xBA\x78\x25\x2E\x1C\xA6\xB4\xC6\xE8\xDD\x74\x1F\x4B\xBD\x8B\x8A"),
           QByteArrayLiteral("\x70\x3E\xB5\x66\x48\x03\xF6\x0E\x61\x35\x57\xB9\x86\xC1\x1D\x9E"),
           QByteArrayLiteral("\xE1\xF8\x98\x11\x69\xD9\x8E\x94\x9B\x1E\x87\xE9\xCE\x55\x28\xDF"),
           QByteArrayLiteral("\x8C\xA1\x89\x0D\xBF\xE6\x42\x68\x41\x99\x2D\x0F\xB0\x54\xBB\x16")};

    SBoxReversed = {QByteArrayLiteral("\x52\x09\x6A\xD5\x30\x36\xA5\x38\xBF\x40\xA3\x9E\x81\xF3\xD7\xFB"),
                    QByteArrayLiteral("\x7C\xE3\x39\x82\x9B\x2F\xFF\x87\x34\x8E\x43\x44\xC4\xDE\xE9\xCB"),
                    QByteArrayLiteral("\x54\x7B\x94\x32\xA6\xC2\x23\x3D\xEE\x4C\x95\x0B\x42\xFA\xC3\x4E"),
                    QByteArrayLiteral("\x08\x2E\xA1\x66\x28\xD9\x24\xB2\x76\x5B\xA2\x49\x6D\x8B\xD1\x25"),
                    QByteArrayLiteral("\x72\xF8\xF6\x64\x86\x68\x98\x16\xD4\xA4\x5C\xCC\x5D\x65\xB6\x92"),
                    QByteArrayLiteral("\x6C\x70\x48\x50\xFD\xED\xB9\xDA\x5E\x15\x46\x57\xA7\x8D\x9D\x84"),
                    QByteArrayLiteral("\x90\xD8\xAB\x00\x8C\xBC\xD3\x0A\xF7\xE4\x58\x05\xB8\xB3\x45\x06"),
                    QByteArrayLiteral("\xD0\x2C\x1E\x8F\xCA\x3F\x0F\x02\xC1\xAF\xBD\x03\x01\x13\x8A\x6B"),
                    QByteArrayLiteral("\x3A\x91\x11\x41\x4F\x67\xDC\xEA\x97\xF2\xCF\xCE\xF0\xB4\xE6\x73"),
                    QByteArrayLiteral("\x96\xAC\x74\x22\xE7\xAD\x35\x85\xE2\xF9\x37\xE8\x1C\x75\xDF\x6E"),
                    QByteArrayLiteral("\x47\xF1\x1A\x71\x1D\x29\xC5\x89\x6F\xB7\x62\x0E\xAA\x18\xBE\x1B"),
                    QByteArrayLiteral("\xFC\x56\x3E\x4B\xC6\xD2\x79\x20\x9A\xDB\xC0\xFE\x78\xCD\x5A\xF4"),
                    QByteArrayLiteral("\x1F\xDD\xA8\x33\x88\x07\xC7\x31\xB1\x12\x10\x59\x27\x80\xEC\x5F"),
                    QByteArrayLiteral("\x60\x51\x7F\xA9\x19\xB5\x4A\x0D\x2D\xE5\x7A\x9F\x93\xC9\x9C\xEF"),
                    QByteArrayLiteral("\xA0\xE0\x3B\x4D\xAE\x2A\xF5\xB0\xC8\xEB\xBB\x3C\x83\x53\x99\x61"),
                    QByteArrayLiteral("\x17\x2B\x04\x7E\xBA\x77\xD6\x26\xE1\x69\x14\x63\x55\x21\x0C\x7D")};

    C = {QByteArrayLiteral("\x02\x03\x01\x01"),
        QByteArrayLiteral("\x01\x02\x03\x01"),
        QByteArrayLiteral("\x01\x01\x02\x03"),
        QByteArrayLiteral("\x03\x01\x01\x02")};

    CReversed = {QByteArrayLiteral("\x0E\x0B\x0D\x09"),
                 QByteArrayLiteral("\x09\x0E\x0B\x0D"),
                 QByteArrayLiteral("\x0D\x09\x0E\x0B"),
                 QByteArrayLiteral("\x0B\x0D\x09\x0E")};


    RCon = {QByteArrayLiteral("x00\x00\x00\x00"),
    QByteArrayLiteral("x01\x00\x00\x00"),
    QByteArrayLiteral("x02\x00\x00\x00"),
    QByteArrayLiteral("x04\x00\x00\x00"),
    QByteArrayLiteral("x08\x00\x00\x00"),
    QByteArrayLiteral("x10\x00\x00\x00"),
    QByteArrayLiteral("x20\x00\x00\x00"),
    QByteArrayLiteral("x40\x00\x00\x00"),
    QByteArrayLiteral("x80\x00\x00\x00"),
    QByteArrayLiteral("x1b\x00\x00\x00"),
    QByteArrayLiteral("x36\x00\x00\x00")};

    Key = QByteArray(key_str);

    Nk = 4;
    Nb = 4;
    Nr = 10;
    qDebug() << Key[0];
    KeyExpansion();
}



void AES::SubBytes(vector<QByteArray>& state)
{    
    for (int i = 0; i < STATE_STR_SIZE; i++)
    {
        SubWord(state[i]);
    }
}

void AES::SubWord(QByteArray &word)
{
    for (int i = 0; i < word.size(); i++)
    {
        QByteArray byteNum;
        byteNum.append(word[i]); // ?????????? ???????????? ?????????????????? ???? ???????? ???????????????? ???????? ?? ????????

        unsigned int num = byteNum.toHex().toUInt(nullptr, 16);

        //byteNum[i] = byteNum[i] / 0x10;

        unsigned int row = num / 16;
        unsigned int col = num % 16;
        word[i] = SBox[row][col];
    }
}

void AES::ShiftRows(vector<QByteArray>& state)
{
    for (int i = 1; i < STATE_STR_SIZE; i++)
    {
        for (int shifts = 0; shifts < i; shifts++)
        {
            LeftShiftRow(state[i]);
        }
    }
}

void AES::LeftShiftRow(QByteArray& row)
{
    QByteArray first;
    first.append(row[0]);
    for (int i = 0; i < row.size() - 1; i++)
    {
        row[i] = row[i + 1];
    }
    row[row.size() - 1] = first.back();
}

void AES::RotWord(QByteArray &word)
{
    LeftShiftRow(word);
}

void AES::MixColumns(vector<QByteArray>& state)
{
    for (int i = 0; i < 4; i++)
    {
        //QByteArray curCol = QByteArray("\x00\x00\x00\x00");
        QByteArray curCol;
        for (int j = 0; j < 4; j++)
        {
            curCol[j] = state[i][j];
        }

        ///////////////////////////////
        unsigned char a[4], b[4];
        for (unsigned char c = 0; c < 4; c++)
        {
            a[c] = curCol[c];
            unsigned char h = (unsigned char)((signed char)curCol[c] >> 7);
            b[c] = curCol[c] << 1;
            b[c] ^= 0x1B & h;
        }
        ////////////////////////////////

        state[i][0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];    // 2a0 + a3 + a2 + 3a1
        state[i][1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];    // 2a1 + a0 + a3 + 3a2
        state[i][2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];    // 2a2 + a1 + a0 + 3a3
        state[i][3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];    // 2a3 + a2 + a1 + 3a0
    }
}

void AES::ByteMatrixCopy(vector<QByteArray> source, vector<QByteArray> dest)
{
    for (int i = 0; i < source.size(); i++)
    {
        for (int j = 0; j < source.size(); j++)
        {
            dest[i][j] = source[i][j];
        }
    }
}

QByteArray AES::XorWord(QByteArray &word1, QByteArray &word2)
{
    QByteArray res;
    for (int i = 0; i < 4; i++)
    {
        res.push_back(word1[i] ^ word2[i]);
    }
    return res;
}

void AES::FillKey()
{
    for (int i = 0; i < Nb * (Nr + 1); i++)
    {
        roundKey.push_back(QByteArrayLiteral("\x00\x00\x00\x00"));
    }
}

void AES::KeyExpansion()
{
    FillKey();

    for (int i = 0; i < Nk; i++)
    {
        QByteArray temp;
        for (int j = 0; j < 4; j++)
        {
            temp.append(Key[Nk * i + j]);
        }
        roundKey[i] = temp;
    }

    for (int i = Nk; i < Nb * (Nr + 1); i++)
    {
        QByteArray temp = roundKey[i - 1];
        if (i % Nk == 0)
        {
            LeftShiftRow(temp);
            SubWord(temp);
            temp = XorWord(temp, RCon[i / Nk]);
        }
        else if (Nk > 6 && (i % Nk == 4))
        {
            SubWord(temp);
        }
        roundKey[i] = XorWord(roundKey[i - Nk], temp);
    }
}

void AES::AddRoundKey(vector<QByteArray> &state, vector<QByteArray> &key, int roundIter)
{
    for (int i = 0; i < STATE_STR_SIZE; i++)
    {
        for (int j = 0; j < STATE_STR_SIZE; j++)
        {
            state[i][j] = state[i][j] ^ key[4 * roundIter + i][j];
        }
    }
}


// ?????????????? ???????????? ?????? ?????????? ???????????????? ??????????
void AES::Encode(string aesFile, string aesFileEncode)
{
    //?????? ????????????????????
    QFile fileRead(aesFile.c_str());
    fileRead.open(QIODevice::ReadOnly);
    QByteArray in;

    // ?????? ????????????
    QFile fileWrite(aesFileEncode.c_str());
    fileWrite.open(QIODevice::WriteOnly); //?????????????????? ?????? Add

    int lastSize = 16;
    while (!fileRead.atEnd())
    {
        in = fileRead.read(Nk * Nb);

        state = {QByteArrayLiteral("\x00\x00\x00\x00"),
                 QByteArrayLiteral("\x00\x00\x00\x00"),
                 QByteArrayLiteral("\x00\x00\x00\x00"),
                 QByteArrayLiteral("\x00\x00\x00\x00")};

        // ?????????????????? state
        for (int i = 0; i < STATE_STR_SIZE; i++)
        {
            for (int j = 0; j < STATE_STR_SIZE; j++)
            {
                state[i][j] = in[i + j * 4];
            }
        }

        // ??????????????
        EncodeBlock();

        QByteArray out;

        for (unsigned int i = 0; i < state.size(); i++)
        {
            for (unsigned int j = 0; j < state.size(); j++)
            {
                out.push_back(state[j][i]);
            }
        }
        fileWrite.write(out);
    }
    fileWrite.close();
    fileRead.close();
}

void AES::EncodeBlock()
{
    AddRoundKey(state, roundKey, 0);

    for (int round = 1; round < Nr; round++)
    {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, roundKey, round);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, roundKey, Nr);
}

void AES::InvSubBytes(vector<QByteArray>& state)
{
    for (int i = 0; i < STATE_STR_SIZE; i++)
    {
        InvSubWord(state[i]);
    }
}

void AES::InvSubWord(QByteArray &word)
{
    for (int i = 0; i < word.size(); i++)
    {
        QByteArray byteNum;
        byteNum.append(word[i]);

        unsigned int num = byteNum.toHex().toUInt(nullptr, 16);

        //byteNum[i] = byteNum[i] / 0x10;

        unsigned int row = num / 16;
        unsigned int col = num % 16;
        word[i] = SBoxReversed[row][col];
    }
}

void AES::InvShiftRows(vector<QByteArray>& state)
{
    for (int i = 1; i < STATE_STR_SIZE; i++)
    {
        for (int shifts = 0; shifts < i; shifts++)
        {
            RightShiftRow(state[i]);
        }
    }
}

void AES::RightShiftRow(QByteArray& row)
{
    QByteArray last;
    last.append(row[row.size() - 1]);
    for (int i = row.size() - 1; i > 0; i--)
    {
        row[i] = row[i - 1];
    }
    row[0] = last.back();
}

void AES::InvMixColumns(vector<QByteArray>& state)
{
    for (int i = 0; i < 4; i++) {
        QByteArray curCol;
        for (int j = 0; j < 4; j++)
        {
            curCol[j] = state[i][j];
        }

        state[i][0] = gMul(curCol[0], 14) ^ gMul(curCol[3], 9) ^ gMul(curCol[2], 13) ^ gMul(curCol[1], 11);
        state[i][1] = gMul(curCol[1], 14) ^ gMul(curCol[0], 9) ^ gMul(curCol[3], 13) ^ gMul(curCol[2], 11);
        state[i][2] = gMul(curCol[2], 14) ^ gMul(curCol[1], 9) ^ gMul(curCol[0], 13) ^ gMul(curCol[3], 11);
        state[i][3] = gMul(curCol[3], 14) ^ gMul(curCol[2], 9) ^ gMul(curCol[1], 13) ^ gMul(curCol[0], 11);
    }
}

unsigned char AES::gMul(unsigned char a, unsigned char b)
{
    unsigned char res = 0;
    for (unsigned char counter = 0; counter < 8; counter++) {
        if ((b & 1) == 1) {
            res ^= a;
        }

        unsigned char h = static_cast<unsigned char>(a & 0x80);
        a <<= 1;

        if (h == 0x80) {
            a ^= 0x1b;
        }

        b >>= 1;
    }

    return res;
}

void AES::Decode(string aesFileEncoded, string aesFileDecoded)
{
    //?????? ????????????????????
    QFile file(aesFileEncoded.c_str());
    file.open(QIODevice::ReadOnly);
    QByteArray in;

    // ?????? ????????????
    QFile fileWrite(aesFileDecoded.c_str());
    fileWrite.open(QIODevice::WriteOnly); //?????????????????? ?????? Add

    int lastSize = 16;
    while (!file.atEnd())
    {
        in = file.read(Nk * Nb);

        state = {QByteArrayLiteral("\x00\x00\x00\x00"),
                 QByteArrayLiteral("\x00\x00\x00\x00"),
                 QByteArrayLiteral("\x00\x00\x00\x00"),
                 QByteArrayLiteral("\x00\x00\x00\x00")};

        // ?????????????????? state
        for (int i = 0; i < STATE_STR_SIZE; i++)
        {
            for (int j = 0; j < STATE_STR_SIZE; j++)
            {
                state[i][j] = in[i + j * 4];
            }
        }

        // ??????????????
        DecodeBlock();

        QByteArray out;

        for (unsigned int i = 0; i < state.size(); i++)
        {
            for (unsigned int j = 0; j < state.size(); j++)
            {
                out.push_back(state[j][i]);
            }
        }
        fileWrite.write(out);
    }
    fileWrite.close();
    file.close();
}

void AES::DecodeBlock()
{
    AddRoundKey(state, roundKey, Nr);

    for (int round = Nr - 1; round > 0; round--)
    {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, roundKey, round);
        InvMixColumns(state);
    }

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, roundKey, 0);
}
