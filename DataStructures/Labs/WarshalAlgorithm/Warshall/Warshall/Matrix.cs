using System.IO;

namespace Warshall
{
    class Matrix
    {
        //Create Matrix of generic type
        public static T[,] CreateMatrix<T>(int matrixSize, T falseValue)
        {
            T[,] tempMatrix = new T[matrixSize, matrixSize];

            //default all links to 0
            for (int i = 0; i < matrixSize; i++)
            {
                for (int j = 0; j < matrixSize; j++)
                {
                    tempMatrix[i, j] = falseValue;
                }
            }

            return tempMatrix;
        }

        public static string[] CreateMatrixNames(int size)
        {
            return new string[size];
        }

        //Use Warshall's Algorithm to mark nodes that can communicate with each other
        public static void GetLinkedNodes<T>(ref T[,] matrix, T trueValue, T falseValue)
        {
            int matrixLength = matrix.GetLength(0);

            for (int i = 0; i < matrixLength; i++)
            {
                for (int j = 0; j < matrixLength; j++)
                {
                    if (object.Equals(matrix[j, i], trueValue))
                    {
                        for (int k = 0; k < matrixLength; k++)
                        {
                            matrix[j, k] = or(matrix[j, k], matrix[i, k], trueValue, falseValue);
                        }
                    }
                }
            }
        }

        //No operator overloading in C#
        //Function to handle the "or" operation
        static T or<T>(T i, T j, T trueValue, T falseValue)
        {
            T result = falseValue;

            if (object.Equals(i, trueValue) || object.Equals(j, trueValue))
                result = trueValue;

            return result;
        }

        //read from file
        public static string[] ReadInputFromFile(string fileName)
        {
            string[] fileContent;

            //open, read, and close file
            fileContent = File.ReadAllLines(fileName);

            return fileContent;
        }

        //Create matrix in single string format
        public static string ToString<T>(T[,] matrix, string[] names)
        {
            string outstring = "";
            int n = matrix.GetLength(0);
            outstring += "\n\t";
            for (int j = 0; j < n; j++)
            {
                outstring += names[j] + "\t";
            }
            outstring += "\n";
            for (int j = 0; j < 6 * (n) + 1; j++)
            {
                outstring += "-";
            }

            for (int i = 0; i < n; i++)
            {
                outstring += "\n" + names[i] + " |\t";
                for (int j = 0; j < n; j++)
                {
                    outstring += matrix[i, j] + " |\t";
                }
                outstring += "\n";
                for (int j = 0; j < 6 * (n) + 1; j++)
                {
                    outstring += "-";
                }

            }
            outstring += "\n\n";

            return outstring;
        }

        //Output text to specified file
        public static void WriteToFile(string fileName, string output)
        {
            output = fileName + "\n\n" + output;
            File.WriteAllText(fileName, output);
        }
    }
}