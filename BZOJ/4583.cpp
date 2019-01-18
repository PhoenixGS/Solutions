#include <cstdio>
#include <algorithm>

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
	int pos, r, g, b;
};

const int M = 1000000007;
const int _n = 50 + 10;
int n;
node x[_n];
int up[2000 + 10], down[2000 + 10];
int f[500 + 20][100 + 10][100 + 10];

bool comp(node x, node y)
{
	return x.pos < y.pos;
}

int main()
{
#ifdef debug
	freopen("4583.in", "r", stdin);
#endif
	up[0] = up[1] = 1;
	for (int i = 2; i <= 2000; i++)
	{
		up[i] = (long long)up[i - 1] * i % M;
	}
	down[0] = down[1] = 1;
	for (int i = 2; i <= 2000; i++)
	{
		down[i] = (long long)(M - M / i) * down[M % i] % M;
	}
	for (int i = 2; i <= 2000; i++)
	{
		down[i] = (long long)down[i - 1] * down[i] % M;
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		x[i].pos = read();
	}
	for (int i = 1; i <= n; i++)
	{
		x[i].r = read();
	}
	for (int i = 1; i <= n; i++)
	{
		x[i].g = read();
	}
	for (int i = 1; i <= n; i++)
	{
		x[i].b = read();
	}
	std::sort(x + 1, x + n + 1, comp);
	int now = 1;
	int id = -1;
	f[0][0][0] = 1;
	for (int i = 0; i < 510; )
	{
		if (id == -1 && x[now].pos == i)
		{
			int tmp = f[i][0][0];
			(f[i][x[now].r][x[now].g] += tmp) %= M;
			f[i][0][0] -= tmp;
			id = now;
			now++;
		}
		if (id != -1 && x[now].pos == i)
		{
			int sum = x[now].r + x[now].g + x[now].b;
			int rem = x[id].r + x[id].g + x[id].b - (i - x[id].pos);
			for (int j = 0; j <= 100; j++)
			{
				for (int k = 0; k <= 100; k++)
				{
					int l = rem - j - k;
					if (f[i][j][k])
					{
						if (j >= x[now].r && k >= x[now].g && l >= x[now].b)
						{
							(f[i + sum][j - x[now].r][k - x[now].g] += (long long)f[i][j][k] * up[x[now].r + x[now].g + x[now].b] % M * down[x[now].r] % M * down[x[now].g] % M * down[x[now].b] % M) %= M;
						}
						if (x[now].r >= j && x[now].g >= k && x[now].b >= l && sum != rem)
						{
							(f[i + rem][x[now].r - j][x[now].g - k] += (long long)f[i][j][k] * up[j + k + l] % M * down[j] % M * down[k] % M * down[l] % M) %= M;
						}
					}
				}
			}
			if (sum == rem)
			{
				i += sum;
				id = -1;
			}
			if (sum > rem)
			{
				i += rem;
				id = now;
			}
			if (sum < rem)
			{
				i += sum;
			}
			now++;
		}
		else
		{
			if (id != -1)
			{
				int rem = x[id].r + x[id].g + x[id].b - (i - x[id].pos);
				for (int j = 0; j <= 100; j++)
				{
					for (int k = 0; k <= 100; k++)
					{
						int l = rem - j - k;
						if (j > 0)
						{
							(f[i + 1][j - 1][k] += f[i][j][k]) %= M;
						}
						if (k > 0)
						{
							(f[i + 1][j][k - 1] += f[i][j][k]) %= M;
						}
						if (l > 0)
						{
							(f[i + 1][j][k] += f[i][j][k]) %= M;
						}
					}
				}
				if (rem == 1)
				{
					id = -1;
				}
			}
			else
			{
				(f[i + 1][0][0] += f[i][0][0]) %= M;
			}
			i++;
		}
	}
	printf("%d\n", f[510][0][0]);
	return 0;
}
