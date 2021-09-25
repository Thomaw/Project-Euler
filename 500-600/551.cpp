cache = {}

def f(m,n,seq):
 if (n, seq) in cache:
  ans = cache[(n, seq)]
  if ans[0] <= m:
   return (m-ans[0],ans[1],ans[2])
 if len(seq) == 1:
  steps = 0
  j = seq[0]
  while j < 10 and steps < m:
   j = 2 * j + n
   steps += 1
  if j >= 10:
   cache[(n,seq)] = (steps, (j / 10), (j % 10,))
  return (m-steps, (j / 10), (j % 10,))
 else:
  steps = 0
  j = seq[0]
  v = tuple(t for t in seq[1:])
  while j < 10 and steps < m:
   (x,y,v) = f(m - steps, n + j, v)
   steps += m - steps - x
   j += y
  if j >= 10:
   cache[(n,seq)] = (steps, (j / 10), (j % 10,) + v)
  return (m - steps, (j / 10), (j % 10,) + v)

def g(r):
 h = (1,)
 while True:
  (a,b,c) = f(r,0,h)
  if a == 0:
   break
  h = (0,)+h
 return c

j = 9
while j <= 999999999999999:
 print "g(%d)=%s" % (j, "".join(str(k) for k in g(j)))
 j = 10 * j + 9