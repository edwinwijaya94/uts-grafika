#include <vector>
#include "framebuffer.h"
#include "input.h"
#include "color32.h"
#include "point2.h"
#include <unistd.h>

using namespace std;

int main(){
	Framebuffer framebuffer;

	set_conio_terminal_mode();

	framebuffer.ClearScreen();

	double t;

	vector<Point2> face; 

	face.push_back(Point2(450,100));
	face.push_back(Point2(600,350));
	face.push_back(Point2(400,650));
	face.push_back(Point2(200,350));
	face.push_back(Point2(350,100));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(face, t, WHITE);
	}

	vector<Point2> hat; 

	hat.push_back(Point2(350,100));
	hat.push_back(Point2(450,100));
	hat.push_back(Point2(650,100));
	hat.push_back(Point2(450,100));
	hat.push_back(Point2(400,50));
	hat.push_back(Point2(350,100));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(hat, t, WHITE);
	}

	vector<Point2> lefteyes; 

	lefteyes.push_back(Point2(350,160));
	lefteyes.push_back(Point2(365,160));
	lefteyes.push_back(Point2(380,160));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(lefteyes, t, WHITE);
	}

	vector<Point2> leftBrow; 

	leftBrow.push_back(Point2(350,180));
	leftBrow.push_back(Point2(365,175));
	leftBrow.push_back(Point2(380,180));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(leftBrow, t, WHITE);
	}

	vector<Point2> righteyes; 

	righteyes.push_back(Point2(410,160));
	righteyes.push_back(Point2(425,160));
	righteyes.push_back(Point2(440,160));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(righteyes, t, WHITE);
	}

	vector<Point2> rightBrow; 

	rightBrow.push_back(Point2(410,180));
	rightBrow.push_back(Point2(425,175));
	rightBrow.push_back(Point2(440,180));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(rightBrow, t, WHITE);
	}

	vector<Point2> LeftBrowDown; 

	LeftBrowDown.push_back(Point2(350,180));
	LeftBrowDown.push_back(Point2(365,185));
	LeftBrowDown.push_back(Point2(380,180));
	framebuffer.SetPixel(363,179, WHITE);
	framebuffer.SetPixel(364,179, WHITE);
	framebuffer.SetPixel(365,179, WHITE);
	framebuffer.SetPixel(366,179, WHITE);
	framebuffer.SetPixel(367,179, WHITE);

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(LeftBrowDown, t, WHITE);
	}

	vector<Point2> rightBrowDown; 

	rightBrowDown.push_back(Point2(410,180));
	rightBrowDown.push_back(Point2(425,185));
	rightBrowDown.push_back(Point2(440,180));
	framebuffer.SetPixel(423,179, WHITE);
	framebuffer.SetPixel(424,179, WHITE);
	framebuffer.SetPixel(425,179, WHITE);
	framebuffer.SetPixel(426,179, WHITE);
	framebuffer.SetPixel(427,179, WHITE);

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(rightBrowDown, t, WHITE);
	}

	vector<Point2> nose; 

	nose.push_back(Point2(400,300 - 50));
	nose.push_back(Point2(390,300 - 50));
	nose.push_back(Point2(350,320 - 50));
	nose.push_back(Point2(450,320 - 50));
	nose.push_back(Point2(410,300 - 50));
	nose.push_back(Point2(400,300 - 50));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(nose, t, WHITE);
	}

	vector<Point2> upperlip; 

	upperlip.push_back(Point2(400,300));
	upperlip.push_back(Point2(390,300));
	upperlip.push_back(Point2(320,320));
	upperlip.push_back(Point2(370,340));
	upperlip.push_back(Point2(400,270));
	upperlip.push_back(Point2(420,340));
	upperlip.push_back(Point2(480,320));
	upperlip.push_back(Point2(410,300));
	upperlip.push_back(Point2(400,300));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(upperlip, t, WHITE);
	}

	vector<Point2> lowerlip; 

	lowerlip.push_back(Point2(400,400 - 67));
	lowerlip.push_back(Point2(390,400 - 67));
	lowerlip.push_back(Point2(320,380 - 67));
	lowerlip.push_back(Point2(370,360 - 67));
	lowerlip.push_back(Point2(400,430 - 67));
	lowerlip.push_back(Point2(420,360 - 67));
	lowerlip.push_back(Point2(480,380 - 67));
	lowerlip.push_back(Point2(410,400 - 67));
	lowerlip.push_back(Point2(400,400 - 67));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(lowerlip, t, WHITE);
	}

	vector<Point2> righttears; 

	righttears.push_back(Point2(440,190));
	righttears.push_back(Point2(440,205));
	righttears.push_back(Point2(440,220));

	for (double i = 0.0; i < 1.0; i+=0.0005) {
		t = i;
		framebuffer.drawCurve(righttears, t, WHITE);
	}

	framebuffer.SwapBuffers();
	Point2 default_rightBrow = rightBrow[1];
	Point2 default_rightBrowDown = rightBrowDown[1];
	int sign_rightBrow = 1;
	int sign_rightBrowDown = -1;

	vector<Point2> default_righttears = righttears;

	while (1) {
		vector<Point2> _rightBrow; 

		_rightBrow.push_back(Point2(410,180));
		_rightBrow.push_back(Point2(425,rightBrow[1].y));
		_rightBrow.push_back(Point2(440,180));

		for (double i = 0.0; i < 1.0; i+=0.0005) {
			t = i;
			framebuffer.drawCurve(_rightBrow, t, BLACK);
		}

		if (rightBrow[1].y - default_rightBrow.y > 5 || default_rightBrow.y - rightBrow[1].y > 8){
			sign_rightBrow *= -1;
		}

		rightBrow[1].y += sign_rightBrow;

		vector<Point2> _rightBrow2; 

		_rightBrow2.push_back(Point2(410,180));
		_rightBrow2.push_back(Point2(425,rightBrow[1].y));
		_rightBrow2.push_back(Point2(440,180));

		for (double i = 0.0; i < 1.0; i+=0.0005) {
			t = i;
			framebuffer.drawCurve(_rightBrow2, t, WHITE);
		}

		vector<Point2> _rightBrowDown; 

		_rightBrowDown.push_back(Point2(410,180));
		_rightBrowDown.push_back(Point2(425,rightBrowDown[1].y));
		_rightBrowDown.push_back(Point2(440,180));

		for (double i = 0.0; i < 1.0; i+=0.0005) {
			t = i;
			framebuffer.drawCurve(_rightBrowDown, t, BLACK);
		}

		if (rightBrowDown[1].y - default_rightBrowDown.y > 5 || default_rightBrowDown.y - rightBrowDown[1].y > 8){
			sign_rightBrowDown *= -1;
		}

		rightBrowDown[1].y += sign_rightBrowDown;
		framebuffer.SetPixel(423,179, WHITE);
		framebuffer.SetPixel(424,179, WHITE);
		framebuffer.SetPixel(425,179, WHITE);
		framebuffer.SetPixel(426,179, WHITE);
		framebuffer.SetPixel(427,179, WHITE);


		vector<Point2> _rightBrow2Down; 

		_rightBrow2Down.push_back(Point2(410,180));
		_rightBrow2Down.push_back(Point2(425,rightBrowDown[1].y));
		_rightBrow2Down.push_back(Point2(440,180));

		for (double i = 0.0; i < 1.0; i+=0.0005) {
			t = i;
			framebuffer.drawCurve(_rightBrow2Down, t, WHITE);
		}

		vector<Point2> _righttears; 

		_righttears.push_back(righttears[0]);
		_righttears.push_back(righttears[1]);
		_righttears.push_back(righttears[2]);

		for (double i = 0.0; i < 1.0; i+=0.0005) {
			t = i;
			framebuffer.drawCurve(_righttears, t, BLACK);
		}

		if (righttears[2].y > 400){
			righttears = default_righttears;
		}

		vector<Point2> _righttears2; 

		_righttears2.push_back(righttears[1]);
		_righttears2.push_back(righttears[2]);
		_righttears2.push_back(Point2(righttears[2].x,righttears[2].y + 7));

		righttears.clear();
		righttears.push_back(_righttears2[0]);
		righttears.push_back(_righttears2[1]);
		righttears.push_back(_righttears2[2]);

		for (double i = 0.0; i < 1.0; i+=0.0005) {
			t = i;
			framebuffer.drawCurve(_righttears2, t, WHITE);
		}

		framebuffer.SwapBuffers();

		if(kbhit()){
			char c = getch();

			if (c == 'x'){
				break;
			}
		}

		usleep(20000);
	}
	
	return 0;
}
