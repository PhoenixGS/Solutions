#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int INF = 1000000000;
const int M = 59393;
const int _n = 3000 + 10, _k = 10 + 10;
int n, k;
int a[_k];
int cost[_n];
int f[_n][_n], pre[_n][_n];
int cnt[_n];
int top;
int stack[_n], least[_n];
int num;

int main()
{
	n = read();
	k = read();
	for (int i = 0; i <= k; i++)
	{
		a[i] = read();
	}
	for (int i = 0; i < n; i++)
	{
		int tmp = 1;
		cost[i] = (long long)tmp * a[0] % M;
		for (int j = 1; j <= k; j++)
		{
			tmp = (long long)tmp * i % M;
			cost[i] = (cost[i] + (long long)tmp * a[j] % M) % M;
		}
	}
	if (n == 1)
	{
		printf("%d %d\n", 0, cost[0]);
		return 0;
	}
	int c1 = cost[1];
	for (int i = 1; i < n; i++)
	{
		cost[i] -= c1;
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < (i - 1); j++)
		{
			f[i][j] = f[i - 1][j];
			pre[i][j] = j;
		}
		for (int j = i - 1; j < n - 1; j++)
		{
			f[i][j] = f[i - 1][j];
			pre[i][j] = j;
			if (f[i][j - (i - 1)] + cost[i] > f[i][j])
			{
				f[i][j] = f[i][j - (i - 1)] + cost[i];
				pre[i][j] = pre[i][j - (i - 1)];
			}
		}
	}
	printf("%d %d\n", n - 1, f[n - 1][n - 2] + n * c1);
	int now = n - 2;
	int nextx;
	for (int i = n - 1; i >= 2; i--)
	{
		nextx = pre[i][now];
		cnt[i] = (now - nextx) / (i - 1);
		now = nextx;
	}
	cnt[1] = n;
	for (int i = 2; i < n; i++)
	{
		cnt[1] -= cnt[i];
	}
	num = n;
	top = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = 1; j <= cnt[i]; j++)
		{
			if (top)
			{
				printf("%d %d\n", num, stack[top]);
				least[top]--;
				while (top && least[top] == 0)
				{
					top--;
				}
				top++;
				stack[top] = num;
				least[top] = i - 1;
				while (top && least[top] == 0)
				{
					top--;
				}
			}
			else
			{
				top++;
				stack[top] = num;
				least[top] = i;
			}
			num--;
		}
	}
	return 0;
}
