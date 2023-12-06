#pragma once
#include "ShapeData.h"

class FinalSVG
{
private:
	vector<ShapeData> final;
public:
	// Constructor
	FinalSVG();

	// Destructor
	~FinalSVG();

	// Getters
	vector<ShapeData> getFinal();


	void readFile(xml_node<>*, string);
	void ReplaceProperties();

};