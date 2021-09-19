from math import acos, sqrt, pi

def prod(a,b):
    return sum(a[i]*b[i] for i in range(2))

def gamma(a,b):
    return acos( prod(a,b)/sqrt( prod(a,a)*prod(b,b) ) )

s=0
for li in file('102.dat'):
    dat=map(int, li.split(','))
    a=dat[0:2]
    b=dat[2:4]
    c=dat[4:6]
    if gamma(a,b)+gamma(b,c)+gamma(c,a) > 2*pi-1E-10:
        s += 1
print s
