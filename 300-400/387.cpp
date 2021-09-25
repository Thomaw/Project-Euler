#include <stdio.h>
typedef long long ll;
typedef unsigned long long ull;

ull ans;

#define LIM 14

int isprime(ull n) {
	int i;
	if(n<2) return 0;
	if(n<4) return 1;
	if(!(n&1)) return 0;
	for(i=3;(ull)i*i<=n;i+=2) if(n%i==0) return 0;
	return 1;
}

void btr(ull num,int ds,int dig) {
	int i,ds2;
	ull cur;
	/*	check if num/ds is prime */
	if(dig==LIM) return;
	for(i=0;i<10;i++) {
		cur=num*10+i;
		ds2=ds+i;
//		if(ullmillerrabin(num/ds) && ullmillerrabin(cur)) ans+=cur;
		if(isprime(num/ds) && isprime(cur)) ans+=cur;
		if(cur%ds2==0) btr(cur,ds2,dig+1);
	}
}

int main() {
	int i;
	ans=0;
	for(i=1;i<10;i++) btr(i,i,1);
	printf("%I64u\n",ans);
	return 0;
}