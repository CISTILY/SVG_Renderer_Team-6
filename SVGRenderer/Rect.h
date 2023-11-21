#pragma once
#include "Shape.h"

class RectangleSVG : public Shape {
private:
	int width, height;
public:
	// Constructor
	RectangleSVG();

	// Destructor
	~RectangleSVG();

	// Build rectangle Shape
	void buildRect(vector<char*>, vector<char*>);

	// Setters
	void setWidth(int);
	void setHeight(int);

	// Getters
	int getWidth();
	int getHeight();

	// Print data of rectangle shape
	void print() override;
};