#include <cstdio>
#include <cstring>

long long T, lx, rx, ly, ry;
long long ff[70][10000];

inline int cc(int pos, int cas, int x, int y)
{
	register int casx = cas / 4;
	register int casy = cas % 4;
	register int upx = casx == 1 || casx == 3;
	register int downx = casx == 2 || casx == 3;
	register int upy = casy == 1 || casy == 3;
	register int downy = casy == 2 || casy == 3;
	if (upx)
	{
		if (x > ((rx >> pos) & 1))
		{
			return -1;
		}
		upx = x == ((rx >> pos) & 1);
	}
	if (downx)
	{
		if (x < ((lx >> pos) & 1))
		{
			return -1;
		}
		downx = x == ((lx >> pos) & 1);
	}
	if (upy)
	{
		if (y > ((ry >> pos) & 1))
		{
			return -1;
		}
		upy = y == ((ry >> pos) & 1);
	}
	if (downy)
	{
		if (y < ((ly >> pos) & 1))
		{
			return -1;
		}
		downy = y == ((ly >> pos) & 1);
	}
	register int tmp = 0;
	tmp += (downx << 1 | upx) << 2;
	tmp += (downy << 1 | upy);
	return tmp;
}

int trans(int pos, int cas, int x, int y)
{
	int tmp = 0;
	for (int i = 0; i < 16; i++)
	{
		if (cas & (1 << i))
		{
			int t = cc(pos, i, x, y);
			if (t != -1)
			{
				tmp = tmp | (1 << t);
			}
		}
	}
	return tmp;
}

long long f(int pos, int cas)
{
	if (pos == -1)
	{
		return 1ll;
	}
	if (ff[pos][cas] != -1)
	{
		return ff[pos][cas];
	}
	long long ans = 0;
	if ((T >> pos) & 1)
	{
		{
			int tmp = trans(pos, cas, 0, 1) | trans(pos, cas, 1, 0);
			if (tmp)
			{
				ans += f(pos - 1, tmp);
			}
		}
		{
			int tmp = trans(pos, cas, 1, 1);
			if (tmp)
			{
				ans += f(pos - 1, tmp);
			}
		}
	}
	else
	{
		int tmp = trans(pos, cas, 0, 0);
		if (tmp)
		{
			ans += f(pos - 1, tmp);
		}
	}
	return ff[pos][cas] = ans;
}

int main()
{
	scanf("%lld%lld%lld%lld%lld", &T, &lx, &rx, &ly, &ry);
	memset(ff, -1, sizeof(ff));
	printf("%lld\n", f(61, 1 << 15));
	return 0;
}
