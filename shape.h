#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <algorithm>
#include "point.h"
#include "line.h"
#include "color32.h"
#include "framebuffer.h"
#include "matrix.h"
#include "gradient.h"

using namespace std;

class Shape {
  private:
  	vector<Point> vertices;
	vector<Line> lines;
	int ymax;
	int ymin;  
	Point centroid;
	int isIntersect(Line, int);
  public:
    Shape();
    Shape(vector<Point> vertices);
    void setVertices(vector<Point> vertices);
    void fill(Color32 color, Framebuffer* f, vector<Point> windowBorder);
    void getTipotForWindow(vector<Point> *tipot, vector<Point> windowBorder);
    void fillGradient(Color32 color, int interval, Framebuffer* f);
    void transform(int dx, int dy, float scale, float rotation);
};

#endif
