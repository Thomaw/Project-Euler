# r(a, b) = b * (a - 2b) / (a - b) = b (1 - 1/x)
# where x = a/b - 1
# G(n) = sum(b*(n-2b)) for b from 1 to n/2 -
#    Integral { from 1 to n/2 } b^2 log (n/b - 1) db

from math import log

N = 10  # Answer: 20.59722222
N = 100  # Answer: 19223.60980
N = 10**11  # Answer: 1.895093981e31

def G(n):
    n2 = n//2
    s = n*n2*(n2+1)//2 - n2*(n2+1)*(n+1)//3
    s -= ((n**3 - 1)*log(n-1) - n**3*log(n2) - 15*n**3/24 + n2 + n**2)/3
    return s

s = str(G(N))
e = s.find("e+")
print(s[:11] + "e" + s [e+2:])  # 1.895093981e31