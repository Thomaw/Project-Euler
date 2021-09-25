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
   timer() { t=clock(); }
   ~timer() { printf("runtime %.3f secs\n", get_time()); }
   double get_time() { return (clock()-t)/CLOCKS_PER_SEC; }
};
int phi(int n)
{
   int pay=n, payda=1;
   if (!(n&1))
   {
      pay>>=1;
      while (n/=2, !(n&1))
         ;
   }
   if (!(n%3))
   {
      pay<<=1;
      payda*=3;
      while (n/=3, !(n%3))
         ;
   }
   int p=1, a=2, hi=sqrt(n)+1;
   while (a=6-a, p+=a, p<=hi)
   {
      if (!(n%p))
      {
         pay*=p-1;
         payda*=p;
         while (n/=p, !(n%p))
            ;
         hi=sqrt(n)+1;
      }
   }
   if (n>1)
   {
      pay*=n-1;
      payda*=n;
   }
   return pay/payda;
}
double f(int m, int n, int d)
{
   int mn=m*n, nd=n/d, mnd=m*nd;
   double pay=phi(d);
   int i=nd;
   while (++i<=mnd)
      pay*=i;
   double payda=mn;
   i=0;
   while (++i<m)
   {
      int j=1;
      while (++j<=nd)
         payda*=j;
   }
   return pay/payda;
}
void f281()
{
   const int64 M=1e15;
   int64 nt=0;
   int m=1;
   while (++m)
   {
      int n=0;
      while (++n)
      {
         int i=0;
         double d=0;
         while (++i<=n)
         {
            if (!(n%i))
               d+=f(m,n,i);
         }
         if (d>M)
            break;
         nt+=(int64)(d+0.5);
         printf("f(%d,%d)=%I64d\n", m,n,(int64)(d+0.5));
      }
      if (n==1)
         break;
   }
   printf("nt=%I64d\n", nt);
}

int main(int argc, char**argv)
{
   timer t;
   f281();
   return 0;
}

/*
f(2,1)=1
f(2,2)=2
f(2,3)=4
f(2,4)=10
f(2,5)=26
f(2,6)=80
f(2,7)=246
f(2,8)=810
f(2,9)=2704
f(2,10)=9252
f(2,11)=32066
f(2,12)=112720
f(2,13)=400024
f(2,14)=1432860
f(2,15)=5170604
f(2,16)=18784170
f(2,17)=68635478
f(2,18)=252088496
f(2,19)=930138522
f(2,20)=3446167860
f(2,21)=12815663844
f(2,22)=47820447028
f(2,23)=178987624514
f(2,24)=671825133648
f(2,25)=2528212128776
f(2,26)=9536895064400
f(2,27)=36054433810102
f(2,28)=136583761444364
f(2,29)=518401146543812
f(3,1)=2
f(3,2)=16
f(3,3)=188
f(3,4)=2896
f(3,5)=50452
f(3,6)=953056
f(3,7)=19003476
f(3,8)=394397776
f(3,9)=8439756848
f(3,10)=185033251616
f(3,11)=4137181680700
f(3,12)=94020327215200
f(4,1)=6
f(4,2)=318
f(4,3)=30804
f(4,4)=3941598
f(4,5)=586637256
f(4,6)=96197661156
f(4,7)=16875655269948
f(5,1)=24
f(5,2)=11352
f(5,3)=11211216
f(5,4)=15277017432
f(5,5)=24934429725024
f(6,1)=120
f(6,2)=623760
f(6,3)=7623616080
f(6,4)=135277939358160
f(7,1)=720
f(7,2)=48648960
f(7,3)=8690922240480
f(8,1)=5040
f(8,2)=5108105520
f(9,1)=40320
f(9,2)=694702028160
f(10,1)=362880
f(10,2)=118794043549440
f(11,1)=3628800
f(12,1)=39916800
f(13,1)=479001600
f(14,1)=6227020800
f(15,1)=87178291200
f(16,1)=1307674368000
f(17,1)=20922789888000
f(18,1)=355687428096000
nt=1485776387445623
runtime 0.028 secs
*/