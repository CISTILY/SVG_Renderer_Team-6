#pragma once

#include "Shape.h"

using namespace std;

class EllipseSVG : public Shape {
protected:
    int rx;
    int ry;
public:
    // Constructor
    EllipseSVG();

    // Destructor
    virtual ~EllipseSVG();

    // Build ellipse shape
    void buildEllipse(vector<char*>, vector<char*>);

    // Setters
    void setRadiusX(int);
    void setRadiusY(int);

    // Getters
    float getRadiusX();
    float getRadiusY();

    // Print data of ellipse
    virtual void print();
};