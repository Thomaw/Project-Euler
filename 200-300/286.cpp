double probThat20WereMade( double q )
{
   double p[51][51] = { 1 }; // [x][y] = given x shots (1,2,..,x), probability that y were made
   for ( int x        = 1; x        <= 50; x++        )
   for ( int numMade  = 0; numMade  <= x ; numMade++  )
      p[x][numMade] = (numMade>0?p[x-1][numMade-1]*(1-x/q):0) + p[x-1][numMade]*(x/q);

   return p[50][20];
}

void main()
{
   double lo = 50;
   double hi = 60;
   while ( hi - lo > 1e-13 )
   {
      double mid = (lo+hi)/2;
      double prob = probThat20WereMade( mid );
      if ( prob > .02 )  lo = mid;
      else               hi = mid;
   }
   cout.precision( 13 );
   cout << lo << endl;
}