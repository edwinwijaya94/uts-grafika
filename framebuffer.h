#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <cmath>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include "color32.h"
#include "point2.h"
#include "point.h"
#include "line.h"

using namespace std;

class Framebuffer {
	private:
		int fbfd;
		struct fb_var_screeninfo vinfo;
		struct fb_fix_screeninfo finfo;
		long int screensize;
		char *fbp;
		char *bbp;
		int IsIntersect(Line line, int y);
		void SortTipot(vector<Point> &tipot);
	public:
		int width;
		int height;
		Framebuffer();
		~Framebuffer();
		void SwapBuffers();
		void ClearScreen();
		void SetPixel(int x, int y, Color32 color);
		void DrawLine(Point p0, Point p1, Color32 color);
		void drawCurve(vector<Point2> points, double t, Color32 color);
		// void DrawPolygon(Polygon2& polygon, Color32 color);
		// void FillPolygon(Polygon2& polygon, Color32 color, bool freeMatrix[][1300]);
};

#endif
