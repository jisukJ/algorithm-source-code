#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
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

typedef vector<vector2>polygon;

double area(const polygon& p) {
	double ret = 0;
	for (int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();
		ret += p[i].x*p[j].y - p[j].x*p[i].y;
	}
	return fabs(ret) / 2.0;
}

bool isInside(vector2 q, const polygon& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();
		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			double atX = (p[j].x - p[i].x)*(q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX) {
				++crosses;
			}
		}
	}
	return crosses % 2 > 0;
}


int C, N;
polygon input;
vector2 map1, map2;

polygon cutPoly(const polygon& p, const vector2& a, const vector2& b) {
	int n = p.size();
	vector<bool>inside(n);
	for (int i = 0; i < n; ++i) {
		inside[i] = ccw(a, b, p[i]) >= 0;
	}
	polygon ret;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		if (inside[i]) {
			ret.push_back(p[i]);
		}
		if (inside[i] != inside[j]) {
			vector2 cross;
			assert(lineIntersection(p[i], p[j], a, b, cross));
			ret.push_back(cross);
		}
	}
	return ret;
}

polygon sutherlandHodgman(const polygon& p, double x1, double y1, double x2, double y2) {
	vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	ret = cutPoly(ret, d, a);
	return ret;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed;
	cout.precision(10);
	cin >> C;
	for (int test = 1; test <= C; ++test) {
		input.clear();
		cin >> map1.x >> map1.y >> map2.x >> map2.y >> N;
		for (int i = 0; i < N; ++i) {
			double x, y;
			cin >> x >> y;
			vector2 tmp(x, y);
			input.push_back(tmp);
		}
		cout << area(sutherlandHodgman(input, map1.x, map1.y, map2.x, map2.y))<<"\n";
	}
}