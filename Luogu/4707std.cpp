#include <cstdio>
#include <algorithm>

inline int read() {
    char c = getchar(); int x = 0;
    while (c < '0' || c > '9') { c = getchar(); }
    while (c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + (c & 15); c = getchar(); }
    return x;
}

const int maxN = 1005, maxM = 10005, p = 998244353;

inline int add(int x, int y) { x += y; return x >= p ? x - p : x; }
inline int sub(int x, int y) { x -= y; return x < 0 ? x + p : x; }

int n, m, s, w, ans, inv[maxM], f[12][maxM];

int main() {
    n = read(); s = n + 1 - read(); m = read();
    for (int i = (inv[1] = 1) + 1; i <= m; i++) { inv[i] = (long long) inv[p % i] * (p - p / i) % p; }
    for (int i = 1; i <= s; i++) { f[i][0] = -1; }
    for (int i = 1; i <= n; i++) {
        w = read();
        for (int j = m; j >= w; j--) {
            for (int k = s; k; k--) { f[k][j] = add(f[k][j], sub(f[k - 1][j - w], f[k][j - w])); }
        }
    }
    for (int i = 1; i <= m; i++) { ans = (ans + (long long) f[s][i] * inv[i] % p) % p; }
    printf("%lld\n", (long long) ans * m % p);
    return 0;
}
