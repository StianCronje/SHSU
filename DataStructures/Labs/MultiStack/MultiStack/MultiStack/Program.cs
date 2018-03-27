using System;
using System.IO;

namespace MultiStack
{
    class Program
    {
        static void Main(string[] args)
        {
            // Get first stack size info
            int m = 0, n = 0, L0 = 0, LB = 0, UB = 0;
            Console.Write("Enter a Lower Bound: ");
            LB = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter a Upper Bound: ");
            UB = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the stack start index: ");
            L0 = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the total amount of space for the stacks: ");
            m = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the number of stacks: ");
            n = Convert.ToInt32(Console.ReadLine());

            // Create string type Super Stack
            SuperStack<string> cbDataStack = SuperStack<string>.CreateStack(LB, UB, L0, m, n);

            // Get C/B option input file information
            string fileName = "";
            do
            {
                Console.Write("Enter name of input file for C/B data: ");
                fileName = Console.ReadLine();
                if (!File.Exists(fileName))
                {
                    Console.WriteLine("File not found");
                }
            }
            while (!File.Exists(fileName));
            string[] input = File.ReadAllLines(fileName);

            // Process C/B data and push/pop into stack
            int s = 0;
            string o = "";
            for (int i = 0; i < input.Length; i++)
            {
                if (input[i].Substring(0, 1).Equals("I"))
                {
                    s = Convert.ToInt32(input[i].Substring(1, 2)) - 1;
                    o = input[i].Substring(3);

                    // If push cannot be completed, even after any reallocation
                    // then stop processing, stack is full
                    if (!cbDataStack.Push(s, o))
                        break;
                }
                else if (input[i].Substring(0, 1).Equals("D"))
                {
                    s = Convert.ToInt32(input[i].Substring(1)) - 1;
                    cbDataStack.Pop(s);
                }
            }

            Console.Write("Final Stack Result for C/B Data: ");
            cbDataStack.PrintStack();

            // Get second stack size info
            Console.Write("Enter a Lower Bound: ");
            LB = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter a Upper Bound: ");
            UB = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the stack start index: ");
            L0 = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the total amount of space for the stacks: ");
            m = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the number of stacks: ");
            n = Convert.ToInt32(Console.ReadLine());
            
            // Create custom type Super Stack
            SuperStack <Date> aDataStack = SuperStack<Date>.CreateStack(LB, UB, L0, m, n);

            // Get A option input file information
            fileName = "";
            input = new string[0];
            do
            {
                Console.Write("Enter name of input file for A data: ");
                fileName = Console.ReadLine();
                if (!File.Exists(fileName))
                {
                    Console.WriteLine("File not found");
                }
            }
            while (!File.Exists(fileName));
            input = File.ReadAllLines(fileName);

            // Parse input to custom class/struct
            // Push/Pop into stack
            s = 0;
            string[] dateVars;
            for (int i = 0; i < input.Length; i++)
            {
                Date date = new Date();
                if (input[i].Substring(0, 1).Equals("I"))
                {
                    s = Convert.ToInt32(input[i].Substring(1, 2)) - 1;
                    dateVars = input[i].Split(new string[] { ",", " " }, StringSplitOptions.RemoveEmptyEntries);
                    for (int j = 1; j < dateVars.Length; j++)
                    {
                        int val = 0;
                        bool isNum = int.TryParse(dateVars[j], out val);
                        if (isNum)
                            if (val <= 31 && val >= 1)
                                date.day = val;
                            else
                                date.year = val;
                        else
                            date.month = dateVars[j];
                    }
                    // If push cannot be completed, even after any reallocation
                    // then stop processing, stack is full
                    if (!aDataStack.Push(s, date))
                        break;
                }
                else if (input[i].Substring(0, 1).Equals("D"))
                {
                    s = Convert.ToInt32(input[i].Substring(1)) - 1;
                    aDataStack.Pop(s);
                }
            }

            Console.Write("Final Stack Result for A Data: ");
            cbDataStack.PrintStack();

            Console.Write("\nPress any key to exit...");
            Console.Read();
        }
    }

    public class Date
    {
        public string month = "";
        public int day = 0;
        public int year = 0;

        public override string ToString()
        {
            return month + " " + day + ", " + year;
        }
    }
}
