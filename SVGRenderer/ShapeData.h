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
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class ShapeData {
private:
    char* typeName;
    bool flagStroke;

    // shape variables
    RectangleSVG rect;
    CircleSVG cir;
    EllipseSVG ellip;
    PolygonSVG polygon;
    LineSVG line;
    PolylineSVG polyline;
    TextSVG text;
public:
    // Constructor
    ShapeData();

    // Destructor
    ~ShapeData();

    // Assign data for shape variables
    void buildAndPrintShapeInfo(SVGReader, int&);

    // Getters
    string getTypeName();
    bool getFlagStroke();
    RectangleSVG getRect();
    CircleSVG getCir();
    EllipseSVG getEllip();
    PolygonSVG getPolygon();
    LineSVG getLine();
    PolylineSVG getPolyline();
    TextSVG getText();

    void readFile(xml_node<>* node, vector<ShapeData>& data, SVGReader, string);
};