def hms():
	months=[31,28,31,30,31,30,31,31,30,31,30,31]
	months2=[31,29,31,30,31,30,31,31,30,31,30,31]
	day=2
	count=0
	for i in range (1901,2001):
		for j in range (0,12):
			if i%4!=0:
				day+=months[j]%7
			else:
				day+=months2[j]%7
			if day%7==0:
				count+=1
	return count
