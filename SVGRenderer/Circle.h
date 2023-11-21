#pragma once

#include "Ellipse.h"

using namespace std;

class CircleSVG : public EllipseSVG {
public:
    // Constructor
    CircleSVG();

    // Destructor
    ~CircleSVG();

    // Build circle
    void buildCircle(vector<char*>, vector<char*>);

    // Print data of circle
    void print() override;
};