#pragma once

#include "Properties.h"
#include "Point2D.h"
#include <vector>
#include <iostream>

using namespace std;

class Shape {
protected:
    Point2D coordinate;
    Properties shapeProps;
public:
    Shape();
    virtual ~Shape();

    int getCoordinateX();
    int getCoordinateY();
    Properties getProperties();
};
