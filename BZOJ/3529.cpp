#include <cstdio>
#include <algorithm>

struct QUES
{
	int n, m, x;
	int id;
};

int mu[200000], ff[200000], last[200000], flag[200000];
int primenum;
int prime[200000];
int bit[200000];
int anss[200000];
QUES ques[200000];
int x[200000];
int maxx;
int q;

int lowbit(int x)
{
	return x & -x;
}

bool comp(int x, int y)
{
	return ff[x] < ff[y];
}

bool compques(QUES x, QUES y)
{
	return x.x < y.x;
}

void change(int x, int delta)
{
	for (int i = x; i <= maxx; i += lowbit(i))
	{
		bit[i] += delta;
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += bit[i];
	}
	return ans;
}

void update(int x)
{
	for (int i = x; i <= maxx; i += x)
	{
		change(i, ff[x] * mu[i / x]);
	}
}

int main()
{
	mu[1] = 1;
	ff[1] = 1;
	for (int i = 2; i <= 100000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			mu[i] = -1;
			ff[i] = i + 1;
			last[i] = 1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 100000; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				ff[i * prime[j]] = ff[last[i]] + prime[j] * ff[i];
				last[i * prime[j]] = last[i];
				break;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
				ff[i * prime[j]] = ff[i] * (1 + prime[j]);
				last[i * prime[j]] = i;
			}
		}
	}
	maxx = 0;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++)
	{
		scanf("%d%d%d", &ques[i].n, &ques[i].m, &ques[i].x);
		maxx = std::max(maxx, std::max(ques[i].n, ques[i].m));
		ques[i].id = i;
	}
	std::sort(ques + 1, ques + q + 1, compques);
	for (int i = 1; i <= maxx; i++)
	{
		x[i] = i;
	}
	std::sort(x + 1, x + maxx + 1, comp);
	int now = 1;
	for (int i = 1; i <= q; i++)
	{
		while (now <= maxx && ff[x[now]] <= ques[i].x)
		{
			update(x[now]);
			now++;
		}
		int pos = 0;
		int top = std::min(ques[i].n, ques[i].m);
		unsigned long long ans = 0;
		for (int j = 1; j <= top; j = pos + 1)
		{
			pos = std::min(ques[i].n / (ques[i].n / j), ques[i].m / (ques[i].m / j));
			ans += (query(pos) - query(j - 1)) * (unsigned long long)(ques[i].n / j) * (unsigned long long)(ques[i].m / j);
		}
		anss[ques[i].id] = (ans & ((1u << 31) - 1));
	}
	for (int i = 1; i <= q; i++)
	{
		printf("%d\n", anss[i]);
	}
	return 0;
}
