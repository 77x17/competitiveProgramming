#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 77 * 17;


struct eulerianPathForDirectedGraph {
    struct Edge {
        int id;

        Edge(int _id) {id = _id;}
    };


    list<Edge> adj[MAX_N];

    int numVertices, numEdges;

    int degIn[MAX_N], degOut[MAX_N];

    void Init(int n, int m) {
        numVertices = n;  numEdges = m;

        memset(degIn, 0, sizeof degIn);  memset(degOut, 0, sizeof degOut);
    }

    void addEdge(int u, int v) {
        adj[u].push_front(v);

        degOut[u]++;  degIn[v]++;
    }


    vector<int> order;

    int dfsEdges = 0;

    void Dfs(int u) {
        while (adj[u].size()) {
            int v = adj[u].front().id;

            adj[u].pop_front();

            dfsEdges++;

            Dfs(v);
        }

        order.push_back(u);
    }

    void findEulerianPath(int s, int t) {
        bool ok = true;

        for (int i = 1; ok && i <= numVertices; i++) if (i != s && i != t) {
            if (degIn[i] - degOut[i] != 0) ok = false;
        }

        if (degOut[s] - degIn[s] != 1) ok = false;

        if (degIn[t] - degOut[t] != 1) ok = false;

        if (ok) {
            Dfs(s);

            if (dfsEdges == numEdges && order[0] == t) {
                reverse(order.begin(), order.end());

                for (int x : order) cout << x << " \n"[x == t];
            } else ok = false;
        }

        if (not ok) cout << "IMPOSSIBLE\n";
    }
} ePath;


struct eulerianPathForUnDirectedGraph {
    struct Edge {
        int id;

        list<Edge>::iterator it;

        Edge(int _id) {id = _id;}
    };


    list<Edge> adj[MAX_N];

    int numVertices, numEdges;

    int deg[2000], d[2000][2000];

    void Init(int n, int m) {
        numVertices = n;  numEdges = m;

        memset(deg, 0, sizeof deg);  memset(d, 0, sizeof d);
    }

    void addEdge(int u, int v, int c) {
        adj[u].push_front(Edge(v));  adj[v].push_front(Edge(u));

        adj[u].begin()->it = adj[v].begin();  adj[v].begin()->it = adj[u].begin();

        d[u][v] = c;  d[v][u] = c;

        deg[u]++;  deg[v]++;
    }


    vector<int> order;

    void Dfs(int u) {
        while (adj[u].size()) {
            int v = adj[u].front().id;

            adj[v].erase(adj[u].front().it);

            adj[u].pop_front();

            Dfs(v);
        }

        order.push_back(u);
    }


    bool minusWeight(int s) {
        int result = 0;

        for (int i = s; i < numEdges; i++) {
            result += d[order[i]][order[i + 1]];

            if (result < 0) return true;
        }

        for (int i = 0; i < s; i++) {
            result += d[order[i]][order[i + 1]];

            if (result < 0) return true;
        }

        return false;
    }

    void findEulerianPath(int s, int t) {
        bool ok = true;

        do {
            Dfs(s);

            s++;
        } while (order.size() == 0);

        for (int i = 1; ok && i <= numVertices; i++) {
            if (deg[i] & 1) ok = false;
        }

        ok = min(ok, order.size() == numEdges + 1);

        if (ok) {
            for (int x = 1; x <= numEdges; x++) if (not minusWeight(x)) {
                for (int i = x; i <= numEdges; i++) cout << order[i] << ' ';

                for (int i = 1; i <= x; i++) cout << order[i] << ' ';

                return;
            }
        }

        cout << "IMPOSSIBLE\n";
    }
};

int n, m;

void Input() {
    cin >> n >> m;  ePath.Init(n, m);

    for (int i = 1; i <= m; i++) {
        int u, v, c; cin >> u >> v;

        ePath.addEdge(u, v);
    }
}


void Process() {
    ePath.findEulerianPath(1, n);
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}
