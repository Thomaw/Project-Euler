#include <stdio.h>


int main()  {
    
    int test,s,u,i,j,k,bit[32],T[32];
    long long int ans=0;

    for(i=0;i<134217728;i++)  {
        u=i;
        for(j=0;j<32;j++)  bit[j]=u&1,u>>=1;
        test=1;
        for(j=0;j<32;j++)  T[j]=0;
        for(j=0;test&&j<32;j++)  {
            s=0;
            for(k=0;k<5;k++)  s+=bit[(j+k)&31]<<k;
            if(T[s])  test=0;
            T[s]=1;
        }
        if(test)  ans+=i;
   }  
   printf("%lld\n",ans);
   return 0;
}