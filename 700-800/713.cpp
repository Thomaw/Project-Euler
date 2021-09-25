	__int64 * tri = new __int64[N+1];
	for (__int64 i = 0; i <= N; i++) tri[i] = i * (i-1) / 2;
	__int64 sum = 0;
	for (int m = 2; m <= N; m++) {
		__int64 n1 = N/(m-1);
		__int64 n2 = n1 + 1;
		__int64 r2 = N - n1 * (m-1);
		__int64 r1 = m - 1 - r2;
		sum = sum + r1*tri[n1] + r2*tri[n2];
	}
	cout << "sum = " << sum << "\n";