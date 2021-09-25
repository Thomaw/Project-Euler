#include <stdio.h>
#include <stdlib.h>

#define PUSH(A,B,C,D) if (depth < alloc_depth) {                        \
  abcd[depth].a=A; abcd[depth].b=B; abcd[depth].c=C; abcd[depth++].d=D; }
  
typedef struct { double a, b, c, d; } abcd_t;

static void count(int qmax, int recip) {
  int alloc_depth = qmax/2/recip/recip + 100;
  int depth = 0, max_depth = 0;
  int ct = (qmax-recip)/2;   /* 1/2q for 2q=recip+1,...,qmax */
  
  abcd_t *abcd = malloc(alloc_depth*sizeof(abcd_t));
  if (!abcd) { perror("malloc"); exit(1); }
  
  PUSH(0,1,1,1)
  
  while (--depth >= 0) {
    double a=abcd[depth].a, b=abcd[depth].b, c=abcd[depth].c, d=abcd[depth].d;
    double u = a*d + b*c;
    double v = 2*b*d;

    if (v <= qmax) {
      if (0<a && u*recip<v) { ct++; if (depth > max_depth) max_depth = depth; }
      PUSH(a,b,a+c,b+d)
      PUSH(a+c,b+d,c,d)
    }
  }
  
  printf("qmax = %8d : count = %7d",qmax,ct);
  printf(" : max depth = %3d (allocated %3d)\n",max_depth,alloc_depth);
  
  free(abcd);
  
  return;
}

int main(void) {
  
  count( 10000000, 100 );
  
  return 0;
}