i = 1
sum = 0
while (i <= 1000):
    sum = sum + i**i
    sum = str(sum)
    sum = int(sum[-10:])
    i = i + 1
print sum
