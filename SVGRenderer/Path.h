#pragma once
#include "Shape.h"

using namespace std;

class Path : public Shape {
private:
	vector<char> command;
	vector<Point2D> Points;
public:
	Path();
	~Path();

	void buildShape(vector<char*>, vector<char*>) override;

	void setCommand(vector<char>);
	void setPoints(vector<Point2D>);

	vector<char> getCommand();
	vector<Point2D> getPoints();

	void print() override;
};