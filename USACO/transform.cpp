/*
ID: thestar1
PROG: transform
LANG: C++
*/

#include <cstdio>
#include <vector>

using namespace std;

typedef vector<vector<int> > Vector;

Vector ans;
Vector vec;
Vector blank;
int n;
char st[100];

Vector f1(Vector x)
{
	Vector A = blank;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			A[j][n - i + 1] = x[i][j];
		}
	}
	return A;
}

Vector f2(Vector x)
{
	return f1(f1(x));
}

Vector f3(Vector x)
{
	return f1(f1(f1(x)));
}

Vector f4(Vector x)
{
	Vector A = blank;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			A[i][n - j + 1] = x[i][j];
		}
	}
	return A;
}

bool f5(Vector x)
{
	return f1(f4(x)) == ans || f2(f4(x)) == ans || f3(f4(x)) == ans;
}

Vector f6(Vector x)
{
	return x;
}

int main()
{
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++)
	{
		vector<int> tmp;
		for (int j = 1; j <= n + 1; j++)
		{
			tmp.push_back(0);
		}
		blank.push_back(tmp);
	}
	vec = blank;
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", st + 1);
		for (int j = 1; j <= n; j++)
		{
			if (st[j] == '@')
			{
				vec[i][j] = 0;
			}
			else
			{
				vec[i][j] = 1;
			}
		}
	}
	ans = blank;
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", st + 1);
		for (int j = 1; j <= n; j++)
		{
			if (st[j] == '@')
			{
				ans[i][j] = 0;
			}
			else
			{
				ans[i][j] = 1;
			}
		}
	}
	if (f1(vec) == ans)
	{
		printf("1\n");
		return 0;
	}
	if (f2(vec) == ans)
	{
		printf("2\n");
		return 0;
	}
	if (f3(vec) == ans)
	{
		printf("3\n");
		return 0;
	}
	if (f4(vec) == ans)
	{
		printf("4\n");
		return 0;
	}
	if (f5(vec))
	{
		printf("5\n");
		return 0;
	}
	if (f6(vec) == ans)
	{
		printf("6\n");
		return 0;
	}
	printf("7\n");
	return 0;
}
