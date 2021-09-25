#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "math.h"
#include <time.h>
using namespace std;

// PROBLEM 439
const __int64 N     = 100000000000L;
const   int   MOD   = 1000000000;
const   int   MOD2  = MOD*2;  // When computing x*(x+1)/2 % MOD , we need x % (2*MOD).
// S(  100) =            57 316768
// S( 1000) =        563576 517282
// S(10000) =   5628 614363 174016 


int _tmain(int argc, _TCHAR* argv[]){
   clock_t time0 = clock();

   const   int   sqrtN   = (int)(1.0 + sqrt(double(N))); // sqrtN > sqrt(N)
   const __int64 sqrtN64 = sqrtN;
   int i, sn, inv;
   int * S    = new int[sqrtN+1];
   int * Sinv = new int[sqrtN+1];
   __int64 n, sumd, sumS, sumi, ni, low_limit_i, up__limit_i, low_limit_i_mod, up__limit_i_mod, uml;

   cout << "Computing d(n), S(n) for n<sqrt(N)...\n";
   S[0] = 0; // It's used once before being set
   for (n=1; n<=sqrtN64; n++) {
      if ((n&16383)==0) cout << "n=" << n << "\n";

      sn = (int)(1.5+sqrt(double(n)));

      sumd = n; // term for i=1
      sumS = 0; // no term for i=1
      for (i=2; i<=sn; i++) {
         sumd = ( sumd + i*          (n/i) ); // Small enough that no mod is required
         sumS = ( sumS - i*(__int64)S[n/i] ); // Small enough that no mod is required
      }
      sumd = sumd % MOD;
      sumS = sumS % MOD;

      // ni is floor(n/i)
      // Loop without optimizations (see explanation below)
      /*
      for (ni=sn; ni>=1; ni--) {
         low_limit_i = n/(ni+1)+1;
         up__limit_i = n/ni;
         if (low_limit_i<=sn) {
            low_limit_i = sn+1; // In the previous loop we added on i up to sn
            if (up__limit_i<=sn) {
               up__limit_i = low_limit_i-1;
            }
         }
         if (up__limit_i >= low_limit_i) {
            uml  = (up__limit_i-low_limit_i) %MOD2;
            sumi = ((uml+1)*(low_limit_i%MOD) + (uml)*(uml+1)/2) %MOD;
            sumd = ( sumd + sumi * ni  ) %MOD;
            sumS = ( sumS - sumi*S[ni] ) %MOD;
         }
      }
      */

      // Initialization loop: without optimizations, until we know we can avoid checks
      for (ni=sn; ni>=1; ni--) {
         low_limit_i = n/(ni+1)+1;
         up__limit_i = n/ni;
         if (low_limit_i<=sn) {
            low_limit_i = sn+1; // In the previous loop we added on i up to sn
            if (up__limit_i<=sn) {
               up__limit_i = low_limit_i-1;
            }
         }else{
            break; // At this point we know we don't have to check any more
         }
         if (up__limit_i >= low_limit_i) {
            uml  = (up__limit_i-low_limit_i) %MOD2;
            sumi = ( (uml+1)*(low_limit_i%MOD) + (uml)*(uml+1)/2 )%MOD;
            sumd = ( sumd + sumi *   ni  )%MOD;
            sumS = ( sumS - sumi * S[ni] )%MOD;
         }
      }

      // "production" loop with optimizations
      up__limit_i     = low_limit_i - 1;
      up__limit_i_mod = up__limit_i % MOD2;
      for (; ni>=1; ni--) { // continue with same value of ni as exited from previous loop
         low_limit_i     = up__limit_i     + 1;
         low_limit_i_mod = up__limit_i_mod + 1;
         up__limit_i     = n/ni;
         up__limit_i_mod = up__limit_i % MOD2;
         uml  = up__limit_i_mod - low_limit_i_mod;
         sumi = ( (uml+1)*(low_limit_i_mod) + (uml)*(uml+1)/2 )%MOD;
         sumd = ( sumd + sumi *   ni  )%MOD;
         sumS = ( sumS - sumi * S[ni] )%MOD;
      }

      S[n] = (int) ((sumd*sumd + sumS) %MOD);

   }

   cout << "Computing d(n), S(n) for n>sqrt(N)...\n";
   for (inv=sqrtN; inv>=1; inv--) {
      // Compute d(floor(N/inv)) and S(floor[N/inv])

      if ((inv&16383)==0) cout << "inv=" << inv << "\n";

      n = N/(__int64)inv;
      sn = (int)(1.5+sqrt(double(n)));

      sumd = n;
      sumS = 0;
      for (i=2; i<=sn; i++) {
         sumd = ( sumd + i* (n/i) )%MOD;
         if (i*inv<=sqrtN) { // i and inv are integer; i*inv <= sn*inv = sqrt(n)*inv = sqrt(N/inv)*inv = sqrt(N*inv) < sqrt(N*sqrt(N)) < 177 milion
            sumS = ( sumS - i*(__int64)Sinv[i*inv] )%MOD;
         }else{
            sumS = ( sumS - i*(__int64)S[n/i] )%MOD;
         }
      }

      /*
      // The following non-optimized loop can be improved by saving on checks and
      // "recycling" the upper limit of one iteration to the lower limit of the next.
      // ni is floor(n/i)
      for (ni=sn; ni>=1; ni--) {
         low_limit_i = n/(ni+1)+1;
         up__limit_i = n/ni;
         if (low_limit_i<=sn) {
            low_limit_i = sn+1; // In the previous loop we added on i up to sn
            if (up__limit_i<=sn) {
               up__limit_i = low_limit_i-1;
            }
         }
         if (up__limit_i >= low_limit_i) {
            uml  = (up__limit_i-low_limit_i) %MOD2;
            sumi = ( (uml+1)*(low_limit_i%MOD) + (uml)*(uml+1)/2 )%MOD;
            sumd = ( sumd + sumi * ni )%MOD;
            if (ni<=sqrtN64) {
               sumS = ( sumS - sumi*S[ni] )%MOD;
            }else{
               sumS = ( sumS - sumi*Sinv[ni] )%MOD;
            }
         }
      }
      */

      // Initialization loop: without optimizations, until we know we can avoid checks
      for (ni=sn; ni>=1; ni--) {
         low_limit_i = n/(ni+1)+1;
         up__limit_i = n/ni;
         if (low_limit_i<=sn) {
            low_limit_i = sn+1; // In the previous loop we added on i up to sn
            if (up__limit_i<=sn) {
               up__limit_i = low_limit_i-1;
            }
         }else{
            break; // At this point we know we don't have to check any more
         }
         if (up__limit_i >= low_limit_i) {
            uml  = (up__limit_i-low_limit_i) %MOD2;
            sumi = ( (uml+1)*(low_limit_i%MOD) + (uml)*(uml+1)/2 )%MOD;
            sumd = ( sumd + sumi * ni )%MOD;
            if (ni<=sqrtN64) {
               sumS = ( sumS - sumi*S[ni] )%MOD;
            }else{
               sumS = ( sumS - sumi*Sinv[ni] )%MOD;
            }
         }
      }

      // "production" loop with optimizations
      up__limit_i     = low_limit_i - 1;
      up__limit_i_mod = up__limit_i % MOD2;
      for (; ni>=1; ni--) { // continue with same value of ni as exited from previous loop
         low_limit_i     = up__limit_i     + 1;
         low_limit_i_mod = up__limit_i_mod + 1;
         up__limit_i     = n/ni;
         up__limit_i_mod = up__limit_i % MOD2;
         uml  = up__limit_i_mod - low_limit_i_mod;
         sumi = ( (uml+1)*(low_limit_i_mod) + (uml)*(uml+1)/2 )%MOD;
         sumd = ( sumd + sumi * ni )%MOD;
         if (ni<=sqrtN64) {
            sumS = ( sumS - sumi*S[ni] )%MOD;
         }else{
            sumS = ( sumS - sumi*Sinv[ni] )%MOD;
         }
      }

      Sinv[inv] = (int) (( sumd*sumd + sumS )%MOD);
   }

   cout << "S(" << N << ") = " << Sinv[1] << "\n";
   cout << "N     = " << N     << "\n";
   cout << "MOD   = " << MOD   << "\n";
   cout << "sqrtN = " << sqrtN << "\n";
   cout << "time spent = " << clock() - time0 << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); return 0;
}