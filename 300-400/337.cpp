#include <stdio.h>
#include <math.h>
#define MAXN 20000000
#define MODD 100000000
#define ll long long
int factor[MAXN+2];
int eulerphi[MAXN+2];
int tree[MAXN+2];
ll seqs[MAXN+2];

void update(int idx,int val)
{
  while(idx<=MAXN)
    {
      tree[idx]=(tree[idx]+val)%MODD;
      idx+=(idx&-idx);
    }
}

int read(int idx)
{
  int sum=0;
  while(idx>0)
    {
      sum=(sum+tree[idx])%MODD;
      idx-=(idx&-idx);
    }
  return sum;
}

int main()
{
  for(int i=1;i<=MAXN;i++)
    factor[i]=-1;
  
  for(int i=2;i<=MAXN;i++)
    {
      if(factor[i]==-1)
	{
	  for(int j=i;j<=MAXN/i;j++)
	    factor[i*j]=i;
	}
    }
  eulerphi[1]=1;
  eulerphi[2]=1;
  for(int i=3;i<=MAXN;i++)
    {
      if(factor[i]==-1)
	eulerphi[i]=i-1;
      else 
	{
	  if((i/factor[i])%factor[i]==0)
	    eulerphi[i]=eulerphi[i/factor[i]]*factor[i];
	  else
	    eulerphi[i]=eulerphi[i/factor[i]]*(factor[i]-1);
	}
    }

  for(int i=1;i<=MAXN;i++)
    tree[i]=0;
  for(int i=MAXN;i>=6;i--)
    {
      //printf("%d %d\n",i,eulerphi[i]);
      seqs[i]=1;
      if(i-1>=eulerphi[i]+1)
	seqs[i]=(seqs[i]+read(i-1)-read(eulerphi[i]))%MODD;
      seqs[i]=(seqs[i]+MODD)%MODD;
      
      update(eulerphi[i],seqs[i]);

   

      /*seqs[i]=1+(cumulfreq[i-1]-cumulfreq

      for(int j=i+1;j<=MAXN;j++)
	{
	  
	  if(eulerphi[j]>eulerphi[i] && eulerphi[j]<i)
	    {
	      seqs[i]=(seqs[i]+seqs[j])%MODD;
	      maxj=j;
	    }
	}
	printf("%d, %d\n",i,maxj);*/
    }
  printf("%lld\n",seqs[6]);

  
}