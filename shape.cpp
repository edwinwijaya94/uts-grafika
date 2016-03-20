#include "shape.h"

Shape::Shape() { }

Shape::Shape(vector<Point> vertices) {
	setVertices(vertices);
}

vector<Point> Shape::getVertices() {
  return vertices;
}

void Shape::setVertices(vector<Point> vertices) {
	this->vertices = vertices;
	ymin = 2000;
	ymax = -1;
	int xmax = -1;
	int xmin = 2000;
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].y > vertices[(i+1)%vertices.size()].y) {
		  Line line;
		  line.phigh.y = vertices[i].y;
		  line.phigh.x = vertices[i].x;
		  line.plow.y = vertices[(i+1)%vertices.size()].y;
		  line.plow.x = vertices[(i+1)%vertices.size()].x;
		  lines.push_back(line);
		}
		else if (vertices[i].y < vertices[(i+1)%vertices.size()].y) {
		  Line line;
		  line.plow.y = vertices[i].y;
		  line.plow.x = vertices[i].x;
		  line.phigh.y = vertices[(i+1)%vertices.size()].y;
		  line.phigh.x = vertices[(i+1)%vertices.size()].x;
		  lines.push_back(line);
		}
		if (vertices[i].y > ymax) 
		  ymax = vertices[i].y;
		if (vertices[i].y < ymin)
		  ymin = vertices[i].y;
		if (vertices[i].x > xmax) 
		  xmax = vertices[i].x;
		if (vertices[i].x < xmin)
		  xmin = vertices[i].x;
		//printf("titik ke-%d : (%d, %d)\n", i, vertices[i].x, vertices[i].y);
	}
	//centroid = Point((xmax+xmin)/2, (ymax+ymin)/2);
	//for (int j = 0; j < lines.size(); j++)
	      //printf("garis ke-%d : (%d, %d) - (%d, %d)\n", j, lines[j].phigh.x, lines[j].phigh.y, lines[j].plow.x, lines[j].plow.y);	
	//printf("ymax : %d, ymin : %d\n", ymax, ymin);
}

void Shape::draw(Framebuffer* f, Color32 color) {
   for(int k=0; k<vertices.size(); k++){  
        Point p1(vertices[k].x, vertices[k].y);   
        Point p2(vertices[(k+1)%vertices.size()].x, vertices[(k+1)%vertices.size()].y);
        f->DrawLine(p1, p2, color);
   }
}

int Shape::isIntersect(Line line, int y) {
	if (y == line.phigh.y) {
		return 2;
	}
	//else if (((y > line.plow.y) && (y < line.phigh.y)) || (y == line.plow.y)) {
	else if ((y > line.plow.y) && (y < line.phigh.y)) {
		return 1;
	}
	else 
		return 0;
}

void Shape::fill(Color32 color, Framebuffer* f, vector<Point> windowBorder) {
  vector<Point> tipot;
  int oldy;
  //printf("fill\n");
  for (int y = ymax; y > ymin; y--) {
  	tipot.clear();
  	//printf("scanline ke-%d\n", y);
    for (int j = 0; j < lines.size(); j++) {
      if (isIntersect(lines[j], y) == 2) {
      	lines[j].dx = abs(lines[j].plow.x-lines[j].phigh.x);
      	lines[j].dy = abs(lines[j].plow.y-lines[j].phigh.y);
      	lines[j].sx = lines[j].phigh.x < lines[j].plow.x ? 1 : -1;
      	lines[j].sy = lines[j].phigh.y < lines[j].plow.y ? 1 : -1;
      	lines[j].err = (lines[j].dx > lines[j].dy ? lines[j].dx : (-1 * lines[j].dy))/2;
      	lines[j].curpoint.x = lines[j].phigh.x;
      	lines[j].curpoint.y = lines[j].phigh.y;

      	tipot.push_back(lines[j].curpoint);
      }
      else if (isIntersect(lines[j], y) == 1) {
      	oldy = lines[j].curpoint.y;
      	do {
      		lines[j].e2 = lines[j].err;
	      	if (lines[j].e2 > -1*lines[j].dx) { lines[j].err -= lines[j].dy; lines[j].curpoint.x += lines[j].sx; }
	      	if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y += lines[j].sy; }		
      		//printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
	      } while (lines[j].curpoint.y == oldy);
      	
      	//if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y = y; }

      	tipot.push_back(lines[j].curpoint);
      }
      //if (j == 2)
      	//printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
    }
    
    //SELECT TIPOT FOR WINDOW AREA ONLY
    getTipotForWindow(&tipot, windowBorder);
    
    sort(tipot.begin(), tipot.end());
    //for (int i = 0; i < tipot.size(); i ++) 
    	//printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
    
    for (int i = 0; i < tipot.size()-1; i += 2) {
    	//printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
    	for (int x = tipot[i].x; x <= tipot[i+1].x; x++) {
    		// if (freeMatrix[y][x]) {
				f->SetPixel(x, y, color);	
				freeMatrix[y][x] = false;
    		// }
    	}
    }
  }
}

void Shape::getTipotForWindow(vector<Point> *tipot, vector<Point> windowBorder){
	//IMPLEMENTS HERE, windowBorder defines 4 corner points of a window (defined in main.cpp)
	
}


void Shape::transform(int dx, int dy, float scale, float rotation) {
	float PI = 3.14159265;
    float rad = rotation * PI / 180.0f;
    //centroid.x += dx;
    //centroid.y += dy;
	for (int i = 0; i < vertices.size(); i++) {
		Point Pnew;
	   
	   //translate
	    Pnew.x = vertices[i].x + dx;
	    Pnew.y = vertices[i].y + dy;
	   
	    //scale
	    Pnew.x = centroid.x +(int)(double(Pnew.x - centroid.x) * scale);
	    Pnew.y = centroid.y +(int)(double(Pnew.y - centroid.y) * scale);

	    //rotate
	    int tx2 = Pnew.x - centroid.x, ty2 = Pnew.y - centroid.y;
	    Pnew.x = centroid.x + (int)((double)tx2 * cos(rad) - (double)ty2 * sin(rad));
	    Pnew.y = centroid.y + (int)((double)tx2 * sin(rad) + (double)ty2 * cos(rad));
	    vertices[i].x = Pnew.x;
	    vertices[i].y = Pnew.y;
	}
	lines.clear();
	setVertices(vertices);
	//fill();
}

void Shape::fillGradient(Color32 color, int interval, Framebuffer *f) {
 
  vector<Point> tipot;
  int oldy;
  Gradient grad(color);
  printf("fill\n");
  for (int y = ymax; y > ymin; y--) {
  	tipot.clear();
  	//printf("scanline ke-%d\n", y);
    for (int j = 0; j < lines.size(); j++) {
      grad.resetColor(color);	
      if (isIntersect(lines[j], y) == 2) {
      	lines[j].dx = abs(lines[j].plow.x-lines[j].phigh.x);
      	lines[j].dy = abs(lines[j].plow.y-lines[j].phigh.y);
      	lines[j].sx = lines[j].phigh.x < lines[j].plow.x ? 1 : -1;
      	lines[j].sy = lines[j].phigh.y < lines[j].plow.y ? 1 : -1;
      	lines[j].err = (lines[j].dx > lines[j].dy ? lines[j].dx : (-1 * lines[j].dy))/2;
      	lines[j].curpoint.x = lines[j].phigh.x;
      	lines[j].curpoint.y = lines[j].phigh.y;

      	tipot.push_back(lines[j].curpoint);
      }
      else if (isIntersect(lines[j], y) == 1) {
      	oldy = lines[j].curpoint.y;
      	do {
      		lines[j].e2 = lines[j].err;
	      	if (lines[j].e2 > -1*lines[j].dx) { lines[j].err -= lines[j].dy; lines[j].curpoint.x += lines[j].sx; }
	      	if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y += lines[j].sy; }		
      		//printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
	      } while (lines[j].curpoint.y == oldy);
      	
      	//if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y = y; }

      	tipot.push_back(lines[j].curpoint);
      }
      //if (j == 2)
      	//printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
    }
    sort(tipot.begin(), tipot.end());
    //for (int i = 0; i < tipot.size(); i ++) 
    	//printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
    for (int i = 0; i < tipot.size()-1; i += 2) {
    	//printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
    	for (int x = tipot[i].x; x <= tipot[i+1].x; x++) {
    		if (freeMatrix[y][x]) {
				f->SetPixel(x, y, grad.getColor());	
				grad.gradate(interval);
				freeMatrix[y][x] = false;
    		}
    	}
    }
  }	
}

void Shape::unfill(Color32 color, Framebuffer* f, vector<Point> windowBorder) {
  vector<Point> tipot;
  int oldy;
  //printf("fill\n");
  for (int y = ymax; y > ymin; y--) {
    tipot.clear();
    //printf("scanline ke-%d\n", y);
    for (int j = 0; j < lines.size(); j++) {
      if (isIntersect(lines[j], y) == 2) {
        lines[j].dx = abs(lines[j].plow.x-lines[j].phigh.x);
        lines[j].dy = abs(lines[j].plow.y-lines[j].phigh.y);
        lines[j].sx = lines[j].phigh.x < lines[j].plow.x ? 1 : -1;
        lines[j].sy = lines[j].phigh.y < lines[j].plow.y ? 1 : -1;
        lines[j].err = (lines[j].dx > lines[j].dy ? lines[j].dx : (-1 * lines[j].dy))/2;
        lines[j].curpoint.x = lines[j].phigh.x;
        lines[j].curpoint.y = lines[j].phigh.y;

        tipot.push_back(lines[j].curpoint);
      }
      else if (isIntersect(lines[j], y) == 1) {
        oldy = lines[j].curpoint.y;
        do {
          lines[j].e2 = lines[j].err;
          if (lines[j].e2 > -1*lines[j].dx) { lines[j].err -= lines[j].dy; lines[j].curpoint.x += lines[j].sx; }
          if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y += lines[j].sy; }   
          //printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
        } while (lines[j].curpoint.y == oldy);
        
        //if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y = y; }

        tipot.push_back(lines[j].curpoint);
      }
      //if (j == 2)
        //printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
    }
    
    //SELECT TIPOT FOR WINDOW AREA ONLY
    getTipotForWindow(&tipot, windowBorder);
    
    sort(tipot.begin(), tipot.end());
    //for (int i = 0; i < tipot.size(); i ++) 
      //printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
    
    for (int i = 0; i < tipot.size()-1; i += 2) {
      //printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
      for (int x = tipot[i].x; x <= tipot[i+1].x; x++) {
        // if (!freeMatrix[y][x]) {
        f->SetPixel(x, y, color); 
        freeMatrix[y][x] = true;
        // }
      }
    }
  }
}


void Shape::undraw(Framebuffer* f) {
 for(int k=0; k<vertices.size(); k++){  
        Point p1(vertices[k].x, vertices[k].y);   
        Point p2(vertices[(k+1)%vertices.size()].x, vertices[(k+1)%vertices.size()].y);
        f->DrawLine(p1, p2, BLACK);
 } 
}

void Shape::setCentroid(Point newPoint) {
  centroid.x = newPoint.x;
  centroid.y = newPoint.y;
}