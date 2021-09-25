s = ""
l = len(s)
x,next,prev,sum = 1,1,0,1
while l < 1000000:
	s = str(x);
	l += len( str(x) )
	if l >= next:
		sum *= int( s[next - prev - 1 ])
		next = next*10
	prev = l	
	x += 1
print sum
