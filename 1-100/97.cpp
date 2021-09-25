// a^b % m
modpow(a,b,m) 
  k= smallest number that makes a^k > m
  a=a^k % m  
  return modpow(a,b/k,m)