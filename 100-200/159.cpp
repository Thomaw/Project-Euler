#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef unsigned int ui;

const ui M=1000000;
ui f[M];

ui DigitalRoot(ui n)
{
ui s=0;
while(n>0)
   {
   s+=n%10;
   n/=10;
   }
if(s>9) return DigitalRoot(s);
return s;
}


int main()
{
double time=clock();
for(ui i=2;i<M;i++) f[i]=DigitalRoot(i);

unsigned long long s=0;
for(ui i=2;i<M;i++)
   {
   s+=f[i];
   for(ui j=2*i;j<M;j+=i)
      {
      ui ft_j=f[i]+f[j/i];
      if(f[j]<ft_j) f[j]=ft_j;   
      }
   }

cout<<s<<" in "<<clock()-time<<"ms"<<endl;
system("Pause");
return 0;
}