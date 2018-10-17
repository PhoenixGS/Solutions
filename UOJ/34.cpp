#include <cstdio>
#include <cmath>
#include <algorithm>

struct Complex
{
	double real, imag;
	
	Complex(){}

	Complex(double _real, double _imag): real(_real), imag(_imag){}
};

const double pi = acos(-1);
int n, m;
int bit;
Complex x[300000], y[300000];
int rev[300000];

inline Complex operator + (Complex x, Complex y)
{
	return Complex(x.real + y.real, x.imag + y.imag);
}

inline Complex operator - (Complex x, Complex y)
{
	return Complex(x.real - y.real, x.imag - y.imag);
}

inline Complex operator * (Complex x, Complex y)
{
	return Complex(x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real);
}

void get_rev(int bit)
{
	for (int i = 0; i < (1 << bit); i++)
	{
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	}
}

void FFT(Complex *x, int n, int cas)
{
	for (int i = 0; i < n; i++)
	{
		if (i < rev[i])
		{
			std::swap(x[i], x[rev[i]]);
		}
	}
	for (int i = 1; i < n; i <<= 1)
	{
		Complex wn(cos(pi / i), cas * sin(pi / i));
		for (int j = 0; j < n; j += (i << 1))
		{
			Complex w(1, 0);
			for (int k = 0; k < i; k++, w = w * wn)
			{
				Complex xx = x[j + k];
				Complex yy = w * x[j + k + i];
				x[j + k] = xx + yy;
				x[j + k + i] = xx - yy;
			}
		}
	}
	if (cas == -1)
	{
		for (int i = 0; i < n; i++)
		{
			x[i] = Complex(x[i].real / n, x[i].imag / n);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)
	{
		scanf("%lf", &x[i].real);
	}
	for (int i = 0; i <= m; i++)
	{
		scanf("%lf", &y[i].real);
	}
	m = n + m;
	bit = 0;
	for (n = 1; n <= m; n <<= 1)
	{
		bit++;
	}
	get_rev(bit);
	FFT(x, n, 1);
	FFT(y, n, 1);
	for (int i = 0; i <= n; i++)
	{
		x[i] = x[i] * y[i];
	}
	FFT(x, n, -1);
	for (int i = 0; i <= m; i++)
	{
		printf("%d ", (int)(x[i].real + 0.5));
	}
	puts("");
	return 0;
}
