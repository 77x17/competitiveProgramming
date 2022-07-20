#include <bits/stdc++.h>

using namespace std;


int n, x;  vector<int> w, c;  //weight - cost

void Input() {
    cin >> n >> x;

    w.assign(n + 1, 0); for (int i = 1; i <= n; i++) cin >> w[i];

    c.assign(n + 1, 0); for (int i = 1; i <= n; i++) cin >> c[i];
}


vector<int> dp[2];

void Process() {
    dp[0].assign(x + 1, 0);  dp[1].assign(x + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= x; j++) {
            dp[1][j] = dp[0][j];

            if (j - w[i] >= 0) dp[1][j] = max(dp[1][j], dp[0][j - w[i]] + c[i]);
        }

        for (int j = 1; j <= x; j++) dp[0][j] = dp[1][j];
    }

    cout << dp[1][x] << '\n';
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}

/* https://cses.fi/problemset/task/1140 */
