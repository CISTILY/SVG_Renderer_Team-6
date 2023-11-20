#include "Shape.h"

using namespace std;

Shape::Shape() {
    this->flagStroke = 0;
    this->stroke_width = 1;
    this->stroke_opacity = 1;
    this->fill_opacity = 1;
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

///////////////// buildProperties function ////////////////////
/*
* Input parameters:
+ vector<char*> name contains vector of Attribute Name
+ vector<char*> value contains vector of Attribute Value

* Usage:
+ Type cast name[i] from char* to string
+ Convert value[i] to corresponding type (atoi for array to int)
+ Assign value to corresponding variable

* Output:
+ Properties variable with correct common properties from "sample.svg"
*/
///////////////////////////////////////////////////////////////
void Shape::buildProperties(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "stroke") {
            this->flagStroke = 1;
            string stroke = value[i];
            this->stroke.setColor(stroke);
        }
        else if (temp == "stroke-width")
        {
            this->flagStroke = 1;
            this->stroke_width = atoi(value[i]);
        }
        else if (temp == "stroke-opacity")
        {
            this->flagStroke = 1;
            this->stroke_opacity = atof(value[i]);
        }
        else if (temp == "fill") {
            string fill = value[i];
            this->fill.setColor(fill);
        }
        else if (temp == "fill-opacity")
            this->fill_opacity = atof(value[i]);
    }
}
///////////////////////////////////////////////////////////////

void Shape::print() {
    cout << "(fill-opacity: " << this->fill_opacity << "), (fill: ";
    this->fill.print();
    cout << "), (stroke: ";
    this->stroke.print();
    cout << "), (stroke-width: " << this->stroke_width << "), (stroke-opacity:" << this->stroke_opacity << ")" << endl;
}

Color Shape::getStroke() {
    return this->stroke;
}

Color Shape::getFill() {
    return this->fill;
}

bool Shape::getFlagStroke()
{
    return this->flagStroke;
}

int Shape::getStrokeWidth() {
    return this->stroke_width;
}

double Shape::getFillOpacity() {
    return this->fill_opacity;
}

double Shape::getStrokeOpacity() {
    return this->stroke_opacity;
}