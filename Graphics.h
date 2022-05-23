#include <vector>

namespace CG {

	struct Point {
		Point() : x{0}, y{0} {};
		Point(float f1, float f2) : x{f1}, y{f2} {};
		float x;
		float y;
		bool operator<(Point);
		bool operator==(Point);
	};

	struct LineSegment {
		LineSegment(Point p, Point q) : begin{p}, end{q} {};
		Point begin;
		Point end;
		float length();
		bool pointOnLeft(Point p);
		bool pointOnRight(Point p);
		bool pointOnLine(Point p);
		bool pointInSegment(Point p);
	};

	struct Polygon {
		Polygon() {};
		Polygon(std::vector<Point>& v) : points{v} {};
		std::vector<Point> points;
	};

	float dist(Point, Point);

	Polygon ConvexHull(std::vector<Point>&);
	
	std::vector<Point> Intersections(std::vector<LineSegment>&);
}
