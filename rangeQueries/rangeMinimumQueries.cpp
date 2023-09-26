#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 77 * 17;

const int MAX_N = 200000 + 77 * 17;

const int LOG = 20;


int n, arr[MAX_N];

void Input() {
    cin >> n;  for (int i = 1; i <= n; i++) cin >> arr[i];
}


int sparse[MAX_N][LOG];

int getMin(int l, int r) {
    int k = log(r - l + 1) / log(2);

    return min(sparse[l][k], sparse[r - (1 << k) + 1][k]);
}

void buildSparseTable() {
    for (int k = 0; k < LOG; k++) {
        for (int i = 1; i <= n; i++) sparse[i][k] = INF;
    }

    for (int i = 1; i <= n; i++) sparse[i][0] = arr[i];

    for (int k = 0; k < LOG; k++) {
        for (int i = 1; i + (1 << (k)) <= n; i++) {
            sparse[i][k + 1] = min(sparse[i][k], sparse[i + (1 << k)][k]);
        }
    }
}

void Process() {
    buildSparseTable();

    int q; cin >> q; while (q--) {
        int l, r; cin >> l >> r;

        cout << getMin(l + 1, r + 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}

/* https://www.spoj.com/problems/RMQSQ/ */
