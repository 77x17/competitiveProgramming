#include <bits/stdc++.h>
using namespace std;
 
const int LOG = 30;
 
int n, q;
vector<vector<int>> par;
 
int Jump(int u, int c) {
	for (int i = 0; i < LOG; i++) {
		if (c & (1 << i)) u = par[u][i];
	}
	return u;
}
 
int main() {
	std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
	if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);
 
	cin >> n >> q;
	par.assign(n + 1, vector<int> (LOG, -1));
	for (int i = 1; i <= n; i++) cin >> par[i][0];
 
	for (int j = 1; j < LOG; j++) {
		for (int i = 1; i <= n; i++) par[i][j] = par[par[i][j - 1]][j - 1];
	}
 
	while (q--) {
		int u, c; cin >> u >> c;
 
		cout << Jump(u, c) << '\n';
	}
 
	return 0;
}
