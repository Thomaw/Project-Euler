rs = [306]
for _ in range(10**5):
    rs.append((rs[-1]**2)%10007)

K = 500
M = 10

ps = [0] * K
for t in range(200):
    nps = [0] * K
    for i in range(K):
        for j in range(M):
            q = rs[i*M+j]%5
            if q == 0:
                nps[i] += 1.
            elif q == 1:
                nps[i] += ps[i] ** 2
            elif q == 2:
                nps[i] += ps[(2*i)%K]
            elif q == 3:
                nps[i] += ps[(i*i+1)%K] ** 3
            elif q == 4:
                nps[i] += ps[i] * ps[(i+1)%K]
        nps[i] /= M
    ps = nps
print(ps[0])