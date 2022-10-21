// https://oj.vnoi.info/problem/nkbm

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = (int)2e3 + 1;

struct MaximumMatching {
    struct edge {
        int from, to, capa, flow;

        edge (int _from = 0, int _to = 0, int _capa = 0) {
            from = _from, to = _to, capa = _capa, flow = 0;
        }

        int residual() {return capa - flow;}
    };

    vector<edge> edges; vector<int> adj[MAX_N];

    void addEdge(int u, int v, int c) {
        adj[u].push_back(edges.size()); edges.push_back(edge(u, v, c));
        adj[v].push_back(edges.size()); edges.push_back(edge(v, u, 0));
    }

    int d[MAX_N], par[MAX_N];

    bool findPath(int s, int t) {
        memset(d, -1, sizeof d); memset(par, -1, sizeof par);

        queue<int> q; q.push(s); d[s] = 0;
        while (q.size() && q.front() != t) {
            int u = q.front(); q.pop();

            for (int x : adj[u]) if (edges[x].residual() > 0) {
                int v = edges[x].to;

                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    par[v] = x;
                    q.push(v);
                }
            }
        }

        return d[t] != -1;
    }

    int main(int s, int t) {
        int result = 0;

        while (findPath(s, t)) {
            int delta = INT_MAX;

            for (int x = t; x != s; x = edges[par[x]].from) {
                delta = min(delta, edges[par[x]].residual());
            }

            for (int x = t; x != s; x = edges[par[x]].from) {
                edges[par[x]].flow += delta;
                edges[par[x] ^ 1].flow -= delta;
            }

            result += delta;
        }

        return result;
    }
} mm;

int X, Y, M;

void Input() {
    cin >> X >> Y >> M;
    for (int i = 1; i <= M; i++) {
        int x, y; cin >> x >> y;

        mm.addEdge(x, y + X, 1);
    }
}

void Prepare() {
    for (int i = 1; i <= X; i++) mm.addEdge(0, i, 1);
    for (int i = 1; i <= Y; i++) mm.addEdge(i + X, X + Y + 1, 1);
}

void Process() {
    cout << mm.main(0, X + Y + 1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();
    Prepare();
    Process();

    return 0;
}
