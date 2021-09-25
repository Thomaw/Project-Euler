#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef unsigned int ui;

const long MAX=1000000;
short z[MAX+1];

int main()
{
double dt=clock();

for(ui i=2;i<=MAX;i++) {z[i]=0;}

for(ui p=2;p<=MAX;p++)
       {
       ui a=4-p%4;
       ui n=0;
       for(ui v=0;v<(3*p-a)/4;v++)
              {
              n=p*(4*v+a); 
              if(n<=MAX) {z[n]++;}
              else {v=MAX;}
              }
       }

ui x=0;
for(ui i=2;i<=MAX;i++)
   {if(z[i]==10) {x++;}}

cout<<x<<" in "<<clock()-dt<<"ms"<<endl;

return 0;
}