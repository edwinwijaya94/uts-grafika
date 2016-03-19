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
map<string, vector<Point> > getPointsFromFile(vector<string>);

#endif
