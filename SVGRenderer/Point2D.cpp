#include "Point2D.h"

using namespace std;

Point2D::Point2D() {
    this->x = 0;
    this->y = 0;

    //cout << "Point2D::Default Constructor" << endl;
}

Point2D::Point2D(string s) {
    if (s[0] == '.')
        s.insert(0, 1, '0');
    string temp;
    int p = s.find(',');

    if (p == string::npos)
        p = s.find(' ');
    if (p == string::npos)
        p = s.find('\n');
    if (p == string::npos)
        p = s.find('\t');

    temp = s.substr(0, p);
    this->x = stof(temp);
    temp = s.substr(p + 1, s.length());
    this->y = stof(temp);
    //cout << "Point2D::String Constructor" << endl;
}

Point2D::Point2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Point2D::~Point2D() {
    //cout << "Point2D::Destructor" << endl;
}

void Point2D::setX(float x) {
    this->x = x;
}

void Point2D::setY(float y) {
    this->y = y;
}

void Point2D::print() {
    cout << this->x << " " << this->y;
}

string Point2D::ToString() {
    return to_string(this->x) + ", " + to_string(this->y);
}

float Point2D::getX() {
    return this->x;
}

float Point2D::getY() {
    return this->y;
}
