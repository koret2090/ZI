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
            privateKey = GeneratePrivateKey(publicKey, phi);
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

        public int GeneratePrivateKey(int publicKey, int phi)
        {
            int t = 0;
            int r = phi; // остаток от деления
            int newt = 1;
            int newr = publicKey;

            while (newr != 0)
            {
                int quotient = r / newr;
                int tmpt = newt;
                newt = t - quotient * newt;
                t = tmpt;

                int tmpr = newr;
                newr = r - quotient * newr;
                r = tmpr;
            }

            if (r > 1)
                return -1;
            if (t < 0)
                t += phi;

            return t;
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
