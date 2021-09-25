
  int factorial[10] = {
    1,
    1,
    1*2,
    2*3,
    2*3*4,
    2*3*4*5,
    2*3*4*5*6,
    2*3*4*5*6*7,
    2*3*4*5*6*7*8,
    2*3*4*5*6*7*8*9
  };
  static int chain_length[7 * 2*3*4*5*6*7*8*9];
  for (int i = 1; i < limit; ++i) if (chain_length[i] == 0) {
    int fs = i, c;
    int seq[100];
    seq[0] = i;
    for (c = 1; ; ++c) {
      int newfs = 0;
      do { newfs += factorial[fs % 10]; fs /= 10; } while (fs != 0);
      seq[c] = fs = newfs;
      int baselen = chain_length[newfs];
      if (baselen > 3) {
        for (int s = 0; s < c; ++s) {
          chain_length[seq[s]] = baselen + c - s;
        }
        c += baselen;
        break;
      } else if (fs == seq[c - 1]) {
        for (int s = 0; s < c; ++s) {
          chain_length[seq[s]] = c - s;
        }
        break;
      } else if (c > 1 && fs == seq[c - 2]) {
        for (int s = 0; s < c - 1; ++s) {
          chain_length[seq[s]] = c - s;
        }
        break;
      } else if (c > 2 && fs == seq[c - 3]) {
        for (int s = 0; s < c - 2; ++s) {
          chain_length[seq[s]] = c - s;
        }
        break;
      }
    }
    if (c >= 60) {
      printf("Found chain at %d, len=%d\n", i, c);
    }
  }
