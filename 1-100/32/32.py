ran = xrange(0,10)
possa = [10*a + b for a in ran for b in ran if a <> b]
possb = []
for a in xrange(100,9999):
    x = str(a)
    y = set(x)
    if len(x) == len(y): possb.append(a)
sol = []
for a in possa:  
    for b in possb:
        if b < max(a,1000.0 / a): continue
        if b > 9999.0 / a: break        
        c = a*b
        if "".join(sorted(str(a)+str(b)+str(c))) == "123456789":            
            sol.append(c)
sol = set(sol)
print sum(sol)
