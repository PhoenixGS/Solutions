#include <cstdio>

const int INF = 1000000000;
const int M = 998244353;
const int _n = 300000 + 10;
int n;
int x[_n];
int inv10000;
int cc[_n][2], chs[_n];
int knum;
int root[_n];
int sum[32 * _n], tag[32 * _n], ch[32 * _n][2];
int cnt, ans;

int pow_mod(int x, int p, int M)
{
	int ans = 1;
	int tmp = x;
	while (p)
	{
		if (p & 1)
		{
			ans = (long long)ans * tmp % M;
		}
		tmp = (long long)tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

void pushup(int x)
{
	sum[x] = (sum[ch[x][0]] + sum[ch[x][1]]) % M;
}

void pushdown(int x)
{
	if (tag[x] != 1)
	{
		if (ch[x][0])
		{
			sum[ch[x][0]] = (long long)sum[ch[x][0]] * tag[x] % M;
			tag[ch[x][0]] = (long long)tag[ch[x][0]] * tag[x] % M;
		}
		if (ch[x][1])
		{
			sum[ch[x][1]] = (long long)sum[ch[x][1]] * tag[x] % M;
			tag[ch[x][1]] = (long long)tag[ch[x][1]] * tag[x] % M;
		}
		tag[x] = 1;
	}
}

void change(int &k, int l, int r, int pos)
{
	knum++;
	k = knum;
	tag[k] = 1;
	if (l == r)
	{
		sum[k] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[k][0], l, mid, pos);
	}
	else
	{
		change(ch[k][1], mid + 1, r, pos);
	}
	pushup(k);
}

int merge(int x, int y, int l, int r, int p, int prex, int prey)
{
	if (x == 0 && y == 0)
	{
		return 0;
	}
	if (y == 0)
	{
		int tmp = ((long long)p * prey % M + (long long)(M + 1 - p) * (M + 1 - prey) % M) % M;
		sum[x] = (long long)sum[x] * tmp % M;
		tag[x] = (long long)tag[x] * tmp % M;
		return x;
	}
	if (x == 0)
	{
		int tmp = ((long long)p * prex % M + (long long)(M + 1 - p) * (M + 1 - prex) % M) % M;
		sum[y] = (long long)sum[y] * tmp % M;
		tag[y] = (long long)tag[y] * tmp % M;
		return y;
	}
	int mid = (l + r) >> 1;
	pushdown(x);
	pushdown(y);
	ch[x][1] = merge(ch[x][1], ch[y][1], mid + 1, r, p, (prex + sum[ch[x][0]]) % M, (prey + sum[ch[y][0]]) % M);
	ch[x][0] = merge(ch[x][0], ch[y][0], l, mid, p, prex, prey);
	pushup(x);
	return x;
}

void calc(int k, int l, int r)
{
	if (! k)
	{
		return;
	}
	if (l == r)
	{
		cnt++;
		ans = (ans + (long long)cnt * l % M * sum[k] % M * sum[k] % M) % M;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(k);
	calc(ch[k][0], l, mid);
	calc(ch[k][1], mid + 1, r);
}

void dfs(int u)
{
	if (u == 0)
	{
		puts("!@#DF");
	}
	if (chs[u] == 0)
	{
		change(root[u], 0, INF, x[u]);
		return;
	}
	x[u] = (long long)x[u] * inv10000 % M;
	if (chs[u] == 1)
	{
		dfs(cc[u][0]);
		root[u] = root[cc[u][0]];
		return;
	}
	dfs(cc[u][0]);
	dfs(cc[u][1]);
	root[u] = merge(root[cc[u][0]], root[cc[u][1]], 0, INF, x[u], 0, 0);
}

int main()
{
	inv10000 = pow_mod(10000, M - 2, M);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int fa;
		scanf("%d", &fa);
		if (i != 1)
		{
			chs[fa]++;
			if (! cc[fa][0])
			{
				cc[fa][0] = i;
			}
			else
			{
				if (cc[fa][1])
				{
					puts("Wrong");
				}
				cc[fa][1] = i;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	dfs(1);
	ans = 0;
	cnt = 0;
	calc(root[1], 0, INF);
	printf("%d\n", ans);
	return 0;
}
