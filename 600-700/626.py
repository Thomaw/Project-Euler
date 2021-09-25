import sympy,fractions

n = 20

# calc the cycle index of Sn
symbols = {x: sympy.Symbol(str(int(x))) for x in range(1,n+1)}
vs = symbols.values()
symbols = {x: y.as_poly(vs) for x,y in symbols.items()}
cycle_index = {0: 1}
for i in range(1,n+1):
  cycle_index[i] = sum([symbols[x] * cycle_index[i - x] for x in range(1,i+1)])/i

# pre-calc info we will need later about each monomial of the cycle index
monomials = cycle_index[n].args
cache = []
for i in range(len(monomials)):
  coeff,prod = monomials[i].as_coeff_Mul()
  prod = {int(str(v)): p for v,p in prod.as_powers_dict().items()}
  powers2 = [[len(bin(x&-x))-3,y] for x,y in prod.items()] # how many powers of 2 in each cycle length
  min2 = min([x[0] for x in powers2])
  cache.append([coeff,prod,powers2,min2])

# iterate of Sn x Sn
ans = 0
for i in range(len(monomials)):
  [coeffI,prodI,powers2I,minI] = cache[i]
  for j in range(i,len(monomials)): 
    [coeffJ,prodJ,powers2J,minJ] = cache[j]
    
    flip_constraints = sum([x[1] for x in powers2I if x[0]>=minJ]) + sum([x[1] for x in powers2J if x[0]>=minI])
    if minI == minJ: flip_constraints -= 1
    exp_sum = 0 # the sum of the exponents in this monomial. we are going to plug 2 for each variable, so only need the sum of exps
    for lenI,powerI in prodI.items():
      for lenJ,powerJ in prodJ.items():
        exp_sum += powerI * powerJ * fractions.gcd(lenI,lenJ)

    ans += 2**(exp_sum-flip_constraints) * coeffI * coeffJ * (1 if i==j else 2)

print ans