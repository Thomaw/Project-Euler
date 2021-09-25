#include <iostream>
#include <cstdlib>
#include <math.h>
#include "stuffs.h"  //this is where i put my powmod function
#include <time.h>
using namespace std;

long long sqrtmod(long long n, long long p); //use the Tonelli-Shanks algorithm

int main () {
	clock_t startt= clock();
	long long M=1e11;
	long long N=1e8;

	//SIEVE PRIMES UP TO N
	bool * p; p=(bool*)calloc(N, sizeof(bool));
	p[0]=1,p[1]=1;
	for (int i=4; i<N; i+=2) p[i]=1;
	for (int i=3; i*i<N; i+=2) if (!p[i]) {
		for (int j=3*i; j<N; j+=2*i) p[j]=1;
	}
	long long * primes; primes=(long long*)calloc(1e7,sizeof(long long));
	int counter=1; primes[0]=2;
	for (int i=3; i<N; i+=2) if (!p[i]) primes[counter]=i,counter++;
	

	long long total=0;
	for (int i=0; i<3; i++) total+=primes[i]* ((M+1)/primes[i]); //I did p=2,3,5 separately
	
	for (int i=3; i<counter; i++) {
		if ( primes[i]%15 ==1) { // 15stuff
			long long rt5 = sqrtmod(5, primes[i]);
			long long half = (primes[i]+1)/2;
			long long phi= ( (1+rt5)* half)%primes[i];
			long long rtD =  sqrtmod( phi*phi-4, primes[i]);
			long long w5 = ( (phi + rtD)* half )%primes[i];

			long long v=sqrtmod(primes[i]-3, primes[i]);
			long long w3 = ((1+v) * half)%primes[i]; 

			long long w = (w3*w3)%primes[i]; w=(w*w5)%primes[i];
			long long wsq = (w*w)%primes[i];

			for (int j=0; j<15; j++) {
				total+=primes[i]* ( (M+primes[i]-w)/primes[i] );
				w= (w*wsq)%primes[i];
			}
		}
		else if (primes[i]%5 ==1) { //5stuff
			long long rt5 = sqrtmod(5, primes[i]);
			long long half = (primes[i]+1)/2;
			long long phi= ( (1+rt5)* half)%primes[i];
			long long rtD =  sqrtmod( phi*phi-4, primes[i]);

			long long w = ( (phi + rtD)* half )%primes[i];
			total+=primes[i]* ( (M+primes[i]-w)/primes[i] );
	
			w= ( (primes[i] +phi - rtD)* half )%primes[i];
			total+=primes[i]* ( (M+primes[i]-w)/primes[i] );

			phi= ( (primes[i]+1-rt5)* half)%primes[i];
			rtD =  sqrtmod( phi*phi-4, primes[i]);

			w = ( (phi + rtD)* half )%primes[i];
			total+=primes[i]* ( (M+primes[i]-w)/primes[i] );

			w= ( (primes[i] +phi - rtD)* half )%primes[i];
			total+=primes[i]* ( (M+primes[i]-w)/primes[i] );
			
			total+= primes[i] * ((M+1)/primes[i]);
		}
		else if ( primes[i]%3 ==1 ) { //3stuff
			long long v=sqrtmod(primes[i]-3, primes[i]);

			long long w = (1+v) * (primes[i]+1)/2; w=w%primes[i];			
			total+=primes[i]* ( (M+primes[i]-w)/primes[i] );

			w = (primes[i]+1-v) * (primes[i]+1)/2; w=w%primes[i];
			total+=primes[i]* ( (M+primes[i]-w)/primes[i] );

			total+= primes[i] * ((M+1)/primes[i]);
		}
		else total+= primes[i] * ((M+1)/primes[i]);
	}
	cout<<total<<endl;
	cout<<"time is "<< (double) (clock() - startt)/CLOCKS_PER_SEC<<endl;
	return 0;
}

long long sqrtmod (long long n, long long p) {
	n = n%p;
	long long Q= p-1, S=0;
	while (Q%2 ==0) Q/=2, S++;
	long long z=1;
	while ( powmod(z, (p-1)/2, p)==1 ) z++;
	long long R = powmod(n, (Q+1)/2, p), t=powmod(n,Q,p), M=S, c = powmod(z,Q,p);
	long long temp; long long i; long long b;
	while (t!=1) {
		temp=t, i=0;
		while (temp!=1) temp= (temp*temp)%p, i++;
		b= powmod(c, 1<<(M-i-1), p), R= (R*b)%p, c=(b*b)%p, t = (t*c)%p, M=i ;
	}
	return R;
}
