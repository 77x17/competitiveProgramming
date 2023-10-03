#include <bits/stdc++.h>
using namespace std;
 
const long long INF = 1e18;
 
struct edge {
	int from;
	int to;
	int weight;
};
 
int n, m;
vector<edge> edges;
vector<vector<int>> adj;
 
int cycle;
vector<long long>  d;		// distance
vector<int> 	   p;		// parent
vector<int>     path;	
vector<bool> visited;	
 
void Dfs(int u) {
	visited[u] = true;
 
	for (int v : adj[u]) if (not visited[v]) Dfs(v);
}
 
bool connect(int u) {
	int x = u;
	for (int i = 1; i <= n; i++) x = p[x];
 
	path = vector<int>();
	for (int cur = x; ; cur = p[cur]) {
		path.push_back(cur);
		if (cur == x && path.size() >= 2) break;
	}
 
	visited.assign(n + 1, false);
	for (int y : path) if (not visited[y]) Dfs(y);
 
	return (visited[1] || visited[n]);
}
 
void Bellman_Ford() {
	d.assign(n + 1, INF);
	p.assign(n + 1, -1);
 
	d[1] = 0;
	for (int i = 1; i <= n; i++) {
		cycle = -1;
		for (edge x : edges) if (d[x.from] != INF) {
			if (d[x.to] > d[x.from] + x.weight) {
				d[x.to] = max(-INF, d[x.from] + x.weight);
				p[x.to] = x.from;
 
				if (i == n && connect(x.to)) cycle = x.to;
			}
		}
	}
 
	if (cycle == -1) {
		cout << -1 * d[n] << '\n';
	} else {
		cout << -1 << '\n';
	}
}
 
int main() {
	std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
	if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);
 
	cin >> n >> m;
	adj.assign(n + 1, vector<int>());
	while (m--) {
		edges.push_back(edge());
		cin >> edges.back().from >> edges.back().to >> edges.back().weight;
		edges.back().weight *= -1;
		adj[edges.back().from].push_back(edges.back().to);
	}
 
	Bellman_Ford();
 
	return 0;
}
