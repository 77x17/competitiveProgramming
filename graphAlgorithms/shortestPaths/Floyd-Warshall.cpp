#include <bits/stdc++.h>
using namespace std;
 
const long long INF = 1e18;
 
int n, m, q;
vector<vector<long long>> d;
 
int main() {
	std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
	if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);
 
	cin >> n >> m >> q;
	d.assign(n + 1, vector<long long> (n + 1, INF));
	while (m--) {
		int u, v, c; cin >> u >> v >> c;
 
		if (d[u][v] > c) d[u][v] = c;
		if (d[v][u] > c) d[v][u] = c;
	}
 
	for (int u = 1; u <= n; u++) d[u][u] = 0;
	for (int k = 1; k <= n; k++) {
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				if (d[u][v] > d[u][k] + d[k][v]) {
					d[u][v] = d[u][k] + d[k][v];
				}
			}
		}
	}
 
	while (q--) {
		int u, v; cin >> u >> v;
		cout << (d[u][v] == INF ? -1 : d[u][v]) << '\n';
	}
 
	return 0;
