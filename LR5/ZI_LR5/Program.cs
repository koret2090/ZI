using System;

namespace ZI_LR5
{
    class Program
    {
        static void Main()
        {
            var sign = new Sign("SHA256");

            string dataFilename = "text.txt";
            string signFilename = "signature.txt";

            //sign.DoSign(dataFilename, signFilename);

            
            if (sign.CheckSign(dataFilename, signFilename))
                Console.WriteLine("OK");
            else
                Console.WriteLine("Fail");
            Console.Read();
            
        }
    }
}
