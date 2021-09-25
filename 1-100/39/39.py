import math
C={}
for a in range(1,500):
	for b in range(a,500):
		c=int(math.sqrt(a*a+b*b))
		if a*a+b*b==c*c:
			try:
				C[a+b+c]+=1
			except KeyError:
				C[a+b+c]=1

mx=-1;
mxp=-1;
for (k, v) in C.iteritems():
	if v>mx:
		mx=v
		mxp=k

print mx,mxp
