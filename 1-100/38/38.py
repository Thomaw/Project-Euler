digits = set("123456789")

maxscrunch = 0

for num in xrange(10000):
	scrunch = str(num)
	times = 1
	while len(scrunch) < 9:
		times += 1
		scrunch = "".join((scrunch, str(num * times)))
	if len(scrunch) == 9 and set(scrunch) == digits:
		# print num, scrunch
		if maxscrunch < int(scrunch):
			maxscrunch = int(scrunch)

print maxscrunch

def isPandigital(num):
	nstr = str(num)
	return len(nstr) == 9 and set(nstr) == set("123456789")
