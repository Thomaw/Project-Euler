#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LIMIT 10000000
#define SOLN 20000000

int gcd(int a, int b) {
   int tmp;

again:
   if (b==0) return a;
   tmp = a%b; a=b; b=tmp;
   goto again;
}


int is_square(long long n) {
   double tmp;
   long long k;

   tmp = sqrt(n); 
   k = tmp;
   if (k*k == n) return k;
   else return -1;
}

int x[SOLN], y[SOLN], ptr=0;
int idx[LIMIT];            // For each j, find the first index i for which
                           // x[i] = j. -1 if no such index.

int OK[LIMIT+1];

// ------------------------------------------
// Three routines for sorting
// ------------------------------------------

void swap(int a, int b) {
   int tmp;

   tmp = x[a]; x[a] = x[b]; x[b] = tmp;
   tmp = y[a]; y[a] = y[b]; y[b] = tmp;
}

int partition(int first, int last, int pivot) {
   int temp, i;

   swap(pivot, last);
   temp = first;

   for(i=first; i<last; i++) 
      if (x[i] <= x[last] || (x[i] == x[last] && y[i] <= y[last])) {
         swap(temp, i);
         temp++;
      }
   swap(temp, last);
   return(temp);
}

void sort(int first, int last) {
   int index;

   if (last > first) {
      index = partition(first, last, (first+last)/2);
      sort(first, index-1);
      sort(index+1, last);
   }
}




main() {
   int j,k,l;
   int p,q,r,qp,g;
   long long tmp,p1,q1,r1;
   long long sum;

   printf("Calculating...\n");

   for(k=1;; k++) {
      if (k*k > 6*LIMIT) break;

      for(j=k+1; j<2*k; j++) {
         if (gcd(j,k)>1) continue;

         q = j*j - k*k; 
         r = j*(2*k - j);

         if (q>r) break;

         if (q % 3 == 0 && r % 3 == 0) { q/=3; r/=3;}

         for(l=1; ; l++) {
            if (l*(q+r) > LIMIT) break;
            x[ptr] = l*q; y[ptr++] = l*r;
         }
      }
   } 

   printf("Sorting...\n");
   sort(0, ptr-1);

   printf("Creating index...\n");

   for(j=0; j<LIMIT; j++) idx[j] = -1;

   for(j=0; j<ptr; j++) {
      if (idx[x[j]] == -1) 
         idx[x[j]] = j;
   }

   // Assume p<q<r. First find (p,q). Then find r.

   for(j=0; j<=LIMIT; j++) OK[j] = 0;

   for(j=0; j<ptr; j++) {
      p = x[j]; q = y[j];

      for(k=idx[q]; k<ptr; k++) {
         if (x[k] != q) break;
         r = y[k];

         p1 = p; q1 = q; r1 = r;
         tmp = p1*p1 + r1*r1 + p1*r1;
         if (is_square(tmp)>=0 && p+q+r <= LIMIT) {
            OK[p+q+r] = 1;
         }
      }

   }

   sum = 0;
   for(j=0; j<=LIMIT; j++)
      if (OK[j]) sum += j;

   printf("%lld\n", sum);
}