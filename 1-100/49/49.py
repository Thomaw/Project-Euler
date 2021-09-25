def main():
    from eulertools import primes
    from sets import Set as set

    def sorted(seq):
        seq = list(seq)
        seq.sort()
        return "".join(seq)

    p = primes(10000)
    
    pd = {}
    for pi in p:
        if pi < 1000: continue
        spi = sorted(str(pi))
        pd.setdefault(spi, []).append(pi)
    
    for i, pi in enumerate(p):
        if pi < 1000 or pi == 1487: continue
        spi = sorted(str(pi))
        pals = pd[spi] 
        if len(pals) < 3: continue
        for pj in pals:
            if pj <= pi: continue 
            if sorted(str(pj)) != spi: continue
            diff = pj - pi
            pk = pj+diff
            if pk in pals:
                print "%s%s%s" % (pi, pj, pk)
                return
main()
