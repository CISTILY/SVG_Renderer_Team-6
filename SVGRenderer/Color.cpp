#include "Color.h"

using namespace std;

Color::Color() {
    red = blue = green = 0;
    //cout << "Color::Default Constructor" << endl;
}

Color::~Color()
{
    //cout << "Color::Destructor" << endl;
}

void Color::setColor(string s) {
    int pos = s.find(',');
    this->red = stoi(s.substr(4, pos));
    s.erase(0, pos + 1);

    pos = s.find(',');
    this->green = stoi(s.substr(0, pos));
    s.erase(0, pos + 1);

    this->blue = stoi(s.substr(0, s.length()));
}

void Color::print() {
    cout << this->red << ", " << this->green << ", " << this->blue;
}

int Color::getRed() {
    return this->red;
}

int Color::getBlue() {
    return this->blue;
}

int Color::getGreen() {
    return this->green;
}