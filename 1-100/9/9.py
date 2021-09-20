for c in xrange(334,500):
    for a in xrange(1, (1000-c)/2):
        b = (1000 - c) - a
        if a**2 + b**2 == c**2:
            print "a,b,c =",a,b,c
