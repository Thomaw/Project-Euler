# Experimental answer:
#       158299928/300000000 = 0.52766642666666663
#       263825218/500000000 = 0.52765043599999994
#      923404641/1750000000 = 0.52765979485714287
#     1907473380/3615000000 = 0.52765 51535269709
#     3953791996/7493000000 = 0.527664 75323635398
#     5271914283/9991000000 = 0.527666 32799519564
#     5272441901/9992000000 = 0.527666 3231585268
#     5272970302/9993000000 = 0.527666 39667767434
#     5273497710/9994000000 = 0.527666 37082249346
#     5274025393/9995000000 = 0.527666 37248624315
#     5274553821/9996000000 = 0.527666 44867947177
#     5275081424/9997000000 = 0.527666 44233269977
#     5275608860/9998000000 = 0.527666 41928385682
#     5276136781/9999000000 = 0.527666 44474447444
#    5276664245/10000000000 = 0.527666 42450000001

# Woohoo I think I got it!    0.527666275943313
# To 10 decimal places that's 0.5276662759

'''

 Here are all the random variables in question:
     discrete variables:
         N1 = exact number of X's til 1 is exceeded
         N2 = exact number of Y's til 2 is exceeded
     continuous variables:
         X1,X2,...XN1=X
         Y1,Y2,...YN1=Y
         A = X1+...+X(N1-1)       i.e. last sum < 1
         B = X1+...+XN1 = A+XN1   i.e. first sum > 1
         C = B+Y1+...+Y(N2-1)     i.e. last sum < 2
         D = B+Y1+...+YN2 = C+YN2 i.e. first sum > 2
 So 0<A<1<B<C<2<D
    A-B=X<1
    D-C=Y<1

 The answer is going to be a nesting of 2 summations (over n1,n2)
 and 4 integrals (over a,b,c,d).
 The summations are theoretically to infinity
 but some preliminary calculation makes it clear that
 any values of n1 or n2 over 16 or so aren't going to contribute to the answer
 at the required precision so we'll just sum them to 16.

 After a few false starts, the strategy I settled on
 is to pull the summations over n1,n2 outside of the integrals,
 so that for each single value pair n1,n2 we do the entire quadruple integral
 resulting in a number, so that we're summing numbers instead of expressions--
 that prevents the integrand expressions from growing out of control in complexity.
 Also this makes it so that, during the symbolic integrations,
 the n1,n2's are ints rather than variables,
 which apparently makes the expressions much much easier
 for the symbolic integrator to swallow.

 So the overall structure of my calculation is:
     P(Y>X) = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] Int[b=1..a+1] Int[c=b..2] Int[d=max(2,c+(b-a))..c+1] p(n1,n2,a,b,c,d)
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] Int[b=1..a+1] p(n1,a,b) Int[c=b..2] Int[d=max(2,c+(b-a))..c+1] p(n2,c,d|b)
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] Int[b=1..a+1] psum(n1-1,a) Int[c=b..2] Int[d=max(2,c+(b-a))..c+1] psum(n2-1,c-b)
 (where psum(n,x) = x^(n-1)/(n-1)!
 is the pdf of n independent uniform vars summing to x)
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] psum(n1-1,a) Int[b=1..a+1] Int[c=b..2] psum(n2-1,c-b) Int[d=max(2,c+(b-a))..c+1] 1
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] a^(n1-2)/(n1-2)! Int[b=1..a+1] Int[c=b..2] (c-b)^(n2-1)/(n2-1)! Int[d=max(2,c+(b-a))..c+1] 1
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] a^(n1-2)/(n1-2)! Int[b=1..a+1] Int[c=b..2] (c-b)^(n2-1)/(n2-1)! ((c+1)-max(2,c+(b-a)))
 The occurrance of "max" implies a behavior change at the value of c where 2=c+(b-a),
 i.e. at c=2-(b-a), so we split up the c range at that point:
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] a^(n1-2)/(n1-2)! Int[b=1..a+1] (Int[c=b..2-(b-a)] (c-b)^(n2-1)/(n2-1)! ((c+1)-max(2,c+(b-a)))
                                                                                    + Int[c=2-(b-a)..2] (c-b)^(n2-1)/(n2-1)! ((c+1)-max(2,c+(b-a))))
 Whoops! Except we just screwed up if the upper sub-range we just created is backwards,
 i.e. if b>2-(b-a), i.e. if 2b>2-a, i.e. if b>1-a/2.
 In that case there was no discontinuity in the c range so it didn't need splitting.
 So, we split the b range at the point b=1-a/2;
 on the lower b sub-range we split c,
 and on the upper b sub-range we don't:
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] a^(n1-2)/(n1-2)! ((Int[b=1..1+a/2]  (Int[c=b..2-(b-a)] (c-b)^(n2-2)/(n2-2)! ((c+1)-max(2,c+(b-a)))
                                                                                         + Int[c=2-(b-a)..2] (c-b)^(n2-2)/(n2-2)! ((c+1)-max(2,c+(b-a)))))
                                                                      + (Int[b=1+a/2..1+a] Int[c=b..2]       (c-b)^(n2-2)/(n2-2)! ((c+1)-max(2,c+(b-a)))))
 Now we've fractured the ranges enough so that we can get rid of the "max"s:
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] a^(n1-2)/(n1-2)! ((Int[b=1..1+a/2]  (Int[c=b..2-(b-a)] (c-b)^(n2-2)/(n2-2)! ((c+1)-2))
                                                                                         + Int[c=2-(b-a)..2] (c-b)^(n2-2)/(n2-2)! ((c+1)-(c+(b-a))))
                                                                      + (Int[b=1+a/2..1+a] Int[c=b..2]       (c-b)^(n2-2)/(n2-2)! ((c+1)-(c+(b-a)))))
            = Sum[n1=2..16] Sum[n2=1..16] Int[a=0..1] a^(n1-2)/(n1-2)! ((Int[b=1..1+a/2]  (Int[c=b..2-(b-a)] (c-b)^(n2-2)/(n2-2)! (c-1)
                                                                                         + Int[c=2-(b-a)..2] (c-b)^(n2-2)/(n2-2)! (1-(b-a)))
                                                                      + (Int[b=1+a/2..1+a] Int[c=b..2]       (c-b)^(n2-2)/(n2-2)! (1-(b-a))))
 That's *almost* something we can start typing into a symbolic integrator,
 except that it's not quite right in the one case of n2=1, i.e. c=b
 (note the occurance of (n2-2)! which makes it break down).
 Fortunately this special case of n2=2 is a bit simpler than the general case.
 In this case the summand becomes (skipping some steps done on paper):
                                          Int[a=0..1] a^(n1-2)/(n1-2)! ((Int[b=1..1+a/2]   (b-1))
                                                                      + (Int[b=1+a/2..1+a] (1-(b-a))))
'''


import sys
import math
import random
import time

def factorial(n):
    assert n >= 0
    answer = 1
    for i in xrange(1,n+1):
        answer *= i
    return answer

def incr(v, i):
    while len(v) <= i: v.append(0)
    v[i] += 1
def incr2(v, i, j):
    while len(v) <= i: v.append([])
    incr(v[i], j)
def get2(v, i, j):
    if len(v) <= i or len(v[i]) <= j:
        return 0
    return v[i][j]

# returns:
#       xs
#       ys
def doOneExperimentReturningXsYs():
    sum = 0.
    xs = []
    while sum < 1.:
        x = random.random()
        xs.append(x)
        sum += x
    ys = []
    while sum < 2.:
        y = random.random()
        ys.append(y)
        sum += y
    return xs,ys
def doOneExperimentReturningN1N2ABCD():
    xs,ys = doOneExperimentReturningXsYs()
    n1 = len(xs)
    n2 = len(ys)
    a = sum(xs[:-1])
    b = a + xs[-1]
    c = b + sum(ys[:-1])
    d = c + ys[-1]
    return n1,n2,a,b,c,d

def ProbYgreaterThanXexperimental(maxN1, maxN2, nSamples):
    print "    in ProbYgreaterThanXexperimental(maxN1="+`maxN1`+", maxN2="+`maxN2`+")"
    print "        gathering "+`nSamples`+" samples..."
    t0 = time.time()
    nPlays = 0
    nWins1 = 0
    nWins2 = 0
    histogramN1N2 = []
    histogramN1N2wins2 = []
    for iSample in xrange(nSamples):
        n1,n2,a,b,c,d = doOneExperimentReturningN1N2ABCD()

        nPlays += 1
        if d-c > b-a:
            nWins2 += 1
        else:
            nWins1 += 1
        incr2(histogramN1N2, n1, n2)
        if d-c > b-a:
            incr2(histogramN1N2wins2, n1, n2)
    t1 = time.time()
    print "        done gathering "+`nSamples`+" samples in "+"%.6f"%(t1-t0)+" secs."
    if nSamples >= 1:
        answer = 0.
        for n1 in xrange(2, maxN1+1):
            print "        n1="+`n1`
            for n2 in xrange(1, maxN2+1):
                print "            n1="+`n1`+" n2="+`n2`
                numerator = get2(histogramN1N2wins2, n1, n2)
                denominator = nPlays
                summand = numerator/float(denominator)
                print "                summand = "+`numerator`+"/"+`denominator`+" = "+`summand`
                answer += summand
    else:
        answer = None
    print "    out ProbYgreaterThanXexperimental(maxN1="+`maxN1`+", maxN2="+`maxN2`+"), returning "+`answer`


# helper integration function that puts v,a,b first,
# since I find that easier to read...
# also uses 'sympy' rather than 'maxima' by default
# since sympy seems to work in some cases where maxima was failing.
# on second thought, use maxima, in the final form of my program it's a lot faster.
# interestingly though, it seems to have significant startup overhead, so use sympy for initial debugging of individual cases.
def integ(v,a,b,expr):
    algorithm = algorithmToUse()
    print "                    using "+`algorithm`
    return integrate(expr,v=v,a=a,b=b,algorithm=algorithm)

def ProbYgreaterThanX(maxN1, maxN2):
    print "    in ProbYgreaterThanX(maxN1="+`maxN1`+", maxN2="+`maxN2`+")"
    answer = 0
    a,b,c,d = var('a,b,c,d')
    for n1 in xrange(2, maxN1+1):
        print "        n1="+`n1`
        for n2 in xrange(1, maxN2+1):
            print "            n1="+`n1`+" n2="+`n2`
            if n2 == 1: # special case
                print "                special case"
                summand = (integ(a,0,1, a^(n1-2) * (integ(b,1,1+a/2, b-1)
                                                  + integ(b,1+a/2,1+a, 1-(b-a))))
                         / factorial(n1-2))
            else:
                summand = (integ(a,0,1, a^(n1-2) * (integ(b,1,1+a/2,   integ(c,b,2-(b-a), (c-b)^(n2-2) * (c-1))
                                                                     + integ(c,2-(b-a),2, (c-b)^(n2-2) * (1-(b-a))))
                                                  + integ(b,1+a/2,1+a, integ(c,b,2, (c-b)^(n2-2) * (1-(b-a))))))
                         / (factorial(n1-2) * factorial(n2-2)))
            summandReal = 1.*summand
            print "                summand = "+`summand`+" = "+`summandReal`
            answer += summandReal
    print "    out ProbYgreaterThanX(maxN1="+`maxN1`+", maxN2="+`maxN2`+"), returning "+`answer`
    return answer

if len(sys.argv) != 5:
    exit("Usage: "+`sys.argv[0]`+" maxN1 maxN2 nSamples [sympy|maxima]")

maxN1 = eval(sys.argv[1])
maxN2 = eval(sys.argv[2])
nSamples = eval(sys.argv[3])
defaultAlgorithm = sys.argv[4]

# having to go through strange convolutions, default function args
# don't seem to work in sage?
def algorithmToUse(): return defaultAlgorithm

print "analytically: " +`ProbYgreaterThanX(maxN1,maxN2)`
print "experimentally: " +`ProbYgreaterThanXexperimental(maxN1,maxN2,nSamples)`