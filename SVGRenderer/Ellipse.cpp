#include "Ellipse.h"

using namespace std;

EllipseSVG::EllipseSVG() {
    this->rx = 0;
    this->ry = 0;

    cout << "Ellipse::Default Constructor" << endl;
}

EllipseSVG::~EllipseSVG() {
    cout << "Ellipse::Destructor" << endl;
}

void EllipseSVG::buildEllipse(vector<char*> name, vector<char*> value, Properties ellipse) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "cx")
            this->coordinate.setX(atoi(value[i]));
        else if (temp == "cy")
            this->coordinate.setY(atoi(value[i]));
        else if (temp == "rx" || temp == "r")
            this->setRadiusX(atoi(value[i]));
        else if (temp == "ry")
            this->setRadiusY(atoi(value[i]));
    }
    this->shapeProps = ellipse;
}

void EllipseSVG::setRadiusX(int x) {
    this->rx = x;
}

void EllipseSVG::setRadiusY(int y) {
    this->ry = y;
}

int EllipseSVG::getRadiusX()
{
    return this->rx;
}

int EllipseSVG::getRadiusY()
{
    return this->ry;
}

void EllipseSVG::print() {
    this->coordinate.print();
    cout << " " << this->rx << " " << this->ry << " ";
    this->shapeProps.print();
}