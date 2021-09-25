#include <stdio.h>

typedef __int64 LL;

int main()
{
	int n,k,i;
	LL p[20]={1};
	for(i=1;i<20;i++) p[i]=10*p[i-1];
	LL ans=0;
	for(n=2;n<1000000;n++)
	{
		char s[20];
		int L=sprintf(s,"%I64d",p[16]/n);
		ans-=L;
		for(k=0;k<=L;k++)
		{
			for(i=0;i<k && s[i]==s[L-k+i];i++);
			if(i==k) ans+=p[k];
		}
	}
	printf("%I64d\n",ans);
	return 0;
}