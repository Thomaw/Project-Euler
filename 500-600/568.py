def euler568(n=123456789):
  from numpy import euler_gamma
  from math import log, log10
  res = log10(euler_gamma + log(n) + 0.5/n) - n*log10(2)
  res += 7 - int(res)
  return int(10**res)