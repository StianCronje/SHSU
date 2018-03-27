using System;
using System.IO;

namespace Warshall
{
    class LinkedNodes
    {
        public static void Main(string[] args)
        {
            string resp = "n";
            do
            {
                string fileInName = "", fileOutName = "";
                int matrixSize = 0;

                //get number of nodes to determine the matrix size
                Console.Write("Enter the number of nodes: ");
                matrixSize = Convert.ToInt32(Console.ReadLine());

                //create matrix
                int[,] nodeMatrix = Matrix.CreateMatrix<int>(matrixSize, 0);
                string[] nodeNames = Matrix.CreateMatrixNames(matrixSize);

                //name the nodes
                Console.Write("Would you like to name the nodes? [y/n]: ");
                resp = Console.ReadLine();
                if (resp.ToUpper().Equals("Y"))
                {
                    for (int i = 0; i < matrixSize; i++)
                    {
                        Console.Write("Enter name for node " + (i + 1) + ": ");
                        nodeNames[i] = Console.ReadLine();
                    }
                }
                else {
                    //if not naming nodes, assign them numbers
                    for (int i = 0; i < matrixSize; i++)
                    {
                        nodeNames[i] = "" + (i + 1);
                    }
                }

                do
                {
                    Console.Write("Enter input file name: ");
                    fileInName = Console.ReadLine();

                } while (!File.Exists(fileInName));

                string[] input = Matrix.ReadInputFromFile(fileInName);
                //blanks are i * size+1
                //4x4 = 0, 5, 10, 15

                //get input for relationship status of each node (except for selves i.e. node[2,2])
                int readOffset = 0;
                for (int i = 0; i < matrixSize; i++)
                {
                    for (int j = 0; j < matrixSize; j++)
                    {
                        if (i == j)
                        {
                            //node i=j is always blank so no confirmation in needed
                            readOffset--;
                            continue;
                        }
                        //can node i talk to node j?
                        resp = "n";
                        int index = (i * matrixSize) + j + readOffset;
                        Console.WriteLine(index);
                        if (resp.ToUpper().Equals("Y"))
                        {
                            nodeMatrix[i, j] = 1;
                        }
                    }
                }
                
                //print provided matrix to console for viewing
                Console.WriteLine(Matrix.ToString(nodeMatrix, nodeNames));

                //Run Warshall's Algorithm to find linked nodes
                Matrix.GetLinkedNodes<int>(ref nodeMatrix, 1, 0);

                //Request output file
                do
                {
                    Console.Write("Enter output file name: ");
                    fileOutName = Console.ReadLine();
                    resp = "y";
                    if (File.Exists(fileOutName))
                    {
                        Console.WriteLine("This file already exists.");
                        Console.Write("Do you wish to overwrite it? [y/n]: ");
                        resp = Console.ReadLine();
                    }
                } while (!resp.ToUpper().Equals("Y"));

                //Create output file
                FileStream fs = File.Create(fileOutName);
                fs.Close();

                //Print new matrix to console
                Matrix.WriteToFile(fileOutName, Matrix.ToString(nodeMatrix, nodeNames));

                //Write Matrix to file
                Console.WriteLine(Matrix.ToString(nodeMatrix, nodeNames));
                Console.WriteLine("Was written to the given File.\n");

                //Run program again?
                Console.Write("Do you want to run again? [y/n]: ");
                resp = Console.ReadLine();

            } while (resp.ToUpper().Equals("Y"));
        }
    }
}