#include <cstdio>
#include <algorithm>
#include <iostream>

int n;
int x[400000][3];
int stack[3][400000];
long long ans;
int last[3];

int binary_search(int now, int l, int r, int key)
{
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (x[stack[now][mid]][now] == key)
		{
			return mid;
		}
		if (x[stack[now][mid]][now] > key)
		{
			l = mid + 1;
		}
		if (x[stack[now][mid]][now] < key)
		{
			r = mid - 1;
		}
	}
	return -1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i][0]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i][1]);
	}
	last[0] = 1;
	last[1] = 1;
	stack[0][1] = 1;
	stack[1][1] = 1;
	ans = 0;
	for (int i = 2; i <= n; i++)
	{
		for (int now = 0; now <= 1; now++)
		{
			int opp = now ^ 1;
			while (last[now] && x[i][now] >= x[stack[now][last[now]]][now])
			{
				int k = binary_search(opp, 1, last[opp], x[stack[now][last[now]]][now]);
				if (k != -1)
				{
					int klast = i - 1;
					ans += (long long)(klast - std::max(stack[now][last[now]], stack[opp][k]) + 1) * (long long)std::max(0, std::min(stack[now][last[now]], stack[opp][k]) - std::max(stack[now][last[now] - 1] + 1, stack[opp][k - 1] + 1) + 1);
				}
				last[now]--;
			}
			last[now]++;
			stack[now][last[now]] = i;
		}
	}
	for (int i = 1; i <= last[0]; i++)
	{
		int now = 0;
		int opp = 1;
		int k = binary_search(opp, 1, last[opp], x[stack[now][i]][now]);
		if (k != -1)
		{
			int klast = n;
			ans += (long long)(klast - std::max(stack[now][i], stack[opp][k]) + 1) * (long long)std::max(0, std::min(stack[now][i], stack[opp][k]) - std::max(stack[now][i - 1] + 1, stack[opp][k - 1] + 1) + 1);
		}
	}
	std::cout << ans << std::endl;
	return 0;
}
