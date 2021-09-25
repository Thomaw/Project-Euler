#include <stdio.h>
#include <math.h>


int main()
{
  int n1,n2,n3,n4,n5,m1,m2,m3,m4,m5;
  n1=1;
  n2=0;
  n3=0;
  n4=1;
  n5=0;
  long long int c=1;
  long long int totcost;
  long long int wanted=1000000000ll;
  long long int i=2;
  while(i+n1+1<=wanted)
    {
      i+=n1+1;
      m1=n2+n1-1;m2=n3+1;m3=n4;m4=n5+n1;m5=1;
      n1=m1;
      n2=m2;
      n3=m3;
      n4=m4;
      n5=m5;
      c++;
      
    }
  long long int diff=wanted-i;

      n1-=diff;
      n2+=diff;
      n5+=diff;     
    
   totcost=c*n1+(c+1)*n2+(c+2)*n3+(c+3)*n4+(c+4)*n5;

   printf("%lld\n",totcost);
 
}