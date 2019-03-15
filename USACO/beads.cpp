/*
ID: thestar1
PROG: beads
LANG: C++
*/

#include <cstdio>
#include <algorithm>

using namespace std;

int n;
char st[1000];
int x[1000];
int f1[1000][3];
int f2[1000][3];

int main()
{
	freopen("beads.in", "r", stdin);
	freopen("beads.out", "w", stdout);
	scanf("%d", &n);
	scanf("%s", st + 1);
	for (int i = 1; i <= n; i++)
	{
		if (st[i] == 'r')
		{
			x[i] = 1;
		}
		if (st[i] == 'b')
		{
			x[i] = 2;
		}
		if (st[i] == 'w')
		{
			x[i] = 3;
		}
	}
	for (int i = n + 1; i <= 2 * n; i++)
	{
		x[i] = x[i - n];
	}
	for (int i = 1; i <= 2 * n; i++)
	{
		if (x[i] == 1)
		{
			f1[i][1] = f1[i - 1][1] + 1;
		}
		if (x[i] == 2)
		{
			f1[i][2] = f1[i - 1][2] + 1;
		}
		if (x[i] == 3)
		{
			f1[i][1] = f1[i - 1][1] + 1;
			f1[i][2] = f1[i - 1][2] + 1;
		}
	}
	for (int i = 2 * n; i >= 1; i--)
	{
		if (x[i] == 1)
		{
			f2[i][1] = f2[i + 1][1] + 1;
		}
		if (x[i] == 2)
		{
			f2[i][2] = f2[i + 1][2] + 1;
		}
		if (x[i] == 3)
		{
			f2[i][1] = f2[i + 1][1] + 1;
			f2[i][2] = f2[i + 1][2] + 1;
		}
	}
	int ans = 0;
	for (int i = 1; i < 2 * n; i++)
	{
		ans = max(ans, max(f1[i][1], f1[i][2]) + max(f2[i + 1][1], f2[i + 1][2]));
	}
	printf("%d\n", min(ans, n));
	return 0;
}
