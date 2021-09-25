bool is_square;
LL a, b, c;
LL c_root;

struct Lattice {
    LL s, t;
    Lattice(): s(0), t(0) {}
    explicit Lattice(int it) {
        if (it == 0) s = b, t = 0;
        else if (it == 1) s = a, t = 0;
        else if (it == 2) s = 0, t = 1;
        else if (it == 3) s = a*b, t = 0;
        else assert(0);
    }
    bool is_pos() { // strictly
        LL u = s;
        LL v = a*b*t;
        if (v == 0) return u > 0;
        if (u == 0) return v > 0;
        if (u > 0 and v > 0) return true;
        if (u < 0 and v < 0) return false;
        assert(u < 1ll<<50 and v < 1ll<<50); 
        __int128 x = c*u*((__int128)u);
        __int128 y = v*((__int128)v);
        if (u > 0) return x > y;
        return y > x;
    }
    bool is_zero() {
        LL u = s;
        LL v = a*b*t;
        if (!is_square) return u == 0 and v == 0;
        else return u*c_root + v == 0;
    }
    void simplify() {
        if (is_square) {
            s += (t / c_root)*(a*b);
            t %= c_root;
        }
    }
};

Lattice operator+(Lattice A, Lattice B) {
    A.s += B.s, A.t += B.t;
    A.simplify();
    return A;
}

Lattice operator-(Lattice A, Lattice B) {
    A.s -= B.s, A.t -= B.t;
    A.simplify();
    return A;
}

bool operator<(Lattice A, Lattice B) {
    return (B-A).is_pos();
}

bool operator>(Lattice A, Lattice B) {
    return (A-B).is_pos();
}

bool operator<=(Lattice A, Lattice B) {
    return !(A>B);
}

bool operator>=(Lattice A, Lattice B) {
    return !(A<B);
}

bool operator==(Lattice A, Lattice B) {
    return (A-B).is_zero();
}

bool operator!=(Lattice A, Lattice B) {
    return !(A == B);
}

template<typename T>
struct GoodList {
    deque<T> vec;
    bool reversed;
    T val;

    GoodList(): vec{}, reversed(false), val{} {}
    int size() {
        return vec.size();
    }
    T front() {
        return (reversed?(val-vec.back()):(vec.front()+val));
    }
    T back() {
        return (reversed?(val-vec.front()):(vec.back()+val));
    }
    T operator[](int id) {
        return (reversed?(val-vec[size()-1-id]):(vec[id]+val));
    }
    void reverse(T z) { // Apply x-> z-x and reverse.
        val = z-val;
        reversed = !reversed;
    }
    void push_back(T x) {
        if (reversed) vec.push_front(val-x);
        else vec.push_back(x-val);
    }
    void push_front(T x) {
        if (reversed) vec.push_back(val-x);
        else vec.push_front(x-val);
    }
    void pop_back() {
        if (reversed) vec.pop_front();
        else vec.pop_back();
    }
    void pop_front() {
        if (reversed) vec.pop_back();
        else vec.pop_front();
    }
};

template<typename T>
struct BestList {
    deque<GoodList<T>*> vec; // Keep only nonempty Goodlists
    int sz;
    int operation_before_rebuild;
    BestList() {}
    BestList(vector<T> vals) {
        sz = vals.size();
        vec = {new GoodList<T>()};
        for (auto x : vals) vec.front()->push_back(x);
        operation_before_rebuild = 0;
        Rebuild();
    }
    
    int size() {
        return sz;
    }
    void push_front(T x) {
        vec.front()->push_front(x);
        sz++;
        Rebuild();
    }
    T front() {
        return vec.front()->front();
    }
    int reverse_below(T x, T c) { // y - > c-y if y < x.
        int it = 0;
        int ans = 0;
        while (vec[it]->back() < x) it++;
        if (vec[it]->front() < x) {
            vec.push_back(new GoodList<T>());
            while (ans < vec[it]->size() and (*vec[it])[ans] < x) ans++;
            for (int i = ans-1; i >= 0; i--) vec.back()->push_back(c-(*vec[it])[i]);
            while (vec[it]->size() > 0 and vec[it]->front() < x) vec[it]->pop_front();
        }
        for (int i = it-1; i >= 0; i--) {
            ans += vec[i]->size();
            vec.push_back(vec[i]);
            vec.back()->reverse(c);
        }
        vec.erase(vec.begin(), vec.begin() + it);
        if (vec.front()->size() == 0) vec.pop_front();
        Rebuild();
        return ans;
    }

    deque<T> debugging() {
        deque<T> res;
        int pos = 0;
        int id = 0;
        for (int i = 0; i < sz; i++) {
            if (id == vec[pos]->size()) pos++, id = 0;
            res.push_back((*vec[pos])[id]);
            id++;
        }
        for (int i = 0; i < sz-1; i++) assert(res[i] < res[i+1]);
        return res;
    }
    
    void Rebuild() {
        operation_before_rebuild--;
        if (operation_before_rebuild > 0) return;
        int bucket = 2*sqrt(sz) + 10;
        deque<GoodList<T>*> new_vec = {new GoodList<T>()};
        int pos = 0;
        int id = 0;
        for (int i = 0; i < sz; i++) {
            if (id == vec[pos]->size()) pos++, id = 0;
            if (new_vec.back()->size() == bucket) new_vec.push_back(new GoodList<T>());
            new_vec.back()->push_back((*vec[pos])[id]);
            id++;
        }
        for (auto& pointer: vec) delete pointer;
        vec = new_vec;
        
        operation_before_rebuild = bucket * 1.5;
    }
};

int evolve(int it, BestList<Lattice>& vec) { // vec contains {0, 1} (shifted)
    Lattice zero = vec.front();
    Lattice one(3);
    Lattice A(it);
    Lattice S = zero + zero + one + A;

    int ans = vec.reverse_below(zero+A, S);
    assert(!(vec.front() < zero + A));
    if (vec.front() != zero + A) vec.push_front(zero + A);

    return ans;
}

vector<int> fast_splitting() {
    BestList<Lattice> vec({Lattice(), Lattice(3)});

    int cnt = 0;
    while(1) {
        cnt++;
        int sz_before = vec.size();
        for (int it = 0; it < 3; it++) evolve(it, vec);
        if (SZ(vec) == sz_before) {
            vector<int> res = {SZ(vec)-1};
            for (int it = 0; it < 3; it++) res.push_back(evolve(it, vec));
            return res;
        }
    }
}



// // PERMUTATIONS // //
vector<int> construct_perm(int N, int x) {
    vector<int> P(2*N);
    for (int i = 0; i < x; i++) {
        P[i] = 2*N-1-i;
        P[N+i] = N-1-i;
    }
    for (int i = x; i < N; i++) {
        P[i] = i-x;
        P[N+i] = N+i-x;
    }
    return P;
}

// A[0] = 0
pair<LL, LL> matching_rotation(int N, vector<int> A, vector<int> B) {
    // Quadratic implementation, should be sufficient
    if (A.size() != B.size()) {
        return {-1, -1};
    }
    int L = A.size();
    int ff = -1, ss = -1;
    for (int p = 0; p < L; p++) {
        bool works = true;
        int diff = B[p%L] - A[0];
        for (int i = 1; i < L and works; i++) {
            works &= B[(p+i)%L] == (A[i] + diff)%N;
        }
        if (works) {
            if (ff == -1) ff = diff;
            else {
                ss = diff-ff;
                break;
            }
        }
    }
    if (ff == -1) return {-1, -1};
    if (ss == -1) ss = N;
    return {ff, ss};
}

LL fixed_points(vector<int> U, vector<int> P) {
    int N = U.size(); // P has size 2N.
    vector<bool> source(2*N, false);
    vector<bool> sink(2*N, false);
    for (int i = 0; i < N; i++) source[U[i]] = true, sink[i] = true;
    vector<bool> visited(2*N, false);
    vector<pair<LL,LL>> crt;
    for (int i = 0; i < 2*N; i++) {
        if (visited[i] or !source[i]) continue;
        int j = i;
        vector<int> A;
        vector<int> B;
        int cnt = 0;
        while (!visited[j]) {
            cnt++;
            visited[j] = true;
            if (source[j]) A.push_back(cnt-1);
            if (sink[j]) B.push_back(cnt-1);
            j = P[j];
        }
        pair<LL, LL> mr = matching_rotation(cnt, A, B);
        if (mr.first == -1) return 1e18;
        crt.push_back(mr);
    }
    pair<LL, LL> res = SolveRemainderSystem(crt);
    if (res.first == -1) return 1e18;
    if (res.first == 0) res.first += res.second;
    return res.first;
}

// First apply A, then B.
vector<int> compose(vector<int> A, vector<int> B) {
    int N = A.size();
    vector<int> C(N);
    for (int i = 0; i < N; i++) C[i] = B[A[i]];
    return C;
}

LL get_period(int N, int x, int y, int z) {
    vector<int> Px = construct_perm(N, x);
    vector<int> Py = construct_perm(N, y);
    vector<int> Pz = construct_perm(N, z);
    vector<int> U(N);
    for (int i = 0; i < N; i++) U[i] = i;
    LL res0 = 3*fixed_points(U, compose(compose(Px, Py), Pz));
    for (int i = 0; i < N; i++) U[i] = Px[U[i]];
    LL res1 = 1 + 3*fixed_points(U, compose(compose(Py, Pz), Px));
    for (int i = 0; i < N; i++) U[i] = Py[U[i]];
    LL res2 = 2 + 3*fixed_points(U, compose(compose(Pz, Px), Py));
    return min(res0, min(res1, res2));
}


LL sub_solve(int a, int b, int c) {
    ::a = a, ::b = b, ::c = c;
    c_root = sqrt(c+0.5);
    is_square = c_root*c_root == c;
    vector<int> res = fast_splitting();
    return get_period(res[0], res[1], res[2], res[3]);
}

LL solve(int n) {
    LL res = 0;
    for (int a = 9; a <= n; a++) {
        for (int b = a+1; b <= n; b++) {
            for (int c = b+1; c <= n; c++) {
                LL ris = sub_solve(a, b, c);
                res += ris;
            }
        }
    }
    return res;
}

int main() {
    cout << solve(53) << endl;
}