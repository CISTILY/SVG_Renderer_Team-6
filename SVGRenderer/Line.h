#pragma once
#include "Shape.h"

using namespace std;

class LineSVG : public Shape {
private:
    Point2D end;
public:
    LineSVG();
    ~LineSVG();

    Point2D getEnd();
    void buildLine(vector<char*>, vector<char*>);
    void print() override;
};