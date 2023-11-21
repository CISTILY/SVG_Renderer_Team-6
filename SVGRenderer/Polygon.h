#pragma once
#include "Polyline.h"

using namespace std;

class PolygonSVG : public PolylineSVG {
public:
    // Constructor
    PolygonSVG();

    // Destructor
    ~PolygonSVG();

    // Build polygon shape
    void buildPolygon(vector<char*>, vector<char*>);
};