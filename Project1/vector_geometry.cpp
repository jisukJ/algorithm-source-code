#include <iostream>
#include <cmath>
#include <vector>

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


//PINBALL
int C, N;
vector2 center[50];
int radius[50];

vector<double> solve2(double a, double b, double c) {
	double d = b * b - 4 * a * c;
	if (d < -EPSILON) {
		return vector<double>();
	}
	if (d < EPSILON) {
		return vector<double>(1, -b / (2 * a));
	}
	vector<double>ret;
	ret.push_back((-b - sqrt(d)) / (2 * a));
	ret.push_back((-b + sqrt(d)) / (2 * a));
	return ret;
}

double hitCircle(vector2 here, vector2 dir, vector2 center, int radius) {
	double a = dir.dot(dir);
	double b = 2 * dir.dot(here - center);
	double c = center.dot(center) + here.dot(here) - 2 * here.dot(center) - radius * radius;
	vector<double> sols = solve2(a, b, c);
	if (sols.empty() || sols[0] < EPSILON) {
		return INFTY;
	}
	return sols[0];
}
void simulate(vector2 here, vector2 dir) {
	dir = dir.normalize();
	int hitCount = 0;
	while (hitCount < 100) {
		int cir = -1;
		double time = INFTY * 0.5;
		for (int i = 0; i < N; ++i) {
			double cand = hitCircle(here, dir, center[i], radius[i] + 1);
			if (cand < time) {
				time = cand;
				cir = i;
			}
		}
		if (cir == -1) {
			break;
		}
		if (hitCount++) {
			cout << " ";
		}
		cout << cir;
		vector2 contact = here + dir * time;
		dir = reflect(dir, center[cir], contact);
		here = contact;
	}
	cout << endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> C;
	for (int test = 1; test <= C; ++test) {
		double x, y, dx, dy;
		cin >> x >> y >> dx >> dy >> N;
		vector2 here(x, y);
		vector2 dir(dx, dy);
		for (int i = 0; i < N; ++i) {
			cin >> center[i].x >> center[i].y >> radius[i];
		}
		simulate(here, dir);
	}
}