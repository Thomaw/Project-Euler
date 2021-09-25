#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _MSC_VER
  #define bool int
  #define false 0
  #define true 1
#else  // Pelle's C
  #include <stdbool.h>  // C99
#endif

bool IsPrime(unsigned long n);

#define MAX 999999

int main(void)
{
    unsigned long x;
    unsigned long y;
    unsigned long *pLoc;
    unsigned long *p;
    unsigned long c = 0;
    unsigned long s = 0;
    unsigned long terms = 0;
    unsigned long sum = 0;
    unsigned long array_size;

    printf("Generating an array of prime numbers... ");

    // find the array size needed
    for(x = 2 ; x <= MAX ; x++)
    {
        if(IsPrime(x))
        {
            c++;
        }
    }

    array_size = c;
    c = 0;

    // Create an array of primes <= MAX
    pLoc = malloc(array_size * sizeof(unsigned long));
    p = pLoc;

    for(x = 2 ; c < array_size ; x++)
    {
        if(IsPrime(x))
        {
            *p = x;
            p++;
            c++;
        }
    }

    // Solve the problem
    printf("\nSolving the problem... ");

    for(x = 0 ; x < array_size ; x++)
    {
        c = 0;
        s = 0;
        p = pLoc;

        for(y = x ; ; y++)
        {
            s += *(p+y);

            if(s > MAX)
            {
                s -= *(p+y);
                break;
            }

            c++;

            if(IsPrime(s))
            {
                if(c > terms)
                {
                    terms = c;
                    sum = s;
                }
            }
        }
    }

    free(pLoc);

    printf("\n\nAnswer = %lu, number of terms = %lu\n\n", sum, terms);

    return 0;
}

bool IsPrime(unsigned long n)
{
    int i;
    int k;

    if(n <= 3)
    {
        if(n == 1)
        {
            return false;
        }
        else    // it's 2 or 3
        {
            return true;
        }
    }

    if((n % 2) == 0)
    {
        return false;
    }

    k = (int) sqrt(n) + 1;

    for (i = 3 ; i <= k ; i += 2)
    {
         if(n % i == 0)
         {
             return false;
         }
    }

    return true;
}
