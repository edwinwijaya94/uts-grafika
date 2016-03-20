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
	Point centroid;
	int isIntersect(Line, int);
  public:
	int ymax;
	int ymin;
	int xmax;
	int xmin;
	
    Shape();
    Shape(vector<Point> vertices);
    vector<Point> getVertices();
    void setVertices(vector<Point> vertices);
    void draw(Framebuffer* f, Color32 color);
    void fill(Color32 color, Framebuffer* f, vector<Point> windowBorder);
    void fillGradient(Color32 color, int interval, Framebuffer* f);
    void transform(int dx, int dy, float scale, float rotation);
    void unfill(Color32 color, Framebuffer* f, vector<Point> windowBorder);
    void undraw(Framebuffer* f);
    void setCentroid(Point newPoint);
};

#endif
