#include <iostream>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

const double EPSILON = 1e-9;
const double INFTY = 1e200;
const double PI = 2.0*acos(0.0);

struct vector2 {
	double x, y;

	explicit vector2(double x_ = 0, double y_ = 0) :x(x_), y(y_) {}

	bool operator == (const vector2& rhs) const {
		return x == rhs.x&&y == rhs.y;
	}

	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const {
		return vector2(x*rhs, y*rhs);
	}

	double norm() const {
		return hypot(x, y);
	}

	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	double polar() const {
		return fmod(atan2(y, x) + 2 * PI, 2 * PI);
	}

	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double cross(const vector2& rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

double howMuchCloser(vector2 p, vector2 a, vector2 b) {
	return (b - p).norm() - (a - p).norm();
}

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) {
		return false;
	}
	x = a + (b - a)*((c - a).cross(d - c) / det);
	return true;
}

bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (b < a) {
		swap(a, b);
	}
	if (d < c) {
		swap(c, d);
	}
	if (ccw(a, b, c) != 0 || b < c || d < a) {
		return false;
	}
	if (a < c) {
		p = c;
	} else {
		p = a;
	}
	return true;
}

bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
	if (b < a) {
		swap(a, b);
	}
	return p == a || p == b || (a < p && p < b);
}

bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (!lineIntersection(a, b, c, d, p)) {
		return parallelSegments(a, b, c, d, p);
	}
	return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
}

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c)*ccw(a, b, d);
	double cd = ccw(c, d, a)*ccw(c, d, b);
	if (ab == 0 && cd == 0) {
		if (b < a) {
			swap(a, b);
		}
		if (d < c) {
			swap(c, d);
		}
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	return a + (p - a).project(b - a);
}

double pointToLine(vector2 p, vector2 a, vector2 b) {
	return (p - perpendicularFoot(p, a, b)).norm();
}

vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
	return (dir - dir.project(contact - center) * 2).normalize();
}

struct edge
{
	int a;
	int b;
	edge() :a(0), b(0) {}
	edge(int _a, int _b) :a(_a), b(_b)
	{
		//for using std::set
		if (a < b) {
			swap(a, b);
		}
	}
	const bool operator== (const edge &e) const {
		return a == e.a && b == e.b;
	}
	const bool operator<(const edge &e) const {
		if (a == e.a) {
			return b < e.b;
		}
		return a < e.a;
	}
};

struct triangle {
	int a, b, c;
	triangle():a(0),b(0),c(0){}
	triangle(int _a, int _b, int _c) :a(_a), b(_b), c(_c) {}
};

bool inCircle(vector2& a, vector2& b, vector2& c, vector2& d)
{
	vector2 ab = b - a;
	vector2 ac = c - a;
	vector2 ad = d - a;
	double isccw = ccw(ab, ac);
	double determinant =
		ad.x * ab.y * (ac.x * ac.x + ac.y * ac.y)
		+ ad.y * ac.x * (ab.x * ab.x + ab.y * ab.y)
		+ ab.x * ac.y * (ad.x * ad.x + ad.y * ad.y)
		- ad.x * ac.y * (ab.x * ab.x + ab.y * ab.y)
		- ad.y * ab.x * (ac.x * ac.x + ac.y * ac.y)
		- ab.y * ac.x * (ad.x * ad.x + ad.y * ad.y);
	return isccw > 0 ? determinant < 0 : determinant > 0;
}


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	vector<vector2>point(n + 3);
	for (int i = 0; i < n; ++i) {
		double x, y;
		cin >> x >> y;
		point[i] = vector2(x, y);
	}

	point[n] = vector2(-1e10, -1e10);
	point[n+1] = vector2(1e10, -1e10);
	point[n+2] = vector2(0, 1e10);
	vector<triangle>tri;
	tri.push_back(triangle(n, n + 1, n + 2));

	for (int i = 0; i < n; ++i) 
	{
		set<edge>poly;
		vector<bool>complete(tri.size(), false);
		for (int j = 0; j < tri.size(); ++j) {
			if (complete[j]) {
				continue;
			}
			triangle curT = tri[j];
			if (inCircle(point[curT.a], point[curT.b], point[curT.c], point[j])) {
				if (poly.count(edge(curT.a, curT.b))) {
					poly.erase(edge(curT.a, curT.b));
				} else {
					poly.insert(edge(curT.a, curT.b));
				}
				if (poly.count(edge(curT.b, curT.c))) {
					poly.erase(edge(curT.b, curT.c));
				} else {
					poly.insert(edge(curT.b, curT.c));
				}
				if (poly.count(edge(curT.c, curT.a))) {
					poly.erase(edge(curT.c, curT.a));
				} else {
					poly.insert(edge(curT.c, curT.a));
				}

				swap(complete[j], complete[tri.size() - 1]);
				swap(tri[j], tri[tri.size() - 1]);
				tri.pop_back();
				--j;
				continue;
			} else {
				complete[j] = true;
			}
		}
		for (auto &tmp : poly) {
			if ((point[tmp.b] - point[tmp.a]).cross(point[i] - point[tmp.a]) == 0) {
				continue;
			} else {
				tri.push_back(triangle(tmp.a, tmp.b, i));
			}
		}
	}

	cout << tri.size();
}
