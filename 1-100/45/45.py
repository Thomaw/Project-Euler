P,Pen = 0,0
while 1:
	Hex = H*(2 * H - 1)
	while Pen < Hex:
		P += 1
		Pen = int( 0.5 * P * (3*P - 1 ))
	if not Pen == Hex:
		continue
	print Tri,Hex,Pen
	break
