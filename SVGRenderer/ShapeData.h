#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "Screen.h"
#include "Shape.h"
#include "Gradient.h"
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
    vector<Shape*> shapesSVG;   
    def gradients;
    ScreenSVG screen;
    static bool read;

    static ShapeData* instance;
    ShapeData();
public:
    // Constructor
    static ShapeData* getInstance();

    // Destructor
    ~ShapeData();

    // Assign data for shape variables
    void buildAndPrintShapeInfo(SVGReader, vector<Shape*>&, int&);

    // Getters
    vector<Shape*> getVectorShape();
    ScreenSVG getScreen();

    //void readFile(xml_node<>* node, vector<ShapeData>& data, string, int&);
    void readSVG(string);
    void readFile(xml_node<>* node, vector<Shape*>&, string, int&);
    void ReplaceProperties(Shape*);
};
