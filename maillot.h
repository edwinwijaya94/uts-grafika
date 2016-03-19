#ifndef MAILLOT_H
#define MAILLOT_H

#include "shape.h"
#include "point.h"

int ExtCode(Point A, Point Pmin, Point Pmax);
Point Angle(int C, Point Pmin, Point Pmax);
int Tcc(int C);
Shape Pclip (Shape P, Point Pmin, Point Pmax);

#endif