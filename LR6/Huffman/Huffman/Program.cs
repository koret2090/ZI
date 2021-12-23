using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace Huffman
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Compress or decompress? (c/d)");
            string method = Console.ReadLine();

            if (method == "c")
            {
                var data = File.ReadAllText("test.txt");
                var tree = new Tree(data);
                tree.Build();
                var encoded = tree.Encode(data);

                int bytes = encoded.Count / 8;
                if ((encoded.Count % 8) != 0) bytes++;
                byte[] arr = new byte[bytes + 1];
                int bitIndex = 0, byteIndex = 0;
                for (int i = 0; i < encoded.Count; i++)
                {
                    if (encoded[i])
                    {
                        arr[byteIndex] |= (byte)(((byte)1) << bitIndex);
                    }
                    bitIndex++;
                    if (bitIndex == 8)
                    {
                        bitIndex = 0;
                        byteIndex++;
                    }
                }

                // trash bits amount
                arr[bytes] = Convert.ToByte(8 - (encoded.Count % 8) + 8);                

                File.WriteAllBytes("en.txt", arr);
                File.WriteAllText("fr.txt", JsonSerializer.Serialize(tree.Frequencies));
            }
            else if (method == "d")
            {
                var fr = JsonSerializer.Deserialize<Dictionary<char, int>>(File.ReadAllText("fr.txt"));
                var encoded = File.ReadAllBytes("en.txt");
                var bits = new BitArray(encoded);
                int trashBits = Convert.ToInt32(encoded[encoded.Length - 1]);
                var bools = new List<bool>();

                for (var i = 0; i < bits.Length - trashBits; i++)
                {
                    bools.Add((bool)bits[i]);
                }

                var tree = new Tree(fr);
                tree.Build();
                var decoded = tree.Decode(bools);
                Console.WriteLine("Decoded: " + decoded);
            }
        }
    }
}