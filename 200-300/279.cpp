#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

typedef __int64 int64;
struct timer
{
   double t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", get_time()); }
   double get_time() { return (clock()-t)/CLOCKS_PER_SEC; }
};

int gcd(int a, int b) 
{ 
   int t;
   while (b!=0)
      t=b, b=a%b, a=t;
   return a;
}
void f279()
{
   const int MAXP=1e8;
   const int MAXA=5e3;
   int nt=MAXP/3;
   int a=0;
   while (++a<MAXA)
   {
      int inc=1+!(a&1), i=1-inc;
      while (i+=inc, i<=a)
      {
         if (i>1 && gcd(a,i)!=1)
            continue;
         int b=i;
         while (b+=a)
         {
            int ab=a+b, c=2*b*ab;
            if (c>MAXP)
               break;
            int ba=b-a;
            if (ba&1)
               nt+=MAXP/c;
            if (ba%3)
            {
               int c1=2*ab*ab+a*b, c2=c+(c>>1), c3=(2*b+a)*ab;
               nt+=MAXP/c1, nt+=MAXP/c2, nt+=MAXP/c3;
            }
         }
         if (a+i==b)
            break;
      }
   }
   printf("%d\n",nt);
}
int main(int argc, char**argv)
{
   timer t;
   f279();
   return 0;
}

/*
416577688
runtime 0.682 secs
*/