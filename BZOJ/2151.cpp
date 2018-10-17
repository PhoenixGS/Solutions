#include <cstdio>
#include <queue>

int n, m;
int left[300000], right[300000];
int ans;
std::priority_queue<std::pair<int, int> > que;
int x[300000];
int flag[300000];

void del(int x)
{
	flag[x] = 1;
	left[right[x]] = left[x];
	right[left[x]] = right[x];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	if (m > n / 2)
	{
		printf("Error!\n");
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		left[i] = i - 1;
		right[i] = i + 1;
	}
	left[1] = n;
	right[n] = 1;
	for (int i = 1; i <= n; i++)
	{
		que.push(std::make_pair(x[i], i));
	}
	ans = 0;
	while (m)
	{
		int k = que.top().second;
		que.pop();
		if (flag[k])
		{
			continue;
		}
		m--;
		ans = ans + x[k];
		x[k] = x[left[k]] + x[right[k]] - x[k];
		que.push(std::make_pair(x[k], k));
		del(left[k]);
		del(right[k]);
	}
	printf("%d\n", ans);
	return 0;
}
