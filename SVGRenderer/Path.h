#pragma once
#include "Shape.h"

using namespace std;

class PathSVG : public Shape 
{
private:
	vector<char> command;
	vector<Point2D> Points;

public:
	// Constructor
	PathSVG();

	// Destructor
	~PathSVG();

	// Build Shape properties
	void buildShape(vector<char*>, vector<char*>) override;

	// Setters
	void setCommand(vector<char>);
	void setPoints(vector<Point2D>);

	// Getters
	vector<char> getCommand();
	vector<Point2D> getPoints();

	// Replace point properties at specific position
	void replaceOnePoint(Point2D, int);

	// Print data
	void print() override;
};