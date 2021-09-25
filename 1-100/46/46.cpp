int
main() {

	int i,pc[1500],j,z;
	double x;

	for (i = 3,j = 0;i < 10000; i +=2) {
		if (isp(i)) 
			pc[j++] = i;
		else
			
			for (z = 0; z < j ; z++) {
				x = sqrt((i - pc[z]) / 2);
				if (x - (int) x < 0.00001)
				break;
			}

		if (z == j)
			break;
	}
	return printf("%d\n" , i);
}
