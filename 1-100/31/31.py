units = (200, 100, 50, 20, 10, 5, 2, 1)

def unitCount(amount = 200, index = 0, units = units):
	count = 0
	if index < len(units) - 1:
		for i in range(0, amount//units[index] + 1):
			deduct = i*units[index]
			next = index + 1
			count += unitCount(amount-deduct, next)
	
	else:
		count += 1
	return count


print unitCount(amount = 200)
