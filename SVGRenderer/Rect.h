#pragma once
#include "Shape.h"

class RectangleSVG : public Shape {
private:
	float width, height;
public:
	// Constructor
	RectangleSVG();

	// Destructor
	~RectangleSVG();

	// Build rectangle Shape
	void buildRect(vector<char*>, vector<char*>);

	// Setters
	void setWidth(float);
	void setHeight(float);

	// Getters
	float getWidth();
	float getHeight();

	// Print data of rectangle shape
	void print() override;
};