using System;
using System.IO;
using System.Text;

namespace Hashing
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Enter the size of the hashtable: ");
            int hashTableSize = Convert.ToInt32(Console.ReadLine());
            float expectedResults = -1;

            string fileName = "";
            do
            {
                Console.Write("Enter name of input file: ");
                fileName = Console.ReadLine();
                if (!File.Exists(fileName))
                {
                    Console.WriteLine("File not found");
                }
            }
            while (!File.Exists(fileName));

            string[] input = File.ReadAllLines(fileName);

            HashNode[] hashtable = new HashNode[hashTableSize];

            #region 40% Linear OldHash
            Console.WriteLine("\nFilling to 40% capacity with old hash algorithm linear probing");
            int entries = 0;
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Linear);
                entries++;
            }

            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region 87% Linear OldHash
            Console.WriteLine("\nFilling to 87% capacity with old hash algorithm linear probing");
            entries = 0;
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Linear);
                entries++;
            }
            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region Random Collision handling OldHash

            #region 40% Random
            Console.WriteLine("\nFilling to 40% capacity with old hash algorithm random probing");
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            entries = 0;
            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Random);
                entries++;
            }

            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region 87% Random
            Console.WriteLine("\nFilling to 87% capacity with old hash algorithm random probing");
            // 87%
            entries = 0;
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Random);
                entries++;
            }
            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #endregion


            #region New Hash Algo
            Console.WriteLine("\nNew Hashing Function");

            #region 40% Linear
            Console.WriteLine("\nFilling to 40% capacity with new hash algorithm linear probing");
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            entries = 0;
            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Linear);
                entries++;
            }

            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion
            #region 87% Linear
            Console.WriteLine("\nFilling to 87% capacity with new hash algorithm linear probing");
            // 87% Linear
            entries = 0;
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Linear);
                entries++;
            }
            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region 40% Random
            Console.WriteLine("\nFilling to 40% capacity with new hash algorithm random probing");
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            entries = 0;
            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Random);
                entries++;
            }

            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion
            #region 87% Random
            Console.WriteLine("\nFilling to 87% capacity with new hash algorithm random probing");
            entries = 0;
            for (int i = 0; i < hashTableSize; i++)
            {
                hashtable[i] = new HashNode();
            }

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashtable, input[entries], ha, ProbeMode.Random);
                entries++;
            }
            PrintHashTable(hashtable);

            PrintProbeResults(hashtable, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion
            #endregion

            /*=========================================
                        Relative File
            =========================================*/
            Console.WriteLine("\n\nStarting Relative File Processing");
            Console.Write("Enter the new size of the hashtable: ");
            hashTableSize = Convert.ToInt32(Console.ReadLine());

            string hashTableFileName = "hashtable40LO.txt";
            StreamWriter sw = new StreamWriter(hashTableFileName, false);
            #region 40% Linear OldHash
            Console.WriteLine("\nFilling to 40% capacity with old hash algorithm linear probing");
            entries = 0;
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Linear);
                entries++;
            }

            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region 87% Linear OldHash
            Console.WriteLine("\nFilling to 87% capacity with old hash algorithm linear probing");
            hashTableFileName = "hashtable87LO.txt";
            sw = new StreamWriter(hashTableFileName, false);
            entries = 0;
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Linear);
                entries++;
            }
            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region Random Collision handling OldHash

            #region 40% Random
            Console.WriteLine("\nFilling to 40% capacity with old hash algorithm random probing");
            hashTableFileName = "hashtable40RO.txt";
            sw = new StreamWriter(hashTableFileName, false);
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            entries = 0;
            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Random);
                entries++;
            }

            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region 87% Random
            Console.WriteLine("\nFilling to 87% capacity with old hash algorithm random probing");
            // 87%
            entries = 0;
            hashTableFileName = "hashtable87RO.txt";
            sw = new StreamWriter(hashTableFileName, false);
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHashOld(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Random);
                entries++;
            }
            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #endregion


            #region New Hash Algo
            Console.WriteLine("\nNew Hashing Function");

            #region 40% Linear
            Console.WriteLine("\nFilling to 40% capacity with new hash algorithm linear probing");
            hashTableFileName = "hashtable40LN.txt";
            sw = new StreamWriter(hashTableFileName, false);
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            entries = 0;
            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Linear);
                entries++;
            }

            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion
            #region 87% Linear
            Console.WriteLine("\nFilling to 87% capacity with new hash algorithm linear probing");
            // 87% Linear
            entries = 0;
            hashTableFileName = "hashtable87LN.txt";
            sw = new StreamWriter(hashTableFileName, false);
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Linear);
                entries++;
            }
            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Linear);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Linear);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion

            #region 40% Random
            Console.WriteLine("\nFilling to 40% capacity with new hash algorithm random probing");
            hashTableFileName = "hashtable40RN.txt";
            sw = new StreamWriter(hashTableFileName, false);
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            entries = 0;
            while (entries < hashTableSize * 0.4f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Random);
                entries++;
            }

            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion
            #region 87% Random
            Console.WriteLine("\nFilling to 87% capacity with new hash algorithm random probing");
            entries = 0;
            hashTableFileName = "hashtable87RN.txt";
            sw = new StreamWriter(hashTableFileName, false);
            for (int i = 0; i < hashTableSize; i++)
            {
                sw.Write("{0,-50}", i + ",,,");
            }
            sw.Flush();
            sw.Close();

            while (entries < hashTableSize * 0.87f && entries < input.Length)
            {
                int ha = GetHash(input[entries], hashTableSize);
                InsertIntoHashTable(hashTableFileName, hashTableSize, input[entries], ha, ProbeMode.Random);
                entries++;
            }
            PrintHashTable(hashTableFileName, hashTableSize);

            PrintProbeResults(hashTableFileName, hashTableSize, input, 30, entries, ProbeMode.Random);
            expectedResults = CalculateExpectedProbes(entries, hashTableSize, ProbeMode.Random);
            Console.WriteLine("Theoretical probe count: " + expectedResults);
            #endregion
            #endregion


            Console.Write("Press any key to continue...");
            Console.Read();
        }

        public static int GetHashOld(string key, int tableSize)
        {
            long temp = ConvertStringToLong(key.Substring(0, 2));
            temp = ConvertStringToLong(key.Substring(5, 2));
            temp *= 256;
            temp += ConvertStringToLong(key.Substring(12, 1));
            temp %= tableSize;
            return (char)temp;
        }

        public static int GetHash(string key, int tableSize)
        {
            long temp = ConvertStringToLong(key.Substring(0, 4));
            temp += ConvertStringToLong(key.Substring(10, 1));
            temp %= tableSize;
            return (char)temp;
        }

        public static void InsertIntoHashTable(HashNode[] table, string key, int ha, ProbeMode mode)
        {
            int originalAddress = ha;
            int probes = 0;
            if (mode == ProbeMode.Linear)
            {
                while (!string.IsNullOrEmpty(table[ha].key))
                {
                    ha++;
                    ha %= table.Length;
                    probes++;
                }
            }
            else if (mode == ProbeMode.Random)
            {
                int randomSeed = 1234;
                Random rand = new Random(randomSeed);

                while (!string.IsNullOrEmpty(table[ha].key))
                {
                    int r = rand.Next(table.Length - 1);
                    ha = (ha + r) % table.Length;
                    probes++;
                }
            }

            table[ha].key = key;
            table[ha].firstHashAddress = originalAddress;
            table[ha].probes = probes + 1;
        }

        public static void InsertIntoHashTable(string fileName, int hastableSize, string key, int ha, ProbeMode mode, int lineLength = 50)
        {
            Stream stream = File.Open(fileName, FileMode.Open, FileAccess.ReadWrite);

            int originalAddress = ha;
            int probes = 0;
            if (mode == ProbeMode.Linear)
            {
                while (!string.IsNullOrEmpty(ReadLineHashInfo(stream, ha, lineLength)[1]))
                {
                    ha++;
                    ha %= hastableSize;
                    probes++;
                }
            }
            else if (mode == ProbeMode.Random)
            {
                int randomSeed = 1234;
                Random rand = new Random(randomSeed);
                
                while (!string.IsNullOrEmpty(ReadLineHashInfo(stream, ha, lineLength)[1]))
                {
                    int r = rand.Next(hastableSize - 1);
                    ha = (ha + r) % hastableSize;
                    probes++;
                }
            }

            char[] chars = string.Format("{0,-50}", ha + "," + key + "," + originalAddress + "," + (probes + 1)).ToCharArray();
            stream.Seek(ha * lineLength, SeekOrigin.Begin);
            byte[] write = Encoding.Default.GetBytes(chars, 0, lineLength);
            stream.Write(write, 0, lineLength);
            stream.Flush();
            stream.Close();
        }

        public static HashNode ProbeHashTable(HashNode[] table, string key, int ha, ProbeMode mode)
        {
            if (mode == ProbeMode.Linear)
            {
                // if key is not what is expected
                // then increment address and search there
                while (table[ha].key != key)
                {
                    ha++;
                    ha %= table.Length;
                }
            }
            else if (mode == ProbeMode.Random)
            {
                int randomSeed = 1234;
                Random rand = new Random(randomSeed);

                // if key is not what is expected
                // then add next random offset to address and search there
                while (table[ha].key != key)
                {
                    int r = rand.Next(table.Length - 1);
                    ha = (ha + r) % table.Length;
                }
            }

            return table[ha];
        }

        public static string[] ProbeHashTable(string fileName, int hastableSize, string key, int ha, ProbeMode mode, int lineLength = 50)
        {
            Stream stream = File.Open(fileName, FileMode.Open, FileAccess.ReadWrite);
            
            string[] hash = new string[4];

            if (mode == ProbeMode.Linear)
            {
                // if key is not what is expected
                // then increment address and search there
                while (!(hash = ReadLineHashInfo(stream, ha, lineLength))[1].Equals(key))
                {
                    ha++;
                    ha %= hastableSize;
                }
            }
            else if (mode == ProbeMode.Random)
            {
                int randomSeed = 1234;
                Random rand = new Random(randomSeed);
                                
                while (!(hash = ReadLineHashInfo(stream, ha, lineLength))[1].Equals(key))
                {
                    int r = rand.Next(hastableSize - 1);
                    ha = (ha + r) % hastableSize;
                }
            }
            stream.Flush();
            stream.Close();

            return hash;
        }

        public static void PrintProbeResults(HashNode[] table, string[] input, int n, int tableEntries, ProbeMode mode)
        {
            int prb = 0, max = 0, total = 0;
            float avg = 0.0f;
            int min = 99999;
            int cnt = 0;
            while (cnt < n)
            {
                prb = ProbeHashTable(table, input[cnt], GetHashOld(input[cnt], table.Length), mode).probes;
                total += prb;
                if (prb < min) min = prb;
                if (prb > max) max = prb;

                cnt++;
            }
            avg = (float)total / (float)n;
            Console.WriteLine("First " + n + " " + mode.ToString() + " Probes: min = " + min + ", max = " + max + ", avg = " + avg.ToString("0.00"));

            prb = max = total = 0;
            avg = 0.0f;
            min = 99999;
            cnt = 0;
            while (cnt < n)
            {
                if (cnt >= input.Length) break;
                prb = ProbeHashTable(table, input[tableEntries - 1 - cnt], GetHashOld(input[tableEntries - 1 - cnt], table.Length), ProbeMode.Linear).probes;
                total += prb;
                if (prb < min) min = prb;
                if (prb > max) max = prb;

                cnt++;
            }
            avg = (float)total / (float)n;
            Console.WriteLine("Last " + n + " " + mode.ToString() + " Probes: min = " + min + ", max = " + max + ", avg = " + avg.ToString("0.00"));
        }

        public static void PrintProbeResults(string fileName, int hastableSize, string[] input, int n, int tableEntries, ProbeMode mode, int lineLength = 50)
        {
            int prb = 0, max = 0, total = 0;
            float avg = 0.0f;
            int min = 99999;
            int cnt = 0;
            string[] probe;
            while (cnt < n)
            {
                probe = ProbeHashTable(fileName, hastableSize, input[cnt], GetHashOld(input[cnt], hastableSize), mode);

                prb = 0;
                int.TryParse(probe[3], out prb);
                total += prb;
                if (prb < min) min = prb;
                if (prb > max) max = prb;

                cnt++;
            }
            avg = (float)total / (float)n;
            Console.WriteLine("First " + n + " " + mode.ToString() + " Probes: min = " + min + ", max = " + max + ", avg = " + avg.ToString("0.00"));

            prb = max = total = 0;
            avg = 0.0f;
            min = 99999;
            cnt = 0;
            while (cnt < n)
            {
                probe = ProbeHashTable(fileName, hastableSize, input[tableEntries - 1 - cnt], GetHashOld(input[tableEntries - 1 - cnt], hastableSize), mode);

                prb = 0;
                int.TryParse(probe[3], out prb);
                total += prb;
                if (prb < min) min = prb;
                if (prb > max) max = prb;

                cnt++;
            }
            avg = (float)total / (float)n;
            
            Console.WriteLine("Last " + n + " " + mode.ToString() + " Probes: min = " + min + ", max = " + max + ", avg = " + avg.ToString("0.00"));
        }

        public static float CalculateExpectedProbes(int numKyes, int tableSize, ProbeMode mode)
        {
            float e = -1;
            float a = (float)numKyes / (float)tableSize;
            if(mode == ProbeMode.Linear)
            {
                e = (1 - a / 2) / (1 - a);
            }
            else if(mode == ProbeMode.Random)
            {
                e = -(1 / a) * (float)Math.Log(1 - a);
            }

            return e;
        }

        public static void PrintHashTable(HashNode[] table)
        {
            Console.WriteLine("{0, -8}|{1, -20}|{2, -17}|{3, -10}|", "ADDRESS", "KEY", "ORIGINAL ADDRESS", "PROBES");
            for (int i = 0; i < table.Length; i++)
            {
                Console.WriteLine("{0, -8}|{1}", i, table[i].ToString());
            }
        }

        public static void PrintHashTable(string fileName, int hastableSize, int lineLength = 50)
        {
            Stream stream = File.Open(fileName, FileMode.Open, FileAccess.Read);

            byte[] buffer = new byte[lineLength];
            string line = "";
            Console.WriteLine("{0, -8}|{1, -20}|{2, -17}|{3, -10}|", "ADDRESS","KEY", "ORIGINAL ADDRESS", "PROBES");
            for (int i = 0; i < hastableSize; i++)
            {
                stream.Seek(i * lineLength, SeekOrigin.Begin);
                stream.Read(buffer, 0, lineLength);
                line = Encoding.Default.GetString(buffer);
                string[] hashData = line.Split(new char[] { ',' }, StringSplitOptions.None);
                string output = "";

                if (!string.IsNullOrEmpty(hashData[1]))
                    output += string.Format("{0, -20}|", hashData[1]);
                else
                    output += string.Format("{0, -20}|", "");

                if (!string.IsNullOrEmpty(hashData[2]))
                    output += string.Format("{0, -17}|", hashData[2]);
                else
                    output += string.Format("{0, -17}|", "");

                int probes = 1;
                int.TryParse(hashData[3], out probes);
                if (int.TryParse(hashData[3], out probes))
                    output += string.Format("{0, -10}|", probes);
                else
                    output += string.Format("{0, -10}|", "");

                Console.WriteLine("{0, -8}|{1}", i, output);
            }

            stream.Flush();
            stream.Close();
        }

        public static string[] ReadLineHashInfo(Stream stream, int lineNumber, int lineLength = 50)
        {
            byte[] buffer = new byte[lineLength];
            stream.Seek(lineNumber * lineLength, SeekOrigin.Begin);
            stream.Read(buffer, 0, lineLength);
            string line = Encoding.Default.GetString(buffer);
            string[] hash = line.Split(new char[] { ',' }, StringSplitOptions.None);

            return hash;
        }

        public static long ConvertStringToLong(string str)
        {
            long result = 0;
            str = str.ToUpper();
            foreach (char c in str)
            {
                result *= 10;
                int parse = 0;
                if (int.TryParse(c.ToString(), out parse))
                    result += parse; // already a number
                else if (!c.Equals(' '))
                    result += (int)c - 64; // converts letter to number
            }

            return result;
        }
    }

    public enum ProbeMode { Linear, Random }

    public class HashNode
    {
        public string key;
        public int? firstHashAddress;
        public int probes;

        public HashNode()
        {
            key = null;
            firstHashAddress = null;
            probes = 0;
        }

        public override string ToString()
        {
            string output = "";
            
            if (!string.IsNullOrEmpty(key))
                output += string.Format("{0, -20}|", key);
            else
                output += string.Format("{0, -20}|", "");

            if (firstHashAddress != null)
                output += string.Format("{0, -17}|", firstHashAddress);
            else
                output += string.Format("{0, -17}|", "");

            if (probes != 0)
                output += string.Format("{0, -10}|", probes);
            else
                output += string.Format("{0, -10}|", "");

            return output;
        }
    }
}
