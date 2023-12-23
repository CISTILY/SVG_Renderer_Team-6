#pragma once
#include "Point2D.h"
#include "Color.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class stop : public ColorSVG {
private:
	float offset;
	ColorSVG stop_color;
	float stop_opacity;
public:
	stop();
	~stop();

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
	vector<stop> stops;
	Point2D p1;
	Point2D p2;
	string gradientUnits;
	string spreadMethod;
	Point2D translate;
	string href;
	float rotate;
	Point2D scale;
public:
	Gradient();
	~Gradient();

	virtual void buildGradient(vector<char*>, vector<char*>) = 0;
	virtual void print() = 0;
	void setID(char*);
	void setGradientUnits(string);
	void setSpreadMethod(string);
	void setGradientTransform(string);

	void addStop(stop);

	void replaceStop(vector<stop>);

	string getHref();
	string getID();
	string getGradientUnits();
	string getSpreadMethod();
	Point2D getPoint1();
	Point2D getPoint2();
	vector<stop> getStops();
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

class def {
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