#include <bits/stdc++.h>
using namespace std;

#define edge pair<int, int>
#define fi first
#define se second

const int MAX_N = (int)1e5 + 1;

int n, m;
vector<edge> adj[MAX_N];

void Input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;

        adj[u].push_back(make_pair(v, i)); adj[v].push_back(make_pair(u, i));
    }
}

int cnt = 0, low[MAX_N], id[MAX_N], nChild[MAX_N];
bool visited[MAX_N], isCut[MAX_N], isBridge[MAX_N];

void Dfs(int u) {
    id[u] = ++cnt;

    for (edge x : adj[u]) if (not visited[x.se]) {
        int v = x.fi, i = x.se;

        visited[i] = true;

        if (id[v] == 0) {
            nChild[u]++;

            Dfs(v);

            low[u] = min(low[u], low[v]);

            if (low[v] > id[u]) isBridge[i] = true;
            if (low[v] >= id[u]) isCut[u] = true;
        } else low[u] = min(low[u], id[v]);
    }
}

void Process() {
    fill(low + 1, low + n + 1, n + 1); fill(id + 1, id + n + 1, 0); fill(nChild + 1, nChild + n + 1, 0);
    fill(visited + 1, visited + m + 1, false); fill(isCut + 1, isCut + n + 1, false); fill(isBridge + 1, isBridge + m + 1, false);

    for (int i = 1; i <= n; i++) if (id[i] == 0) {
        Dfs(i);

        if (nChild[i] == 1) isCut[i] = false;
    }

    int result = 0;
    for (int i = 1; i <= n; i++) result += isCut[i];
    cout << result << ' ';

    result = 0;
    for (int i = 1; i <= m; i++) result += isBridge[i];
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}
