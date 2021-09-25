#include <pe.hpp>

const int64 mod = 1000000000;
const int64 mod2 = 2000000000;
const int64 mod6 = 6000000000;

#if 1
const int64 N = 1000000000000000000LL;
const int64 K = 1000000;
#else
const int64 N = 10000;
const int64 K = 10000;
#endif

int64 F[21000000];
struct Node {
  int pre, flag, ch[2];
  int64 s, e, cnt;
};

int64 cal(const int64 s, const int64 e, const int64 i) {
  const int64 delta = abs(s - e);
  const int64 is1 = (int128)delta % mod2 * (delta + 1) % mod2 / 2 % mod;
  const int64 is2 = (int128)delta % mod6 * (delta + 1) % mod6 *
                    ((2 * delta + 1) % mod6) % mod6 / 6 % mod;
  if (s <= e) {
    int64 t = (int128)i * s % mod * (delta + 1) % mod;
    t = add_mod(t, (i + s) % mod * is1 % mod, mod);
    t = add_mod(t, is2 % mod, mod);
    return t;
  } else {
    int64 t = (int128)i * s % mod * (delta + 1) % mod;
    t = add_mod(t, ((s - i) % mod + mod) % mod * is1 % mod, mod);
    t = sub_mod(t, is2 % mod, mod);
    return t;
  }
}

Node ns[3000500];
int top;
struct SplayTree {
  SplayTree() {
    top = 10;
    ns[0].ch[0] = 1;
    ns[0].cnt = N + 2;

    ns[1].pre = 0;
    ns[1].s = 0, ns[1].e = N - 1;
    ns[1].ch[0] = 2;
    ns[1].ch[1] = 3;
    ns[1].cnt = N + 2;

    ns[2].pre = 1;
    ns[2].s = -1, ns[2].e = -1;
    ns[2].cnt = 1;

    ns[3].pre = 1;
    ns[3].s = N, ns[3].e = N;
    ns[3].cnt = 1;
  }

  void push_down(int x) {
    Node& nd = ns[x];
    if (nd.flag == 1) {
      nd.flag = 0;
      if (nd.ch[0]) {
        ns[nd.ch[0]].flag ^= 1;
        swap(ns[nd.ch[0]].s, ns[nd.ch[0]].e);
      }
      if (nd.ch[1]) {
        ns[nd.ch[1]].flag ^= 1;
        swap(ns[nd.ch[1]].s, ns[nd.ch[1]].e);
      }
      swap(nd.ch[0], nd.ch[1]);
    }
  }

  void update(int x) {
    Node& nd = ns[x];
    Node &l = ns[nd.ch[0]], &r = ns[nd.ch[1]];
    int64 cnt = abs(nd.s - nd.e) + 1;
    if (nd.ch[0]) cnt += l.cnt;
    if (nd.ch[1]) cnt += r.cnt;
    nd.cnt = cnt;
  }

  void rotate(int x, int c) {
    int y = ns[x].pre;
    push_down(y), push_down(x);
    ns[y].ch[c ^ 1] = ns[x].ch[c];
    if (ns[x].ch[c]) ns[ns[x].ch[c]].pre = y;
    ns[x].pre = ns[y].pre;
    if (ns[ns[y].pre].ch[0] == y)
      ns[ns[y].pre].ch[0] = x;
    else
      ns[ns[y].pre].ch[1] = x;
    ns[x].ch[c] = y, ns[y].pre = x, update(y);
  }

  void splay(int x, int f) {
    for (push_down(x); ns[x].pre != f;)
      if (ns[ns[x].pre].pre == f)
        if (ns[ns[x].pre].ch[0] == x)
          rotate(x, 1);
        else
          rotate(x, 0);
      else {
        int y = ns[x].pre, z = ns[y].pre;
        if (ns[z].ch[0] == y)
          if (ns[y].ch[0] == x)
            rotate(y, 1), rotate(x, 1);
          else
            rotate(x, 0), rotate(x, 1);
        else if (ns[y].ch[1] == x)
          rotate(y, 0), rotate(x, 0);
        else
          rotate(x, 1), rotate(x, 0);
      }
    update(x);
  }

  int find(int64& key) {
    int curr = ns[0].ch[0];
    for (; curr;) {
      push_down(curr);
      int64 lsize = 0;
      if (ns[curr].ch[0]) {
        lsize = ns[ns[curr].ch[0]].cnt;
      }
      if (key <= lsize) {
        curr = ns[curr].ch[0];
        continue;
      }

      key -= lsize;
      int64 mesize = abs(ns[curr].e - ns[curr].s) + 1;
      if (key <= mesize) return curr;
      key -= mesize;
      curr = ns[curr].ch[1];
    }
    return curr;
  }

  int64 idx;
  int64 solve_impl(int r) {
    int64 ret = 0;
    push_down(r);
    if (ns[r].ch[0]) ret = add_mod(ret, solve_impl(ns[r].ch[0]), mod);
    if (idx >= 0 && idx < N) {
      ret = add_mod(ret, cal(ns[r].s, ns[r].e, idx), mod);
    }
    idx += abs(ns[r].s - ns[r].e) + 1;
    if (ns[r].ch[1]) ret = add_mod(ret, solve_impl(ns[r].ch[1]), mod);
    return ret;
  }
  int64 solve() {
    idx = -1;
    return solve_impl(ns[0].ch[0]);
  }
};

int main() {
  F[1] = F[2] = 1;
  for (int i = 3; i < 2100000; ++i) F[i] = (F[i - 1] + F[i - 2]) % N;

  SplayTree st;
  for (int id = 1; id <= K; ++id) {
    int64 s = F[id * 2 - 1], e = F[id * 2];
    if (s == e) continue;
    if (s > e) swap(s, e);
    // Make sure s is a start index of a node.
    // Make sure e is the end index of a node.
    for (int64 target : {s + 2, e + 3}) {
      int64 x = target;
      int id = st.find(x);
      if (x != 1) {
        st.splay(id, 0);
        int dir = ns[id].s <= ns[id].e ? 1 : -1;
        int64 olde = ns[id].e;
        ns[id].e = ns[id].s + dir * (x - 2);
        int z = ns[id].ch[1];
        st.push_down(z);
        while (ns[z].ch[0]) {
          z = ns[z].ch[0];
          st.push_down(z);
        }
        ns[z].ch[0] = top;
        ns[top].pre = z;
        ns[top].s = ns[id].e + dir;
        ns[top].e = olde;
        ns[top].cnt = abs(ns[top].s - ns[top].e) + 1;
        ns[top].flag = 0;
        ++top;
        do {
          st.update(z), z = ns[z].pre;
        } while (z != 0);
      }
    }

    int64 x = s + 1;
    const int id1 = st.find(x);
    st.splay(id1, 0);
    assert(x == abs(ns[id1].s - ns[id1].e) + 1);

    int64 y = e + 3;
    const int id2 = st.find(y);
    assert(y == 1);
    st.splay(id2, id1);

    const int id3 = ns[id2].ch[0];
    assert(id3 != 0);
    swap(ns[id3].s, ns[id3].e);
    ns[id3].flag ^= 1;
  }

  dbg(st.solve());
  return 0;
}
