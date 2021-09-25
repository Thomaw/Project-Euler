int c( int i )
{
   int ret = 0;
   for ( int k = 1; k < N/i; k++ )
      ret += (N/(i*k)-1) * moebius( k );

   return 1 - ret;
}