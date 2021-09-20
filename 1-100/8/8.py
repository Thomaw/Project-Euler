a="long number here"

l = [int(a[0]), int(a[1]), int(a[2]), int(a[3]), int(a[4]), int(a[5])]
i = 0
T = 5

max = l[0]*l[1]*l[2]*l[3]*l[4]

for j in range(5, 1000):
    l[i] = int(a[j])
    i = (i+1)%T

    p = l[0]*l[1]*l[2]*l[3]*l[4]
    if p > max:
        max = p
