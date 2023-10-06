#include <iostream>
#include <vector>
 
const int MAX_N = 1e5 + 1;
 
int n, m;
std::vector<int> adj[MAX_N];
 
int dfsTime;
int low[MAX_N];
int num[MAX_N];
std::vector<int> s;
 
int nConnect;
std::vector<int> connect[MAX_N];
 
int kingdomID[MAX_N];
 
void Dfs(int u) {
	low[u] = num[u] = ++dfsTime;
	s.push_back(u);
 
	for (int v : adj[u]) {
		if (num[v] == 0) {
			Dfs(v);
 
			low[u] = std::min(low[u], low[v]);
		} else low[u] = std::min(low[u], num[v]);
	}
 
	if (low[u] == num[u]) {
		for (int v = -1; v != u;) {
			v = s.back(); s.pop_back();
 
			low[v] = num[v] = n + 1;
 
			connect[nConnect].push_back(v);
		}
 
		nConnect++;
	}
}
 
void Tarjan() {
	dfsTime = 0;
	nConnect = 0;
	for (int i = 1; i <= n; i++) if (num[i] == 0) Dfs(i);
}	
 
int main() {
	std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
	if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);
 
	std::cin >> n >> m;
	while (m--) {
		int u, v; std::cin >> u >> v;
		adj[u].push_back(v);
	}
 
	Tarjan();
 
	for (int i = 0; i < nConnect; i++) {
		for (int x : connect[i]) kingdomID[x] = i + 1;
	}
 
	std::cout << nConnect << '\n';
 
	for (int i = 1; i <= n; i++) std::cout << kingdomID[i] << ' ';
	
	return 0;
