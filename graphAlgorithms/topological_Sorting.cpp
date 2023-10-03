#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int n, m;
vector<vector<int>> adj;

vector<int>  d;
vector<int>  topoList;
vector<bool> visited;

void Dfs(int u) {
	visited[u] = true;
	for (int v : adj[u]) if (not visited[v]) Dfs(v);
	topoList.push_back(u);
}

int main() {
	std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
	if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);

	cin >> n >> m;
	adj.assign(n + 1, vector<int>());
	while (m--) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
	}

	visited.assign(n + 1, false);
	for (int i = 1; i <= n; i++) if (not visited[i]) Dfs(i);
	reverse(topoList.begin(), topoList.end());

	d.assign(n + 1, 0); d[1] = 1;
	for (int u : topoList) {
		for (int v : adj[u]) if (d[u] != 0) {
			if ((d[v] += d[u]) >= MOD) d[v] -= MOD;
		}
	}
	cout << d[n] << '\n';

	return 0;
}
