#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};
enum { Z='0' };
int sum=0;
char a[128]={0};
void fx()
{
   int factor=0;
   while (++factor<10)
   {
      int d=0;
      while (++d<10)
      {
         int digits=0;
         int next=d*factor;
         int elde=next/10;
         a[100-digits]=Z+d;
         while (++digits<100)
         {
            next%=10;
            int last=next;
            a[100-digits]=Z+next;
            next=next*factor+elde;
            elde=next/10;
            if (last!=0 && d==next && elde==0)
               sum+=atoi(a+100-(digits<5?digits:5));
         }
      }
   }
}
int main(int argc, char**argv)
{
   timer t;
   fx();
   printf("sum=%d\n",sum%100000);
   return 0;
}
/*
sum=59206
runtime 0.001 secs
*/