#include "maillot.h"

int ExtCode(Point A, Point Pmin, Point Pmax) {
	int C = 0;

	if (A.x < Pmin.x) {
		C += 1;
		if (A.y < Pmin.y) C += 20;
		if (A.y > Pmax.y) C += 24;
		return C;
	} 
	if (A.x > Pmax.x) {
		C += 2;
		if (A.y < Pmin.y) C += 20;
		if (A.y > Pmax.y) C += 24;
		return C;
	}

	if (A.y < Pmin.y) C += 4;
	if (A.y > Pmax.y) C += 8;

	return C;
}

Point Angle(int C, Point Pmin, Point Pmax) {
	Point A = { 0, 0 };

	if (C & 1) A.x = Pmin.x;
	if (C & 2) A.x = Pmax.x;
	if (C & 4) A.y = Pmin.y;
	if (C & 8) A.y = Pmax.y;

	return A;
}

int Tcc(int C) {
	int corr = 0;

	if (C & 1) corr = -1;
	else if (C & 2) corr = 1;
	else if (C & 4) corr = -4;
	else if (C & 8) corr = 4;

	return corr;
}

// Maillot's Algorithm
Shape Pclip (Shape Polygon, Point Pmin, Point Pmax) {
	// 1
	int k = 0;
	Shape clippedPolygon;
	vector<Point> clippedP;
 
	vector<Point> P = Polygon.getVertices();

	// 2
	Point start = P[P.size()- 1];
 
	// 3
	step3:
	if (k > (P.size() - 1)) {
		clippedPolygon.setVertices(clippedP);
		return clippedPolygon;
	}
 
	// 4
	Point end = P[k];
	int Cend = ExtCode(end, Pmin, Pmax);
	int Cstart = ExtCode(start, Pmin, Pmax);
 
	// 5
	int C1 = Cstart;
	int C2 = Cend;
 
	Point p1 = start;
	Point p2 = end;
 
	// 6
	bool clip = false;
	bool flip = false;
	bool segm = false;
 
	// 7
	step7:
	if ( ((C1 | C2) & 15) == 0 ) {
		// 8
		if (flip) std::swap(p1, p2);
		// 9
		segm = true;
	} else {
		// 10
		if (C1 & C2 & 15) {
			segm = false;
		} else {
			// 11
			if ((C1 & 15) == 0) {
				std::swap(p1, p2);
				std::swap(C1, C2);
				flip = !flip;
			}
 
			// 12
			if ((C1 & 15) && !flip) clip = true;
 
			if (C1 & 1) {
				p1.y = p2.y - (p2.x - Pmin.x) * (p2.y - p1.y) / (p2.x - p1.x);
				p1.x = Pmin.x;
			}
 
			if (C1 & 2) {
				p1.y = p2.y - (p2.x - Pmax.x) * (p2.y - p1.y) / (p2.x - p1.x);
				p1.x = Pmax.x;
			}
 
			if (C1 & 4) {
				p1.x = p2.x - (p2.y - Pmin.y) * (p2.x - p1.x) / (p2.y - p1.y);
				p1.y = Pmin.y;
			}
 
			if (C1 & 8) {
				p1.x = p2.x - (p2.y - Pmax.y) * (p2.x - p1.x) / (p2.y - p1.y);
				p1.y = Pmax.y;
			}
 
			C1 = ExtCode(p1, Pmin, Pmax);
			// 13
			goto step7;
		}
	}
 
	// 14-15
	C2 = Cend;
 
	// 16
	if (segm) {
		if (clip) clippedP.push_back(p1);
		clippedP.push_back(p2);
	} 
	// 17
	else {
		// a
		if (Cend & 16) {
			if ( (Cstart & Cend & 15) == 0 ) {
				// i
				if ( (Cstart & 16) == 0 ) C1 = Cend + Tcc(Cstart);
				else {
					// A
					p1 = start;
					p2 = end;
					int C11 = Cstart;
					int C12 = Cend;
					// B
					step17aiB:
					Point mid = { (p1.x + p2.x) / 2 , (p1.y + p2.y) / 2 };
					// C
					C1 = ExtCode(mid, Pmin, Pmax);
					// D
					if (C1 & 16) {
						if (C1 == C12) {
							p2 = mid;
							C12 = C1;
							goto step17aiB;
						}
						if (C1 == C11) {
							p1 = mid;
							C11 = C1;
							goto step17aiB;
						}
					} else {
						if (C1 & C12) C1 = C11 + Tcc(C1);
						else C1 = C12 + Tcc(C1);
					}
				}
				// ii
				clippedP.push_back(Angle(C1, Pmin, Pmax));
			}
		} 
		// b
		else {
			if ( (Cstart & Cend & 15) == 0 ) {
				if (Cstart & 16) C2 = Cstart + Tcc(Cend);
				else C2 = Cstart + Cend + 16;
			}
		}
	}
 
	// 18
	if (C2 & 16) clippedP.push_back(Angle(C2, Pmin, Pmax));
 
	// 19
	k++;
	Cstart = Cend;
	start = end;
	goto step3;
}