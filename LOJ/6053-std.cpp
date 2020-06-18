#include <bits/stdc++.h>
using namespace std;

#define int long long 

typedef long long lint;
const int maxn = 200005, mod = 1e9 + 7, inv2 = (mod + 1) / 2;

lint n, w[maxn];
int m, S;

int id1[maxn], id2[maxn];
int vis[maxn], p[maxn], sum[maxn], tot;
int h[maxn], g[maxn];

inline lint gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	lint sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

void pre(int n)
{
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) p[++tot] = i, sum[tot] = sum[tot - 1] + i;
		for (int j = 1; i * p[j] <= n; ++j) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

int s(int x, int i)
{
	if (x <= 1 || p[i] > x) return 0;
	int k = x <= S ? id1[x] : id2[n / x];
	int res = ((g[k] - h[k] - (sum[i - 1] - (i - 1))) % mod + mod) % mod;

	if (i == 1) res += 2;
	printf("..%d %d %d %d %d\n", x, i, res, g[k], h[k]);
	lint p1, p2;
	for (int j = i; j <= tot && (lint)p[j] * p[j] <= x; ++j){
		p1 = p[j]; p2 = p1 * p[j];
		for (lint e = 1; p2 <= x; p1 = p2, p2 *= p[j], ++e) {
			res += ((lint)s(x / p1, j + 1) * (p[j] ^ e) + (p[j] ^ (e + 1))) % mod;
			if (res >= mod) res -= mod;
		}
	}
	printf("..%d %d %d\n", x, i, res);
	return res;
}

signed main()
{
	n = gi(); S = sqrt(n);

	pre(S);

	for (lint i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		w[++m] = n / i;
		if (w[m] <= S) id1[w[m]] = m;
		else id2[n / w[m]] = m;
		h[m] = (w[m] - 1) % mod;
		g[m] = (lint)(w[m] + 2) % mod * ((w[m] - 1) % mod) % mod * inv2 % mod;
	}

	for (int j = 1; j <= tot; ++j)
		for (int i = 1; i <= m && (lint)p[j] * p[j] <= w[i]; ++i) {
			int k = (w[i] / p[j] <= S) ? id1[w[i] / p[j]] : id2[n / (w[i] / p[j])];
			h[i] = ((lint)h[i] - h[k] + j - 1 + mod) % mod;
			g[i] = (g[i] - (lint)p[j] * (g[k] - sum[j - 1]) % mod + mod) % mod;
		}

	printf("%lld\n", s(n, 1) + 1);
	
	return 0;
}
