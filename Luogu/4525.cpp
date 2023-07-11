#include <cstdio>
#include <cmath>

const double eps = 1e-8;
double a, b, c, d, L, R;

double f(double x)
{
	return (c * x + d) / (a * x + b);
}

double simpson(double l, double r)
{
	double mid = (l + r) / 2;
	return (r - l) * (f(l) + f(r) + 4 * f(mid)) / 6;
}

double asr(double l, double r, double eps, double ans)
{
	double mid = (l + r) / 2;
	double fl = simpson(l, mid);
	double fr = simpson(mid, r);
	if (fabs(fl + fr - ans) <= 15 * eps)
	{
		return fl + fr + (fl + fr - ans) / 15;
	}
	return asr(l, mid, eps, fl) + asr(mid, r, eps, fr);
}

int main()
{
	scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &L, &R);
	printf("%.6f\n", asr(L, R, eps, simpson(L, R)));
	return 0;
}
