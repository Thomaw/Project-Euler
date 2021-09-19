def calcE():
	x = y = 1
	sum = 0
	while (sum < 1000000):
		sum += (x + y)
		x, y = x + 2 * y, 2 * x + 3 * y
	return sum
