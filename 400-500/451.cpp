// problem 451
//
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const unsigned int limit   = 20000000;

static vector<uint8_t> sieve(limit+1);
static vector<uint32_t> primes;

static uint64_t total_sum;

static void init_primes( void )
{
     for (auto &x : sieve) x=0;

     for (unsigned int i=2; i<sieve.size(); i++)
     {
	  if (sieve[i] == 0)
	  {
	       primes.push_back(i);
	       for (unsigned int j=i; j<sieve.size(); j+=i)
	       {
		    sieve[j] = 1;
	       }
	  }
     }
}

static void gcd(int32_t x, int32_t y, 
		int32_t &nx, int32_t &ny)
{
     //
     // On the assumption that gcd(x,y)=1, return nx and ny s.t. x*nx+y*ny = 1;
     //
     if (x<y) {
	  gcd(y,x,ny,nx);
	  return;
     }

     int32_t n1x = 1;
     int32_t n1y = 0;
     int32_t n2x = 0;
     int32_t n2y = 1;

     while (true) {
          int32_t z = x%y;
          if (z == 0) {
               nx = n2x;
               ny = n2y;
               return ;
          }

          int32_t n = x/y;
          int32_t n3x = n1x - n*n2x;
          int32_t n3y = n1y - n*n2y;
          x = y ;
          y = z ;

          n1x = n2x;
          n1y = n2y;

          n2x = n3x;
          n2y = n3y;
     }
}


void search( unsigned int np,   // index of next prime
	     uint32_t     ppr,  // product of primes so far
	     uint32_t     *r,   // possible solutions of x*x=1 mod ppr
	     uint32_t     nr )  // number of solutions
{
     unsigned int i, j, j2;

     if (ppr > 2) 
     {
	  unsigned int r_max = 1;
	  for (i=0; i<nr; i++)
	  {
	       if (r[i] != ppr-1)
	       {
		    if (r[i] > r_max)
		    {
			 r_max = r[i];
		    }
	       }
	  }

	  total_sum += r_max;
     }


     uint32_t rr[512];
     for (i=np; i<primes.size(); i++)
     {
	  uint32_t p = primes.at(i);

	  if (p*(uint64_t) ppr > limit) break;

          do
	  {
	       uint32_t pppr = ppr*p;
	       j2 = 0;

	       int32_t n1, n2;
	       gcd( ppr, p, n1, n2 );

	       for (j=0; j<nr; j++)
	       {
		    int64_t t0 = p*(uint64_t)n2*(r[j]-1)+1;
		    int64_t t1 = p*(uint64_t)n2*(r[j]+1)-1;
		    if (t0 < 0) t0 += pppr * (1-t0/pppr);
		    t0 %= pppr;
		    rr[j2++] = t0;

		    if (t1 < 0) t1 += pppr * (1-t1/pppr);
		    t1 %= pppr;
		    rr[j2++] = t1;
	       }

	       search( i+1, pppr, rr, j2 );

	       if (primes.at(i) > limit/p) break;

	       p *= primes.at(i);
	  } while (p*(uint64_t) ppr <= limit);
     }
}

void solve(void)
{
     uint32_t r[4];
     r[0] = 1;
     search( 1, 2, r, 1);

     r[0] = 1;
     r[1] = 3;
     search( 1, 4, r, 2);

     for (uint32_t q=8; q<=limit; q*=2)
     {
	  r[0] = 1;
	  r[1] = q/2-1;
	  r[2] = q/2+1;
	  r[3] = q-1;
	  search( 1, q, r, 4);
     }

     for (unsigned int i=1; i<primes.size(); i++)
     {
	  uint32_t q = primes.at(i);
	  while (q <= limit)
	  {
	       r[0] = 1;
	       r[1] = q-1;
	       search( i+1, q, r, 2 );
	    
	       if (primes.at(i) > limit/q) break;
	       q *= primes.at(i);
	  }
     }

     cout << "total_sum  = " << total_sum << endl;
}

int main( int argc, char ** argv )
{     
     init_primes();

     solve();

     cout << "Correct      153651073760956" << endl;

     return 0;
}