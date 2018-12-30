#include <cstdio>
#include <cstring>
#include <algorithm>

int T, n;
char s[100];
int v[100000];
int c[100000];
int x[100000];
int sa[2][100000], rank[2][100000];
int *SA, *RANK;
int h[100000];
int f[100000][20];
int ans;

void calcsa(int *sa, int *rank, int *SA, int *RANK, int k)
{
	rank[n + 1] = 0;
	for (int i = 1; i <= n; i++)
	{
		v[rank[sa[i]]] = i;
	}
	for (int i = n; i >= 1; i--)
	{
		if (sa[i] > k)
		{
			SA[v[rank[sa[i] - k]]--] = sa[i] - k;
		}
	}
	for (int i = n; i >= n - k + 1; i--)
	{
		SA[v[rank[i]]--] = i;
	}
	RANK[SA[1]] = 1;
	for (int i = 2; i <= n; i++)
	{
		RANK[SA[i]] = RANK[SA[i - 1]] + (rank[SA[i]] != rank[SA[i - 1]] || rank[SA[i] + k] != rank[SA[i - 1] + k]);
	}
}

void getsa()
{
	int p = 0, q = 1;
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; i++)
	{
		v[x[i]]++;
	}
	for (int i = 1; i <= 2; i++)
	{
		v[i] = v[i - 1] + v[i];
	}
	for (int i = n; i >= 1; i--)
	{
		sa[p][v[x[i]]--] = i;
	}
	rank[p][sa[p][1]] = 1;
	for (int i = 2; i <= n; i++)
	{
		rank[p][sa[p][i]] = rank[p][sa[p][i - 1]] + (x[sa[p][i]] != x[sa[p][i - 1]]);
	}
	for (int k = 1; k < n; k <<= 1, p ^= 1, q ^= 1)
	{
		calcsa(sa[p], rank[p], sa[q], rank[q], k);
	}
	SA = (sa[p]);
	RANK = (rank[p]);
}

void geth()
{
	for (int i = 1, j, k = 0; i <= n; h[RANK[i++]] = k)
	{
		for (k = k ? k - 1 : k, j = SA[RANK[i] - 1]; x[i + k] == x[j + k]; k++);
	}
}

void getrmq()
{
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = h[i];
	}
	for (int j = 1; (1 << j) <= n; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query(int x, int y)
{
	int l = std::min(RANK[x], RANK[y]) + 1;
	int r = std::max(RANK[x], RANK[y]);
	int k = c[r - l + 1];
	//printf("V%d %d %d\n", l, r, std::min(f[l][k], f[r - (1 << k) + 1][k]));
	return std::min(f[l][k], f[r - (1 << k) + 1][k]);
}

int main()
{
	c[1] = 0;
	for (int i = 2; i <= 50000; i++)
	{
		c[i] = c[i >> 1] + 1;
	}
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", s + 1);
			x[i] = s[1] == 'a' ? 1 : 2;
		}
		if (n == 1)
		{
			printf("%d\n", 1);
			continue;
		}
		getsa();
		geth();
		getrmq();
		ans = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = i + 1; j <= n; j += i)
			{
				int kk = query(j - i, j);
				if (kk % i == 0)
				{
					ans = std::max(ans, kk / i + 1);
				}
				else
				{
					ans = std::max(ans, kk / i + 1 + (query(j - i - (i - kk % i), j - (i - kk % i)) >= (i - kk % i)));
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
