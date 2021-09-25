int p[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
enum{NX=25,HI=1000000000};
unsigned __int64 hi=HI;
unsigned __int64 result;
void fx(int inx, unsigned __int64 num)
{
   int nx = 0;
   while (1)
   {
      if (inx >= NX)
         break;
      unsigned __int64 ix = p[inx];
      unsigned __int64 n = num*ix;
      if (n >= hi)
         break;
      ++nx;
      fx(inx, n);
      ++inx;
   }
   result += nx;
}
int main(int argc, char**argv)
{
   result = 0;
   fx(0, 1);
   printf("sum=%I64d\n", result+2);
   return 0;
}