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

using namespace std;

class Renderer {
private:
    char* typeName;
    bool flagStroke;

    RectangleSVG rect;
    CircleSVG cir;
    EllipseSVG ellip;
    PolygonSVG polygon;
    LineSVG line;
    PolylineSVG polyline;
    TextSVG text;

public:
    void buildAndPrintShapeInfo(SVGReader, Properties, int&);
};

