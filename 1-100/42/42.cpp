int main() {

	int i,x,rez = 0;
	
	for (i = 0 ; words[i] != NULL; i++) {
		x = 0;
		while (*words[i]) {
			x += (*words[i] - 'A') + 1;
			*words[i]++;
		}
		if ( (sqrt(1 + 2 * x * 4) - 1 / 2) - (int)sqrt(1 + 2 * x * 4) - 1 / 2 <= 0.000000001)
			++rez;
	}
	return printf("%d\n" , rez);
}
