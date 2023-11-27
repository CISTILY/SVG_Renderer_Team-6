#include "Shape.h"

using namespace std;

Shape::Shape() {
    this->flagStroke = 0;
    this->stroke_width = 1;
    this->stroke_opacity = 1;
    this->fill_opacity = 1;
    this->scaleAngle = 1;
    this->scalePoint.setX(1);
    this->scalePoint.setY(1);
    //cout << "Shape::Constructor" << endl;
}

Shape::~Shape() {
    //cout << "Shape::Destructor" << endl;
}

void Shape::splitWord(string str, Point2D& translate, int& rotate, Point2D& scalePoint, int& scaleAngle) {
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
            rotate = stoi(value);
            str.erase(0, pos + 1);
        }
        else if (str.find("scale") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("scale") + 6, pos - 1 - 5);
            if (value.find(',') != string::npos) {
                Point2D* temp = new Point2D(value);
                scalePoint = *temp;
                delete temp;
            }
            else {
                scaleAngle = stoi(value);
            }
            str.erase(0, pos + 1);
        }
    }
}

void Shape::setTransform(Point2D translate, int angle, Point2D scalePoint, int scaleAngle) {
    this->translate = translate;
    this->rotate = angle;
    this->scaleAngle = scaleAngle;
    this->scalePoint = scalePoint;
}

void Shape::buildProperties(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "stroke") {
            string stroke = value[i];
            if (stroke == "none")
                continue;
            
            else {
                this->flagStroke = 1;
                
                this->stroke.setColor(stroke);
            }
            
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
            if (fill == "none")
                continue;

            else {
                this->fill.setColor(fill);
            }
        }
        else if (temp == "fill-opacity")
            this->fill_opacity = atof(value[i]);

        else if (temp == "transform") {
            this->splitWord(value[i], this->translate, this->rotate, this->scalePoint, this->scaleAngle);
        }
    }
}

void Shape::print() {
    cout << "(fill-opacity: " << this->fill_opacity << "), (fill: ";
    this->fill.print();
    cout << "), (stroke: ";
    this->stroke.print();
    cout << "), (stroke-width: " << this->stroke_width << "), (stroke-opacity:" << this->stroke_opacity << ")" << endl;
    cout << "transform ("; this->translate.print(); cout << ") rotate (" << this->rotate << ") scale (";
    if (this->scaleAngle != 1) {
        cout << this->scaleAngle << ")";
    }

    else if (this->scalePoint.getX() != 1 || this->scalePoint.getY() != 1) {
        this->scalePoint.print();
        cout << ")";
    }

    else {
        this->scalePoint.print();
        cout << ")";
    }
}

int Shape::getCoordinateX() {
    return this->coordinate.getX();
}

int Shape::getCoordinateY() {
    return this->coordinate.getY();
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