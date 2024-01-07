#pragma once
#include "Shape.h"
#include "ShapeData.h"

class ShapeData;

class GroupSVG : public Shape 
{
private:
	vector<Shape*> shapes;

public:
	// Constructor
	GroupSVG();

	// Destructor
	~GroupSVG();

	// Build group Shape
	void buildShape(vector<char*>, vector<char*>) override {};

	// Getters
	vector<Shape*> getVectorShape();
	vector<Shape*>* getVectorShapeAddress();
};
