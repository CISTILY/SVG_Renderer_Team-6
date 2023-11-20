#include "Circle.h"

using namespace std;

CircleSVG::CircleSVG() {
    cout << "Circle::Default Constructor" << endl;
}

CircleSVG::~CircleSVG() {
    cout << "Cricle::Destructor" << endl;
}

/////////////////// CircleSVG Constructor ///////////////////////
/*
* Input parameters:
+ vector<char*> contains vector of Attribute Name
+ vector<char*> contains vector of Attribute Value
+ Properties variable built previously contains shape effect (stroke, fill, opacity, etc)

* Usage:
+ Type cast name[i] from char* to string
+ Convert value[i] to corresponding type (atoi for array to int)
+ Assign value to corresponding variable

* Output:
+ CricleSVG variable with correct properties from "sample.svg"
*/
/////////////////////////////////////////////////////////////////
void CircleSVG::buildCircle(vector<char*> name, vector<char*> value) {
    this->buildEllipse(name, value);
}
/////////////////////////////////////////////////////////////////


void CircleSVG::print() {
    this->coordinate.print();
    cout << " " << this->rx << " ";
    Shape::print();
}
