#include "Polygon.h"

using namespace std;

PolygonSVG::PolygonSVG() {
    //cout << "Polygon::Default Constructor" << endl;
}

PolygonSVG::~PolygonSVG() {
    //cout << "Polygon::Destructor" << endl;
}

void PolygonSVG::buildPolygon(vector<char*> name, vector<char*> value) {
    this->buildPolyline(name, value);
}
