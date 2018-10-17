#include <cstdio>
#include <algorithm>

struct T
{
	long long time, in, out, w, f;
};

const long long INF = 1ll << 60;
T x[200000];
T tmp[200000];
int que[200000];
int n;
long long ss, maxtime;
int cas;
long long ans;

bool comp(T x, T y)
{
	return x.time < y.time;
}

long double calc(int j, int k)
{
	long double tmp = (long double)((x[j].f - x[k].f + (x[k].time + 1) * x[k].w - (x[j].time + 1) * x[j].w + x[j].out - x[k].out));
	if (x[j].w == x[k].w)
	{
		return tmp > 0 ? INF : -INF;
	}
	return tmp / (x[k].w - x[j].w);
}

void solve(int l, int r)
{
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	int head = 1;
	int tail = 0;
	for (int i = l; i <= mid; i++)
	{
		if (x[i].f >= 0)
		{
			while (head + 1 <= tail && calc(que[tail - 1], que[tail]) > calc(que[tail], i))
			{
				tail--;
			}
			tail++;
			que[tail] = i;
		}
	}
	for (int i = mid + 1; i <= r; i++)
	{
		while (head + 1 <= tail && calc(que[head], que[head + 1]) <= x[i].time)
		{
			head++;
		}
		long long s = (x[i].time - x[que[head]].time - 1) * x[que[head]].w + x[que[head]].out + x[que[head]].f;
		if (s >= x[i].in)
		{
			x[i].f = std::max(x[i].f, s - x[i].in);
		}
	}
	solve(mid + 1, r);
	int i = l;
	int j = mid + 1;
	int now = l - 1;
	while (i <= mid && j <= r)
	{
		if (x[i].w < x[j].w)
		{
			now++;
			tmp[now] = x[i];
			i++;
		}
		else
		{
			now++;
			tmp[now] = x[j];
			j++;
		}
	}
	while (i <= mid)
	{
		now++;
		tmp[now] = x[i];
		i++;
	}
	while (j <= r)
	{
		now++;
		tmp[now] = x[j];
		j++;
	}
	for (int i = l; i <= r; i++)
	{
		x[i] = tmp[i];
	}
}

int main()
{
	while (scanf("%d%lld%lld", &n, &ss, &maxtime) == 3 && (n || ss || maxtime))
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%lld%lld%lld%lld", &x[i].time, &x[i].in, &x[i].out, &x[i].w);
			x[i].f = -INF;
		}
		n++;
		x[n] = (T){0, 0, 0, 0, ss};
		std::sort(x + 1, x + n + 1, comp);
		solve(1, n);
		cas++;
		ans = 0;
		for (int i = 1; i <= n; i++)
		{
			if (x[i].f >= 0)
			{
				ans = std::max(ans, x[i].f + (maxtime - x[i].time) * x[i].w + x[i].out);
			}
		}
		printf("Case %d: %lld\n", cas, ans);
	}
	return 0;
}
