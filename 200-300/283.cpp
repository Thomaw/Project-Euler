
void main()
{
   __int64 tot = 0;
      
   // side lengths a,b,c, with a<=b<=c
   const int MAXRATIO = 1000;
   for ( __int64 r = 1; r <= 1000; r++ )     // ratio
   for ( __int64 x = 2; x <= 8000; x += 2 )  // c = a+b-x  for ratio to be < 1000, x needs to be small (skinny triangle)
   for ( __int64 a = std::max(x,(16*r*r+x*x)/(2*x)); ; a++ )
   {
      // given r and x, solve for b
      __int64 b_num = (2*a-x)*(x*x+16*r*r);  // b's numerator
      __int64 b_den = 2*x*(2*a-x)-16*r*r*2;  // b's denominator
      if ( b_den <= 0 ) continue;
      if ( b_num / b_den < a ) break; // b continues to shrink, so quit this loop
      if ( b_den == 0 || b_num % b_den ) continue; // b must be an integer
      __int64 b = b_num/b_den;
      __int64 c = a+b-x;
      if ( b < a ) continue; // hmm, i think i already checked this
      tot += a + b + c; 
   }
   
   cout << " tot =  " << tot << endl;
}
