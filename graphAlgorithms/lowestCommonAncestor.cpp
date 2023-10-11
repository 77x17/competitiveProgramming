#include <iostream>
#include <vector>

const int MAX_N = 2e5;
const int LOG = 18;

int n, m;
int par[MAX_N + 1][LOG + 1];
std::vector<int> adj[MAX_N + 1];

int high[MAX_N + 1];
int dist[MAX_N + 1];

void Dfs(int u) {
	for (int v : adj[u]) {
		if (v != par[u][0]) {
			high[v] = high[u] + 1;
			dist[v] = dist[u] + 1;
			par[v][0] = u;
			Dfs(v);	
		}
	}
}

int find_LCA(int u, int v) {
	if (high[u] < high[v]) return find_LCA(v, u);
	for (int j = LOG; j >= 0; j--) {
		if (high[par[u][j]] >= high[v]) u = par[u][j];
	}
	if (u == v) return u;
	for (int j = LOG; j >= 0; j--) {
		if (par[u][j] != par[v][j]) u = par[u][j], v = par[v][j];
	}
	return par[u][0];
}

int main() {
	std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
	if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);

	std::cin >> n >> m;
	for (int i = 2; i <= n; i++) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	high[0] = -1; 
	Dfs(1);
	for (int j = 1; j <= LOG; j++) {
		for (int i = 1; i <= n; i++) {
			par[i][j] = par[par[i][j - 1]][j - 1];
		}
	} 

	while (m--) {
		int u, v;
		std::cin >> u >> v;

		std::cout << dist[u] + dist[v] - 2 * dist[find_LCA(u, v)] << '\n';
	}
}
