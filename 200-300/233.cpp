#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <queue>
#include <algorithm>

typedef __int64 int64;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};
struct SPrimeSieve : std::vector<int>
{
   enum{HI=10000,M=HI/4};
 
   SPrimeSieve()
   {
      reserve(M);
      bool* f = new bool [HI+1];
      // prime sieve in f. saving individual primes in vector
      f[0]=f[1]=0;
      int i=1;
      while (++i<=HI)
         f[i]=1;

      i=1;
      while (++i<=HI)
      {
         if(f[i]==1)
         {
            push_back(i);
            for(uint j=i+i;j<=HI;j+=i) f[j]=0;
         }
      }
      printf(" found %d primes until %d\n", size(), at(size()-1));
      delete [] f;
   }
   int isPrime(int number)
   {
      int ix = 0;
      int sqr = sqrt(number)+1;
      int* ap=begin();
      int divisor = ap[ix++];
      int n = number;
      while (divisor < sqr)
      {
         if (0 == (n % divisor))
         {
            return 0;
         }
         divisor = ap[ix++];
      }
      return 1;
   }
};
struct node
{
   int a,b,c;
   node(int a, int b, int c){this->a=a, this->b=b, this->c=c;}
   node(const node& r){this->a=r.a, this->b=r.b, this->c=r.c;}
};
void fx()
{
   SPrimeSieve ps;
   const int MAXK=4733728; //=ceil( 10^11/(5^3*13^2) )
   std::vector<int> v;
   std::queue<node> q;
   q.push( node(3,4,5) );
   while (!q.empty())
   {
      node nodex=q.front();
      q.pop();
      if (nodex.c>MAXK)
         continue;
      if (ps.isPrime(nodex.c))
      {
         v.push_back(nodex.c);
      }
      int a=-(nodex.a<<1)+nodex.b+(nodex.c<<1); // (a b c) (-2 1 2)
      int b=-nodex.a+(nodex.b<<1)+(nodex.c<<1); // (a b c) (-1 2 2)
      int c=-(nodex.a<<1)+(nodex.b<<1)+nodex.c*3; // (a b c) (-2 2 3)
      q.push( node(a,b,c) );

      a=(nodex.a<<1)+nodex.b+(nodex.c<<1); // (a b c) (2 1 2)
      b=nodex.a+(nodex.b<<1)+(nodex.c<<1); // (a b c) (1 2 2)
      c=(nodex.a<<1)+(nodex.b<<1)+nodex.c*3; // (a b c) (2 2 3)
      q.push( node(a,b,c) );

      a=nodex.a-(nodex.b<<1)+(nodex.c<<1); // (a b c) (1 -2 2)
      b=(nodex.a<<1)-nodex.b+(nodex.c<<1); // (a b c) (2 -1 2)
      c=(nodex.a<<1)-(nodex.b<<1)+nodex.c*3; // (a b c) (2 -2 3)
      q.push( node(a,b,c) );
   }
   int size=v.size();
   printf("size=%d\n", size);
   int* p=v.begin();
   std::sort(p, p+size);
   const int64 MAXN=100000000000;
   int64 sum=0;
   bool* pf = new bool[MAXK+1];
   memset(pf,false,sizeof(bool)*(MAXK+1));
   int i=-1;
   while (++i<size)
   {
      int j=p[i];
      int k=j;
      do
         pf[k]=true;
      while ((k+=j)<=MAXK);
   }
   i=-1;
   // a^7*b^3
   while (++i, 1)
   {
      int64 a=p[i];
      int64 a3=a*a*a;
      int64 a7=a3*a3*a;
      int foundj=0;
      int j=-1;
      while (++j<size)
      {
         if (j==i) continue;
         int64 b=p[j];
         int64 bb=b*b;
         int64 bbb=bb*b;
         int64 n=a7*bbb;
         if (n>0 && n<=MAXN)
         {
            int64 nx=MAXN/n;
            int64 ix=0;
            while (++ix<=nx)
            {
               if (pf[ix]==false)
                  sum+=n*ix;
            }
            ++foundj;
         }
      }
      if (!foundj)
         break;
   }

   // a^10*b^2
   i=-1;
   while (++i, 1)
   {
      int64 a=p[i];
      int64 a3=a*a*a;
      int64 a7=a3*a3*a;
      int64 a10=a7*a3;
      int foundj=0;
      int j=-1;
      while (++j<size)
      {
         if (j==i) continue;
         int64 b=p[j];
         int64 bb=b*b;
         int64 n=a10*bb;
         if (n>0 && n<=MAXN)
         {
            int64 nx=MAXN/n;
            int64 ix=0;
            while (++ix<=nx)
            {
               if (pf[ix]==false)
                  sum+=n*ix;
            }
            ++foundj;
         }
      }
      if (!foundj)
         break;
   }

   // a^3*b^2*c
   i=-1;
   while (++i, 1)
   {
      int64 a=p[i];
      int64 a3=a*a*a;
      int foundj=0;
      int j=-1;
      while (++j<size)
      {
         if (j==i) continue;
         int64 b=p[j];
         int64 bb=b*b;
         int foundk=0;
         int k=-1;
         while (++k<size)
         {
            if (k==i || k==j) continue;
            int64 c=p[k];
            int64 n=a3*bb*c;
            if (n>MAXN)
               break;
            if (n<0)
               break;
            ++foundk;
            int64 nx=MAXN/n;
            int64 ix=0;
            while (++ix<=nx)
            {
               if (pf[ix]==false)
                  sum+=n*ix;
            }
         }
         if (!foundk)
            break;
         ++foundj;
      }
      if (!foundj)
         break;
   }
   printf("sum=%I64d\n", sum);
   delete [] pf;
}

int main(int ac, char** av)
{
   timer t;
   fx();
   return 0;
}
/*
Outputs:
 found 1229 primes until 9973
size=165549
sum=271204031455541309
runtime 0.908 secs
*/