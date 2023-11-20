#pragma once

#include "Color.h"
#include "Point2D.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

using namespace std;

class Shape {
protected:
    Point2D coordinate;
    bool flagStroke;
    Color stroke;
    int stroke_width;
    double stroke_opacity;
    Color fill;
    double fill_opacity;
public:
    Shape();
    virtual ~Shape();

    int getCoordinateX(); 
    int getCoordinateY();

    void buildProperties(vector<char*>, vector<char*>);
    virtual void print();

    bool getFlagStroke();
    int getStrokeWidth();
    double getStrokeOpacity();
    double getFillOpacity();
    Color getStroke();
    Color getFill();
};
