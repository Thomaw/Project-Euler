def _primefactor(n):
	d = 2
	l = []
	c = 0
	while n>1:
		if not(n%d):
			c += 1
			n /= d
			if n==1:
				l.append((d,c))
		else:
			if c>0:
				l.append((d,c))
			c = 0
			if d==2:
				d = 3
			else:
				d += 2
	return l

def _ndivs(n):
	l = _primefactor(n)
	return reduce(lambda x,y: x*y,map(lambda x:x+1,[c for (d,c) in l]))
			
def pb12(n=500):
	k = 2
	while 1:
		tmp = k*(k+1)/2
		if _ndivs(tmp)>=n:
			break
		k += 1
	return tmp
