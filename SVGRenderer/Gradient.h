#pragma once
#include "Point2D.h"
#include "Color.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class Stop {
private:
	float offset;
	ColorSVG stop_color;
	float stop_opacity;
public:
	Stop();
	~Stop();

	void buildStop(vector<char*>, vector<char*>);
	void setOffset(float);
	void setColor(string);
	float getOffset();
	ColorSVG getStopColor();
	void printStop();
};

class Gradient {
protected:
	string id;
	vector<Stop> stops;
	Point2D p1;
	Point2D p2;
	string gradientUnits;
	string spreadMethod;
	string href;
	Point2D translate;
	float rotate;
	Point2D scale;
	float matrix[6];
public:
	Gradient();
	~Gradient();

	virtual void buildGradient(vector<char*>, vector<char*>) = 0;
	virtual void print() = 0;

	void setID(char*);
	void setGradientUnits(string);
	void setSpreadMethod(string);
	void setGradientTransform(string);
	void setHref(string);

	void addStop(Stop);

	void replaceStop(vector<Stop>);

	string getHref();
	string getID();
	string getGradientUnits();
	string getSpreadMethod();
	Point2D getPoint1();
	Point2D getPoint2();
	vector<Stop> getStops();
};

class LinearGradientSVG : public Gradient {
public:
	LinearGradientSVG();
	~LinearGradientSVG();

	void buildGradient(vector<char*>, vector<char*>) override;
	void print() override;
};

class RadialGradientSVG : public Gradient {
	float r;
public:
	RadialGradientSVG();
	~RadialGradientSVG();

	void buildGradient(vector<char*>, vector<char*>) override;
	void print() override;
};

class Def {
private:
	int previous;
	vector<LinearGradientSVG> LinearGradients;
	vector<RadialGradientSVG> RadialGradients;
public:

	void readGradient(xml_node<>* node);
	void buildDef(string, vector<char*>, vector<char*>);
	void printGradient();
	void performHref();
};
