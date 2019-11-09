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

const long long INF = (long long)100000000 * 100000000;
const int _n = 100000 + 10;
int n, need;
int x[_n];
long long s[_n];
int head, tail;
int que[_n];
long long f[_n];
int g[_n];
long long ans;

long long calc(int j, int i, long long M)
{
	return f[j] + (s[i] - s[j] + 1) * (s[i] - s[j] + 1) - M;
}

long long T(int j)
{
	return f[j] + s[j] * s[j] - 2 * s[j];
}

long long up(int k, int j)
{
	return T(j) - T(k);
}

long long down(int k, int j)
{
	return 2 * (s[j] - s[k]);
}

int check(long long M)
{
	head = 1;
	tail = 0;
	tail++;
	que[tail] = 0;
	f[0] = 0;
	g[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		f[i] = calc(que[head], i, M);
		g[i] = g[que[head]] + 1;
		while (head < tail && calc(que[head], i, M) >= calc(que[head + 1], i, M))
		{
			if (calc(que[head], i, M) == calc(que[head + 1], i, M))
			{
				g[i] = std::max(g[i], g[que[head + 1]] + 1);
			}
			else
			{
				f[i] = calc(que[head + 1], i, M);
				g[i] = g[que[head + 1]] + 1;
			}
			head++;
		}
/*		while (head < tail && up(que[head], que[head + 1]) <= s[i])
		{
			head++;
		}
		f[i] = f[que[head]] + (s[i] - s[que[head]] + 1) * (s[i] - s[que[head]] + 1) + M;*/
		while (head < tail && up(que[tail - 1], que[tail]) * down(que[tail], i) >= up(que[tail], i) * down(que[tail - 1], que[tail]))
		{
			tail--;
		}
		tail++;
		que[tail] = i;
	}
//	printf("?%lld %d\n", M, g[n]);
	ans = f[n];
	return g[n];
}

int main()
{
	scanf("%d%d", &n, &need);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
		s[i] = s[i - 1] + x[i];
	}
	long long l = -INF;
	long long r = INF;
	while (l < r)
	{
		long long mid = (l + r) >> 1;
		if (check(mid) >= need)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	check(l);
	printf("%lld\n", ans + l * need);
	return 0;
}
		


