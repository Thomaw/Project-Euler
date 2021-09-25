lint Problem() {
	lint nMax = 100000000ll;
	vector < int > v (nMax, 0);
	for (lint i = 1; i*i < nMax; ++i) {
		for (lint k = 1; (k*i+k+2 <= (k+1)*i-k-3); ++k) {
			if (i*(k*i+k+2) >= nMax)
				break;
			for (lint j = k*i+k+2; j <= (k+1)*i-k-3; ++j) {
				if (i&j&1)
					continue;
				if (i*j < nMax)
					++v[i*j];
			}
		}
	}

	for (lint i = 0; i < nMax; ++i) {
		if (v[i] == 200) {
			return i;
		}
	}
}