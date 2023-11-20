#pragma once

#include "Ellipse.h"

using namespace std;

class CircleSVG : public EllipseSVG {
public:
    CircleSVG();
    ~CircleSVG();

    void buildCircle(vector<char*>, vector<char*>);
    void print() override;
};