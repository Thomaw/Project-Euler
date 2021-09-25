import time
tStart=time.time()
list=[2, 3, ... 9967, 9973]
for x in range(1,10000):
    omg="no"
    if x in list or x/2==x*.5:
        continue
    y=0
    while y<int(x**.5) and omg=="no":
        y+=1
        if x-2*y*y in list:
            omg="yes"
    if omg=="no":
        print x
