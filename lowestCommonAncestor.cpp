#include <bits/stdc++.h>

#define fi first

#define se second

using namespace std;

const int MAX_N = 300000;


int n, LOG;

vector<pair<int, int>> adj[MAX_N + 1];

void Input() {
    cin >> n; LOG = log(n) / log(2);

    for (int i = 1; i < n; i++) {
        int u, v, c; cin >> u >> v >> c;

        adj[u].push_back({c, v}); adj[v].push_back({c, u});
    }
}


vector<int> high; vector<long long> dist; vector<vector<int>> par;

void Dfs(int u) {
    for (pair<int, int> v : adj[u]) if (v.se != par[u][0]) {
        high[v.se] = high[u] + 1; dist[v.se] = dist[u] + v.fi; par[v.se][0] = u;

        Dfs(v.se);
    }
}

int LCA(int u, int v) {
    if (high[u] < high[v]) return LCA(v, u);

    for (int j = LOG; j >= 0; j--) if (high[par[u][j]] >= high[v]) u = par[u][j];

    if (u == v) return u;

    for (int j = LOG; j >= 0; j--) if (par[u][j] != par[v][j]) u = par[u][j], v = par[v][j];

    return par[u][0];
}

void Process() {
    high.assign(n + 1, 0); high[0] = -1; dist.assign(n + 1, 0); par.assign(n + 1, vector<int> (LOG + 1, 0));

    Dfs(1);

    for (int j = 1; j <= LOG; j++) for (int i = 1; i <= n; i++) par[i][j] = par[par[i][j - 1]][j - 1];


    int q; cin >> q;

    while (q--) {
        int u, v; cin >> u >> v;

        cout << dist[u] + dist[v] - 2 * dist[LCA(u, v)] << '\n';
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}

/*-----
Input:
8
1 2 2
2 6 2
1 3 7
3 4 1
3 5 9
4 7 9
1 8 7
3
5 7
6 1
3 8
Output:
19
4
14
-----*/
