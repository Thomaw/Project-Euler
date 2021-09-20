import math
import time
def sOD(x):
  s = 1
  for i in range(2, int(math.sqrt(x)) + 1):
    if (x % i == 0):
      s += i
      if i != x/i: s += x / i
  return s

t=time.time()
s=0
x=[]
for n in range(1,28124):
    if sOD(n) > n:
        x.append(n)
print len(x), time.time()-t
t=time.time()
for n in range(1,30000):
    i=0
    a=0
    s+=n
    while x[i]*2 <= n:
        if n-x[i] in x:
            a=1
            s-=n
            break
        i+=1
    if n % 100 == 0: print 'cur:', n, s, time.time()-t
print "Done:", s, time.time()-t
