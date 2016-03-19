#include "framebuffer.h"

Framebuffer::Framebuffer(){
	fbfd = open("/dev/fb0", O_RDWR);
	if (fbfd == -1) {
		perror("Error: cannot open framebuffer device");
		exit(1);
	}
	printf("The framebuffer device was opened successfully.\n");
 
	// Get fixed screen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
		perror("Error reading fixed information");
		exit(2);
	}
 
	// Get variable screen information
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
		perror("Error reading variable information");
		exit(3);
	}
 
	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
	
	// Figure out the size of the screen in bytes
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	width = vinfo.xres;
	height = vinfo.yres;
	
	// Map the device to memory
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	bbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, (off_t)0);

	if ((int)fbp == -1) {
		perror("Error: failed to map framebuffer device to memory");
		exit(4);
	}
	printf("The framebuffer device was mapped to memory successfully.\n");
}

Framebuffer::~Framebuffer(){
	munmap(fbp, screensize);
	munmap(bbp, screensize);
	close(fbfd);
}

void Framebuffer::SwapBuffers()
{
	memcpy(fbp, bbp, screensize);
}

void Framebuffer::ClearScreen(){
	int i;
	for(i = 0; i < screensize; i++){
		*(bbp+i) = 0;
	}
}

void Framebuffer::SetPixel(int x, int y, Color32 color){
	long int location = 0;
	if(color.a != 0 && x >= 0 && x < vinfo.xres && y >= 0 && y < vinfo.yres){
		location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
		*((uint32_t*)(bbp + location)) = (color.r<<vinfo.red.offset) | (color.g<<vinfo.green.offset) | (color.b<<vinfo.blue.offset);
	} else {
		//Out of bound
	}
}

void Framebuffer::DrawLine(Point p0, Point p1, Color32 color) {
	int x0 = (int)p0.x;
	int y0 = (int)p0.y;
	int x1 = (int)p1.x;
	int y1 = (int)p1.y;
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		SetPixel(x0,y0,color);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

// void Framebuffer::DrawPolygon(Polygon2& polygon, Color32 color){
//     for(int i=0; i<polygon.vertices.size(); i++){     
//         DrawLine(polygon.vertices[i], polygon.vertices[(i+1)%polygon.vertices.size()], color);
//     }
// }

int Framebuffer::IsIntersect(Line line, int y) {
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

void Framebuffer::SortTipot(vector<Point> &tipot) {
	int i, j;
	Point temp;
	for (i = 1; i < tipot.size(); i++) {
		for (j = 0; j < tipot.size() -1; j++) {
			if (tipot[j].x > tipot[j+1].x) {
				temp = tipot[j];
				tipot[j] = tipot[j+1];
				tipot[j+1] = temp;
			}
		}
	}
}


void Framebuffer::drawCurve(vector<Point2> points, double t, Color32 color) {
	if (points.size() == 1) {
		SetPixel((int)points[0].x, (int)points[0].y, color);
	} 
	else {
		vector<Point2> newpoints(points.size()-1);
		for (int i = 0; i < newpoints.size(); i++) {
			newpoints[i].x = (1-t) * points[i].x + t * points[i+1].x;
			newpoints[i].y = (1-t) * points[i].y + t * points[i+1].y;
		}
		drawCurve(newpoints, t, color);
	}
}


/*void Framebuffer::fillPolygon(Polygon2& polygon, Color32 color) {
	vector<Line> vl = polygon.lines;
	int ymax = polygon.ymax;
	int ymin = polygon.ymin;
  int y, i, x, j;
  vector<Point> tipot;
  for (y = ymin; y <= ymax; y++) {
  	tipot.clear();
    for (j = 0; j < vl.size(); j++) {
      if (IsIntersect(vl[j], y) == 2) {
      	vl[j].dx = abs(vl[j].phigh.x-vl[j].plow.x);
      	vl[j].dy = abs(vl[j].phigh.y-vl[j].plow.y);
      	vl[j].sx = vl[j].plow.x < vl[j].phigh.x ? 1 : -1;
      	vl[j].sy = vl[j].plow.y < vl[j].phigh.y ? 1 : -1;
      	vl[j].err = (vl[j].dx > vl[j].dy ? vl[j].dx : -1 * vl[j].dy)/2;
      	vl[j].curpoint = vl[j].plow;

      	tipot.push_back(vl[j].plow);
      }
      else if (IsIntersect(vl[j], y) == 1) {
      	vl[j].e2 = vl[j].err;
      	if (vl[j].e2 > -1*vl[j].dx) { vl[j].err -= vl[j].dy; vl[j].curpoint.x += vl[j].sx; }
      	if (vl[j].e2 < vl[j].dy) { vl[j].err += vl[j].dx; vl[j].curpoint.y += vl[j].sy; }

      	tipot.push_back(vl[j].curpoint);
      }
    }
    SortTipot(tipot);
    for (i = 0; i < tipot.size()-1; i += 2) {
    	for (x = tipot[i].x; x <= tipot[i+1].x; x++) {
    		this->SetPixel(x, y, color);
    	}
    }
  }
}
*/
// void Framebuffer::FillPolygon(Polygon2& polygon, Color32 color, bool freeMatrix[][1300]) {
//   vector<Point> tipot;
//   int oldy;
//   vector<Line> lines = polygon.lines;
//   int ymin = polygon.ymin;
//   int ymax = polygon.ymax;
//   //printf("fill\n");
//   for (int y = ymax; y > ymin; y--) {
//   	tipot.clear();
//   	//printf("scanline ke-%d\n", y);
//     for (int j = 0; j < lines.size(); j++) {
//       if (IsIntersect(lines[j], y) == 2) {
//       	lines[j].dx = abs(lines[j].plow.x-lines[j].phigh.x);
//       	lines[j].dy = abs(lines[j].plow.y-lines[j].phigh.y);
//       	lines[j].sx = lines[j].phigh.x < lines[j].plow.x ? 1 : -1;
//       	lines[j].sy = lines[j].phigh.y < lines[j].plow.y ? 1 : -1;
//       	lines[j].err = (lines[j].dx > lines[j].dy ? lines[j].dx : (-1 * lines[j].dy))/2;
//       	lines[j].curpoint.x = lines[j].phigh.x;
//       	lines[j].curpoint.y = lines[j].phigh.y;

//       	tipot.push_back(lines[j].curpoint);
//       }
//       else if (IsIntersect(lines[j], y) == 1) {
//       	oldy = lines[j].curpoint.y;
//       	do {
//       		lines[j].e2 = lines[j].err;
// 	      	if (lines[j].e2 > -1*lines[j].dx) { lines[j].err -= lines[j].dy; lines[j].curpoint.x += lines[j].sx; }
// 	      	if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y += lines[j].sy; }		
//       		//printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
// 	      } while (lines[j].curpoint.y == oldy);
      	
//       	//if (lines[j].e2 < lines[j].dy) { lines[j].err += lines[j].dx; lines[j].curpoint.y = y; }

//       	tipot.push_back(lines[j].curpoint);
//       }
//       //if (j == 2)
//       	//printf("scanline ke-%d : garis ke 2 : (%d, %d)\n", y, lines[j].curpoint.x, lines[j].curpoint.y);
//     }
//     sort(tipot.begin(), tipot.end());
//     //for (int i = 0; i < tipot.size(); i ++) 
//     //	printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
    	
//     for (int i = 0; i < tipot.size()-1; i += 2) {
//     	//printf("tipot ke-%d : (%d, %d)\n", i, tipot[i].x, tipot[i].y);
//     	for (int x = tipot[i].x; x <= tipot[i+1].x; x++) {
//     		if (freeMatrix[y][x]) {
// 				this->SetPixel(x, y, color);	
// 				freeMatrix[y][x] = false;
//     		}
//     	}
//     }
//   }
// }


