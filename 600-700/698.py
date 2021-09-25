## Ctrl + B to build, Ctrl + Shift + P to run
## Don't forget to delete REPL stuff

import numpy as np
import pandas as pd

def fac(x):
	ret = 1
	for i in range(1, x+1):
		ret = ret * i
	return ret

def calc(x):
	L = [0, 1, 2, 3, 11, 12, 13, 21, 22, 23, 31, 32, 33]
	ret = 0
	for i in L:
		for j in L:
			for k in L:
				if i + j + k == x:
					ret += fac(x) // fac(i) // fac(j) // fac(k)
	return ret

def gogo_find(X, x, num, num_1, num_2, num_3):
	if x == 0:
		return 0
	ret = 0
	L = [0, 1, 2, 3, 11, 12, 13, 21, 22, 23, 31, 32, 33]
	## start with 1
	for i in L: 
		for j in L:
			for k in L:
				if i >= num_1 + 1 and j >= num_2 and k >= num_3 and i + j + k == X:
					ret += fac(x-1) // fac(i-num_1-1) // fac(j-num_2) // fac(k-num_3)
	if ret >= num:
		ans = 10 ** (x-1)
		ans += gogo_find(X, x-1, num, num_1+1, num_2, num_3)
		return ans
	pret = ret
	## start with 2
	for i in L: 
		for j in L:
			for k in L:
				if i >= num_1 and j >= num_2 + 1 and k >= num_3 and i + j + k == X:
					ret += fac(x-1) // fac(i-num_1) // fac(j-num_2-1) // fac(k-num_3)
	if ret >= num:
		ans = 2 * (10 ** (x-1))
		ans += gogo_find(X, x-1, num-pret, num_1, num_2+1, num_3)
		return ans
	## start with 3
	pret = ret
	ans = 3 * (10 ** (x-1))
	ans += gogo_find(X, x-1, num-pret, num_1, num_2, num_3+1)
	return ans

mod = 123123123
goal = 111111111111222333
cur = 0
for i in range(1, 300):
	cur += calc(i)
	if cur >= goal:
		cur -= calc(i)
		ans = gogo_find(i, i, goal-cur, 0, 0, 0) ## i digit, (goal-cur)th (1-index)
		print(ans%mod)
		break