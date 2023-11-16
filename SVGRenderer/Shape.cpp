#include "Shape.h"

using namespace std;

Shape::Shape() {
    cout << "Shape::Constructor" << endl;
}

Shape::~Shape() {
    cout << "Shape::Destructor" << endl;
}

int Shape::getCoordinateX() {
    return this->coordinate.getX();
}

int Shape::getCoordinateY() {
    return this->coordinate.getY();
}

Properties Shape::getProperties() {
    return this->shapeProps;
}