#include <cstdio>
#include <cstring>
#include <algorithm>

int n;
char s[300000];
int sa[2][300000], rank[2][300000];
int v[300000];
int k;

void calc(int* sa, int* rank, int* SA, int* RANK)
{
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
	for (int i = 1; i <= n; i++)
	{
		RANK[SA[i]] = RANK[SA[i - 1]] + (rank[SA[i - 1]] != rank[SA[i]] || rank[SA[i - 1] + k] != rank[SA[i] + k]);
	}
}

void work()
{
	int p = 0, q = 1;
	for (int i = 1; i <= n; i++)
	{
		v[s[i]]++;
	}
	for (int i = 1; i <= 256; i++)
	{
		v[i] = v[i - 1] + v[i];
	}
	for (int i = 1; i <= n; i++)
	{
		sa[p][v[s[i]]--] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		rank[p][sa[p][i]] = rank[p][sa[p][i - 1]] + (s[sa[p][i]] != s[sa[p][i - 1]]);
	}
	for (k = 1; k < n; k <<= 1, std::swap(p, q))
	{
		calc(sa[p], rank[p], sa[q], rank[q]);
	}
	for (int i = 1; i <= n; i++)
	{
		if (sa[p][i] <= n / 2)
		{
			printf("%c", s[sa[p][i] + n / 2 - 1]);
		}
		//printf("%d\n", sa[p][i]);
	}
	puts("");
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		s[n + i] = s[i];
	}
	n = n + n;
	work();
}
