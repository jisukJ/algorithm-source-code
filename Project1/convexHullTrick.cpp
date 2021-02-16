#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

struct linearFunc {
	long long a, b;
	double s;
	linearFunc() :linearFunc(1, 0) {}
	linearFunc(long long _a, long long _b) : a(_a), b(_b), s(0) {}
};

int N;
long long A[100001];
long long B[100001];
long long mem[100001];
linearFunc funcStack[100001];
int top=0;

inline double cross(linearFunc &f1, linearFunc &f2) {
	return (f2.b - f1.b) / (f1.a - f2.a);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}
	for (int i = 1; i <= N; ++i) {
		cin >>B[i];
	}
	for (int i = 1; i <= N; ++i) {
		linearFunc tmpF(B[i-1], mem[i - 1]);
		while (0<top) {
			tmpF.s = cross(funcStack[top-1], tmpF);
			if (funcStack[top-1].s < tmpF.s) {
				break;
			} else {
				--top;
			}
		}
		funcStack[top++]=tmpF;

		long long x = A[i];
		int fpos = top - 1;
		if (x < funcStack[top - 1].s) {
			int lo = 0, hi = top - 1;
			while (lo + 1 < hi) {
				int mid = (lo + hi) / 2;
				(x < funcStack[mid].s ? hi : lo) = mid;
			}
			fpos = lo;
		}
		mem[i] = funcStack[fpos].a*x + funcStack[fpos].b;
	}
	cout << mem[N];
}