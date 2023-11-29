#pragma once

#include "Color.h"
#include "Point2D.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Shape {
protected:
    Point2D coordinate;
    Point2D translate;
    Point2D scalePoint;
    float rotate;
    bool flagStroke;
    float stroke_width;
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
    float getCoordinateX(); 
    float getCoordinateY();
    float getTranslateX();
    float getTranslateY();
    float getScaleX();
    float getScaleY();
    bool getFlagStroke();
    float getStrokeWidth();
    double getStrokeOpacity();
    double getFillOpacity();
    Color getStroke();
    Color getFill();
    float getRotate();
    

    // Print out attributes
    virtual void print();

    void splitWord(string, Point2D&, float&, Point2D&);
};
