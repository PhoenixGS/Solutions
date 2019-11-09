#include <cstdio>

const int _n = 500000 + 10;
int n, M;
int x[_n];
long long s[_n];
int head, tail;
int que[_n];
long long f[_n];

long long up(int k, int j)
{
	return f[j] + s[j] * s[j] - f[k] - s[k] * s[k];
}

long long down(int k, int j)
{
	return 2ll * (s[j] - s[k]);
}

int main()
{
	while (scanf("%d%d", &n, &M) == 2)
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x[i]);
			s[i] = s[i - 1] + x[i];
		}
		head = 1;
		tail = 0;
		tail++;
		que[tail] = 0;
		for (int i = 1; i <= n; i++)
		{
			while (head < tail && up(que[head], que[head + 1]) <= s[i] * down(que[head], que[head + 1]))
			{
				head++;
			}
			f[i] = f[que[head]] + (s[i] - s[que[head]]) * (s[i] - s[que[head]]) + M;
			while (head < tail && up(que[tail - 1], que[tail]) * down(que[tail], i) >= up(que[tail], i) * down(que[tail - 1], que[tail]))
			{
				tail--;
			}
			tail++;
			que[tail] = i;
		}
		printf("%d\n", f[n]);
	}
	return 0;
}
