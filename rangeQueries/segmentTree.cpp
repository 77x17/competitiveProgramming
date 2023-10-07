#include <iostream>

const int MAX_N = 2e5 + 1;
const long long INF = 1e18 + 7;

struct SegmentTree {
    long long  val[4 * MAX_N];
    long long lazy[4 * MAX_N];

    void pushDown(int id) {
         val[2 * id] += lazy[id];  val[2 * id + 1] += lazy[id];
        lazy[2 * id] += lazy[id]; lazy[2 * id + 1] += lazy[id];
        lazy[id] = 0;
    }

    void Update(int id, int l, int r, int u, int v, long long c) {
        if (r <  u || v <  l) return;
        if (u <= l && r <= v) {
             val[id] += c;
            lazy[id] += c;
            return;
        }

        pushDown(id);

        int mid = (l + r) >> 1;
        Update(2 * id    , l      , mid, u, v, c);
        Update(2 * id + 1, mid + 1, r  , u, v, c);
        val[id] = std::min(val[2 * id], val[2 * id + 1]);
    }

    long long Query(int id, int l, int r, int u, int v) {
        if (r <  u || v <  l) return INF;
        if (u <= l && r <= v) return val[id];  

        pushDown(id);

        int mid = (l + r) >> 1;
        return std::min(
            Query(2 * id    , l      , mid, u, v),
            Query(2 * id + 1, mid + 1, r  , u, v)
        );
    }
} ST;

int n, m;
int arr[MAX_N];

int main() {
    std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> arr[i];    

    for (int i = 1; i <= n; i++) ST.Update(1, 1, n, i, i, arr[i]);

    while (m--) {
        int t; std::cin >> t;

        if (t == 1) {
            int u, v, c; std::cin >> u >> v >> c;
            ST.Update(1, 1, n, u, v, c);
        } else if (t == 2) {
            int u; std::cin >> u;
            std::cout << ST.Query(1, 1, n, u, u) << '\n';
        }
    }

    return 0;
}
