using System;

namespace P710
{
    class Program
    {       
        static void Main()
        {     
            long l1 = 0, l2 = 1, l3 = 0, l4 = 2, l5 = 1, ln;
            long m = 1000000;
            long k = 6;

            while (true)
            {
                ln = 3 * l4 + l3 - 2 * l2 - 2 * l1;
                ln %= m;

                if (ln == 0) break;              

                l1 = l2;
                l2 = l3;
                l3 = l4;
                l4 = l5;
                l5 = ln;
                k++;
            }

            Console.WriteLine(k);
        }
    }
}
