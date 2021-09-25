import heapq

primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43]

def power(x, y):
	p = 0
	while 0 == x % y:
		x /= y
		p += 1
	return p

def factors(x):
	return map(lambda y: power(x, y), primes)

def mono(arr):
	i = 1
	while (i < len(arr)) and (arr[i - 1] >= arr[i]):
		i += 1
	return i == len(arr)

def gen():
	h = [1]
	was = set()
	while True:
		top = heapq.heappop(h)
		yield top
		# print top
		for p in primes:
			next = p*top
			if (not next in was) and mono(factors(next)):
				was.add(next)
				heapq.heappush(h, next)	

def dCount(x):
	return (reduce(lambda x, y: x*(2*y + 1), factors(x), 1) + 1) / 2

maxcount = 0
i = 0
for n in gen():
	i += 1
	count = dCount(n)
	if count > maxcount:
		print i, n, factors(n), count
		maxcount = count
	if count > 4000000:
		break