#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

typedef pair<int, int> PP;
typedef long long LL;
#define pb push_back
#define fr first
#define sc second

const LL maxn = 20000000;
LL t[maxn * 12 + 1];
typedef long long vec[3];

LL f(vec a, vec b) {
    LL sum_a = abs(a[0]) + abs(a[2]) + abs(a[1]);
    LL sum_b = abs(b[0]) + abs(b[2]) + abs(b[1]);

    if (b[2] < b[1]) swap(b[1], b[2]), swap(a[1], a[2]);
    if (a[2] > b[2]) swap(a, b), swap(sum_a, sum_b);
    
    LL sum = min(sum_a, sum_b);
    if (a[2] == 0) return sum;
    int k = b[2] / a[2];
    vec c = {b[0] - a[0] * k, b[1] - a[1] * k, b[2] - a[2] * k};
    if (abs(c[0]) + abs(c[1]) + abs(c[2]) < sum) sum = min(sum, f(c, a));
    for (int i = 0; i < 3; i ++) c[i] = a[i] - c[i];
    if (abs(c[0]) + abs(c[1]) + abs(c[2]) < sum) sum = min(sum, f(c, a));
    return sum;
}


int main() {
    t[2] = 1;
    for (LL i = 3; i < maxn * 12 + 1; i ++) t[i] = (t[i - 1] + t[i - 2] + t[i - 3]) % 10000000;
    LL res = 0;

    for (int i = 1; i <= maxn; i ++) {
        vec a = {t[12*i-11] - t[12*i-10], t[12*i-9] + t[12*i-8], t[12*i-7] * t[12*i-6]};
        vec b = {t[12*i- 5] - t[12*i- 4], t[12*i-3] + t[12*i-2], t[12*i-1] * t[12*i]};
        LL tmp = f(a, b);
        res += tmp;
    }
    cout << res << endl;

    return 0;
}