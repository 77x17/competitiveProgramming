#include <bits/stdc++.h>
using namespace std;

const int MAX_N = (int)1e6 + 1;

const int N_MOD = 4;
const int MOD[] = {(int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277};
const int BASE = 256;

int pw[N_MOD][MAX_N];

void Prepare() {
    for (int j = 0; j < N_MOD; j++) {
        pw[j][0] = 1;

        for (int i = 1; i < MAX_N; i++) pw[j][i] = 1LL * pw[j][i - 1] * BASE % MOD[j];
    }
}

struct Hash {
    int val[N_MOD];

    Hash() {fill(val, val + N_MOD, 0);}
    Hash(char c) {fill(val, val + N_MOD, c);}

    Hash operator + (const Hash& x) const {
        Hash result;
        for (int j = 0; j < N_MOD; j++) {
            if ((result.val[j] = val[j] + x.val[j]) >= MOD[j]) result.val[j] -= MOD[j];
        }
        return result;
    }

    Hash operator - (const Hash& x) const {
        Hash result;
        for (int j = 0; j < N_MOD; j++) {
            if ((result.val[j] = val[j] - x.val[j]) < 0) result.val[j] += MOD[j];
        }
        return result;
    }

    Hash operator * (const int& k) const {
        Hash result;
        for (int j = 0; j < N_MOD; j++) {
            result.val[j] = 1LL * val[j] * pw[j][k] % MOD[j];
        }
        return result;
    }

    Hash operator < (const Hash& x) const {
        for (int j = 0; j < N_MOD; j++) if (val[j] != x.val[j]) return val[j] < x.val[j];

        return false;
    }

    bool operator == (const Hash& x) const {
        for (int j = 0; j < N_MOD; j++) if (val[j] != x.val[j]) return false;

        return true;
    }
};

string A, B; int n, m;

void Input() {
    cin >> A >> B;
    n = A.size(), m = B.size();
}

Hash s[MAX_N], t[MAX_N];

Hash getHash(int l, int r, Hash arr[]) {
    return (arr[r] - arr[l - 1]) * (n - r);
}

void Process() {
    if (A.size() < B.size()) return;

    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + Hash(A[i - 1]) * i;
    for (int i = 1; i <= m; i++) t[i] = t[i - 1] + Hash(B[i - 1]) * i;

    for (int i = 1; i + m - 1 <= n; i++) {
        if (getHash(1, m, t) == getHash(i, i + m - 1, s)) cout << i << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();
    Prepare();
    Process();

    return 0;
}
