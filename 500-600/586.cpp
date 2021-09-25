def is_neutral(n, l):
    for v in l:
        while n % v == 0: n /= v
        if n < v: return n == 1
    return n == 1

def count(n, e, Q=1, i=0):
    global generators, complementors

    if len(e) == 0: return bisect(complementors, n / Q)
    if i == len(generators): return 0
    s = sum(e)
    p = generators[i]
    f = Q * p**e[0]
    cnt = 0
    while f <= n:
        c = count(n, e[1:], f, i+1)
        if c == 0: break
        cnt += c
        i += 1
        if i == len(generators): break
        p = generators[i]
        f = Q * p**e[0]
    return cnt

def count5(n):
    global generators, complementors

    cnt = 0
    L = len(generators)
    for i in range(L-4):
        f1 = generators[i] ** 4
        for j in range(L-3):
            if j == i: continue
            f2 = f1 * generators[j]
            if f2 > N: break
            for k in range(j+1, L-2):
                if k == i: continue
                f3 = f2 * generators[k]
                if f3 > N: break
                for l in range(k+1, L-1):
                    if l == i: continue
                    f4 = f3 * generators[l]
                    if f4 > N: break
                    for m in range(l+1, L):
                        if m == i: continue
                        f5 = f4 * generators[m]
                        if f5 > N: break
                        cnt += bisect(complementors, n / f5)
    return cnt

patterns = ( 11**4 * 19**3 * 29**3,		#     4,3,3
	     11**7 * 19**4 * 29,		#     7,4,1
	     11**8 * 19**2 * 29**2,		#     8,2,2
	     11**9 * 19**3 * 29,		#     9,3,1
	     11**2 * 19**2 * 29**2 * 31**2,	#   2,2,2,2
	     11**4 * 19**3 * 29    * 31,	#   4,3,1,1
	     11**9 * 19    * 29    * 31,	#   9,1,1,1
	     11**4 * 19    * 29    * 31 * 41 )	# 4,1,1,1,1  (81490227)

N = 10**15
a = max (int( (N / (11**4 * 19**3)) ** 1/3.0 ), int( N / (11**7 * 19**4) ),
	 int( (N / (11**8 * 19**2)) ** 0.5 ), int( N / (11**9 * 19**3) ),
	 int( (N / (11**2 * 19**2  * 29**2)) ** 0.5 ), int( N / (11**4 * 19**3 * 29) ),
	 int( N / (11**9 * 19 * 29) ), int( N / (11**4 * 19 * 29 * 31) ) )

b = min(patterns)
primes = sieve(a+1)
generators = filter(lambda p: p % 10 == 1 or p % 10 == 9, primes)
l = filter(lambda p: p % 10 != 1 and p % 10 != 9, sieve(int(sqrt(N / b))))
l = map(lambda v: v*v, l)
l[l.index(25)] = 5
l.sort()
complementors = filter(lambda v: is_neutral(v,l), range(1, N / b + 1))


cnt = 0
for s in ( (4,3,3), (7,4,1), (8,2,2), (9,3,1), (2,2,2,2), (4,3,1,1), (9,1,1,1) ):
    for e in unique_permutations(s):
        r = count(N, e)
        if r == 0: break
        cnt += r
        print e, r, cnt

cnt += count5(N)

print cnt