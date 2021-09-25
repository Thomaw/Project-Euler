#include <vector>
#include <algorithm>

#define X first
#define Y second
#define MP make_pair

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<vector<ld>, ld> result;

bool bit_set(int set, int bit) {
  return ((set>>bit)&1)==1;
}
int remove_bit(int set, int bit) {
  return set & (~(1<<bit));
}

ld EPS = 1e-9;

const ll N = 14;
// The skill of each player
vector<ld> S(N, 0);

// Memoization table
vector<vector<result> > DP(1<<N, vector<result>(N, MP(vector<ld>(N, 0), 0.0)));
// "Have we seen this state before" memoization table
vector<vector<int> > DP_S(1<<N, vector<int>(N, 0));

// f(live, who) = pair of (winning probabilities, expected length)
// given the bitset of which players are in the game and whose turn it is
pair<vector<ld>, ld> f(int live, int who) {
  // Skip dead players
  if(!bit_set(live, who)) { return f(live, (who+1)%N); }
  // If there's only 1 player left, the game is over
  if(__builtin_popcount(live) == 1) {
    vector<ld> W(N, 0);
    for(int i=0; i<N; i++) {
      // The last player standing won; everyone else lost
      W[i] = bit_set(live, i) ? 1.0 : 0.0;
    }
    // Once someone wins, there are 0 more turns left in the game.
    return MP(W, 0);
  }

  // Memoize
  if(DP_S[live][who]) { return DP[live][who]; }
  DP_S[live][who] = 1;

  // Our return values
  vector<ld> W(N, 0);
  ld turns = 0;

  // Compute the probability of each player getting the next shot
  vector<ld> P(N, 0);
  ld pleft = 1.0; // The probability no one has shot yet
  for(int i=0; i<N; i++) {
    int pi = (who+i)%N;
    if(bit_set(live, pi)) {
      P[pi] = pleft*S[pi];
      pleft *= (1-S[pi]);
    }
  }

  // Take care of the cycle; if no one shoots,
  // we're back where we started
  if(pleft > EPS) {
    for(int i=0; i<N; i++) {
      P[i] *= 1.0/(1.0-pleft);
    }
    // The # of rounds till someone shoots is a
    // Geometric random variable.
    turns += __builtin_popcount(live) * (1.0/(1-pleft)-1);
  }

  int my_pos = 0;
  // For each person, see what happens if they shoot next
  for(int i=0; i<N; i++) {
    int pi = (who+i)%N;
    int next = (pi+1)%N;
    if(P[pi] > EPS) {
      my_pos++;
      bool best_set = false;
      result best;

      // Who should I shoot to maximize the chance I win?
      for(int j=0; j<N; j++) {
        int pj = (pi+j)%N;
        if(bit_set(live, pj)) {
          // Compute the rest of the game recursively
          result res = f(remove_bit(live, pj), next);
          if(!best_set || res.X[pi] > best.X[pi]) {
            best_set = true;
            best = res;
          }
        }
      }

      // Update winning probabilities and length
      // based on my best option
      for(int j=0; j<N; j++) {
        // The probability I shoot times
        // the probability you win if I shoot
        W[j] += P[pi]*best.X[j];
      }
      // The probability I shoot times
      // The number of people before me
      // plus the number of shots in the rest of the game
      turns += P[pi]*(my_pos+best.Y);
    }
  }

  return DP[live][who] = MP(W, turns);
}

int main() {
  vector<ll> FIB(N+2, 0);
  FIB[1] = 1;
  FIB[2] = 1;
  for(int i=3; i<=N+1; i++) {
    FIB[i] = FIB[i-1] + FIB[i-2];
  }
  for(int i=0; i<N; i++) {
    S[i] = ld(FIB[i+1]) / ld(FIB[N+1]);
  }

  // 0x3fff = everyone is alive
  // 0 = first player starts
  result res = f(0x3fff, 0);
  for(int i=0; i<N; i++) {
    // The probabilities that each player wins
    printf("%Lf\n", res.X[i]);
  }
  // The expected length of the game (the answer!)
  printf("%.8Lf\n", res.Y);
}