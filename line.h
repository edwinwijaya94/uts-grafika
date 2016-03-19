#ifndef LINE_H
#define LINE_H

#include "point.h"

typedef struct {
  Point plow; // plow adalah point dengan y minimum
  Point phigh; // plow adalah point dengan y maximum
  int dx;
  int dy;
  int sx;
  int sy;
  int err;
  int e2;
  Point curpoint;
} Line;

#endif
