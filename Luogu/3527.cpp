#include <cstdio>
#include <vector>

inline long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 300010, _m = 300010, _k = 300010;
int n, m, k;
int lim[_n];
std::vector<int> vec[_n];
int ll[_k], rr[_k], cc[_k];
long long sum[_m];
int ans[_n];
int x[_n], nx[_n];

inline int lowbit(int x)
{
	return x & -x;
}

inline void add(int x, int delta)
{
	for (int i = x; i <= m + 1; i += lowbit(i))
	{
		sum[i] += delta;
	}
}

inline long long query(int x)
{
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += sum[i];
	}
	return ans;
}

void solve(int l, int r, int L, int R)
{
	if (l > r || L > R)
	{
		return;
	}
	if (L == R)
	{
		for (register int i = l; i <= r; i++)
		{
			ans[x[i]] = L;
		}
		return;
	}
	int mid = (L + R) >> 1;
	for (register int i = L; i <= mid; i++)
	{
		if (i == k + 1)
		{
			continue;
		}
		if (ll[i] <= rr[i])
		{
			add(ll[i], cc[i]);
			add(rr[i] + 1, -cc[i]);
		}
		else
		{
			add(ll[i], cc[i]);
			add(m + 1, -cc[i]);
			add(1, cc[i]);
			add(rr[i] + 1, -cc[i]);
		}
	}
	int nowl = l - 1;
	int nowr = r + 1;
	for (register int i = l; i <= r; i++)
	{
		int z = x[i];
		long long cnt = 0;
		for (register int j = 0; j < (int)vec[z].size(); j++)
		{
			cnt += query(vec[z][j]);
			if (cnt >= lim[z])
			{
				break;
			}
		}
		if (cnt < lim[z])
		{
			nowr--;
			nx[nowr] = x[i];
			lim[z] -= cnt;
		}
		else
		{
			nowl++;
			nx[nowl] = x[i];
		}
	}
	for (register int i = L; i <= mid; i++)
	{
		if (i == k + 1)
		{
			continue;
		}
		if (ll[i] <= rr[i])
		{
			add(ll[i], -cc[i]);
			add(rr[i] + 1, cc[i]);
		}
		else
		{
			add(ll[i], -cc[i]);
			add(m + 1, cc[i]);
			add(1, -cc[i]);
			add(rr[i] + 1, cc[i]);
		}
	}
	for (register int i = l; i <= r; i++)
	{
		x[i] = nx[i];
	}
	solve(l, nowl, L, mid);
	solve(nowr, r, mid + 1, R);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int v = read();
		vec[v].push_back(i);
	}
	for (int i = 1; i <= n; i++)
	{
		lim[i] = read();
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; i++)
	{
		ll[i] = read();
		rr[i] = read();
		cc[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		x[i] = i;
	}
	solve(1, n, 1, k + 1);
	for (int i = 1; i <= n; i++)
	{
		if (ans[i] == k + 1)
		{
			puts("NIE");
		}
		else
		{
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
