#include "gradient.h"

Gradient::Gradient() { }

Gradient::Gradient(Color32 initialColor) {
	grad = initialColor;
}

Color32 Gradient::getColor() {
	return grad;
} 

void Gradient::resetColor(Color32 color) {
	grad = color;
}

void Gradient::gradate(int interval) {
	if ((grad.r > grad.g) && (grad.r > grad.b)) 
		grad.r -= interval;
	else if ((grad.g > grad.r) && (grad.g > grad.b)) 
		grad.g -= interval;
	else if ((grad.b > grad.r) && (grad.b > grad.g)) 
		grad.b -= interval;
}
