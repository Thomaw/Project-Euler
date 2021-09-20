def fact(k, n):
	f = []
	for j in range(1, n + 1):
		f.append(k % j)
		k /= j
	return f[::-1]
