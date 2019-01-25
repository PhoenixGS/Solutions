/*
ID: thestar1
PROG: friday
LANG: C++
*/

#include <cstdio>

int n;
int last;
int ans[10];
int monthx[12] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

int main()
{
	freopen("friday.in", "r", stdin);
	freopen("friday.out", "w", stdout);
	last = 3;
	scanf("%d", &n);
	for(int year = 1900; year < 1900 + n; year++)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			monthx[2] = 29;
		}
		for (int month = 0; month < 12; month++)
		{
			last = (last + monthx[month]) % 7;
			ans[last]++;
		}
		monthx[2] = 28;
	}
	for (int i = 0; i < 6; i++)
	{
		printf("%d ", ans[(i + 6) % 7]);
	}
	printf("%d\n", ans[5]);
	return 0;
}
