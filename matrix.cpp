#include "matrix.h"

bool freeMatrix [800][1300];

void initMatrix() {
	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 1300; j++) {
			freeMatrix[i][j] = true;
		}
	}
}
