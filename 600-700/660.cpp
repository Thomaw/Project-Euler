// are a, b, and c together n-pandigital
bool nPanDig[20];
bool nPandigital(int n, int a, int b, int c)
{
	for (int u = 0; u < n; u++) nPanDig[u] = false;
	int ct = 0, d, aa = a;
	while (aa > 0)
	{
		d = aa % n;
		if (nPanDig[d]) return false;
		nPanDig[d] = true; ct++;  aa /= n;
	}
	int bb = b;
	while (bb > 0)
	{
		d = bb % n;
		if (nPanDig[d]) return false;
		nPanDig[d] = true; ct++; bb /= n;
	}
	int cc = c;
	while (cc > 0)
	{
		d = cc % n;
		if (nPanDig[d]) return false;
		nPanDig[d] = true;  ct++; cc /= n;
	}	
	return (ct == n);
}



// Problem 660: Pandigital Triangles
void Problem660()
{
	long long int m, n, a, b, c, aa, bb, cc, ans = 0, mx = 34012224;
	m = 2; n = 1; a = m * m + m * n + n * n;
	while (a < mx)
	{
		for (n = 1; n < m; n++)
			if (((m - n) % 3) != 0)
				if (GCD(m, n) == 1)
				{
					a = m * m + m * n + n * n;
					b = 2 * m * n + n * n;
					c = m * m - n * n;
					aa = a; bb = b; cc = c;
					while (aa < mx)
					{
						for (int w = 9; w <= 18; w++)
							if (nPandigital(w, aa, bb, cc))
							{
								//cout << w << "-pan: " << aa << ", " << bb << ", " << cc << "\n";
								ans += aa; break;
							}
						aa += a; bb += b; cc += c;

					}
					
				}
		m++;
	}
	cout << "Problem 660: " << ans << "\n";
}
