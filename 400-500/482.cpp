
#include <iostream>
#include <cmath>
#include <vector>

std::vector< std::vector<long long int> > reg(1000000);

void findTriads( long long int a, long long int b, long long int c )
{
  if ( c > 3400000 )
    return;

  for ( long long int m = 1 ; m*a < 1000000 ; ++m )
    reg[a*m].push_back( b*m );
  for ( long long int m = 1 ; m*b < 1000000 ; ++m )
    reg[b*m].push_back( a*m );

  findTriads( 2*c - 2*b + a, 2*c - b + 2*a, 3*c - 2*b + 2*a );
  findTriads( 2*c + 2*b + a, 2*c + b + 2*a, 3*c + 2*b + 2*a );
  findTriads( 2*c + b - 2*a, 2*c + 2*b - a, 3*c + 2*b - 2*a );
}

int main()
{
  findTriads(3,4,5);
  long long int sum = 0;
  for ( long long int r = 1 ; r < 1000000 ; ++r )
  {
    if ( r%100000 == 0 )
      std::cout << r << std::endl;
    std::vector <long long int> legs = reg[r];
    int sz = legs.size();
    for ( int i = 0 ; i < sz ; ++i )
    {
      for ( int j = i ; j < sz ; ++j )
      {        
        unsigned long long int num = r*r*(legs[i]+legs[j]);
	unsigned long long int den = legs[i]*legs[j]-r*r;
        if ( den <= 0 )
          continue;
        if ( num%den )
          continue;
	long long int z = num/den;
	if ( z < legs[j] )
	  continue;
	if ( z < legs[i] )
	  continue;
	long long int hh = z*z+r*r;
	long long int sq = sqrt(hh+0.1);
        if ( sq*sq != hh )
          continue;
        den = legs[i]+legs[j]+z;
        if ( den > 5000000 )
          continue;
        sum += 2*den;
        sum += sqrt(legs[i]*legs[i]+r*r+0.1);
        sum += sqrt(legs[j]*legs[j]+r*r+0.1);
        sum += sqrt(z*z+r*r+0.1);
      }
    }
  }
  std::cout << sum << std::endl;
}