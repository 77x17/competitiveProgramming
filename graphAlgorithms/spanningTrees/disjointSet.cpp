#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 77 * 17;


int n, q, arr[MAX_N];

void Input() {
    cin >> n >> q;  for (int i = 1; i <= n; i++) cin >> arr[i];
}


struct disjointSet {
    int par[MAX_N];

    void Init(int n) {
        for (int i = 1; i <= n; i++) par[i] = -1;
    }

    int findRoot(int x) {
        if (par[x] < 0) return x;

        return par[x] = findRoot(par[x]);
    }

    void Union(int x, int y) {
        if ((x = findRoot(x)) == (y = findRoot(y))) return;

        if (par[x] > par[y]) swap(x, y);

        par[x] += par[y];
        par[y] = x;
    }
} DSU;

vector<int> adj[MAX_N];

void Process() {
    DSU.Init(n);

    for (int i = 1; i <= n; i++) adj[arr[i]].push_back(i);

    while (q--) {
        int e, u, v; cin >> e >> u >> v;

        if (e == 1) DSU.Union(u, v);
        else {
            int result = 0, target = DSU.findRoot(u);

            for (int x : adj[v]) if (DSU.findRoot(x) == target) result++;

            cout << result << '\n';
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}

/* https://oj.vnoi.info/problem/colquery */
