#include "Shape.h"

using namespace std;

Shape::Shape() {
    this->flagStroke = 0;
    this->flagStrokeWidth = 0;
    this->flagStrokeOpacity = 0;
    this->flagFill = 0;
    this->flagFillOpacity = 0;
    this->flagTransform = 0;

    this->stroke_width = 0;
    this->stroke_opacity = 1;
    this->fill_opacity = 1;
    //cout << "Shape::Constructor" << endl;
}

Shape::~Shape() {
    //cout << "Shape::Destructor" << endl;
}

void Shape::splitWord(string str, vector<Point2D>& translate, vector<float>& rotate, vector<Point2D>& scalePoint) {
    string value;
    while (str != "") {
        if (str.find("translate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("translate") + 10, pos - 1 - 9);
            Point2D* temp = new Point2D(value);
            translate.push_back(*temp);
            str.erase(0, pos + 1);
            delete temp;
        }
        else if (str.find("rotate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("rotate") + 7, pos - 1 - 6);
            rotate.push_back(stof(value));
            str.erase(0, pos + 1);
        }
        else if (str.find("scale") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("scale") + 6, pos - 1 - 5);
            Point2D* temp = new Point2D(value);
            scalePoint.push_back(*temp);
            delete temp;
            str.erase(0, pos + 1);
        }
    }
}

void Shape::buildProperties(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "stroke") {
            string stroke = value[i];
            if (stroke == "none") {
                this->flagStroke = 1;
                this->stroke.setColor("-1, -1, -1");
                continue;
            }
            
            else {
                this->flagStroke = 1;
                this->stroke.setColor(stroke);
            }
            
        }
        else if (temp == "stroke-width")
        {
            this->flagStrokeWidth = 1;
            this->stroke_width = stof(value[i]);
        }
        else if (temp == "stroke-opacity")
        {
            this->flagStrokeOpacity = 1;
            this->stroke_opacity = stof(value[i]);
        }
        else if (temp == "fill") {
            string fill = value[i];
            if (fill == "none") {
                this->flagFill = 1;
                this->fill.setColor("-1, -1, -1");
                continue;
            }

            else {
                this->flagFill = 1;
                this->fill.setColor(fill);
            }
        }
        else if (temp == "fill-opacity") {
            this->flagFillOpacity = 1;
            this->fill_opacity = stof(value[i]);
        }
            

        else if (temp == "transform") {
            this->flagTransform = 1;
            this->transform.push_back(value[i]);
        }
    }
}

void Shape::print() {
    cout << "Properties flag: ";
    cout << this->flagStroke << " " << this->flagStrokeWidth << " " << this->flagStrokeOpacity << " " << this->flagFill << " " << this->flagFillOpacity << " " << this->flagTransform;
    cout << "(fill-opacity: " << this->fill_opacity << "), (fill: ";
    this->fill.print();
    cout << "), (stroke: ";
    this->stroke.print();
    cout << "), (stroke-width: " << this->stroke_width << "), (stroke-opacity: " << this->stroke_opacity << ")" << endl;
    cout << "transform: ";
    for (int i = 0; i < this->transform.size(); ++i)
        cout << "No. " << i << this->transform[i] << " ";
}

void Shape::setStroke(ColorSVG stroke) {
    this->flagStroke = 1;
    this->stroke = stroke;
}

void Shape::setStrokeWidth(float strokeWidth) {
    this->flagStrokeWidth = 1;
    this->stroke_width = strokeWidth;
}

void Shape::setStrokeOpacity(double strokeOpacity) {
    this->flagStrokeOpacity = 1;
    this->stroke_opacity = strokeOpacity;
}

void Shape::setFill(ColorSVG fill) {
    this->flagFill = 1;
    this->fill = fill;
}

void Shape::setFillOpacity(double fillOpacity) {
    this->flagFillOpacity = 1;
    this->fill_opacity = fillOpacity;
}

void Shape::setTransform(string transform) {
    this->flagTransform = 1;
    this->transform.push_back(transform);
}

float Shape::getCoordinateX() {
    return this->coordinate.getX();
}

float Shape::getCoordinateY() {
    return this->coordinate.getY();
}

ColorSVG Shape::getStroke() {
    return this->stroke;
}

ColorSVG Shape::getFill() {
    return this->fill;
}

bool Shape::getFlagStroke()
{
    return this->flagStroke;
}

bool Shape::getFlagStrokeWidth() {
    return this->flagStrokeWidth;
}

bool Shape::getFlagStrokeOpacity() {
    return this->flagStrokeOpacity;
}

bool Shape::getFlagFill() {
    return this->flagFill;
}

bool Shape::getFlagFillOpacity() {
    return this->flagFillOpacity;
}

bool Shape::getFlagTransform() {
    return this->flagTransform;
}


float Shape::getStrokeWidth() {
    return this->stroke_width;
}

double Shape::getFillOpacity() {
    return this->fill_opacity;
}

double Shape::getStrokeOpacity() {
    return this->stroke_opacity;
}

vector<string> Shape::getTransform() {
    return this->transform;
}

FinalSVG Shape::getG()
{
    return FinalSVG();
}

