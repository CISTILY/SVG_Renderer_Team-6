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
    int stroke_width;
    double fill_opacity;
    double stroke_opacity;
    Color fill;
    Color stroke;
public:
    // Constructor
    Shape();

    // Destructor
    virtual ~Shape();

    // Setters
    void buildProperties(vector<char*>, vector<char*>);

    // Getters
    int getCoordinateX(); 
    int getCoordinateY();
    bool getFlagStroke();
    int getStrokeWidth();
    double getStrokeOpacity();
    double getFillOpacity();
    Color getStroke();
    Color getFill();

    // Print out attributes
    virtual void print();
};
