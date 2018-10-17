#include <cstdio>
#include <cmath>
#include <map>

typedef long long ll;

int T, cas;
int x, y, M;
std::map<int, int> map;

int pow_mod(int x, int p, int M)
{
	int ans = 1;
	int tmp = x;
	while (p)
	{
		if (p & 1)
		{
			ans = (long long)ans * tmp % M;
		}
		tmp = (long long)tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int exgcd(int a, int &x, int b, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, x, a % b, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return d;
}

void solve2(int x, int y, int M)
{
	int d = gcd(x, M);
	if (y % d)
	{
		printf("Orz, I cannot find x!\n");
		return;
	}
	x /= d;
	y /= d;
	M /= d;
	int xx, yy;
	d = exgcd(x, xx, M, yy);
	int ans = (long long)y * xx % M;
	ans = (ans + M) % M;
	printf("%d\n", ans);
}

void solve3(int x, int y, int M)
{
	x = x % M;
	if (! x && ! y)
	{
		printf("1\n");
		return;
	}
	if (! x)
	{
		printf("Orz, I cannot find x!\n");
		return;
	}
	map.clear();
	int m = ceil(sqrt(M));
	int ans = 1;
	for (int i = 0; i <= m; i++)
	{
		if (i == 0)
		{
			ans = y % M;
			map[ans] = i;
		}
		else
		{
			ans = (long long)ans * x % M;
			map[ans] = i;
		}
	}
	int tmp = pow_mod(x, m, M);
	ans = 1;
	for (int i = 1; i <= m; i++)
	{
		ans = (long long)ans * tmp % M;
		if (map[ans])
		{
			int anss = i * m - map[ans];
			anss = (anss % (M - 1) + (M - 1)) % (M - 1);
			printf("%d\n", anss);
			return;
		}
	}
	printf("Orz, I cannot find x!\n");
}

/*
std::map<int, int> mp;
void solve3(int y,int z,int p)
{
	y%=p;
	if(!y&&!z){puts("1");return;}
	if(!y){puts("Orz, I cannot find x!");return;}
	mp.clear();
	ll m=ceil(sqrt(p)),t=1;
	mp[1]=m+1;
	for(ll i=1;i<m;i++)
	{
		t=t*y%p;
		if(!mp[t])mp[t]=i;
	}
	ll tmp=pow_mod(y,p-m-1,p),ine=1;
	for(ll k=0;k<m;k++)
	{
		int i=mp[z*ine%p];
		if(i)
		{
			if(i==m+1)i=0;
			printf("%lld\n",k*m+i);
			return;
		}
		ine=ine*tmp%p;
	}
	puts("Orz, I cannot find x!");
}
*/
int main()
{
	scanf("%d%d", &T, &cas);
	while (T--)
	{
		scanf("%d%d%d", &x, &y, &M);
		if (cas == 1)
		{
			printf("%d\n", pow_mod(x, y, M));
		}
		if (cas == 2)
		{
			solve2(x, y, M);
		}
		if (cas == 3)
		{
			solve3(x, y, M);
		}
	}
	return 0;
}
