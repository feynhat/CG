#include "Graphics.h"
#include <vector>
#include <cmath>
#include <algorithm>

namespace CG {

	float dist(Point p, Point q)
	{
		float dx = p.x - q.x;
		float dy = p.y - q.y;
		return sqrt(dx*dx + dy*dy);
	}

	bool Point::operator<(Point p)
	{
		if (x < p.x) return true;
		if (x == p.x && y < p.y) return true;
		return false;
	}

	bool Point::operator==(Point p)
	{
		if (x == p.x && y == p.y) return true;
		return false;
	}

	float LineSegment::length()
	{
		return dist(begin, end);
	}

	bool LineSegment::pointOnLeft(Point p)
	{
		float D = (end.x*p.y - p.x*end.y) - (begin.x*p.y - p.x*begin.y)
			+ (begin.x*end.y - end.x*begin.y);
		if (D > 0) return true;
		return false;
	}

	bool LineSegment::pointOnRight(Point p)
	{
		float D = (end.x*p.y - p.x*end.y) - (begin.x*p.y - p.x*begin.y)
			+ (begin.x*end.y - end.x*begin.y);
		if (D < 0) return true;
		return false;
	}

	bool LineSegment::pointOnLine(Point p)
	{
		float D = (end.x*p.y - p.x*end.y) - (begin.x*p.y - p.x*begin.y)
			+ (begin.x*end.y - end.x*begin.y);
		if (D == 0) return true;
		return false;
	}

	bool LineSegment::pointInSegment(Point p)
	{
		if (abs(dist(begin, p) + dist(p, end) - length()) < EPSILON) return true;
		return false;
	}

	bool LineSegment::intersects(LineSegment l)
	{
		Point p = intersection(l);
		return p.x > -INFINITY && pointInSegment(p) && l.pointInSegment(p);
	}

	std::vector<float> LineSegment::equation()
	{
		float a = (end.y - begin.y);
		float b = -(end.x - begin.x);
		float c = begin.y*(end.x-begin.x)-begin.x*(end.y-begin.y);
		std::vector<float> out = {a, b, c};
		return out;
	}

	Point LineSegment::intersection(LineSegment l)
	{
		auto eq1 = equation();
		auto eq2 = l.equation();
		float D = eq1[0]*eq2[1] - eq2[0]*eq1[1];
		float X = -INFINITY;
		float Y = -INFINITY;
		if (D) {
			X = (eq1[1]*eq2[2] - eq2[1]*eq1[2])/D;
			Y = (eq1[2]*eq2[0] - eq2[2]*eq1[0])/D;
		}
		return Point(X, Y);
	}

}
