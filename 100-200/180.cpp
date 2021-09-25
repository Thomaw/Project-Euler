#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef unsigned long long int64;
const int k=35;

int main()
{
double time=clock();

const int m=13220;
int su[m];
int sv[m];
int i=0;

for(int a=1;a<k;a++){
for(int b=a+1;b<=k;b++){if(gcd(a,b)==1){

for(int e=1;e<k;e++){
for(int f=e+1;f<=k;f++){if(gcd(e,f)==1){

for(int c=1;c<k;c++){int bcf=b*c*f,bec=b*e*c,fac=f*a*c;
for(int d=c+1;d<=k;d++){if(gcd(c,d)==1)

{
int afd=a*f*d,bed=b*e*d,dea=d*e*a;
        
// n<0
if(bec<dea && fac<dea)
     {
     int64 p=bec,q=fac,r=dea;
        for(int n=1;n<3;n++)
        { 
        if(p+q==r)
            {
            int v=b*f*d;
            int u=afd+bed+bcf;
            int g=gcd(u,v);
            v/=g;
            u/=g;
            for(int j=0;j<i;j++)
               {
               if(sv[j]==v && su[j]==u) {goto A;}
               }
            sv[i]=v;
            su[i]=u;
            i++;
            A:
            int pp;
            }
        p*=p;
        q*=q;
        r*=r;
        }
     }   
     
// n>0
if(afd<bcf && bed<bcf)
     {
     int64 p=afd,q=bed,r=bcf;
        for(int n=1;n<3;n++)
        { 
        if(p+q==r)
            {
            int v=b*f*d;
            int u=afd+bed+bcf;
            int g=gcd(u,v);
            v/=g;
            u/=g;
            for(int j=0;j<i;j++)
               {
               if(sv[j]==v && su[j]==u) {goto B;}
               }
            sv[i]=v;
            su[i]=u;
            i++;
            B:
            int pp;
            }
        p*=p;
        q*=q;
        r*=r;
        }
     }
     
}}}
}}}
}}}


int64 y=1;
int64 x=0;
for(int j=0;j<i;j++) 
   {
   int64 v=sv[j],u=su[j];
   int64 g=gcd64(y,v);
   int64 vg=v/g;
   x*=vg;
   x+=u*(y/g);
   y*=vg;
   g=gcd64(x,y);
   x/=g; 
   y/=g;
   }

cout<<x+y<<endl<<" in "<<clock()-time<<"ms"<<endl;
system("Pause");
return 0;
}