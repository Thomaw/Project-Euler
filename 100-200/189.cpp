#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gmp.h"


#define maxN 16

int main()  {

    time_t seconds=time(NULL);

    mpz_t result;
    mpz_t prod;
    mpz_t temp;
    mpz_t inv;
    mpz_t P;
    mpz_t PR;
    mpz_t up;
    
    mpz_init(result);
    mpz_init(prod);
    mpz_init(temp);
    mpz_init(inv);
    mpz_init(P);
    mpz_init(PR);
    mpz_init(up);
 
    int *A,*B,S=1,rem[32][32],div,n,i,j,d,pow3,lpow3,k,p,c1,c2,x[3],count=0,pos,sum,digit[32];
    int smallprimes[32],pr=100000000;
    for(i=1;i<maxN;i++)  S*=3;
    
    A=(int*) (malloc) (S*sizeof(int));
    B=(int*) (malloc) (S*sizeof(int));
    
    mpz_set_ui(prod,1);
    mpz_ui_pow_ui(up,3,maxN*maxN);
    
    while(mpz_cmp(prod,up)<=0) {
    mpz_set_ui(PR,pr+1);
    mpz_nextprime(PR,PR);
    pr=mpz_get_ui(PR);
    smallprimes[count]=pr;
    mpz_mul_ui(prod,prod,pr);
    count++;
    A[0]=1;
    pow3=1;
    lpow3=3;

    for(n=2;n<=maxN;n++)  {
        for(i=0;i<pow3;i++)  {
            B[i]=A[i];
            p=i;
            for(j=1;j<n;j++)  digit[j]=p%3,p/=3;
            k=0,p=1;
            for(j=1;j<n;j++)  k+=((digit[j]+1)%3)*p,p*=3; 
            B[k]=A[i];
            k=0,p=1;
            for(j=1;j<n;j++)  k+=((digit[j]+2)%3)*p,p*=3;
            B[k]=A[i];
        }
        
        div=pow3;
        for(k=1;k<n;k++)  {
            for(i=0;i<lpow3;i++)  A[i]=0;
            for(i=0;i<lpow3;i++)  {
                c1=(i/(3*div))%3;
                c2=(i/div)%3;
                d=i-div*c2;
                pos=d;
                for(j=0;j<3;j++)  {
                    x[0]=1,x[1]=1,x[2]=1;
                    x[c1]=0;
                    x[c2]=0;
                    x[j]=0;
                    A[pos]=(A[pos]+B[i]*(x[0]+x[1]+x[2]))%pr;
                    pos+=div;
                }
            }
            for(i=0;i<lpow3;i++)  B[i]=A[i];
            div/=3;
        }
        sum=0;
        for(i=0;i<lpow3;i++)  sum=(sum+A[i])%pr;
        rem[n][count-1]=sum;
    pow3*=3;
    lpow3*=3;
    }}
    if(maxN>0)  printf("For 1 triangle #colourings=3\n");
    for(n=2;n<=maxN;n++)  {
        mpz_set_ui(prod,smallprimes[0]);
        mpz_set_ui(result,rem[n][0]);
        for(i=1;i<count;i++)  {
            pr=smallprimes[i];
            mpz_set_ui(P,pr);
            mpz_invert(inv,prod,P);

            mpz_set_ui(temp,rem[n][i]);
            mpz_sub(temp,temp,result);
            
            mpz_mul(temp,temp,inv);
            mpz_mod(temp,temp,P);
            
            mpz_addmul(result,temp,prod);
            
            mpz_mul(prod,prod,P);
        }
        mpz_mul_ui(result,result,3);
        gmp_printf("For %d triangles #colourings=%Zd\n",n*n,result);
    }
    printf("Total time=%ld sec.\n",(int) time(NULL)-seconds);
    
    return 0;
}