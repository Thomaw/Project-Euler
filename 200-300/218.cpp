#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <set>
typedef __int64 myint;
myint gcd(myint a,myint b)
{
  myint c;
 
  while(b>0)  {
     if(a>=b)  {
        a-=b;
        if(a>=b)  {
           a-=b;
           if(a>=b)  {
              a-=b;
              if(a>=b)  {
                 a-=b;
                 if(a>=b)  {
                    a-=b;
                    if(a>=b)  {
                       a-=b;
                       if(a>=b)  {
                          a-=b;
                          if(a>=b)  {
                             a-=b;
                             if(a>=b)  a%=b;
              }}}}}}}}
     c=a,a=b,b=c;
  }
  return a;
}
myint sum = 0;
inline int fx(myint u, myint v)
{
   if (gcd(u,v)==1)
   {
      myint uu = u*u;
      myint vv = v*v;
      myint h = uu + vv;
      if (h > 10000000000000000)
         return 0;
      myint s = sqrt(h);
      if (s*s == h)
      {
         myint d=84;
         while (!(d&1) && !(u&1))
            d>>=1, u>>=1;
         while (!(d&1) && !(v&1))
            d>>=1, v>>=1;
         if ((u%3)==0 || (v%3)==0)
            d/=3;
         if ((u%7)==0 || (v%7)==0)
            d/=7;
         if (d > 1)
         {
            uu-=vv;
            if (uu%d)
               ++sum;
         }
      }
   }
   return 1;
}
int main(int ac, char** av)
{
   myint u = 0;
   time_t t1 = time(0);
   while (++u)
   {
      myint uu = u*u;
      myint v = u-1;
      while (v+=2)
      {
         if (!fx(v*v-uu,2*u*v))
            break;
       }
      if (u+1 == v)
         break;
   }
   time_t t2 = time(0);
   printf("sum=%I64d %d secs\n", sum, t2-t1);
   return 0;
}s