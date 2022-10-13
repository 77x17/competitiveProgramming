#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 1;

struct FenwickTree {
    int n, val[MAX_N];

    void Init(int _n) {
        n = _n;

        fill(val + 1, val + _n + 1, 0);
    }

    void Update(int x, int v) {
        for (; x <= n; x += x & -x) val[x] += v;
    }

    int Get(int x) {
        int result = 0;
        for (; x >= 1; x -= x & -x) result += val[x];
        return result;
    }
} bit;

int n;

void Input() {
    cin >> n;
}

void Process() {
    bit.Init(n);

    int q; cin >> q; while (q--) {
        int k; cin >> k;

        if (k == 0) {
            int x, v; cin >> x >> v;

            bit.Update(x, v);
        }

        if (k == 1) {
            int x; cin >> x;

            cout << bit.Get(x) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}
