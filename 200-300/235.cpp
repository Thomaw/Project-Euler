double s(double r, int n) {
	double r2 = Pow(r, n);
	double r1 = r - 1;
	return 1/r1 * (900 * (r2-1) - 3*n*r2 + 3*(r2-1)/r1);
}