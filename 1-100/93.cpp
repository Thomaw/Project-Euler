void test(vector<double> n, vector<bool>& p) {
	if(n.size() == 1 && fabs(round(n[0]) - n[0]) < 0.00001) { // compensate for rounding errors
		// we have a result
		p[lround(n[0])] = true;
		return;
	}
	for(int i = 0; i < n.size(); i++) {
		for(int j = i+1; j < n.size(); j++) {
			// pick two numbers from the set
			double a = n[i], b = n[j];
			vector<double> m = n;
			// remove one of these numbers
			m.erase(m.begin() + j);
			// replace the other by the combined result: sum, product, etc.
			m[i] = a + b;
			test(m, p);
			m[i] = a * b;
			test(m, p);
			if(a >= b) { // avoid negative numbers
				m[i] = a - b;
				test(m, p);
			}
			if(a <= b) { // avoid negative numbers
				m[i] = b - a;
				test(m, p);
			}
			if(a != 0) { // avoid division by 0
				m[i] = b / a;
				test(m, p);
			}
			if(b != 0) { // avoid division by 0
				m[i] = a / b;
				test(m, p);
			}
		}
	}
}

int main() {
	int m = 0, r;
	for(int a = 0; a <= 9; a++) {
		for(int b = a+1; b <= 9; b++) {
			for(int c = b+1; c <= 9; c++) {
				for(int d = c+1; d <= 9; d++) {
					vector<bool> p(3025, false);
					vector<double> n(4);
					n[0] = a; n[1] = b; n[2] = c; n[3] = d;
					test(n, p);
					// find the longest sequence
					int k = 0;
					for(int i = 1; i < p.size(); i++) {
						if(p[i]) {
							k++;
						}
						else {
							k = 0;
						}
						if(k > m) {
							m = k;
							r = 1000*a + 100*b + 10*c + d;
						}
					}
				}
			}
		}
	}
	cout << r << endl;
	return 0;
}