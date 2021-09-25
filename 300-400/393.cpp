// Euler.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include "math.h"
#include <time.h>
using namespace std;

// PROBLEM 393
#define CLOSED 0
#define ENTERS 1
#define EXITS  2

int _tmain(int argc, _TCHAR* argv[])
{
   clock_t time = clock();

   int n = 10; // n must be <= 10
   int i, j, c[4], row, column, newSol, doorUp, doorDown, doorRight, doorLeft, maskAbove, oldSol;
   __int64 * oldWall = new __int64[4194304];
   __int64 * newWall = new __int64[4194304];
   int maskUp  [11] = {3, 12, 48, 192, 768, 3072, 12288, 49152, 196608, 786432, 3145728};
   int pow4    [11] = {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576};
   int maskNine[11];

   // make a list with the 3^11 valid masks
   int * validMask = new int[177147], nValidMasks = 0, indexNewSol;
   for (i=0; i<4194304; i++) {
      if (((i&3)!=3) && ((i&12)!=12) && ((i&48)!=48) && ((i&192)!=192) && ((i&768)!=768) && ((i&3072)!=3072) && ((i&12288)!=12288)
         && ((i&49152)!=49152) && ((i&196608)!=196608) && ((i&786432)!=786432) && ((i&3145728)!=3145728)) {
         validMask[nValidMasks++] = i;
      }
   }
   for (i=0; i<4194304; i++) { oldWall[i] = 0; newWall[i] = 0; }
   for (i=0; i<10; i++) maskNine[i] = 1048575 - maskUp[i];

   oldWall[0] = 1;
   for (row=0; row<n; row++) {
      for (column=0; column<n; column++) {
         // cout << "row=" << row << ", column=" << column << "\n";
         for (indexNewSol = 0; indexNewSol<177147; indexNewSol++) {
            newSol = validMask[indexNewSol];
            maskAbove =  newSol & maskNine[column];
            doorRight = (newSol & maskUp  [10]    ) >> 20;
            doorDown  = (newSol & maskUp  [column]) >> (2*column);
            for (doorUp=0; doorUp<3; doorUp++) {
               for (doorLeft=0; doorLeft<3; doorLeft++) {
                  c[0] = 0; c[1] = 0; c[2] = 0;
                  c[doorUp]++; c[doorDown]++; c[doorRight]++; c[doorLeft]++;
                  if (c[CLOSED]==2 && c[ENTERS]==1 && c[EXITS]==1) {
                     oldSol = maskAbove + pow4[column]*doorUp+ pow4[10]*doorLeft;
                     newWall[newSol] += oldWall[oldSol];
                  }
               }
            }
         }
         for (i=0; i<177147; i++) { j = validMask[i]; oldWall[i] = newWall[i]; newWall[i] = 0; }
      }
      for (i=59049; i<118098; i++) oldWall[validMask[i]] = 0;
   }
   cout << "nSols = " << oldWall[0] << "\n";
   delete[] oldWall;
   delete[] newWall;
   delete[] validMask;

   time = clock() - time; cout << "time spent = " << time << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); return 0;
}