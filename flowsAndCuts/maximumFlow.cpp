#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

const int MAX_N = 1e5 + 77 * 17;


struct maximumFlow {
    struct Edge {
        int from, to, capa, flow;

        Edge(int _from = 0, int _to = 0, int _capa = 0) {
            from = _from, to = _to, capa = _capa;
        }

        int remain() {return capa - flow;}
    };

    vector<Edge> edges;  vector<int> adj[MAX_N];

    void addEdge(int u, int v, int c) {
        adj[u].push_back(edges.size());  edges.push_back(Edge(u, v, c));

        adj[v].push_back(edges.size());  edges.push_back(Edge(v, u, 0));
    }

    int d[MAX_N], par[MAX_N];

    bool findPath(int s, int t) {
        memset(d, -1, sizeof d);  memset(par, -1, sizeof par);

        queue<int> q; q.push(s);  d[s] = 0;

        while (q.size()) {
            int u = q.front(); q.pop();

            for (int id : adj[u]) if (edges[id].remain() > 0) {
                int v = edges[id].to;

                if (d[v] == -1) {
                    d[v] = d[u] + 1;

                    par[v] = id;

                    q.push(v);
                }
            }
        }

        return d[t] >= 0;
    }

    int findMaximumFlow(int s, int t) {
        for (Edge &x : edges) x.flow = 0;

        int result = 0;

        while (findPath(s, t)) {
            int delta = INF;

            for (int i = t; i != s; i = edges[par[i]].from) {
                delta = min(delta, edges[par[i]].remain());
            }

            for (int i = t; i != s; i = edges[par[i]].from) {
                edges[par[i]].flow += delta;

                edges[par[i] ^ 1].flow -= delta;
            }

            result += delta;
        }

        return result;
    }
} F;


int n, m, s, t;

void Input() {
    cin >> n >> m >> s >> t;

    for (int i = 1; i <= m; i++) {
        int u, v, c; cin >> u >> v >> c;

        F.addEdge(u, v, c);
    }
}


void Process() {
    cout << F.findMaximumFlow(s, t) << '\n';
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}
