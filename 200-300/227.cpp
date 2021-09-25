# import psyco
# psyco.full()

NP = 100

def makeClean():
    res = []
    for i in xrange(NP):
        res.append(0.)
    return res

def prev(x):
    return (x + NP - 1) % NP

def next(x):
    return (x + 1) % NP

def iterate1(sec):
    for x, p in sec:
        yield (prev(x), p*1./6)
        yield (next(x), p*1./6)
        yield (x, p*2./3)

def iterate(matrix):
    res = makeClean()
    for i in xrange(NP):
        for x, p in iterate1(iterate1([(i, matrix[i])])):
            res[x] += p
    return res

result = 0
matrix = makeClean()
matrix[NP / 2] = 1.
move = 0
for i in xrange(100000):
    if 0 == i % 1000:
        print i
    matrix = iterate(matrix)
    move += 1
    result += matrix[0]*move
    matrix[0] = 0

print result, sum(matrix)