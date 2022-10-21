#include "Graphics.h"
#include <vector>
#include <algorithm>

namespace CG {
	
	Polygon ConvexHull(std::vector<Point>& points)
	{
		/*
		Input: a vector of **distinct** points
		Output: a Polygon object describing the bounding polygon of the convex
		hull in clockwise order, starting from the left-most point.

		This algorithm is an implementation of the incremental algorithm,
		described in [de Berg, van Kreveld et. al.]
		*/
		if (points.size() <= 2)
			return Polygon(points);

		std::vector<Point> upper_hull, lower_hull;
		Polygon convex_hull;
		int n = points.size();

		sort(points.begin(), points.end());

		upper_hull.push_back(points[0]);
		upper_hull.push_back(points[1]);

		for (int i = 2; i < n; ++i) {
			upper_hull.push_back(points[i]);
			int m = upper_hull.size();
			Point p = upper_hull[m-3];
			Point q = upper_hull[m-2];
			Point r = upper_hull[m-1];
			LineSegment l(p, q);
			while (l.pointOnLeft(r) && upper_hull.size() > 2) {
				upper_hull.erase(upper_hull.begin() + (m-2));
				m = upper_hull.size();
				p = upper_hull[m-3];
				q = upper_hull[m-2];
				l = LineSegment(p, q);
			}
		}
		for (int i = 0; i < upper_hull.size(); ++i) {
			convex_hull.points.push_back(upper_hull[i]);
		}

		lower_hull.push_back(points[n-1]);
		lower_hull.push_back(points[n-2]);

		for (int i = n-3; i >= 0; --i) {
			lower_hull.push_back(points[i]);
			int m = lower_hull.size();
			Point p = lower_hull[m-3];
			Point q = lower_hull[m-2];
			Point r = lower_hull[m-1];
			LineSegment l(p, q);
			while (l.pointOnLeft(r) && lower_hull.size() > 2) {
				lower_hull.erase(lower_hull.begin() + (m-2));
				m = lower_hull.size();
				p = lower_hull[m-3];
				q = lower_hull[m-2];
				l = LineSegment(p, q);
			}
		}
		for (int i = 1; i < lower_hull.size()-1; ++i) {
			convex_hull.points.push_back(lower_hull[i]);
		}

		return convex_hull;
	}

}
