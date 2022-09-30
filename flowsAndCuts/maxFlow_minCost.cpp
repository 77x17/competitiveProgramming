//https://oj.vnoi.info/problem/mincost

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int MAX_N = 1000 + 1;

struct minCostFlow {
    struct Edge {
        int from, to, capa, cost, flow;

        Edge (int _from = 0, int _to = 0, int _capa = 0, int _cost = 0) {
            from = _from, to = _to, capa = _capa, cost = _cost, flow = 0;
        }

        int remain() {return capa - flow;}
    };

    vector<Edge> edges; vector<int> adj[MAX_N];

    void addEdge(int u, int v, int c, int w) {
        adj[u].push_back(edges.size()); edges.push_back({u, v, c, +w});
        adj[v].push_back(edges.size()); edges.push_back({v, u, 0, -w});
    }

    bool in_queue[MAX_N];
    int d[MAX_N], par[MAX_N];

    bool findPath(int s, int t) {
        fill(in_queue, in_queue + MAX_N, false);
        fill(d, d + MAX_N, INF); fill(par, par + MAX_N, -1);

        queue<int> q; q.push(s); d[s] = 0; in_queue[s] = true;

        while (q.size()) {
            int u = q.front(); q.pop(); in_queue[u] = false;

            for (int x : adj[u]) if (edges[x].remain()) {
                int v = edges[x].to, w = edges[x].cost;

                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w; par[v] = x;

                    if (not in_queue[v]) q.push(v), in_queue[v] = true;
                }
            }
        }

        return d[t] != INF;
    }

    array<int, 2> maxFlow_minCost(int s, int t) {
        int maxFlow = 0, minCost = 0;

        while (findPath(s, t)) {
            int delta = INF;

            for (int x = t; x != s; x = edges[par[x]].from) {
                delta = min(delta, edges[par[x]].remain());
            }

            for (int x = t; x != s; x = edges[par[x]].from) {
                edges[par[x]].flow += delta;
                edges[par[x] ^ 1].flow -= delta;
            }

            maxFlow += delta;
            minCost += delta * d[t];
        }

        return {maxFlow, minCost};
    }

    void printEdges() {
        for (Edge x : edges) if (x.flow > 0 && x.from >= 1) cout << x.from << ' ' << x.to << ' ' << x.flow << '\n';

        cout << "0 0 0\n";
    }
} mcf;

int n, m, k, s, f;

void Input() {
    cin >> n >> m >> k >> s >> f;

    for (int i = 1; i <= m; i++) {
        int u, v, w, c; cin >> u >> v >> w >> c;

        mcf.addEdge(u, v, c, w); mcf.addEdge(v, u, c, w);
    }

    mcf.addEdge(0, s, k, 0);
}

void Process() {
    array<int, 2> result = mcf.maxFlow_minCost(0, f);

    if (result[0] < k) {
        cout << -1 << '\n';

        return;
    }

    cout << result[1] << '\n';

    mcf.printEdges();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}

