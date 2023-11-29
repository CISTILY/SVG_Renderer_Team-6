#include "Shape.h"

using namespace std;

Shape::Shape() {
    this->flagStroke = 0;
    this->stroke_width = 0;
    this->stroke_opacity = 1;
    this->fill_opacity = 1;
    this->rotate = 0;
    this->scalePoint.setX(1);
    this->scalePoint.setY(1);
    //cout << "Shape::Constructor" << endl;
}

Shape::~Shape() {
    //cout << "Shape::Destructor" << endl;
}

void Shape::splitWord(string str, Point2D& translate, float& rotate, Point2D& scalePoint) {
    string value;
    while (str != "") {
        if (str.find("translate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("translate") + 10, pos - 1 - 9);
            Point2D* temp = new Point2D(value);
            translate = *temp;
            str.erase(0, pos + 1);
            delete temp;
        }
        else if (str.find("rotate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("rotate") + 7, pos - 1 - 6);
            rotate = stof(value);
            str.erase(0, pos + 1);
        }
        else if (str.find("scale") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("scale") + 6, pos - 1 - 5);
            Point2D* temp = new Point2D(value);
            scalePoint = *temp;
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
            this->flagStroke = 1;
            this->stroke_width = stof(value[i]);
        }
        else if (temp == "stroke-opacity")
        {
            this->flagStroke = 1;
            this->stroke_opacity = stof(value[i]);
        }
        else if (temp == "fill") {
            string fill = value[i];
            if (fill == "none")
                continue;

            else {
                this->fill.setColor(fill);
            }
        }
        else if (temp == "fill-opacity")
            this->fill_opacity = stof(value[i]);

        else if (temp == "transform") {
            this->splitWord(value[i], this->translate, this->rotate, this->scalePoint);
        }
    }
}

void Shape::print() {
    cout << "(fill-opacity: " << this->fill_opacity << "), (fill: ";
    this->fill.print();
    cout << "), (stroke: ";
    this->stroke.print();
    cout << "), (stroke-width: " << this->stroke_width << "), (stroke-opacity: " << this->stroke_opacity << ")" << endl;
    cout << "transform ("; this->translate.print(); cout << ") rotate (" << this->rotate << ") scale (";
    this->scalePoint.print();
    cout << ")";
}

float Shape::getCoordinateX() {
    return this->coordinate.getX();
}

float Shape::getCoordinateY() {
    return this->coordinate.getY();
}

float Shape::getTranslateX() {
    return this->translate.getX();
}

float Shape::getTranslateY() {
    return this->translate.getY();
}

float Shape::getScaleX() {
    return this->scalePoint.getX();
}

float Shape::getScaleY() {
    return this->scalePoint.getY();
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

float Shape::getStrokeWidth() {
    return this->stroke_width;
}

double Shape::getFillOpacity() {
    return this->fill_opacity;
}

double Shape::getStrokeOpacity() {
    return this->stroke_opacity;
}

float Shape::getRotate() {
    return this->rotate;
}