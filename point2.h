#ifndef POINT2_H
#define POINT2_H

#include <cmath>

class Point2{
	public:
		float x;
		float y;
		Point2();
		Point2(float x, float y);
		Point2 operator+(const Point2& other);
		Point2 operator-(const Point2& other);
		Point2 operator*(const Point2& other);
		Point2 operator/(const Point2& other);
		void operator=(const Point2& other);
		void Transform(Point2 centroid, float scale, float rotation);
};

#endif
