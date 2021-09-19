#include <iostream.h>

void main ()
{
 const int SIZE=10;
 int array[SIZE];
 int   three, five;
 long sum=0;

 for (int i=1;i<SIZE;i++)
    {
      three= (i%3==0);
      five= (i%5==0);
      if (three||five)
       {
	 cout<<i<<" ";
	 sum =  sum+ (i*i); // the key line of code
       }//endif
     } //endfor
    cout<<"\n"<<sum;
} //end main
