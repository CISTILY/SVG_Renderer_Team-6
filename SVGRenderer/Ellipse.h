#pragma once

#include "Shape.h"

using namespace std;

class EllipseSVG : public Shape {
protected:
    int rx;
    int ry;
public:
    EllipseSVG();
    virtual ~EllipseSVG();

    void buildEllipse(vector<char*>, vector<char*>);

    void setRadiusX(int);
    void setRadiusY(int);
    int getRadiusX();
    int getRadiusY();

    virtual void print();
};