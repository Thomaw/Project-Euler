#include <iostream>
#include <NTL/lzz_p.h>
#include <NTL/lzz_pX.h>

using namespace NTL;

int main()
{
  int n = 24680;
  n -= 1;
  long mod = 1020202009;  
  int fac_n = 1;
  for (int i = 2; i <= n; i++) {
    fac_n = (long)fac_n * i % mod; 
  }
  zz_p::init(mod);
  zz_pX den;
  den.SetLength(n);
  int inv_f = InvMod(fac_n,mod);
  for (int i = n; i; i--) {
    switch (i % 4) {
      case 1: SetCoeff(den, i, mod-inv_f); break;
      case 3: SetCoeff(den, i, inv_f); break;
    }
    inv_f = (long)inv_f * i % mod;
  }
  SetCoeff(den,0, 1);
  zz_pX egf = InvTrunc(den,n+1);
  std::cout << zz_p(fac_n) * coeff(egf,n) << std::endl;
}