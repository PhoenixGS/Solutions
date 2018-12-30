#include <cstdio>
#include <cstring>

int T;
char s[2000];
int v[2000];
int sa[2][2000], rank[2][2000];
int* SA;
int* RANK;
int h[2000];
int n;
int k;
int ans;

void calcsa(int* sa, int* rank, int* SA, int* RANK)
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
	for (int i = n - k + 1; i <= n; i++)
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
		v[s[i]]++;
	}
	for (int i = 1; i <= 128; i++)
	{
		v[i] = v[i - 1] + v[i];
	}
	for (int i = 1; i <= n; i++)
	{
		sa[p][v[s[i]]--] = i;
	}
	rank[p][sa[p][1]] = 1;
	for (int i = 2; i <= n; i++)
	{
		rank[p][sa[p][i]] = rank[p][sa[p][i - 1]] + (s[sa[p][i]] != s[sa[p][i - 1]]);
	}
	for (k = 1; k < n; k <<= 1, p ^= 1, q ^= 1)
	{
		calcsa(sa[p], rank[p], sa[q], rank[q]);
	}
	SA = (sa[p]);
	RANK = (rank[p]);
}

void geth()
{
	for (int i = 1, j, k = 0; i <= n; h[RANK[i++]] = k)
	{
		for (k = k ? k - 1 : k, j = SA[RANK[i] - 1]; s[i + k] == s[j + k]; k++);
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		getsa();
		geth();
		ans = n * (n + 1) / 2;
		for (int i = 1; i <= n; i++)
		{
			ans = ans - h[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
