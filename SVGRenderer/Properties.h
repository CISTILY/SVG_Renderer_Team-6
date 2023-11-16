#pragma once
#include "Color.h"
#include <iostream>
#include <vector>

using namespace std;

class Properties {
private:
	bool flagStroke;
	Color stroke;
	int stroke_width;
	double stroke_opacity;
	Color fill;
	double fill_opacity;
public:
	Properties();
	~Properties();

	void buildProperties(vector<char*>, vector<char*>);
	void print();

	bool getFlagStroke();
	int getStrokeWidth();
	double getStrokeOpacity();
	double getFillOpacity();
	Color getStroke();
	Color getFill();
};
