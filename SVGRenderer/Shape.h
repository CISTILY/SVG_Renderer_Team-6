#pragma once

#include "Color.h"
#include "Point2D.h"
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

class Shape 
{
protected:
    string typeName;
    Point2D coordinate;

    vector<string> transform;
    vector<Point2D> translate;
    vector<float> rotateAngle;
    vector<Point2D> scalePoint;
    vector<int*> order_of_TranslateRotateScale;

    bool flagStroke;
    bool flagStrokeWidth;
    bool flagStrokeOpacity;
    bool flagFill;
    bool flagFillOpacity;
    bool flagTransform;

    float stroke_width;
    double fill_opacity;
    double stroke_opacity;
    ColorSVG fill;
    ColorSVG stroke;
    string style;

public:
    // Constructor
    Shape();

    // Destructor
    virtual ~Shape();

    // Setters
    void buildProperties(vector<char*>, vector<char*>);
    void setStroke(ColorSVG);
    void setStrokeWidth(float);
    void setStrokeOpacity(double);
    void setFill(ColorSVG);
    void setFillOpacity(double);
    void setTransform(vector<string>, vector<Point2D>, vector<float>, vector<Point2D>, vector<int*>);

    // Caculate
    void findOrderTransform(string);
    void convertTransform(string);

    // Getters
    string getTypeName();
    float getCoordinateX(); 
    float getCoordinateY();

    bool getFlagStroke();
    bool getFlagStrokeWidth();
    bool getFlagStrokeOpacity();
    bool getFlagFill();
    bool getFlagFillOpacity();
    bool getFlagTransform();

    float getStrokeWidth();
    double getStrokeOpacity();
    double getFillOpacity();
    ColorSVG getStroke();
    ColorSVG getFill();

    vector<string> getTransform();
    vector<Point2D>getTranslate();
    vector<float>getRotateAngle();
    vector<Point2D>getScalePoint();
    vector<int*> getOrderOfTransform();

    // Print out attributes
    virtual void print();

    // pure virtual function to parse Shape from xml node
    virtual void buildShape(vector<char*>, vector<char*>) = 0;
};
