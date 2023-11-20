#pragma once
#include "Shape.h"

class RectangleSVG : public Shape {
private:
	int width, height;
public:
	RectangleSVG();
	~RectangleSVG();

	void buildRect(vector<char*>, vector<char*>);

	void setWidth(int);
	void setHeight(int);
	int getWidth();
	int getHeight();

	void print() override;
};