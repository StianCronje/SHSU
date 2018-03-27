using System;

namespace MultiStack
{
    class SuperStack<T>
    {
        int m = 0, n = 0, L0 = 0, lowBound = 0, upBound = 0, minSpace = 1;
        T[] stack;
        int[] sBase;
        int[] sTop;
        int[] oneArray; // combines growth, oltTop, and newBase Required for B option

        // Creates an array in system stack to be used for Multi-Stack
        public static SuperStack<T> CreateStack(int lowBound, int upBound, int l0, int size, int amtStacks)
        {
            // Generic SuperStack
            SuperStack<T> ss = new SuperStack<T>();

            // initialize all variables
            ss.stack = new T[upBound - lowBound];
            ss.sBase = new int[amtStacks + 1];
            ss.sTop = new int[amtStacks];
            ss.oneArray = new int[amtStacks + 1];
            ss.minSpace = Floor(size * 0.05f);
            ss.lowBound = lowBound;
            ss.upBound = upBound;
            ss.m = size;
            ss.L0 = l0;
            ss.n = amtStacks;

            // assign initial base stacks
            for (int i = 0; i < amtStacks; i++)
            {
                ss.sBase[i] = ss.sTop[i] = ss.oneArray[i + 1] = (size - l0) / amtStacks * i + l0;
            }
            // last (extra) base used to check overflow on last stack
            ss.sBase[amtStacks] = size;

            // return SuperStack to be used by main program
            return ss;
        }
        
        public bool Push(int stackNum, T obj)
        {
            sTop[stackNum]++;
            if (sTop[stackNum] > sBase[stackNum + 1])
            {
                Console.WriteLine("Stack overflow: Stack " + (stackNum+1) + " while pushing " + obj.ToString());
                Console.WriteLine("Reallocating stack space...");

                // If reallocate is a success
                // then try to push the object into the stach again
                // else stop processing
                Console.Write("\nBefore Reallocate: ");
                PrintStack();
                bool success = Reallocate(0.15f);
                Console.Write("\nAfter Reallocate: ");
                PrintStack();
                sTop[stackNum]--;

                if (success)
                    Push(stackNum, obj);
                else
                    return false;
            }
            else
            {
                stack[sTop[stackNum]] = obj;
                Console.WriteLine("Pushing " + obj.ToString() + " to stack" + (stackNum + 1) + "[" + sTop[stackNum] + "]");
                return true;
            }
            return true;
        }

        public T Pop(int stackNum)
        {
            T obj = default(T);
            if (sTop[stackNum] == sBase[stackNum])
            {
                Console.WriteLine("Stack underflow: Stack " + (stackNum + 1)+ " is empty.");
                return default(T);
            }
            else
            {
                obj = stack[sTop[stackNum]];
                Console.WriteLine("Popping stack" + (stackNum + 1) + "[" + sTop[stackNum] + "] = \"" + obj + "\"");
                stack[sTop[stackNum]] = default(T); // clear position to make printing cleaner
                sTop[stackNum]--;
            }

            return obj;
        }

        bool Reallocate(float equalAllocate)
        {
            int availSpace = m - L0;
            int totalInc = 0;
            int j = n - 1;

            for (int i = 0; i < n; i++)
            {
                availSpace -= sTop[i] - sBase[i];
                totalInc += sTop[i] - oneArray[i + 1];
            }

            if (availSpace < minSpace)
            {
                Console.WriteLine("Insufficient memory for re-packing");
                return false;
            }

            float growthAllocate = 1 - equalAllocate;
            float alpha = equalAllocate * availSpace / n;
            float beta = growthAllocate * availSpace / totalInc;

            // oneArray being used as newBase
            oneArray[0] = sBase[0];
            float sigma = 0;
            for (int i = 1; i <= n; i++)
            {
                // oneArray being used to calculate growth and the assigned newBase
                float tau = sigma + alpha + Max(sTop[i - 1] - oneArray[i], 0) * beta;
                oneArray[i] = oneArray[i - 1] + (sTop[i - 1] - sBase[i - 1]) + Floor(tau) - Floor(sigma);
                sigma = tau;
            }

            MoveStack();

            for (int i = 0; i < n; i++)
            {
                // oneArray being used as oldTop after stacks have been moved
                oneArray[i + 1] = sTop[i];
            }
            return true;
        }

        void MoveStack()
        {
            // try move stacks down
            int delta = 0;
            for (int i = 1; i < n; i++)
            {
                if (oneArray[i] < sBase[i])
                {
                    delta = sBase[i] - oneArray[i];
                    for (int l = sBase[i]+1; l <= sTop[i]; l++)
                    {
                        stack[l - delta] = stack[l];
                    }
                    sBase[i] = oneArray[i];
                    sTop[i] -= delta;
                }
            }

            // try move stacks up
            delta = 0;
            for (int i = n - 1; i >= 1; i--)
            {
                if (oneArray[i] > sBase[i])
                {
                    delta = oneArray[i] - sBase[i];
                    for (int l = sTop[i]; l >= sBase[i]; l--)
                    {
                        stack[l + delta] = stack[l];
                    }
                    sBase[i] = oneArray[i];
                    sTop[i] += delta;
                }
            }
        }

        public void PrintStack()
        {
            Console.WriteLine();
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine("Stack " + i + " -- Base: " + sBase[i] + ", Top: " + sTop[i] + ", OldTop: " + oneArray[i + 1]);
            }

            int stackNum = 0;
            for (int i = L0; i <= m; i++)
            {
                Console.WriteLine("Location " + i + " : Stack " + (stackNum + 1) + " : " + stack[i]);
                if (i == sBase[stackNum + 1])
                {
                    stackNum++;
                }
            }
            Console.WriteLine();
        }


        static int Floor(float val)
        {
            int temp = (int)val;
            if (temp <= val)
                return temp;
            else
                return temp - 1;
        }

        static int Max(int a, int b)
        {
            if (a > b)
                return a;
            else
                return b;
        }
    }
}
