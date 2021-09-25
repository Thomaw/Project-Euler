#include <time.h>             /* clock, CLK_TCK */
#include <stdio.h>            /* printf */
#include <conio.h>            /* getch */
#include <math.h>             /* sqrt, floor */

int A[1001];

int gcd(int a, int b)
{
  if ((a % b) == 0)
    return b;
  else
    return gcd(b, a % b);
}

void reduce(int *a, int *b)
{
  long g;
  g = gcd(*a,*b);
  *a /= g;
  *b /= g;
}

int main(void)
{
  clock_t start, ends;
  double t;
  long psum = 0;
  int found = 0;
  int i, j, k, n;
  int tmp, zn, den, num;
  double z;
  printf("\n*******************************");
  printf("\n* Project Euler - Problem 64  *");
  printf("\n*                             *");
  printf("\n* Answer: 1322                *");
  printf("\n*******************************");
  start = clock();
  for (i=1;i<=10000;i++){
    z = sqrt(i);
    if (z == floor(z)) continue;
    k = 0;
    A[0] = (int) sqrt(i);
    num = -A[0];
    den = -num;
    num = i-num*num;
    zn = 1;
    found = 0;
    while (!found){
      z = (double) (zn*(A[0]+den)/num);
      j = (int) z;
      k++;
      found = (2*A[0] == j);
      A[k] = j;
      if (found) break;
      den = den-A[k]*num;
      tmp = den;
      den = num;
      num = tmp;
      zn = den;
      den = -num;
      num = i-num*num;
      reduce(&zn,&num);
    }
    if ((k % 2) != 0) psum++;
  }
  ends = clock();
  t = (double) (ends-start)/CLK_TCK;
  printf("\n\nAnswer is %ld, found in %lf second(s) ",psum,t);
  getch();
  return 0;
}
