#pragma once
#include "Point2D.h"
#include "Color.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class Stop 
{
private:
	float offset;
	ColorSVG stop_color;
	float stop_opacity;

public:
	// Constructor
	Stop();

	// Destructor
	~Stop();

	// Build Stop
	void buildStop(vector<char*>, vector<char*>);

	// Setters
	void setOffset(float);
	void setStopOpacity(float);

	// Getters
	float getOffset();
	ColorSVG getStopColor();
	float getStopOpacity();

	// Print stop information
	void printStop();
};

class Gradient 
{
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
	// Constructor
	Gradient();

	// Destructor
	~Gradient();

	// Pure virtual functions
	virtual void buildGradient(vector<char*>, vector<char*>) = 0;	// Assign right attributes value for data members
	virtual void print() = 0;										// Print out data

	// Setters
	void setPoint1(double, double);
	void setPoint2(double, double);
	void setID(char*);
	void setGradientUnits(string);
	void setSpreadMethod(string);
	void setGradientTransform(string);
	void setHref(string);

	// Add a stop for this Gradient
	void addStop(Stop);

	// Use stops of different Gradient for this Gradient
	void replaceStop(vector<Stop>);

	// Getters
	string getHref();
	string getID();
	string getGradientUnits();
	string getSpreadMethod();
	Point2D getPoint1();
	Point2D getPoint2();
	float getRotate();
	Point2D getTranslate();
	Point2D getScale();
	float* getMatrix();
	vector<Stop> getStops();
};

class LinearGradientSVG : public Gradient 
{
public:
	// Constructor
	LinearGradientSVG();

	// Destructor
	~LinearGradientSVG();

	// Overrided functions
	void buildGradient(vector<char*>, vector<char*>) override;
	void print() override;
};

class RadialGradientSVG : public Gradient 
{
private:
	float r;

public:
	// Constructor
	RadialGradientSVG();

	// Destructor
	~RadialGradientSVG();

	// Overrided functions
	void buildGradient(vector<char*>, vector<char*>) override;
	void print() override;

	// Getter
	float getRadius();
};

class Def 
{
private:
	int previous;	// Flag for previous Gradient (1 for Linear, 2 for Radial)
	vector<LinearGradientSVG> LinearGradients;
	vector<RadialGradientSVG> RadialGradients;

public:
	// Constructor
	Def();

	// Destructor
	~Def();

	// Parsing Gradient from xml node
	void readGradient(xml_node<>* node);

	// Build data for data members
	void buildDef(string, vector<char*>, vector<char*>);

	// Print data
	void printGradient();

	// Perform Href attributes
	void performHref();

	// Getters
	vector<LinearGradientSVG> getLinearGradients();
	vector<RadialGradientSVG> getRadialGradient();
	vector<LinearGradientSVG>* getLinearGradientAddress();
};
