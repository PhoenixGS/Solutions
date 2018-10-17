#include <cstdio>
#include <algorithm>

const double eps = 1e-10;
int n, m;
char s[400][400];
int fail[400][400];
double mat[400][400];
double mi[400];

double abss(double x)
{
	return x > eps ? x : -x;
}

void getfail(int *fail, char *s)
{
	int j = 0;
	for (int i = 2; i <= m; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		fail[i] = j;
	}
}

int cc(int *fail, char *s, char *t)
{
	int j = 0;
	for (int i = 1; i <= m; i++)
	{
		while (j && s[j + 1] != t[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == t[i])
		{
			j++;
		}
	}
	return j;
}

double calc(int *fail, char *s, char *t)
{
	int j = cc(fail, s, t);
	double ans = 0.0;
	for (; j; j = fail[j])
	{
		ans = ans + mi[m - j];
	}
	return ans;
}

void gauss(int n)
{
	for (int i = 1; i <= n; i++)
	{
		int r = i;
		for (int j = i; j <= n; j++)
		{
			if (abss(mat[j][i]) > abss(mat[r][i]))
			{
				r = j;
			}
		}
		for (int j = i; j <= n + 1; j++)
		{
			std::swap(mat[i][j], mat[r][j]);
		}
		for (int k = i + 1; k <= n; k++)
		{
			double t = mat[k][i] / mat[i][i];
			for (int j = i; j <= n + 1; j++)
			{
				mat[k][j] = mat[k][j] - t * mat[i][j];
			}
		}
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = n; j > i; j--)
		{
			mat[i][n + 1] -= mat[i][j] * mat[j][n + 1];
		}
		mat[i][n + 1] /= mat[i][i];
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s[i] + 1);
	}
	mi[0] = 1.0;
	for (int i = 1; i <= m; i++)
	{
		mi[i] = mi[i - 1] * 0.5;
	}
	for (int i = 1; i <= n; i++)
	{
		getfail(fail[i], s[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			mat[i][j] = calc(fail[i], s[i], s[j]);
		}
		mat[i][n + 1] = -mi[m];
		mat[i][n + 2] = 0.0;
	}
	for (int i = 1; i <= n; i++)
	{
		mat[n + 1][i] = 1.0;
	}
	mat[n + 1][n + 1] = 0.0;
	mat[n + 1][n + 2] = 1.0;
	gauss(n + 1);
	for (int i = 1; i <= n; i++)
	{
		printf("%.10f\n", mat[i][n + 2]);
	}
	return 0;
}
