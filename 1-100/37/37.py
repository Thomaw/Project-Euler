from math import sqrt

# List of primes:
primes = [2, 3, 5, 7]
# Truncatable primes from left and right:
t_primes = []
# Number of primes truncatable from left and right:
limit = 11

def isprime(n):
	if n < 2:
		return False
	for i in primes:
		if i > sqrt(n):
			break
		if n % i == 0:
			return False
	primes.append(n)
	return True

def istruncatable(n):
	if isrtruncatable(n/10):
		if isltruncatable(int(str(n)[1:len(str(n))])):
			return True
	return False

def isltruncatable(n):
	candidates = [n]
	strn = str(n)
	lenn = len(strn)
	for x in range(1, int(len(str(n)))):
		candidates.append(int(strn[x:lenn]))
	
	for y in candidates:
		if isprime(y) == False:
			return False
	
	return True

def isrtruncatable(n):
	candidates = [n]
	for x in range(1, int(len(str(n)))):
		candidates.append(n/(10**x))
		
	for y in candidates:
		if isprime(y) == False:
			return False
	
	return True

def main():
	candidate = primes[-1] + 2
	sum = 0
	
	while len(t_primes) < limit:
		if isprime(candidate):
			if istruncatable(candidate):
				t_primes.append(candidate)

		candidate += 2
	
	for x in t_primes:
		sum += x
		
	print sum

if __name__ == "__main__":
	main()
