#include <iostream>

const int MAX_N = 2e5 + 1;

struct FenwickTree {
    int n;
    long long val[MAX_N];

    void Init(int _n) {
        n = _n;
    }

    void Update(int x, int c) {
        for (; x <= n; x += x & -x) val[x] += c;
    }

    long long Get(int x) {
        long long result = 0;
        for (; x >= 1; x -= x & -x) result += val[x];
        return result;
    }
} BIT;

int n, m;
int arr[MAX_N];

int main() {
    std::ios_base::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    if (fopen("Input.txt", "r")) freopen("Input.txt", "r", stdin);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> arr[i];

    BIT.Init(n);
    for (int i = 1; i <= n; i++) BIT.Update(i, arr[i]);

    while (m--) {
        int l, r; std::cin >> l >> r;

        std::cout << BIT.Get(r) - BIT.Get(l - 1) << '\n';
    }

    return 0;
}
