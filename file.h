#ifndef FILE_H
#define FILE_H

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "point.h"
#include "point2.h"
#include "color32.h"

using namespace std;

// File format
// [pesawat]
// 1 2 
// 3 4
// 5 6
// 7 8

// [parasut]
// 2 3
// 5 6
// 9 8
map<string, vector<Point>> getPointsFromFile(vector<string>);
map<string, int> getIntegersFromFile(vector<string>);
map<string, Color32 > getColorsFromFile(vector<string>);

#endif
