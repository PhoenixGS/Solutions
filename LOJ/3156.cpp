#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

struct node
{
	int u, v, p, q;
};

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 100000 + 10, _m = 200000 + 10;
int n, m, A, B, C;
node z[_m];
int head[_n], tail[_n], now[_n];
std::vector<int> vec[_n], vv[_n];
long long f[_m];
long long ans;

bool comp(node x, node y)
{
	return x.q < y.q;
}

long long T(int idx)
{
	return f[idx] + (long long)A * z[idx].q * z[idx].q - (long long)B * z[idx].q;
}

long long Q(int idx)
{
	return (long long)z[idx].q;
}

long long calc(int pos, int idx)
{
	printf("#%d\n", pos);
	while (now[pos] < (int)vv[pos].size() && z[idx].p >= z[vv[pos][now[pos]]].q)
	{
		printf("%d %d\n", z[idx].p, z[vv[pos][now[pos]]].q);
		while (tail[pos] - head[pos] + 1 >= 2 && (T(vec[pos][tail[pos]]) - T(vec[pos][tail[pos] - 1])) * (Q(vv[pos][now[pos]]) - Q(vec[pos][tail[pos]])) > (T(vv[pos][now[pos]]) - T(vec[pos][tail[pos]])) * (Q(vec[pos][tail[pos]]) - Q(vec[pos][tail[pos] - 1]))) tail[pos]--;
		tail[pos]++;
		if (tail[pos] == (int)vec[pos].size())
		{
			vec[pos].push_back(0);
		}
		vec[pos][tail[pos]] = vv[pos][now[pos]];
		now[pos]++;
	}
	int l = head[pos];
	int r = tail[pos];
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (T(vec[pos][mid]) - 2ll * A * Q(vec[pos][mid]) * z[idx].p > T(vec[pos][mid + 1]) - 2ll * A * Q(vec[pos][mid + 1]) * z[idx].p)
		{
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}
	int j = vec[pos][l];
	printf("%lld %d %d %d %lld\n", f[j], z[idx].p, z[j].q, z[idx].p - z[j].q, f[j] + (long long)A * (z[idx].p - z[j].q) * (z[idx].p - z[j].q) + (long long)B * (z[idx].p - z[j].q) + C);
	return f[j] + (long long)A * (z[idx].p - z[j].q) * (z[idx].p - z[j].q) + (long long)B * (z[idx].p - z[j].q) + C;
//	return T(vec[pos][l]) - 2ll * A * Q(vec[pos][l]) * z[idx].p;
}

void add(int pos, int idx)
{
	vv[pos].push_back(idx);
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
	for (int i = 1; i <= m; i++)
	{
		z[i].u = read();
		z[i].v = read();
		z[i].p = read();
		z[i].q = read();
		vec[z[i].v].push_back(0);
	}
	std::sort(z + 1, z + m + 1, comp);

	for (int i = 0; i <= n; i++)
	{
		f[i] = INF;
		head[i] = 1;
		tail[i] = 0;
		vec[i].push_back(0);
		vec[i].push_back(0);
		now[i] = 0;
	}

	ans = INF;
	z[0].v = 1;
	f[0] = 0;
	add(1, 0);
	for (int i = 1; i <= m; i++)
	{
		f[i] = calc(z[i].u, i);
		printf("%d\n", i);
		assert(f[i] >= 0);
		add(z[i].v, i);
		if (z[i].v == n)
		{
			ans = std::min(ans, f[i] + z[i].q);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
