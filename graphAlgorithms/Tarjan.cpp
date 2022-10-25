#include <bits/stdc++.h>
using namespace std;

const int MAX_N = (int)1e4 + 1;

int n, m;
vector<int> adj[MAX_N];

void Input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;

        adj[u].push_back(v);
    }
}

stack<int> s;
int result = 0, dfs_time = 0, low[MAX_N], num[MAX_N];

void Dfs(int u) {
    low[u] = num[u] = ++dfs_time;
    s.push(u);

    for (int v : adj[u]) {
        if (num[v] == 0) {
            Dfs(v);

            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], num[v]);
    }

    if (low[u] == num[u]) {
        result++;

        int v;

        do {
            v = s.top(), s.pop();

            low[v] = num[v] = n + 1;
        } while (v != u);
    }
}

void Process() {
    fill(low + 1, low + n + 1, n + 1);
    fill(num + 1, num + n + 1, 0);

    for (int i = 1; i <= n; i++) if (num[i] == 0) Dfs(i);

    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}
