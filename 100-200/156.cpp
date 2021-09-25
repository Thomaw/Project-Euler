#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;
double getmval(int *digits,int m);
void fillit(int pos,int numdigits,int *digits,int whichdigit);
double total;
int main(int argc, char *argv[])
{
    int digits[20],numdigits,whichdigit;

     numdigits=14;
    whichdigit=1;
    digits[0]=numdigits;
    
    for(whichdigit=1;whichdigit<=9;whichdigit++)
    {
    //total=0;
    fillit(1,numdigits,&digits[0],whichdigit);
    printf("Total is %1.2f\n",total);
    }
        system("PAUSE");
    return EXIT_SUCCESS;
    
   
    
}


void fillit(int pos,int numdigits,int *digits,int whichdigit)
{
     int i,j;
     //cout << pos << endl ;
     double minnumber,maxnumber,number,getmval_minnumber,getmval_maxnumber;
     if(pos==numdigits+1)
       {
       //cout << digits[1] << endl ;
       number=0;
       for(i=1;i<=numdigits;i++)
         number=number*10+digits[i];
       //printf("Number is %1.2f\n",number);
       total+=number;
       return ;
       }
     
       
     for(i=0;i<=9;i++)
     {
        digits[pos]=i;
        //compute the maximum and the minimum number
        
        for(j=pos+1;j<=numdigits;j++)
           digits[j]=0;

        minnumber=0;
        for(j=1;j<=numdigits;j++)
          minnumber=minnumber*10+digits[j];
        getmval_minnumber=getmval(&digits[0],whichdigit);        
        for(j=pos+1;j<=numdigits;j++)
           digits[j]=9;
        maxnumber=0;
        
        for(j=1;j<=numdigits;j++)
          maxnumber=maxnumber*10+digits[j];
        getmval_maxnumber=getmval(&digits[0],whichdigit); 
        if(getmval_minnumber<=maxnumber && getmval_maxnumber>=minnumber)
            fillit(pos+1,numdigits,&digits[0],whichdigit);
          
        
     }
        
     

}


double getmval(int *digits,int m)
{
     int i;
     //cout <<  << endl ;
     if(digits[0]==0)
       return 0;
    double k;
    double retval=0;
    double number;
    int tmpdigits[20];
    for(i=1;i<=digits[0]-1;i++)
       tmpdigits[i]=digits[i+1];
    tmpdigits[0]=digits[0]-1;
    
    retval=0;
    k=(double)digits[0]-1;
    retval+=k*pow(10,k-1)*digits[1];
    if(m<digits[1])
        retval+=pow(10,k);
    if(m==digits[1])
        {
         number=0;
         for(i=2;i<=digits[0];i++)
            number=number*10+(double)digits[i];
         retval+=number+1;
        }
    
    retval+=getmval(&tmpdigits[0],m);
    
    return retval; 
        
        
    
}