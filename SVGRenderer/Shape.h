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
    bool flagStrokeWidth;
    bool flagStrokeOpacity;
    bool flagFill;
    bool flagFillOpacity;
    bool flagTransform;

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
    void setStroke(Color);
    void setStrokeWidth(float);
    void setStrokeOpacity(double);
    void setFill(Color);
    void setFillOpacity(double);
    void setTransform(Point2D, float, Point2D);

    // Getters
    float getCoordinateX(); 
    float getCoordinateY();
    float getTranslateX();
    float getTranslateY();
    float getScaleX();
    float getScaleY();

    bool getFlagStroke();
    bool getFlagStrokeWidth();
    bool getFlagStrokeOpacity();
    bool getFlagFill();
    bool getFlagFillOpacity();
    bool getFlagTransform();

    float getStrokeWidth();
    double getStrokeOpacity();
    double getFillOpacity();
    Color getStroke();
    Color getFill();
    float getRotate();
    

    // Print out attributes
    virtual void print();
    virtual void buildShape(vector<char*>, vector<char*>) = 0;
    void splitWord(string, Point2D&, float&, Point2D&);
};
