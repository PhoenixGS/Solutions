#include <cstdio>
#include <algorithm>

int m, n;
int x[600][600];
int v[600][600];
int top;
int ans;
int stack[600];
int left[600];

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &x[i][j]);
			if (x[i][j])
			{
				v[i][j] = v[i][j - 1] + 1;
			}
		}
	}
	ans = 0;
	for (int j = 1; j <= n; j++)
	{
		top = 0;
		v[m + 1][j] = -1;
		for (int i = 1; i <= m + 1; i++)
		{
			if (top == 0 || v[i][j] > v[stack[top]][j])
			{
				top++;
				stack[top] = i;
				left[i] = i;
				continue;
			}
			if (v[i][j] == v[stack[top]][j])
			{
				continue;
			}
			while (top >= 1 && v[i][j] < v[stack[top]][j])
			{
				ans = std::max(ans, (i - left[stack[top]]) * v[stack[top]][j]);
				top--;
			}
			left[i] = left[stack[top + 1]];
			top++;
			stack[top] = i;
		}
	}
	printf("%d\n", ans);
	return 0;
}
