#include <stdio.h>
#include <math.h>
bool isprime(long long int prime);
long long int primes[4000000];
int main()
{
  long long int N=999966663333ll;
  //long long int N=1000;
  long long int count=0;
  for(long long int i=2;i*i<=N+10000;i++)
    {
      if(isprime(i))
	{
	  
	  primes[count]=i;
	  //printf("%lld\n",i);
	  count++;
	}
    }
  long long int ct=0;
  long long int ctr=0;
  for(long long int i=0;i<count-1;i++)
    {
      long long int p1=primes[i];
      long long int p2=primes[i+1];
      for(long long int j=p1*p1+p1;j<=p2*p2-1;j+=p1)
	{
	  if(j<=N)
	  if((j%p1==0 && j%p2!=0) || (j%p1!=0 && j%p2==0) )
	    {
	    ct+=j;
	    ctr=(ctr+j)%100000;

	    // printf("%lld\n",j);
	    }
	}
        for(long long int j=p2*p2-p2;j>=p1*p1+1;j-=p2)
	{
	  if(j<=N)
	  if((j%p1==0 && j%p2!=0) || (j%p1!=0 && j%p2==0) )
	    {
	    ct+=j;
	    ctr=(ctr+j)%100000;
	    //printf("%lld\n",j);
	    }
	}
    }
  printf("%lld %lld\n",ct,ctr);
}


bool isprime(long long int num)
{
  for(long long int i=2;i*i<=num;i++)
    {
      if(num%i==0)
	return 0;
    
    }
  return 1;
}