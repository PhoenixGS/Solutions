#include <cstdio>

int n, m;
long long v[100];
int last;
long long vv[100];
int flag;

void insert(long long x)
{
	for (int i = 60; i >= 0; i--)
	{
		if ((1ll << i) & x)
		{
			if (v[i])
			{
				x = x ^ v[i];
			}
			else
			{
				v[i] = x;
				return;
			}
		}
	}
	flag = 1;
}

void build()
{
	for (int i = 0; i <= 52; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if ((1ll << j) & v[i])
			{
				v[i] ^= v[j];
			}
		}
	}
	last = 0;
	for (int i = 0; i <= 52; i++)
	{
		if (v[i])
		{
			vv[last] = v[i];
			last++;
		}
	}
}

long long query(long long k)
{
	k -= flag;
	if (k >= (1ll << last))
	{
		return (long long)-1;
	}
	long long ans = 0;
	for (int i = 0; i < last; i++)
	{
		if ((1ll << i) & k)
		{
			ans = ans ^ vv[i];
		}
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		long long x;
		scanf("%lld", &x);
		insert(x);
	}
	build();
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		long long k;
		scanf("%lld", &k);
		printf("%lld\n", query(k));
	}
	return 0;
}
