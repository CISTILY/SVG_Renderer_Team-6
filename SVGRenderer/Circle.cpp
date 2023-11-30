#include "Circle.h"

using namespace std;

CircleSVG::CircleSVG() {
    //cout << "Circle::Default Constructor" << endl;
}

CircleSVG::~CircleSVG() {
    //cout << "Cricle::Destructor" << endl;
}

void CircleSVG::buildShape(vector<char*> name, vector<char*> value) {
    EllipseSVG::buildShape(name, value);
}

void CircleSVG::print() {
    this->coordinate.print();
    cout << " " << this->rx << " ";
    Shape::print();
}
