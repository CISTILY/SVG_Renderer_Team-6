#include "Ellipse.h"

using namespace std;

EllipseSVG::EllipseSVG() 
{
    this->rx = 0;
    this->ry = 0;
}

EllipseSVG::~EllipseSVG() 
{

}

void EllipseSVG::buildShape(vector<char*> name, vector<char*> value) 
{
    string temp;
    for (int i = 0; i < name.size(); ++i) 
    {
        temp = name[i];
        if (temp == "cx")
            this->coordinate.setX(stof(value[i]));
        else if (temp == "cy")
            this->coordinate.setY(stof(value[i]));
        else if (temp == "rx" || temp == "r")
            this->setRadiusX(stoi(value[i]));
        else if (temp == "ry")
            this->setRadiusY(stoi(value[i]));
    }
}

void EllipseSVG::setRadiusX(float x) 
{
    this->rx = x;
}

void EllipseSVG::setRadiusY(float y) 
{
    this->ry = y;
}

float EllipseSVG::getRadiusX()
{
    return this->rx;
}

float EllipseSVG::getRadiusY()
{
    return this->ry;
}

void EllipseSVG::print() 
{
    this->coordinate.print();
    cout << " " << this->rx << " " << this->ry << " ";
    Shape::print();
}