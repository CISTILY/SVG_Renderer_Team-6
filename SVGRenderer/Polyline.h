#pragma once
#include "Shape.h"

using namespace std;

class PolylineSVG : public Shape 
{
protected:
    vector<Point2D> points;

public:
    // Constructor
    PolylineSVG();

    // Destructor
    virtual ~PolylineSVG();

    // Build polyline shape
    void buildShape(vector<char*>, vector<char*>) override;

    // Getters
    vector<Point2D> getPoints();
    
    // Print data of polyline shape 
    void print() override;
};