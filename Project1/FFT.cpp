#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = acos(-1);

void FFT(vector<complex<double>>& a, complex<double> w)
{
	int n = a.size();
	if (n == 1) {
		return;
	}
	vector<complex<double>>odd(n / 2), even(n / 2);
	for (int i = 0; i < n; ++i) {
		if (i % 2 == 1) {
			odd[i / 2] = a[i];
		} else {
			even[i / 2] = a[i];
		}
	}
	FFT(odd, w*w);
	FFT(even, w*w);
	complex<double>power(1, 0);
	for (int i = 0; i < n / 2; ++i) {
		a[i] = even[i] + power * odd[i];
		a[n / 2 + i] = even[i] - power * odd[i];
		power *= w;
	}
}

vector<complex<double>>multiply(vector<complex<double>>&a, vector<complex<double>>&b)
{
	int n = 1;
	while (n < max(a.size(), b.size())) {
		n *= 2;
	}
	n *= 2;
	a.resize(n);
	b.resize(n);
	vector<complex<double>>c(n);
	complex<double>w(cos(2 * PI / n), sin(-2 * PI / n));
	FFT(a, w);
	FFT(b, w);
	for (int i = 0; i < n; ++i) {
		c[i] = a[i] * b[i];
	}
	FFT(c, complex<double>(1, 0) / w);
	for (int i = 0; i < n; ++i) {
		c[i] /= complex<double>(n, 0);
	}
	return c;
}

int main()
{
	vector<complex<double>>a;
	vector<complex<double>>b;
	vector<complex<double>>c;
	a.push_back(1);
	a.push_back(1);
	b.push_back(1);
	b.push_back(1);
	c = multiply(a, b);
	for (int i = 0; i < c.size(); ++i) {
		cout << c[i]<<" ";
	}
}

