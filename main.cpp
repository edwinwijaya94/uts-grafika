#include <vector>
#include <map>
#include <iostream>
#include "framebuffer.h"
#include "input.h"
#include "color32.h"
#include "point2.h"
#include "file.h"
#include "shape.h"
#include <unistd.h>

using namespace std;

Framebuffer framebuffer;

void moveUp(vector<Point2> *points_edit, Point2 *point_idx, int n){
	double t;
	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, BLACK);
	}

	framebuffer.SwapBuffers();

	point_idx->y -= n;

	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, WHITE);
	}

	framebuffer.SwapBuffers();
}

void moveUp(vector<Point2> *points_edit, Point2 *point_idx){
	moveUp(points_edit, point_idx, 5);
}

void moveDown(vector<Point2> *points_edit, Point2 *point_idx, int n){
	double t;
	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, BLACK);
	}

	framebuffer.SwapBuffers();

	point_idx->y += n;

	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, WHITE);
	}

	framebuffer.SwapBuffers();
}

void moveDown(vector<Point2> *points_edit, Point2 *point_idx){
	moveDown(points_edit, point_idx, 5);
}

void moveRight(vector<Point2> *points_edit, Point2 *point_idx, int n){
	double t;
	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, BLACK);
	}

	framebuffer.SwapBuffers();

	for (int i = 0; i < points_edit->size(); i++) {
		points_edit->at(i).x += n;
	}

	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, WHITE);
	}

	framebuffer.SwapBuffers();
}

void moveRight(vector<Point2> *points_edit, Point2 *point_idx){
	moveRight(points_edit, point_idx, 5);
}

void moveLeft(vector<Point2> *points_edit, Point2 *point_idx, int n){
	double t;
	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, BLACK);
	}

	framebuffer.SwapBuffers();

	for (int i = 0; i < points_edit->size(); i++) {
		points_edit->at(i).x -= n;
	}

	for (double i = 0.0; i < 1.0; i+=0.01) {
		t = i;
		framebuffer.drawCurve(*points_edit, t, WHITE);
	}

	framebuffer.SwapBuffers();
}

void moveLeft(vector<Point2> *points_edit, Point2 *point_idx){
	moveLeft(points_edit, point_idx, 5);
}

int main(){
	framebuffer.ClearScreen();
	framebuffer.SwapBuffers();
	set_conio_terminal_mode();
	
	vector<string> filenames;
    filenames.push_back("indomap.txt");
	
	double t;
	
	//window border
	vector<Point> windowBorder; // define 4 corner points of a window
	windowBorder.push_back((Point){0,0});
	windowBorder.push_back((Point){framebuffer.width, 0});
	windowBorder.push_back((Point){framebuffer.width, framebuffer.height});
	windowBorder.push_back((Point){0, framebuffer.height});
	
	map<string, vector<Point> > points = getPointsFromFile(filenames);
	
	vector<Shape> areas;
	
	for(map<string, vector<Point>>::iterator it=points.begin(); it!=points.end(); it++){
		vector<Point> Pol = it->second;
		for(int k=0; k<Pol.size(); k++){
			framebuffer.DrawLine(Pol[k], Pol[(k+1)%Pol.size()], (Color32){255,255,255,255});
		}
		Shape* s = new Shape(Pol);
		areas.push_back(*s); // add new area
	}
	printf("area size %d\n", areas.size());	
	// fill areas
	for(int i=0; i<areas.size(); i++){
		areas[i].fill(WHITE, &framebuffer, windowBorder);
	}
	
	
	//vector<Point2> *points_edit;

	/*while (1) {
		

		usleep(20000);
	}*/

	return 0;
}
