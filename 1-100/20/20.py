def f(num):
    result = 1
    for i in range(1,num+1):
        result *= i
    return result


number = f(100)
sum = 0
for i in str(number):
    sum += int(i)
print sum
