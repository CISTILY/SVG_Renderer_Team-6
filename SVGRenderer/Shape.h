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
    vector<string> transform;

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
    void setTransform(string);

    // Getters
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
    Color getStroke();
    Color getFill();
    vector<string> getTransform();
    

    // Print out attributes
    virtual void print();
    virtual void buildShape(vector<char*>, vector<char*>) = 0;
    void splitWord(string, vector<Point2D>&, vector<float>&, vector<Point2D>&);
};
