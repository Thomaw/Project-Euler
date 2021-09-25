
def prob30(x):
        s = 0
        for i in range(2,1000000):
                t = 0
                for a in str(i):
                        t += int(a)**x
                if t == i:
                        s += t
        print s
prob30(5)
