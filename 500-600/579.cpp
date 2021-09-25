#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long llu;

int32_t gcd(int32_t a, int32_t b) {return b?gcd(b, a%b):abs(a);}

int main(int argc, char **argv)
{
  llu ans=0, N=argc>1?strtoull(argv[1],NULL,0):5000, M=argc>2?strtoull(argv[2],NULL,0):1000000000;

  #pragma omp parallel for schedule(static, 1) reduction(+:ans)
  for(int32_t c=0; c <= N; c++) // c*c <= N is OK if not using OMP, or even 4*c*c < N

    for(int32_t b=c, g=c; b*b + (unsigned long long)c*c <= N; b++, g=gcd(b, c))

      for(int32_t a=c?c:b, gg=g; a*a + b*b + c*c <= N; a++, gg=gcd(a, g))

	for(int32_t d=(a^b^c^1)&1; d<=a && d<=b && a*a + b*b + c*c + d*d <= N; d+=2)

	  if(((a!=d && b!=c) || a==b || c==d) && (a*c<b*d || (a*c==b*d && a>=b)) && gcd(d, gg)==1)
	    {
	    int32_t //vertices of primitive cube of side length n are these rows:
	      x11=a*a+b*b-c*c-d*d, x12=2*(a*d+b*c), x13=2*(-a*c+b*d),
	      x21=2*(-a*d+b*c), x22=a*a-b*b+c*c-d*d, x23=2*(a*b+c*d),
	      x31=2*(a*c+b*d), x32=2*(-a*b+c*d), x33=a*a-b*b-c*c+d*d;

	    llu n=a*a+b*b+c*c+d*d, // side of this cube
	      //dimensions of smallest bounding box, and of smallest bounding cube (the max):
	      m1=(llu)x11+abs(x21)+x31, m2=(llu)x12+abs(x22)+abs(x32), m3=(llu)x13+x23+abs(x33),
	      m=(m1>m2)?((m1>m3)?m1:m3):((m2>m3)?m2:m3);  

	    if(m>N) continue;

	    llu g=gcd(x11, gcd(x12, x13)) + gcd(x21, gcd(x22, x23)) + gcd(x31, gcd(x32, x33)),
	      sym=!c?(!d?(!b?1:6):((a==b||b==d)?((a==d)?4:12):24)):(a==d && (a==b||a==c)?8:24),
	      tmp=0;
	    for(llu k=1; k<=N/m; k++)
	      {
	      tmp += (k*n*k*n % M *k*n + k*(k*n+1)*g + 1) % M // # of lattice points in scaled cube
		* ((N+1-k*m1) * (N+1-k*m2) % M * (N+1-k*m3) % M) % M; // # of shifts of scaled cube

	      if(tmp >> 63) tmp %= M;
	    }
	    ans += tmp % M * sym;
	    ans %= M;
	  }
  printf ("%llu\n", ans % M);  // need %M if running multi-threaded
}