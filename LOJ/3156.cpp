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
	int cas, pos, tim, idx;
};

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 100000 + 10, _m = 200000 + 10;
int n, m, A, B, C;
int u[_m], v[_m], p[_m], q[_m];
int last;
node z[2 *_m];
int head[_n], tail[_n];
std::vector<int> vec[_n];
long long f[_m];
long long ans;

bool comp(node x, node y)
{
	return x.tim < y.tim || (x.tim == y.tim && x.cas > y.cas);
}

long long T(int idx)
{
	return f[idx] + (long long)A * q[idx] * q[idx] - (long long)B * q[idx];
}

long long Q(int idx)
{
	return (long long)q[idx];
}

long long calc(int pos, int idx)
{
	int l = head[pos];
	int r = tail[pos];
	if (l > r)
	{
		return INF;
	}
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (T(vec[pos][mid]) - 2ll * A * Q(vec[pos][mid]) * p[idx] > T(vec[pos][mid + 1]) - 2ll * A * Q(vec[pos][mid + 1]) * p[idx])
//		if ((double)T(vec[pos][mid]) - 2ll * A * Q(vec[pos][mid]) * p[idx] > (double)T(vec[pos][mid + 1]) - 2ll * A * Q(vec[pos][mid + 1]) * p[idx])
		{
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}
	int j = vec[pos][l];
	assert(p[idx] >= q[j]);
	return f[j] + (long long)A * (p[idx] - q[j]) * (p[idx] - q[j]) + (long long)B * (p[idx] - q[j]) + C;
}

void add(int pos, int idx)
{
	while (tail[pos] - head[pos] + 1 >= 2 && (T(vec[pos][tail[pos]]) - T(vec[pos][tail[pos] - 1])) * (Q(idx) - Q(vec[pos][tail[pos]])) > (T(idx) - T(vec[pos][tail[pos]])) * (Q(vec[pos][tail[pos]]) - Q(vec[pos][tail[pos] - 1]))) tail[pos]--;
	tail[pos]++;
	vec[pos][tail[pos]] = idx;
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
	for (int i = 1; i <= m; i++)
	{
		u[i] = read();
		v[i] = read();
		p[i] = read();
		q[i] = read();
		last++;
		z[last].cas = 0;
		z[last].pos = u[i];
		z[last].tim = p[i];
		z[last].idx = i;
		last++;
		z[last].cas = 1;
		z[last].pos = v[i];
		z[last].tim = q[i];
		z[last].idx = i;
		vec[v[i]].push_back(0);
	}
	last++;
	z[last].cas = 1;
	z[last].pos = 1;
	z[last].tim = 0;
	z[last].idx = 0;
	std::sort(z + 1, z + last + 1, comp);
	
	for (int i = 0; i <= n; i++)
	{
		head[i] = 1;
		tail[i] = 0;
		vec[i].push_back(0);
		vec[i].push_back(0);
	}
	for (int i = 0; i <= m; i++)
	{
		f[i] = INF;
	}

	f[0] = 0;
	for (int i = 1; i <= last; i++)
	{
		if (z[i].cas == 0)
		{
			f[z[i].idx] = calc(z[i].pos, z[i].idx);
		}
		else
		{
			if (f[z[i].idx] < INF)
			{
				add(z[i].pos, z[i].idx);
			}
		}
	}

	ans = INF;
	for (int i = 1; i <= m; i++)
	{
		if (v[i] == n)
		{
			ans = std::min(ans, f[i] + q[i]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
