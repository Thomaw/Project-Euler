#include <iostream>
#include <cmath>
#include <fstream>
#include <bitset>
#include <cstdio>
using namespace std;


const int MaxPrime = 60380000;
bitset<MaxPrime> PrimeSieve;
int Primes[10000000];
int Divisors[60000002];     //Divisors of numbers upto 60000001

inline int GetFactorCount(unsigned int num)
{
    register unsigned int i = 0;
    if (PrimeSieve[num] == 1) return 2;
    int Divisors = 1;
    i=0;
    while (true)
    {
        register int Prime = Primes[i++];
        int PrimeCount = 0;
        while (num % Prime == 0)
        {
            PrimeCount++;
            num /= Prime;
        }
        Divisors *= (PrimeCount+1);
        if (PrimeSieve[num] == 1)
        {
            Divisors *= 2;
            break;
        }
        if (num == 1) break;

    }
    return Divisors;

}
/**
    @brief
    This function is a major part of this code.
    What it does is, it takes a number n. And it first calculates its number of divisors.
    Now after having calculated them, it generates the divisors of all the numbers which are of the
    form p * n
    p being a prime number

*/
inline void InvestigateDivisors(int n)
{

    if (Divisors[n] != 0)
     return;
    Divisors[n] = GetFactorCount(n);
    for (int i =0;true; i++)
    {
        register int Prime = Primes[i];
        long long int num = n,s=n;
        s*=Prime;
        if(s<0 || s>60000001)
            return;
        if (Divisors[s]!=0) continue;
        while (true)
        {
            if (num % Prime == 0) num/=Prime;
            else break;
        }
        int FactorCountOfNWithoutThisPrime = Divisors[num];
        num = n;
        int lastnum = num;
        num*=Prime;

        while (num < 60000001)
        {
            Divisors[num] = Divisors[lastnum] + FactorCountOfNWithoutThisPrime;
            lastnum = num;
            num*=Prime;

        }
    }
}
inline unsigned int DivOfTriangleNum(int n)
{
    if (n%2==0)
        return Divisors[n/2] * Divisors[n+1];
    else
        return Divisors[(n+1)/2] * Divisors[n];
}
long long int Result(int n)
{
    //The divisor of a triangular number
    unsigned int *TriangularDiv = new unsigned int [n+2];

    //For a give j, Number of i such that i < j and dT(i) > dT(j)
    int *HowManyBelow = new int[n+2];

    //For a given n. Tr(n) in the form Sum2[n] . Sum[n] (concatenated... upto 18 digits)
    long long int *Sum = new long long int[n+2];
    long long int *Sum2 = new long long int[n+2];

    for (int i=1; i<=n; i++)
        {
            TriangularDiv[i] = DivOfTriangleNum(i);
            HowManyBelow[i] = 0;
            for (int j=i-1; j>0; j--)
            {
                if (TriangularDiv[j] > TriangularDiv[i])
                {
                    HowManyBelow[i]++;
                    //break;
                }
                else if (TriangularDiv[j] == TriangularDiv[i])
                {
                    HowManyBelow[i] += HowManyBelow[j];
                    break;
                }
                else
                {
                    if (HowManyBelow[j] == 0) break;
                }
            }
        }

    long long int r = 0, m=0;
    for (int k=3; k<=n; k++)
    {
        int items = HowManyBelow[k];
        {
        for (int j=k-1; j>0;j--)
        {
            if (items == 0) break;
            if (TriangularDiv[j]< TriangularDiv[k]) continue;
            if (TriangularDiv[k] == TriangularDiv[j])
            {
                r+=Sum[j];
                if (r > 999999999)
                    {
                        m+= r/1000000000;
                        r %= 1000000000;
                    }
                m += Sum2[j];
                if (m > 999999999)
                    {
                        m %= 1000000000;

                    }
                Sum[k] += Sum[j];
                Sum2[k] += Sum2[j];
                if (Sum[k] > 999999999)
                {
                    Sum2[k]+= (Sum[k]/1000000000);
                    Sum[k] %= 1000000000;

                    if (Sum2[k] > 999999999) Sum2[k] %= 1000000000;
                }
                break;
            }
                items--;
                r+=HowManyBelow[j];
                Sum[k] += HowManyBelow[j];
                if (Sum[k] > 999999999)
                {
                    Sum2[k]+=(Sum[k]/1000000000);
                    Sum[k] %= 1000000000;
                    if (Sum2[k] > 999999999) Sum2[k] %= 1000000000;
                }
                if (r > 999999999)
                    {
                        m+= r/1000000000;
                        r %= 1000000000;
                    }
                else if (m > 999999999)
                    {
                        m %= 1000000000;

                    }
        }

        }
    }
    cout << ' ' << m << ' ' << r<<endl;

    delete[] TriangularDiv;
    delete[] HowManyBelow;
    delete[] Sum;
    delete[] Sum2;
    return r;
}
int main()
{
    FILE *f = fopen("Pro.txt","r");
    fread(&PrimeSieve,sizeof(PrimeSieve),1,f);  //Read primes from the file Pro.txt
    fclose(f);

    register int PrimeIndex=0;
    Primes[PrimeIndex++] = 2;
    for (int i=3; i<MaxPrime; i+=2)
        if (PrimeSieve[i])Primes[PrimeIndex++] = i;

    Divisors[1] = 1;
    for (int i=2;i<=60000001; i++)
        {
            InvestigateDivisors(i);
        }
    Result(60000000);

}