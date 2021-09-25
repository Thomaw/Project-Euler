#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()  {
    
    int *isprime,sec;
    long long int sum=0,*pr,interval,i,j,si,B,N,pos[32],ct,depth,backtrack;
    long long int mul[]={0,0,0,0,0,1,-6,21,-56,126,-252,462,-792,1287,-2002,3003};
    
    scanf("%lld",&B);
    interval=B/15561+1;
    pr=(long long int*)(malloc)(interval*sizeof(long long int));
    isprime=(int*)(malloc)(interval*sizeof(int));
    
    for(i=0;i<interval;i++)  isprime[i]=(i>1);
    for(i=0;i*i<=interval;i++)  {
        if(isprime[i])  {
           for(j=i*i;j<interval;j+=i)  isprime[j]=0;
        }
    }
    si=4;
    pr[1]=7;
    pr[2]=9;
    pr[3]=13;
    pr[4]=19;
    for(i=20;i<interval;i++)
        if(isprime[i]&&(i%3==1))  si++,pr[si]=i;
    printf("primes=%lld\n",si);
    
    sec=time(NULL);
    depth=1;
    pos[1]=0;
    while(depth>0)  {
          backtrack=0;
          pos[depth]++;
          if(pos[depth]>si)  backtrack=1;
          else {
             N=1;
             for(i=1;i<=depth;i++)  N*=pr[pos[i]];
             if(N>B)  backtrack=1;
             else {
                ct=B/N;
                sum+=mul[depth]*ct*(ct+1)/2*N;
                depth++;
                pos[depth]=pos[depth-1];
            }
         }
         if(backtrack)  depth--;
   }
   printf("sum=%lld,time=%ld sec.\n",sum,time(NULL)-sec);
}