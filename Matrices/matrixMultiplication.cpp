// https://oj.vnoi.info/problem/atcoder_dp_r

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 50 + 1;

struct matrix {
    int v[MAX_N][MAX_N];

    matrix() {memset(v, 0, sizeof v);}

    matrix operator * (const matrix& x) const {
        matrix result;
        for (int i = 1; i < MAX_N; i++) for (int j = 1; j < MAX_N; j++) for (int k = 1; k < MAX_N; k++) {
            if ((result.v[i][j] += 1LL * v[i][k] * x.v[k][j] % MOD) >= MOD) result.v[i][j] -= MOD;
        }
        return result;
    }
};

matrix matrixPower(matrix a, long long b) {
    matrix result;
    for (int i = 1; i < MAX_N; i++) result.v[i][i] = 1;

    while (b > 0) {
        if (b & 1) result = result * a;

        a = a * a;

        b >>= 1;
    }

    return result;
}

int n; long long m;
matrix arr;

void Input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> arr.v[i][j];
}

void Process() {
    arr = matrixPower(arr, m);

    int result = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        if ((result += arr.v[i][j]) >= MOD) result -= MOD;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}
