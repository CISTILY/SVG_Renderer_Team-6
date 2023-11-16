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
    sf::Vector2f getCenter();
    void buildPolyline(vector<char*>, vector<char*>, Properties);
    void print();
};