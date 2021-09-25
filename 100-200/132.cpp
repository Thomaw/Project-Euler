bool isFactor32(uint32 p) {
  // q = GCD(p-1, 10^9)
  uint32 q = 1, t = p - 1;
  for(int c = 0; c < 9 && (t & 1) == 0; c++) { t >>= 1; q <<= 1; }
  for(int c = 0; c < 9 && (t % 5) == 0; c++) { t /= 5; q += q << 2; }

  // b = highest set bit in q
  uint32 b = 1; t = q;
  if (t > 0xFFFF) { b <<= 16; t >>= 16; }
  if (t > 0xFF) { b <<= 8; t >>= 8; }
  if (t > 0xF) { b <<= 4; t >>= 4; }
  if (t > 3) { b <<= 2; t >>= 2; }
  if (t > 1) { b <<= 1; }

  // a = (10^q) mod p
  uint32 a = 1;
  for(;;) {
    if ((q & b) != 0) a = ((uint64)(a) * 10) % p;
    if ((b >>= 1) == 0) break;
    a = ((uint64)(a) * a) % p;
  }
  return a == 1;
}