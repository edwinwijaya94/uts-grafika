#include "point2.h"

Point2::Point2(){
	this->x = 0;
	this->y = 0;
}

Point2::Point2(float x, float y){
	this->x = x;
	this->y = y;
}

Point2 Point2::operator+(const Point2& other){
	Point2 result(this->x + other.x, this->y + other.y);
	return result;
}
Point2 Point2::operator-(const Point2& other){
	Point2 result(this->x - other.x, this->y - other.y);
	return result;
}
Point2 Point2::operator*(const Point2& other){
	Point2 result(this->x * other.x, this->y * other.y);
	return result;
}
Point2 Point2::operator/(const Point2& other){
	Point2 result(this->x / other.x, this->y / other.y);
	return result;
}
void Point2::operator=(const Point2& other){
	this->x = other.x;
	this->y = other.y;
}


void Point2::Transform(Point2 centroid, float scale, float rotation){
	float xnew;
	float ynew;
    float PI = 3.14159265;
    float rad = rotation * PI / 180.0f;
	
	this->x -= centroid.x;
	this->y -= centroid.y;
	//scale
	if(scale != 1){
		this->x *= scale;
		this->y *= scale;
	}
	//rotate
	if(rotation != 0){
		xnew = (this->x * cos(rad)) - (this->y * sin(rad));
		ynew = (this->x * sin(rad)) + (this->y * cos(rad));
		this->x = xnew;
		this->y = ynew;
	}
	
	this->x += centroid.x;
	this->y += centroid.y;
}

