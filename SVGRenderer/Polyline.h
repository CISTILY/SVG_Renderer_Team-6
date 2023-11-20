#pragma once
#include "Shape.h"

using namespace std;

class PolylineSVG : public Shape {
protected:
    vector<Point2D> points;
public:
    PolylineSVG();
    virtual ~PolylineSVG();

    vector<Point2D> getPoints();
    void buildPolyline(vector<char*>, vector<char*>);
    void print() override;
};