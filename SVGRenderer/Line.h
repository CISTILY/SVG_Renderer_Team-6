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
    void buildShape(vector<char*>, vector<char*>) override;

    // Getters
    Point2D getEnd();
    
    // Print data of line
    void print() override;
};