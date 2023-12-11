#pragma once

#include "Shape.h"

using namespace std;

class EllipseSVG : public Shape {
protected:
    float rx;
    float ry;
public:
    // Constructor
    EllipseSVG();

    // Destructor
    virtual ~EllipseSVG();

    // Build ellipse shape
    void buildShape(vector<char*>, vector<char*>) override;

    // Setters
    void setRadiusX(float);
    void setRadiusY(float);

    // Getters
    float getRadiusX();
    float getRadiusY();

    // Print data of ellipse
    virtual void print();
};