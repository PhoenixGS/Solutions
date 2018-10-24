#include <cstdio>
#include <algorithm>
#include <vector>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 1000 + 10, _m = 1000 + 10, _q = 300000 + 10;
int n, q;
int c[_n], v[_n], m[_n];
int que[_m], val[_m];
int f[20][_n];
std::vector<std::pair<int, int> > vec[_n];
int ans[_q];

void update(int *f, int pos)
{
	for (int i = 0; i < c[pos]; i++)
	{
		int head = 1, tail = 1;
		que[1] = 0;
		val[1] = f[i];
		for (int j = 1; i + c[pos] * j <= 1000; j++)
		{
			while (head <= tail && j - que[head] > m[pos])
			{
				head++;
			}
			while (head <= tail && f[i + c[pos] * j] >= val[tail] + (j - que[tail]) * v[pos])
			{
				tail--;
			}
			tail++;
			que[tail] = j;
			val[tail] = f[i + c[pos] * j];
			f[i + c[pos] * j] = val[head] + (j - que[head]) * v[pos];
		}
	}
}

void solve(int l, int r, int d)
{
	if (l == r)
	{
		for (int i = 0; i < (int)vec[l].size(); i++)
		{
			ans[vec[l][i].second] = f[d][vec[l][i].first];
		}
		return;
	}
	int mid = (l + r) >> 1;
	for (int i = 0; i <= 1000; i++)
	{
		f[d + 1][i] = f[d][i];
	}
	for (int i = mid + 1; i <= r; i++)
	{
		update(f[d + 1], i);
	}
	solve(l, mid, d + 1);
	for (int i = 0; i <= 1000; i++)
	{
		f[d + 1][i] = f[d][i];
	}
	for (int i = l; i <= mid; i++)
	{
		update(f[d + 1], i);
	}
	solve(mid + 1, r, d + 1);
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		c[i] = read();
		v[i] = read();
		m[i] = read();
	}
	q = read();
	for (int i = 1; i <= q; i++)
	{
		int pos, sum;
		pos = read();
		sum = read();
		pos++;
		vec[pos].push_back(std::make_pair(sum, i));
	}
	solve(1, n, 1);
	for (int i = 1; i <= q; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}