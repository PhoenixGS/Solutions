/*
ID: thestar1
PROG: ride
LANG: C++
*/

#include <cstdio>
#include <cstring>

char x[100];
char y[100];
int n, m;
int xx, yy;

int main()
{
	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);
	scanf("%s", x + 1);
	scanf("%s", y + 1);
	n = strlen(x + 1);
	m = strlen(y + 1);
	xx = 1;
	for (int i = 1; i <= n; i++)
	{
		xx = xx * (x[i] - 64) % 47;
	}
	yy = 1;
	for (int i = 1; i <= m; i++)
	{
		yy = yy * (y[i] - 64) % 47;
	}
	if (xx == yy)
	{
		printf("GO\n");
	}
	else
	{
		printf("STAY\n");
	}
	return 0;
}
