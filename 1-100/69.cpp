def totients(nmax):
	ts=range(nmax)
	for i in xrange(2,nmax):
		if ts[i]==i: #Prime, as it hasn't been divided by anything lower.
			ts[i]-=1 #Primes are coprime to everything below them.
			#Factor i into the totients of its multiples.
			for j in xrange(i+i,nmax,i):
				ts[j] = (ts[j]*(i-1))//i
	return ts
from itertools import imap
def p69(nmax):
	tots=totients(nmax)
	return max(imap(lambda n: (n/tots[n], n), xrange(2,nmax)))
