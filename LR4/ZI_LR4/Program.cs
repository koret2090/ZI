using System;
using System.IO;

namespace ZI_LR4
{
    class Program
    {
        static void Main(string[] args)
        {
            RSA rsa = new RSA();

            string toRead = "text.txt";
            string toEncode = "encoded.txt";
            string toDecode = "decoded.txt";

            EncodeFile(rsa, toRead, toEncode);
            DecodeFile(rsa, toEncode, toDecode);
        }

        public static void EncodeFile(RSA rsa, string from, string to)
        {
            FileStream fileFrom = new FileStream(from, FileMode.Open);
            FileStream fileTo = new FileStream(to, FileMode.Create);
            BinaryWriter binWriter = new BinaryWriter(fileTo);

            int symbol;
            while (fileFrom.CanRead)
            {
                symbol = fileFrom.ReadByte();
                if (symbol == -1)
                    break;
                int res = rsa.Encrypt(symbol);
                binWriter.Write(res);
            }
            binWriter.Write(-1);

            binWriter.Close();
            fileTo.Close();
            fileFrom.Close();
        }

        public static void DecodeFile(RSA rsa, string from, string to)
        {
            FileStream fileFrom = new FileStream(from, FileMode.Open);
            FileStream fileTo = new FileStream(to, FileMode.Create);
            BinaryReader binReader = new BinaryReader(fileFrom);
            BinaryWriter binWriter = new BinaryWriter(fileTo);

            int symbol;
            while (fileFrom.CanRead)
            {
                symbol = binReader.ReadInt32();
                if (symbol == -1)
                    break;
                int res = rsa.Decrypt(symbol);

                binWriter.Write((byte)res);
            }
            binWriter.Close();
            binReader.Close();
            fileTo.Close();
            fileFrom.Close();
        }
    }
}
