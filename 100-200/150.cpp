#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef int ui;
double pauze;

const ui m=1000;
const ui M=500500;
ui s[M+1];
ui a[m+1][m+1];

void make_s();
void make_a();

int main()
{
double time=clock();
make_s();
make_a();

long long X=0;
for(int j=1;j<=1000;j++)
   {
   for(int i=j;i<=1000;i++)
      {
      long long S=0;
      for(int i2=i;i2<=1000;i2++)
         {
         if(S<X) X=S;
         for(int j2=j;j2<=j+i2-i;j2++) S+=a[i2][j2];
         }
      }
   }


cout<<X<<" in "<<clock()-time<<"ms"<<endl;
system("Pause");
return 0;
}


void make_s()
{
long long t=0;
long long tmod=1048576;
for(ui k=1;k<=M;k++) 
   {
   t=(615949*t+797807);
   t=t%tmod;
   long long s_t=t-524288;
   s[k]=s_t;
   }
}

void make_a()
{
ui x=1;
for(int i=1;i<=m;i++)
   {
   for(int j=1;j<=i;j++) 
       {
       a[i][j]=s[x];
       x++;
       }
   }
}