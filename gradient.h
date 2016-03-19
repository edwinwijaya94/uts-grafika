#ifndef GRADIENT_H
#define GRADIENT_H

#include "color32.h"

class Gradient {
  private:
	Color32 grad;
  public:
  	Gradient();
  	Gradient(Color32 initialColor);
  	Color32 getColor();
  	void resetColor(Color32 color);
  	void gradate(int interval);
};

#endif
