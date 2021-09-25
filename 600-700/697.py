
from scipy.special import gammainc
from math import log

L = 0
R = 10**9
n = 10 ** 7
T = 0.75

for i in range(1000):
    M = (L + R) * 0.5
    v = gammainc(n, M)
    if v < T:
        L = M
    else:
        R = M

print(L / log(10.0))