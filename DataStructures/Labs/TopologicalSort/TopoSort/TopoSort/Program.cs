using System;
using System.Collections.Generic;
using System.IO;

namespace TopoSort
{
    public class Program
    {
        static void Main(string[] args)
        {
            string resp = "n";
            do
            {
                bool isLoop = false;
                Console.WriteLine("Enter the relation file name: ");
                string fileInName = Console.ReadLine();
                Console.WriteLine("Enter the output file name: ");
                string fileOutName = Console.ReadLine();

                #region Programmer defined parsing rules for custom objects
                // Parse file for objects
                string[,] objects = TopologicalSort.GetObjectsFromFile(fileInName);

                // create base relation list
                Parent[,] relations = new Parent[objects.GetLength(0), objects.GetLength(1)];

                //assign relations to custom classes deriving from "Parent"
                for (int i = 0; i < objects.GetLength(0); i++)
                {
                    for (int j = 0; j < objects.GetLength(1); j++)
                    {
                        // custom class
                        if (objects[0, 0].ToCharArray()[0].Equals('('))
                        {
                            // read and assign to required class
                            string[] fields = objects[i, j].Split(new string[] { "(", ", ", ",", ")" }, StringSplitOptions.RemoveEmptyEntries);

                            Parent n = new Parent();
                            float f_value = 0.0f;
                            int i_value = 0;
                            if (fields[1].Contains(".") && float.TryParse(fields[1], out f_value))
                            {
                                //create new food
                                n = new Food(fields[0], f_value);
                            }
                            else if (Int32.TryParse(fields[1], out i_value))
                            {
                                //create new car
                                n = new Car(fields[0], i_value);
                            }
                            else
                            {
                                //create new person
                                n = new Person(fields[0], fields[1]);
                            }

                            relations[i, j] = n;
                        }
                        else //if basic data type
                        {
                            // check if int or name
                            Parent n;
                            int tempInt;
                            string tempName;
                            if (Int32.TryParse(objects[i, j], out tempInt))
                            {
                                n = new IntegerType(tempInt);
                            }
                            else
                            {
                                tempName = objects[i, j];
                                n = new NameType(tempName);
                            }

                            relations[i, j] = n;
                        }
                    }
                }
                #endregion

                // get list of unique nodes in relation list
                Parent[] table = TopologicalSort.GetUniqueNodes(relations);
                int na = table.Length;

                // try to sort the nodes
                Parent[] topoSortedList;
                isLoop = !TopologicalSort.TrySort(relations, table, out topoSortedList);

                string output = "";
                output += "Processed " + fileInName + "\n";
                if (isLoop)
                {
                    // output the resulting table after failed sort
                    output += "Sort cannot be completed!\n";
                    output += "Loop detected\n";
                    output += "dat: ";
                    for (int i = 0; i < topoSortedList.Length; i++)
                    {
                        output += topoSortedList[i].Print() + "\t";
                    }
                    output += "\n";
                    output += "cnt: ";
                    for (int i = 0; i < topoSortedList.Length; i++)
                    {
                        output += topoSortedList[i].cnt + "\t";
                    }
                    output += "\n";
                    output += "top: ";
                    for (int i = 0; i < topoSortedList.Length; i++)
                    {
                        if (topoSortedList[i].top.Count > 0)
                            output += topoSortedList[i].top[0].Print() + "\t";
                        else
                            output += "null\t";
                    }
                    output += "\n";
                }
                else
                {
                    // output sequence of nodes in sorted order
                    output += "Sort completed successfully!\n";
                    output += "Results:\n";

                    for (int i = 0; i < topoSortedList.Length - 1; i++)
                    {
                        output += topoSortedList[i].Identify() + " -> ";
                    }
                    output += topoSortedList[topoSortedList.Length - 1].Identify();
                    output += "\n\n";
                }

                Console.WriteLine(output);

                File.WriteAllText(fileOutName, output);

                Console.Write("Press any key to continue...");
                Console.ReadKey();

                //Run program again?
                Console.Write("Do you want to run again? [y/n]: ");
                resp = Console.ReadLine();

            } while (resp.ToUpper().Equals("Y"));
        }
    }


    #region Programmer Defined Token Types
    public class IntegerType : Parent
    {
        public int integerValue = 0;

        public IntegerType(int _intvalue)
        {
            integerValue = _intvalue;
        }

        public override string Print()
        {
            return integerValue.ToString();
        }

        public override string Identify()
        {
            return "IntegerType(" + integerValue + ")";
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            if (!(obj is IntegerType))
                return false;

            IntegerType n = obj as IntegerType;
            return integerValue.Equals(n.integerValue);
        }

        public override int GetHashCode()
        {
            return integerValue.GetHashCode();
        }
    }

    public class NameType : Parent
    {
        public string name = "null";

        public NameType(string _name)
        {
            name = _name;
        }

        public override string Print()
        {
            return name;
        }

        public override string Identify()
        {
            return "NameType(" + name + ")";
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            if (!(obj is NameType))
                return false;

            NameType n = obj as NameType;
            return name.Equals(n.name);
        }

        public override int GetHashCode()
        {
            return name.GetHashCode();
        }
    }

    public class Person : Parent
    {
        public string name = "";
        public string role = "";

        public Person(string _name, string _role)
        {
            name = _name.ToUpper();
            role = _role.ToUpper();
        }

        public override string Print()
        {
            return name + "-" + role;
        }

        public override string Identify()
        {
            return "Person(" + name + ", " + role + ")";
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            if (!(obj is Person))
                return false;

            Person n = obj as Person;
            return name.Equals(n.name) && role.Equals(n.role);
        }

        public override int GetHashCode()
        {
            return name.GetHashCode() ^ role.GetHashCode();
        }
    }

    public class Car : Parent
    {
        public string item = "";
        public int value = 0;

        public Car(string _item, int _val)
        {
            item = _item.ToUpper();
            value = _val;
        }

        public override string Print()
        {
            return item + "-" + value;
        }

        public override string Identify()
        {
            return "Car(" + item + ", " + value + ")";
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            if (!(obj is Car))
                return false;

            Car n = obj as Car;
            return item.Equals(n.item) && value.Equals(n.value);
        }

        public override int GetHashCode()
        {
            return item.GetHashCode() ^ value.GetHashCode();
        }
    }

    public class Food : Parent
    {
        public string item = "";
        public float value = 0.0f;

        public Food(string _item, float _val)
        {
            item = _item.ToUpper();
            value = _val;
        }

        public override string Print()
        {
            return item + "-" + value;
        }

        public override string Identify()
        {
            return "Food(" + item + ", " + value + ")";
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            if (!(obj is Food))
                return false;

            Food n = obj as Food;
            return item.Equals(n.item) && value.Equals(n.value);
        }

        public override int GetHashCode()
        {
            return item.GetHashCode() ^ value.GetHashCode();
        }
    }
    #endregion
}