//------------------------------------
main() {
  long k=2;
  double S=0;

  for( long N=5; N<=10000; N++ ) {
    if( Test(N,k)==false ) {
      k++;
    }
    long k1=k/GCD(N,k);
    if( Cancel(Cancel(k1,5),2) == 1 ) S-=N;
    else S+=N;
  }
}

//------------------------------------
bool Test(long N, long k)
{
  double t=1;
  for( long i=1; i<=k; i++ ) t*=( (double)(k+1)/k );
  t*=(k+1);
  if( N>t ) return false;
  return true;
}
//------------------------------------