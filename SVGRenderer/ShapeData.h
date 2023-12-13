#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "Shape.h"
#include "SVG.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon.h"
#include "Text.h"
#include "Line.h"
#include "Ellipse.h"
#include "Polyline.h"
#include "SVG.h"
#include "Path.h"
#include "Group.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class ShapeData {
private:
    char* typeName;

    // shape variables
    Shape* shapeSVG;
public:
    // Constructor
    ShapeData();

    // Destructor
    ~ShapeData();

    // Assign data for shape variables
    void buildAndPrintShapeInfo(SVGReader, int&);

    // Getters
    string getTypeName();
    Shape* getShape();

    // Setters
    void setStroke(ColorSVG stroke);
    void setStrokeWidth(float strokeWidth);
    void setStrokeOpacity(double strokeOpacity);
    void setFill(ColorSVG fill);
    void setFillOpacity(double fillOpacity);
    void setTransform(vector<string>, vector<Point2D>, vector<float>, vector<Point2D>, vector<int*>);

    void readFile(xml_node<>* node, vector<ShapeData>& data, string, int&);
    void ReplaceProperties();
};
