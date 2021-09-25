#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
long a,b,c,taille,etape,flag,flagg,i,j,num,sodom,compteur,somme;
double elapsed,plafond;
long t[100000];
clock_t start,end;

long cycle(long n)
{
     a=0;
     b=1;
     c=1;
     taille=1;
     flag=0;
     etape=1;
     while (flag==0)
     {
           a=c;
           b=(b*10)%n;
           c=(a+b)%n;
           if (c==0)
           {
                    taille=etape+1;
                    flag=1;
           }
           if (etape==n+1)
           flag=1;
           etape++;
     }
return taille;
}

int main(int argc, char *argv[])
{
  start=clock();
  i=1000000;
  flagg=0;
  while(flagg==0)
  {
     if(i%2!=0)
     if(i%5!=0)
     if(cycle(i)>1000000)
     {
       flagg=1;
       printf(\"%ld\\n\",i);
     }
     i++;
     if(i%100000==0)
     printf(\"%ld\\n\",i);
  }
  end=clock();
  elapsed=((double)end-start)/CLOCKS_PER_SEC;
  printf(\"%lf\\n\",elapsed);          
  system(\"PAUSE\");
}