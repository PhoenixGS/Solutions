#include <cstdio>
#include <algorithm>
#include <iostream>

int n;
int f[1005][9005];
int s[1005][9005];
int M = 1000000007;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= 9; i++)
	{
		f[1][i] = 1;
		s[1][i] = 1;
	}
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= 9 * i; j++)
		{
			for (int k = 0; k <= std::min(9, j); k++)
			{
				(f[i][j] += f[i - 1][j - k]) %= M;
			}
			s[i][j] = (s[i - 1][j] + f[i][j]) % M;
		}
	}
	long long ans = 0;
	for (int sum = 0; sum <= 9 * n; sum++)
	{
		(ans += (long long)f[n][sum] * s[n][sum]) %= (long long)M;
	}
	std::cout << ans << std::endl;
	return 0;
}
