#include <iostream>
#include <vector>

long long int mod = 1000000007;

#define MATSIZE 200
long long int* mat;
long long int* val;

void doPower( long long int k )
{
  long long int* powm = new long long int[MATSIZE*MATSIZE];
  long long int* tmp = new long long int[MATSIZE*MATSIZE];
  for ( int i = 0 ; i < MATSIZE*MATSIZE ; ++i )
  {
    val[i] = 0;
    powm[i] = (mod+mat[i])%mod;
  }
  for ( int i = 0 ; i < MATSIZE ; ++i )
    val[i+MATSIZE*i] = 1;
  while ( k )
  {
    //std::cout << k << std::endl;
    if ( k%2 )
    {
      for ( int i = 0 ; i < MATSIZE*MATSIZE ; ++i )
        tmp[i] = 0;
      for ( int i = 0 ; i < MATSIZE ; ++i )
      {
        for ( int j = 0 ; j < MATSIZE ; ++j )
        {
          for ( int ind = 0 ; ind < MATSIZE ; ++ind )
          {
            tmp[i*MATSIZE+j] += powm[i*MATSIZE+ind]*val[ind*MATSIZE+j];
            tmp[i*MATSIZE+j] %= mod;
          }
        }
      }
      for ( int i = 0 ; i < MATSIZE*MATSIZE ; ++i )
        val[i] = tmp[i];
    }
    for ( int i = 0 ; i < MATSIZE*MATSIZE ; ++i )
      tmp[i] = 0;
    for ( int i = 0 ; i < MATSIZE ; ++i )
    {
      for ( int j = 0 ; j < MATSIZE ; ++j )
      {
        for ( int ind = 0 ; ind < MATSIZE ; ++ind )
        {
          tmp[i*MATSIZE+j] += powm[i*MATSIZE+ind]*powm[ind*MATSIZE+j];
          tmp[i*MATSIZE+j] %= mod;
        }
      }
    }
    for ( int i = 0 ; i < MATSIZE*MATSIZE ; ++i )
      powm[i] = tmp[i];
    k /= 2;
  }
  delete[] powm;
  delete[] tmp;
}

int calcMat( long long int w, long long int h )
{
  mat = new long long int[MATSIZE*MATSIZE];
  val = new long long int[MATSIZE*MATSIZE];

  for ( int i = 0 ; i < MATSIZE*MATSIZE ; ++i )
    mat[i] = 0;

  for ( int i = 0 ; i < MATSIZE ; ++i )
  {
    int ch = i%100;
    int pa = (i/100)&1;
    for ( int j = 0 ; j < h ; ++j )
    {
      int paradd = 0;
      if ( j > ch )
        paradd = (j-ch)%2;
      paradd ^= pa;
      int newind = j + paradd*100;
      ++mat[newind*MATSIZE+i];
    }
  }

  doPower( w );
  long long int cnt = 0;
  for ( int i = 100 ; i < 200 ; ++i )
    cnt = (cnt+val[i*MATSIZE])%mod;
  delete[] mat;
  delete[] val;
  
  return cnt;
}

long long int calcDyn( long long int w, long long int h ) {
  long long int* reg = new long long int[10000];
  long long int* nex = new long long int[10000];
  for ( int i = 0 ; i < 10000 ; ++i )
    reg[i] = i%2;

  long long int tot = 1;
  for ( int l = 0 ; l < w ; ++l )
  {
    long long int running[2];
    running[0] = 0;
    for ( int i = 0 ; i < h ; ++i )
    {
      nex[i] = 0;
      running[0] += reg[i];
    }
    running[0] %= mod;
    running[1] = running[0];
    for ( int i = 0 ; i < h ; ++i )
    {
      nex[i] = running[i%2];
      running[i%2] += tot;
      running[i%2] += 2*mod-2*reg[i+1-2*(i%2)];
      running[i%2] %= mod;
      if ( i%2 )
        nex[i] = running[i%2];
    }
    for ( int i = 0 ; i < h ; ++i )
      reg[i] = nex[i];
    tot *= (h%mod);
    tot %= mod;
  }
  return reg[0];
}

std::vector<long long int> pasc(110*110,0);
std::vector<long long int> bern(110,0);
std::vector<long long int> faul(110*110,0);

long long int invert( long long int num, long long int base )
{
   std::vector<long long int> mult(2,0);
   std::vector<long long int> reduc(2,base);
   reduc[1] = num%base;
   std::vector<long long int> ans(2,0);
   ans[1] = 1;
   int curr = 1;
   while ( reduc[curr] != 1 )
   {
      long long int div = reduc[curr-1]/reduc[curr];
      mult.push_back(div);
      reduc.push_back(reduc[curr-1]-div*reduc[curr]);
      ans.push_back(ans[curr-1]-div*ans[curr]);
      ++curr;
   }
   return (ans[curr]+base)%base;
}

void genFaul( )
{
  // First generate binomial coefficients
  for ( long long int i = 0 ; i <= 105 ; ++i )
  {
    pasc[110*i] = 1;
    for ( int k = 1 ; k <= i ; ++k )
      pasc[110*i+k] = (pasc[110*(i-1)+k-1]+pasc[110*(i-1)+k])%mod;
  }

  // Then Bernoulli numbers
  std::vector<long long int> a(110);
  std::vector<long long int> minv(110);
  for ( int i = 1 ; i < 105 ; ++i )
    minv[i] = invert( i, mod );
  long long int den = 1;
  for ( long long int i = 0 ; i <= 105 ; ++i )
  {
    den = (den*(i+1))%mod;
    bern[i] = 0;
    if ( !(i%2) )
    {
      for ( int m = 0 ; m <= i ; ++m )
      {
        a[m] = (den*minv[m+1])%mod;
        for ( int j = m ; j > 0 ; --j )
          a[j-1] = (j*(mod+a[j-1]-a[j]))%mod;
      }
      bern[i] = a[0];
    }
    bern[i] *= invert(den,mod);
    bern[i] %= mod;
  }
  bern[1] = (mod-1)/2;

  // Finally construct the Faulhaber polynomials
  for ( long long int p = 0 ; p < 105 ; ++p )
  {
    for ( long long int j = 0 ; j <= p ; ++j )
    {
      long long int num = bern[j]*pasc[110*(p+1)+j];
      num %= mod;
      if ( j%2 )
        num = (mod-num)%mod;
      faul[110*p+p+1-j] = (num*minv[p+1])%mod;
    }
  }
}

long long int sumk( long long int p, long long int n )
{
  long long int res = 0;
  for ( int i = 1 ; i <= p+1 ; ++i )
  {
    long long int newnum = faul[110*p+i];
    for ( int k = 0 ; k < i ; ++k )
      newnum = (newnum*(n%mod))%mod;
    res = (res+newnum)%mod;
  }
  return res;
}

void promote( std::vector<long long int>& poly )
{
  std::vector<long long int> newp( 105, 0 );
  for ( int i = 0 ; i < 105 ; ++i )
  {
    if ( !poly[i] )
      continue;
    for ( int j = 1 ; j <= i+1 ; ++j )
    {
      newp[j] += 2*poly[i]*faul[110*i+j];
      newp[j] %= mod;
    }
  }
  for ( int i = 0 ; i < 105 ; ++i )
    poly[i] = (mod-newp[i])%mod;
}

long long int calcPol( long long int w, long long int h )
{
  std::vector<long long int> peven(105,0);
  std::vector<long long int> podd(105,0);
  std::vector<long long int> sube(105,0);
  std::vector<long long int> subo(105,0);
  peven[0] = 1;
  long long int tot = 1;
  for ( int d = 0 ; d < w ; ++d )
  {
    long long int sumConst = 0;
    for ( int i = 0 ; i < 105 ; ++i )
    {
      if ( peven[i] + podd[i] )
      {
        sumConst += peven[i]*sumk( i, h/2 );
        sumConst += podd[i]*sumk( i, (h+1)/2 );
        sumConst %= mod;
      }
    }
    
    sube = podd;
    promote( sube );
    sube[1] += tot;
    sube[1] %= mod;
    sube[0] += sumConst;
    sube[0] %= mod;
    
    subo = peven;
    promote( subo );
    subo[1] += tot;
    subo[1] %= mod;
    subo[0] += sumConst;
    subo[0] %= mod;
    for ( int i = 0 ; i < 105 ; ++i )
    {
      subo[i] += 2*peven[i];
      subo[i] %= mod;
    }
    subo[0] += mod-tot;
    subo[0] %= mod;
    
    tot *= h%mod;
    tot %= mod;
    peven = sube;
    podd = subo;
  }

  long long int guess = 0;
  for ( int k = 104 ; k >= 0 ; --k )
    guess += podd[k];
  guess %= mod;
  return guess;
}

int main()
{
  long long int highMat = calcMat( 1000000000000, 100 );
  long long int lowMat  = calcMat( 1000000000000, 100-1 );
  std::cout << " 10^12 by  100    " <<
              (mod+highMat-lowMat)%mod << std::endl;

  long long int highDyn = calcDyn( 10000, 10000 );
  long long int lowDyn  = calcDyn( 10000, 10000-1 );
  std::cout << " 10000 by 10000   " <<
              (mod+highDyn-lowDyn)%mod << std::endl;

  genFaul( );
  long long int highPol = calcPol( 100, 1000000000000 );
  long long int lowPol  = calcPol( 100, 1000000000000-1 );
  std::cout << "  100  by 10^12   " <<
              (mod+highPol-lowPol)%mod << std::endl;
  
  long long int res = (mod+highMat-lowMat)
                    + (mod+highDyn-lowDyn)
                    + (mod+highPol-lowPol);

  std::cout << std::endl << "     Total        " << res%mod << std::endl;
}
