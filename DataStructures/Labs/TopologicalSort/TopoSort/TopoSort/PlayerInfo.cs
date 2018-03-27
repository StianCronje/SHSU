using System;
using System.Collections.Generic;
using System.IO;

namespace TopoSort
{
    public class TopologicalSort
    {
        public static bool TrySort(Parent[,] relations, Parent[] table, out Parent[] result)
        {
            int na = table.Length;
            bool isLoop = false;

            for (int i = 0; i < relations.GetLength(0); i++)
            {
                table[IndexOf(table, relations[i, 0])].top.Insert(0, relations[i, 1]);
                table[IndexOf(table, relations[i, 1])].cnt++;
            }

            //sort in alpha order to view easily
            List<Parent> tempSortList = new List<Parent>();
            tempSortList.AddRange(table);
            tempSortList.Sort((x, y) => x.Print().CompareTo(y.Print()));
            table = tempSortList.ToArray();

            List<Parent> sortedQueue = new List<Parent>();

            while (sortedQueue.Count < na)
            {
                if (isLoop = IsLoop(table)) break;

                for (int i = 0; i < table.Length; i++)
                {
                    if (table[i].cnt == 0)
                    {
                        int tempI = 0;
                        sortedQueue.Add(table[i]); //add to sorted queue
                        table[i].cnt--; //remove from search

                        while (table[i].top.Count > 0)
                        {
                            int top = IndexOf(table, table[i].top[0]);
                            table[top].cnt--; //dec at index of pointer
                            table[i].top.RemoveAt(0); //pop from list
                            tempI = top;
                        }
                        i = tempI;

                    }
                }
            }

            // return the loop details
            if (isLoop)
                result = table;
            else //return list results
                result = sortedQueue.ToArray();

            return !isLoop;
        }

        public static string[,] GetObjectsFromFile(string fileName)
        {
            string[] lines = File.ReadAllLines(fileName);

            string[,] relations = new string[lines.Length, 2];
            for (int i = 0; i < lines.Length; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    //parse at relation indicator
                    relations[i, j] = lines[i].Split(new string[] { " < ", "<" }, StringSplitOptions.None)[j];
                }
            }

            return relations;
        }

        public static Parent[] GetUniqueNodes(Parent[,] relations)
        {
            List<Parent> nodeList = new List<Parent>();

            for (int i = 0; i < relations.GetLength(0); i++)
            {
                for (int j = 0; j < relations.GetLength(1); j++)
                {
                    if (!Contains(nodeList.ToArray(), relations[i, j]))
                    {
                        nodeList.Add(relations[i, j]);
                    }
                }
            }

            return nodeList.ToArray();
        }

        public static Parent[,] GetNodeRelations(string fileName, ref List<Parent> nodeList)
        {
            string[] lines = File.ReadAllLines(fileName);

            Parent[,] relations = new Parent[lines.Length, 2];
            for (int i = 0; i < relations.GetLength(0); i++)
            {
                for (int j = 0; j < relations.GetLength(1); j++)
                {
                    relations[i, j] = new Parent();
                }
            }

            for (int i = 0; i < relations.GetLength(0); i++)
            {
                for (int j = 0; j < relations.GetLength(1); j++)
                {
                    if (!Contains(nodeList.ToArray(), relations[i, j]))
                    {
                        nodeList.Add(relations[i, j]);
                    }
                }
            }

            return relations;
        }

        static bool Contains(Parent[] lst, Parent nd)
        {
            for (int i = 0; i < lst.Length; i++)
            {
                if (lst[i].Equals(nd))
                {
                    return true;
                }
            }

            return false;
        }

        static int IndexOf(Parent[] lst, Parent nd)
        {
            for (int i = 0; i < lst.Length; i++)
            {
                if (lst[i].Equals(nd))
                {
                    return i;
                }
            }

            return -1;
        }

        static bool IsLoop(Parent[] list)
        {
            for (int i = 0; i < list.Length; i++)
            {
                if (list[i].cnt == 0)
                {
                    return false;
                }
            }

            return true;
        }
    }


    public class Parent
    {
        public int cnt = 0;
        public List<Parent> top = new List<Parent>();

        public virtual string Print()
        {
            return "_parent";
        }

        public virtual string Identify()
        {
            return "Parent()";
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            if (!(obj is Parent))
                return false;

            Parent n = obj as Parent;
            return cnt.Equals(n.cnt) && top.Equals(n.top);
        }

        public override int GetHashCode()
        {
            return cnt.GetHashCode() ^ top.GetHashCode();
        }
    }
}
