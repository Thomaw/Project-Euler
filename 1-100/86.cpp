#include "iostream.h"
#include "math.h"

using namespace std;

int main()
{
   int M=1;
   int allcount=0;

   do {
      int count=0;
      for (int i=1; i<=M; i++)
         for (int j=i; j<=M; j++)
         {
         int t=j+M;
         int l1=i*i+t*t;
         t=i+M;
         int l2=j*j+t*t;
         t=i+j;
         int l3=M*M+t*t;
         int min1=l1;
         if (l2 < min1) min1=l2;
         if (l3 < min1) min1=l3;
         int s=sqrt(min1);
         if ((s*s)==min1)
            count++;
	 }
      allcount+=count;
      M++;
   } while (allcount<1000000);

   cout << endl << --M << endl;
   return 0;				
}