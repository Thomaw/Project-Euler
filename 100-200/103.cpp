class DispersionError(Exception):
    pass

import itertools

def test_special_sum(b):
    '''
        test set b for special_sum
    '''
    b = list(b)
    s = set(b)
    try:
        if len(s) < len(b):
            raise DispersionError('NOT ENOUGH')
        b.sort()
        for i in range(1,len(b)//2+1):
            if sum(b[:i+1]) <= sum(b[-i:]):
                raise DispersionError('too much')
        for i in range(2,len(b)//2+1):
            for c in itertools.combinations(b,i):
                sumc = sum(c)
                d = list(s-set(c))
                d.sort()
                for e in itertools.combinations(d,i):
                    sume = sum(e)
                    if sume == sumc:
                        raise DispersionError('not enough')
                    #if sumc < sume:
                    #    break
    except DispersionError as yuk:
        return (9999999999,b,)
    else:
        return(sum(b),b,)

#print(e105())

# wrong:  132094,81153
# problems 103, 106

def e103():
    return min(test_special_sum((20+i,31+j,38+k,39+l,40+m,42+n,45+o))for(i,j,k,l,m,n,o)in itertools.product((0,-1,-2,-3,1,2,3),repeat=7))

print(e103())