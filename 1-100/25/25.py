def _fibo():
	a,b,i = 1,1,1
	while 1:
		yield a,i
		a,b,i = b,a+b,i+1

def pb25(n=1000):
	for f,i in _fibo():
		if len(str(f))==n:
			break
	print i
