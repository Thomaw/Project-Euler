from ProjectEuler import isqrt

def A(nmax):
    # b**2 + 13 = a**2 and sqrt(3*a*b) is int

    sumA=0
    # case 1: b**2=3*p**2, a**2=q**2, 3*p**2+13 = q**2
    p,q=1,4
    while True:
        a2,b2 = q*q,3*p*p
        area=3*3*p*q
        P,Q,R = b2,a2,4*a2*b2
        y=0
        x=isqrt(R//P)
        if x>nmax : break
        if P*x*x+Q*y*y==R : sumA+=2*area
        p,q = 2*p+q, 3*p+2*q

    p,q=2,5
    while True:
        a2,b2 = q*q,3*p*p
        area=3*3*p*q
        P,Q,R = b2,a2,4*a2*b2
        y=0
        x=isqrt(R//P)
        if x>nmax : break
        if P*x*x+Q*y*y==R : sumA+=2*area
        p,q = 2*p+q, 3*p+2*q

    # case 2: b**2=3*13*p**2, a**2=13*q**2, 3*p**2+1 = q**2
    p,q=1,2
    while True:
        a2,b2 = 13*q*q,13*3*p*p
        area=3*3*13*p*q
        P,Q,R = b2//13, a2//13, 4*a2*b2//13
        y=isqrt(R//(P*49//3+Q))
        x=isqrt((R-Q*y*y)//P)
        if x>nmax : break
        if P*x*x+Q*y*y==R : sumA+=4*area
        p,q = 2*p+q, 3*p+2*q
    return sumA

        
print A(10) # 252
print A(100) # 34632
print A(1000) # 3529008
print A(10**9)