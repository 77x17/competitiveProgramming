#include <bits/stdc++.h>

#define fi first

#define se second

using namespace std;

const int MAX_N = 100000;

const long long INF = 1e18 + 7;

int n, m;

vector<pair<int, int>> adj[MAX_N + 1];

void Input() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, c; cin >> u >> v >> c;

        adj[u].push_back({c, v});
    }
}


vector<long long> dist;

void Dijkstra(int s) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist.assign(n + 1, INF); dist[s] = 0; pq.push({0, s});

    while (pq.size()) {
        pair<long long, int> u = pq.top(); pq.pop();

        if (u.fi == dist[u.se]) for (pair<int, int> v : adj[u.se]) {
            if (dist[v.se] > dist[u.se] + v.fi) {
                dist[v.se] = dist[u.se] + v.fi;

                pq.push({dist[v.se], v.se});
            }
        }
    }
}

void Process() {
    Dijkstra(1);

    for (int i = 1; i <= n; i++) cout << dist[i] << ' '; cout << '\n';
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}

/* https://cses.fi/problemset/task/1671 */
