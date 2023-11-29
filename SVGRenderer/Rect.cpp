#include "Rect.h"

RectangleSVG::RectangleSVG() {
    this->width = 0;
    this->height = 0;

    //cout << "Rectangle::Default Constructor" << endl;
}

RectangleSVG::~RectangleSVG() {
    //cout << "Rectangle::Destructor" << endl;
}

void RectangleSVG::buildRect(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "x")
            this->coordinate.setX(stof(value[i]));
        else if (temp == "y")
            this->coordinate.setY(stof(value[i]));
        else if (temp == "width")
            this->setWidth(atoi(value[i]));
        else if (temp == "height")
            this->setHeight(atoi(value[i]));
    }
}

void RectangleSVG::setWidth(float w) {
    this->width = w;
}

void RectangleSVG::setHeight(float h) {
    this->height = h;
}

float RectangleSVG::getHeight() {
    return this->height;
}

float RectangleSVG::getWidth() {
    return this->width;
}

void RectangleSVG::print() {
    this->coordinate.print();
    cout << " " << this->width << " " << this->height << " ";
    Shape::print();
}