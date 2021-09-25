#include <stdio.h>

/*[a,b]/[b,c]=a/c  ==> res=(c1/a1)*(c1/a2)*(c3/a3)*(c4/a4)*/
int main(int argc, char *argv[])
{
  float a;float b;float c;float da;float db;float den=1.0;
  for(a=1.0;a<=9.0;a++)
  {
   for(b=a;b<=9.0;b++)
   {
    da=(10.0*a)+b;
    for(c=1.0;c<=9;c++)
    {
     db=(10*b)+c;
     if(da < db )
     {
      if(da/db==a/c)
      {
       printf("\n[%f/%f]=%f/%f",da,db,a,c);den=den*(c/a);
      }
     }
    }
   }
  }
  printf("\n den=%f\n",den);
  system("PAUSE");
  return 0;
}
