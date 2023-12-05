#pragma once
#include "Shape.h"

class ShapeData;

class GroupSVG : public Shape {
private:
	vector<ShapeData>* g;
public:
	// Constructor
	GroupSVG();

	// Destructor
	~GroupSVG();

	
	// Build group Shape
	void buildShape(vector<char*>, vector<char*>) override {};

	// Getters
	vector<ShapeData>* getG() override;

	// Print data of group shape
	void print() override;
};