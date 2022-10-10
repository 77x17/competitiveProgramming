// https://oj.vnoi.info/problem/mtriarea

#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;

    point(int _x = 0, int _y = 0) {
        x = _x, y = _y;
    }

    bool operator < (const point& A) const {
        return x < A.x || (x == A.x && y < A.y);
    }
};

// (+) => counter clockwise | (-) => clockwise
int crossProduct(point O, point A, point B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<point> convexHull(vector<point> arr) {
    int n = arr.size(), k = 0;

    if (n <= 3) return arr;

    sort(arr.begin(), arr.end());

    vector<point> result(2 * n);

    for (int i = 0, anchor = k + 2; i < n; i++) {
        while (k >= anchor && crossProduct(result[k - 2], result[k - 1], arr[i]) <= 0) k--;

        result[k++] = arr[i];
    }

    for (int i = n - 1, anchor = k + 1; i >= 0; i--) {
        while (k >= anchor && crossProduct(result[k - 2], result[k - 1], arr[i]) <= 0) k--;

        result[k++] = arr[i];
    }

    result.resize(k - 1);

    return result;
}

int n; vector<point> arr;

void Input() {
    cin >> n; if (n == -1) exit(0);

    arr.assign(n, point(0, 0));

    for (int i = 0; i < n; i++) cin >> arr[i].x >> arr[i].y;
}

int Area(point a, point b, point c) {
    return abs(1ll * a.x * (b.y - c.y) + 1ll * b.x * (c.y - a.y) + 1ll * c.x * (a.y - b.y));
}

int Area(int a, int b, int c) {
    return Area(arr[a], arr[b], arr[c]);
}

void Process() {
    arr = convexHull(arr); n = arr.size();

    int result = 0;

    for (int i = 0, j = 1, k = 2; i < n; i++) {
        if (i == j) j = (j + 1) % n;
        if (j == k) k = (k + 1) % n;

        while (true) {
            while (Area(i, j, k) <= Area(i, j, (k + 1) % n)) k = (k + 1) % n;

            if (Area(i, j, k) <= Area(i, (j + 1) % n, k)) j = (j + 1) % n; else break;
        }

        result = max(result, Area(i, j, k));
    }

    cout << result / 2 << ((result & 1) ? ".50\n" : ".00\n");
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    while (true) {
        Input();

        Process();
    }

    return 0;
}
