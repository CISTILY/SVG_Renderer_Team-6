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

	// Constructor
	stop();

	// Destructor
	~stop();

	// Build Stop
	void buildStop(vector<char*>, vector<char*>);

	// Setters
	void setOffset(float);
	void setColor(string);
	void setStopOpacity(float);

	// Getters
	float getOffset();
	ColorSVG getStopColor();
	float getStopOpacity();

	// Print stop information
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
	vector<float> matrix;
public:
	// Constructor
	Gradient();

	// Destructor
	~Gradient();

	// Pure virtual functions
	virtual void buildGradient(vector<char*>, vector<char*>) = 0;	// Assign right attributes value for data members
	virtual void print() = 0;										// Print out data

	// Setters
	void setID(char*);
	void setGradientUnits(string);
	void setSpreadMethod(string);
	void setGradientTransform(string);

	// Add a stop for this Gradient
	void addStop(stop);

	// Use stops of different Gradient for this Gradient
	void replaceStop(vector<stop>);

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
	vector<float> getMatrix();
	vector<stop> getStops();
};

class LinearGradientSVG : public Gradient {
public:
	// Constructor
	LinearGradientSVG();

	// Destructor
	~LinearGradientSVG();

	// Overrided functions
	void buildGradient(vector<char*>, vector<char*>) override;
	void print() override;
};

class RadialGradientSVG : public Gradient {
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
};

class def {
private:
	int previous;	// Flag for previous Gradient (1 for Linear, 2 for Radial)
	vector<LinearGradientSVG> LinearGradients;
	vector<RadialGradientSVG> RadialGradients;
public:
	// Constructor
	def();

	// Destructor
	~def();

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
};