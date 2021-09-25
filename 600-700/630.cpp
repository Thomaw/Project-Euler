#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

using Line = pair<pair<int, int>, pair<int, int>>;

bool is_the_same(const Line& l1, const Line& l2) {
    return (l1.second.first - l1.first.first) * (l2.second.second - l2.first.second) == (l2.second.first - l2.first.first) * (l1.second.second - l1.first.second) &&
        (l1.second.first - l1.first.first) * (l2.second.second - l1.first.second) == (l2.second.first - l1.first.first) * (l1.second.second - l1.first.second);
}

bool is_less(const Line& l1, const Line& l2) {
    const int a = (l1.second.first - l1.first.first) * (l2.second.second - l2.first.second);
    const int b = (l2.second.first - l2.first.first) * (l1.second.second - l1.first.second);
    return a < b || (a == b &&
        (l1.second.first - l1.first.first) * (l2.second.second - l1.first.second) > (l2.second.first - l1.first.first) * (l1.second.second - l1.first.second));
}

bool is_parallel(const Line& l1, const Line& l2) {
    return (l1.second.first - l1.first.first) * (l2.second.second - l2.first.second) == (l2.second.first - l2.first.first) * (l1.second.second - l1.first.second);
}

int main() {
    constexpr int len = 2500;
    vector<int> t;
    long s = 290797;
    for (int i = 0; i < len * 2; ++i) {
        s = (s * s) % 50515093L;
        t.push_back(int(s % 2000) - 1000);
    }

    vector<Line> lines;
    for (int i = 0; i < len * 2 - 2; i += 2) {
        pair<int, int> point1 = make_pair(t[i], t[i + 1]);
        for (int j = i + 2; j < len * 2; j += 2) {
            pair<int, int> point2 = make_pair(t[j], t[j + 1]);
            lines.push_back(point1 < point2 ? make_pair(point1, point2) : make_pair(point2, point1));
        }
    }

    // Remove duplicate lines.
    cout << "Lines: " << lines.size() << endl;
    sort(lines.begin(), lines.end(), [](const Line& l1, const Line& l2){ return is_less(l1, l2); });
    lines.erase(unique(lines.begin(), lines.end(), is_the_same), lines.end());

    cout << "Without duplicates: " << lines.size() << endl;

    // Calculate crosses. All lines except parallels are crossing. All parallel lines are adjacent due to sorting comparison
    long amount = 0;
    for (size_t i = 0; i < lines.size() - 1; ++i) {
        for (size_t j = i + 1; j < lines.size(); ++j) {
            if (!is_parallel(lines[i], lines[j])) {
                amount += (lines.size() - j) * 2;
                break;
            }
        }
    }

    cout << "Answer: " << amount << endl;
}
