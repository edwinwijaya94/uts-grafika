#include <vector>
#include <map>
#include <iostream>
#include "framebuffer.h"
#include "input.h"
#include "color32.h"
#include "point2.h"
#include "file.h"
#include "shape.h"
#include "maillot.h"
#include <unistd.h>

using namespace std;

Framebuffer framebuffer;

int main(){
	framebuffer.ClearScreen();
	framebuffer.SwapBuffers();
	set_conio_terminal_mode();
	
	vector<string> filenames;
    filenames.push_back("indomap.txt");

	initMatrix();
	
	//window border
	vector<Point> windowBorder; // define 4 corner points of a window
	windowBorder.push_back((Point){0,0});
	windowBorder.push_back((Point){framebuffer.width, 0});
	windowBorder.push_back((Point){framebuffer.width, framebuffer.height});
	windowBorder.push_back((Point){0, framebuffer.height});
	
	map<string, vector<Point> > points = getPointsFromFile(filenames);
	
	//vector<Shape> areas;
	map<string, Shape> areas;

	Point Pmin = {0, 0};
	Point Pmax = {framebuffer.width, framebuffer.height};
	//Shape res = Pclip(shape3, Pmin, Pmax);

	for(map<string, vector<Point>>::iterator it=points.begin(); it!=points.end(); it++){
		vector<Point> Pol = it->second;
		string str = it->first;
	
		Shape s(Pol);
		Shape sclip = Pclip(s, Pmin, Pmax);
		//s.draw(&framebuffer, WHITE);
		sclip.draw(&framebuffer, WHITE);
		//areas.push_back(s); // add new area
		//areas[str] = s;
		areas[str] = sclip;
	}
	printf("area size %d\n", areas.size());	

	// fill areas
	// for(int i=0; i<areas.size(); i++){
	// 	//areas[i].fill(WHITE, &framebuffer, windowBorder);
	// }
	framebuffer.SwapBuffers();

	map<string, Shape>::iterator it=areas.begin();
	it->second.fill(RED, &framebuffer, windowBorder);
	framebuffer.SwapBuffers();

	while(1){
		char c = getch();
		// if(c == 'd'){ //fill next area
		// 	if (next(it) != areas.end()) {
		// 		it->second.unfill(&framebuffer, windowBorder);
		// 		it->second.draw(&framebuffer, WHITE);
		// 		it++;
		// 		it->second.fill(RED, &framebuffer, windowBorder);
		// 		framebuffer.SwapBuffers();
		// 	}
		// } 
		// else if(c == 'a'){ //fill previous area
		// 	if (prev(it) != prev(areas.begin())) {
		// 		it->second.unfill(&framebuffer, windowBorder);
		// 		it->second.draw(&framebuffer, WHITE);
		// 		it--;
		// 		it->second.fill(RED, &framebuffer, windowBorder);	
		// 		framebuffer.SwapBuffers();
		// 	}
		// }
		if (c == 'w') {
			areas["ForeignArea56"].undraw(&framebuffer);
			areas["ForeignArea56"].transform(0, -1, 1, 0);
			areas["ForeignArea56"].draw(&framebuffer, WHITE);
			//areas["ForeignArea56"].fill(RED, &framebuffer, windowBorder);
			framebuffer.SwapBuffers();
		}
		else if (c == 's') {
			areas["ForeignArea56"].undraw(&framebuffer);
			areas["ForeignArea56"].transform(0, 1, 1, 0);
			areas["ForeignArea56"].draw(&framebuffer, WHITE);
			//areas["ForeignArea56"].fill(RED, &framebuffer, windowBorder);
			framebuffer.SwapBuffers();
		}
		else if (c == 'a') {
			areas["ForeignArea56"].undraw(&framebuffer);
			areas["ForeignArea56"].transform(-1, 0, 1, 0);
			areas["ForeignArea56"].draw(&framebuffer, WHITE);
			//areas["ForeignArea56"].fill(RED, &framebuffer, windowBorder);
			framebuffer.SwapBuffers();
		}
		else if (c == 'd') {
			areas["ForeignArea56"].undraw(&framebuffer);
			areas["ForeignArea56"].transform(1, 0, 1, 0);
			areas["ForeignArea56"].draw(&framebuffer, WHITE);
			//areas["ForeignArea56"].fill(RED, &framebuffer, windowBorder);
			framebuffer.SwapBuffers();
		}
		else if(c == 'x'){
			break;
		}
		

	}

	//printf("area highlighted: %s\n", it->first);	
	//cout << it->first << endl;

	vertices<Point> pmy = areas["ForeignArea56"].getVertices();

	for (int i = 0; i < pmy.size(); i++) {

	}

	return 0;
}
