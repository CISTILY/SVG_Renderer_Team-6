#pragma once
#include "Shape.h"

using namespace std;

class PathSVG : public Shape {
private:
	vector<char> command;
	vector<Point2D> Points;
public:
	PathSVG();
	~PathSVG();

	void buildShape(vector<char*>, vector<char*>) override;

	void setCommand(vector<char>);
	void setPoints(vector<Point2D>);

	vector<char> getCommand();
	vector<Point2D> getPoints();

	void print() override;
};