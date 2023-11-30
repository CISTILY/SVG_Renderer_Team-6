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
    void buildShape(vector<char*>, vector<char*>) override;
};