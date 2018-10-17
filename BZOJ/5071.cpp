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

int T;
int n;
long long x[200000];
long long y[200000];

int main()
{
	T = read();
	while (T--)
	{
		n = read();
		for (int i = 1; i <= n; i++)
		{
			x[i] = read();
			x[i] = x[i - 1] + x[i];
		}
		for (int i = 1; i <= n; i++)
		{
			y[i] = read();
			y[i] = y[i - 1] + y[i];
		}
		std::sort(x + 1, x + n + 1);
		std::sort(y + 1, y + n + 1);
		bool flag = true;
		for (int i = 1; i <= n; i++)
		{
			if (x[i] != y[i])
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
