#pragma once
#include <iostream>
#include <string>

using namespace std;

class Point2D {
private:
	int x;
	int y;
public:
	// Constructor
	Point2D();
	Point2D(string);

	// Destructor
	~Point2D();

	// Setters
	void setX(int);
	void setY(int);

	// Getters
	int getX();
	int getY();

	// Print data of Point2D
	void print();
};