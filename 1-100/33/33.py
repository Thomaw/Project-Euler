def red(r): #does a/b reduce, where r = a,b, [a,b],etc
    a,b = r
    x = (set(str(a)) & set(str(b))) - set(['0'])    
    for n in x:        
        a1 = filter(lambda z:str(a)[(z+1)%2] == n,[0,1]) 
        a2 = filter(lambda z:str(b)[(z+1)%2] == n,[0,1])
        for c in a1:
            for d in a2:
                if a*int(str(b)[d]) == b*int(str(a)[c]):                                 
                    return(True)
    return(False)
def red2(r): # reduce a/b to lowest terms, where r= a,b, etc
    (a,b) = r
    while True:
        for d in range(2,min(a,b)+1):
            if a % d == 0 and b % d == 0:
                (a,b) = (a/d,b/d)
                break
        else: return((a,b))
sols = filter(red,[(a,b) for a in range(10,100) for b in range(a+1,100)])
sol = red2([reduce(lambda a,b:a*b,[x[k] for x in sols]) for k in [0,1]])
print sols
