#pragma once

#include "Ellipse.h"

using namespace std;

class CircleSVG : public EllipseSVG 
{
public:
    // Constructor
    CircleSVG();

    // Destructor
    ~CircleSVG();

    // Build circle
    void buildShape(vector<char*>, vector<char*>) override;

    // Print data of circle
    void print() override;
};