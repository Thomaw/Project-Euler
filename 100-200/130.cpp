#include <stdio.h>
#include <math.h>
long long int n,k,foundit,rem;
int checkifprime(long long int n);
main()
{
  long long int summ=0;
  int ct=0;
  n=1;
  while(ct<25)
    {
      if(n%2!=0 && n%5!=0 && !checkifprime(n))
	{
	  foundit=0;
	  k=1;
	  rem=1;
	  while(foundit==0)
	    {
	      k++;
	      rem=(rem*10+1)%n;
	      if(rem==0)
		foundit=1;
	    }
	  if((n-1)%k==0)
	    {
	      ct++;
	    printf("%d %lld %lld\n",ct,n,k);
	    summ+=n;
	    }
	}
      n++;
    }
  printf("%lld\n",summ);
}
	  
	      
int checkifprime(long long int n)
{
  int isprime;
  long long int i;
  long long int upbound=(long long int)pow((double)n,0.5)+3;
  isprime=1;
  i=2;
  while(isprime==1 && i<=upbound)
    {
      if(n%i==0)
	isprime=0;
      i++;
    }
  return isprime;
}