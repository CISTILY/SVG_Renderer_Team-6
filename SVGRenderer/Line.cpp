#include "Line.h"

using namespace std;

LineSVG::LineSVG() {
    cout << "Line::Constructor" << endl;
}

LineSVG::~LineSVG() {
    cout << "Line::Destructor" << endl;
}

Point2D LineSVG::getEnd()
{
    return this->end;
}

void LineSVG::buildLine(vector<char*> name, vector<char*> value, Properties line) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "x1")
            this->coordinate.setX(atoi(value[i]));
        else if (temp == "y1")
            this->coordinate.setY(atoi(value[i]));
        else if (temp == "x2")
            this->end.setX(atoi(value[i]));
        else if (temp == "y2")
            this->end.setY(atoi(value[i]));
    }
    this->shapeProps = line;
}

void LineSVG::print() {
    this->coordinate.print();
    cout << " ";
    this->end.print();
    cout << " ";
    this->shapeProps.print();
}