#include <iostream>

typedef unsigned long long uint64;

int main()
{
	unsigned goldNuggetsCnt = 1;
	uint64 nuggetsSum = 2;
	uint64 a = 3, aSub1 = 0, aSub2;
	uint64 b = 16, bSub1 = 2, bSub2;
	
	for (uint64 n = 2, k = 1; goldNuggetsCnt < 30; k++) {
		if (k % 2) {
			goldNuggetsCnt++;
			n += a;
			nuggetsSum += n;
			aSub2 = aSub1;
			aSub1 = a;
			a = 7*aSub1-aSub2;
		} else if (goldNuggetsCnt < 30) {
			goldNuggetsCnt++;
			n += b;
			nuggetsSum += n;
			bSub2 = bSub1;
			bSub1 = b;
			b = 7*bSub1-bSub2;
		}
	}
		
	std::cout << nuggetsSum;
	return 0;
}int main(int argc, char *argv[]) {
  uint64_t limit = (argc != 2) ? 1024 : atoi(argv[1]);
  // hk's optimization: find all lower 16-bits that could be squares
  static char canberoot[65536];
  for (int i = 0; i < 65536; ++i) {
    canberoot[(i * i) & 65535] = 1;
  }

  uint64_t sum = 0;
  std::set<int> nset;
  for (int f = 1; f <= limit; ++f) {
    // if f has a perfect square as a factor, then there exists a smaller
    // f with larger A and B that is also a solution.
    // this is the outer loop so it's worth removing a few
    if ((f % 4) == 0 || (f % 9) == 0 || (f % 25) == 0) continue;
    // pre-compute limit^2 / f^2; it comes in handy
    uint64_t limit2f2 = limit * limit / f / f;
    // don't bother with B if B^3 * f^2 > limit^2
    for (uint64_t B = 1, B3; (B3 = B * B * B) < limit2f2; ++B) {
      // likewise we don't care about A > B or A * B^3 * f^2 > limit^2
      uint64_t maxA = limit2f2 / B3;
      if (maxA > B) maxA = B;
      for (uint64_t A = 1; A < maxA; ++A) {
        uint64_t n = f * A * (f * B3 + A);
        if (!canberoot[n & 65535]) continue;
        uint64_t N = sqrt(double(n));
        if (N * N == n) {
          if (nset.count(int(N)) == 0) {
            sum += n;
            nset.insert(int(N));
          }
        }
      }
    }
  }
  printf("Sum is %lld\n", sum);
}