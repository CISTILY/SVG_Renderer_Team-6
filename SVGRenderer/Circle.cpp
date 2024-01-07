#include "Circle.h"

using namespace std;

CircleSVG::CircleSVG() 
{

}

CircleSVG::~CircleSVG() 
{

}

void CircleSVG::buildShape(vector<char*> name, vector<char*> value) 
{
    EllipseSVG::buildShape(name, value);
}

void CircleSVG::print() 
{
    this->coordinate.print();
    cout << " " << this->rx << " ";
    Shape::print();
}
