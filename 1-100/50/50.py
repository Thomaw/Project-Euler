import euler,time
from euler import prime
ti = time.time()
def nextprime(n):
    '''finds the next prime after n, given primes, the set of primes'''
    x = n+1
    while True:
        if prime(x): return(x)
        else: x += 1       
primes = [0] + euler.sieve(1000)
best = 21,953
while True:    
    del primes[0]     
    s = sum(primes)
    while True:
        if s >= 10**6: break
        else:
            n = nextprime(primes[-1])
            s += n
            primes += [n]
    s = sum(primes[:best[0]+1])
    if s >= 10**6: break        
    for n in range(len(primes) - 1,best[0] + 1,-1):
        s = sum(primes[0:n])
        if prime(s):
            best = n,s
            break
print best,time.time() - ti   
