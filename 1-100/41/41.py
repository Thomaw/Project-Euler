def gen_pandigital(digits=9):
	"""generates pandigital numbers starting with the biggest"""
	
	def generator(start, digits_left):
		if len(digits_left) == 1:
			yield int(start + digits_left[0])
		else:
			for i in digits_left:
				for p in generator(start + i, filter(lambda x: x != i, digits_left)):
					yield p

	digits = [str(i) for i in range(digits,0,-1)]
	for i in generator("",digits):
		yield i

def prime_check(maxnum):
	"""Returns a function that checks if a number < maxnum is prime"""
	bucket = range(int(math.sqrt(maxnum)) + 1)
	bucket[1] = 0
	for i in bucket:
		if i <> 0:
			for not_prime in xrange(2*i, int(math.sqrt(maxnum)) +1, i):
				bucket[not_prime] = 0
	bucket = filter(lambda x: x <> 0, bucket)
	
	def isPrime(num):
		for i in bucket:
			if num % i == 0:
				return False
			if i > math.sqrt(num):
				return True
		return True

	return isPrime

def problem_41():
	isPrime = prime_check(7654321)
	for i in gen_pandigital(7):
		if isPrime(i):
			return i
