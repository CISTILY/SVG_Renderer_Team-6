#pragma once
#include <iostream>
#include <string>

using namespace std;

class Point2D 
{
private:
	float x;
	float y;
public:
	// Constructor
	Point2D();
	Point2D(float, float);
	Point2D(string);

	// Destructor
	~Point2D();

	// Setters
	void setX(float);
	void setY(float);

	// Getters
	float getX();
	float getY();

	// Print data
	void print();

	string ToString();
};