struct SPrimes
{
   enum{N=50};
   int* ap;
   unsigned int ixCurrent;
   unsigned int ixMax;
   SPrimes(unsigned int max=N)
   {
      if (max < 1000) max=1000;
      ap = new int[(ixMax=max)+1];
      ap[ixCurrent=0] = 2;
      ap[++ixCurrent] = 3;
      int ix = 5;
      int ani = 0;
      while (1)
      {
         if (isPrime(ix))
         {
            ap[++ixCurrent] = ix;
            if (ixCurrent >= ixMax)
               break;
         }
         ix += 2 + 2*(ani++ & 1);
      }
      printf(" found %d primes until ix=%d\n", ixCurrent, ix);
   }
   ~SPrimes()
   {
      delete [] ap;
   }
   int isPrime(unsigned __int64 number)
   {
      int ix = 0;
      int sqr = sqrt((__int64)number)+1;
      int divisor = ap[ix++];
      __int64 n = number;
	   while (divisor < sqr) {
		   if (0 == (n % divisor)) {
			   return 0;
		   }
         divisor = ap[ix++];
	   }
      return 1;
   }
   int isSquareFree(__int64 num)
   {
      int ix = 0;
      while (ix < ixCurrent)
      {
         int divisor = ap[ix++];
         divisor *= divisor;
         if ((num%divisor) == 0)
            return 1;
      }
      return 0;
   }
};
__int64 n[1400]={1};
__int64* p[52]={&n[0]};
std::set<__int64> objNumbers;
SPrimes objPrimes;
int main(int argc, char**argv)
{
   int ix = 1;
   int ipx = 1;
   int nx = 1;
   __int64* px;
   __int64* ppx = p[0];
   objNumbers.insert(1);
   while (ix < 51)
   {
      px = &n[nx];
      p[ix] = px;
      int ixx = 0;
      px[ixx++] = 1;
      while (ixx < ix)
      {
         __int64 n = ppx[ixx-1]+ppx[ixx];
         px[ixx++] = n;
         if (!objPrimes.isSquareFree(n))
            objNumbers.insert(n);
      }
      px[ixx++] = 1;
      ppx = px;
      nx += ixx;
      ++ix;
   }
   std::set<__int64>::iterator itx = objNumbers.begin();
   unsigned __int64 sum = 0;
   while (itx != objNumbers.end())
   {
      __int64 n = (*itx);
      sum += n;
      ++itx;
   }
   printf("sum=%I64u\n", sum);
   return 0;
}