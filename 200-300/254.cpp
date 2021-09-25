#include <stdio.h>


int sf(long long int x)  {
    
    int s=0;
    while(x)  s+=x%10,x/=10;
    return s;
}

int main()  {

    int i,j,L,d,fact[10];
    long long int A[151][10],n,s,p10[20],v[10],w[10],s1,s2,diff;
    p10[0]=1;
    for(i=1;i<20;i++)p10[i]=10*p10[i-1];
    fact[0]=1;
    for(i=1;i<10;i++)fact[i]=i*fact[i-1];
    
    for(i=1;i<=150;i++)
        for(j=1;j<10;j++)  A[i][j]=(j==9)*p10[18];
    
    for(L=1;L<=18;L++)
        for(d=1;d<10;d++)
            for(i=0;i<1000000;i++)  {
                 n=d*p10[L-1]-i;
                 if(n>0)  {
                    s=sf(n);
                    if(s<=150)  {
                    for(j=9;j>=1;j--)  v[j]=n/fact[j],n%=fact[j];
                    for(j=1;j<10;j++)  w[j]=A[s][j];
                    
                    s1=0,s2=0;
                    for(j=1;j<10;j++)  s1+=v[j],s2+=w[j];
                    diff=0;
                    if(s1!=s2)  diff=s2-s1;
                    else {
                       for(j=1;j<10;j++)
                           if(v[j]!=w[j])  {
                              diff=v[j]-w[j];
                              break;
                           }
                   }
                   if(diff>0)  {
                      for(j=1;j<10;j++)  A[s][j]=v[j];
                   }}
                }
          }
   s=0;
   for(i=1;i<=150;i++)
       for(j=1;j<10;j++)  s+=j*A[i][j];
   printf("s=%lld\n",s);
   return 0;
}