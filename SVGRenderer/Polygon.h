#pragma once
#include "Polyline.h"

using namespace std;

class PolygonSVG : public PolylineSVG {
public:
    PolygonSVG();
    ~PolygonSVG();

    void buildPolygon(vector<char*>, vector<char*>, Properties);
};