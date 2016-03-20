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
//#include <fstream>

#define MAXCITIZEN 43200000 // max citizen in a province

using namespace std;

Framebuffer framebuffer;

Color32 getAreaColour(int citizen){
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 255;
	
	float frac = float(citizen) / MAXCITIZEN;
	if(frac >0.5){
		r = 255;
		g = (int)(2*(1-frac) * 255);
	}
	else{
		r = (int)(2*(1-frac) * 255);
		g = 255;
	}
	
	Color32 res = (Color32){r,g,b,a};
	
	return res;
}

int main(){
	framebuffer.ClearScreen();
	framebuffer.SwapBuffers();
	set_conio_terminal_mode();
	
	vector<string> filenames;
    filenames.push_back("indomap.txt");
    int hex = "#89abe3";
    cout << "Hex : :" << hex;
    //Filenames for coloring the map based on total population of each province
    vector<string> populationFile;
    populationFile.push_back("weight.txt");

	initMatrix();
	
	//window border
	vector<Point> windowBorder; // define 4 corner points of a window
	windowBorder.push_back((Point){0,0});
	windowBorder.push_back((Point){framebuffer.width, 0});
	windowBorder.push_back((Point){framebuffer.width, framebuffer.height});
	windowBorder.push_back((Point){0, framebuffer.height});
	
	map<string, vector<Point> > points = getPointsFromFile(filenames);
	//Mapping the population of each region with the same order
	map<string, int> populations = getIntegersFromFile(populationFile);

	//vector<Shape> areas;
	map<string, Shape> areas;

	Point Pmin = {0, 0};
	Point Pmax = {framebuffer.width, framebuffer.height};
	Point Pcenter = {framebuffer.width/2, framebuffer.height/2};
	//Shape res = Pclip(shape3, Pmin, Pmax);

	for(map<string, vector<Point>>::iterator it=points.begin(); it!=points.end(); it++){
		vector<Point> Pol = it->second;
		string str = it->first;
	
		Shape s(Pol);
		s.setCentroid(Pcenter);
		Shape sclip = Pclip(s, Pmin, Pmax);
		//s.draw(&framebuffer, WHITE);
		sclip.draw(&framebuffer, WHITE);
		//sclip.fill(WHITE, &framebuffer, windowBorder);
		//areas.push_back(s); // add new area
		areas[str] = s;
		//areas[str] = sclip;
	}
	printf("area size %d\n", areas.size());	

	// fill areas
	// for(int i=0; i<areas.size(); i++){
	// 	//areas[i].fill(WHITE, &framebuffer, windowBorder);
	// }
	framebuffer.SwapBuffers();

	map<string, Shape>::iterator it2=areas.begin();
	it2->second.fill(RED, &framebuffer, windowBorder);
	framebuffer.SwapBuffers();

	int dx = 10;
	int dy = 10;
	float sf = 0.1; // scaling factor
	float deg = 15.0; // degree of rotation
	bool debugMode = false;

	while(1){
		// cout << "area highlighted before : " << it2->first << endl;
		char c = getch();

		if(c == 'h'){ //fill next area
			if (next(it2) != areas.end()) {
				it2->second.unfill(&framebuffer, windowBorder);
				it2->second.draw(&framebuffer, WHITE);
				it2++;
				it2->second.fill(getAreaColour(22000000), &framebuffer, windowBorder);
				framebuffer.SwapBuffers();
			}
		} 
		else if(c == 'g'){ //fill previous area
			if (prev(it2) != prev(areas.begin())) {
				it2->second.unfill(&framebuffer, windowBorder);
				it2->second.draw(&framebuffer, WHITE);
				it2--;
				it2->second.fill(getAreaColour(15000000), &framebuffer, windowBorder);	
				framebuffer.SwapBuffers();
			}
		}
		else if (c == 'w') { // move up
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//it->second.unfill(&framebuffer, windowBorder);
				//initMatrix();
				it->second.transform(0, -dy, 1, 0);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if (c == 's') { // move down
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//it->second.unfill(&framebuffer, windowBorder);
				//initMatrix();
				it->second.transform(0, dy, 1, 0);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if (c == 'a') { // move left
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//it->second.unfill(&framebuffer, windowBorder);
				//initMatrix();
				it->second.transform(-dx, 0, 1, 0);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if (c == 'd') { // move right
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//it->second.unfill(&framebuffer, windowBorder);
				//initMatrix();
				it->second.transform(dx, 0, 1, 0);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if (c == 'i') { // zooom in
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//initMatrix();
				it->second.transform(0, 0, 1+sf, 0);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if (c == 'o') { // zoom out
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//initMatrix();
				it->second.transform(0, 0, 1-sf, 0);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if (c == 'l') { // rotate right
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//initMatrix();
				it->second.transform(0, 0, 1, deg);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if (c == 'k') { // rotate left
			framebuffer.ClearScreen();
			for(map<string, Shape>::iterator it=areas.begin(); it!=areas.end(); it++){
				//it->second.undraw(&framebuffer);
				//initMatrix();
				it->second.transform(0, 0, 1, -deg);
				Shape sclip = Pclip(it->second, Pmin, Pmax);
				sclip.draw(&framebuffer, WHITE);
				//sclip.fill(WHITE, &framebuffer, windowBorder);
			}
			framebuffer.SwapBuffers();
		}
		else if(c == 'x'){
			break;
		}
		else if(c == '1'){
			debugMode = !debugMode;

			if (debugMode){
				//cout << "area highlighted now : " << it2->first << endl;
				Color32 res = getAreaColour(43200000);
				printf("rgba= %d %d %d %d\n",res.r,res.g,res.b,res.a);
			} else {
				it2->second.unfill(&framebuffer, windowBorder);
				it2->second.draw(&framebuffer, WHITE);
				// it2++;
				it2->second.fill(RED, &framebuffer, windowBorder);
				framebuffer.SwapBuffers();
			}
		}

		if (debugMode){
			cout << "area highlighted now : " << it2->first << endl;
		}
	}

	cout << "area highlighted : " << it2->first << endl;

	// vector<Point> pmy = areas["ForeignArea56"].getVertices();
	// ofstream myfile("output.txt");

	// if (myfile.is_open()) {
	// 	for (int i = 0; i < pmy.size(); i++) {
	// 		myfile << pmy[i].x << " " << pmy[i].y << endl;
	// 	}
	// 	myfile.close();
	// }


	return 0;
}
