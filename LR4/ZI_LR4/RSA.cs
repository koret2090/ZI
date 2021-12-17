using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace ZI_LR4
{
    class RSA
    {
        public Random random;
        int n;
        int phi;
        int publicKey;
        int privateKey;

        public RSA()
        {
            random = new Random();
            List<int> nums = GeneratePrimeNumbers();
            int p = nums[0];
            int q = nums[1];
            n = p * q;
            phi = (p - 1) * (q - 1);
            publicKey = GeneratePublicKey(phi);
            GeneratePrivateKey(publicKey, phi, out int x, out int y);
            privateKey = x;

            if (privateKey < 0)
                privateKey += phi;
        }

        public List<int> GeneratePrimeNumbers()
        {
            int randomNumber1 = random.Next(1000, 9999);
            while (!isPrime(randomNumber1))
            {
                randomNumber1 = random.Next(1000, 9999);
            }
            
            int randomNumber2 = random.Next(1000, 9999);
            while (!isPrime(randomNumber2) || randomNumber1 == randomNumber2)
            {
                randomNumber2 = random.Next(1000, 9999);
            }

            List<int> nums = new List<int>();
            nums.Add(randomNumber1);
            nums.Add(randomNumber2);

            return nums;
        }

        public bool isPrime(int num)
        {
            for (int i = 2; i < num; i++)
            {
                if (num % i == 0)
                    return false;
            }
            return true;
        }

        public int GCD(int num1, int num2)
        {
            int temp;
            while (num2 != 0)
            {
                temp = num1;
                num1 = num2;
                num2 = temp % num2;
            }
            return num1;
        }

        public int GeneratePublicKey(int phi)
        {
            int nod = 0;
            int num = -1;
            while (nod != 1)
            {
                num = random.Next(2, phi);
                nod = GCD(phi, num);
            }
            return num;
        }

        public int GeneratePrivateKey(int a, int b, out int x, out int y)
        {
            if (a == 0)
            {
                x = 0;
                y = 1;
                return b;
            }

            int d = GeneratePrivateKey(b % a, a, out var x1, out var y1);
            x = y1 - (b / a) * x1;
            y = x1;
            return d;
        }

        public int Encrypt(int m)
        {
            return (int)BigInteger.ModPow(m, publicKey, n);
        }

        public int Decrypt(int c)
        {
            return (int)BigInteger.ModPow(c, privateKey, n);
        }
    }
}
