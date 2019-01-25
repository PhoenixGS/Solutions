/*
ID: thestar1
PROG: milk2
LANG: C++
*/

#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int flag[2000000];
int minx, maxx;

int main()
{
	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);
	scanf("%d", &n);
	minx = 1000000000;
	maxx = 0;
	for (int i = 1; i <= n; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		minx = min(minx, l);
		maxx = max(maxx, r);
		flag[l]++;
		flag[r]--;
	}
	int ans1 = 0;
	int ans2 = 0;
	int now = 0;
	int begins1 = -1;
	int begins2 = -1;
	for (int i = minx; i <= maxx; i++)
	{
		int pre = now;
		now += flag[i];
		if (pre == 0 && now != 0)
		{
			begins1 = i;
			if (begins2 != -1)
			{
				ans2 = max(ans2, i - begins2);
			}
			begins2 = -1;
		}
		if (pre != 0 && now == 0)
		{
			begins2 = i;
			if (begins1 != -1)
			{
				ans1 = max(ans1, i - begins1);
			}
			begins1 = -1;
		}
	}
	if (begins1 != -1)
	{
		ans1 = max(ans1, maxx - begins1);
	}
	if (begins2 != -1)
	{
		ans2 = max(ans2, maxx - begins2);
	}
	printf("%d %d\n", ans1, ans2);
	return 0;
}
