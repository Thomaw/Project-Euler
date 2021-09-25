#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

long long int numways[13497500][2];
vector <int> primes;
map <pair <long long int,int>, long long int> hashed;
long long int MOD;



bool isprime(int x)
{
  for(int i=2;i*i<=x;i++)
    if(x%i==0)
      return 0;
  return 1;
}


int main()
{
  MOD=10000000000000000ll;

  primes.resize(0);
  for(int i=2;i<=5000;i++)
    {
      if(isprime(i))
	primes.push_back(i);
    }

  numways[0][0]=1;
  for(int i=0;i<primes.size();i++)
    {
      printf("%d\n",i);
      for(int j=0;j<1707300;j++)
	{
	  if(j>=primes[i])
	    numways[j][1]=(numways[j-primes[i]][0]+numways[j][0])%MOD;
	  else
	    numways[j][1]=numways[j][0];
	}
      for(int j=0;j<1707289;j++)
	numways[j][0]=numways[j][1];
    }
  long long int count=0;
  for(int i=2;i<1707300;i++)
    if(isprime(i))
      {
	printf("%d %lld\n",i,numways[i][0]);
	count=(count+numways[i][0])%MOD;
      }
  printf("%lld\n",count);



}