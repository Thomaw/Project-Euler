int W = 9;
int H = 12;

// ** ** *   * * ***
// *   * ** ** *
//             *
int npieces = 6;
int msk[] = { 3|(1<<W), 3|(2<<W), 1|(3<<W), 1|(3<<(W-1)), 1|(1<<W)|(1<<2*W), 7 };
int sz[][2] = { {2,2}, {2,2}, {2,2}, {1,2}, {1,3}, {3,1} };
int *NR = new int[W*H];
int *NC = new int[W*H];

map<int,long long> *cache = new map<int,long long>[W*H];

long long rec(int c, int m) {
	if(c>=W*H) return 1;
	if(cache[c].count(m)>0) return cache[c][m];
	if(m&1) return cache[c][m]=rec(c+1,m>>1);
	
	int R,C;
	R=NR[c]; C=NC[c];
	
	long long total=0;
	for(int i=0; i<npieces; i++) {
		if(C+sz[i][0]>W || R+sz[i][1]>H) continue;
		if((m&msk[i])>0) continue;
		if(i==3 && C==0) continue;
		total += rec(c+1,(m|msk[i])>>1);
	}
	
	cache[c][m]=total;
	return total;
}

void prob161() {
	for(int i=0; i<H; i++) for(int j=0; j<W; j++) { NC[i*W+j] = j; NR[i*W+j] = i; }

	printf("Total: %lld\n", rec(0,0));
}