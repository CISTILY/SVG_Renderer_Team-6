#include "Rect.h"

RectangleSVG::RectangleSVG() {
    this->width = 0;
    this->height = 0;

    cout << "Rectangle::Default Constructor" << endl;
}

RectangleSVG::~RectangleSVG() {
    cout << "Rectangle::Destructor" << endl;
}

void RectangleSVG::buildRect(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "x")
            this->coordinate.setX(atoi(value[i]));
        else if (temp == "y")
            this->coordinate.setY(atoi(value[i]));
        else if (temp == "width")
            this->setWidth(atoi(value[i]));
        else if (temp == "height")
            this->setHeight(atoi(value[i]));
    }
}

void RectangleSVG::setWidth(int w) {
    this->width = w;
}

void RectangleSVG::setHeight(int h) {
    this->height = h;
}

int RectangleSVG::getHeight() {
    return this->height;
}

int RectangleSVG::getWidth() {
    return this->width;
}

void RectangleSVG::print() {
    this->coordinate.print();
    cout << " " << this->width << " " << this->height << " ";
    Shape::print();
}