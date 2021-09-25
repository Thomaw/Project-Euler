from itertools import takewhile, count
from fractions import gcd

def make_prime_table(N):
    a = [ True ] * (N + 1)
    for p in takewhile(lambda p: p * p <= N, (n for n in count(2) if a[n])):
        for m in xrange(p * p, N + 1, p):
            a[m] = False
    return [ n for n in xrange(2, N + 1) if a[n] ]

primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 31, 37, 41, 43,47, 61, 67, 73,83,89, 97, 107,127, \
137, 151,193,257,331, 379, 547, 661, 757, 1093, 1181, 1597, 1871, 2281,3851, 4561, \
8191, 34511, 131071, 524287, 797161, 2147483647]
primes.reverse()
lim = 10**14
c=0
okList = []
powersOf3 = []
for k in xrange(1,50):
    powersOf3 += [3**k]
print powersOf3

def checkP(n,exps):
  global c, okList, powersOf3
  lenExps = len(exps)
  if lenExps==len(primes):
    num = 1
    den = 1
    for i in xrange(0,lenExps):
      if exps[i] != 0:
        num *= primes[i] ** (exps[i] + 1) - 1
        den *= (primes[i] ** exps[i]) * (primes[i] -1)
        g = gcd(num,den)
        num /= g
        den /= g

    #print  "Exps = ",exps, " - val = ",n, " - num = ",num, " - den = ",den
    
    if den in powersOf3: 
      okList += [n]
      print len(okList), sum(okList)
    c+=1
    return
  
  p = primes[lenExps]
  power = 0
  #print "p = ",p
  while n<=lim:
    newExps = exps+[power]
    checkP(n,newExps)
    power += 1
    n *= p

checkP(1,[])
print primes
print "hits = ",c
print "result List = ",okList
print "result = ",sum(okList)