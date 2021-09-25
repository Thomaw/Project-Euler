#include <stdio.h>
#include <stdlib.h>


void printint64(long long int n)  {
    long long int M=n;
    int digit[20],i,len;
    
    for(i=0;i<20;i++)  digit[i]=M%10,M/=10;
    len=19;
    while((len>=0)&&(digit[len]==0))  len--;
    for(i=len;i>=0;i--) printf("%d",digit[i]);
    printf("\n");
    
    return;
}


int main()  {

    unsigned long long int sum,***A;
    int i,j,k,d;
    A=(unsigned long long int***) (malloc) (41*sizeof(unsigned long long int));
    for(i=0;i<41;i++)  A[i]=(unsigned long long int**) (malloc) (10*sizeof(unsigned long long int));
    for(i=0;i<41;i++) 
    for(j=0;j<10;j++) A[i][j]=(unsigned long long int*) (malloc) (1024*sizeof(unsigned long long int));

    for(i=0;i<41;i++)
        for(j=0;j<10;j++)
           for(k=0;k<1024;k++)  A[i][j][k]=0;

    for(i=1;i<10;i++)  A[1][i][1<<i]=1;
    
    for(i=2;i<=40;i++)  {
        for(j=0;j<10;j++) {
            for(k=0;k<1024;k++)  {
               if(j!=0)  {
                 if((k>>(j-1))%2==0)  d=k+(1<<(j-1));
                 else d=k;
                 A[i][j-1][d]+=A[i-1][j][k];
               }
               if(j!=9)  {
                 if((k>>(j+1))%2==0)  d=k+(1<<(j+1));
                 else d=k;
                 A[i][j+1][d]+=A[i-1][j][k];
               }
          }
       }
    }
    
    sum=0;
    for(i=1;i<=40;i++)
        for(j=0;j<10;j++)  sum+=A[i][j][1023];
    printint64(sum);
    
    return 0;
}