#include "Line.h"

using namespace std;

LineSVG::LineSVG() {
    //cout << "Line::Constructor" << endl;
}

LineSVG::~LineSVG() {
    //cout << "Line::Destructor" << endl;
}

Point2D LineSVG::getEnd()
{
    return this->end;
}

void LineSVG::buildShape(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "x1")
            this->coordinate.setX(stof(value[i]));
        else if (temp == "y1")
            this->coordinate.setY(stof(value[i]));
        else if (temp == "x2")
            this->end.setX(stof(value[i]));
        else if (temp == "y2")
            this->end.setY(stof(value[i]));
    }
}

void LineSVG::print() {
    this->coordinate.print();
    cout << " ";
    this->end.print();
    cout << " ";
    Shape::print();
}