#include "stijn.cpp"
#include <algorithm>
typedef long long ui;

const int M=1000000;
const ui M2=1000000000000ll;

// primes
bool f[M];
int am=0;
int a[100000];

// squbes
vector<ui> X;

bool check_200(ui x)
 {    
 int a0=x%10;
 x/=10;
 int a1=x%10;
 while(x>0)
   {
   x/=10;
   int a2=x%10;
   if(a2==2 && a1==0 && a0==0) return true;
            
   a0=a1;
   a1=a2;
   }
 
 return false;
 }
 

bool IsPrime(ui n)
 {
 for(int i=0;a[i]<=sqrtint(n);i++)
    {
    if(n%a[i]==0) return false;
    }
 return true;
 }

int main()
  {  
  double time=clock();
  
  // prime sieve
  f[0]=f[1]=0;
  
  for(int i=2;i<M;i++) f[i]=1;
  
  for(int i=2;i<M;i++)
     {
     if(f[i]==1)
       {
       a[am]=i;
       
       for(int j=2*i;j<M;j+=i) f[j]=0;

       for(int j=0;j<am;j++)
          {
          ui x=(ui)i*(ui)i*(ui)a[j]*(ui)a[j]*(ui)a[j];
          if(x>M2) break;
          
          if(check_200(x)) X.push_back(x);
          }
        
        for(int j=0;j<am;j++)
          {
          ui x=(ui)i*(ui)i*(ui)i*(ui)a[j]*(ui)a[j];
          if(x>M2) break;
          
          if(check_200(x)) X.push_back(x);
          }
        
        am++;          
       }
     }
    
  // is prime proof ?
  for(int i=0;i<X.size();i++) 
     {
     ui x=X[i];
     if(x%2==0 || x%5==0)
       {
       x=x-(x%10);
       for(int j=1;j<=9;j+=2)
        {
        if(IsPrime(x+j)) {X[i]=M2; break;}
        }
       }
     
     else
       {
       for(ui j=1;j<x;j*=10)
          {
          ui x_t=x-((x/j)%10)*j;
          for(int k=0;k<=9;k++)
             {
             if(IsPrime(x_t+j*k)) {X[i]=M2+1; j=x; break;}
             }
          }
       }
     }
  
  sort(X.begin(),X.end());
  
  einde( X[199] );
  }