#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

int powval[350250];

bool isprime(int x)
{
  for(int i=2;i*i<=x;i++)
    if(x%i==0)
      return 0;
  return 1;
}

int findmodpow(int i,int j)
{
  if(j==0)
    return 1;
  int tmp=findmodpow(i,j/2);
  if(j%2==0)
    return (tmp*tmp)%250;
  else
    return (tmp*tmp*((i)%250))%250;
}

int main()
{
  long long int MOD=10000000000000000ll;

  for(int i=1;i<=250250;i++)
    {
      
      powval[i]=findmodpow(i,i)%250;
      //printf("%d %d\n",i,powval[i]);
    }

  long long int answer[251][2];
 for(int j=0;j<250;j++)
	answer[j][0]=0;
  answer[0][0]=1;

  for(int i=1;i<=250250;i++)
    {
      for(int j=0;j<250;j++)
	{
	  answer[j][1]=(answer[(j-powval[i]+250)%250][0]+answer[j][0])%MOD;
	}
      for(int j=0;j<250;j++)
	answer[j][0]=answer[j][1];
	    

    }

  printf("%lld\n",answer[0][0]-1);


}