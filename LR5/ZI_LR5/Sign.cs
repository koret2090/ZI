using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace ZI_LR5
{
    class Sign
    {
        HashAlgorithm hashAlg;

        RSACryptoServiceProvider cryptoProvider;
        RSAPKCS1SignatureDeformatter deformatter;
        RSAPKCS1SignatureFormatter formatter;

        public Sign(string hashAlgName)
        {
            hashAlg = HashAlgorithm.Create(hashAlgName);

            cryptoProvider = new RSACryptoServiceProvider(); // создаются ключи здесь
            formatter = new RSAPKCS1SignatureFormatter(cryptoProvider);
            deformatter = new RSAPKCS1SignatureDeformatter(cryptoProvider);

            formatter.SetHashAlgorithm(hashAlgName);
            deformatter.SetHashAlgorithm(hashAlgName);
        }

        public void DoSign(string filenameSource, string filenameSignature)
        {
            FileStream reader = new FileStream(filenameSource, FileMode.Open);
            BinaryWriter writer = new BinaryWriter(new FileStream(filenameSignature, FileMode.Create));
            
            // рассказывам всем о своей подписи (закрытый ключ RSA - открытый для всех для подписи)
            var key = cryptoProvider.ExportCspBlob(true);
            writer.Write(key.Length);
            writer.Write(key);

            var hash = hashAlg.ComputeHash(reader);
            var signed_hash = formatter.CreateSignature(hash);
            int hash_len = signed_hash.Length;

            writer.Write(hash_len);
            writer.Write(signed_hash);
            

            reader.Close();
            writer.Close();
        }

        public bool CheckSign(string filename, string signatureFilename)
        {
            bool isCorrect = false;
            BinaryReader signatureReader = new BinaryReader(new FileStream(signatureFilename, FileMode.Open));
            FileStream reader = new FileStream(filename, FileMode.Open);
                
            var key = signatureReader.ReadBytes(signatureReader.ReadInt32());
            cryptoProvider.ImportCspBlob(key);

            var hash_len = signatureReader.ReadInt32();
            var signed_hash = signatureReader.ReadBytes(hash_len);

            var hash = hashAlg.ComputeHash(reader);

            isCorrect = deformatter.VerifySignature(hash, signed_hash);

            signatureReader.Close();
            reader.Close();

            return isCorrect;
        }
    }
}
