#include "math.h"

long double N=1000000;
long double count=0;

// k x k - inner square ("hole")
// size of largest lamina with (k x k) hole (k+2+2+2...+2)
// (k+2+2+2...+2)^2 <= N
 
for( long double k=1; k<=floorl(N/4-1); k++ ) {
  count+=floorl((floorl(sqrtl(N+(long double)k*k))-k)/2);
}

// one of floorls is redundant: this suits too
//  count += floorl( ( sqrtl(N+(long double)k*k) -k)/2 );