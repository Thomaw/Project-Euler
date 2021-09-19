def highest_order_term(seq):
    order, order_factorial = 0,1
    while [t for t in seq if t != seq[0]]:
        # Take diff till all the same.
        seq = [(i2-i1) for (i1,i2) in zip(seq, seq[1:])]
        order += 1
        order_factorial *= order
    return seq[0] / order_factorial, order

def make_poly(seq):
    # Make polynomial function that gives seq.
    terms = [] # K,o pairs
    while 1:
        K,o = highest_order_term(seq)
        terms.append((K,o))
        if o == 0:
            break # Got all terms.
        # now subtract Kn^o from each term
        diff=[K*(n**o) for n in range(1, len(seq))]
        seq = [a-b for (a,b) in zip(seq, diff)]
    return lambda n: sum(k*(n**o) for (k,o) in terms)

def t(n): return sum((-n)**e for e in range(11))
seq=[t(n) for n in range(1,20)]

print sum( make_poly(seq[:i])(i+1) for i in range(1,11))
