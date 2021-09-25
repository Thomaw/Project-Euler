int main() {

	unsigned int i,j, pc[300];
	float rez,rez2;

	for (i = 1;;i++) {
		pc[i] = (i * ( 3 * i - 1)) / 2;

		for (j = 1 ; j < i ; j++) {
			rez = (sqrt(1 + 3 * 8 * (pc[i] + pc[j]) ) + 1) / 6;
			rez2 = (sqrt(1 + 3 * 8 * (pc[i] - pc[j]) ) + 1) / 6;

			if (rez - (int) rez < 0.00001 && rez2 - (int) rez2 < 0.00001) {
				printf("%d\n" , (int) pc[i] -   pc[j]);
				exit(9);
			}
		}
	}
	return 0;
}
