#pragma once
#include "Shape.h"

using namespace std;

class LineSVG : public Shape {
private:
    Point2D end;
public:
    // Constructor
    LineSVG();

    // Destructor
    ~LineSVG();

    // Build line
    void buildLine(vector<char*>, vector<char*>);

    // Getters
    Point2D getEnd();
    
    // Print data of line
    void print() override;
};