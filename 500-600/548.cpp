
#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include "math.h"
#include <time.h>
#include <vector>
using namespace std;

// Euler problem 548
#define GMAX 10000000000000000L

// array of primes
int * prime = NULL;

// An array of dimensions [54][21][11][7][5][4][3][3][2][2][2][2][2]
// would be too large; so...
__int64 ************* G;

// list of values of g to analyze later to see whether x=g(x)
vector<__int64> valuesToAnalyze;

// inclusion-exclusion arrays
int pow2[14];
int exp_i_e[13];
int twoSignArray[8192]; // 8192 = 2^13

// Create an array of dimension nDims able to store multiples of
// product. Since many of the allocations are tiny, instead of
// calling new, use working arrays, "FORTRAN style".
// Allocate work64 and workPtr once, then get chunks of them
// using used64 and usedPtr to keep track of the unused parts.
int nAllocations = 0;
__int64 * work64 = new __int64[500000];
__int64 ** workPtr = new __int64*[500000];
int used64 = 0;
int usedPtr = 0;
void* createGArray(int nDims, __int64 product, int maxDim) {
   // This function generates a subtree to hold exponents.
   // nDims is the number of dimensions the resulitng arrays must have.
   // product is the smallest number that could be mapped into cells
   // of this subtree.
   // maxDim indicates the smallest maximum exponent that has appeared
   // before. For instace, if we are computing G[6][3][1][0], all
   // dimensions must be 0, because exponents are stored decreasingly, 
   // and the fourth exponent must already be 0.
   if (nDims == 1) {
      nAllocations++;
      // old version with allocations: __int64 * retVal = new __int64[maxDim];
      __int64 * retVal = work64 + used64;
      used64 += maxDim;
      for (int i=0; i<maxDim; i++) retVal[i] = 0; // initialize to 0!
      return retVal;
   }
   int dpa = 1; // dimension of pointer array
   __int64 p = product;
   while (p*prime[13-nDims] < GMAX) {
      p = p*prime[13-nDims];
      dpa++;
   }
   dpa = min(dpa, maxDim);
   nAllocations++;
   // old version with allocations: __int64** retVal = new __int64*[dpa];
   void** retVal = (void**)(workPtr + usedPtr);
   usedPtr += dpa;
   p = product;
   for (int i=0; i<dpa; i++) {
      retVal[i] = createGArray(nDims-1, p, i+1);
      p = p * prime[13-nDims];
   }
   return retVal;
}


// would be arguments to recursive function explore();
int n;
int expArray[13];
__int64 product;

int NPRIMES;
void createTableOfPrimesUpTo(int n) {
   // First part: sieve
   char * primeSieve = new char[n+1];
   primeSieve[0] = primeSieve[1] = 0;
   int i, mult;
   for (i=2; i<=n; i++) primeSieve[i] = 1;
   for (i=2; i*i<=n; i++) {
      if (primeSieve[i]==1) {
         mult = i*i;
         while (mult<=n) {
            primeSieve[mult] = 0;
            mult+=i;
         }
      }
   }
   // second part: create table with primes
   NPRIMES = 0;
   for (i=2; i<=n; i++) {
      if (primeSieve[i]==1) NPRIMES++;
   }
   prime = new int[NPRIMES];
   NPRIMES = 0;
   for (i=2; i<=n; i++) {
      if (primeSieve[i]==1) {
         prime[NPRIMES++] = i;
      }
   }
   delete[] primeSieve;
   cout << "prime[" << NPRIMES-1 << "] = " << prime[NPRIMES-1] << "\n";
}


int fact_n; __int64 *fact_p=new __int64[60]; int *fact_e=new int[60];
void factorize(__int64 n) {
   int ipr = 0, pr = 2;
   fact_n = 0;
   while (n >= (__int64)pr*pr) {
      if (n%pr==0) {
         fact_p[fact_n] = pr;
         fact_e[fact_n] = 0; 
         do {
            fact_e[fact_n]++;
            n = n/pr;
         } while (n%pr==0);
         fact_n++;
      }
      ipr++;
      pr = prime[ipr];
   }
   if (n>1) {
      fact_p[fact_n] = n;
      fact_e[fact_n] = 1;
      fact_n++;
   }
}


__int64 getGfromTable(int * ea) {
   int i, itemp;

   // sort ea decreasingly
   bool changes;
   int nIts = 1;
   do {
      changes = false;
      for (i=0; i<n-nIts; i++) {
         if (ea[i]<ea[i+1]) {
            itemp = ea[i]; ea[i] = ea[i+1]; ea[i+1] = itemp;
            changes = true;
         }
      }
      nIts++;
   } while (changes);

   return G[ea[0]][ea[1]][ea[2]][ea[3]][ea[4]][ea[5]][ea[6]][ea[7]][ea[8]][ea[9]][ea[10]][ea[11]][ea[12]];
}


// evaluate at expArray
__int64 evaluateg() {
   __int64 sum = 0;
   int i, j;

   // inclusion-exclusion evaluation
   for (i=1; i<pow2[n]; i++) {
      for (j=0; j<n; j++) {
         if (i & pow2[j]) {
            exp_i_e[j] = expArray[j]-1;
         }else{
            exp_i_e[j] = expArray[j];
         }
      }
      sum = sum + twoSignArray[i]*getGfromTable(exp_i_e); // this call overwrites exp_i_e
   }

   // Take into account term for x=1
   bool account = true;
   for (i=0; i<n; i++) {
      if (expArray[i] != 1) {
         account = false;
         break;
      }
   }
   if (account) {
      sum = sum + 1 - 2*(n&1); // add 1 if n even, subtract 1 if n odd
   }

   for (i=0; i<n; i++) exp_i_e[i] = 0; // reset for next call
   valuesToAnalyze.push_back(sum);
   return sum;
}


void explore() {
   __int64 gval, product0;

   // product check
   //__int64 pr = 1;
   //for (int i=0; i<13; i++) {
   //   for (int j=0; j<expArray[i]; j++) {
   //      pr = pr * prime[i];
   //   }
   //}
   //if (pr != product) {
   //   throw "error";
   //}

   // calculate the value of g at this point
   gval = evaluateg();

   /*
   cout << "explore(";
   for (i=0; i<n; i++) {
      cout << expArray[i];
      if (i!=n-1) cout << " ";
   }
   cout << "         >= " << product << ")        = " << gval << ")\n";
   */

   // store value in table of g values
   G[expArray[0]][expArray[1]][expArray[2]][expArray[3]][expArray[4]][expArray[5]][expArray[6]]
    [expArray[7]][expArray[8]][expArray[9]][expArray[10]][expArray[11]][expArray[12]] = gval;

   if (gval > GMAX) return;

   // Keep exploring.
   // Add new exponent?
   product0 = product;
   if (n<13 && (product = product*prime[n]) < GMAX) {
      expArray[n] = 1;
      n++;
      explore();
      n--;
      expArray[n] = 0;
   }
   // Increase exponent n?
   if ((n==1 || expArray[n-1] < expArray[n-2]) && (product = product0*prime[n-1]) < GMAX) {
      expArray[n-1]++;
      explore();
      expArray[n-1]--;
   }
   product = product0;
}


int _tmain(int argc, _TCHAR* argv[]){
   clock_t time0 = clock();
   int i, j, sign;

   createTableOfPrimesUpTo(100);
   //cout << "time spent primes = " << clock() - time0 << " ms\n"; 

   pow2[0] = 1;
   for (i=1; i<14; i++) pow2[i] = 2*pow2[i-1];
   for (i=0; i<8192; i++) {
      sign = -2;
      for (j=0; j<13; j++) {
         if (i & pow2[j]) {
            sign = -sign;
         }
      }
      twoSignArray[i] = sign;
   }

   // initialization of G
   G = (__int64*************)createGArray(13, 1, 100); // 13 exponents, product 1, biggest exponent 100
   G[0][0][0][0][0][0][0][0][0][0][0][0][0] = 1;
   //cout << "time spent init G = " << clock() - time0 << " ms\n"; 

   // start at exponents 1,0,0,0,0,0,0,0,0,0,0,0,0 (product = 2)
   n = 1;
   expArray[0] = 1;
   for (i = 1; i<13; i++) {
      expArray[i] = 0;
      exp_i_e[i] = 0;
   }
   product = 2;
   explore();

   //cout << "time spent explore = " << clock() - time0 << " ms\n"; 
   __int64 sumSols = 0;
   
   for (i=0; i<(int)valuesToAnalyze.size(); i++) {
      __int64 valg = valuesToAnalyze[i];
      if (valg < GMAX) {
         factorize(valg);
         for (j=fact_n; j<13; j++) fact_e[j] = 0; // reset exponents of factorization to 0
         n = fact_n;
         __int64 gval = getGfromTable(fact_e);
         if (gval == valg) {
            //cout << "sol found: " << gval << "\n";
            sumSols = sumSols + gval;
         }
      }
   }
   //cout << "nAllocations = " << nAllocations << "\n";
   cout << "final value = " << sumSols << "\n";
   cout << "time spent = " << clock() - time0 << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); 
   return 0;
}