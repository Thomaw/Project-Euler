struct board {
    static const int EMPTY = 0;
    static const int TRI_UL = 1;
    static const int TRI_UR = 2;
    static const int TRI_BL = 3;
    static const int TRI_BR = 4;
    static const int FULL = 5;

    int n, m;
    int t[10][10];

    static int combine(int t1, int t2) {
        if (t1 == EMPTY || t2 == EMPTY) return t1 + t2;
        return (t1 + t2 == FULL) ? FULL : -1;
    }
};

struct pattern {
    struct cell {
        int i, j;
        int t;
    };
    vector<cell> v;
};

vector<pattern> patterns {
    { { { 0, 0, board::FULL } } },
    { { { 0, 0, board::TRI_UL }, { 0, -1, board::TRI_BR } } },
    { { { 0, 0, board::TRI_UR }, { 0, +1, board::TRI_BL } } },
    { { { 0, 0, board::TRI_BL }, { +1, 0, board::TRI_UR } } },
    { { { 0, 0, board::TRI_BL }, { 0, -1, board::TRI_UR } } },
    { { { 0, 0, board::TRI_BL }, { 0, -1, board::TRI_BR }, { +1, -1, board::TRI_UR }, { +1, 0, board::TRI_UL } } },
    { { { 0, 0, board::TRI_BR }, { +1, 0, board::TRI_UL } } },
    { { { 0, 0, board::TRI_BR }, { 0, +1, board::TRI_UL } } },
    { { { 0, 0, board::TRI_BR }, { 0, +1, board::TRI_BL }, { +1, 0, board::TRI_UR }, { +1, +1, board::TRI_UL } } },
};


void print(const board& brd) {
    for (int i = 0; i < brd.n; i++) {
        for (int j = 0; j < brd.m; j++) {
            printf("%d", brd.t[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

board oct_board(int a, int b) {
    board brd;
    brd.n = brd.m = a + b * 2;
    for (int i = 0; i < brd.n; i++) {
        for (int j = 0; j < brd.m; j++) {
            brd.t[i][j] = board::EMPTY;
        }
    }
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < b - 1 - i; j++) {
            brd.t[i][j] = board::FULL;
            brd.t[i][brd.m - 1 - j] = board::FULL;
            brd.t[brd.n - 1 - i][j] = board::FULL;
            brd.t[brd.n - 1 - i][brd.m - 1 - j] = board::FULL;
        }
        brd.t[i][b - 1 - i] = board::TRI_UL;
        brd.t[i][brd.m - b + i] = board::TRI_UR;
        brd.t[brd.n - 1 - i][b - 1 - i] = board::TRI_BL;
        brd.t[brd.n - 1 - i][brd.m - b + i] = board::TRI_BR;
    }
    return brd;
}

board rot_board(const board& brd) {
    static const int rot_map[] = { 0, 3, 1, 4, 2, 5 };
    board ret;
    ret.n = brd.m;
    ret.m = brd.n;
    for (int i = 0; i < brd.n; i++) {
        for (int j = 0; j < brd.m; j++) {
            ret.t[brd.m - 1 - j][i] = rot_map[brd.t[i][j]];
        }
    }
    return ret;
}

board sub_board(const board& brd, int i0, int j0, int n, int m) {
    board ret;
    ret.n = n;
    ret.m = m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ret.t[i][j] = brd.t[i0 + i][j0 + j];
        }
    }
    return ret;
}

int fit_pattern(const board& brd, int i0, int j0, const pattern& pat) {
    for (const auto& c : pat.v) {
        int i = i0 + c.i, j = j0 + c.j;
        if (i < 0 || j < 0 || i >= brd.n || j >= brd.m) return 0;
        if (board::combine(brd.t[i][j], c.t) < 0) return 0;
    }
    return 1;
}

void add_pattern(board& brd, int i0, int j0, const pattern& pat) {
    for (const auto& c : pat.v) {
        brd.t[i0 + c.i][j0 + c.j] += c.t;
    }
}

void sub_pattern(board& brd, int i0, int j0, const pattern& pat) {
    for (const auto& c : pat.v) {
        brd.t[i0 + c.i][j0 + c.j] -= c.t;
    }
}

int64_t calc(board& brd, int i = 0, int k = 0) {
    if (brd.n == 0 || brd.m == 0) return 1;
    int j = brd.m / 2;
    while (i < brd.n && brd.t[i][j] == board::FULL) i++, k = 0;
    if (i >= brd.n) {
        auto r1 = calc(rot_board(sub_board(brd, 0, j + 1, brd.n, brd.m - j - 1)));
        if (r1 == 0) return 0;
        return r1 * calc(rot_board(sub_board(brd, 0, 0, brd.n, j)));
    }
    int64_t r = 0;
    for (; k < patterns.size(); k++) {
        const auto& pat = patterns[k];
        if (!fit_pattern(brd, i, j, pat)) continue;
        add_pattern(brd, i, j, pat);
        r += calc(brd, i, k + 1);
        sub_pattern(brd, i, j, pat);
    }
    return r;
}

int main() {
    auto brd = oct_board(4, 2);
    int64_t r = calc(brd);
    printf("%lld %d ms\n", r, clock());
    return 0;
}