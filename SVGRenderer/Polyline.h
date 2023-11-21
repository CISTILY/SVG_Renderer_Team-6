#pragma once
#include "Shape.h"

using namespace std;

class PolylineSVG : public Shape {
protected:
    vector<Point2D> points;
public:
    // Constructor
    PolylineSVG();

    // Destructor
    virtual ~PolylineSVG();

    // Build polyline shape
    void buildPolyline(vector<char*>, vector<char*>);

    // Getters
    vector<Point2D> getPoints();
    
    // Print data of polyline shape 
    void print() override;
};