#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18 + 7;


class SegmentTree {
private:
    int n;  vector<long long> tree, lazy;

    void pushDown(int id) {
        tree[2 * id] += lazy[id];  tree[2 * id + 1] += lazy[id];

        lazy[2 * id] += lazy[id];  lazy[2 * id + 1] += lazy[id];

        lazy[id] = 0;
    }

    void update(int id, int l, int r, int u, int v, int val) {
        if (r < u || v < l) return;

        if (u <= l && r <= v) {
            tree[id] += val;  lazy[id] += val;  return;
        }

        pushDown(id);

        int mid = (l + r) / 2;

        update(2 * id, l, mid, u, v, val);  update(2 * id + 1, mid + 1, r, u, v, val);

        tree[id] = max(tree[2 * id], tree[2 * id + 1]);
    }

    long long getmax(int id, int l, int r, int u, int v) {
        if (r < u || v < l) return -INF;

        if (u <= l && r <= v) return tree[id];

        pushDown(id);

        int mid = (l + r) / 2;

        long long a = getmax(2 * id, l, mid, u, v),  b = getmax(2 * id + 1, mid + 1, r, u, v);

        return max(a, b);
    }
public:
    SegmentTree(int n = 0): n(n) {
        tree.assign(4 * n + 1, 0);  lazy.assign(4 * n + 1, 0);
    }

    void update(int u, int v, long long val) {update(1, 1, n, u, v, val);}

    long long getmax(int u, int v) {return getmax(1, 1, n, u, v);}
} ST;


int n;  vector<int> arr;

void Input() {
    cin >> n;  arr.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) cin >> arr[i];
}


void Process() {
    ST = SegmentTree(n);

    for (int i = 1; i <= n; i++) ST.update(i, i, arr[i]);

    int q; cin >> q; while (q--) {
        int e; cin >> e;

        if (e == 1) {
            int x, y, val; cin >> x >> y >> val;

            ST.update(x, y, val);
        } else {
            int x, y; cin >> x >> y;

            cout << ST.getmax(x, y) << '\n';
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    Input();

    Process();

    return 0;
}

/* https://oj.vnoi.info/problem/segtree_itlazy */
