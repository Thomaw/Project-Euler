#include <stdio.h>


int main()  {

    int i,j,L,T,digit[20];
    long long int I;
    for(i=1000000030;;)  {
        I=i;
        I*=I;
        L=0;
        while(I)  digit[L]=I%10,I/=10,L++;
        T=0;
        for(j=2;j<=18;j+=2)
            if(digit[j]==10-j/2)  T++;
        if(T==9)  {
           printf("%d\n",i);
           break;
        }
        if(i%100==30)  i+=40;
        else  i+=60;
    }
    return 0;
}