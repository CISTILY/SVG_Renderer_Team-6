#pragma once
#include "Shape.h"

#include"Final.h"

class GroupSVG : public Shape {
private:
	FinalSVG g;
public:
	// Constructor
	GroupSVG();

	// Destructor
	~GroupSVG();

	
	// Build group Shape
	void buildShape(vector<char*>, vector<char*>) override {};

	// Getters
	FinalSVG getG() override;

	// Print data of group shape
	void print() override;
};