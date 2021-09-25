void fx()
{
   /*
   n=2^a 3^b 5^c 7^d 11^e 13^f ... (a>b>c>d>e>f ...)
   2x+1 = (2a-1)(2b+1)(2c+1)(2d+1)(2e+1)(2f+1) ...
   2*47547+1 = 19 * 13 * 11 * 7 * 5 * 1
   a=10 b=6 c=5 d=3 e=2 f=0
   */
   enum{NP=8};
   int exponents[NP]={10,6,5,3,2,0}, primes[NP]={2,3,5,7,11,13,17,19};
   int64 ans=1;
   int i=-1,j;
   while (j=exponents[++i])
      while (j--)
         ans*=primes[i];
   printf("ans=%I64d\n",ans);
}

/*
Outputs:
ans=96818198400000
runtime 0.000 secs
*/