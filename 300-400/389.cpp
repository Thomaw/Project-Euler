int P;
	fin >> P;
	double M1 = 1.0, M2 = 1.0;
	for (int i = 0; i < P; ++i) {
		int N;
		fin >> N;
		double m1 = 0.5 * (N + 1) * M1;
		double m2 = 1.0 * M1 * (N + 1) * (2 * N + 1) / 6 + 0.25 * (M2 - M1) * (N + 1) * (N + 1);
		M1 = m1; M2 = m2;
	}
	fout << M2 - M1 * M1 << '\n';