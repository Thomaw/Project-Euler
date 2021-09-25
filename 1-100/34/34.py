import math, operator

upper = 3000000
upperPow = int(math.log10(upper))
result = []
cache = [None] * 10000

def factorial(i):
    t = 1
    while i > 1:
        t *= i
        i -= 1
    return t

# Fill the cache for 0 <= 1 < 10
for i in range(10):
    t = 0
    for d in str(i):
        t += factorial(int(d))
    cache[i] = t

# Fill the cache for 10 <= i < 10000
for i in range(1, 10):
    s = 10 * i
    for j in range(10):
        t = s + j
        u = 10 * t
        cache[t] = cache[i] + cache[j]
        if cache[t] == t:
            result.append(t)
        for k in range(10):
            v = u + k
            w = 10 * v
            cache[v] = cache[t] + cache[k]
            if cache[v] == v:
                result.append(v)
            for l in range(10):
                cache[w + l] = cache[v] + cache[l]
                if cache[w + l] == w + l:
                    result.append(w + l)

reverseCache = {}
for i in range(len(cache)):
    # Account for the leading zeros in the lower four digits (0! = 1).
    if i < 10:
        e = 3
    elif i < 100:
        e = 2
    elif i < 1000:
        e = 1
    else:
        e = 0
    d = i - cache[i] - e
    if d in reverseCache:
        reverseCache[d].append(i)
    else:
        reverseCache[d] = [i]

# Check numbers above 9999 (outside the cache).
for i in xrange(10000, upper, 10000):
    delta = i - cache[i / 10000]
    if -delta in reverseCache:
        for n in reverseCache[-delta]:
            result.append(i + n)

print reduce(operator.add, result)
