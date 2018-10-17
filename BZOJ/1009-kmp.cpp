#include <cstdio>
#include <cstring>

int n, m, M;
char s[1000];
int nextx[1000];
int mat[22][22], ans[22][22], z[22][22];
int anss;

void getnextx()
{
	int j = 0;
	for (int i = 2; i <= m; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = nextx[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		nextx[i] = j;
	}
}

void mul(int x[22][22], int y[22][22])
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			z[i][j] = 0;
		}
	}
	for (int k = 0; k < m; k++)
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				z[i][j] = (z[i][j] + (long long)x[i][k] * y[k][j] % M) % M;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			x[i][j] = z[i][j];
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &M);
	scanf("%s", s + 1);
	getnextx();
	for (int i = 0; i < m; i++)
	{
		for (char j = '0'; j <= '9'; j++)
		{
			int tmp = i;
			while (tmp && s[tmp + 1] != j)
			{
				tmp = nextx[tmp];
			}
			if (s[tmp + 1] == j)
			{
				tmp++;
			}
			if (tmp != m)
			{
				mat[i][tmp]++;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		ans[i][i] = 1;
	}
	while (n)
	{
		if (n & 1)
		{
			mul(ans, mat);
		}
		mul(mat, mat);
		n >>= 1;
	}
	anss = 0;
	for (int i = 0; i < m; i++)
	{
		anss = (anss + ans[0][i]) % M;
	}
	printf("%d\n", anss);
	return 0;
}
