#ifndef COLOR32_H
#define COLOR32_H

#include <stdint.h>

#define WHITE (Color32){255, 255, 255, 255}
#define BLACK (Color32){0, 0, 0, 255}
#define GREEN (Color32){0, 255, 0, 255}
#define RED (Color32){255, 0, 0, 255}


typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color32;

#endif
