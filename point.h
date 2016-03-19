#ifndef POINT_H
#define POINT_H

// typedef struct {
// 	int x;
// 	int y;
// } Point;

/*typedef struct {
	int x;
	int y;
} Pointf;*/

class Point {
  public:
  	int x;
  	int y;
  	Point() { }
  	Point(int x, int y) { this->x = x; this->y = y; }
  	bool operator < (const Point& p) const
  	{
  		return (x < p.x);
  	}
};

#endif
