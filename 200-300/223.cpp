nmax = 25 * 10 ** 6

m = [[[-2, 1, 2], [-1, 2, 2], [-2, 2, 3]],
     [[2, 1, 2], [1, 2, 2], [2, 2, 3]],
     [[1, -2, 2], [2, -1, 2], [2, -2, 3]]]

s = [[1, 1, 1], [1, 2, 2]]
c = 0

while True:
    t = []
    c += len(s)
    for a in s:
        for mm in m if a[0] < a[1] else m[1:]:
            b = [sum(mm[i][j] * a[j] for j in range(3)) for i in range(3)]
            if sum(b) <= nmax:
                t.append(b)
    if not t:
        break
    s = t

print(c)