#include <cstdio>

int x[3000000];
int y[3000000];
int n, m;
const int M = 1000000007;

int main()
{
	x[0] = 1;
	for (int i = 1; i <= 2000000; i++)
	{
		x[i] = (long long)x[i - 1] * i % M;
	}
	y[1] = 1;
	for (int i = 2; i <= 2000000; i++)
	{
		y[i] = (-(long long)(M / i) * y[M % i] % M + M) % M;
	}
	for (int i = 2; i <= 2000000; i++)
	{
		y[i] = (long long)y[i - 1] * y[i] % M;
	}
	scanf("%d%d", &n, &m);
	printf("%lld\n", (long long)x[n + m - 2] * y[n - 1] % M * y[m - 1] % M);
	return 0;
}
