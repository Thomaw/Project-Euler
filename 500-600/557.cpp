int _tmain(int argc, _TCHAR* argv[]){
   clock_t time0 = clock();

   
   createTableOfPrimesUpTo(100000);
   int MAXAREA = 10000, ibc;
   __int64 MAXAREA2 = (__int64)MAXAREA*(__int64)MAXAREA;
   __int64 a, b, c, d, a2d, sum = 0, nSols = 0, bc, bpc, dif, s;
   for (a=1; a<MAXAREA-2; a++) {
      for (d=1; d<MAXAREA-a-1; d++) {
         a2d = a*a*d;
         findDivisors(a2d);
         for (ibc=0; ibc<nDivisors; ibc++) {
            bc = divisor[ibc];
            if (bc<=MAXAREA2) {
               bpc = (a2d/bc)-2*a-d; // b + c
               if (bpc >= 2 && bpc <= bc+1) {
                  dif = bpc*bpc-4*bc; // (b-c)^2
                  if (dif >= 0) {
                     s = (__int64)(0.5 + sqrt((double)dif));
                     b = (bpc + s)/2;
                     c = bpc - b;
                     if (c > 0 && b*c == bc && a+b+c+d <= MAXAREA) {
                        // solution found
                        nSols ++;
                        if ((nSols&1023)==0) cout << a << " " << b << " " << c << " " << d << "  " << a+b+c+d << "\n";
                        sum += a+b+c+d;
                     }
                  }
               }
            }
         }
      }
   }
   cout << "sum = " << sum << "\n";
   

   cout << "time spent = " << clock() - time0 << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); 
   return 0;
}