#include <cstdio>
<<<<<<< HEAD
=======
#include <cmath>
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

int n, m;
int x[60000];
int knumber;
int knum[60000];
int vvv;
int vv[60000];
int bit[60000];
int tim[60000];
int f[240][60000];
int sum[240][60000];
int TIM = 0;;

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i <= vvv; i += lowbit(i))
	{
		if (tim[i] != TIM)
		{
			tim[i] = TIM;
			bit[i] = delta;
		}
		else
		{
			bit[i] += delta;
		}
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		if (tim[i] == TIM)
		{
			ans += bit[i];
		}
	}
	return ans;
}

void add(int *bit, int x, int delta)
{
	for (int i = x; i <= vvv; i += lowbit(i))
	{
		bit[i] += delta;
	}
}

int query(int *bit, int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += bit[i];
	}
	return ans;
}

int query(int l, int r)
{
	int ll = (l - 1) % knumber == 0 ? knum[l] : knum[l] + 1;
	int rr = r % knumber == 0 ? knum[r] : knum[r] - 1;
	int ans = 0;
	if (ll <= rr)
	{
		ans = f[ll][r];
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			add(x[i], 1);
		}
		for (int i = (ll - 1) * knumber; i >= l; i--)
		{
			ans += query(sum[rr], x[i] - 1) - query(sum[ll - 1], x[i] - 1) + query(x[i] - 1);
			add(x[i], 1);
		}
		/*for (int i = l; i <= (ll - 1) * knumber; i++)
		{
			ans += query(sum[rr], x[i] - 1) - query(sum[ll - 1], x[i] - 1);
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			ans += (query(sum[rr], n) - query(sum[rr], x[i])) - (query(sum[ll - 1], n) - query(sum[ll - 1], x[i]));
		}
		for (int i = l; i <= (ll - 1) * knumber; i++)
		{
			ans += query(bit, n) - query(bit, x[i]);
			add(bit, x[i], 1);
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			ans += query(bit, n) - query(bit, x[i]);
			add(bit, x[i], 1);
		}
		for (int i = l; i <= (ll - 1) * knumber; i++)
		{
			add(bit, x[i], -1);
		}
		for (int i = rr * knumber + 1; i <= r; i++)
		{
			add(bit, x[i], -1);
		}*/
	}
	else
	{
		for (int i = l; i <= r; i++)
		{
			ans += query(vvv) - query(x[i]);
			add(x[i], 1);
		}
	}
	return ans;
}
>>>>>>> 6f661aa6cb24872fa23075107f903c233938bb68

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
<<<<<<< HEAD
		scanf("%d", &x[i]);
=======
		x[i] = read();
		vv[i] = x[i];
	}
	std::sort(vv + 1, vv + n + 1);
	vvv = std::unique(vv + 1, vv + n + 1) - vv - 1;
	for (int i = 1; i <= n; i++)
	{
		x[i] = std::lower_bound(vv + 1, vv + vvv + 1, x[i]) - vv;
>>>>>>> 6f661aa6cb24872fa23075107f903c233938bb68
	}
	knumber = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
<<<<<<< HEAD

}
=======
	for (int i = 1; i <= knum[n]; i++)
	{
		TIM++;
		int now = 0;
		for (int j = (i - 1) * knumber + 1; j <= n; j++)
		{
			now += query(vvv) - query(x[j]);
			add(x[j], 1);
			f[i][j] = now;
		}
	}
	TIM++;
	for (int i = 1; i <= n; i++)
	{
		add(x[i], 1);
		if (i % knumber == 0 || i == n)
		{
			for (int j = 1; j <= vvv; j++)
			{
				sum[knum[i]][j] = tim[j] == TIM ? bit[j] : 0;
			}
		}
	}
	int preans = 0;
	scanf("%d", &m);
	while (m--)
	{
		TIM++;
		int l, r;
		l = read();
		r = read();
		l = l ^ preans;
		r = r ^ preans;
		if (l > r)
		{
			std::swap(l, r);
		}
		preans = query(l, r);
		printf("%d\n", preans);
	}
	return 0;
}

>>>>>>> 6f661aa6cb24872fa23075107f903c233938bb68
